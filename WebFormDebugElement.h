#pragma once
#include "WebFormAbstractUiElement.h"
#include <list>
class WebFormDebugElement : public WebFormAbstractUiElement
{
public:
    WebFormDebugElement(ArduParWebServerClass* server) {this-> server = server;  }
    void generateHtml(String &outputBuffer); ///<  Add your own output to the String
    void reactToRequest(ArduParWebServerClass &server);  ///< react to an incoming request, possibly parsing arguments or URIs
    ArduParWebServerClass* server;
};
