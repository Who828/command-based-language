#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <ctype.h>
#include "../include/dbg.h"
#include "../include/command_language.h"

#define MAX_SOURCE_LINE_SIZE 4096
#define MAX_COMMAD_SIZE 64
#define MAX_PARAM_SIZE 1024
#define COMMAND_PRINTSTRING "PRINTSTRING"
#define COMMAND_PRINTSTRINGLOOP "PRINTSTRINGLOOP"
#define COMMAND_NEWLINE "NEWLINE"

int g_iScriptSize = 0;
char ** g_pptrScript;
int g_iCurrScriptLine;
int g_iCurrentLineChar;

void LoadScript(char * pstrFilename)
{
    FILE * pScriptFile;

    check(pScriptFile = fopen(pstrFilename, "rb"), "File I/O error");

    while (!feof(pScriptFile))
        if (fgetc(pScriptFile) == '\n')
            ++g_iScriptSize;
    ++g_iScriptSize;

    fclose(pScriptFile);
    check(pScriptFile = fopen(pstrFilename, "r"), "File I/O error");

    g_pptrScript = (char **) malloc(g_iScriptSize * sizeof(char *));

    for (int i=0; i < g_iScriptSize; i++)
    {
        g_pptrScript[i] = (char *) malloc (MAX_SOURCE_LINE_SIZE+1);
        fgets(g_pptrScript[i], MAX_SOURCE_LINE_SIZE, pScriptFile);
    }

    fclose(pScriptFile);

    return;
error:
    exit(0);
}

void UnloadScript()
{
    if (!g_pptrScript)
        return;
    for (int i=0; i < g_iScriptSize; i++)
        free(g_pptrScript[i]);
    
    free(g_pptrScript);
}

void GetCommand(char * pstrDestString)
{
    int iCommandSize = 0;

    char cCurrChar;

    while (g_iCurrentLineChar <
            (int) strlen(g_pptrScript[g_iCurrScriptLine]))
    {
        cCurrChar = g_pptrScript[g_iCurrScriptLine][g_iCurrentLineChar];

        if (cCurrChar == ' ' || cCurrChar == '\n')
            break;

        pstrDestString[iCommandSize] = toupper(cCurrChar);
        iCommandSize++;
        g_iCurrentLineChar++;
    }
        g_iCurrentLineChar++;
        pstrDestString[iCommandSize] = '\0';
}

int GetIntParam()
{
    char pstrString[MAX_PARAM_SIZE];
    int iParamSize = 0;

    char cCurrChar;

    while (g_iCurrentLineChar <
            (int) strlen(g_pptrScript[g_iCurrScriptLine]))
    {
        cCurrChar = g_pptrScript[g_iCurrScriptLine][g_iCurrentLineChar];

        if (cCurrChar == ' ' || cCurrChar == '\n')
            break;

        pstrString[iParamSize] = cCurrChar;
        iParamSize++;
        g_iCurrentLineChar++;
    }
        g_iCurrentLineChar++;
        pstrString[iParamSize] = '\0';
        
        int iIntValue = atoi(pstrString);

        return iIntValue;
}

void GetStringParam(char * pstrDestString)
{
    int iParamSize = 0;

    char cCurrChar;

    g_iCurrentLineChar++;

    while (g_iCurrentLineChar <
            (int) strlen(g_pptrScript[g_iCurrScriptLine]))
    {
        cCurrChar = g_pptrScript[g_iCurrScriptLine][g_iCurrentLineChar];

        if (cCurrChar == '"' || cCurrChar == '\n')
            break;

        pstrDestString[iParamSize] = cCurrChar;
        iParamSize++;
        g_iCurrentLineChar++;
    }
        g_iCurrentLineChar+=2;
        pstrDestString[iParamSize] = '\0';
}

void RunScript()
{
    char pstrCommand[MAX_COMMAD_SIZE];
    char pstrStringParam[MAX_PARAM_SIZE];

    for (g_iCurrScriptLine=0; g_iCurrScriptLine < g_iScriptSize; g_iCurrScriptLine++)
    {
        g_iCurrentLineChar = 0;

        GetCommand(pstrCommand);

        if (strcmp(pstrCommand, COMMAND_PRINTSTRING) == 0)
        {
            GetStringParam(pstrStringParam);
            printf("\t%s\n", pstrStringParam);
        }

        else if (strcmp(pstrCommand, COMMAND_PRINTSTRINGLOOP) == 0)
        {
            GetStringParam(pstrStringParam);
            int iLoopCount = GetIntParam();

            for (int i=0; i < iLoopCount; i++)
                printf("\t%d: %s\n", i, pstrStringParam);
        }

        else if (strcmp(pstrCommand, COMMAND_NEWLINE) == 0)
        {
            printf("\n");
        }

        else 
        {
            break;
        }
    }
}

int main()
{
    LoadScript("example.script");
    RunScript();
    UnloadScript();
    return 0;
}
