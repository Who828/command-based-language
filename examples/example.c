#include "../include/command_language.h"

int main()
{
    LoadScript("./example.script");
    RunScript();
    UnloadScript();
    return 0;
}
