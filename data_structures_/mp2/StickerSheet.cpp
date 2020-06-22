#include <iostream>
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;


StickerSheet::StickerSheet(const Image & picture, unsigned max){

  base = picture;
  maxx=max;
  x_ = new unsigned[maxx];
  y_ = new unsigned[maxx];
  st_count = new Image*[maxx];

  for(unsigned int i=0; i<maxx; i++)
  {
    st_count[i]=NULL;
    x_[i]=0;
    y_[i]=0;
  }

}

StickerSheet::~StickerSheet(){
  clear();
}

StickerSheet::StickerSheet (const StickerSheet &other){

  copy(other);

}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
  if(this!=&other)
  {
    clear();
    copy(other);
  }
  return *this;
}

void StickerSheet::changeMaxStickers (unsigned max){

  StickerSheet original(base, max);
  if(maxx>max)
  {
    for(unsigned int i=0; i<max; i++)
    {
      if(st_count[i]!=NULL)
      {
        original.x_[i]=x_[i];
        original.y_[i]=y_[i];
        original.st_count[i]=new Image(*st_count[i]);
      }
    }
  }
  else if(max>maxx)
  {
    for(unsigned int i=0; i<maxx; i++)
    {
      if(st_count[i]!=NULL)
      {
        if(i<maxx)
        {
          original.x_[i]=x_[i];
          original.y_[i]=y_[i];
          original.st_count[i]=new Image(*st_count[i]);
        }
      }
    }
  }
  else if(max==maxx)
  {
    return;
  }
  *this=original;

}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){

  for(unsigned int i=0; i<maxx; i++)
  {
      if(st_count[i] == NULL)
      {
        x_[i] = x;
        y_[i] = y;
        st_count[i] = new Image(sticker);
        return (int)i;
      }
    }
    return -1;

}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){

  if(index>maxx)
  {
      return false;
  }
  else if(st_count[index]==NULL)
  {
    return false;
  }
  else
  {
    x_[index] = x;
    y_[index] = y;
    return true;
  }
}

void StickerSheet::removeSticker (unsigned index){
  if(st_count[index]!=NULL)
  {
    if(maxx>index)
    {
      x_[index]=0;
      y_[index]=0;
      delete st_count[index];
      st_count[index]=NULL;
    }
  }

}

Image * StickerSheet::getSticker (unsigned index) const{

  if(st_count[index] != NULL)
    {
      if(maxx>index)
      {
        return st_count[index];
      }
    }

    return NULL;
}

Image StickerSheet::render () const{

  unsigned z;
  double st_h=base.height();
  double st_w=base.width();
  double temp_h, temp_w;
  int x_location, y_location;

    for(z=0; z<maxx; z++)
    {
      if(st_count[z] != NULL){
        x_location=x_[z];
        y_location=y_[z];
        temp_h=st_count[z]->height()+y_location;
        temp_w=st_count[z]->width()+x_location;

        if(st_h<temp_h)
        {
          st_h=temp_h;
        }

        if(st_w<temp_w)
        {
          st_w=temp_w;
        }

      }
    }
    Image myimage=base;
    myimage.resize(st_w, st_h);

    for(z=0; z<maxx; z++)
    {
      if(st_count[z] != NULL)
      {
        x_location=x_[z];
        y_location=y_[z];

        for(unsigned int i=0; i<st_count[z]->width(); i++)
        {
          for(unsigned int j=0; j<st_count[z]->height(); j++)
          {
            HSLAPixel& stpix=st_count[z]->getPixel(i,j);
            HSLAPixel& newpix=myimage.getPixel(i+x_location,j+y_location);
            if(stpix.a!=0)
            {
              newpix.h = stpix.h;
              newpix.s = stpix.s;
              newpix.l = stpix.l;
              newpix.a = stpix.a;
            }
          }
        }
      }
    }
    return myimage;
}

void StickerSheet::clear(){
  for(unsigned int i=0; i<maxx; i++)
  {
    delete st_count[i];
    st_count[i]=NULL;
  }

  if(st_count!=NULL)
  {
    delete [] st_count;
    st_count=NULL;
  }

  if(x_!=NULL)
  {
    delete [] x_;
    x_=NULL;
  }

  if(y_!=NULL)
  {
    delete [] y_;
    y_=NULL;
  }

}

void StickerSheet::copy(const StickerSheet& other){

  base = other.base;
  maxx = other.maxx;
  x_ = new unsigned[maxx];
  y_ = new unsigned[maxx];
  st_count = new Image*[maxx];

  for(unsigned int i=0; i<maxx; i++)
  {
    st_count[i]=NULL;
    if(other.st_count[i]!=NULL)
    {
      st_count[i] = new Image(*other.st_count[i]);
      x_[i]=other.x_[i];
      y_[i]=other.y_[i];
    }
  }
}
