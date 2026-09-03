#ifndef _CodeObjectH_
#define _CodeObjectH_

#include "Headers/ArrayUtilities.h"
#include "Headers/StringUtilities.h"

typedef struct {
    char* Code;
    char* Path;
    char* Name;
} LilMermaid_CodeObject;

typedef struct {
    Vector* CodeObjects;
    String* SourceCode;
    String* OutputPath;
} LilMermaid_BigGirl;

void GirlAppend(LilMermaid_BigGirl* Girl, LilMermaid_CodeObject* CodeObject);
void GirlInit(LilMermaid_BigGirl* Girl);

#endif