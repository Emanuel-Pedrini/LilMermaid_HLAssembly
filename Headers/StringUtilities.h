#ifndef _StringUtilitiesH_
#define _StringUtilitiesH_

#include "Headers/InterpreterTypes.h"
Bool EndsWith(char* String, char* Suffix);
Bool StartsWith(char* String, char* Prefix);
char* Substring(char* String, Usize Start, Usize End);
char* File(char* FullPath);
Bool IsNumerical(const char Char);
Bool IsAlphabetic(const char Char);
Bool IsAlphaNumerical(const char Char);
Bool IsIndentifierChar(const char Char);
Bool IsSpace(const char Char);
Bool Is(const char* Word, const char* Src);

typedef struct {
    Usize Size;
    Usize Capacity;
    char* Chars;
} String;
void NewStr(String* Str);
void AddStr(String* Str, const char Char);
void AppendStr(String* Str, char* Src);
String* FromStr(const char* Src);
String* ConcatStr(String* Str, String* Src);

#endif