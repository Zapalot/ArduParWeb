#include "WebFormArduParUiEntry.h"
#include "Arduino.h"
#include <string.h>

void WebFormArduParUiEntry::setup(AbstractArduPar3 *arduPar)
{
    myArduPar = arduPar;
}
void WebFormArduParUiEntry::generateHtml(String &outputBuffer)
{
    outputBuffer += "<td>";
    outputBuffer += myArduPar->getAddress();
    outputBuffer += "</td>\n";
    outputBuffer += "<td>";
    outputBuffer += myArduPar->getDescription();
    outputBuffer += "</td>\n";
    outputBuffer += "<td>";
    switch (myArduPar->getType(0))
    {
    case AbstractArduPar3::ArduPar3TypeTrigger:
        outputBuffer += R"___( <input type="submit" formtarget="invisible_iframe" value=")___";
        outputBuffer += myArduPar->getDescription();
        outputBuffer += "\" name= \"";
        outputBuffer += myArduPar->getAddress();
        outputBuffer += R"(">)";
        break;
    case AbstractArduPar3::ArduPar3TypeBool:
    {
        String elementCode=R"(<input type="hidden" name="%checkboxName%" value="%checkboxState%"><input type="checkbox" onclick="this.previousElementSibling.value=1-this.previousElementSibling.value" %checked%>)";
        elementCode.replace("%checkboxName%",myArduPar->getAddress());
        elementCode.replace("%checkboxState%",myArduPar->getValueAsBool(0)?"1":"0");
        elementCode.replace("%checked%",myArduPar->getValueAsBool(0)?"checked":"");
        outputBuffer+=elementCode;
    }
    break;
    default:
        outputBuffer += R"( <input type="text" name=")";
        outputBuffer += myArduPar->getAddress();
        outputBuffer += R"(" value=")";

        const int bufSize = 256;
        char buffer[bufSize];
        size_t valTextLength = myArduPar->getValueTextLength();
        if (bufSize < valTextLength)
        {
            Serial.println(F("WARNING: insufficient buffer to represent parameter content!"));
            return;
        }
        myArduPar->getValueAsText(buffer, bufSize);
        outputBuffer += buffer;
        outputBuffer += R"(">)";
    }
    outputBuffer += "</td>\n";
}
void WebFormArduParUiEntry::reactToRequest(ArduParWebServerClass &server)
{
    // everything that's not a trigger parameter needs a submit button to be pressed in order to update
    if (myArduPar->getType(0) != AbstractArduPar3::ArduPar3TypeTrigger)
    {
        if (!server.hasArg("___submit___"))
            return;
    }
    String addressAsString = myArduPar->getAddress();
    for (int i = 0; i < server.args(); i++)
    {
        if (server.argName(i) == addressAsString)
            myArduPar->setValueFromText(server.arg(i).c_str());
    }
}
