#ifndef _ParserH_
#define _ParserH_

#include "Headers/InterpreterTypes.h"
#include "Headers/Lexer.h"

typedef enum EnumInstructionType {
    LM_AdressDeclr,
    LM_OperationDeclr,
    LM_AliasDeclr,
    LM_PositionDeclr
} LM_NodeType;

typedef struct StructParserNode {
    LM_NodeType Type;
    Usize Line;
    union {
        struct 
        { 
            char* Name;
            struct StructParserNode* Body; 
        } LM_AdressDeclr;

        struct 
        {
            char* x;
        } LM_RegisterOperationDeclr;

        struct 
        {
            char* Name;
            struct StrucParserNode* Value;
        } LM_AliasDeclr;
    } Data;
} LM_ParserNode;

void Parsenize(LilMermaid_BigGirl* BigGirl, Vector* Tokens);
#endif