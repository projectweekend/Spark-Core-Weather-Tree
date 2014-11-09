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


void setup()
{
    neopixelRingLarge.begin();
    neopixelRingLarge.show();

    neopixelRingMedium.begin();
    neopixelRingMedium.show();

    neopixelRingSmall.begin();
    neopixelRingSmall.show();

    neopixelSingle.begin();
    neopixelSingle.show();

    randomSeed(analogRead(0));

    Spark.function("snow", snow);
    Spark.function("none", noPercipitation);
}


void loop() {

}


int snow(String args)
{
    ringSmall.AnimateRandom(neopixelRingSmall, neopixelRingLarge.Color(127, 127, 127), 100);
    ringMedium.AnimateRandom(neopixelRingMedium, neopixelRingMedium.Color(127, 127, 127), 100);
    ringLarge.AnimateRandom(neopixelRingLarge, neopixelRingSmall.Color(127, 127, 127), 100);

    return 200;
}


int noPercipitation(String args)
{
    ringSmall.ColorWipe(neopixelRingSmall, neopixelRingLarge.Color(0, 255, 0), 100);
    ringMedium.ColorWipe(neopixelRingMedium, neopixelRingMedium.Color(0, 255, 0), 100);
    ringLarge.ColorWipe(neopixelRingLarge, neopixelRingSmall.Color(0, 255, 0), 100);

    return 200;
}
