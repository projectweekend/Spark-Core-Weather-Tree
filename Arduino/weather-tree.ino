// This #include statement was automatically added by the Spark IDE.
#include "neopixel/neopixel.h"

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, WS2812);


class Snow {

    unsigned long interval;
    unsigned long previousMillis;

    public:
    Snow(unsigned long interval) {
        interval = interval;
        previousMillis = 0;
    }

    void Run() {
        // int randomPixel = random(0, Adafruit_NeoPixel::numPixels());

        unsigned long currentMillis = millis();

        if(currentMillis - previousMillis > interval) {
            previousMillis = currentMillis;
            // Adafruit_NeoPixel::setPixelColor(randomPixel, Adafruit_NeoPixel::Color(127, 127, 127));
            // Adafruit_NeoPixel::show();
        }

        // Adafruit_NeoPixel::setPixelColor(randomPixel, 0);
    }

};


void setup() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    randomSeed(analogRead(0));
}


void loop() {

}
