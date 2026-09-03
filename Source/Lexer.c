#include "Headers/CodeObject.h"
#include "Headers/ArrayUtilities.h"
#include "Headers/StringUtilities.h"
#include "Headers/Lexer.h"
#include "External/Libraries.h"

char ActualChar(LexerState* MermaidState) {
    return MermaidState -> Code -> Chars[MermaidState -> Pointer];
}

char Peek(LexerState* MermaidState, int Offset) {
    return MermaidState -> Code -> Chars[MermaidState -> Pointer + Offset];
}

void Next(LexerState* MermaidState, int Offset) {
    MermaidState -> Pointer += Offset;
}

void Skip(LexerState* MermaidState) {
    while (1) 
    {
        if (ActualChar(MermaidState) == '#' && Peek(MermaidState, 1) == '#') 
        {
            while (ActualChar(MermaidState) != '\n' && ActualChar(MermaidState) != '\0') {
                if (ActualChar(MermaidState) == '\n') 
                {
                    MermaidState -> Line++;
                }
                Next(MermaidState, 1);
            }
        }

        if (ActualChar(MermaidState) == ' ' || ActualChar(MermaidState) == '\n') 
        {
            if (ActualChar(MermaidState) == '\n') 
            {
                MermaidState -> Line++;
            }
            Next(MermaidState, 1);
        } 
        else 
        {
            break;
        } 
    }
}

void Set(LexerState* MermaidState, Usize SetValue) 
{
    if (SetValue >= 0) 
    {
        MermaidState -> Pointer = SetValue;
    }
}

LM_Token* CreateToken(
    LM_TokenType Type,
    Usize Start,
    Usize Length
) 
{
    LM_Token* Buffer = malloc(sizeof(LM_Token));
    Buffer -> Type = Type;
    Buffer -> Start = Start;
    Buffer -> Length = Length;
    return Buffer;
}

LM_Token* ReadSpecial(LexerState* MermaidState) 
{
    LM_TokenType Type = Tk_Illegal;
    Usize Start = MermaidState -> Pointer;
    Usize Length = 1;

    switch (ActualChar(MermaidState)) {
        case '@':
            Type = Tk_Adress;
            break;

        case '(':
            Type = Tk_LeftParenthesis;
            break;
        case ')':
            Type = Tk_RightParenthesis;
            break;
        case '{':
            Type = Tk_LeftKeys;
            break;
        case '}':
            Type = Tk_RightKeys;
            break;
        case '[':
            Type = Tk_LeftBrace;
            break;
        case ']':
            Type = Tk_RightBrace;
            break;

        case '%':
            Type = Tk_Percentage;
            break;
        case '$':
            Type = Tk_Money;
            break;

        case '?':
            Type = Tk_Interrogation;
            break;

        case '*':
            switch (Peek(MermaidState, 1))
            {
                case '*':
                    Type = Tk_DoubleAsterisk;
                    Length = 2;
                    break;

                default:
                    Type = Tk_Asterisk;
                    break;
            }
            break;
        case '<':
            switch (Peek(MermaidState, 1))
            {
                case '<':
                    Type = Tk_LeftDoubleArrow;
                    Length = 2;
                    break;

                case '-':
                    Type = Tk_Push;
                    Length = 2;
                    break;

                default:
                    Type = Tk_LeftArrow;
                    break;
            }
            break;
        case '>':
            switch (Peek(MermaidState, 1))
            {
                case '>':
                    Type = Tk_RightDoubleArrow;
                    Length = 2;
                    break;

                default:
                    Type = Tk_RightArrow;
                    break;
            }
            break;
        case '!':
            Type = Tk_Bang;
            break;
        case '^':
            Type = Tk_UpArrow;
            break;
        case '+':
            switch (Peek(MermaidState, 1))
            {
                case '+':
                    Type = Tk_PlusPLus;
                    Length = 2;
                    break;

                default:
                    Type = Tk_Plus;
                    break;
            }
            break;
        case '-':
            switch (Peek(MermaidState, 1))
            {
                case '-':
                    Type = Tk_MinusMinus;
                    Length = 2;
                    break;

                case '>':
                    Type = Tk_Pop;
                    Length = 2;
                    break;

                default:
                    Type = Tk_Minus;
                    break;
            }
            break;
        case '=':
            switch (Peek(MermaidState, 1))
            {
                case '=':
                    Type = Tk_EqualEqual;
                    Length = 2;
                    break;

                default:
                    Type = Tk_Equal;
                    break;
            }
            break;

        case '/':
            switch (Peek(MermaidState, 1))
            {
                case '/':
                    Type = Tk_Div;
                    Length = 2;
                    break;

                default:
                    Type = Tk_DivDiv;
                    break;
            }
            break;

        case '\\':
            switch (Peek(MermaidState, 1))
            {
                case '\\':
                    Type = Tk_DoubleBackslash;
                    Length = 2;
                    break;

                default:
                    Type = Tk_Backslash;
                    break;
            }
            break;
        case '&':
            switch (Peek(MermaidState, 1))
            {
                case '&':
                    Type = Tk_DoubleCommercial;
                    Length = 2;
                    break;

                default:
                    Type = Tk_Commercial;
                    break;
            }
            break;
        case '|':
            switch (Peek(MermaidState, 1))
            {
                case '|':
                    Type = Tk_DoublePipe;
                    Length = 2;
                    break;

                default:
                    Type = Tk_Pipe;
                    break;
            }
            break;
        case ',':
            Type = Tk_Comma;
            break;
        default:
            Type = Tk_Illegal;
            break;
    }
    return CreateToken(Type, Start, Length);
}

