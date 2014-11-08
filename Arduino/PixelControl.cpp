#include "PixelControl.h"


PixelControl::PixelControl() {
    previousMillisAnimateRandom = 0;
    previousMillisColorWipe = 0;
}

void PixelControl::AnimateRandom(Adafruit_NeoPixel &pixelStrip, uint32_t color, long interval) {
    int randomPixel = random(0, pixelStrip.numPixels());

    unsigned long currentMillis = millis();

    if(currentMillis - previousMillisAnimateRandom > interval) {
        previousMillisAnimateRandom = currentMillis;
        pixelStrip.setPixelColor(randomPixel, color);
        pixelStrip.show();
    }
    pixelStrip.setPixelColor(randomPixel, 0);
}


void PixelControl::ColorWipe(Adafruit_NeoPixel &pixelStrip, uint32_t color, long interval)
{
    for(uint16_t i = 0; i < pixelStrip.numPixels(); i++)
    {
        pixelStrip.setPixelColor(i, color);
        pixelStrip.show();
        delay(interval);
    }
}
