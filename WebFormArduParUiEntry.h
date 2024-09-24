#pragma once
#include "WebFormAbstractUiElement.h"
#include "AbstractArduPar3.h"
// Represents a user interface for a single ArduPar
class WebFormArduParUiEntry:public WebFormAbstractUiElement{
    public:
    virtual ~WebFormArduParUiEntry(){};
    void setup(AbstractArduPar3* arduPar);
    void generateHtml(String& outputBuffer); ///<  Add your own output to the String
    void reactToRequest(ArduParWebServerClass& server);  ///< react to an incoming request, possibly parsing arguments or URIs   
    AbstractArduPar3* myArduPar;
    
    const int maxAddressLength=40;
};
