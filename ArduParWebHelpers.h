#pragma once
#ifdef ESP8266
#include <ESP8266WebServer.h>
#define ArduParWebServerClass ESP8266WebServer
#endif

#ifdef ESP32
#include <WebServer.h>
#define ArduParWebServerClass WebServer
#endif