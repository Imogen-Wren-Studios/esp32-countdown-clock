/* ~~~~** Neopixel **~~~~** Seven Segment Display Library **~~~~~
   pixleSevenSegment.h

   Library to manage neopixel strips arranged into 7 segment display digits.
   The segments

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




#ifndef pixelSevenSegment_h
#define pixelSevenSegment_h

#if (ARDUINO >=100)
#include <Arduino.h>
#else
#include <wProgram.h>
#endif


#include <FastLED.h>
//#include "globals.h"


FASTLED_USING_NAMESPACE      // This line defines which template is used from the library for constructor or setup


#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif



#define DATA_PIN    22                  // Data pin connection to LED string
//#define CLK_PIN   4                      // Not required for 3 pin LED strings
#define LED_TYPE    WS2812B                // This must be set to match the specific LED driver used

//#define LED_TYPE WS2811_400               //

#define COLOR_ORDER GRB

//#define NUM_LEDS 273  // is this depreciated?                             //Number of LEDS in 6 digits (will add more for the sign and dots later  need at least 7 for +- and 4 for dots

#define NUM_DIGITS 6
#define LED_PER_SEG 6
#define ADDITIONAL_LEDS 21

#define TOTAL_LEDS 273      //((number_digits * leds_per_segment * 7)+extra_leds);

#define LEDS_IN_TPLUS 16

#define MAX_BRIGHTNESS 20


//#define CURRENT_COLOUR countdownClock.currentColour    // Macro to make main code more readable.




class pixelSevenSegment {

  public:

    int total_leds;

    CRGBArray<TOTAL_LEDS> ledString;

    //Constructor

    pixelSevenSegment(int number_digits = 6, int leds_per_segment = 6, int extra_leds = 21):

      total_leds((number_digits * leds_per_segment) + extra_leds),
      ledString()
      // tell FastLED about the LED strip configuration

    {
    }



    //::::::::::::::::::::::::::::::::::::::::::::::::::::::: Neopixel to Seven Segment Variables :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // The following data structures are intended to make the neopixles function effectivly like a traditional 7 segment display.


    struct digitSeg {                                // Data Structure to contain the data for "characters" divided up into 7 segments. Each segment can be on or off.
      uint8_t A;                                       // Segments mirror the wiring of traditional 7 segment display
      uint8_t B;
      uint8_t C;
      uint8_t D;
      uint8_t E;
      uint8_t F;
      uint8_t G;
    };



    void sevenSegSetup(byte brightness = 20);

    void setDigit (digitSeg current, int8_t digitNumber, uint8_t red, uint8_t green, uint8_t blue );



    void setDotsRGB(uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255);   // Ignore does not work atm


    void setStringRGB(uint16_t start, uint16_t to, uint8_t red, uint8_t green, uint8_t blue);   // Sets any string of LEDs to the passed colour values



    void setDigitsBlank();

    void setAllDigitsX(digitSeg X, byte r = 255, byte g = 255, byte b = 255);

    void changeBrightness(byte bright = 255);



    // These values are passed bit arrays to print specific digits to each character in the display

    digitSeg seconds0;                                          // Holds the current displayed least significant seconds figure
    digitSeg seconds1;                                           // holds the current displayed most significant seconds figure

    digitSeg minutes2;                                          // Holds the current displayed least significant minuitesfigure
    digitSeg minutes3;                                           // holds the current displayed most significant minuites figure

    digitSeg hours4;                                          // Holds the current displayed least significant hours figure
    digitSeg hours5;                                           // holds the current displayed most significant hours figure

    digitSeg plusminus;                                       // Holds the positive or negative (might be a better way of doing this as it only requires 2 bytes of data, not 7
    digitSeg dots;                                             // holds the values for the dots (also could be done differently, as it only needs one bit for control, but 4 LED id's


    digitSeg displayedDigits[6] = {seconds0, seconds1, minutes2, minutes3, hours4, hours5};   // holds the data values above in an array making referencing in functions and loops easier.





    // these constant data structures hold the arrays for each unique character. Bits mirror the segments of a typical 7 segment display. Other letters and Characters can be added by adding arrays

    const digitSeg zero    = {1, 1, 1, 1, 1, 1, 0};
    const digitSeg one     = {0, 1, 1, 0, 0, 0, 0};
    const digitSeg two     = {1, 1, 0, 1, 1, 0, 1};
    const digitSeg three   = {1, 1, 1, 1, 0, 0, 1};
    const digitSeg four    = {0, 1, 1, 0, 0, 1, 1};
    const digitSeg five    = {1, 0, 1, 1, 0, 1, 1};
    const digitSeg six     = {1, 0, 1, 1, 1, 1, 1};
    const digitSeg seven   = {1, 1, 1, 0, 0, 0, 0};
    const digitSeg eight   = {1, 1, 1, 1, 1, 1, 1};
    const digitSeg nine    = {1, 1, 1, 0, 0, 1, 1};


    digitSeg alldigits[10] = {zero, one, two, three, four, five, six, seven, eight, nine};   // array to hold data structures above. Array number matches the character being recalled.

    const digitSeg blank = {0, 0, 0, 0, 0, 0, 0};

    // This can be accessed as:

    //alldigits[0];   // contains the display data for the character 0
    //alldigits[1];   // Contains the display data for the character 1
    // et al

    //Other Letters and characters that could be easily printed (needs arrays to be filled in);

    digitSeg A   = {1, 1, 1, 0, 1, 1, 1};
    digitSeg E   = {1, 0, 0, 1, 1, 1, 1};
    digitSeg i   = {0, 0, 1, 0, 0, 0, 0};
    digitSeg O   = {1, 1, 1, 1, 1, 1, 0};
    digitSeg o   = {0, 0, 1, 1, 1, 0, 1};
    digitSeg U   = {0, 1, 1, 1, 1, 1, 0};
    digitSeg u   = {0, 0, 1, 1, 1, 0, 0};

    digitSeg B   = {1, 1, 1, 1, 1, 1, 1};
    digitSeg C   = {1, 0, 0, 1, 1, 1, 0};
    digitSeg F   = {1, 0, 0, 0, 1, 1, 1};
    digitSeg H   = {0, 1, 1, 0, 1, 1, 1};
    digitSeg J   = {1, 1, 1, 1, 0, 0, 0};
    digitSeg L   = {0, 0, 0, 1, 1, 1, 0};

    digitSeg P   = {1, 1, 0, 0, 1, 1, 1};
    digitSeg S   = {1, 0, 1, 1, 0, 1, 1};



    digitSeg b   = {0, 0, 1, 1, 1, 1, 1};
    digitSeg c   = {0, 0, 0, 1, 1, 0, 1};
    digitSeg d   = {0, 1, 1, 1, 1, 0, 1};
    digitSeg g   = {1, 1, 1, 1, 0, 1, 1};
    digitSeg h   = {0, 0, 1, 0, 1, 1, 1};
    digitSeg l   = {0, 0, 0, 0, 1, 1, 0};
    digitSeg n   = {0, 0, 1, 0, 1, 0, 1};
    digitSeg p   = {1, 1, 0, 0, 1, 1, 1};
    digitSeg qu  = {1, 1, 1, 0, 0, 1, 1};
    digitSeg r   = {0, 0, 0, 0, 1, 0, 1};
    digitSeg t   = {0, 0, 0, 1, 1, 1, 1};
    digitSeg y   = {0, 1, 1, 1, 0, 1, 1};
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::





    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Colour Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Custom Colour Creator:
    // use savedColour Constructor to craete custom colours that can be passed to the display


    struct savedColour {             // data structure to save named RGB values that could be passed to functions
      uint8_t r;
      uint8_t g;
      uint8_t b;
    };


    // Pick and Name Colours here, then add them to the colourArray to make them easily accessable


    savedColour  skyroraBlue = { 0, 80, 255};    // Data structure for "skyroraBlue" colour as an RGB value

    savedColour     pureBlue = {0, 0, 255};

    savedColour  offWhite = { 160, 255, 200};      // data structure for an offwhite colour, all LEDs on max (these figures chave been calibrated to produce a cleaner white)

    savedColour  yellowOrange = {255, 160, 0};     // Holds Orange Colour as a nice contrast to the blue

    savedColour  blackout = {0 , 0 , 0};          // data structure holding "black" - all LEDS off.

    savedColour  pureWhite = {255, 255, 255};

    savedColour  currentColour;                  // data structure to hold the current LED colour


    savedColour colourArray[4] = {skyroraBlue, offWhite, yellowOrange, pureWhite};     // array to hold different colour data structures. Makes it easy to cycle through them

    uint8_t colourSelect = 0;  // Variable to hold the current selected colour from colourArray

    void changeColourRGB(byte red, byte green, byte blue);
    void changeColourStruc(savedColour newColour);

    void  setDigit_colourName(digitSeg input, int8_t digitNum, savedColour inputColour);
    void setDotsName(savedColour newColour);
    void setStringName(uint16_t start, uint16_t to, savedColour newColour);

    void flyingDigit(digitSeg in, savedColour inputColour, uint32_t animationDelay = 100);

    uint8_t currentBrightness;

    uint8_t countdownBrightness;    // 
    uint8_t countupBrightness;      // 

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




  private:


    uint8_t iteration = 0;   // used for iterating animation effects through mulitple loops







};




#endif
