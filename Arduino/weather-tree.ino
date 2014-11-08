#include "neopixel/neopixel.h"
#include "RandomPixels.h"


Adafruit_NeoPixel neopixelRingLarge = Adafruit_NeoPixel(24, 6, WS2812);
RandomPixels ringLarge = RandomPixels();

Adafruit_NeoPixel neopixelRingMedium = Adafruit_NeoPixel(16, 7, WS2812);
RandomPixels ringMedium = RandomPixels();

Adafruit_NeoPixel neopixelRingSmall = Adafruit_NeoPixel(12, 8, WS2812);
RandomPixels ringSmall = RandomPixels();

// This is the pixel on the top...it will be controlled differently: TODO
Adafruit_NeoPixel neopixelSingle = Adafruit_NeoPixel(1, 9, WS2812);


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

}


void loop() {

    // Snow...make this into function that is callable from API: TODO
    ringSmall.Animate(neopixelRingLarge, neopixelRingLarge.Color(127, 127, 127), 100);
    ringMedium.Animate(neopixelRingLarge, neopixelRingLarge.Color(127, 127, 127), 100);
    ringLarge.Animate(neopixelRingLarge, neopixelRingLarge.Color(127, 127, 127), 100);

}
