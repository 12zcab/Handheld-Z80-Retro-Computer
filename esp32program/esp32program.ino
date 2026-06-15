#define RXD1 21
#define TXD1 20
#include <TFT_eSPI.h>
//#define LOAD_FONT2   pls copy this to TFT_eSPI User_Setup.h
//#define TFT_MISO 8
//#define TFT_MOSI 5
//#define TFT_SCLK 4
//#define TFT_CS 0
//#define TFT_DC 3
//#define TFT_RST 1
TFT_eSPI tft = TFT_eSPI();
uint8_t posx = 0; //16/480
uint8_t posy = 0; //16/320
void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);

  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
}
bool is_printable_ascii(int ch) {
    return (ch >= 32 && ch <= 126);
}
void loop() {
  if (Serial1.available()) {
    char rc;
    rc = Serial1.read();
    if (is_printable_ascii(rc));
      tft.setTextFont(2);
      tft.drawString(rc, posx * 16, posy * 16);
      posx++;
      if (posx >= 30){
        posx = 0;
        posy++;
      }
      if (posy >= 20){
        posy = 20;      //erm yah currently no scrolling function available :|
      }
    }
    Serial.write(rc);
  }
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
}
