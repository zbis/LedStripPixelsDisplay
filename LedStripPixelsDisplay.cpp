#include <Adafruit_NeoPixel.h>
#include "LedStripPixelsDisplay.h"

#define CHAR_0        14,17,17,17,17,17,14
#define CHAR_1         4,12,20, 4, 4, 4,14
#define CHAR_2        14,17, 1, 2, 4, 8,31
#define CHAR_3        14, 1, 1, 6, 1, 1,14
#define CHAR_4         2, 6,10,31, 2, 2, 2
#define CHAR_5        31,16,30, 1, 1,17,14
#define CHAR_6        14,16,16,30,17,17,14
#define CHAR_7        31, 1, 2,14, 4, 8, 8
#define CHAR_8        14,17,17,14,17,17,14
#define CHAR_9        14,17,17,15, 1, 1,14
#define CHAR_DOT       0, 0, 0, 0, 0, 0, 4
#define CHAR_TWODOTS   0, 0,16, 0,16, 0, 0
#define CHAR_DBLQUOTE  5, 5, 0, 0, 0, 0, 0
#define CHAR_SMPQUOTE  8, 8, 0, 0, 0, 0, 0
#define CHAR_SLASH     1, 2, 2, 4, 8, 8,16
#define CHAR_LT        2, 4, 8,16, 8, 4, 2
#define CHAR_GT       16, 8, 4, 2, 4, 8,16
#define CHAR_UNDER     0, 0, 0, 0, 0, 0,31
#define CHAR_A        14,17,17,31,17,17,17
#define CHAR_B        30,17,17,30,17,17,30
#define CHAR_C        14,17,16,16,16,17,14
#define CHAR_D        30,17,17,17,17,17,30
#define CHAR_E        31,16,16,28,16,16,31
#define CHAR_F        31,16,16,24,16,16,16
#define CHAR_G        14,17,16,19,17,17,14
#define CHAR_H        17,17,17,31,17,17,17
#define CHAR_I        14, 4, 4, 4, 4, 4,14
#define CHAR_J        14, 4, 4, 4,20,20,12
#define CHAR_K        14,17,17,31,17,17,17
#define CHAR_L        16,16,16,16,16,16,31
#define CHAR_M        17,27,21,21,17,17,17
#define CHAR_N        17,25,21,21,21,19,17
#define CHAR_O        14,17,17,17,17,17,14
#define CHAR_P        30,17,17,30,16,16,16
#define CHAR_Q        14,17,17,31,17,17,17
#define CHAR_R        30,17,17,30,24,20,17
#define CHAR_S        14,17,16,14, 1, 1,14
#define CHAR_T        31, 4, 4, 4, 4, 4, 4
#define CHAR_U        17,17,17,17,17,17,14
#define CHAR_V        17,17,17,10,10,10, 4
#define CHAR_W        17,17,17,17,21,27,17
#define CHAR_X        17,17,10, 4,10,17,17
#define CHAR_Y        17,17,10,10, 4, 4, 4
#define CHAR_Z        14,17,17,31,17,17,17
#define CHAR_a         0, 0,12, 2,14,10, 6
#define CHAR_b         8, 8, 4,10,10,10,12
#define CHAR_d         2, 2, 2, 6,10,10, 6
#define CHAR_c         0, 0, 0, 6, 8, 8, 6
#define CHAR_e         0, 0, 0, 6,15, 8, 6
//#define CHAR_e         0, 0, 4,10,14, 8, 6
//#define CHAR_ecute     4, 8, 4,10,14, 8, 6
#define CHAR_ecute       4, 8, 0, 6,15, 8, 6
//#define CHAR_e         0, 0, 0, 0, 4,14, 6
#define CHAR_f         4,10, 8,12, 8, 8, 8
#define CHAR_g         0, 0, 4,10, 6, 2, 4
#define CHAR_h         8, 8, 8, 8,14,10,10
#define CHAR_i         0, 4, 0, 4, 4, 4, 4
#define CHAR_j         0, 2, 0, 2, 2,10, 4
#define CHAR_k         0, 8, 8, 8,10,12,10
#define CHAR_l         8, 8, 8, 8, 8, 8, 8
#define CHAR_m         0, 0, 0, 8,14,14,14
#define CHAR_n         0, 0, 0,12,10,10,10
#define CHAR_o         0, 0, 0, 4,10,10, 4
#define CHAR_p         0, 0,12,10,12, 8, 8
#define CHAR_q         0, 0,12,10,12, 2, 2
#define CHAR_r         0, 0, 0,10,12, 8, 8
#define CHAR_s         0, 0, 6, 8, 4, 2,12
#define CHAR_t         8, 8,12, 8, 8,10, 4
#define CHAR_u         0, 0, 0,10,10,10, 6
#define CHAR_ugrave    4, 2, 0,10,10,10, 6
#define CHAR_v         0, 0, 0,10,10,10, 4
#define CHAR_w         0, 0, 0,10,10,14,14
#define CHAR_x         0, 0, 0, 0,10, 4,10
#define CHAR_y         0, 0,10,10, 6, 2, 4
//#define CHAR_z         0, 0, 14,2, 4, 8,14
#define CHAR_z         0, 0, 0,14, 2, 8,14
#define CHAR_SPACE     0, 0, 0, 0, 0, 0, 0
#define CHAR_EXCL      4, 4, 4, 4, 4, 0, 4

