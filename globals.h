
// New Variables

bool triggerCountdown;

bool triggerCountdownPause;

String toggleCountdown = "off";

String countdownRun = "off";
String countdownPause = "on";

String H = "00";
String M = "01";
String S = "60";


// Old Variables

int lampBrightness;   // variable to hold the output value for PWM

uint32_t fadeInterval;

uint32_t onTime;

bool modeChange;








// Variable to store the HTTP request
String header;   //this line working




// Auxiliar variables to store the current output state
String sadLampState = "off";           // SAD lamp Relay Output

//String output26State = "off";            // Green LED
//String output27State = "off";            // Blue LED

// Assign output variables to GPIO pins
const int relayOnPin = 12;
const int relayOffPin = 14;

//PWM Properties
const int freq = 5000;                     // PWM frequency
const int resolution = 8;                  // PWM resolution (bits) 8: 0-255

// using the LED pwm controller assign channels 0-15    16 total avaliable
const int ledREDchannel = 0;
const int ledGREENchannel = 1;
const int ledBLUEchannel = 2;

int redPWM = 254;                               // Red LED Level
int greenPWM = 100;                             // Green LED Level
int bluePWM = 100;                               // Blue LED Level



String R = "255";                                 // Strings to hold PWM values which are printed to the browser when called
String G = "255";
String B = "255";                               // they literally do the thing in the printing to the page.

String BRIGHT = "255";


bool printSerial = true;
