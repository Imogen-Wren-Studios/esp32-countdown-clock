/*********
  ESP32 Web Server Clock Controller

  Use a web server
  accessed over
  local network to
  control a clock


  Imogen Heard
  06/11/2020
*********/

// Load Wi-Fi library
#include <WiFi.h>


// Load other Librarys
//#include <buttonObject.h>

#include <timeObject.h>

timeObject simpleClock;

#define FORCE_PRINT_CLOCK false


// Variables for NeoPixels (Must go above // "#include <pixelSevenSegment.h>"



#include "pixelSevenSegment.h"

pixelSevenSegment countdownClock;

#define CURRENT_COLOUR countdownClock.currentColour    // Macro to make code more readable



// .......User Options......
// Colours
#define COUNTDOWN_COLOUR countdownClock.skyroraBlue
//#define COUNTDOWN_COLOUR countdownClock.pureBlue
#define COUNTUP_COLOUR countdownClock.pureWhite
#define BLACK countdownClock.blackout
//Brightness
#define COUNTDOWN_BRIGHTNESS 200
#define COUNTUP_BRIGHTNESS 100

//#define MAX_BRIGHTNESS 20
#define BRIGHTNESS 255                 // Used for initial brightness during setup

//Clock Defaults
#define INITAL_HOURS 0        // This is also the default value the clock "resets to"
#define INITAL_MINS 1
#define INITAL_SECS 30

#define INTRO_ANIMATION true

// GUI
String PAGE_HEADER = {"Skyrora Countdown Clock"};    // Text displayed as GUI header

#include "animations.h"        // Contains all the animations called by pixel_functions.h
#include "pixel_functions.h"

//#include <autoDelay.h>
#include "globals.h"

// Outputs

#include "wifi_Utilities.h"
#include "dataParsing.h"
#include "CSS.h"
#include "htmlObjects.h"
#include "javascript.h"

#include "html_webpage.h"





//autoDelay timePrintDelay;

//autoDelay testPrintDelay;










//uint8_t maxBrightness = 20;                      // Define the max brightness of all LEDs. 0 - 255. 20-50 reccomended for testing: MUST use seperate 5v supply for full brightness operation! Do not use USB power!




//--------------------------------------------Setup---------------------------------------
void setup() {

  Serial.begin(115200);
  delay(100);

  setup_accessPoint();   //only set up to default IP at the moment 192.168.4.1
  //  connectWifi_staticIP();  // connects to wifi with static IP address

  delay(500);
  // Set up neopixles and set start colour
  displaySetup(BRIGHTNESS);
  countdownClock.changeColourStruc( COUNTDOWN_COLOUR );

  delay (1000);
  light_dots(true);
  light_t(true);
  light_minus(true);

  delay(100);



  simpleClock.countdownSetup(INITAL_HOURS, INITAL_MINS, INITAL_SECS);

  // simpleClock.countdownStart();   // for testing, else we want countdown paused untill triggered

countdownClock.countdownBrightness = COUNTDOWN_BRIGHTNESS;
countdownClock.countupBrightness = COUNTUP_BRIGHTNESS;

  countdownClock.changeBrightness(countdownClock.countdownBrightness);    // Just in case countdown brightness is different to setup brightness

}




//--------------------------------------------Main Loop---------------------------------------

void loop() {

  // Controls all the HTTP requests & parsing
  serverLoop();

  // Call in every loop, updates the master clock
  simpleClock.countdownLoop();

  if (simpleClock.tzero) {
    countdownClock.changeColourStruc(COUNTUP_COLOUR);
    countdownClock.changeBrightness(countdownClock.countupBrightness);
    light_dots(true);
    light_t(true);
    light_plus(true);
    simpleClock.tzero = false;
  }



  //Serial Prints the clock every time seconds change.
  //Can be forced to print always by passing true as an argument
  simpleClock.countdownPrint(FORCE_PRINT_CLOCK);

  // need function here to split master clock into MSF and LSFs
  // Set up displayed digits with correct bit arrays for the current time
  //simpleClock.countdown_master.h;
  //simpleClock.countdown_master.m;
  ///simpleClock.countdown_master.s;
  countdownClock.displayedDigits[0] = countdownClock.alldigits[return_least_sf(simpleClock.countdown_master.s)];
  countdownClock.displayedDigits[1] = countdownClock.alldigits[return_most_sf(simpleClock.countdown_master.s)];

  countdownClock.displayedDigits[2] = countdownClock.alldigits[return_least_sf(simpleClock.countdown_master.m)];
  countdownClock.displayedDigits[3] = countdownClock.alldigits[return_most_sf(simpleClock.countdown_master.m)];

  countdownClock.displayedDigits[4] = countdownClock.alldigits[return_least_sf(simpleClock.countdown_master.h)];
  countdownClock.displayedDigits[5] = countdownClock.alldigits[return_most_sf(simpleClock.countdown_master.h)];


  //Set The digit with the data passed from presaved bit arrays

  for (int q = 0; q < 6; q++) {
    countdownClock.setDigit(countdownClock.displayedDigits[q], q, CURRENT_COLOUR.r, CURRENT_COLOUR.g, CURRENT_COLOUR.b);  // Passed Arguments (digitSeg.bitarray, digitNumber, red, green, blue)
  }


  // if the time has been updated, print the new data to the clock display
  if (simpleClock.time_updated) {
    FastLED.show();
    simpleClock.time_updated = false;
  }




}




// countdown clock master variables:

//simpleClock.countdown_master;
//simpleClock.countdown_master.h;
//simpleClock.countdown_master.m;
///simpleClock.countdown_master.s;

// char countdownclock_as_char[12];   //

//    String countdown_clock_string;

//    bool tminus = true;        // API can be polled to detect if clock is in t- or t+ mode

//   bool runCountdown = false;   //

// bool time_updated;           // toggles true if seconds have changed, must be reset manually
