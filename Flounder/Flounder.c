#include "Headers/FlounderManager.h"
#include "Headers/CharUtils.h"
#include "Control/Commands.h"
#include "Headers/FlounderState.h"
#include "Control/Version.h"

int main(int ArgumentCount, char* Arguments[]) {
    FL_FlounderState LocalState;
    LocalState.Actual = "";
    LocalState.Pointer = 1;
    LocalState.Arguments = Arguments;
    ReadArguments(&LocalState);
    return 0;
}