#include "WebFormDebugElement.h"

void WebFormDebugElement::generateHtml(String &outputBuffer)
{
    // add debug info:
    outputBuffer += "URI: ";
    outputBuffer += server->uri();
    outputBuffer += "<br>Method: ";
    outputBuffer += (server->method() == HTTP_GET) ? "GET" : "POST";
    outputBuffer += "<br>Arguments: ";
    outputBuffer += server->args();

    for (int i = 0; i < server->args(); i++)
    {
        outputBuffer += "<br>";
        outputBuffer += server->argName(i);
        outputBuffer += "\t:\t";
        outputBuffer += server->arg(i);
    }
    outputBuffer += "<br>";
}

void WebFormDebugElement::reactToRequest(WebServer &server)
{
}