/*
   Routeins for data parsing and switch cases


*/

#include <WiFi.h>

//------------------------------------------------GPIO Control and string parsing----------------------------
// turns the GPIOs on and off:

void GPIOcontrol() {

  if (header.indexOf("GET /25/off") >= 0) {
    Serial.println("GPIO 25 off");
    // sadLampState = "off";

    modeChange = true;
  } else if (header.indexOf("GET /25/on") >= 0) {
    Serial.println("GPIO 25 on");
    //  sadLampState= "on";

    //   modeChange = true;
  }
}
//------------------------------------------^^^-----GPIO Control-------------------------

bool genericBoolcontrol(String headerValue) {

  if (header.indexOf("GET /" + headerValue + "/off") >= 0) {
    Serial.print(headerValue);
    Serial.println(": Bool False");
    return false;
    // sadLampState = "off";

    // modeChange = true;
  } else if (header.indexOf("GET /" + headerValue + "/on") >= 0) {
    Serial.print(headerValue);
    Serial.println(": Bool True");
    return true;
    //  sadLampState= "on";

    //   modeChange = true;
  } else {
    return false;   // Not ideal if used as a toggle but should work for our purposes now
  }
}

bool toggleBoolcontrol(String headerValue) {

  if (header.indexOf("GET /" + headerValue + "/off") >= 0) {
    Serial.print(headerValue);
    Serial.println(": Bool False");

    toggleCountdown = "off";
    simpleClock.countdownStop();
    modeChange = true;
    return false;
  } else if (header.indexOf("GET /" + headerValue + "/on") >= 0) {
    Serial.print(headerValue);
    Serial.println(": Bool True");

    toggleCountdown = "on";
    simpleClock.countdownStart();
    modeChange = true;
    return true;
  } else {
    return false;   // Not ideal if used as a toggle but should work for our purposes now
  }
}





// Uses values returned from genericBOOL header to control the state of the clock
void startPausecountdown() {
  if (!simpleClock.runCountdown) {      // countdown state is off
    countdownRun = "off";                      // These variables control the style applied to buttons
    countdownPause = "on";
    if (triggerCountdown) {                 // if trigger flag has been set
      simpleClock.countdownStart();           // start the countdown
    }
  } else {                                    // If countdown is running
    countdownRun = "on";
    countdownPause = "off";
    if (triggerCountdownPause) {                 // if trigger pause flag has been set
      simpleClock.countdownStop();           // pause the countdown
    }
  }
}




//------------------------------------------------String Parsing Numerical updates----------------------------


//---------------------  Numerical Data Extraction ----

int32_t numericalDataParse(String headerText, int32_t origionalValue) {


  if (header.indexOf("GET /?" + headerText + "=") >= 0) {                  // If the header contains the passed header text






    int stringLength =  header.length() + 1;                      // work out the length of char array needed to hold the String
    // object header.

    char copy[stringLength];                                    /// this is long....like 535 characters long wtf man.
    // it works but damn there has to be a better way
    header.toCharArray(copy, stringLength);                     // copy the String - header. to char copy
    // This data is now indexed and can be sorted.

    int pointer = header.indexOf("=");                            // find the location of the = sign


    char u[4];   // Char array to hold the integer value
    int y = 0;      // Iterator value for char u


    for (int i = pointer + 1; i < (pointer + 4); i++) {      // copy the string from the pointer to pointer+3
      u[y] = copy[i];
      Serial.println(u[y]);                                  // print the result as it iterates
      y++;
    }

    Serial.println("Extracted Char Array:");               // Printing for testing
    Serial.println(u);


    int32_t extractedData = atoi( u );                                 // put char array into extracted data value as int.



    Serial.print("Extracted Numerical Value: ");
    Serial.println(extractedData);



    for (int i = 0; i < sizeof(copy); i++) {               // Resets copy buffer maybe unneeded

      copy[i] = (char)0;
    }

    // return extractedData;
    return extractedData;
  } else {
    return origionalValue;
  }

}


// Uses Numerical data parse to update the master clock

void updateClock() {


  simpleClock.countdown_master.h = numericalDataParse("hours", simpleClock.countdown_master.h);

  simpleClock.countdown_master.m = numericalDataParse("mins", simpleClock.countdown_master.m);

  simpleClock.countdown_master.s = numericalDataParse("secs", simpleClock.countdown_master.s);


  // update brightnesses  // REQUIRES "Reset Clock" To apply

  countdownClock.countdownBrightness = numericalDataParse("cntdwn_bright", countdownClock.countdownBrightness);   // Clock must be Reset in GUI

  countdownClock.countupBrightness = numericalDataParse("cntup_bright", countdownClock.countupBrightness);      // for changes to be applied
}


void resetClock(String triggerValue) {
  if (header.indexOf("GET /" + triggerValue + "/on") >= 0) {
    simpleClock.countdownStop();           // pause the countdown
    toggleCountdown = "off";
    countdownClock.changeColourStruc( COUNTDOWN_COLOUR );
    countdownClock.changeBrightness(countdownClock.countdownBrightness);
    FastLED.show();
    light_minus(true);
    light_dots(true);
    light_t(true);
    simpleClock.countdownSetup(INITAL_HOURS, INITAL_MINS, INITAL_SECS);

  }
}


void resetEverything(String triggerValue) {
  if (header.indexOf("GET /" + triggerValue + "/on") >= 0) {
    disconnectWIFI();  // Probably better practice
    ESP.restart();;
  }
}
