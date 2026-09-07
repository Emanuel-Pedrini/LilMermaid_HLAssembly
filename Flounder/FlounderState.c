#include <stdlib.h>
#include <stdio.h>

#include "Headers/FlounderState.h"
#include "Headers/FlounderManager.h"
#include "Headers/CharUtils.h"
#include "Control/Commands.h"

char* GetArgument(FL_FlounderState* FlounderState, int Offset) 
{
    char* ActualArgument = FlounderState -> Arguments[FlounderState -> Pointer + Offset];
    return ActualArgument;
}

void NextArgument(FL_FlounderState* FlounderState, int Offset)
{
    FlounderState -> Pointer += Offset;
    char* ActualArgument = FlounderState -> Arguments[FlounderState -> Pointer];
}

void ReadArguments(FL_FlounderState* FlounderState) 
{
    while (GetArgument(FlounderState, 0) != NULL) {
        if (IsEqual(GetArgument(FlounderState, 0), CREATE_COMMAND)) 
        {
            CreateFlounder(GetArgument(FlounderState, 1));
        }
        if (IsEqual(GetArgument(FlounderState, 0), INITIALIZE_COMMAND)) 
        {
            CreateFlounder("");
        }
        printf("%s\n", GetArgument(FlounderState, 0));
        NextArgument(FlounderState, 1);
    }
}