Bool Is(const char* Word, const char* Src) {
    if (strcmp(Word, Src) == 0) 
    {
        return True;
    }
    return False;
}

LM_TokenType Indentify(const char* Word) 
{
    if (Is(Word, RETURN_KEYWORD)) 
    {
        return Tk_Return;
    }
    else if (Is(Word, CONSTANT_KEYWORD)) {
        return Tk_Define;
    }
    else if (Is(Word, WRITE_KEYWORD)) {
        return Tk_Write;
    }
    else if (Is(Word, END_OF_CODE_KEYWORD)) {
        return Tk_EndOfCode;
    }
    else 
    {
        return Tk_Indentifier;
    }
}

LM_Token* ReadIndentifier(LexerState* MermaidState) 
{
    int Length = 0;
    Usize Start = MermaidState -> Pointer;
    while (IsIndentifierChar(MermaidState -> Code -> Chars[Start + Length])) 
    {
        Length++;
    }
    char* Word =  Substring(MermaidState -> Code -> Chars, Start, (Start + Length));
    LM_TokenType Type = Indentify(Word);

    // Temporary
    printf("%s ", Word);

    return CreateToken(Type, Start, Length);
}

LM_Token* ReadString(LexerState* MermaidState)
{
    Next(MermaidState, 1);
    int Length = 0;
    Usize Start = MermaidState -> Pointer;
    while ((MermaidState -> Code -> Chars[Start + Length]) != STRING_MARKER) 
    {
        Length++;
    }
    char* Word =  Substring(MermaidState -> Code -> Chars, Start, (Start + Length));

    // Temporary
    printf("%s ", Word);
    Next(MermaidState, 1);
    return CreateToken(Tk_String, Start, Length);
}

LM_Token* ReadNumerical(LexerState* MermaidState) 
{
    int Length = 0;
    Usize Start = MermaidState -> Pointer;
    Bool Float = False;
    while (IsNumerical(MermaidState -> Code -> Chars[Start + Length]) 
        || MermaidState -> Code -> Chars[Start + Length] == '.'
        || MermaidState -> Code -> Chars[Start + Length] == 'b'
        || MermaidState -> Code -> Chars[Start + Length] == 'x') 
    {
        if (MermaidState -> Code -> Chars[Start + Length] == '.' && Float == False) { Float = True; }
        Length++;
        if (MermaidState -> Code -> Chars[Start + Length] == '.' && Float ==  True) { printf("Error (%d) : Wrong FLOAT!", MermaidState -> Line); abort(); }
    }
    char* Word =  Substring(MermaidState -> Code -> Chars, Start, (Start + Length));

    // Temporary
    printf("%s ", Word);

    return CreateToken(Tk_Integer, Start, Length);
}

LM_Token* ReadRegister(LexerState* MermaidState) 
{
    Next(MermaidState, 1);
    Usize Start = MermaidState -> Pointer;
    int Length = 0;
    while (
        (MermaidState -> Code -> Chars[Start + Length] != ' ' 
        && IsIndentifierChar(MermaidState -> Code -> Chars[Start + Length]))
        && !IsSpace(MermaidState -> Code -> Chars[Start + Length])) 
    {
        Length++;
    }
    char* RegisterName = Substring(MermaidState -> Code -> Chars, Start, (Start + Length));
    
    // Temporary
    printf("%s ", RegisterName);

    return CreateToken(Tk_Register, Start, Length);
}

LM_Token* ReadArchiveMarker(LexerState* MermaidState)
{
    Next(MermaidState, 1);
    int Length = 0;
    Usize Start = MermaidState -> Pointer;
    while ((MermaidState -> Code -> Chars[Start + Length]) != ARCHIVE_MARKER) 
    {
        Length++;
    }
    char* Word =  Substring(MermaidState -> Code -> Chars, Start, (Start + Length));

    return CreateToken(Tk_ArchiveMarker, Start, Length + 1);
    MermaidState -> Line = 1;
}

void Tokenize(LilMermaid_BigGirl* Girl, Vector* Tokens) 
{
    LexerState LocalState;
    LocalState.Char = '_';
    LocalState.Pointer = 0;
    LocalState.Line = 1;

    LocalState.Code = Girl -> SourceCode;
    for (int x = 0; ActualChar(&LocalState) != '\0';x++) {
        Skip(&LocalState);
        Usize Offset = 1;

        LM_Token* LocalToken = NULL;

        if (ActualChar(&LocalState) == ARCHIVE_MARKER) 
        {
            LocalToken = ReadArchiveMarker(&LocalState);
        }

        else if (ActualChar(&LocalState) == REGISTER_MARKER) 
        {
            LocalToken = ReadRegister(&LocalState);
        }
        else if (ActualChar(&LocalState) == STRING_MARKER) 
        {
            LocalToken = ReadString(&LocalState);
        }
        else if (!IsIndentifierChar(ActualChar(&LocalState))) 
        {
            LocalToken = ReadSpecial(&LocalState);
        }
        else if (IsNumerical(ActualChar(&LocalState))) 
        {
            LocalToken = ReadNumerical(&LocalState);
        }
        else if (IsIndentifierChar(ActualChar(&LocalState)))
        {
            LocalToken = ReadIndentifier(&LocalState);
        }
        if (LocalToken != NULL) {
            Offset = LocalToken -> Length;
            Add(Tokens, LocalToken);
        }
        Next(&LocalState, Offset);
    }
}
