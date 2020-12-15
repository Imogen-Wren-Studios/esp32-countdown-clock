/* ~~~~** Neopixel **~~~~** Seven Segment Display Library **~~~~~
   pixleSevenSegment.cpp

   Library to manage neopixel strips arranged into 7 segment display digits.
   The segments are wired in series, and follow the layout of typical 7 segment
   displays. Segments: A, B, C, D, E, F, G.

   Setups:
   Number of LEDS in each Segment
   Number of Digits.

   Inputs:
   individual digit ID & Value
   hours, minutes, seconds as char strings or ints
   time as complete string
   current display colour
   specific digit colour


 * *
   Outputs:
   Data to Neopixel string

   Serial print of current displayed time/values



*/


#include "pixelSevenSegment.h"


//pixelSevenSegment::pixelSevenSegment(int number_digits , int leds_per_segment, int extra_leds){//






void pixelSevenSegment::sevenSegSetup(byte brightness) {

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(ledString, TOTAL_LEDS).setCorrection(TypicalLEDStrip);            // This sets up our LED string object


  // set master brightness control
  FastLED.setBrightness(brightness);
  // Sets the brightness for the entire string
  currentBrightness = brightness;



}




void pixelSevenSegment::flyingDigit(digitSeg in, savedColour inputColour, uint32_t animationDelay) {
  int iteration = 0;  // this variable needs to be external
  pixelSevenSegment::setDigit_colourName(in, iteration, inputColour);
  iteration++;
}


void pixelSevenSegment::setAllDigitsX(digitSeg X, byte r, byte g, byte b) {

  pixelSevenSegment::setDigit(X, 0, r, g, b);
  pixelSevenSegment::setDigit(X, 1, r, g, b);
  pixelSevenSegment::setDigit(X, 2, r, g, b);
  pixelSevenSegment::setDigit(X, 3, r, g, b);
  pixelSevenSegment::setDigit(X, 4, r, g, b);
  pixelSevenSegment::setDigit(X, 5, r, g, b);


}


void pixelSevenSegment::setDigitsBlank() {  // Method to set all digits to black (off)

  pixelSevenSegment::setDigit(alldigits[8], 0, 0, 0, 0);  // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
  pixelSevenSegment::setDigit(alldigits[8], 1, 0, 0, 0);  // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
  pixelSevenSegment::setDigit(alldigits[8], 2, 0, 0, 0);  // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
  pixelSevenSegment::setDigit(alldigits[8], 3, 0, 0, 0);  // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
  pixelSevenSegment::setDigit(alldigits[8], 4, 0, 0, 0);  // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
  pixelSevenSegment::setDigit(alldigits[8], 5, 0, 0, 0);  // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)

}


// this function needs to be a method for a "digit" object but I couldn't work out how to do that.
// This method is slightly more inelegent but it should work (UNTESTED with more than 1 digit but confident it will function)




void pixelSevenSegment::setDigit_colourName(digitSeg input, int8_t digitNum, savedColour inputColour) {

  pixelSevenSegment::setDigit(input, digitNum, inputColour.r, inputColour.g, inputColour.b);
}


void pixelSevenSegment::setDigit (digitSeg current, int8_t digitNumber, uint8_t red, uint8_t green, uint8_t blue ) {           // This function sets the first digit based on the data structure passed to it.


  // A new instance of digitSeg has been set up ready to take whatever data is placed into it
  // After this,  a variable to denote which digit we are setting is passed as an argument.
  // Also passed to function - rgb colour value, which sets the colour for the entire digit



  uint16_t  q = ((digitNumber) * (LED_PER_SEG * 7));  // This variable is added onto the array numbers, advancing down the LED array as each successive digit is selected to be written to.

  //Serial.println(q);
  // Above algorithm may need updating once dots are added, as to sync any animated lighting effects, the led addresses for the : : Dots needs to come between the ids for each digit

  int16_t s = 0;    // Addr to advance the array through each segement of each digit



  if (current.A) {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }


  s = (LED_PER_SEG);

  if (current.B) {
    ledString((s + q ), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }

  s = ((LED_PER_SEG) * 2);

  if (current.C) {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }

  s = ((LED_PER_SEG) * 3);

  if (current.D) {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }


  s = ((LED_PER_SEG) * 4);

  if (current.E) {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }

  s = ((LED_PER_SEG) * 5);

  if (current.F) {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }


  s = ((LED_PER_SEG) * 6);

  if (current.G) {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB(red, green, blue);
  } else {
    ledString((s + q), (s + LED_PER_SEG + q - 1)) = CRGB::Black;
  }


}














// After all the arrays for the digits, ID for the dots starts again at ID:

//  (LED_PER_SEG * 7)* 6 to ((LED_PER_SEG * 7)* 6) + 4

void pixelSevenSegment::setDotsRGB(uint8_t red, uint8_t green, uint8_t blue ) {

  int16_t d = (LEDS_IN_TPLUS + (LED_PER_SEG * 7) * 6);

  ledString(d, (d + 4)) = CRGB(red, green, blue);
}

void pixelSevenSegment::setDotsName(savedColour newColour) {

  int16_t d = (LEDS_IN_TPLUS + (LED_PER_SEG * 7) * 6);

  ledString(d, (d + 4)) = CRGB(newColour.r, newColour.g, newColour.b);
}


void pixelSevenSegment::setStringRGB(uint16_t start, uint16_t to, uint8_t red, uint8_t green, uint8_t blue) {
  ledString(start, to) = CRGB(red, green, blue);
}

void pixelSevenSegment::setStringName(uint16_t start, uint16_t to, savedColour newColour) {
  ledString(start, to) = CRGB(newColour.r, newColour.g, newColour.b);
}

void pixelSevenSegment::changeColourRGB(byte red, byte green, byte blue) {

  currentColour.r = red;
  currentColour.g = green;
  currentColour.b = blue;
}

void pixelSevenSegment::changeColourStruc(savedColour newColour) {

  currentColour = newColour;

}

void pixelSevenSegment::changeBrightness(byte bright) {

  currentBrightness = bright;
  FastLED.setBrightness(bright);
}
