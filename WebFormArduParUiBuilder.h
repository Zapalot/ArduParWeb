#pragma once
#include "AbstractArduPar3.h"
#include "ArduPar3Collection.h"
#include "ArduParWebHelpers.h"
#include "WebFormAbstractUiElement.h"
#include "WebFormSection.h"
#include "WebFormHtmlPage.h"
#include "WebFormArduParUiEntry.h"
#include <list>

#define WebFormArduParUiBuilderSectionTitleBufferLength 40

class WebFormAddressTreeNode: public WebFormAbstractUiElement{
    public:
    WebFormAddressTreeNode(const char* nodeTextBegin,size_t nodeTextLength,const char *actionUrl, const char *submitButtonText, int branchLevel);
    virtual ~WebFormAddressTreeNode();
    void generateHtml(String &outputBuffer); ///<  Add your own output to the String
    void reactToRequest(ArduParWebServerClass &server);  ///< react to an incoming request, possibly parsing arguments or URIs
    char sectionTitleBuffer[WebFormArduParUiBuilderSectionTitleBufferLength];
    const char *actionUrl;
    const char *submitButtonText;


    void addEntry(WebFormArduParUiEntry* entry, const char* remainingAddress); // will tokenize address into parts separated by "/" and build a tree to resemble the structure of the address space
    int branchLevel=0; // how far to the root is this node?
    const char* nodeTextBegin=nullptr;
    size_t nodeTextLength=0;
    std::list<WebFormAddressTreeNode*> branches;    // created during 
    std::list<WebFormAbstractUiElement* >leafs; 
};

class WebFormArduParUiBuilder:public WebFormAbstractUiElement{
    public:
    WebFormArduParUiBuilder();
    ~WebFormArduParUiBuilder();
    void generateHtml(String &outputBuffer); ///<  Add your own output to the String
    void reactToRequest(ArduParWebServerClass &server);  ///< react to an incoming request, possibly parsing arguments or URIs

    void buildUi(ArduPar3Collection* collection,const char *actionUrl);
    void addParameter(AbstractArduPar3* par);    ///< create an WebFormArduParUiEntry for that parameter and add it to the collection
    std::list<WebFormArduParUiEntry*> uiEntries; ///< these are created on the heap in "addParameter", and destroyed in the destructor
    WebFormAddressTreeNode rootNode;
    WebFormHtmlPage htmlPage;
};