LedStripPixelsDisplay::LedStripPixelsDisplay(Adafruit_NeoPixel &pixels, int ledByLines){
  //_pin = pin;
  black = pixels.Color(0, 0, 0);
  _ledByLines = ledByLines;
  _totalpixels = _ledByLines * 7;
  _pixels = pixels;
  //_pixels = Adafruit_NeoPixel(_ledByLines*7, _pin, NEO_GRB + NEO_KHZ800);
}


void LedStripPixelsDisplay::scroll_message(String msg, uint32_t color, int (*f)(int, uint32_t color)) {
  for(int i=0;i<msg.length()*6+_ledByLines;i+=2) {
    clear();
    int len = (*f)(i, color);
    for(int j=0;j<msg.length();j++){
      setChar(j*6-i+_ledByLines, color, msg[j], len, _ledByLines-1);
    }
    _pixels.show();
    delay(100);
  }
}


void LedStripPixelsDisplay::tap_message(String msg, uint32_t color, int (*f)(int, uint32_t color)) {
  //scroll_message(msg, color, f);
  /*for(int i=0;i<msg.length()*6+60;i+=2) {
    clear();
    int len = (*f)(i, color);
    for(int j=0;j<msg.length();j++){
      setChar(j*6-i+60, color, msg[j], len, 59);
    }
    pixels.show();
    delay(100);
  }*/
  for(int i=0;i<msg.length();i++){
    clear();
    int low = (msg.length() - i + 1) > 9 ? msg.length() - 9 : 0;
    for(int j=0;j<i;j++){
      setChar(j*6, color, msg[j+low], 0, 53);
    }
    for(int j=0;j<4;j++){
      (*f)(i+low-1, (j % 2) == 0 ? color : black);
      _pixels.show();
      delay((j%2)==0 ? 250 : 100);
    }
  }
}

void LedStripPixelsDisplay::message(String msg, uint32_t color) {
  for(int j=0;j<msg.length();j++){
    setChar(j*6, color, msg[j]);
  }
}

void LedStripPixelsDisplay::clear() {
	clear_color(black);
}

void LedStripPixelsDisplay::clear_color(uint32_t color) {
	for(int cl=0;cl<_totalpixels;cl++) {
		_pixels.setPixelColor(cl, color);
	}
}

void LedStripPixelsDisplay::digits(int pos, uint32_t color, byte l0, byte l1, byte l2, byte l3, byte l4, byte l5, byte l6, int from, int to) {
   line(pos, color, 6, l0, from, to);
   line(pos, color, 5, l1, from, to);
   line(pos, color, 4, l2, from, to);
   line(pos, color, 3, l3, from, to);
   line(pos, color, 2, l4, from, to);
   line(pos, color, 1, l5, from, to);
   line(pos, color, 0, l6, from, to);
}

void LedStripPixelsDisplay::line(int pos, uint32_t color, byte line, byte content, int from, int to) {
  onebit(pos, color, line, content, 0, from, to);
  onebit(pos, color, line, content, 1, from, to);
  onebit(pos, color, line, content, 2, from, to);
  onebit(pos, color, line, content, 3, from, to);
  onebit(pos, color, line, content, 4, from, to);
}

void LedStripPixelsDisplay::onebit(int pos, uint32_t color, byte line, byte content, byte col, int from, int to) {
  if(pos+col<from){
  }else if(pos+col>to) {
  }else{
    byte colp = 16 >> col;
    onebit(color, pos+col, line, (content & colp)==colp);
  }
}

void LedStripPixelsDisplay::onebit(uint32_t color, int col, byte line, bool enabled) {
  int c = _ledByLines * line + (line % 2 == 0 ? col : (_ledByLines-1-col));
  if(enabled)
    _pixels.setPixelColor(c, color);
  else
    _pixels.setPixelColor(c, black);
}

