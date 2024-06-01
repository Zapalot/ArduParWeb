#pragma once
#include "Arduino.h"
#include <WebServer.h>
/// @brief  this class represents a form entry, that can generate a snipped of HTML and parse a get query to pass on commands to an underlying parameter
class WebFormAbstractUiElement{
    public:
    virtual void generateHtml(String& outputBuffer)=0; ///< Add your own output to the String
    virtual void reactToRequest(WebServer& server)=0; ///< react to an incoming request, possibly parsing arguments or URIs
};