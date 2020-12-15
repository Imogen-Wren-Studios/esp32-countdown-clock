/*  // Contents of HTML Webpage






*/


// Quick outline of the "content" of the displayed HTML webpage


void pageContent(WiFiClient client) {    // Displays All the Content Displayed to Client


  numberInputBox(client, "Hours", "hours", String(simpleClock.countdown_master.h));

  numberInputBox(client, "Minutes", "mins", String(simpleClock.countdown_master.m));

  numberInputBox(client, "Seconds", "secs", String(simpleClock.countdown_master.s));

  //  genericButton(client, "Start Countdown | Current State = ", "Start", countdownRun, "start_countdown");

  //  genericButton(client, "Pause Countdown | Current State = ", "Pause", countdownPause, "pause_countdown");
  // javascript_timeBody(client); Does not work

  toggleButton(client, "Toggle Countdown | Current State = ", "Start", "Pause", toggleCountdown, "toggle_countdown");

  webDisplayClockStatic(client);   // Non javascript Static Text clock (updates on pageload)

  // Javascript Clock Updater:

  //  javascriptClockItem(client);   // Does not function Yet



  toggleButton(client, "Reset Clock ", "Reset", "", "" , "reset_clock");   // Button to Reset Clock



  byteInputBox(client, "Countdown Brightness", "cntdwn_bright", String(countdownClock.countdownBrightness));

  byteInputBox(client, "Countup Brightness", "cntup_bright", String(countdownClock.countupBrightness));

  genericButton(client, "Set Brightness", "Update", "", "set_bright");

  toggleButton(client, "Reboot ESP || Current State = ", "Reboot", "", "On" , "reset_esp");   // Button to Reboot ESP
}


// Collect all functions that extract data from returning HTTP headers from client

void dataSortingMethods(WiFiClient client) {



  // Boolean Data Parsing

  toggleBoolcontrol("toggle_countdown");     // start/pause button data parsing

  resetClock("reset_clock");   // Method to restart ESP from GUI button


  if ( genericBoolcontrol("set_bright")) {  // Method to update the running clock brightness
    Serial.println("Updating Brightness");
    if (simpleClock.tminus) {
      countdownClock.changeBrightness(countdownClock.countdownBrightness);
    } else {
      countdownClock.changeBrightness(countdownClock.countupBrightness);
    }
    FastLED.show();
  }

  resetEverything("reset_esp");   // Method to restart ESP from GUI button

  // Numerical Data Parsing

  updateClock();      // updates clock with values from numerical input boxes



  // clockData_toJson(client, simpleClock.countdown_master.h, simpleClock.countdown_master.m, simpleClock.countdown_master.s );    // Updater for live clock
}






// HTML Header
void htmlPageHeading(WiFiClient client) {
  // Display the HTML web page
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");

  //javaScript_timeHead(client);  << does not seem to work

  // Head closed by CSS Method
}




// Method calls everything required to run the server module

void serverLoop() {
  //------------------------ Client HTTP Requests-----------------------------

  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected

      simpleClock.countdownLoop();            // Bug fix ( I dont like but should work) This loop gets stuck waiting for data, so just run the clock functions here too.
      simpleClock.countdownPrint(FORCE_PRINT_CLOCK);

      //   Serial.println("While client.connected");
      if (client.available()) {             // if there's bytes to read from the client,
        //   Serial.println("if client.available");
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;                        // add that character to the header String
        //  Serial.print(c); //see what was captured   // ADDED LINE << Lets see wtf goes on here.

        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.

          // that's the end of the client HTTP request, so send a response:



          //--------------------------------------------AP--HTTP Response--------------------
          //--------------------------------------------AP--HTTP Response--------------------
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            //--------------------------------^^^^---- HTTP Requests/Response------------------------------------
            // This function returns a HTTP respone to the client
            //--------------------------------^^^^---- HTTP Requests/Response------------------------------------


            // >>>>>>>>>>>> Data Parsing Functions Here <<<<<<<<<<<<<


            dataSortingMethods(client);


            //~~~~~~~~~~~~~~~~~~~~~~~~~# HTTP WEB PAGE GOES HERE #~~~~~~~~~~~~~~~~~~


            //-------------------HTML Header----------
            htmlPageHeading(client);

            //--------------------CSS---------
            // CSS to style the on/off buttons
            callCSS(client);  //  function calls CSS sheet    // Must be passed wifi client.


            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~## Web Page CONTENT ##~~~~~~~~~~~~~~~~~~~

            //-------- Web Page Heading-----------------------------------------------------------------------
            client.println("<body><h1>" + PAGE_HEADER + "</h1>");



            //-------------------------------------------------------------Display Buttons-------------------------

            pageContent(client);

            //   displayDayTimes(client);     // New Funtion added to display each weekday and the time the clock is set to.


            // end the HTML body
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            //added line below to force close:
            //  client.stop();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }

    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");


  }

}
