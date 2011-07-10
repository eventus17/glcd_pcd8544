// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: t -*-

//
// glcd_Device.h - Support for PCD8544 LCD controllers
//
//	Copyright (c) 2011 Michael Smith
//
// Based on glcd_Device.h from the GLCD library:
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
// 

/// @file	glcd_Device_PCD8544.h
/// @brief	GLCD driver for PCD8544 LCD controllers

#ifndef	GLCD_DEVICE_H
#define GLCD_DEVICE_H

#include <Print.h>

// Constants used at this level.
#define NON_INVERTED		false
#define INVERTED     		true
#define BLACK				0xFF
#define WHITE				0x00

// This version of the library has no config headers, so we specify these here.
#define DISPLAY_WIDTH		84
#define DISPLAY_HEIGHT		48

//
// From the GLCD header:
//
//	Note that all data in glcd_Device is static so that all derived instances  
//	(gText instances for example) share the same device state.
//	Any added data fields should also be static unless there is explicit reason
//	to not share the field among the instances 
//
// Failure to observe this will cause odd behaviour (typically, things not
// drawing).
 
///
/// @class	glcd_Device
/// @brief	driver for the PCD8544
///
class glcd_Device : public Print   
{
private:
	// Constants
	enum {
		CMD_NOP				= 0,		//< command that does nothing

		CMD_FUNCTION_SET	= (1<<5),	//< set operating mode
		SET_POWERDOWN		= (1<<2),	//< if set, powers down the display
		SET_ENTRYMODE		= (1<<1),	//< vertical/horizontal cursor increment
		SET_EXTENDED		= (1<<0),	//< switch to extended commands

		// Basic commands
		CMD_CONTROL			= (1<<3),	//< display control
		CONTROL_BLANK		= 0x00,		//< blanks the display
		CONTROL_ALL_ON		= 0x01,		//< turns on all pixels
		CONTROL_NORMAL		= 0x04,		//< sets normal operating mode
		CONTROL_INVERTED	= 0x05,		//< sets inverse display mode

		CMD_YADDR			= (1<<6),	//< sets cursor Y address (page number)
		CMD_XADDR			= (1<<7),	//< sets cursor X address (column number)

		// Extended commands
		CMDX_SET_TEMP_COEF	= (1<<2),	//< sets LCD temperature coefficient
		CMDX_SET_BIAS		= (1<<4),	//< sets LCD bias voltage
		CMDX_SET_VOP		= (1<<7),	//< sets LCD Vop
	};

	// Arduino pin numbers for slow/rarely used pins
	static uint8_t _rst;			//< reset
	static uint8_t _cs;				//< chip select

	/// Pin info for fast pins
	struct pinfo {
		volatile uint8_t	*reg;	//< register holding pin state
		volatile uint8_t	bit;	//< bit in register assigned to pin
	};
	static pinfo		_sdin;		//< data out to the display
	static pinfo		_sclk;		//< clock out to the display
	static pinfo		_dc;

	static uint8_t _displayX;		//< cache of the display's current X co-ordinate
	static uint8_t _displayY;		//< cache of the display's current Y co-ordinate

	/// Copy of the display contents.
	static uint8_t glcd_rdcache[DISPLAY_HEIGHT/8][DISPLAY_WIDTH];

	/// Sends a command to the display
	///
	/// @param	cmd			The command byte to send.
	///
	void _sendCommand(uint8_t cmd);

	/// Sends a data byte to the display
	///
	/// @param	data		The byte to send.
	///
	void _sendData(uint8_t data);

	/// Optimised version of the Arduino shiftOut PIO SPI function
	///
	/// @param	data		The byte to send.
	///
	void _shiftOut(uint8_t data);
	
public:
	/// Constructor
	///
	glcd_Device();

	/// Required by Print
	///
	virtual void write(unsigned char c);

protected: 
	static uint8_t	 	Inverted;	//< if set, the drawn result is inverted

	/// Low-level initialisation of display and interface.
	///
	///	Following initialisation the display is cleared and the cursor is at 0,0.
	///
	/// @note It would be nice to be able to use the hardware display inverter,
	///       but inversion is handled at a higher level and changes can't be
	///		  captured at this layer.
	///
	/// @param	invert		If INVERTED, the display image is drawn inverted (BLACK
	///						pixels are transparent).
	///
    void Init(uint8_t invert = NON_INVERTED);

	/// Set a single pixel's state
	///
	/// Sets the pixel at location x,y to the specified color.
	/// x and y are relative to the 0,0 origin of the display which
	/// is the upper left corner.
	/// Requests to set pixels outside the range of the display will be ignored.
	/// 
	/// @note If the display has been set to INVERTED mode then the colors
	/// will be automically reversed.
	///
	/// @param	x		The pixel's x position
	/// @param	y		The pixel's y position
	/// @param	color	The color to set
	///
	void SetDot(uint8_t x, uint8_t y, uint8_t color);

	/// Fill a rectangle of pixels with a single colour.
	/// 
	/// sets the pixels an area bounded by x,y to x2,y2 inclusive
	/// to the specified color.
	/// 
	/// The width of the area is x2-x + 1. 
	/// The height of the area is y2-y+1 
	///
	/// @param	x		X coordinate of upper left corner
	/// @param	y		Y coordinate of upper left corner
	/// @param	x1		X coordinate of lower right corner
	/// @param	y1		Y coordinate of lower right corner
	/// @param	color	The color to set
	/// 
	void SetPixels(uint8_t x, uint8_t y,uint8_t x1, uint8_t y1, uint8_t color);

	/// Reads back the byte of data at the current co-ordinates
	///
	/// Note that the current y co-ordinate is rounded down to the base
	/// of the page before reading.
	///
    uint8_t ReadData(void);

	/// Write a byte to display device memory
	/// 
	/// The data specified is written to glcd memory at the current
	/// x,y position. If the y location is not on a byte boundary, the write
	/// is fragemented up into multiple writes.
	/// 
	/// @note the x,y address will not be the same as it was prior to this call.
 	/// The y address will remain the same but the x address will advance by one.
	/// This allows back to writes to write sequentially through memory without having
	/// to do additional x,y positioning.
	///
	/// @param	data	date byte to write to memory
	/// 
    void WriteData(uint8_t data); 

	/// set current x,y coordinate on display device
	/// 
	/// Sets the current pixel location to x,y.
	/// x and y are relative to the 0,0 origin of the display which
	/// is the upper left most pixel on the display.
	/// 
	/// @param	x		X coordinate
	/// @param	y		Y coordinate
	///
  	void GotoXY(uint8_t x, uint8_t y);   

};
  
#endif
