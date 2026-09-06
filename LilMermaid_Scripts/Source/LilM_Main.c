#include "LilMermaid_Scripts/External/Libraries.h"
#include "LilMermaid_Scripts/Headers/ArchiveManager.h"
#include "LilMermaid_Scripts/Headers/StringUtilities.h"
#include "LilMermaid_Scripts/Headers/InterpreterConstants.h"
#include "LilMermaid_Scripts/Headers/Lexer.h"
#include "LilMermaid_Scripts/Headers/Parser.h"
#include "LilMermaid_Scripts/Headers/Cleaner.h"
#include "LilMermaid_Scripts/Headers/Reader.h"
#include "LilMermaid_Scripts/Headers/RustLibrary.h"

int main(int argc, char* argv[]) {
    CompAttributes* CompilationAttributes = Reader(argc, argv);
    LilMermaid_BigGirl BigGirl;
    Vector Tokens;
    New(&Tokens, sizeof(LM_Token));
    GirlInit(&BigGirl);
    ReadPath(CompilationAttributes, &BigGirl);
    Clean(&BigGirl);
    Tokenize(&BigGirl, &Tokens);
    Parsenize(&BigGirl, &Tokens);
    RustPrint(24, 57);
    return 0;
}
