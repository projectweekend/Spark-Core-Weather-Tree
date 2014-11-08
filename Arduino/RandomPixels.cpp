#include "RandomPixels.h"


RandomPixels::RandomPixels() {
    previousMillis = 0;
}


void RandomPixels::Animate(Adafruit_NeoPixel &pixelStrip, uint32_t color, long interval) {
    int randomPixel = random(0, pixelStrip.numPixels());

    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;
        pixelStrip.setPixelColor(randomPixel, color);
        pixelStrip.show();
    }
    pixelStrip.setPixelColor(randomPixel, 0);
}
