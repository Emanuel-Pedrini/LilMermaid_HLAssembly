#ifndef _ArchiveManagerH_
#define _ArchiveManagerH_

#include "Headers/ArrayUtilities.h"
#include "Headers/CodeObject.h"

char* OpenFileNWindows(char* ArchivePath, Usize Capacity);
LilMermaid_CodeObject* OpenMermaidFile(char* ArchivePath);

#endif