#include "LilMermaid_Scripts/Headers/Parser.h"
#include "LilMermaid_Scripts/External/Libraries.h"
LM_Token* GetToken(LM_Parser* ParserState, Usize Offset) 
{ 
    return Get(ParserState -> Tokens, Offset);
}

LM_Token* ActualToken(LM_Parser* ParserState) 
{
    ParserState -> Actual = Get(ParserState -> Tokens, ParserState -> Pointer);
    return ParserState -> Actual;
}

void NextToken(LM_Parser* ParserState, int Offset)
{
    ParserState -> Pointer += Offset;
    ParserState -> Actual = Get(ParserState -> Tokens, ParserState -> Pointer);
}

Bool ExpectToken(LM_Parser* ParserState, LM_TokenType ExpectedType, int Offset) 
{
    if (GetToken(ParserState, ParserState -> Pointer + Offset) -> Type == ExpectedType) {
        return True;
    }
    return False;
}

void Parsenize(LilMermaid_BigGirl* BigGirl, Vector* Tokens) {
    LM_Parser LocalState;
    LocalState.Pointer = 0;
    LocalState.BigGirl = BigGirl;
    LocalState.Tokens = Tokens;
    LocalState.Actual = Get(Tokens, 0);

    printf("\n");
    for (int x = 0;x < Len(Tokens);x++) {
        LM_Token* y = ActualToken(&LocalState);
        
        printf("(%d) \"%s\"\n" , y -> Type, Substring(BigGirl -> SourceCode -> Chars, y -> Start, y -> Start + y -> Length));
        
        NextToken(&LocalState, 1);
    }
}