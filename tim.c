#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <windows.h>
#include <math.h>

#include "ptrop.h"
#include "logger.h"
#include "tim.h"

#define TRUE 1
#define FALSE 0

t_time *time_create_structure()
{
    short alloc_state = 0;
    t_time *t = NULL;

    if ( (t=(t_time*)malloc(sizeof(t_time))) )
    {
        if ( (t->yea = allocate_1D_d(1)) )
        {
            t->yea[0] = 0.;
            if ( (t->mon = allocate_1D_d(1)) )
            {
                t->mon[0] = 0.;
                if ( (t->day = allocate_1D_d(1)) )
                {
                    t->day[0] = 0.;
                    if ( (t->hou = allocate_1D_d(1)) )
                    {
                        t->hou[0] = 0.;
                        if ( (t->min = allocate_1D_d(1)) )
                        {
                            t->min[0] = 0.;
                            if ( (t->sec = allocate_1D_d(1)) )
                            {
                                t->sec[0] = 0.;
                                alloc_state = 1;

                                if (!alloc_state)
                                    deallocate_1D_d(t->sec), t->sec = NULL;
                            }
                            if (!alloc_state)
                                deallocate_1D_d(t->min), t->min = NULL;
                        }
                        if (!alloc_state)
                            deallocate_1D_d(t->hou), t->hou = NULL;
                    }
                    if (!alloc_state)
                        deallocate_1D_d(t->day), t->day = NULL;
                }
                if (!alloc_state)
                    deallocate_1D_d(t->mon), t->mon = NULL;
            }
            if (!alloc_state)
                deallocate_1D_d(t->yea), t->yea = NULL;
        }
        if (!alloc_state)
            free(t), t = NULL;
    }
    else fprintf(logger,"tim.h::time_create_structure -> %s\n", strerror(errno));
    return t;
}

t_boolean is_time_null(t_time *t)
{
    unsigned int is_null=TRUE;
    if(t)
    {
        if(t->yea)
        {
            if(t->mon)
            {
                if(t->day)
                {
                    if(t->hou)
                    {
                        if(t->min)
                        {
                            if(t->sec)
                                is_null=FALSE;
                        }
                    }
                }
            }
        }
    }
    return is_null;
}

void time_destroy_structure(t_time *t)
{
    if (t)
    {
        if (t->yea)
            deallocate_1D_d(t->yea);

        if (t->mon)
            deallocate_1D_d(t->mon);

        if (t->day)
            deallocate_1D_d(t->day);

        if (t->hou)
            deallocate_1D_d(t->hou);

        if (t->min)
            deallocate_1D_d(t->min);

        if (t->sec)
            deallocate_1D_d(t->sec);

        free(t);
    }
    else fprintf(logger,"tim.h::time_destroy_structure -> %s\n", strerror(errno));
}

void time_display(t_time *t)
{
    if (is_time_null(t)==FALSE)
    {
        printf("\n+----------------------+");
        printf("\n|         TIME         |");
        printf("\n+----------------------+");
        printf("\n| %10.0lf year(s)   |",t->yea[0]);
        printf("\n| %10.0lf month(s)  |",t->mon[0]);
        printf("\n| %10.0lf day(s)    |",t->day[0]);
        printf("\n| %10.0lf hour(s)   |",t->hou[0]);
        printf("\n| %10.0lf minute(s) |",t->min[0]);
        printf("\n| %10.0lf second(s) |",t->sec[0]);
        printf("\n+----------------------+\n");
    }
    else fprintf(logger,"tim.h::time_display -> %s\n", strerror(errno));
}

double time_clock_start()
{
    return GetTickCount();
}

double time_clock_stop(double t)
{
    return (GetTickCount()-t);
}

void time_wait( double x )
{
    double t0=GetTickCount();
    while( GetTickCount() - t0 < x*1000 ){}
}

void time_format( double x, t_time *t )
{
    if (is_time_null(t)==FALSE)
    {
        t->yea[0] = floor(  x/YEAR                                                                                           );
        t->mon[0] = floor( (x - (t->yea[0])*YEAR                                                                    )/MONTH  );
        t->day[0] = floor( (x - (t->yea[0])*YEAR - (t->mon[0])*MONTH                                                )/DAY    );
        t->hou[0] = floor( (x - (t->yea[0])*YEAR - (t->mon[0])*MONTH - (t->day[0])*DAY                              )/HOUR   );
        t->min[0] = floor( (x - (t->yea[0])*YEAR - (t->mon[0])*MONTH - (t->day[0])*DAY -(t->hou[0])*HOUR            )/MINUTE );
        t->sec[0] = floor(  x - (t->yea[0])*YEAR - (t->mon[0])*MONTH - (t->day[0])*DAY -(t->hou[0])*HOUR -(t->min[0])*MINUTE );
    }
    else fprintf(logger,"tim.h::time_format -> %s\n", strerror(errno));
}

double time_second( t_time *t)
{
    double r=-1;
    if (!is_time_null(t))
        r=(t->yea[0])*YEAR + (t->mon[0])*MONTH + (t->day[0])*DAY + (t->hou[0])*HOUR + (t->min[0])*MINUTE + t->sec[0];

    else fprintf(logger,"tim.h::time_second -> %s\n", strerror(errno));

    return r;
}

t_time *time_add(t_time *t1, t_time *t2)
{
    t_time *t0 = time_create_structure();
    double s = time_second(t1) + time_second(t2);
    time_format(s,t0);
    return t0;
}

t_time *time_sub(t_time *t1, t_time *t2)
{
    t_time *t0 = time_create_structure();
    double s = time_second(t1) - time_second(t2);
    if ( s<0 )
        time_format(0,t0);

    else time_format(s,t0);
    return t0;
}

