#include <cstring>
#include <U8g2lib.h>

using namespace std;

//U8g2 Contructor
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 5, /* data=*/ 4, /* reset=*/ 16);
// Alternative board version. Uncomment if above doesn't work.
// U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 2, /* reset=*/ 4);

u8g2_uint_t offset;     // current offset for the scrolling text
u8g2_uint_t width;      // pixel width of the scrolling text (must be lesser than 128 unless U8G2_16BIT is defined
u8g2_uint_t dwidth;

String temp = "73.6 ";

//const char *text = "COMO SE DICE? "; // scroll this text from right to left


void setup(void) {
  u8g2.begin();
  u8g2.setFont(u8g2_font_logisoso32_tf); // set the target font to calculate the pixel width
  u8g2.setFontMode(0);    // enable transparent mode, which is faster
  u8g2_uint_t dwidth = u8g2.getDisplayWidth();
}


void loop(void) {
  u8g2_uint_t x;

  temp.concat("outside");
  char *text = new char[temp.length() + 1];
  std::strcpy(text, temp.c_str());

  width = u8g2.getUTF8Width(text);    // calculate the pixel width of the text

  u8g2.firstPage();
  do {

    // draw the scrolling text at current offset
    x = offset;
    u8g2.setFont(u8g2_font_logisoso32_tf);   // set the target font
    do {                // repeated drawing of the scrolling text...
      u8g2.drawUTF8(x, 32, text);     // draw the scolling text
      x += width;           // add the pixel width of the scrolling text
    } while ( x < dwidth );   // draw again until the complete display is filled

    u8g2.setFont(u8g2_font_logisoso32_tf);   // draw the current pixel width
    u8g2.setCursor(0, 64);
    u8g2.print(width);          // this value must be lesser than 128 unless U8G2_16BIT is set

  } while ( u8g2.nextPage() );

  offset -= 1;            // scroll by one pixel
  if ( (u8g2_uint_t)offset < (u8g2_uint_t) - width )
    offset = 0;             // start over again
}
