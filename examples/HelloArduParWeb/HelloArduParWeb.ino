#include "ArduPar3.h"
//An example for a simple web based user interface using ArduPar3
//Tested on ESP32 (will not work ATMega based Arduinos)

///// Create some ArduPar3 parameters and useful Callbacks to play with
ArduPar3Collection parameterCollection;  // create a collection for parameters so we can conveniently do things with all of them at once

float someFloat = 0;  // we will controll the value of this number
SingleFloatArduPar3 someFloatParameter;

int32_t someInt = 0;  // we will controll the value of this number too
SingleInt32ArduPar3 someInt32Parameter;

// A function that can be triggered remotely to print all parameter states
void dumpFunction() {
  parameterCollection.dumpParameterInfos(&Serial);
}
CallbackArduPar3 dumpCallbackParameter;
// A function that can be triggered remotely to load parameter states
void loadFunction() {
  parameterCollection.loadAll();
}
CallbackArduPar3 loadCallbackParameter;

// A function that can be triggered remotely to save parameter states
void saveFunction() {
  parameterCollection.saveAll();
}
CallbackArduPar3 saveCallbackParameter;

//////////////////////////Everything WiFi
#include <esp_wifi.h>
#include <WiFi.h>

void setupWifi(const char *ssid, const char *password);

///////////////////everything Web///
#include <WiFiClient.h>
#include <WebServer.h>

WebServer server(80);
void notFound();            // function to call on unknon URIs
void serveArduParFormUi();  // function to serve our UI

#include "WebFormArduParUiEntry.h"
#include "WebFormSection.h"
#include "WebFormHtmlPage.h"
#include "WebFormDebugElement.h"
#include "WebFormArduParUiBuilder.h"

WebFormArduParUiBuilder arduParUi;
WebFormDebugElement debugSection(&server);


void setup() {
  Serial.begin(115200);
  /// try to get connected to a WiFi
  setupWifi("SSID", "Password");

  // initialize parameters and callbacks
  ArduPar3Collection::globalDefaultCollection = &parameterCollection;  // use our parameter collection as a default
  someFloatParameter.setup(PSTR("/numbers/someFloat"), PSTR("An exquisite float"), 0, 10, &someFloat);
  someInt32Parameter.setup(PSTR("/numbers/someInt"), PSTR("An exquisite integer"), 0, 10000, &someInt);
  dumpCallbackParameter.setup(PSTR("/commands/dump"), PSTR("Print Parameter Summary"), &dumpFunction);
  loadCallbackParameter.setup(PSTR("/commands/load"), PSTR("Load Settings."), &loadFunction);
  saveCallbackParameter.setup(PSTR("/commands/save"), PSTR("Save Settings."), &saveFunction);

  delay(500);
  // print current values of parameters to serial
  parameterCollection.dumpParameterInfos(&Serial);
  /////// initialize the web interface
  arduParUi.buildUi(ArduPar3Collection::globalDefaultCollection, "/");  // initialize the web-user interfac
  /// setup web server to serve our interface
  server.on("/", serveArduParFormUi);
  server.onNotFound(notFound);
  server.begin();

  //  write the generated web page to serial for debug purposes
  String buffer;
  arduParUi.generateHtml(buffer);
  Serial.println(buffer);
}

void loop() {
  server.handleClient();                                          // let the webserver serve clients
  parameterCollection.updateParametersFromStream(&Serial, 1000);  // read commands from serial
  delay(2);                                                       //allow the cpu to switch to other tasks
}

void setupWifi(const char *ssid, const char *password) {

  Serial.print("Connecting to wifi network \"");
  Serial.print(ssid);
  Serial.print("\" .");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  long start = millis();
  // try for ten seconds to connect every 500 ms (i.e. make 10000/500 = 20 attempts)
  while (WiFi.status() != WL_CONNECTED && millis() - start < 4000) {
    Serial.print(".");
    delay(500);
  }

  // print result of connection attempt(s) on serial console
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print(" failed with status ");
    Serial.println(WiFi.status());
  } else {
    Serial.println(" succeeded");
    Serial.print("local IP address is ");
    Serial.println(WiFi.localIP());
    esp_wifi_set_ps(WIFI_PS_NONE);
  }
}
// function to serve our UI
void serveArduParFormUi() {
  // print a debug message to the serial
  bool debug = true;
  if (debug) {
    String message = "_________new Request!\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    Serial.println(message);
  }

  arduParUi.reactToRequest(server);  // let the user interface update parameters based on the get/post arguments
  String pageContent;                // reserve memory for the page to serve to the client
  pageContent.reserve(8192);
  arduParUi.generateHtml(pageContent);         // build the webpage to be served
  server.send(200, "text/html", pageContent);  // send the webpage to the client
}

void notFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
