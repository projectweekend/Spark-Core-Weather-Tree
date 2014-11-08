#include "neopixel/neopixel.h"


class PixelControl {

    unsigned long previousMillis;

    public:
    PixelControl();

    void AnimateRandom(Adafruit_NeoPixel &pixelStrip, uint32_t color, long interval);

};
