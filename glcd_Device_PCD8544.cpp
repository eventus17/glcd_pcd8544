// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: t -*-

//
// glcd_Device.cpp - Support for PCD8544 LCD controllers
//
//	Copyright (c) 2011 Michael Smith
//
// Based on glcd_Device.cpp from the GLCD library:
//
//	Copyright (c) 2009, 2010 Michael Margolis and Bill Perry
//
// This file is a contribution to the Arduino GLCD library.
//
// GLCD is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 2.1 of the License, or
// (at your option) any later version.
// GLCD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License
// along with GLCD.  If not, see <http://www.gnu.org/licenses/>.
// the glcd_Device class impliments the protocol for sending and receiving data and commands to a GLCD device.
// 

/// @file	glcd_Device_PCD8544.cpp
/// @brief	GLCD driver for PCD8544 LCD controllers

#include <WProgram.h>

#include "glcd_Config.h"
#include "include/glcd_Device.h"
#include "include/arduino_io.h"

#define debugNL(str, num)	//Serial.print(str " "); Serial.println(num, DEC)
#define debugN(str, num)	//Serial.print(str " "); Serial.print(num, DEC); Serial.print(" ")
#define debugXNL(str, num)	//Serial.print(str " "); Serial.println(num, HEX)
#define debugXN(str, num)	//Serial.print(str " "); Serial.print(num, HEX); Serial.print(" ")

// Validate the pin configuration
#if !defined(GLCD_SCLK) || !defined(GLCD_SDIN) || !defined(GLCD_DC) || !defined(GLCD_RST)
# error Pins not configured - see glcd_Config.h
#endif
#if !defined(GLCD_CS)
# define GLCD_CS	0
#endif

// static variables
uint8_t	glcd_Device::Inverted; 
uint8_t	glcd_Device::glcd_rdcache[DISPLAY_HEIGHT/8][DISPLAY_WIDTH];

uint8_t	glcd_Device::_rst;
uint8_t	glcd_Device::_cs;

glcd_Device::pinfo	glcd_Device::_sdin;
glcd_Device::pinfo	glcd_Device::_sclk;
glcd_Device::pinfo	glcd_Device::_dc;

uint8_t	glcd_Device::_displayX;
uint8_t	glcd_Device::_displayY;

void
glcd_Device::_sendCommand(uint8_t cmd)
{
	debugNL("cmd", cmd);

	// switch briefly to command mode to send the command
	*_dc.reg &= ~_dc.bit;
	_shiftOut(cmd);
	*_dc.reg |= _dc.bit;
}

void
glcd_Device::_sendData(uint8_t data)
{

	// refuse to send data if we have walked off the edge of the display
	if (_displayX < DISPLAY_WIDTH) {
		debugN("data", data);debugNL("x", _displayX);
		_shiftOut(data);

		// maintain the Read Cache
		glcd_rdcache[_displayY / 8][_displayX] = data;

		// Update our idea of where the next display byte will go
		// Note that the display may actually wrap, but we ignore this
		// as the rest of the library does not depend on the behaviour
		// Note also that if X goes out of bounds we must invalidate Y
		// as it may have changed too.
		if (++_displayX >= DISPLAY_WIDTH) {
			_displayY = DISPLAY_HEIGHT;
		}
	} else {
		debugNL("overX", _displayX);
	}
}

void
glcd_Device::_shiftOut(uint8_t data)
{
	register uint8_t mask;
	register uint8_t sdin_high = _sdin.bit;
	register uint8_t sdin_low = ~sdin_high;
	register uint8_t sclk_high = _sclk.bit;
	register uint8_t sclk_low = ~sclk_high;

	// must be volatile as they may alias
	register volatile uint8_t *sdin = _sdin.reg;
	register volatile uint8_t *sclk = _sclk.reg;

	// mask interrupts while we shift the byte out
	uint8_t sreg = SREG;
	cli();

	for (mask = 0x80; mask; mask >>=1) {
		if (data & mask) {
			*sdin |= sdin_high;
		} else {
			*sdin &= sdin_low;
		}
		*sclk |= sclk_high;
		*sclk &= sclk_low;
	}

	// restore interrupt state
	SREG = sreg;
}

glcd_Device::glcd_Device()
{
}

void
glcd_Device::write(unsigned char c)
{
	// we don't support printing anything at this level
}


void 
glcd_Device::Init(uint8_t invert)
{  
	debugNL("init start", 0);

	// Configure display interface pins
	pinMode(GLCD_SCLK, OUTPUT);
	_sclk.reg = portOutputRegister(digitalPinToPort(GLCD_SCLK));
	_sclk.bit = digitalPinToBitMask(GLCD_SCLK);

	pinMode(GLCD_SDIN, OUTPUT);
	_sdin.reg = portOutputRegister(digitalPinToPort(GLCD_SDIN));
	_sdin.bit = digitalPinToBitMask(GLCD_SDIN);

	pinMode(GLCD_DC, OUTPUT);
	_dc.reg = portOutputRegister(digitalPinToPort(GLCD_DC));
	_dc.bit = digitalPinToBitMask(GLCD_DC);

	// If CS is connected, assert it to select the display. The
	// display doesn't seem to care if we leave it low forever.
	if (GLCD_CS > 0) {
		pinMode(GLCD_CS, OUTPUT);
		digitalWrite(GLCD_CS, LOW);
	}

	// Reset the display.
	pinMode(GLCD_RST, OUTPUT);
	digitalWrite(GLCD_RST, LOW);
	delay(500);
	digitalWrite(GLCD_RST, HIGH);

	// configure magic numbers
	_sendCommand(CMD_FUNCTION_SET | SET_EXTENDED);
	_sendCommand(CMDX_SET_BIAS | 4);	// generally-accepted value
	_sendCommand(CMDX_SET_VOP | 50);	// generally-accepted value

	// set horizontal addressing, display active
	_sendCommand(CMD_FUNCTION_SET | 0);

	// set 'normal' display mode
	_sendCommand(CMD_CONTROL | CONTROL_NORMAL);

	this->Inverted = invert;

	/*
	 * All hardware initialization is complete.
	 *
	 * Now, clear the screen and home the cursor to ensure that the display always starts
	 * in an identical state after being initialized.
	 *
	 * Note: the reason that SetPixels() below always uses WHITE, is that once the
	 * the invert flag is in place, the lower level read/write code will invert data
	 * as needed.
	 * So clearing an areas to WHITE when the mode is INVERTED will set the area to BLACK
	 * as is required.
	 */

	this->SetPixels(0,0, DISPLAY_WIDTH-1,DISPLAY_HEIGHT-1, WHITE);
	this->GotoXY(0,0);

	debugNL("init done", 0);
}

