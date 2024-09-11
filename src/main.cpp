#include <iostream>
#include "include/CApp.h"

int main(int argc, char* argv[])
{
    CApp app;
    if(app.OnExecute() == -1)
    {
        return EXIT_FAILURE;
    }
    return 0;
}