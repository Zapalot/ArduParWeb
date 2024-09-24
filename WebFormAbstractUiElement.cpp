#include "WebFormAbstractUiElement.h"

// this is especially useful for building callback functions:
// i.e. server.on("/address", [](){uiElementInstance.serveYourself(server)});
void WebFormAbstractUiElement::serveYourself(ArduParWebServerClass& server,size_t bufferReserve){
    String pageContent;
    pageContent.reserve(bufferReserve); // maybe we should just not do that
    reactToRequest(server);
    generateHtml(pageContent);
    server.send(200, "text/html", pageContent);
}