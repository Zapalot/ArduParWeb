#include "WebFormArduParUiBuilder.h"

WebFormArduParUiBuilder::WebFormArduParUiBuilder():rootNode("/", 1,"/","Submit",0),
htmlPage((const char*)F("ArduPar"))
{
    
}

WebFormArduParUiBuilder::~WebFormArduParUiBuilder()
{
    for (auto curUiEntry : uiEntries)
        delete curUiEntry;

} ///<  Add your own output to the String
void WebFormArduParUiBuilder::generateHtml(String &outputBuffer)
{
    htmlPage.generateHtml(outputBuffer);    
}
///< react to an incoming request, possibly parsing arguments or URIs
void WebFormArduParUiBuilder::reactToRequest(WebServer &server)
{
    htmlPage.reactToRequest(server);
}

void WebFormArduParUiBuilder::buildUi(ArduPar3Collection *collection,const char *actionUrl)
{
    rootNode.actionUrl=actionUrl;
    for (int i = 0; i < collection->numInstancesRegistered; i++)
    {
        addParameter(collection->knownInstances[i]);
    }
    htmlPage.uiElements.push_back(&rootNode);
}
void WebFormArduParUiBuilder::addParameter(AbstractArduPar3 *par)
{

    WebFormArduParUiEntry *newEntry = new WebFormArduParUiEntry();
    newEntry->setup(par);
    uiEntries.push_back(newEntry);
    rootNode.addEntry(newEntry, par->getAddress());

}

WebFormAddressTreeNode::WebFormAddressTreeNode(const char *nodeTextBegin, size_t nodeTextLength,const char *actionUrl, const char *submitButtonText, int branchLevel)
{
    this->nodeTextBegin = nodeTextBegin;
    this->nodeTextLength = nodeTextLength;
    this->actionUrl=actionUrl;
    this->submitButtonText=submitButtonText;
    this-> branchLevel=branchLevel;
    // build a section title
    strncpy(sectionTitleBuffer, nodeTextBegin, min((size_t)(WebFormArduParUiBuilderSectionTitleBufferLength - 1), nodeTextLength));
    sectionTitleBuffer[nodeTextLength] = 0;
};
WebFormAddressTreeNode::~WebFormAddressTreeNode(){
    for (auto curBranch : branches)
        delete curBranch;

}

// will tokenize address into parts separated by "/" and build a tree to resemble the structure of the address space
void WebFormAddressTreeNode::addEntry(WebFormArduParUiEntry *entry, const char *remainingAddress)
{

    //Serial.print("Processing Par:");
    //Serial.println(remainingAddress);

    // tokenize address into parts separated by "/" and build a tree to resemble the structure of the address space
    while (*remainingAddress == '/')
        remainingAddress++; // skip trailing slashes
    const char *nextSlash = strchr(remainingAddress, '/');

    // is this the last part of the address? then add it to out list of leafs
    if (nextSlash == nullptr)
    {
        //Serial.print("Adding Par as Leaf.");
        leafs.push_back(entry);
        //Serial.print("finished.");
        return;
    }
    int nCharsInNextPart = nextSlash - remainingAddress;
    //Serial.print("chars to next slash:");
    //Serial.println(nCharsInNextPart);
    // otherwise check if we already have a branch for the next address part
    bool matchedBranch = false;
    for (auto curBranch : branches)
    {
        //Serial.print("Comparing to Branch:");
        //Serial.println(curBranch->nodeTextBegin);
        if (strncmp(remainingAddress, curBranch->nodeTextBegin, nCharsInNextPart) == 0)
        {
            curBranch->addEntry(entry, nextSlash + 1);
            matchedBranch = true;
            break;
        }
    }
    // if none of the Branches matched, create a new one
    if (!matchedBranch)
    {
        //Serial.print("Creating Branch:");
        //Serial.println(remainingAddress);
        WebFormAddressTreeNode *newNode = new WebFormAddressTreeNode(remainingAddress, nCharsInNextPart,actionUrl,submitButtonText,branchLevel+1);

        branches.push_back(newNode);
        branches.back()->addEntry(entry, nextSlash + 1);
    }
}

///< react to an incoming request, possibly parsing arguments or URIs
void WebFormAddressTreeNode::reactToRequest(WebServer &server)
{
    for (auto curBranch : branches)
        curBranch->reactToRequest(server);
    for (auto curLeaf : leafs)
        curLeaf->reactToRequest(server);
}

void WebFormAddressTreeNode::generateHtml(String &outputBuffer)
{
    outputBuffer += "<h"+String(branchLevel)+">";
    outputBuffer += sectionTitleBuffer;
    outputBuffer += "</h"+String(branchLevel)+"><br>\n";
    if (leafs.size() > 0)
    {
        // start of a form
        outputBuffer += R"RawLiteral(<form action=")RawLiteral";
        outputBuffer += actionUrl;
        outputBuffer += "\">\n";
        outputBuffer += "<br>";
        outputBuffer += "<table>";
        // add all interface parts of this page
        for (auto curLeaf : leafs)
        {
            outputBuffer += "<tr>";
            curLeaf->generateHtml(outputBuffer);
            outputBuffer += "</tr>";
        }
        //end of form
        outputBuffer+="</table>\n<br>";
        outputBuffer+=R"RawLiteral(<input type="submit" name="___submit___" value=")RawLiteral";
        outputBuffer+=submitButtonText;
        outputBuffer+="\">";
        outputBuffer+="</form>\n";
    }

    for (auto curBranch : branches)
        curBranch->generateHtml(outputBuffer);
}