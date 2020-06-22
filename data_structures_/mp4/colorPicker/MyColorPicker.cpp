#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
 MyColorPicker::MyColorPicker(double increment)
   : luminance(0), increment(increment) { }

 HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
   /* @todo [Part 3] */
   HSLAPixel pixel(175, 1, luminance);
   luminance += increment;
   if (luminance > 1) { luminance -= 1; }
   return pixel;
 }
