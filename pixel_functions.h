




// Not really required as libaray has function
void light_dots(bool turn_On) {

  if (turn_On) {
    countdownClock.setStringName(17 + (LED_PER_SEG * 42), ((LED_PER_SEG * 42) + 21 ), CURRENT_COLOUR); // lights the dots with passed colour name
  } else {
    countdownClock.setStringName(17 + (LED_PER_SEG * 42), ((LED_PER_SEG * 42) + 21 ), BLACK); // lights the dots with passed colour name //
  }
}


void light_t(bool turn_On) {
  if (turn_On) {
    countdownClock.setStringName((LED_PER_SEG * 42) + 8, ((LED_PER_SEG * 42) + 16 ), CURRENT_COLOUR);   //lights the T & +-  Sets string of LEDs, (from, too, red, green, blue);
  } else {
    countdownClock.setStringName((LED_PER_SEG * 42) + 8, ((LED_PER_SEG * 42) + 16 ), BLACK);
  }
}

void light_plus(bool turn_On) {
  if (turn_On) {
    countdownClock.setStringName((LED_PER_SEG * 42), ((LED_PER_SEG * 42) + 8 ), CURRENT_COLOUR);   //lights the T & +-  Sets string of LEDs, (from, too, red, green, blue);
  } else {
    countdownClock.setStringName((LED_PER_SEG * 42), ((LED_PER_SEG * 42) + 8 ), BLACK);
  }
}



void light_minus(bool turn_On) {
  if (turn_On) {
    light_plus(false);
    countdownClock.setStringName((LED_PER_SEG * 42) + 4, ((LED_PER_SEG * 42) + 8 ), CURRENT_COLOUR);  //lights the T & +-  Sets string of LEDs, (from, too, red, green, blue);
  } else {
    countdownClock.setStringName((LED_PER_SEG * 42) + 4, ((LED_PER_SEG * 42) + 8 ), BLACK);
  }
}


void light_plusminus() {  // Could be pass bool as argument to light the + sign, or just use global variables

  if (simpleClock.tminus) {
    // Light up Just the - Symbol
    light_minus(true);
  } else {
    // Light up the Plus & the Minus symbol
    light_plus(true);
  }

}

void every_led_on() {
  countdownClock.setStringName(0, TOTAL_LEDS, CURRENT_COLOUR);  // lights the dots with passed colour name
}


// function to take a number and return the most significant figure

int32_t return_most_sf(int32_t input) {
  if (input < 10) {
    return 0;
  } else {
    input = input / 10;
    return input;
  }
}



// function to take a number and return the least significant figure


int32_t return_least_sf(int32_t input) {

  char calc[3];
  if (input < 10) {
    return input;
  } else {
    return (input % 10);
  }
}







void displaySetup(int8_t setupBrightness) {
  Serial.println("Clock Initializing...");

  countdownClock.sevenSegSetup(setupBrightness);

  Serial.println("Seven Seg Setup");


  CURRENT_COLOUR = countdownClock.pureWhite;


  // Preset the starting LED colour, can be changed later in program
  delay(100);
  countdownClock.setDigitsBlank();   // Set all digits to blank
  delay (200);
  FastLED.show();
  Serial.println("||    ~~Set Digits Blank~~    ||");


  delay(500);

  for (int j = 0; j < 6 ; j++) {
    countdownClock.setDigit(countdownClock.alldigits[8], j, CURRENT_COLOUR.r, CURRENT_COLOUR.g, CURRENT_COLOUR.b);  // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
    Serial.printf("Set Digit %i 8" , j);
    Serial.println("");
    FastLED.show();
    delay(100);
  }

  // added here 04.12.2020
  light_dots(true);
  FastLED.show();
  delay(100);
  light_minus(true);
  FastLED.show();
  delay(100);
  light_plus(true);
  FastLED.show();
  delay(100);
  light_t(true);
  FastLED.show();



  delay(1000);
  countdownClock.setDigitsBlank();   // Set all digits to blank
  light_dots(false);
  light_t(false);
  light_plus(false);
  delay(100);
  FastLED.show();
  Serial.println("Setting Digits Blank");
  delay(200);

  //countdownClock.setAllDigitsX(countdownClock.H, 255, 255, 255);

  if (INTRO_ANIMATION) {
    introAnimation();
  }

  delay(100);
  FastLED.show();
  Serial.println("Setup Complete, Clock Starting:");

  delay(500);
  countdownClock.setDigitsBlank();   // Set all digits to blank
  delay(100);
  FastLED.show();

}
