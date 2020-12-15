/*
     Function here calls the stylesheet for the displayed page




*/



#include <WiFi.h>


//---------------------------------------------------------CSS--------------------------------------------------------------
// CSS to style the on/off buttons

// --------------------------------- function calls CSS sheet-------------
void callCSS(WiFiClient client) {               // passed wifi client ?? it works I know not why
  client.println("<style>");

  client.println("html { font-family: Consolas; display: inline-block; margin: 0px auto; text-align: center;}");

 // client.println("body {background-color: #212121; color:#e68a00;}");  // Old Style
 client.println("body {background-color: #212121; color:#f0f0f0;}");

 client.println("p1 { text-align: center;  font-size: 20px;  margin-top: 2px;}"); // added for live clock
 

  client.println(".button { background-color: #00cccc; border: none; color: white; padding: 16px 20px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");

  client.println(".button2 {background-color: #555555;}");

  client.println(".inputForm {display: flex; overflow-y: scroll; padding-bottom: 1px;}");
  client.println(".inputForm input {margin: 5px; min-width: 40px; font-size: 1.025em; font-weight: bold; ");
  client.println("border: 1px solid #e68a00; border-left: 3px solid; border-radius: 5px; ");
  client.println("transition: border-color .5s ease-out; text-align: center;}");

  client.println(".centerBox { height: 100%; margin: auto;}");  //max-width: 100%; (display: flex; justify-content:center;)  removed

  client.println(".flexBox{display: flex; flex-direction: row;  flex-wrap: nowrap;");           // another div box to help center things
  client.println("justify-content: center;  align-items: stretch;  align-content: center; }");
  
 client.println(".marginBox(display: flex; float:left; width: 5%; height: 5%;}");  // could be used for making outside boxes to space inner ones
 
  client.println(".leftBox {display: flex;  float:left;  justify-content:center; margin: auto;}");
  client.println(".rightBox {display: flex;  float:right;  justify-content:center; margin: auto;}"); // margin could be auto

  //  CSS for the sliders
  client.println(".slidecontainer {width: 100%;}");                      // Width of the outside container

  // The slider itself   //Override default CSS styles
  client.println(".slider {-webkit-appearance: none;  width: 100%; height: 10px;");   //appearance: none; removed
  client.println("background: #d3d3d3; outline: none;   border-radius: 10px; opacity: 0.7;");    // Set transparency (for mouse-over effects on hover)
  client.println("-webkit-transition: .2s;  transition: opacity .2s;}");                                                                                                                      // 0.2 seconds transition on hover */


  // /* Mouse-over effects *//* Fully shown on mouse-over */
  client.println(".slider: hover {opacity: 1;}");

  //    The slider handle (use -webkit- (Chrome, Opera, Safari, Edge) and -moz- (Firefox) to override default look)
  client.println(".slider:: -webkit - slider - thumb {-webkit - appearance: none; appearance: none;");
  client.println("width: 25px; height: 25px; background: #00cccc;  border-radius: 50%;  cursor: pointer;}");  // Set a specific slider handle width // Slider handle height
  //  Cursor on hover

  client.println(".slider::-moz-range-thumb {width: 25px;  height: 25px;  background: #4CAF50; cursor: pointer;}");
  // Set a specific slider handle width Slider handle height */
  // Cursor on hover */




  // added line for text box;
    client.println("input[type=number] {  width: 20%;  padding: 5px 5px;  margin: 2px 2px;  box-sizing: border-box;}"); // added line


  client.println("</style></head>");

}
