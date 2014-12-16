#include "neopixel/neopixel.h"
#include "PixelControl.h"


Adafruit_NeoPixel neopixelRingLarge = Adafruit_NeoPixel(24, 6, WS2812);
PixelControl ringLarge = PixelControl();

Adafruit_NeoPixel neopixelRingMedium = Adafruit_NeoPixel(16, 5, WS2812);
PixelControl ringMedium = PixelControl();

Adafruit_NeoPixel neopixelRingSmall = Adafruit_NeoPixel(12, 4, WS2812);
PixelControl ringSmall = PixelControl();

// This is the pixel on the top...it will be controlled differently: TODO
Adafruit_NeoPixel neopixelSingle = Adafruit_NeoPixel(1, 7, WS2812);

int currentPercipitation = 0;


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

    // Default color
    // ringSmall.ColorWipe(neopixelRingSmall, neopixelRingLarge.Color(0, 255, 0), 100);
    // ringMedium.ColorWipe(neopixelRingMedium, neopixelRingMedium.Color(0, 255, 0), 100);
    // ringLarge.ColorWipe(neopixelRingLarge, neopixelRingSmall.Color(0, 255, 0), 100);

    int result = noPercipitation();

    randomSeed(analogRead(0));

    Spark.function("rain", rain);
    Spark.function("snow", snow);
    Spark.function("none", noPercipitation);
}


void loop()
{
    switch (currentPercipitation) {
        case 1:
            // Rain
            ringSmall.AnimateRandom(neopixelRingSmall, neopixelRingLarge.Color(0, 0, 255), 100);
            ringMedium.AnimateRandom(neopixelRingMedium, neopixelRingMedium.Color(0, 0, 255), 100);
            ringLarge.AnimateRandom(neopixelRingLarge, neopixelRingSmall.Color(0, 0, 255), 100);
            break;
        case 2:
            // Snow
            ringSmall.AnimateRandom(neopixelRingSmall, neopixelRingLarge.Color(127, 127, 127), 100);
            ringMedium.AnimateRandom(neopixelRingMedium, neopixelRingMedium.Color(127, 127, 127), 100);
            ringLarge.AnimateRandom(neopixelRingLarge, neopixelRingSmall.Color(127, 127, 127), 100);
            break;
    }
}


int noPercipitation(String args)
{
    clear();
    ringSmall.ColorWipe(neopixelRingSmall, neopixelRingLarge.Color(0, 255, 0), 100);
    ringMedium.ColorWipe(neopixelRingMedium, neopixelRingMedium.Color(0, 255, 0), 100);
    ringLarge.ColorWipe(neopixelRingLarge, neopixelRingSmall.Color(0, 255, 0), 100);
    currentPercipitation = 0;
    return 200;
}


int rain(String args)
{
    clear();
    currentPercipitation = 1;
    return 200;
}


int snow(String args)
{
    clear();
    currentPercipitation = 2;
    return 200;
}


void clear()
{
    ringSmall.ColorWipe(neopixelRingSmall, 0, 0);
    ringMedium.ColorWipe(neopixelRingMedium, 0, 0);
    ringLarge.ColorWipe(neopixelRingLarge, 0, 0);
}
