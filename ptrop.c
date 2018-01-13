#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "logger.h"
#include "ptrop.h"


/************************************************************************************************************/

void deallocate_1D_c( char *p )
{
    if (p)
    {
        free(p);
        p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_1D_c -> %s\n",strerror(errno));
}

char *allocate_1D_c( unsigned long long int n )
{
    unsigned long long int i;
    char *p = NULL;
    if ((p = (char *)malloc(n*sizeof(char))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_c -> %s\n", strerror(errno));

    return p;
}

void c_1D_value_insert(char **t, unsigned long long int *t_length, unsigned long long int offset, char value)
{
    unsigned long long int i;
    char *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(char))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::c_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_c( char *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("\n-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%c\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_c -> %s\n",strerror(errno));
}

void destroy_1D_c( t_1Dc *s)
{
    if (s)
    {
        if (s->da != NULL )
            deallocate_1D_c(s->da);

        free(s);
    }
    s=NULL;
}

t_1Dc *create_empty_1D_c()
{
    t_1Dc *s = NULL;
    if ( !(s = (t_1Dc*)malloc(sizeof(t_1Dc))) )
        fprintf(logger, "create_da.h::create_empty_1D_c -> %s\n", strerror(errno));

    return s;
}

t_1Dc *create_1D_c( unsigned long long int x )
{
    t_1Dc *s = NULL;
    if ( (s = create_empty_1D_c()) )
    {
        if ((s->da = allocate_1D_c(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_c -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_c -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_c( t_1Dc *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%c\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_c -> %s\n", strerror(errno));
}

void deallocate_2D_c( char **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_c -> %s\n",strerror(errno));
}

char **allocate_2D_c( unsigned long long int x, unsigned long long int y )
{
    char **t = NULL;
    if ( (t = (char**)malloc( x*sizeof(char*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_c(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_c -> %s\n", strerror(errno));
                deallocate_2D_c(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_c -> %s\n", strerror(errno));
    return t;
}

void display_2D_c( char **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%c\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_c -> %s\n",strerror(errno));
}

void destroy_2D_c( t_2Dc *s)
{
    deallocate_2D_c(s->da, s->x); free(s); s=NULL;
}

t_2Dc *create_empty_2D_c()
{
    t_2Dc *s = NULL;
    if ( !(s = (t_2Dc*)malloc(sizeof(t_2Dc))) )
        fprintf(logger, "create_da.h::create_empty_2D_c -> %s\n", strerror(errno));

    return s;
}

t_2Dc *create_2D_c( unsigned long long int x, unsigned long long int y )
{
    t_2Dc *s = NULL;
    if ( (s = create_empty_2D_c()) )
    {
        if ((s->da = allocate_2D_c(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_c -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_c -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_c( t_2Dc *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%c\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_c -> %s\n", strerror(errno));
}

void deallocate_3D_c( char ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_c -> %s\n",strerror(errno));
}

char ***allocate_3D_c( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    char ***t = NULL;
    if ( (t = (char***)malloc( x*sizeof(char**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_c(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_c -> %s\n", strerror(errno));
                deallocate_3D_c(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_c -> %s\n", strerror(errno));
    return t;
}

void display_3D_c( char ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%c\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_c -> %s\n",strerror(errno));
}

void destroy_3D_c( t_3Dc *s)
{
    deallocate_3D_c(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Dc *create_empty_3D_c()
{
    t_3Dc *s = NULL;
    if ( !(s = (t_3Dc*)malloc(sizeof(t_3Dc))) )
        fprintf(logger, "create_da.h::create_empty_3D_c -> %s\n", strerror(errno));

    return s;
}

t_3Dc *create_3D_c( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Dc *s = NULL;
    if ( (s = create_empty_3D_c()) )
    {
        if ((s->da = allocate_3D_c(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_c -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_c -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_c( t_3Dc *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%c\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_c -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_uc( unsigned char *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_uc -> %s\n",strerror(errno));
}

unsigned char *allocate_1D_uc( unsigned long long int n )
{
    unsigned long long int i;
    unsigned char *p = NULL;
    if ((p = (unsigned char *)malloc(n*sizeof(unsigned char))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_uc -> %s\n", strerror(errno));

    return p;
}

void uc_1D_value_insert(unsigned char **t, unsigned long long int *t_length, unsigned long long int offset, unsigned char value)
{
    unsigned long long int i;
    unsigned char *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(unsigned char))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::uc_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_uc( unsigned char *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%d\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_uc -> %s\n",strerror(errno));
}

void destroy_1D_uc( t_1Duc *s)
{
    deallocate_1D_uc(s->da); free(s); s=NULL;
}

t_1Duc *create_empty_1D_uc()
{
    t_1Duc *s = NULL;
    if ( !(s = (t_1Duc*)malloc(sizeof(t_1Duc))) )
        fprintf(logger, "create_da.h::create_empty_1D_uc -> %s\n", strerror(errno));

    return s;
}

t_1Duc *create_1D_uc( unsigned long long int x )
{
    t_1Duc *s = NULL;
    if ( (s = create_empty_1D_uc()) )
    {
        if ((s->da = allocate_1D_uc(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_uc -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_uc -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_uc( t_1Duc *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%d\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_uc -> %s\n", strerror(errno));
}

void deallocate_2D_uc( unsigned char **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_uc -> %s\n",strerror(errno));
}

unsigned char **allocate_2D_uc( unsigned long long int x, unsigned long long int y )
{
    unsigned char **t = NULL;
    if ( (t = (unsigned char**)malloc( x*sizeof(unsigned char*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_uc(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_uc -> %s\n", strerror(errno));
                deallocate_2D_uc(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_uc -> %s\n", strerror(errno));
    return t;
}

void display_2D_uc( unsigned char **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%d\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_uc -> %s\n",strerror(errno));
}

void destroy_2D_uc( t_2Duc *s)
{
    deallocate_2D_uc(s->da, s->x); free(s); s=NULL;
}

t_2Duc *create_empty_2D_uc()
{
    t_2Duc *s = NULL;
    if ( !(s = (t_2Duc*)malloc(sizeof(t_2Duc))) )
        fprintf(logger, "create_da.h::create_empty_2D_uc -> %s\n", strerror(errno));

    return s;
}

t_2Duc *create_2D_uc( unsigned long long int x, unsigned long long int y )
{
    t_2Duc *s = NULL;
    if ( (s = create_empty_2D_uc()) )
    {
        if ((s->da = allocate_2D_uc(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_uc -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_uc -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_uc( t_2Duc *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%d\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_uc -> %s\n", strerror(errno));
}

void deallocate_3D_uc( unsigned char ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_uc -> %s\n",strerror(errno));
}

unsigned char ***allocate_3D_uc( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    unsigned char ***t = NULL;
    if ( (t = (unsigned char***)malloc( x*sizeof(unsigned char**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_uc(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_uc -> %s\n", strerror(errno));
                deallocate_3D_uc(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_uc -> %s\n", strerror(errno));
    return t;
}

void display_3D_uc( unsigned char ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%d\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_uc -> %s\n",strerror(errno));
}

void destroy_3D_uc( t_3Duc *s)
{
    deallocate_3D_uc(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Duc *create_empty_3D_uc()
{
    t_3Duc *s = NULL;
    if ( !(s = (t_3Duc*)malloc(sizeof(t_3Duc))) )
        fprintf(logger, "create_da.h::create_empty_3D_uc -> %s\n", strerror(errno));

    return s;
}

t_3Duc *create_3D_uc( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Duc *s = NULL;
    if ( (s = create_empty_3D_uc()) )
    {
        if ((s->da = allocate_3D_uc(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_uc -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_uc -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_uc( t_3Duc *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%d\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_uc -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_s( short *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_s -> %s\n",strerror(errno));
}

short *allocate_1D_s( unsigned long long int n )
{
    unsigned long long int i;
    short *p = NULL;
    if ((p = (short *)malloc(n*sizeof(short))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_s -> %s\n", strerror(errno));

    return p;
}

void s_1D_value_insert(short **t, unsigned long long int *t_length, unsigned long long int offset, short value)
{
    unsigned long long int i;
    short *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(short))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::s_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_s( short *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%d\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_s -> %s\n",strerror(errno));
}

void destroy_1D_s( t_1Ds *s)
{
    deallocate_1D_s(s->da); free(s); s=NULL;
}

t_1Ds *create_empty_1D_s()
{
    t_1Ds *s = NULL;
    if ( !(s = (t_1Ds*)malloc(sizeof(t_1Ds))) )
        fprintf(logger, "create_da.h::create_empty_1D_s -> %s\n", strerror(errno));

    return s;
}

t_1Ds *create_1D_s( unsigned long long int x )
{
    t_1Ds *s = NULL;
    if ( (s = create_empty_1D_s()) )
    {
        if ((s->da = allocate_1D_s(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_s -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_s -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_s( t_1Ds *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%d\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_s -> %s\n", strerror(errno));
}

void deallocate_2D_s( short **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_s -> %s\n",strerror(errno));
}

short **allocate_2D_s( unsigned long long int x, unsigned long long int y )
{
    short **t = NULL;
    if ( (t = (short**)malloc( x*sizeof(short*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_s(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_s -> %s\n", strerror(errno));
                deallocate_2D_s(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_s -> %s\n", strerror(errno));
    return t;
}

void display_2D_s( short **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%d\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_s -> %s\n",strerror(errno));
}

void destroy_2D_s( t_2Ds *s)
{
    deallocate_2D_s(s->da, s->x); free(s); s=NULL;
}

t_2Ds *create_empty_2D_s()
{
    t_2Ds *s = NULL;
    if ( !(s = (t_2Ds*)malloc(sizeof(t_2Ds))) )
        fprintf(logger, "create_da.h::create_empty_2D_s -> %s\n", strerror(errno));

    return s;
}

t_2Ds *create_2D_s( unsigned long long int x, unsigned long long int y )
{
    t_2Ds *s = NULL;
    if ( (s = create_empty_2D_s()) )
    {
        if ((s->da = allocate_2D_s(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_s -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_s -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_s( t_2Ds *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%d\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_s -> %s\n", strerror(errno));
}

void deallocate_3D_s( short ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_s -> %s\n",strerror(errno));
}

short ***allocate_3D_s( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    short ***t = NULL;
    if ( (t = (short***)malloc( x*sizeof(short**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_s(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_s -> %s\n", strerror(errno));
                deallocate_3D_s(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_s -> %s\n", strerror(errno));
    return t;
}

void display_3D_s( short ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%d\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_s -> %s\n",strerror(errno));
}

void destroy_3D_s( t_3Ds *s)
{
    deallocate_3D_s(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Ds *create_empty_3D_s()
{
    t_3Ds *s = NULL;
    if ( !(s = (t_3Ds*)malloc(sizeof(t_3Ds))) )
        fprintf(logger, "create_da.h::create_empty_3D_s -> %s\n", strerror(errno));

    return s;
}

t_3Ds *create_3D_s( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Ds *s = NULL;
    if ( (s = create_empty_3D_s()) )
    {
        if ((s->da = allocate_3D_s(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_s -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_s -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_s( t_3Ds *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%d\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_s -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_us( unsigned short *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_us -> %s\n",strerror(errno));
}

unsigned short *allocate_1D_us( unsigned long long int n )
{
    unsigned long long int i;
    unsigned short *p = NULL;
    if ((p = (unsigned short *)malloc(n*sizeof(unsigned short))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_us -> %s\n", strerror(errno));

    return p;
}

void us_1D_value_insert(unsigned short **t, unsigned long long int *t_length, unsigned long long int offset, unsigned short value)
{
    unsigned long long int i;
    unsigned short *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(unsigned short))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::us_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_us( unsigned short *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%d\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_us -> %s\n",strerror(errno));
}

void destroy_1D_us( t_1Dus *s)
{
    deallocate_1D_us(s->da); free(s); s=NULL;
}

t_1Dus *create_empty_1D_us()
{
    t_1Dus *s = NULL;
    if ( !(s = (t_1Dus*)malloc(sizeof(t_1Dus))) )
        fprintf(logger, "create_da.h::create_empty_1D_us -> %s\n", strerror(errno));

    return s;
}

t_1Dus *create_1D_us( unsigned long long int x )
{
    t_1Dus *s = NULL;
    if ( (s = create_empty_1D_us()) )
    {
        if ((s->da = allocate_1D_us(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_us -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_us -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_us( t_1Dus *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%d\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_us -> %s\n", strerror(errno));
}

void deallocate_2D_us( unsigned short **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i])/*, p[i]=NULL*/;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_us -> %s\n",strerror(errno));
}

unsigned short **allocate_2D_us( unsigned long long int x, unsigned long long int y )
{
    unsigned short **t = NULL;
    if ( (t = (unsigned short**)malloc( x*sizeof(unsigned short*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_us(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_us -> %s\n", strerror(errno));
                deallocate_2D_us(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_us -> %s\n", strerror(errno));
    return t;
}

void display_2D_us( unsigned short **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%d\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_us -> %s\n",strerror(errno));
}

void destroy_2D_us( t_2Dus *s)
{
    deallocate_2D_us(s->da, s->x); free(s); s=NULL;
}

t_2Dus *create_empty_2D_us()
{
    t_2Dus *s = NULL;
    if ( !(s = (t_2Dus*)malloc(sizeof(t_2Dus))) )
        fprintf(logger, "create_da.h::create_empty_2D_us -> %s\n", strerror(errno));

    return s;
}

t_2Dus *create_2D_us( unsigned long long int x, unsigned long long int y )
{
    t_2Dus *s = NULL;
    if ( (s = create_empty_2D_us()) )
    {
        if ((s->da = allocate_2D_us(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_us -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_us -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_us( t_2Dus *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%d\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_us -> %s\n", strerror(errno));
}

void deallocate_3D_us( unsigned short ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_us -> %s\n",strerror(errno));
}

unsigned short ***allocate_3D_us( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    unsigned short ***t = NULL;
    if ( (t = (unsigned short***)malloc( x*sizeof(unsigned short**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_us(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_us -> %s\n", strerror(errno));
                deallocate_3D_us(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_us -> %s\n", strerror(errno));
    return t;
}

void display_3D_us( unsigned short ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%d\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_us -> %s\n",strerror(errno));
}

void destroy_3D_us( t_3Dus *s)
{
    deallocate_3D_us(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Dus *create_empty_3D_us()
{
    t_3Dus *s = NULL;
    if ( !(s = (t_3Dus*)malloc(sizeof(t_3Dus))) )
        fprintf(logger, "create_da.h::create_empty_3D_us -> %s\n", strerror(errno));

    return s;
}

t_3Dus *create_3D_us( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Dus *s = NULL;
    if ( (s = create_empty_3D_us()) )
    {
        if ((s->da = allocate_3D_us(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_us -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_us -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_us( t_3Dus *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%d\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_us -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_i( int *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_i -> %s\n",strerror(errno));
}

int *allocate_1D_i( unsigned long long int n )
{
    unsigned long long int i;
    int *p = NULL;
    if ((p = (int *)malloc(n*sizeof(int))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_i -> %s\n", strerror(errno));

    return p;
}

void i_1D_value_insert(int **t, unsigned long long int *t_length, unsigned long long int offset, int value)
{
    unsigned long long int i;
    int *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(int))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::i_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_i( int *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%d\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_i -> %s\n",strerror(errno));
}

void destroy_1D_i( t_1Di *s)
{
    deallocate_1D_i(s->da); free(s); s=NULL;
}

t_1Di *create_empty_1D_i()
{
    t_1Di *s = NULL;
    if ( !(s = (t_1Di*)malloc(sizeof(t_1Di))) )
        fprintf(logger, "create_da.h::create_empty_1D_i -> %s\n", strerror(errno));

    return s;
}

t_1Di *create_1D_i( unsigned long long int x )
{
    t_1Di *s = NULL;
    if ( (s = create_empty_1D_i()) )
    {
        if ((s->da = allocate_1D_i(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_i -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_i -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_i( t_1Di *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%d\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_i -> %s\n", strerror(errno));
}

void deallocate_2D_i( int **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_i -> %s\n",strerror(errno));
}

int **allocate_2D_i( unsigned long long int x, unsigned long long int y )
{
    int **t = NULL;
    if ( (t = (int**)malloc( x*sizeof(int*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_i(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_i -> %s\n", strerror(errno));
                deallocate_2D_i(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_i -> %s\n", strerror(errno));
    return t;
}

void display_2D_i( int **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%d\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_i -> %s\n",strerror(errno));
}

void destroy_2D_i( t_2Di *s)
{
    deallocate_2D_i(s->da, s->x); free(s); s=NULL;
}

t_2Di *create_empty_2D_i()
{
    t_2Di *s = NULL;
    if ( !(s = (t_2Di*)malloc(sizeof(t_2Di))) )
        fprintf(logger, "create_da.h::create_empty_2D_i -> %s\n", strerror(errno));

    return s;
}

t_2Di *create_2D_i( unsigned long long int x, unsigned long long int y )
{
    t_2Di *s = NULL;
    if ( (s = create_empty_2D_i()) )
    {
        if ((s->da = allocate_2D_i(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_i -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_i -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_i( t_2Di *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%d\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_i -> %s\n", strerror(errno));
}

void deallocate_3D_i( int ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_i -> %s\n",strerror(errno));
}

int ***allocate_3D_i( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    int ***t = NULL;
    if ( (t = (int***)malloc( x*sizeof(int**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_i(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_i -> %s\n", strerror(errno));
                deallocate_3D_i(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_i -> %s\n", strerror(errno));
    return t;
}

void display_3D_i( int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%d\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_i -> %s\n",strerror(errno));
}

void destroy_3D_i( t_3Di *s)
{
    deallocate_3D_i(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Di *create_empty_3D_i()
{
    t_3Di *s = NULL;
    if ( !(s = (t_3Di*)malloc(sizeof(t_3Di))) )
        fprintf(logger, "create_da.h::create_empty_3D_i -> %s\n", strerror(errno));

    return s;
}

t_3Di *create_3D_i( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Di *s = NULL;
    if ( (s = create_empty_3D_i()) )
    {
        if ((s->da = allocate_3D_i(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_i -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_i -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_i( t_3Di *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%d\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_i -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_ui( unsigned int *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_ui -> %s\n",strerror(errno));
}

unsigned int *allocate_1D_ui( unsigned long long int n )
{
    unsigned long long int i;
    unsigned int *p = NULL;
    if ((p = (unsigned int *)malloc(n*sizeof(unsigned int))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_ui -> %s\n", strerror(errno));

    return p;
}

void ui_1D_value_insert(unsigned int **t, unsigned long long int *t_length, unsigned long long int offset, unsigned int value)
{
    unsigned long long int i;
    unsigned int *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(unsigned int))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::ui_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_ui( unsigned int *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%d\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_ui -> %s\n",strerror(errno));
}

void destroy_1D_ui( t_1Dui *s)
{
    deallocate_1D_ui(s->da); free(s); s=NULL;
}

t_1Dui *create_empty_1D_ui()
{
    t_1Dui *s = NULL;
    if ( !(s = (t_1Dui*)malloc(sizeof(t_1Dui))) )
        fprintf(logger, "create_da.h::create_empty_1D_ui -> %s\n", strerror(errno));

    return s;
}

t_1Dui *create_1D_ui( unsigned long long int x )
{
    t_1Dui *s = NULL;
    if ( (s = create_empty_1D_ui()) )
    {
        if ((s->da = allocate_1D_ui(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_ui -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_ui -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_ui( t_1Dui *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%d\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_ui -> %s\n", strerror(errno));
}

void deallocate_2D_ui( unsigned int **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_ui -> %s\n",strerror(errno));
}

unsigned int **allocate_2D_ui( unsigned long long int x, unsigned long long int y )
{
    unsigned int **t = NULL;
    if ( (t = (unsigned int**)malloc( x*sizeof(unsigned int*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_ui(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_ui -> %s\n", strerror(errno));
                deallocate_2D_ui(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_ui -> %s\n", strerror(errno));
    return t;
}

void display_2D_ui( unsigned int **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%d\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_ui -> %s\n",strerror(errno));
}

void destroy_2D_ui( t_2Dui *s)
{
    deallocate_2D_ui(s->da, s->x); free(s); s=NULL;
}

t_2Dui *create_empty_2D_ui()
{
    t_2Dui *s = NULL;
    if ( !(s = (t_2Dui*)malloc(sizeof(t_2Dui))) )
        fprintf(logger, "create_da.h::create_empty_2D_ui -> %s\n", strerror(errno));

    return s;
}

t_2Dui *create_2D_ui( unsigned long long int x, unsigned long long int y )
{
    t_2Dui *s = NULL;
    if ( (s = create_empty_2D_ui()) )
    {
        if ((s->da = allocate_2D_ui(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_ui -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_ui -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_ui( t_2Dui *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%d\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_ui -> %s\n", strerror(errno));
}

void deallocate_3D_ui( unsigned int ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_ui -> %s\n",strerror(errno));
}

unsigned int ***allocate_3D_ui( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    unsigned int ***t = NULL;
    if ( (t = (unsigned int***)malloc( x*sizeof(unsigned int**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_ui(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_ui -> %s\n", strerror(errno));
                deallocate_3D_ui(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_ui -> %s\n", strerror(errno));
    return t;
}

void display_3D_ui( unsigned int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%d\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_ui -> %s\n",strerror(errno));
}

void destroy_3D_ui( t_3Dui *s)
{
    deallocate_3D_ui(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Dui *create_empty_3D_ui()
{
    t_3Dui *s = NULL;
    if ( !(s = (t_3Dui*)malloc(sizeof(t_3Dui))) )
        fprintf(logger, "create_da.h::create_empty_3D_ui -> %s\n", strerror(errno));

    return s;
}

t_3Dui *create_3D_ui( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Dui *s = NULL;
    if ( (s = create_empty_3D_ui()) )
    {
        if ((s->da = allocate_3D_ui(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_ui -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_ui -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_ui( t_3Dui *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%d\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_ui -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_li( long int *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_li -> %s\n",strerror(errno));
}

long int *allocate_1D_li( unsigned long long int n )
{
    unsigned long long int i;
    long int *p = NULL;
    if ((p = (long int *)malloc(n*sizeof(long int))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_li -> %s\n", strerror(errno));

    return p;
}

void li_1D_value_insert(long int **t, unsigned long long int *t_length, unsigned long long int offset, long int value)
{
    unsigned long long int i;
    long int *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(long int))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::li_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_li( long int *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%ld\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_li -> %s\n",strerror(errno));
}

void destroy_1D_li( t_1Dli *s)
{
    deallocate_1D_li(s->da); free(s); s=NULL;
}

t_1Dli *create_empty_1D_li()
{
    t_1Dli *s = NULL;
    if ( !(s = (t_1Dli*)malloc(sizeof(t_1Dli))) )
        fprintf(logger, "create_da.h::create_empty_1D_li -> %s\n", strerror(errno));

    return s;
}

t_1Dli *create_1D_li( unsigned long long int x )
{
    t_1Dli *s = NULL;
    if ( (s = create_empty_1D_li()) )
    {
        if ((s->da = allocate_1D_li(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_li -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_li -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_li( t_1Dli *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%ld\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_li -> %s\n", strerror(errno));
}

void deallocate_2D_li( long int **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_li -> %s\n",strerror(errno));
}

long int **allocate_2D_li( unsigned long long int x, unsigned long long int y )
{
    long int **t = NULL;
    if ( (t = (long int**)malloc( x*sizeof(long int*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_li(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_li -> %s\n", strerror(errno));
                deallocate_2D_li(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_li -> %s\n", strerror(errno));
    return t;
}

void display_2D_li( long int **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%ld\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_li -> %s\n",strerror(errno));
}

void destroy_2D_li( t_2Dli *s)
{
    deallocate_2D_li(s->da, s->x); free(s); s=NULL;
}

t_2Dli *create_empty_2D_li()
{
    t_2Dli *s = NULL;
    if ( !(s = (t_2Dli*)malloc(sizeof(t_2Dli))) )
        fprintf(logger, "create_da.h::create_empty_2D_li -> %s\n", strerror(errno));

    return s;
}

t_2Dli *create_2D_li( unsigned long long int x, unsigned long long int y )
{
    t_2Dli *s = NULL;
    if ( (s = create_empty_2D_li()) )
    {
        if ((s->da = allocate_2D_li(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_li -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_li -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_li( t_2Dli *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%ld\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_li -> %s\n", strerror(errno));
}

void deallocate_3D_li( long int ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_li -> %s\n",strerror(errno));
}

long int ***allocate_3D_li( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    long int ***t = NULL;
    if ( (t = (long int***)malloc( x*sizeof(long int**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_li(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_li -> %s\n", strerror(errno));
                deallocate_3D_li(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_li -> %s\n", strerror(errno));
    return t;
}

void display_3D_li( long int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%ld\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_li -> %s\n",strerror(errno));
}

void destroy_3D_li( t_3Dli *s)
{
    deallocate_3D_li(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Dli *create_empty_3D_li()
{
    t_3Dli *s = NULL;
    if ( !(s = (t_3Dli*)malloc(sizeof(t_3Dli))) )
        fprintf(logger, "create_da.h::create_empty_3D_li -> %s\n", strerror(errno));

    return s;
}

t_3Dli *create_3D_li( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Dli *s = NULL;
    if ( (s = create_empty_3D_li()) )
    {
        if ((s->da = allocate_3D_li(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_li -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_li -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_li( t_3Dli *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%ld\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_li -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_uli( unsigned long int *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_uli -> %s\n",strerror(errno));
}

unsigned long int *allocate_1D_uli( unsigned long long int n )
{
    unsigned long long int i;
    unsigned long int *p = NULL;
    if ((p = (unsigned long int *)malloc(n*sizeof(unsigned long int))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_uli -> %s\n", strerror(errno));

    return p;
}

void uli_1D_value_insert(unsigned long int **t, unsigned long long int *t_length, unsigned long long int offset, unsigned long int value)
{
    unsigned long long int i;
    unsigned long int *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(unsigned long int))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::uli_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_uli( unsigned long int *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%ld\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_uli -> %s\n",strerror(errno));
}

void destroy_1D_uli( t_1Duli *s)
{
    deallocate_1D_uli(s->da); free(s); s=NULL;
}

t_1Duli *create_empty_1D_uli()
{
    t_1Duli *s = NULL;
    if ( !(s = (t_1Duli*)malloc(sizeof(t_1Duli))) )
        fprintf(logger, "create_da.h::create_empty_1D_uli -> %s\n", strerror(errno));

    return s;
}

t_1Duli *create_1D_uli( unsigned long long int x )
{
    t_1Duli *s = NULL;
    if ( (s = create_empty_1D_uli()) )
    {
        if ((s->da = allocate_1D_uli(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_uli -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_uli -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_uli( t_1Duli *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%ld\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_uli -> %s\n", strerror(errno));
}

void deallocate_2D_uli( unsigned long int **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_uli -> %s\n",strerror(errno));
}

unsigned long int **allocate_2D_uli( unsigned long long int x, unsigned long long int y )
{
    unsigned long int **t = NULL;
    if ( (t = (unsigned long int**)malloc( x*sizeof(unsigned long int*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_uli(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_uli -> %s\n", strerror(errno));
                deallocate_2D_uli(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_uli -> %s\n", strerror(errno));
    return t;
}

void display_2D_uli( unsigned long int **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%ld\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_uli -> %s\n",strerror(errno));
}

void destroy_2D_uli( t_2Duli *s)
{
    deallocate_2D_uli(s->da, s->x); free(s); s=NULL;
}

t_2Duli *create_empty_2D_uli()
{
    t_2Duli *s = NULL;
    if ( !(s = (t_2Duli*)malloc(sizeof(t_2Duli))) )
        fprintf(logger, "create_da.h::create_empty_2D_uli -> %s\n", strerror(errno));

    return s;
}

t_2Duli *create_2D_uli( unsigned long long int x, unsigned long long int y )
{
    t_2Duli *s = NULL;
    if ( (s = create_empty_2D_uli()) )
    {
        if ((s->da = allocate_2D_uli(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_uli -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_uli -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_uli( t_2Duli *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%ld\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_uli -> %s\n", strerror(errno));
}

void deallocate_3D_uli( unsigned long int ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_uli -> %s\n",strerror(errno));
}

unsigned long int ***allocate_3D_uli( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    unsigned long int ***t = NULL;
    if ( (t = (unsigned long int***)malloc( x*sizeof(unsigned long int**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_uli(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_uli -> %s\n", strerror(errno));
                deallocate_3D_uli(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_uli -> %s\n", strerror(errno));
    return t;
}

void display_3D_uli( unsigned long int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%ld\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_uli -> %s\n",strerror(errno));
}

void destroy_3D_uli( t_3Duli *s)
{
    deallocate_3D_uli(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Duli *create_empty_3D_uli()
{
    t_3Duli *s = NULL;
    if ( !(s = (t_3Duli*)malloc(sizeof(t_3Duli))) )
        fprintf(logger, "create_da.h::create_empty_3D_uli -> %s\n", strerror(errno));

    return s;
}

t_3Duli *create_3D_uli( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Duli *s = NULL;
    if ( (s = create_empty_3D_uli()) )
    {
        if ((s->da = allocate_3D_uli(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_uli -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_uli -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_uli( t_3Duli *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%ld\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_uli -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_lli( long long int *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_lli -> %s\n",strerror(errno));
}

long long int *allocate_1D_lli( unsigned long long int n )
{
    unsigned long long int i;
    long long int *p = NULL;
    if ((p = (long long int *)malloc(n*sizeof(long long int))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_lli -> %s\n", strerror(errno));

    return p;
}

void lli_1D_value_insert(long long int **t, unsigned long long int *t_length, unsigned long long int offset, long long int value)
{
    unsigned long long int i;
    long long int *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(long long int))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::lli_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_lli( long long int *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%I64d\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_lli -> %s\n",strerror(errno));
}

void destroy_1D_lli( t_1Dlli *s)
{
    deallocate_1D_lli(s->da); free(s); s=NULL;
}

t_1Dlli *create_empty_1D_lli()
{
    t_1Dlli *s = NULL;
    if ( !(s = (t_1Dlli*)malloc(sizeof(t_1Dlli))) )
        fprintf(logger, "create_da.h::create_empty_1D_lli -> %s\n", strerror(errno));

    return s;
}

t_1Dlli *create_1D_lli( unsigned long long int x )
{
    t_1Dlli *s = NULL;
    if ( (s = create_empty_1D_lli()) )
    {
        if ((s->da = allocate_1D_lli(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_lli -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_lli -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_lli( t_1Dlli *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%I64d\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_lli -> %s\n", strerror(errno));
}

void deallocate_2D_lli( long long int **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_lli -> %s\n",strerror(errno));
}

long long int **allocate_2D_lli( unsigned long long int x, unsigned long long int y )
{
    long long int **t = NULL;
    if ( (t = (long long int**)malloc( x*sizeof(long long int*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_lli(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_lli -> %s\n", strerror(errno));
                deallocate_2D_lli(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_lli -> %s\n", strerror(errno));
    return t;
}

void display_2D_lli( long long int **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%I64d\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_lli -> %s\n",strerror(errno));
}

void destroy_2D_lli( t_2Dlli *s)
{
    deallocate_2D_lli(s->da, s->x); free(s); s=NULL;
}

t_2Dlli *create_empty_2D_lli()
{
    t_2Dlli *s = NULL;
    if ( !(s = (t_2Dlli*)malloc(sizeof(t_2Dlli))) )
        fprintf(logger, "create_da.h::create_empty_2D_lli -> %s\n", strerror(errno));

    return s;
}

t_2Dlli *create_2D_lli( unsigned long long int x, unsigned long long int y )
{
    t_2Dlli *s = NULL;
    if ( (s = create_empty_2D_lli()) )
    {
        if ((s->da = allocate_2D_lli(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_lli -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_lli -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_lli( t_2Dlli *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%I64d\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_lli -> %s\n", strerror(errno));
}

void deallocate_3D_lli( long long int ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_lli -> %s\n",strerror(errno));
}

long long int ***allocate_3D_lli( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    long long int ***t = NULL;
    if ( (t = (long long int***)malloc( x*sizeof(long long int**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_lli(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_lli -> %s\n", strerror(errno));
                deallocate_3D_lli(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_lli -> %s\n", strerror(errno));
    return t;
}

void display_3D_lli( long long int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%I64d\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_lli -> %s\n",strerror(errno));
}

void destroy_3D_lli( t_3Dlli *s)
{
    deallocate_3D_lli(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Dlli *create_empty_3D_lli()
{
    t_3Dlli *s = NULL;
    if ( !(s = (t_3Dlli*)malloc(sizeof(t_3Dlli))) )
        fprintf(logger, "create_da.h::create_empty_3D_lli -> %s\n", strerror(errno));

    return s;
}

t_3Dlli *create_3D_lli( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Dlli *s = NULL;
    if ( (s = create_empty_3D_lli()) )
    {
        if ((s->da = allocate_3D_lli(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_lli -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_lli -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_lli( t_3Dlli *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%I64d\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_lli -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_ulli( unsigned long long int *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_ulli -> %s\n",strerror(errno));
}

unsigned long long int *allocate_1D_ulli( unsigned long long int n )
{
    unsigned long long int i;
    unsigned long long int *p = NULL;
    if ((p = (unsigned long long int *)malloc(n*sizeof(unsigned long long int))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_ulli -> %s\n", strerror(errno));

    return p;
}

void ulli_1D_value_insert(unsigned long long int **t, unsigned long long int *t_length, unsigned long long int offset, unsigned long long int value)
{
    unsigned long long int i;
    unsigned long long int *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(unsigned long long int))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::ulli_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_ulli( unsigned long long int *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%I64u\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_ulli -> %s\n",strerror(errno));
}

void destroy_1D_ulli( t_1Dulli *s)
{
    deallocate_1D_ulli(s->da); free(s); s=NULL;
}

t_1Dulli *create_empty_1D_ulli()
{
    t_1Dulli *s = NULL;
    if ( !(s = (t_1Dulli*)malloc(sizeof(t_1Dulli))) )
        fprintf(logger, "create_da.h::create_empty_1D_ulli -> %s\n", strerror(errno));

    return s;
}

t_1Dulli *create_1D_ulli( unsigned long long int x )
{
    t_1Dulli *s = NULL;
    if ( (s = create_empty_1D_ulli()) )
    {
        if ((s->da = allocate_1D_ulli(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_ulli -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_ulli -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_ulli( t_1Dulli *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%I64u\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_ulli -> %s\n", strerror(errno));
}

void deallocate_2D_ulli( unsigned long long int **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_ulli -> %s\n",strerror(errno));
}

unsigned long long int **allocate_2D_ulli( unsigned long long int x, unsigned long long int y )
{
    unsigned long long int **t = NULL;
    if ( (t = (unsigned long long int**)malloc( x*sizeof(unsigned long long int*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_ulli(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_ulli -> %s\n", strerror(errno));
                deallocate_2D_ulli(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_ulli -> %s\n", strerror(errno));
    return t;
}

void display_2D_ulli( unsigned long long int **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%I64u\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_ulli -> %s\n",strerror(errno));
}

void destroy_2D_ulli( t_2Dulli *s)
{
    deallocate_2D_ulli(s->da, s->x); free(s); s=NULL;
}

t_2Dulli *create_empty_2D_ulli()
{
    t_2Dulli *s = NULL;
    if ( !(s = (t_2Dulli*)malloc(sizeof(t_2Dulli))) )
        fprintf(logger, "create_da.h::create_empty_2D_ulli -> %s\n", strerror(errno));

    return s;
}

t_2Dulli *create_2D_ulli( unsigned long long int x, unsigned long long int y )
{
    t_2Dulli *s = NULL;
    if ( (s = create_empty_2D_ulli()) )
    {
        if ((s->da = allocate_2D_ulli(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_ulli -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_ulli -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_ulli( t_2Dulli *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%I64u\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_ulli -> %s\n", strerror(errno));
}

void deallocate_3D_ulli( unsigned long long int ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_ulli -> %s\n",strerror(errno));
}

unsigned long long int ***allocate_3D_ulli( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    unsigned long long int ***t = NULL;
    if ( (t = (unsigned long long int***)malloc( x*sizeof(unsigned long long int**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_ulli(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_ulli -> %s\n", strerror(errno));
                deallocate_3D_ulli(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_ulli -> %s\n", strerror(errno));
    return t;
}

void display_3D_ulli( unsigned long long int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%I64u\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_ulli -> %s\n",strerror(errno));
}

void destroy_3D_ulli( t_3Dulli *s)
{
    deallocate_3D_ulli(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Dulli *create_empty_3D_ulli()
{
    t_3Dulli *s = NULL;
    if ( !(s = (t_3Dulli*)malloc(sizeof(t_3Dulli))) )
        fprintf(logger, "create_da.h::create_empty_3D_ulli -> %s\n", strerror(errno));

    return s;
}

t_3Dulli *create_3D_ulli( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Dulli *s = NULL;
    if ( (s = create_empty_3D_ulli()) )
    {
        if ((s->da = allocate_3D_ulli(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_ulli -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_ulli -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_ulli( t_3Dulli *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%I64u\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_ulli -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_f( float *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_f -> %s\n",strerror(errno));
}

float *allocate_1D_f( unsigned long long int n )
{
    unsigned long long int i;
    float *p = NULL;
    if ((p = (float *)malloc(n*sizeof(float))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_f -> %s\n", strerror(errno));

    return p;
}

void f_1D_value_insert(float **t, unsigned long long int *t_length, unsigned long long int offset, float value)
{
    unsigned long long int i;
    float *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(float))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::f_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_f( float *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%f\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_f -> %s\n",strerror(errno));
}

void destroy_1D_f( t_1Df *s)
{
    deallocate_1D_f(s->da); free(s); s=NULL;
}

t_1Df *create_empty_1D_f()
{
    t_1Df *s = NULL;
    if ( !(s = (t_1Df*)malloc(sizeof(t_1Df))) )
        fprintf(logger, "create_da.h::create_empty_1D_f -> %s\n", strerror(errno));

    return s;
}

t_1Df *create_1D_f( unsigned long long int x )
{
    t_1Df *s = NULL;
    if ( (s = create_empty_1D_f()) )
    {
        if ((s->da = allocate_1D_f(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_f -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_f -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_f( t_1Df *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%f\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_f -> %s\n", strerror(errno));
}

void deallocate_2D_f( float **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_f -> %s\n",strerror(errno));
}

float **allocate_2D_f( unsigned long long int x, unsigned long long int y )
{
    float **t = NULL;
    if ( (t = (float**)malloc( x*sizeof(float*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_f(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_f -> %s\n", strerror(errno));
                deallocate_2D_f(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_f -> %s\n", strerror(errno));
    return t;
}

void display_2D_f( float **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%f\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_f -> %s\n",strerror(errno));
}

void destroy_2D_f( t_2Df *s)
{
    deallocate_2D_f(s->da, s->x); free(s); s=NULL;
}

t_2Df *create_empty_2D_f()
{
    t_2Df *s = NULL;
    if ( !(s = (t_2Df*)malloc(sizeof(t_2Df))) )
        fprintf(logger, "create_da.h::create_empty_2D_f -> %s\n", strerror(errno));

    return s;
}

t_2Df *create_2D_f( unsigned long long int x, unsigned long long int y )
{
    t_2Df *s = NULL;
    if ( (s = create_empty_2D_f()) )
    {
        if ((s->da = allocate_2D_f(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_f -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_f -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_f( t_2Df *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%f\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_f -> %s\n", strerror(errno));
}

void deallocate_3D_f( float ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_f -> %s\n",strerror(errno));
}

float ***allocate_3D_f( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    float ***t = NULL;
    if ( (t = (float***)malloc( x*sizeof(float**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_f(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_f -> %s\n", strerror(errno));
                deallocate_3D_f(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_f -> %s\n", strerror(errno));
    return t;
}

void display_3D_f( float ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%f\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_f -> %s\n",strerror(errno));
}

void destroy_3D_f( t_3Df *s)
{
    deallocate_3D_f(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Df *create_empty_3D_f()
{
    t_3Df *s = NULL;
    if ( !(s = (t_3Df*)malloc(sizeof(t_3Df))) )
        fprintf(logger, "create_da.h::create_empty_3D_f -> %s\n", strerror(errno));

    return s;
}

t_3Df *create_3D_f( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Df *s = NULL;
    if ( (s = create_empty_3D_f()) )
    {
        if ((s->da = allocate_3D_f(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_f -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_f -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_f( t_3Df *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%f\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_f -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_d( double *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_d -> %s\n",strerror(errno));
}

double *allocate_1D_d( unsigned long long int n )
{
    unsigned long long int i;
    double *p = NULL;
    if ((p = (double *)malloc(n*sizeof(double))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_d -> %s\n", strerror(errno));

    return p;
}

void d_1D_value_insert(double **t, unsigned long long int *t_length, unsigned long long int offset, double value)
{
    unsigned long long int i;
    double *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(double))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::d_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_d( double *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%lf\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_d -> %s\n",strerror(errno));
}

void destroy_1D_d( t_1Dd *s)
{
    deallocate_1D_d(s->da); free(s); s=NULL;
}

t_1Dd *create_empty_1D_d()
{
    t_1Dd *s = NULL;
    if ( !(s = (t_1Dd*)malloc(sizeof(t_1Dd))) )
        fprintf(logger, "create_da.h::create_empty_1D_d -> %s\n", strerror(errno));

    return s;
}

t_1Dd *create_1D_d( unsigned long long int x )
{
    t_1Dd *s = NULL;
    if ( (s = create_empty_1D_d()) )
    {
        if ((s->da = allocate_1D_d(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_d -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_d -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_d( t_1Dd *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%lf\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_d -> %s\n", strerror(errno));
}

void deallocate_2D_d( double **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_d -> %s\n",strerror(errno));
}

double **allocate_2D_d( unsigned long long int x, unsigned long long int y )
{
    double **t = NULL;
    if ( (t = (double**)malloc( x*sizeof(double*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_d(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_d -> %s\n", strerror(errno));
                deallocate_2D_d(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_d -> %s\n", strerror(errno));
    return t;
}

void display_2D_d( double **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%lf\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_d -> %s\n",strerror(errno));
}

void destroy_2D_d( t_2Dd *s)
{
    deallocate_2D_d(s->da, s->x); free(s); s=NULL;
}

t_2Dd *create_empty_2D_d()
{
    t_2Dd *s = NULL;
    if ( !(s = (t_2Dd*)malloc(sizeof(t_2Dd))) )
        fprintf(logger, "create_da.h::create_empty_2D_d -> %s\n", strerror(errno));

    return s;
}

t_2Dd *create_2D_d( unsigned long long int x, unsigned long long int y )
{
    t_2Dd *s = NULL;
    if ( (s = create_empty_2D_d()) )
    {
        if ((s->da = allocate_2D_d(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_d -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_d -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_d( t_2Dd *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%lf\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_d -> %s\n", strerror(errno));
}

void deallocate_3D_d( double ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_d -> %s\n",strerror(errno));
}

double ***allocate_3D_d( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    double ***t = NULL;
    if ( (t = (double***)malloc( x*sizeof(double**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_d(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_d -> %s\n", strerror(errno));
                deallocate_3D_d(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_d -> %s\n", strerror(errno));
    return t;
}

void display_3D_d( double ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%lf\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_d -> %s\n",strerror(errno));
}

void destroy_3D_d( t_3Dd *s)
{
    deallocate_3D_d(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Dd *create_empty_3D_d()
{
    t_3Dd *s = NULL;
    if ( !(s = (t_3Dd*)malloc(sizeof(t_3Dd))) )
        fprintf(logger, "create_da.h::create_empty_3D_d -> %s\n", strerror(errno));

    return s;
}

t_3Dd *create_3D_d( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Dd *s = NULL;
    if ( (s = create_empty_3D_d()) )
    {
        if ((s->da = allocate_3D_d(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_d -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_d -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_d( t_3Dd *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%lf\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_d -> %s\n", strerror(errno));
}



/************************************************************************************************************/

void deallocate_1D_ld( long double *p )
{
    if (p)
        free(p), p=NULL;

    else fprintf(logger,"deallocate.h::deallocate_1D_ld -> %s\n",strerror(errno));
}

long double *allocate_1D_ld( unsigned long long int n )
{
    unsigned long long int i;
    long double *p = NULL;
    if ((p = (long double *)malloc(n*sizeof(long double))))
        for ( i=0 ; i<n ; i++ )
            p[i]=0;

    else fprintf(logger, "allocate.h::allocate_1D_ld -> %s\n", strerror(errno));

    return p;
}

void ld_1D_value_insert(long double **t, unsigned long long int *t_length, unsigned long long int offset, long double value)
{
    unsigned long long int i;
    long double *realloc_test=NULL;
    (*t_length)++;
    if ( (realloc_test = realloc(*t, *t_length*sizeof(long double))) )    {
        *t=realloc_test;
        for(i=*t_length-1 ; i>offset-1 ; i--)
            (*t)[i]=(*t)[i-1];

        (*t)[offset-1]=value;
    }
    else fprintf(logger, "ptrop.h::ld_1D_value_insert -> %s\n", strerror(errno));
}
void display_1D_ld( long double *p, unsigned long long int x, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<x ; i++)
           printf("p[%I64u]=%lf\n", i, p[i]);
   }
   else fprintf(logger,"display_da.h::display_1D_ld -> %s\n",strerror(errno));
}

void destroy_1D_ld( t_1Dld *s)
{
    deallocate_1D_ld(s->da); free(s); s=NULL;
}

t_1Dld *create_empty_1D_ld()
{
    t_1Dld *s = NULL;
    if ( !(s = (t_1Dld*)malloc(sizeof(t_1Dld))) )
        fprintf(logger, "create_da.h::create_empty_1D_ld -> %s\n", strerror(errno));

    return s;
}

t_1Dld *create_1D_ld( unsigned long long int x )
{
    t_1Dld *s = NULL;
    if ( (s = create_empty_1D_ld()) )
    {
        if ((s->da = allocate_1D_ld(x)))
            s->x = x;

        else fprintf(logger, "create_da.h::create_1D_ld -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_1D_ld -> %s\n", strerror(errno));
    return s;
}

void displayda_1D_ld( t_1Dld *s, const char *name)
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i;
       for (i=0 ; i<s->x ; i++)
           printf("da[%I64u]=%lf\n", i, s->da[i]);
   }
   else fprintf(logger, "display_da.h::displayda_1D_ld -> %s\n", strerror(errno));
}

void deallocate_2D_ld( long double **p, unsigned long long int x )
{
    if (p)
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_2D_ld -> %s\n",strerror(errno));
}

long double **allocate_2D_ld( unsigned long long int x, unsigned long long int y )
{
    long double **t = NULL;
    if ( (t = (long double**)malloc( x*sizeof(long double*))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_1D_ld(y) ) )
            {
                fprintf(logger,"allocate.h::allocate_2D_ld -> %s\n", strerror(errno));
                deallocate_2D_ld(t,i-1);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_2D_ld -> %s\n", strerror(errno));
    return t;
}

void display_2D_ld( long double **p, unsigned long long int x, unsigned long long int y, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               printf("p[%I64u][%I64u]=%lf\n", i, j, p[i][j]);
   }
   else fprintf(logger,"display.h_da::display_2D_ld -> %s\n",strerror(errno));
}

void destroy_2D_ld( t_2Dld *s)
{
    deallocate_2D_ld(s->da, s->x); free(s); s=NULL;
}

t_2Dld *create_empty_2D_ld()
{
    t_2Dld *s = NULL;
    if ( !(s = (t_2Dld*)malloc(sizeof(t_2Dld))) )
        fprintf(logger, "create_da.h::create_empty_2D_ld -> %s\n", strerror(errno));

    return s;
}

t_2Dld *create_2D_ld( unsigned long long int x, unsigned long long int y )
{
    t_2Dld *s = NULL;
    if ( (s = create_empty_2D_ld()) )
    {
        if ((s->da = allocate_2D_ld(x,y)))
            s->x = x, s->y = y;

        else fprintf(logger, "create_da.h::create_2D_ld -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_2D_ld -> %s\n", strerror(errno));
    return s;
}

void displayda_2D_ld( t_2Dld *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               printf("da[%I64u][%I64u]=%lf\n", i, j, s->da[i][j]);
   }
   else fprintf(logger, "display_da.h::displayda_2D_ld -> %s\n", strerror(errno));
}

void deallocate_3D_ld( long double ***p, unsigned long long int x, unsigned long long int y )
{
    if (p)
    {
        unsigned long long int i,j;
        for ( i=0 ; i<x ; i++ )
            for ( j=0 ; j<y ; j++ )
                free(p[i][j]), p[i][j]=NULL;

        for ( i=0 ; i<x ; i++ )
            free(p[i]), p[i]=NULL;

        free(p), p=NULL;
    }
    else fprintf(logger,"deallocate.h::deallocate_3D_ld -> %s\n",strerror(errno));
}

long double ***allocate_3D_ld( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    long double ***t = NULL;
    if ( (t = (long double***)malloc( x*sizeof(long double**))) )
    {
        unsigned long long int i;
        for ( i=0 ; i<x ; i++ )
        {
            if ( !( t[i] = allocate_2D_ld(y,z) ) )
            {
                fprintf(logger,"allocate.h::allocate_3D_ld -> %s\n", strerror(errno));
                deallocate_3D_ld(t,i-1,y);
                i=x;
            }
        }
    }
    else fprintf(logger,"allocate.h::allocate_3D_ld -> %s\n", strerror(errno));
    return t;
}

void display_3D_ld( long double ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name)
{
   if(p)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<x ; i++)
           for (j=0 ; j<y ; j++)
               for (k=0 ; k<z ; k++)
                   printf("p[%I64u][%I64u][%I64u]=%lf\n", i, j, k, p[i][j][k]);
   }
   else fprintf(logger,"display_da.h::display_2D_ld -> %s\n",strerror(errno));
}

void destroy_3D_ld( t_3Dld *s)
{
    deallocate_3D_ld(s->da, s->x, s->y); free(s); s=NULL;
}

t_3Dld *create_empty_3D_ld()
{
    t_3Dld *s = NULL;
    if ( !(s = (t_3Dld*)malloc(sizeof(t_3Dld))) )
        fprintf(logger, "create_da.h::create_empty_3D_ld -> %s\n", strerror(errno));

    return s;
}

t_3Dld *create_3D_ld( unsigned long long int x, unsigned long long int y, unsigned long long int z )
{
    t_3Dld *s = NULL;
    if ( (s = create_empty_3D_ld()) )
    {
        if ((s->da = allocate_3D_ld(x,y,z)))
            s->x = x, s->y = y, s->z = z;

        else fprintf(logger, "create_da.h::create_3D_ld -> %s\n", strerror(errno));
    }
    else fprintf(logger, "create_da.h::create_3D_ld -> %s\n", strerror(errno));
    return s;
}

void displayda_3D_ld( t_3Dld *s, const char *name )
{
   if (s)
   {
       printf("-----------------%s-----------------\n", name);
       unsigned long long int i,j,k;
       for (i=0 ; i<s->x ; i++)
           for (j=0 ; j<s->y ; j++)
               for (k=0 ; k<s->z ; k++)
                   printf("da[%I64u][%I64u][%I64u]=%lf\n", i, j, k, s->da[i][j][k]);
   }
   else fprintf(logger, "display_da.h::displayda_3D_ld -> %s\n", strerror(errno));
}

