#include "neopixel/neopixel.h"
#include "RandomPixels.h"


#define PIN 6


Adafruit_NeoPixel snowStrip1 = Adafruit_NeoPixel(24, PIN, WS2812);
RandomPixels snowRing1 = RandomPixels();


void setup() {

    snowStrip1.begin();
    snowStrip1.show();
    randomSeed(analogRead(0));

}


void loop() {

    snowRing1.Animate(snowStrip1, snowStrip1.Color(127, 127, 127), 100);

}
