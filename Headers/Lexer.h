#ifndef _LexerH_
#define _LexerH_
#include "Headers/ArrayUtilities.h"
#include "Headers/CodeObject.h"

#define STRING_MARKER '\"' 
#define REGISTER_MARKER '.'
#define ARCHIVE_MARKER '`'

#define CONSTANT_KEYWORD "def"
#define RETURN_KEYWORD "ret"
#define WRITE_KEYWORD "writ"
#define END_OF_CODE_KEYWORD "__END_OF_CODE__"

typedef struct {
    
    String* Code;

    Usize Pointer;
    char Char;
    Usize Line;

} LexerState;

void Tokenize(LilMermaid_BigGirl* Girl, Vector* Tokens);
Bool Is(const char* Word, const char* Src);
typedef enum {
    Tk_Illegal, // 0
    Tk_ArchiveMarker, // 1
    
    Tk_Adress, // 2
    Tk_Integer, // 3
    Tk_Colon, // 4
    Tk_Point, // 5
    Tk_Comma, // 6
    Tk_Percentage,// 7
    Tk_Asterisk,// 8
    Tk_Commercial,// 9
    Tk_Money,// 10
    Tk_Hashtag,// 11
    Tk_Bang,// 12
    Tk_Interrogation,// 13
    Tk_Backslash,// 14
    Tk_Pipe,// 15

    Tk_DoublePoint,// 16
    Tk_DoubleBackslash,// 17
    Tk_DoubleCommercial,// 18
    Tk_DoublePipe,// 19
    Tk_DoubleAsterisk,// 20
    Tk_String,// 21

    Tk_LeftArrow,// 22
    Tk_RightArrow,// 23
    Tk_LeftDoubleArrow,// 24
    Tk_RightDoubleArrow,// 25
    Tk_LeftTripleArrow,// 26
    Tk_RightTripleArrow,// 27
    Tk_UpArrow,// 28

    Tk_Minus,// 29
    Tk_MinusMinus,// 30
    Tk_Plus,// 31
    Tk_PlusPLus,// 32
    Tk_Equal,// 33
    Tk_EqualEqual,// 34
    Tk_Div,// 35
    Tk_DivDiv,// 36

    Tk_LeftParenthesis,// 37
    Tk_RightParenthesis,// 38
    Tk_LeftBrace,// 39
    Tk_RightBrace,// 40
    Tk_LeftKeys,// 41
    Tk_RightKeys,// 42

    Tk_Indentifier,// 43
    Tk_Return,// 44
    Tk_Register,// 45
    Tk_Define,// 46
    Tk_Write,// 47
    Tk_EndOfCode,// 48
    Tk_Push,
    Tk_Pop

} LM_TokenType;

typedef struct {
    LM_TokenType Type;
    Usize Start;
    Usize Length;
} LM_Token;

#endif