#pragma once
#include "WebFormAbstractUiElement.h"
#include <list>
class WebFormDebugElement : public WebFormAbstractUiElement
{
public:
    WebFormDebugElement(WebServer* server) {this-> server = server;  }
    void generateHtml(String &outputBuffer); ///<  Add your own output to the String
    void reactToRequest(WebServer &server);  ///< react to an incoming request, possibly parsing arguments or URIs
    WebServer* server;
};
