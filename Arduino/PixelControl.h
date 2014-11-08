#include "neopixel/neopixel.h"


class PixelControl {

    unsigned long previousMillisAnimateRandom;
    unsigned long previousMillisColorWipe;

    public:
    PixelControl();

    void AnimateRandom(Adafruit_NeoPixel &pixelStrip, uint32_t color, long interval);
    void ColorWipe(Adafruit_NeoPixel &pixelStrip, uint32_t color, long interval);

};
