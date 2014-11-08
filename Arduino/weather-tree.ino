#include "neopixel/neopixel.h"
#include "PixelControl.h"


Adafruit_NeoPixel neopixelRingLarge = Adafruit_NeoPixel(24, 4, WS2812);
PixelControl ringLarge = PixelControl();

Adafruit_NeoPixel neopixelRingMedium = Adafruit_NeoPixel(16, 5, WS2812);
PixelControl ringMedium = PixelControl();

Adafruit_NeoPixel neopixelRingSmall = Adafruit_NeoPixel(12, 6, WS2812);
PixelControl ringSmall = PixelControl();

// This is the pixel on the top...it will be controlled differently: TODO
Adafruit_NeoPixel neopixelSingle = Adafruit_NeoPixel(1, 7, WS2812);


void setup() {

    neopixelRingLarge.begin();
    neopixelRingLarge.show();

    neopixelRingMedium.begin();
    neopixelRingMedium.show();

    neopixelRingSmall.begin();
    neopixelRingSmall.show();

    neopixelSingle.begin();
    neopixelSingle.show();

    randomSeed(analogRead(0));

    Spark.function("brew", snow);

}


void loop() {

}


int snow(String args) {

    ringSmall.AnimateRandom(neopixelRingLarge, neopixelRingLarge.Color(127, 127, 127), 100);
    ringMedium.AnimateRandom(neopixelRingMedium, neopixelRingMedium.Color(127, 127, 127), 100);
    ringLarge.AnimateRandom(neopixelRingSmall, neopixelRingSmall.Color(127, 127, 127), 100);

    return 200;
}
