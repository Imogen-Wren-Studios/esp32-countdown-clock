// ~~~~~~~~ Wifi Functions ~~~~~~~~

#include <WiFi.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Access Point/Station Variables ~~~~~

// Variables for SOFT AP (Access Point)
const char* APssid     = "countdownClock";              //Wifi Name  - SSID
const char* APpassword = "12345678";                  //Router Password - PASSWORD       // Minimum 8 Characters

#define USE_AP_PASSWORD false
#define USE_DEFAULT_IP false

// Variables for Local network (Station)
//const char* STssid = "EE-Hub-G3ge";
//const char* STpassword = "stock-led-HALF";
const char* STssid = "Skyrora_Works";
const char* STpassword = "Barbos_1243%";


#define USE_STATIC_IP true             // Only effects parameters when in station mode


#define USE_ACCESS_POINT true        // Not implemented yet - No effect
#define USE_STATION false




//~~~~~~ IP Info ~~~~

//wiFi.softAPIP - This defaults to 192.168.4.1   // Can be overwritten

// Set web server port number to 80
WiFiServer server(80);

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 4);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 254);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional





unsigned int connectionAttempts = 0;          // Number of attempts taken to connect to wifi

unsigned int maxAttempts = 10;              // Maximum number of attempts before reset or alternative action

unsigned long rolloverDelay = 500;   // time between attempts with different wifi credentials.

unsigned long resetDelay = 10000;    // disconnected time that would trigger a reset





// Disconnect all wifi (can be used for stability before restarting wifi)

void disconnectWIFI() {

  Serial.println(F("Wifi Disconnecting.."));

  //////////////////////////////////////////////////////////////////////////////////////BUG FIX POWER UP WIFI ISSUE??????????????????????????????
  WiFi.disconnect(true);                     // disconnects STA Mode
  delay(1000);
  WiFi.softAPdisconnect(true);           // disconnects AP Mode
  delay(1000);
  /////////////////////////////////////////////////////////////////////////////////////////

  Serial.println(F("Wifi Successfully Disconnected"));
}









// Set up Server as an Access Point (AP)

void setup_accessPoint() {

  disconnectWIFI();

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open

//  WiFi.hostname("relay");

  if (USE_AP_PASSWORD) {
    WiFi.softAP(APssid, APpassword);
  } else {
    WiFi.softAP(APssid);
  }

  IPAddress IP;
  if (USE_DEFAULT_IP) {
    IP = WiFi.softAPIP();                     //wiFi.softAPIP - This defaults to 192.168.4.1
  } else {
    IP = local_IP;
  }

  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();

  Serial.println("Server Ready");
}




// Connect to wifi with a Static IP

void connectWifi_staticIP() {

  disconnectWIFI();

  delay(2000);  // delay for power issue during wifi startup // decoupling cap added to board as well.

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
    delay(1);
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(STssid);
  WiFi.begin(STssid, STpassword);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.printf("  Connection Attempt: %i \n", connectionAttempts);

    connectionAttempts++;
    if (connectionAttempts >= maxAttempts) {
      delay(1);
      Serial.println("....");
      Serial.println("RESETTING!");
      Serial.println(" ");
      ESP.restart();;
      connectionAttempts = 0;
    }
  }

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

}


// ~~~~~~~~ Wifi Utilities ~~~~~~~~
/*
 *  Off the Shelf Functions for setting up ESP32 wifi modules
 * 
 * 
 * 
 * 
 */





// Connect to a Wifi Router as a Station - uses DHCP

void connectWifi_as_station() {

  disconnectWIFI();

  Serial.println(F("Trying to connect to WiFi as Station"));

  WiFi.begin(STssid, STpassword);
  delay(1000);


  int wificheck = millis();

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
    Serial.printf("  Connection Attempt: %i \n", connectionAttempts);

    connectionAttempts++;
    if (connectionAttempts >= maxAttempts) {
      // This does nothing at the moment might do something later.
      connectionAttempts = 0;
    }

    if ((millis() - wificheck) > 10000) {
      Serial.println("....");
      Serial.println("RESETTING!");
      Serial.println(" ");
      ESP.restart();;
    }
  }
  Serial.println("WiFi Connected Successfully");
}
