#include "WebFormHtmlPage.h"

void WebFormHtmlPage::generateHtml(String &outputBuffer)
{
    outputBuffer += "<!DOCTYPE HTML><html><head> <title>";
    outputBuffer += title;
    outputBuffer += "</title>";
    outputBuffer += R"___(<meta name="viewport" content="width=device-width, initial-scale=1">)___";

    // styling
    outputBuffer +=
        R"___(<style>
body {
  font-family: arial, sans-serif;
}
table {
  font-family: arial, sans-serif;
  border-collapse: collapse;
}

td, th {
  text-align: left;
  padding: 8px;
}
</style>
)___";

    outputBuffer += "</head><body>\n";
    // add an invisible iframe where we can direkt the reloads caused by button clicks:
    outputBuffer += R"___(<iframe name="invisible_iframe" style="display:none;"></iframe>)___";

    // add all interface parts of this page
    for (auto part : uiElements)
    {
        part->generateHtml(outputBuffer);
    }
    /*

    */
    outputBuffer += "</body></html>";
}

void WebFormHtmlPage::reactToRequest(WebServer &server)
{
    for (auto part : uiElements)
    {
        part->reactToRequest(server);
    }
}