/* #### HTML Objects #####
 *  
 * Functions that outline specific HTML objects that can be used and reused for different purposes
 * 
 * 
*/

#include <WiFi.h>




// Print the text box for a number input
void numberInputBox(WiFiClient client, String boxLabel, String boxName, String currentValue ) {

  client.println(boxLabel + ": <span id=\"" + boxName + "\"></span> </br>");
  client.println("<div class= \"centerBox\">");
  client.println("<div class= \"flexBox\">");   // centered box
  client.println("<form action='/' class=\"inputForm\" method=get >"); //uses IP/port of web page
  client.println("<input type=\"number\" name=\"" + boxName + "\" min =\"0\" max =\"60\" value= " + currentValue + "  style=\"width: 3em\"><br>");

  client.println("</br> <input type=\"submit\" value=\"Apply\">");
  client.println("</form> </div> </br> ");
  //client.println("</div>");
}


// Print the text box for a number input
void byteInputBox(WiFiClient client, String boxLabel, String boxName, String currentValue ) {

  client.println(boxLabel + ": <span id=\"" + boxName + "\"></span> </br>");
  client.println("<div class= \"centerBox\">");
  client.println("<div class= \"flexBox\">");   // centered box
  client.println("<form action='/' class=\"inputForm\" method=get >"); //uses IP/port of web page
  client.println("<input type=\"number\" name=\"" + boxName + "\" min =\"0\" max =\"255\" value= " + currentValue + "  style=\"width: 3em\"><br>");

  client.println("</br> <input type=\"submit\" value=\"Apply\">");
  client.println("</form> </div> </br> ");
  //client.println("</div>");
}




// Generic Single button

void genericButton(WiFiClient client, String titleText, String buttonONText, String currentState, String returnString) {

  client.println("<p>" + titleText + currentState + "</p>");

  if (currentState == "on") {
    //    client.println("<p><a href=\"/" + returnString + "/off\"><button class=\"button button2\"></button></a></p>");
  } else {
    client.println("<p><a href=\"/" + returnString + "/on\"><button class=\"button\">" + buttonONText + "</button></a></p>");
  }
}


// Generic Toggle Button
void toggleButton(WiFiClient client, String titleText, String buttonONtext, String buttonOFFtext, String currentState, String returnString) {

  client.println("<p>" + titleText + currentState + "</p>");

  if (currentState == "on") {
    client.println("<p><a href=\"/" + returnString + "/off\"><button class=\"button button2\">" + buttonOFFtext + "</button></a></p>");
  } else {
    client.println("<p><a href=\"/" + returnString + "/on\"><button class=\"button\">" + buttonONtext + "</button></a></p>");
  }
}


// This is in javascript.h for now, just for referencing variables


// Display a static Clock on the webpage
void webDisplayClockStatic(WiFiClient client){

 // client.println("<div class= \"centerBox\">");
 // client.println("<div class= \"flexBox\">"); 

 client.println("<h1>"+simpleClock.countdown_clock_string+"</h1>");
  
//client.println("</div> ");
//client.println("</div> ");

  
}




void httpResponse(WiFiClient client) {
}


































void sliderInputForm(WiFiClient client) {

  /*
              client.println("<p>Red - GPIO 25 - State " + R + "</p>");        //output25State replaced by red PWM might not work coz its an int not a char
              // If the output25State is off, it displays the ON button
              if (output25State == "off") {
                client.println("<p><a href=\"/25/on\"><button class=\"button button2\">OFF</button></a></p>");
              } else {
                client.println("<p><a href=\"/25/off\"><button class=\"button\">ON</button></a></p>");
              }


              // Print the text box for PWM value;   // HIGHLY EXPEREMENTAL
              client.println("Red Level: <span id=\"red\"></span> </br>");

              client.println(" <div class= \"centerBox\">");

              client.println("<form action='/' class=\"inputForm\" method=get >"); //uses IP/port of web page

              client.println(" <div class= \"flexBox\">");   // centered box

              client.println(" <div class= \"marginBox\"> </div>");  //

              client.println(" <div class= \"leftBox\">");   // div box for input slider/form

              //this line for text box input
              // client.println("<input type=\"number\" name=\"redPWM\" min =\"0\" max =\"255\" value= " + R + "  style=\"width: 3em\"><br>");

              //these lines for slider input;
              client.println("<div class=\"slidecontainer\">");
              client.println("<input type=\"range\" name=\"redPWM\" min =\"0\" max =\"255\" value= " + R + " class=\"slider\"");
              client.println("id=\"redRange\"><br>");   // id= "myRange used for javascript (style=\"width: 3em\") remioved
              client.println("</div>");    // close slider box
              client.println("</div>");   // close left box

              client.println(" <div class= \"rightBox\">");   // div box for apply button

              client.println("<input type=\"submit\" value=\"Apply\">");   ///</br>  removed from start of box
              client.println("</div>");   // close right box
                client.println("</div>");   // close flex box

              client.println("</form>");   // close the form
              client.println("</div>");     // close the center box


              // print javascript object;
              client.println("<script> var slider = document.getElementById(\"redRange\");");
              client.println("var output = document.getElementById(\"red\");");
              client.println("output.innerHTML = slider.value;");

              client.println("slider.oninput = function() {output.innerHTML = this.value;}");
              client.println("</script>");
  */
}























//char dayNames[][10] = {"Monday", "Tuseday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

/*
  void displayDayTimes(WiFiClient client) {

  client.println(" <div class= \"centerBox\">");
  client.println(" <div class= \"flexBox\">");   // centered box

  client.println(" <div class= \"leftBox\">");   // div box for input slider/form

  for (int i = 0; i < 7; i++) {

    //   String D = dayNames[i];
    //  String T =  turnOnTimes[i];
    T.remove(0 , 1);   // Remove the 2 characters at the start that are just used to hold the number of the weekday.

    // Put display here with each weekday name and the time the switch is timed on at
    client.println("<p>"  + D +  " Wakeup Time: " + T + "</p>");
  }
  client.println("</div>");    // close Left box
  client.println("</div>");   // close Flex box
  client.println("</div>");     // close the center box
  }
*/
