#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>

using namespace cs225;

PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
  }

void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  PNG* original=new PNG();
  original->readFromFile(inputFile);
  unsigned width = original->width();
  unsigned height = original->height();
  PNG* output=setupOutput(width, height);

  for (unsigned y = 0; y< height; y++) {
      for (unsigned x = 0; x < width; x++) {
          HSLAPixel *pix = original->getPixel(x, y);
          *(output->getPixel((width-1-x),(height-1-y))) = *pix;
      }
  }
output->writeToFile(outputFile);
delete original;
original=NULL;
delete output;
output=NULL;
}


PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  for (unsigned y = 0; y< height; y++) {
          for (unsigned x = 0; x < width; x++) {
          HSLAPixel * pixel1 = png.getPixel(x, y);

          pixel1->h=336.0-x*0.5;
          pixel1->s=0.88;
          pixel1->l=0.86;
          pixel1->a=0.85;
        }
      }
  return png;
}
