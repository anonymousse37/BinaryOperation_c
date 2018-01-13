#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "file.h"
#include "ptrop.h"
#include "str.h"
#include "tim.h"
#include "logger.h"

#define TRUE 1
#define FALSE 0


unsigned short logger_on()
{
    unsigned short status = TRUE;
    remove("logger.txt");
    logger = NULL;
    if (!(logger=fopen("logger.txt","w")))
        printf("\n ##ERROR WHILE STARTING THE LOGGING FUNCTION##"), status=FALSE;

    return status;
}

void logger_off()
{
    if(logger)
        fclose(logger), logger = NULL;
}

void logger_read()
{
    char *log = NULL;
    if ( (log=file_to_string("logger.txt")) )
        if ( strcmp(log, "") != 0 )
        {
            printf("\n\n±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±");
            printf("\n±±                                   LOG FILE                                        ±±");
            printf("\n±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±\n");
            printf("---------------------------------------------------------------------------------------\n");
            unsigned long long int i;
            for (i=0;i<str_length(log);i++)
            {
                printf("%c",log[i]);
                if(log[i]=='\n')
                    printf("---------------------------------------------------------------------------------------\n");
            }
            free(log);
            printf("\n±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±\n");
        }
        else remove(".\\logger.txt");
}
