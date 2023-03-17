#include <Adafruit_ST7789.h>
#include <Adafruit_ST77xx.h>
#include <Adafruit_GFX.h>
#include <SPI.h>

#define TFT_DC 9 // pin of your choice
#define TFT_RST 8 // pin of your choice
#define TFT_MOSI 7 // fixed pin
#define TFT_SCLK 13 // fixed pin

// For 1.3", 1.54", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_DC, TFT_RST, TFT_SCLK, TFT_MOSI);

void setup() {

Serial.begin(9600);
Serial.println(); // cut the gibberish first line Serial Monitor
Serial.println();
Serial.print("Hello"); // test Serial Monitor

tft.init(240, 240); // initialize a ST7789 chip, 240×240 pixels
tft.fillScreen(ST77XX_BLACK);
tft.setCursor(20, 50);
tft.setTextColor(ST77XX_YELLOW);
tft.setTextSize(3);
tft.print("Hello world"); // initialization message on the TFT display
tft.println("SURPSCON on the air");
}

void loop (){

}
