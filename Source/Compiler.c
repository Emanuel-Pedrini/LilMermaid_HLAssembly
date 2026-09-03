#include "Headers/CodeObject.h"
#include "External/Libraries.h"
int FileWrite(char* Path, char* Content) 
{
    FILE* File = fopen(Path, "w");
    if (File == NULL) {
        free(File);
        return 1;
    }
    fprintf(File, Content);
    fclose(File);
    return 0;
}

int BinaryWrite(char* Path, unsigned int Content)
{
    FILE* File = fopen(Path, "w");
    if (File == NULL) {
        free(File);
        return 1;
    }
    fwrite(&Content, sizeof(unsigned int), 1, File);
    fclose(File);
    return 0;   
}