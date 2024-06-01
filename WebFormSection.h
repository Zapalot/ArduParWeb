#pragma once
#include "WebFormAbstractUiElement.h"
#include <list>
class WebFormSection : public WebFormAbstractUiElement
{
public:
    WebFormSection(const char *title, const char *actionUrl, const char *submitButtonText);

    void generateHtml(String &outputBuffer); ///<  Add your own output to the String
    void reactToRequest(WebServer &server);  ///< react to an incoming request, possibly parsing arguments or URIs
    std::list<WebFormAbstractUiElement *> uiElements;
    const char *title = 0;
    const char *actionUrl = 0;
    const char *submitButtonText = 0;
};
