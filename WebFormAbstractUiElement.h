#pragma once
#include "Arduino.h"
#include "ArduParWebHelpers.h"
/// @brief  this class represents a form entry, that can generate a snipped of HTML and parse a get query to pass on commands to an underlying parameter
class WebFormAbstractUiElement{
    public:
    virtual void generateHtml(String& outputBuffer)=0; ///< Add your own output to the String
    virtual void reactToRequest(ArduParWebServerClass& server)=0; ///< react to an incoming request, possibly parsing arguments or URIs
    void serveYourself(ArduParWebServerClass& server,size_t bufferReserve=8192); ///< serve generated HTML to Server 
};
