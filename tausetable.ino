#include <FastLED.h>
#define NUM_LEDS 175
#define DATA_PIN1 8
#define DATA_PIN2 9

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];

const int buttonPin[] = {3, 4, 5, 2};  // the number of the pushbutton pins

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int oneCount = 0;
int twoCount = 0;
int threeCount = 0;
int fourCount = 0;
int currentCount = 0;
int currentButton = 0;


const CRGB oneColor[] = {CRGB::Red, CRGB::Blue, CRGB::Green, CRGB::Purple, CRGB::White};
const CRGB twoColorOne[] = {CRGB::Red, CRGB::Blue, CRGB::Purple, CRGB::Blue, CRGB::Red, CRGB::Green};
const CRGB twoColorTwo[] = {CRGB::Blue, CRGB::Red, CRGB::Blue, CRGB::Purple, CRGB::Green, CRGB::Red};
const CRGB threeColorOne[] = {CRGB::Red, CRGB::Blue, CRGB::Purple,  CRGB::Red, CRGB::Purple};
const CRGB threeColorTwo[] = {CRGB::Blue, CRGB::Green, CRGB::Blue, CRGB::Green, CRGB::Red};


void setup() {
  Serial.begin(9600);


  FastLED.addLeds<NEOPIXEL, DATA_PIN1>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds2, NUM_LEDS);

  // initialize the keypad pin(s) as an input:
  for (int x = 0; x < 4; x++)
  {
    pinMode(buttonPin[x], INPUT_PULLUP);
  }

}

void loop() {
  // read the state of the keypad value

  for (int x = 0; x < 4; x++)
  {
    //signifying the state of which the button is in by reading the appropriate pin #
    buttonState = digitalRead(buttonPin[x]);

    // check if the pushbutton on the keypad is pressed.
    // if it is, the buttonState is LOW:
    if (buttonState == LOW && buttonPin[x] == 3) {

      if (currentCount > 15000) {
        singleColor(oneColor[oneCount]);
        oneCount = (oneCount + 1) % 5;
        currentCount = 0;
      }
      else if (currentButton != 1) {
        currentCount = 0;
        currentButton = 1;
      }
      else {
        currentCount += 1;
      }
    }
    if (buttonState == LOW && buttonPin[x] == 4) {

      if (currentCount > 15000) {
        doubleColor(twoColorOne[twoCount], twoColorTwo[twoCount]);
        twoCount = (twoCount + 1) % 6;
        currentCount = 0;
      }
      else if (currentButton != 2) {
        currentCount = 0;
        currentButton = 2;
      }
      else {
        currentCount += 1;
      }
    }
    if (buttonState == LOW && buttonPin[x] == 5) {

      if (currentCount > 15000) {
        stripes(threeColorOne[threeCount], threeColorTwo[threeCount], 3);
        threeCount = (threeCount + 1) % 6;
        currentCount = 0;
      }
      else if (currentButton != 3) {
        currentCount = 0;
        currentButton = 3;
      }
      else {
        currentCount += 1;
      }
    }
    if (buttonState == LOW && buttonPin[x] == 2) {

      rainbow(100, 10);
    }

  }

}

void rainbow(int cycles, int speed) { // TODO direction
  if (cycles == 0) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds1[i] = Wheel(((i * 256 / NUM_LEDS)) & 255);
      leds2[i] = Wheel(((i * 256 / NUM_LEDS)) & 255);

    }
    FastLED.show();
  }
  else {
    for (int j = 0; j < 256 * cycles; j++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds1[i] = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
        leds2[i] = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      }
      FastLED.show();
      delay(speed);
    }
  }
}

void singleColor(CRGB c) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = c;
    leds2[i] = c;
  }
  FastLED.show();
}

void doubleColor(CRGB c, CRGB d) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = c;
    leds2[i] = d;
  }
  FastLED.show();

}
void allRandom() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = randomColor();
    leds2[i] = randomColor();
  }
  FastLED.show();
}

void stripes(CRGB c1, CRGB c2, int width) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % (width * 2) < width) {
      leds1[i] = c1;
      leds2[i] = c1;
    }
    else {
      leds1[i] = c2;
      leds2[i] = c2;
    }
  }
  FastLED.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

CRGB randomColor() {
  return Wheel(random(256));
}
