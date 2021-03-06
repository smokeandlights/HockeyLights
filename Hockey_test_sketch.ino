#include <FastLED.h>

const int floorGlowRed = 3;   //These 3 are an RGB strip mounted under the table
const int floorGlowGreen = 5; //Use PWM pins, or add softPWM and use whatever pins I want.
const int floorGlowBlue = 6;
const int floorGlowWhite = 9; //And a white strip, so I don't have to RGB white.

const int downLights = 5;  //White & UV LED strips adhered to underside of the scoreboard.
//Let's make this a physical switch selection for now.
//Ground from both color downlights should feed through a
//slider switch to select. Switch to UV for "Cosmic" mode,
//with a 3D printed flourescent puck

#define DATA_PIN    2
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    10
CRGB neoLoop[NUM_LEDS];
#define BRIGHTNESS  96
#define FRAMES_PER_SECOND  120

const int button = 4;         //game start/reset button
const int redScoreSwitch = 7; //switch inside the blue goalie's goal
const int blueScoreSwitch = 8;//switch inside the red goalie's goal

unsigned long gameTimer = 0;  //keep track of the game time, so I can add an attract mode later.
int blueScore = 0;  //Keeping score, because I can.
int redScore = 0;

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(redScoreSwitch, INPUT_PULLUP);
  pinMode(blueScoreSwitch, INPUT_PULLUP);
  Serial.begin(9600);

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(neoLoop, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(neoLoop, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
for (int t = 0; t < NUM_LEDS; t += 3) { //I want the neopixels ring to show red, white and blue,.
    neoLoop[t] = CRGB::Red;               //static around the strip. It might be fun to make this pattern chase later.
    FastLED.show();
  }
  for (int t = 1; t < NUM_LEDS; t += 3) {
    neoLoop[t] = CRGB::White;
    FastLED.show();
  }
  for (int t = 2; t < NUM_LEDS; t += 3) {
    neoLoop[t] = CRGB::Blue;
    FastLED.show();
  }
  delay(5000);                            //wait for the anthem snippet, then go into "game mode"
  fadeToBlackBy(neoLoop, NUM_LEDS, 40);
  analogWrite(floorGlowWhite, BRIGHTNESS);
  // digitalWrite(downLights, HIGH);
  for (int b = 0; b < 255; b++) { //fade up the downlights, because it looks cooler
    analogWrite(downLights, b);
    delay(10);
  }
}
