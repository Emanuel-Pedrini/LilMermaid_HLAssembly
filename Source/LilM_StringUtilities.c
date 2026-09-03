#include "Headers/StringUtilities.h"
#include "Headers/InterpreterTypes.h"
#include "External/Libraries.h"

char* Substring(char* String, Usize Start, Usize End)
{
    int pretendedSize = (End - Start) + 1;
    if (pretendedSize <= 0) {
        return NULL;
    }
    Usize substringSize = pretendedSize;
    char* temporaryBuffer = malloc(substringSize * sizeof(unsigned char));
    if (temporaryBuffer != NULL) {
        Usize x = Start, y = 0;
        for (; x < End && String[x] != '\0' ; x++, y++) {
            temporaryBuffer[y] = String[x];
        }
        temporaryBuffer[y] = '\0';
        return temporaryBuffer;
    }
    return NULL;
}

Bool EndsWith(char* String, char* Suffix)
{
    Usize preffixSize = strlen(Suffix);
    Usize stringSize = strlen(String);
    if (!(preffixSize > stringSize)) {
        char* stringStart = Substring(String, stringSize - preffixSize, stringSize);
        if (strcmp(stringStart, Suffix) == 0) {
            return True;
        }
        return False;
    }
    return False;
}

Bool StartsWith(char* String, char* Prefix)
{
    Usize preffixSize = strlen(Prefix);
    Usize stringSize = strlen(String);
    if (!(preffixSize > stringSize)) {
        char* stringStart = Substring(String, 0, preffixSize);
        if (strcmp(stringStart, Prefix) == 0) {
            return True;
        }
        return False;
    }
    return False;
}

char* File(char* FullPath) {
    Usize stringSize = strlen(FullPath);
    int x;
    for (x = stringSize; FullPath[x] != '\\' &&  FullPath[x] != '/'; x--) {
    }
    return Substring(FullPath, x + 1, stringSize);
}

Bool IsNumerical(const char Char) 
{
    if (Char >= '0' && Char <= '9') {
        return True;
    }
    return False;
}

Bool IsAlphabetic(const char Char)
{
    if ((Char >= 'a' && Char <= 'z') || (Char >= 'A' && Char <= 'Z')) {
        return True;
    }
    return False;
}

Bool IsAlphaNumerical(const char Char)
{
    if (IsAlphabetic(Char) || IsNumerical(Char))
    {
        return True;
    }
    return False;
}

Bool IsIndentifierChar(const char Char)
{
    if (IsAlphabetic(Char) || IsNumerical(Char) || Char == '_')
    {
        return True;
    }
    return False;
}

String* FromStr(const char* Src) {

    String* Buffer = malloc(sizeof(String));
    if (Buffer == NULL) {
        free(Buffer);
        return NULL;
    }
    Buffer -> Size = strlen(Src);
    Buffer -> Capacity = Buffer -> Size * 2 + 1;
    Buffer -> Chars = malloc(Buffer -> Capacity * sizeof(char));
    if (Buffer -> Chars == NULL) {
        free(Buffer -> Chars);
        return NULL;
    }
    memcpy(
        Buffer -> Chars,
        Src,
        Buffer -> Size  + 1
    );
    return Buffer;
}

void NewStr(String* Str)
{

}
void AddStr(String* Str, const char Char)
{
    if (Str -> Size + 1 >= Str -> Capacity) {
        Usize NewCapacity = Str -> Capacity * 2 + 1;
        char* NewChars = realloc(Str -> Chars, NewCapacity * sizeof(char));
        if (NewChars == NULL) {
            free(NewChars);
            return;
        }
        Str -> Chars = NewChars;
        Str -> Capacity = NewCapacity;
    }
    Str -> Chars[Str -> Size] = Char;
    Str -> Size++;
    Str -> Chars[Str -> Size] = '\0';
}
void AppendStr(String* Str, char* Src)
{
    int Size = strlen(Src);
    for (int x = 0 ; x < Size ; x++) 
    {
        AddStr(Str, Src[x]);
    }
}

String* ConcatStr(String* Str, String* Src) {
    String* TemporaryString = FromStr("");
    for (int x = 0 ; x < Str -> Size; x++) {
        AddStr(TemporaryString, Str -> Chars[x]);
    }
    for (int x = 0 ; x < Src -> Size; x++) {
        AddStr(TemporaryString, Src -> Chars[x]);
    }
    return TemporaryString;
}

Bool IsSpace(const char Char) 
{
    if (Char == ' ' || Char == '\n' || Char == '\t') 
    {
        return True;
    }
    return False;
}