#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image basepic;
	Image creation;
	Image sticker1;
	Image sticker2;
  Image sticker3;
	basepic.readFromFile("alma.png");
	sticker1.readFromFile("sticker1.png");
	sticker2.readFromFile("sticker2.png");
  sticker3.readFromFile("sticker3.png");
	StickerSheet myImage = StickerSheet(basepic, 13);

	sticker1.scale(0.13);
  myImage.addSticker(sticker1, 300, 50);
  myImage.addSticker(sticker1, 500, 50);

	sticker2.scale(0.09);
  for(int x=320; x<600; x+=100)
  {
    for(int y=280; y<550; y+=100)
    {
      myImage.addSticker(sticker2, x, y);
    }
  }

  sticker3.scale(0.34);
  myImage.addSticker(sticker3, 80, 150);
  myImage.addSticker(sticker3, 680, 150);

	creation=myImage.render();
	creation.writeToFile("myImage.png");
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
