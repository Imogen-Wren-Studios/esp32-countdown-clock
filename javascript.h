/* Javascript functions go here




*/



// New Idea

void javascriptClockItem(WiFiClient client) {


  client.println("<div>");
  client.println("<p1 id='live_clock'></p>");
  client.println("</div>");

}


/*

void write_xml(int inputData){

 if(xmlDocument.Parse(live_clock)!= XML_SUCCESS){
    Serial.println("Error parsing"); 
    return; 
  };
  
}

void script_read_xml(){

 
  XMLNode * root = xmlDocument.FirstChild();
  XMLElement * element = root->FirstChildElement("element");
 
  int val;
  element->QueryIntText(&val);
   
  Serial.println(val);
  
}
*/


// Client side clock. Advantages - less load on microcontroller. No refresh of page required.
//disadvantages - no true sync between webpage clock and actual clock time.
// Needs alot more work to work smoothly through t = 0
// This whole thing is scuffed

void clockData_toJson(WiFiClient client, int h, int m, int s) {


  client.println("<script>");

  // Set up variables

  client.print("var hours =");
  client.print(h);
  client.println(";");

  client.print("var mins =");
  client.print(m);
  client.println(";");

  client.print("var sec =");
  client.print(s - 1);
  client.println(";");


  // Update the count down every 1 second

  client.println("var x = setInterval(function() {");

  if (simpleClock.runCountdown) {
    client.println("sec = (sec - 1);");
    
// if minuites and seconds = zero, subtract 1 from hours
        client.println("if (mins <= 0 && sec <= 0){");
    client.println("hours = hours - 1;");
    client.println("if (hours > 1){");
    client.println("mins = 60;");
    client.println("}");

// if seconds is zero subtract 1 from minuites
    client.println("if (sec <= 0){");
    client.println("sec = 60;");
    client.println("mins = mins -1;");
    client.println("}");


    client.println("}");
  }
 


  client.print("document.getElementById(\"live_clock\").innerHTML =");

if (simpleClock.tminus){
  client.print("hours");
  client.print(" + \":\" + ");
  client.print("mins");
  client.print(" + \":\" + ");
  client.print("sec");
} else {
client.print("T > 0 || Test In Progress || ");
  
}
  client.println(";");

  client.println("}, 1000);");


client.println("</script>");


}





// This updater requires data to be saved in an XML document called "liveClock" with the data laid out like

// {"live_clock": T- 00:20:10}

// This may be possible with tinyxm12.h library
/*
  void javascriptXMLUpdater(){

  <script>
    requestData(); // get intial data straight away

    // request data updates every 5000 milliseconds
    setInterval(requestData, 1000);

    function requestData() {

      var xhr = new XMLHttpRequest();
      xhr.open('GET', 'liveClock');

      xhr.onload = function() {
        if (xhr.status === 200) {

          if (xhr.responseText) { // if the returned data is not null, update the values

            var data = JSON.parse(xhr.responseText);

            document.getElementById("live_clock").innerText = data.live_clock;


          } else { // a problem occurred

            document.getElementById("live_clock").innerText = "?";

          }
        } else {
          console.log('Request failed.  Returned status of ' + xhr.status);

          document.getElementById("live_clock").innerText = "00:00:00";


        }
      };

      xhr.send();
    }

  </script>

  }
*/


















// Old didnt work stuff
// Live Clock - Broken atm

/*
  void javaScript_timeHead(WiFiClient client) {

  // This Code goes in Head //
  client.println("<script>");
  client.println("function startTime() {");

  client.println("var time = simpleClock.countdown_clock_string");

  client.println("  document.getElementById('webTime').innerHTML =");
  client.println(" time;");
  client.println("  var t = setTimeout(startTime, 500);");
  client.println("}");


  client.println("</script>");
  // </head>
  }


  void javascript_timeBody(WiFiClient client) {
  // Code for body //
  client.println("<body onload=\"startTime()\">");

  client.println("<div id=\"webTime\"></div>");



  }

*/
