#include "neopixel/neopixel.h"


class RandomPixels {
    unsigned long previousMillis;

    public:
    RandomPixels();

    void Animate(Adafruit_NeoPixel &pixelStrip, uint32_t color, long interval);
};
