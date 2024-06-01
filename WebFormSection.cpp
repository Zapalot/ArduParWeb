#include "WebFormSection.h"

WebFormSection::WebFormSection(const char *title, const char *actionUrl, const char *submitButtonText) : title(title),
                                                                                                         actionUrl(actionUrl),
                                                                                                         submitButtonText(submitButtonText)
{
}

void WebFormSection::generateHtml(String&  outputBuffer)
{
    outputBuffer+="<h2>";
    outputBuffer+=title;
    outputBuffer+="</h2><br>\n";
    outputBuffer+=R"RawLiteral(<form action=")RawLiteral";
    outputBuffer+=actionUrl;
    outputBuffer+="\">\n";
    outputBuffer+="<br>";
    outputBuffer+="<table>";
    // add all interface parts of this page

    for (auto part : uiElements)
    {
        outputBuffer+="<tr>";
        part->generateHtml(outputBuffer);
        outputBuffer+="</tr>";
    }
    outputBuffer+="</table>\n<br>";
    outputBuffer+=R"RawLiteral(<input type="submit" name="___submit___" value=")RawLiteral";
    outputBuffer+=submitButtonText;
    outputBuffer+="\">";
    outputBuffer+="</form>\n";
}

void WebFormSection::reactToRequest(WebServer& server)
{
    for (auto part : uiElements)
    {
        part->reactToRequest(server);
    }
}