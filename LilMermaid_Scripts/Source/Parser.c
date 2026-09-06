#include "LilMermaid_Scripts/Headers/Parser.h"
#include "LilMermaid_Scripts/External/Libraries.h"
void Parsenize(LilMermaid_BigGirl* BigGirl, Vector* Tokens) {
    printf("\n");
    for (int x = 0;x < Len(Tokens);x++) {
        LM_Token* y = Get(Tokens, x);
        printf("(%d) \"%s\"\n", y -> Type, Substring(BigGirl -> SourceCode -> Chars, y -> Start, y -> Start + y -> Length));
    }
}