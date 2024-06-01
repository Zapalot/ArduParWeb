#pragma once
#include "WebFormAbstractUiElement.h"
#include <list>
class WebFormHtmlPage : public WebFormAbstractUiElement
{
public:
    WebFormHtmlPage(const char *title) { this->title = title; }
    void generateHtml(String &outputBuffer); ///<  Add your own output to the String
    void reactToRequest(WebServer &server);  ///< react to an incoming request, possibly parsing arguments or URIs
    std::list<WebFormAbstractUiElement *> uiElements;
    const char *title = 0;
};
