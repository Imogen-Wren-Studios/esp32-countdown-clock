/*
 * 
 * 
 * 
 * 
 * 
 * 
 *   // Display current state, and ON/OFF buttons for GPIO 25


  client.println("<p>SAD Lamp - State " + sadLampState + "</p>");        //output25State replaced by red PWM might not work coz its an int not a char
  // If the output25State is off, it displays the ON button
  if (sadLampState == "off") {
    client.println("<p><a href=\"/25/on\"><button class=\"button button2\">OFF</button></a></p>");
  } else {
    client.println("<p><a href=\"/25/off\"><button class=\"button\">ON</button></a></p>");
  }


  // Print the text box for PWM value;   // HIGHLY EXPEREMENTAL
  client.println("Lamp Level: <span id=\"lamp\"></span> </br>");

  client.println(" <div class= \"centerBox\">");

  client.println("<form action='/' class=\"inputForm\" method=get >"); //uses IP/port of web page

  client.println(" <div class= \"flexBox\">");   // centered box

  client.println(" <div class= \"marginBox\"> </div>");  //

  client.println(" <div class= \"leftBox\">");   // div box for input slider/form

  //this line for text box input
  // client.println("<input type=\"number\" name=\"redPWM\" min =\"0\" max =\"255\" value= " + R + "  style=\"width: 3em\"><br>");

  //these lines for slider input;
  client.println("<div class=\"slidecontainer\">");
  client.println("<input type=\"range\" name=\"lampPWM\" min =\"0\" max =\"255\" value= " +  BRIGHT + " class=\"slider\"");
  client.println("id=\"lampRange\"><br>");   // id= "myRange used for javascript (style=\"width: 3em\") remioved
  client.println("</div>");    // close slider box
  client.println("</div>");   // close left box

  client.println(" <div class= \"rightBox\">");   // div box for apply button

  client.println("<input type=\"submit\" value=\"Apply\">");   ///</br>  removed from start of box
  client.println("</div>");   // close right box
  client.println("</div>");   // close flex box

  client.println("</form>");   // close the form
  client.println("</div>");     // close the center box


  // print javascript object;
  client.println("<script> var slider = document.getElementById(\"lampRange\");");
  client.println("var output = document.getElementById(\"lamp\");");
  client.println("output.innerHTML = slider.value;");

  client.println("slider.oninput = function() {output.innerHTML = this.value;}");
  client.println("</script>");

 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
