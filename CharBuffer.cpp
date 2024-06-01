#include "CharBuffer.h"
; // buffer has to be preallocated
CharBuffer::CharBuffer(char* buffer, size_t bufferSize){
    this->buffer=buffer;
    this->bufferSize=bufferSize;
}
bool CharBuffer::advanceCurPos(size_t numBytes){
    if(getBytesRemaining()>=numBytes){
        curPos+=numBytes;
        return true;
    }
    return false;
};

bool CharBuffer::append(const char* src){
    size_t bytesToCopy=strlen(src);
    if(bytesToCopy>getBytesRemaining())return false;
    strcpy(getStartOfEmpty(),src);
    curPos+=bytesToCopy;
    return true;
}
 // subsititutes a special character by some other, useful for using OSC addresses in forms
bool CharBuffer::appendSubstituted(const char* src, char replace, char by){
    size_t bytesToCopy=strlen(src);
    if(bytesToCopy>getBytesRemaining())return false; 
    while(*src){
        buffer[curPos]=*src==replace?by:*src;
        curPos++;
        src++;
    }
    return true;
}
