#ifdef command_language_h
#define command_language_h

#include <stdlib.h>
#include <stdio.h>

extern int g_iScriptSize;
extern int g_iCurrScriptLine;
extern int g_iCurrentLineChar;
extern char ** g_pptrScript;

void LoadScript(char * pstrFilename);
void GetCommand(char * pstrCommand);
void GetStringParam(char * pstrDestString);
void UnloadScript();

int GetIntParam();

#endif
