/*
 * allFonts.h font header for GLCD library 
 * The fonts listed below will be available in a sketch if this file is included
 *
 * If you create your own fonts you can add the header to this file
 *
 * Note that the build environment only holds a font in Flash if its selected 
 * so there is no penalty to including a font file here if its not used 
 */

#include "SystemFont5x7.h"       // system font
#include "Arial14.h"             // proportional font
#include "Arial_bold_14.h"       // Bold proportional font
#include "Corsiva_12.h"
#include "Verdana_digits_24.h"   // large proportional font - numerals only 
#include "fixednums7x15.h"       // fixed width font - numerals only 
#include "fixednums8x16.h"       // fixed width font - numerals only 
#include "fixednums15x31.h"      // fixed width font - numerals only 

// The following fonts are not part of the stock GLCD distribution
// All are free for general use; see the individual headers for copyright
// and source information.
//
#include "Proggy.h"		// Fonts from proggyfonts.com
#include "TomThumb.h"		// A compact (~4x6) terminal-style font
#include "Tiny.h"		// A very small 4pt font
#include "F04b.h"		// A family of compact, stylish fonts
#include "CalHenderson.h"	// Freeware fonts by Cal Henderson
#include "dictator.h"		// a low-rez font in 4 and 8pts