void 
glcd_Device::SetDot(uint8_t x, uint8_t y, uint8_t color) 
{
	uint8_t data;

	debugN("dot", x); debugN("", y); debugNL("", color);

	if((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT))
		return;
	
	this->GotoXY(x, y-y%8);					// read data from display memory
  	
	data = this->ReadData();
	if(color == BLACK){
		data |= 0x01 << (y%8);				// set dot
	} else {
		data &= ~(0x01 << (y%8));			// clear dot
	}
	this->WriteData(data);					// write data back to display
}

void
glcd_Device::SetPixels(uint8_t x, uint8_t y,uint8_t x2, uint8_t y2, uint8_t color)
{
	uint8_t mask, pageOffset, h, i, data;
	uint8_t height = y2-y+1;
	uint8_t width = x2-x+1;
	
	debugN("box", x); debugN("", y); debugN("", x2); debugN("", y2); debugNL("", color);

	pageOffset = y%8;
	y -= pageOffset;
	mask = 0xFF;
	if(height < 8-pageOffset) {
		mask >>= (8-height);
		h = height;
	} else {
		h = 8-pageOffset;
	}
	mask <<= pageOffset;
	
	this->GotoXY(x, y);
	for(i=0; i < width; i++) {		// XXX suboptimal for pageOffset == 0
		data = this->ReadData();
		
		if(color == BLACK) {
			data |= mask;
		} else {
			data &= ~mask;
		}

		this->WriteData(data);
	}
	
	while(h+8 <= height) {
		h += 8;
		y += 8;
		this->GotoXY(x, y);
		
		for(i=0; i <width; i++) {
			this->WriteData(color);
		}
	}
	
	if(h < height) {
		mask = ~(0xFF << (height-h));
		this->GotoXY(x, y+8);
		
		for(i=0; i < width; i++) {
			data = this->ReadData();
		
			if(color == BLACK) {
				data |= mask;
			} else {
				data &= ~mask;
			}
	
			this->WriteData(data);
		}
	}
}

uint8_t
glcd_Device::ReadData()
{
	uint8_t x, data;

	x = _displayX;
	if(x >= DISPLAY_WIDTH)
	{
		return(0);
	}
	data = glcd_rdcache[_displayY / 8][x];

	if(this->Inverted)
	{
		data = ~data;
	}
	//debugXNL("read", data);
	return(data);
}

void
glcd_Device::WriteData(uint8_t data) 
{
	uint8_t displayData, yOffset;

	debugN("write", data);debugNL("inverted", Inverted);

	if (_displayX >= DISPLAY_WIDTH){
		return;
	}

	yOffset = _displayY % 8;

	if(yOffset != 0) {
		// first page
		displayData = this->ReadData();

		displayData |= data << yOffset;

		if(this->Inverted) {
			displayData = ~displayData;
		}
		_sendData(displayData);

		// second page

		/*
		 * Make sure to goto y address of start of next page
		 * and ensure that we don't fall off the bottom of the display.
		 */
		uint8_t ysave = _displayY;
		if(((ysave+8) & ~7) >= DISPLAY_HEIGHT) {
			return;
		}
	
		this->GotoXY(_displayX - 1, ((ysave+8) & ~7));

		displayData = this->ReadData();

		displayData |= data >> (8-yOffset);
		if(this->Inverted){
			displayData = ~displayData;
		}
		_sendData(displayData);
		this->GotoXY(_displayX, ysave);
	}else 
	{
		// just this code gets executed if the write is on a single page
		if(this->Inverted)
			data = ~data;	  

		_sendData(data);

	}
}

void 
glcd_Device::GotoXY(uint8_t x, uint8_t y)
{
	debugN("goto", x); debugN("", y); debugN("from", _displayX); debugNL("", _displayY);

	if (x != _displayX) {
		if (x >= DISPLAY_WIDTH)
			return;
		debugN(" moveX", _displayX); debugNL("->", x);
		_sendCommand(CMD_XADDR | x);
		_displayX = x;
	}

	if (y != _displayY) {
		if (y >= DISPLAY_HEIGHT)
			return;
		debugN(" moveY", _displayY); debugNL("->", y);
		if ((y / 8) != (_displayY / 8))
			_sendCommand(CMD_YADDR | (y / 8));
		_displayY = y;
	}
	debugN("  at", _displayX); debugNL("", _displayY);
}
