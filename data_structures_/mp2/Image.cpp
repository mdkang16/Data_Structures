#include <iostream>
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;

void Image::lighten()
{

  for (unsigned x = 0; x < this->width(); x++) {
     for (unsigned y = 0; y < this->height(); y++) {
       HSLAPixel & pixel = this->getPixel(x, y);
       pixel.l=pixel.l+0.1;
       if(pixel.l>1)
       {
         pixel.l=1;
       }
       if(pixel.l<0)
       {
         pixel.l=0;
       }
     }
    }
}

void Image::lighten(double amount)
{
  for (unsigned x = 0; x < this->width(); x++) {
     for (unsigned y = 0; y < this->height(); y++) {
       HSLAPixel & pixel = this->getPixel(x, y);

       pixel.l=pixel.l+amount;
       if(pixel.l>1)
       {
         pixel.l=1;
       }
       if(pixel.l<0)
       {
         pixel.l=0;
       }
     }
   }
}

void Image::darken()
{
  for (unsigned x = 0; x < this->width(); x++) {
     for (unsigned y = 0; y < this->height(); y++) {
       HSLAPixel & pixel = this->getPixel(x, y);

       pixel.l=pixel.l-0.1;
       if(pixel.l>1)
       {
         pixel.l=1;
       }
       if(pixel.l<0)
       {
         pixel.l=0;
       }
     }
    }
}

void Image::darken(double amount)
{
  PNG image;
  for (unsigned x = 0; x < this->width(); x++) {
     for (unsigned y = 0; y < this->height(); y++) {
       HSLAPixel & pixel = this->getPixel(x, y);

       pixel.l=pixel.l-amount;
       if(pixel.l>1)
       {
         pixel.l=1;
       }
       if(pixel.l<0)
       {
         pixel.l=0;
       }
     }
   }
}

void Image::saturate()
{
  for (unsigned x = 0; x < this->width(); x++) {
     for (unsigned y = 0; y < this->height(); y++) {
       HSLAPixel & pixel = this->getPixel(x, y);

       pixel.s=pixel.s+0.1;
       if(pixel.s>1)
       {
         pixel.s=1;
       }
       if(pixel.s<0)
       {
         pixel.s=0;
       }
     }
    }
}

void Image::saturate(double amount)
{
  for (unsigned x = 0; x < this->width(); x++) {
     for (unsigned y = 0; y < this->height(); y++) {
       HSLAPixel & pixel = this->getPixel(x, y);

       pixel.s=pixel.s+amount;
       if(pixel.s>1)
       {
         pixel.s=1;
       }
       if(pixel.s<0)
       {
         pixel.s=0;
       }
     }
   }
}

void Image::desaturate()
{
  for (unsigned x = 0; x < this->width(); x++) {
     for (unsigned y = 0; y < this->height(); y++) {
       HSLAPixel & pixel = this->getPixel(x, y);

       pixel.s=pixel.s-0.1;
       if(pixel.s>1)
       {
         pixel.s=1;
       }
       if(pixel.s<0)
       {
         pixel.s=0;
       }
     }
    }
}

void Image::desaturate(double amount)
{
  for (unsigned x = 0; x < this->width(); x++) {
     for (unsigned y = 0; y < this->height(); y++) {
       HSLAPixel & pixel = this->getPixel(x, y);

       pixel.s=pixel.s-amount;
       if(pixel.s>1)
       {
         pixel.s=1;
       }
       if(pixel.s<0)
       {
         pixel.s=0;
       }
     }
   }
}

void Image::grayscale()
{
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees)
{
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      pixel.h=pixel.h+degrees;

      if(pixel.h>360)
      {
        while(pixel.h>360){
        pixel.h=pixel.h-360;
        }
      }
      if(pixel.h<0)
      {
        while(pixel.h<0)
        {
          pixel.h=pixel.h+360;
        }
      }

    }
  }
}

void Image::illinify()
{
  for (unsigned x = 0; x < this->width(); x++) {
     for (unsigned y = 0; y < this->height(); y++) {
       HSLAPixel & pixel = this->getPixel(x, y);
       if (pixel.h>113.5 && pixel.h<293.5)
       {
         pixel.h=216;
       }
       else
       {
         pixel.h=11;
       }
     }
   }
}

void Image::scale(double factor)
{
  PNG temp(this->width(), this->height());

  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      HSLAPixel & temp1 = temp.getPixel(x,y);
      temp1=pixel;
    }
  }
  this->resize(this->width() *factor, this->height() *factor);
  if (factor<1)
  {
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
        int tempx= (int)((1/factor) *x);
        int tempy= (int)((1/factor) *y);
        HSLAPixel & pixel1 = temp.getPixel(tempx, tempy);
        HSLAPixel & pixel = this->getPixel(x, y);
        pixel=pixel1;
      }
    }
  }
  if (factor>1)
  {

    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
        int tempx= (int)((1/factor) *x);
        int tempy= (int)((1/factor) *y);
        HSLAPixel & pixel1 = temp.getPixel(tempx, tempy);
        HSLAPixel & pixel = this->getPixel(x, y);
        pixel=pixel1;
            }
          }
        }

}

void Image::scale(unsigned w, unsigned h)
{
  unsigned factor;
  PNG temp(this->width(), this->height());
  if (w==temp.width() || h==temp.height())
  {
    factor=1;
  }

  factor = ((h/temp.height()) > (w/temp.width()) ? (w/temp.width()) : (h/temp.height()) );
  scale(factor);
}
