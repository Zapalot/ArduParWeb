#pragma once
#include "Arduino.h"
class CharBuffer{
    public:
    CharBuffer(char* buffer, size_t bufferSize); // buffer has to be preallocated
    char* buffer;

    size_t getCurrentPosInBuffer(){return curPos;}
    size_t getBytesRemaining(){return bufferSize-curPos;};
    char* getStartOfEmpty(){return buffer+curPos;}
    bool advanceCurPos(size_t numBytes);
    bool append(const char* src);
    bool appendSubstituted(const char* src, char replace, char by);  // subsititutes a special character by some other, useful for using OSC addresses in forms
    void reset(){curPos=0;}
protected:
    size_t bufferSize;
    size_t curPos;

};