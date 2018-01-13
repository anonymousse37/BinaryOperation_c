#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <dirent.h>
#include <direct.h>

#include "ptrop.h"
#include "file.h"
#include "logger.h"
#include "str.h"
#include "tim.h"
#include "bin.h"
#include "dir.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[], char* env[])
{
    system("title Library");
    system("mode con cols=150 lines=75");
    if (logger_on()==TRUE)
    {
        bin_example();
        logger_off();
        logger_read();
    }
    else printf("\n Could not initialize the logging file");
    return 0;
}




