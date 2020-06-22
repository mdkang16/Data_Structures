#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  point_ = Point(99999, 99999);
  flag = NULL;
}

ImageTraversal::Iterator::Iterator(PNG* png, const Point & start, double tolerance, ImageTraversal* ptr) {
  /** @todo [Part 1] */
  x_val=start.x;
  y_val=start.y;
  ptr_=ptr;
  png_=png;
  point_=start;
  tolerance_=tolerance;
  width_=png_->width();
  height_=png_->height();

  flag=new int[width_*height_];
  for(unsigned i=0; i<width_*height_; i++){
    flag[i]=0;
  }
    neighbor(x_val, y_val);
}

ImageTraversal::Iterator::~Iterator() {
  if(flag!=NULL)
    delete [] flag;
}

void ImageTraversal::Iterator::neighbor(unsigned x, unsigned y){
  flag[x+y*width_] = 1;
  if(x<width_-1){
    ptr_->add(Point(x+1, y));
  }
  if(y<height_-1){
    ptr_->add(Point(x, y+1));
  }
  if(x>0){
    ptr_->add(Point(x-1, y));
  }
  if(y>0){
    ptr_->add(Point(x, y-1));
  }
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
   /** @todo [Part 1] */
   Point temp = ptr_->pop();

   while(calculateDelta(png_->getPixel(temp.x, temp.y), png_->getPixel(x_val, y_val)) >= tolerance_
          || flag[temp.x + temp.y * width_]) {
     if(ptr_->empty()) {
       point_=Point(99999, 99999);
       return *this;
     }
     temp=ptr_->pop();
   }
   neighbor(temp.x, temp.y);
   point_=temp;
   return *this;
}

/**
 * Iterator accessor opreator.

 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return point_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(point_==other.point_){
  return false;
  }
return true;
}
