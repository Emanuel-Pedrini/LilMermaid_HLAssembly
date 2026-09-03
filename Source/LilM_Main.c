#include "External/Libraries.h"
#include "Headers/ArchiveManager.h"
#include "Headers/StringUtilities.h"
#include "Headers/InterpreterConstants.h"
#include "Headers/Lexer.h"
#include "Headers/Parser.h"
#include "Headers/Cleaner.h"
#include "Headers/Reader.h"
#include "Headers/Compiler.h"

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
    return 0;
}
