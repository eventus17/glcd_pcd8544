GLCD for the PCD8544
====================

This is a port of the GLCD library (http://code.google.com/p/glcd-arduino/)
for the PCD8544 LCD controller, commonly found in LCD panels described as
Nokia 3310, 5110 etc. displays.

Differences between GLCD and GLCD_PCD8544:

 - Some examples that cannot be used with the smaller display have been 
   removed, including GLCDdiags.  There are far fewer opportunities for
   mis-connecting these displays, and GLCDdemo contains most of the
   other interesting examples.

 - Unused header files, over-sized bitmaps and some unused support files have
   been removed.

 - Configuration files are simpler, but located in the same place and
   similar in content.

 - The distribution build and documentation source folders have been removed.
   The builder would need to be ported, and the documentation has not been
   updated for the PCD8544.

--

readme.txt file for Arduino glcd library

INSTALL 
This library should be unziped into a folder named glcd in the libraries
directory. If you already have a folder called libraries in your Arduino 
sketchbook directory, unzip the glcd files there. If not, create a
folder called libraries in the sketchbook folder, and drop the library
folder here.
Then re-start the Arduino programming environment, and you should see the glcd 
library in the Sketch > Import LIbrary menu. 

DOCUMENTATION
The documentation can be found in the doc directory. There is an
overview document named GLCD_Documentation.pdf and detailed reference
material in GLCDref.htm.

CONFIG
Configuration files for defining pins and panel charactoristics are in the
config folder. The library is capable of auto-configuring when using a
standard processor and panel with the suggested wiring.
If you need to modify the configuration see the documentation for details
on how to do this.

EXAMPLES
The example sketches are in the examples folder and can be accessed from 
the IDE menu by selecting File > Examples > glcd

GLCDdemo provides a good introduction to the functionality of the library.

GLCDdiags is a test sketch to help get things up and running and provides
diagnostic information that can help with troubleshooting.

Other example sketches are provided that show how to use various capabilities
of the library.

FONTS
The library is supplied with fixed and variable width font definitons 
located in the fonts folder. See the documentation for information on adding
your own fonts to this folder.

BITMAPS
Bitmap images are stored in the bitmaps folder. The documentation 
describes how to create you own bitmaps using a utility provided in the 
bitmaps\glcdMakeBitmaps folder

OTHER FOLDERS
The include and device folders contain low level system files.
These do not need to be modifed for normal operation.

LICENCE
The Arduino GLCD library files are either licensed under the terms of the
GNU Lesser General Public License or are compatible with this license when
the GLCD library code is used in the Arduino software environment.
See licence.txt for details.

The glcd library was created by Michael Margolis. Extensive enhancements 
including the majority of the improvements in this release were led
by Bill Perry.

 
