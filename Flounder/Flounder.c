#include "External/Libraries.h"
#include "Flounder/Flounder_Headers/Flounder_StringUtilities.h"
#include "Control/VersionControl.h"

#define SUBDIRECTORY_NAME "src/"
#define TARGET_DIRECTORY_NAME "bin/"

#define INITIALIZE_KEYWORD "init"
#define NEW_KEYWORD "create"
#define HELP_KEYWORD "help"
#define VERSION_KEYWORD "version"
#define DOCUMENTATION_KEYWORD "docs"
#define BUILD_KEYWORD "make"
#define RUN_KEYWORD "go"

#define DEPENDENCIES_NAME "deps.flmk"
#define DEPENDECIES_TEXT "__INFORMATION__\nproject_name \"%s\"\nlil_mermaid_version \"%s\"\n"

#define RED   "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE  "\x1b[34m"
#define RESET "\x1b[0m"

int MakeFile(char* FileName, char* InitialText) 
{
    FILE* File = fopen(FileName, "w");
    if (File == NULL) {
        return 1;
    }
    fprintf(File, "%s", InitialText);
    fclose(File);
    return 0;
}

int SetupFlounder(char* DirectoryName) 
{
    int CheckCreation = 0;
    String* MainDirectoryName = FromStr("");

    if (!Is(DirectoryName, "")) {
        MainDirectoryName = FromStr(DirectoryName);
        CheckCreation = mkdir(MainDirectoryName -> Chars);
        AddStr(MainDirectoryName, '/');
    }
    else {
        MainDirectoryName = FromStr("");
        int CheckCreation = 0;
    }
    
    String* SubPath = FromStr(SUBDIRECTORY_NAME);
    String* SubDirectory = ConcatStr(MainDirectoryName, SubPath);

    String* TargetSubPath = FromStr(TARGET_DIRECTORY_NAME);
    String* TargetSubDirectory = ConcatStr(MainDirectoryName, TargetSubPath);

    String* GitIgnore = FromStr(".gitignore");
    String* GitIgnorePath = ConcatStr(MainDirectoryName, GitIgnore);

    String* Dependecies = FromStr(DEPENDENCIES_NAME);
    String* DependenciesPath = ConcatStr(MainDirectoryName, Dependecies);

    String* MainName = FromStr("main.lm");
    String* MainPath = ConcatStr(SubDirectory, MainName);

    if (CheckCreation == 0) 
    {
        printf(GREEN "Your directory was created sucessfully!" RESET);
        int SubDirectoryCreation = mkdir(SubDirectory -> Chars);
        int TargetDirectoryCreation = mkdir(TargetSubDirectory -> Chars);

        MakeFile(GitIgnorePath -> Chars, "");
        MakeFile(MainPath -> Chars, "@main\n  ret 0");

        int size = snprintf(NULL, 0, DEPENDECIES_TEXT, DirectoryName, LILMERMAID_VERSION);
        char* t = (char*)malloc(size + 1);
        if (t != NULL) 
        {
            snprintf(t, size + 1, DEPENDECIES_TEXT, DirectoryName, LILMERMAID_VERSION);
            MakeFile(DependenciesPath -> Chars, t);
        }

        return 1;
    } 
    else 
    {
        printf(RED "Failed to create the directory!" RESET);
        return 0;
    }
    return 0;
}

void Help() 
{
    printf("'" GREEN "let project_name" RESET "'create a new directory for your project! (with some premade files and folders)" RESET);
}

void Documentation() 
{    
}

void ListFolderFiles(const char* Folder) 
{
    DIR* Directory = opendir(Folder);
    if (!Directory) return;
    struct dirent* entry;
    while ((entry = readdir(Directory)) != NULL) {
        if (EndsWith(entry -> d_name, ".lm")) 
        {
            printf("%s\n", entry -> d_name);
        }
    }
    closedir(Directory);
}

int main(int ArgumentCount, char* ArgumentValue[])
{
    for (int x = 1 ; x < ArgumentCount ; x++) 
    {
        if (Is(ArgumentValue[x], NEW_KEYWORD)) 
        {
            int Next = x + 1;
            if (!(Next >= ArgumentCount)) 
            {
                SetupFlounder(ArgumentValue[Next]);
                return 0;
            }
            return 1;
        }
        else if (Is(ArgumentValue[x], INITIALIZE_KEYWORD)) 
        {
            SetupFlounder("");
            return 0;
        }
        else if (Is(ArgumentValue[x], HELP_KEYWORD))
        {
            Help();
            return 0;
        } 
        
        else if (Is(ArgumentValue[x], VERSION_KEYWORD))
        {
            printf(BLUE "Version <( %s )>\n" RESET, LILMERMAID_VERSION);
            return 0;
        }

        else if (Is(ArgumentValue[x], DOCUMENTATION_KEYWORD))
        {
            Documentation();
            return 0;
        }
        else if (Is(ArgumentValue[x], BUILD_KEYWORD))
        {
            ListFolderFiles("src");
            return 0;
        }
        else {
            printf(RED "Error!\n" GREEN "Hint: " RESET "Hey, i didn't found '%s' command!\nIf you want to know you options maybe you should try 'flounder help'" RESET, ArgumentValue[x]);
        }
    }
    return 0;
}