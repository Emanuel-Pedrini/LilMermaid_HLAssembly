#ifndef _ReaderH_
#define _ReaderH_

typedef enum {
    C = 1,
    MACHINE_CODE
} TargetAttribute;

typedef enum {
    COMPILE_INDIVIDUALLY = 1
} Specifications;

typedef struct StructCompAttributes {
    TargetAttribute Target;
    String* Paths;
    Vector* Specifications;
    char* TargetArchive;
} CompAttributes;

CompAttributes* Reader(int NumberOfArguments, char** Arguments);
void ReadCallArgument(CompAttributes* Attributes, char* Argument);
void ReadPath(CompAttributes* CompilationAttributes, LilMermaid_BigGirl* BigGirl);

#endif