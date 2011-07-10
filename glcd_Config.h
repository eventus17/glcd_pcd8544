/*
 * glcd_Config.h - User specific configuration for Arduino GLCD library
 */

#ifndef glcd_CONFIG_H
#define glcd_CONFIG_H

/*
 * Standard Configurations.
 *
 * If your board is not listed here, see the Manual Pin Configuration section below.
 */
#include "config/pcd8544_OverLoad.h"

/*
 * Manual Pin Configuration
 *
 * In order to remain compatible with the GLCD API, pin assignment can be specified
 * here.  Alternatively, include a standard configuration from the config/ directory.
 */

//#define GLCD_CS	?	// May be left undefined if CS is not used
//#define GLCD_RST	?
//#define GLCD_DC	?
//#define GLCD_SDIN	?
//#define GLCD_SCLK	?

/*========================== Optional User Defines ==================================*/

//#define GLCD_NO_SCROLLDOWN    // disable reverse scrolling (saves ~600 bytes of code)
                                // This will allow those tight on FLASH space to save a bit of code space

#endif
