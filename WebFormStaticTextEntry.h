#include "WebFormAbstractUiElement.h"

/// @brief  Adds a static piece of text to the outputBuffer (that can be literally everything)
class WebFormStaticTextEntry : public WebFormAbstractUiElement
{
public:
    WebFormStaticTextEntry(const char* text){this->text=text;};
    void generateHtml(String &outputBuffer){outputBuffer+=text;}; ///<  Add your own output to the String
    void reactToRequest(ArduParWebServerClass &server){};  ///< no reactions
    const char *text = 0;
};