void LedStripPixelsDisplay::setChar(int pos, uint32_t color, char ch){
  setChar(pos, color, ch, 0, _ledByLines-1);
}
void LedStripPixelsDisplay::setChar(int pos, uint32_t color, char ch, int from, int to) {
  switch(ch){
    case '0':digits(pos, color, CHAR_0, from, to);break;
    case '1':digits(pos, color, CHAR_1, from, to);break;
    case '2':digits(pos, color, CHAR_2, from, to);break;
    case '3':digits(pos, color, CHAR_3, from, to);break;
    case '4':digits(pos, color, CHAR_4, from, to);break;
    case '5':digits(pos, color, CHAR_5, from, to);break;
    case '6':digits(pos, color, CHAR_6, from, to);break;
    case '7':digits(pos, color, CHAR_7, from, to);break;
    case '8':digits(pos, color, CHAR_8, from, to);break;
    case '9':digits(pos, color, CHAR_9, from, to);break;
    case ':':digits(pos, color, CHAR_TWODOTS, from, to);break;
    case '.':digits(pos, color, CHAR_DOT, from, to);break;
    case '/':digits(pos, color, CHAR_SLASH, from, to);break;
    case '<':digits(pos, color, CHAR_LT, from, to);break;
    case '>':digits(pos, color, CHAR_GT, from, to);break;
    case '_':digits(pos, color, CHAR_UNDER, from, to);break;
    case '\'':digits(pos, color, CHAR_SMPQUOTE, from, to);break;
    case '"':digits(pos, color, CHAR_DBLQUOTE, from, to);break;
    case '!':digits(pos, color, CHAR_EXCL, from, to);break;
    case 'A':digits(pos, color, CHAR_A, from, to);break;
    case 'B':digits(pos, color, CHAR_B, from, to);break;
    case 'C':digits(pos, color, CHAR_C, from, to);break;
    case 'D':digits(pos, color, CHAR_D, from, to);break;
    case 'E':digits(pos, color, CHAR_E, from, to);break;
    case 'F':digits(pos, color, CHAR_F, from, to);break;
    case 'G':digits(pos, color, CHAR_G, from, to);break;
    case 'H':digits(pos, color, CHAR_H, from, to);break;
    case 'I':digits(pos, color, CHAR_I, from, to);break;
    case 'J':digits(pos, color, CHAR_J, from, to);break;
    case 'K':digits(pos, color, CHAR_K, from, to);break;
    case 'L':digits(pos, color, CHAR_L, from, to);break;
    case 'M':digits(pos, color, CHAR_M, from, to);break;
    case 'N':digits(pos, color, CHAR_N, from, to);break;
    case 'O':digits(pos, color, CHAR_O, from, to);break;
    case 'P':digits(pos, color, CHAR_P, from, to);break;
    case 'Q':digits(pos, color, CHAR_Q, from, to);break;
    case 'R':digits(pos, color, CHAR_R, from, to);break;
    case 'S':digits(pos, color, CHAR_S, from, to);break;
    case 'T':digits(pos, color, CHAR_T, from, to);break;
    case 'U':digits(pos, color, CHAR_U, from, to);break;
    case 'V':digits(pos, color, CHAR_V, from, to);break;
    case 'W':digits(pos, color, CHAR_W, from, to);break;
    case 'X':digits(pos, color, CHAR_X, from, to);break;
    case 'Y':digits(pos, color, CHAR_Y, from, to);break;
    case 'Z':digits(pos, color, CHAR_Z, from, to);break;
    case 'a':digits(pos, color, CHAR_a, from, to);break;
    case 'b':digits(pos, color, CHAR_b, from, to);break;
    case 'c':digits(pos, color, CHAR_c, from, to);break;
    case 'd':digits(pos, color, CHAR_d, from, to);break;
    case 'e':digits(pos, color, CHAR_e, from, to);break;
    case '\xe9':digits(pos, color, CHAR_ecute, from, to);break;
    case 'f':digits(pos, color, CHAR_f, from, to);break;
    case 'g':digits(pos, color, CHAR_g, from, to);break;
    case 'h':digits(pos, color, CHAR_h, from, to);break;
    case 'i':digits(pos, color, CHAR_i, from, to);break;
    case 'j':digits(pos, color, CHAR_j, from, to);break;
    case 'k':digits(pos, color, CHAR_k, from, to);break;
    case 'l':digits(pos, color, CHAR_l, from, to);break;
    case 'm':digits(pos, color, CHAR_m, from, to);break;
    case 'n':digits(pos, color, CHAR_n, from, to);break;
    case 'o':digits(pos, color, CHAR_o, from, to);break;
    case 'p':digits(pos, color, CHAR_p, from, to);break;
    case 'q':digits(pos, color, CHAR_q, from, to);break;
    case 'r':digits(pos, color, CHAR_r, from, to);break;
    case 's':digits(pos, color, CHAR_s, from, to);break;
    case 't':digits(pos, color, CHAR_t, from, to);break;
    case 'u':digits(pos, color, CHAR_u, from, to);break;
    case '\xf9':digits(pos, color, CHAR_ugrave, from, to);break;
    case 'v':digits(pos, color, CHAR_v, from, to);break;
    case 'w':digits(pos, color, CHAR_w, from, to);break;
    case 'x':digits(pos, color, CHAR_x, from, to);break;
    case 'y':digits(pos, color, CHAR_y, from, to);break;
    case 'z':digits(pos, color, CHAR_z, from, to);break;
    case ' ':digits(pos, color, CHAR_SPACE, from, to);break;
    default:digits(pos, color, CHAR_SPACE, from, to);break;
  }
}



void LedStripPixelsDisplay::drawPath(byte p[], uint32_t color) {
  drawPath(p, color, 0, sizeof(p));
}

void LedStripPixelsDisplay::drawPath(byte p[], uint32_t color, int from, int to) {
  drawPath(p, color, from, to, 5, 0);
}
void LedStripPixelsDisplay::drawPath(byte p[], uint32_t color, int from, int to, int w, int offset) {
  for(int i=from;i<=to;i++){
    int v = p[i];
    onebit(color, offset + (v % w), v / w, true);
  }
}