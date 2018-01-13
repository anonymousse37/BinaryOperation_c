#ifndef PTROP_H
#define PTROP_H



typedef unsigned short t_boolean;

/************************************************************************************************************/

typedef struct
{
    char *da;
    unsigned long long int x;
}t_1Dc;

typedef struct
{
    char **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Dc;

typedef struct
{
    char ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Dc;

void deallocate_1D_c( char *p );
char *allocate_1D_c( unsigned long long int n );
void c_1D_value_insert(char **t, unsigned long long int *t_length, unsigned long long int offset, char value);
void display_1D_c( char *p, unsigned long long int x, const char *name);
void destroy_1D_c( t_1Dc *s);
t_1Dc *create_1D_c( unsigned long long int x );
t_1Dc *create_empty_1D_c();
void displayda_1D_c( t_1Dc *s, const char *name);
void deallocate_2D_c( char **p, unsigned long long int x );
char **allocate_2D_c( unsigned long long int x, unsigned long long int y );
void display_2D_c( char **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_c( t_2Dc *s);
t_2Dc *create_empty_2D_c();
t_2Dc *create_2D_c( unsigned long long int x, unsigned long long int y );
void displayda_2D_c( t_2Dc *s, const char *name );
void deallocate_3D_c( char ***p, unsigned long long int x, unsigned long long int y );
char ***allocate_3D_c( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_c( char ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_c( t_3Dc *s);
t_3Dc *create_empty_3D_c();
t_3Dc *create_3D_c( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_c( t_3Dc *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    unsigned char *da;
    unsigned long long int x;
}t_1Duc;

typedef struct
{
    unsigned char **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Duc;

typedef struct
{
    unsigned char ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Duc;

void deallocate_1D_uc( unsigned char *p );
unsigned char *allocate_1D_uc( unsigned long long int n );
void uc_1D_value_insert(unsigned char **t, unsigned long long int *t_length, unsigned long long int offset, unsigned char value);
void display_1D_uc( unsigned char *p, unsigned long long int x, const char *name);
void destroy_1D_uc( t_1Duc *s);
t_1Duc *create_1D_uc( unsigned long long int x );
t_1Duc *create_empty_1D_uc();
void displayda_1D_uc( t_1Duc *s, const char *name);
void deallocate_2D_uc( unsigned char **p, unsigned long long int x );
unsigned char **allocate_2D_uc( unsigned long long int x, unsigned long long int y );
void display_2D_uc( unsigned char **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_uc( t_2Duc *s);
t_2Duc *create_empty_2D_uc();
t_2Duc *create_2D_uc( unsigned long long int x, unsigned long long int y );
void displayda_2D_uc( t_2Duc *s, const char *name );
void deallocate_3D_uc( unsigned char ***p, unsigned long long int x, unsigned long long int y );
unsigned char ***allocate_3D_uc( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_uc( unsigned char ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_uc( t_3Duc *s);
t_3Duc *create_empty_3D_uc();
t_3Duc *create_3D_uc( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_uc( t_3Duc *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    short *da;
    unsigned long long int x;
}t_1Ds;

typedef struct
{
    short **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Ds;

typedef struct
{
    short ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Ds;

void deallocate_1D_s( short *p );
short *allocate_1D_s( unsigned long long int n );
void s_1D_value_insert(short **t, unsigned long long int *t_length, unsigned long long int offset, short value);
void display_1D_s( short *p, unsigned long long int x, const char *name);
void destroy_1D_s( t_1Ds *s);
t_1Ds *create_1D_s( unsigned long long int x );
t_1Ds *create_empty_1D_s();
void displayda_1D_s( t_1Ds *s, const char *name);
void deallocate_2D_s( short **p, unsigned long long int x );
short **allocate_2D_s( unsigned long long int x, unsigned long long int y );
void display_2D_s( short **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_s( t_2Ds *s);
t_2Ds *create_empty_2D_s();
t_2Ds *create_2D_s( unsigned long long int x, unsigned long long int y );
void displayda_2D_s( t_2Ds *s, const char *name );
void deallocate_3D_s( short ***p, unsigned long long int x, unsigned long long int y );
short ***allocate_3D_s( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_s( short ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_s( t_3Ds *s);
t_3Ds *create_empty_3D_s();
t_3Ds *create_3D_s( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_s( t_3Ds *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    unsigned short *da;
    unsigned long long int x;
}t_1Dus;

typedef struct
{
    unsigned short **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Dus;

typedef struct
{
    unsigned short ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Dus;

void deallocate_1D_us( unsigned short *p );
unsigned short *allocate_1D_us( unsigned long long int n );
void us_1D_value_insert(unsigned short **t, unsigned long long int *t_length, unsigned long long int offset, unsigned short value);
void display_1D_us( unsigned short *p, unsigned long long int x, const char *name);
void destroy_1D_us( t_1Dus *s);
t_1Dus *create_1D_us( unsigned long long int x );
t_1Dus *create_empty_1D_us();
void displayda_1D_us( t_1Dus *s, const char *name);
void deallocate_2D_us( unsigned short **p, unsigned long long int x );
unsigned short **allocate_2D_us( unsigned long long int x, unsigned long long int y );
void display_2D_us( unsigned short **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_us( t_2Dus *s);
t_2Dus *create_empty_2D_us();
t_2Dus *create_2D_us( unsigned long long int x, unsigned long long int y );
void displayda_2D_us( t_2Dus *s, const char *name );
void deallocate_3D_us( unsigned short ***p, unsigned long long int x, unsigned long long int y );
unsigned short ***allocate_3D_us( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_us( unsigned short ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_us( t_3Dus *s);
t_3Dus *create_empty_3D_us();
t_3Dus *create_3D_us( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_us( t_3Dus *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    int *da;
    unsigned long long int x;
}t_1Di;

typedef struct
{
    int **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Di;

typedef struct
{
    int ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Di;

void deallocate_1D_i( int *p );
int *allocate_1D_i( unsigned long long int n );
void i_1D_value_insert(int **t, unsigned long long int *t_length, unsigned long long int offset, int value);
void display_1D_i( int *p, unsigned long long int x, const char *name);
void destroy_1D_i( t_1Di *s);
t_1Di *create_1D_i( unsigned long long int x );
t_1Di *create_empty_1D_i();
void displayda_1D_i( t_1Di *s, const char *name);
void deallocate_2D_i( int **p, unsigned long long int x );
int **allocate_2D_i( unsigned long long int x, unsigned long long int y );
void display_2D_i( int **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_i( t_2Di *s);
t_2Di *create_empty_2D_i();
t_2Di *create_2D_i( unsigned long long int x, unsigned long long int y );
void displayda_2D_i( t_2Di *s, const char *name );
void deallocate_3D_i( int ***p, unsigned long long int x, unsigned long long int y );
int ***allocate_3D_i( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_i( int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_i( t_3Di *s);
t_3Di *create_empty_3D_i();
t_3Di *create_3D_i( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_i( t_3Di *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    unsigned int *da;
    unsigned long long int x;
}t_1Dui;

typedef struct
{
    unsigned int **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Dui;

typedef struct
{
    unsigned int ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Dui;

void deallocate_1D_ui( unsigned int *p );
unsigned int *allocate_1D_ui( unsigned long long int n );
void ui_1D_value_insert(unsigned int **t, unsigned long long int *t_length, unsigned long long int offset, unsigned int value);
void display_1D_ui( unsigned int *p, unsigned long long int x, const char *name);
void destroy_1D_ui( t_1Dui *s);
t_1Dui *create_1D_ui( unsigned long long int x );
t_1Dui *create_empty_1D_ui();
void displayda_1D_ui( t_1Dui *s, const char *name);
void deallocate_2D_ui( unsigned int **p, unsigned long long int x );
unsigned int **allocate_2D_ui( unsigned long long int x, unsigned long long int y );
void display_2D_ui( unsigned int **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_ui( t_2Dui *s);
t_2Dui *create_empty_2D_ui();
t_2Dui *create_2D_ui( unsigned long long int x, unsigned long long int y );
void displayda_2D_ui( t_2Dui *s, const char *name );
void deallocate_3D_ui( unsigned int ***p, unsigned long long int x, unsigned long long int y );
unsigned int ***allocate_3D_ui( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_ui( unsigned int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_ui( t_3Dui *s);
t_3Dui *create_empty_3D_ui();
t_3Dui *create_3D_ui( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_ui( t_3Dui *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    long int *da;
    unsigned long long int x;
}t_1Dli;

typedef struct
{
    long int **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Dli;

typedef struct
{
    long int ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Dli;

void deallocate_1D_li( long int *p );
long int *allocate_1D_li( unsigned long long int n );
void li_1D_value_insert(long int **t, unsigned long long int *t_length, unsigned long long int offset, long int value);
void display_1D_li( long int *p, unsigned long long int x, const char *name);
void destroy_1D_li( t_1Dli *s);
t_1Dli *create_1D_li( unsigned long long int x );
t_1Dli *create_empty_1D_li();
void displayda_1D_li( t_1Dli *s, const char *name);
void deallocate_2D_li( long int **p, unsigned long long int x );
long int **allocate_2D_li( unsigned long long int x, unsigned long long int y );
void display_2D_li( long int **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_li( t_2Dli *s);
t_2Dli *create_empty_2D_li();
t_2Dli *create_2D_li( unsigned long long int x, unsigned long long int y );
void displayda_2D_li( t_2Dli *s, const char *name );
void deallocate_3D_li( long int ***p, unsigned long long int x, unsigned long long int y );
long int ***allocate_3D_li( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_li( long int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_li( t_3Dli *s);
t_3Dli *create_empty_3D_li();
t_3Dli *create_3D_li( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_li( t_3Dli *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    unsigned long int *da;
    unsigned long long int x;
}t_1Duli;

typedef struct
{
    unsigned long int **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Duli;

typedef struct
{
    unsigned long int ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Duli;

void deallocate_1D_uli( unsigned long int *p );
unsigned long int *allocate_1D_uli( unsigned long long int n );
void uli_1D_value_insert(unsigned long int **t, unsigned long long int *t_length, unsigned long long int offset, unsigned long int value);
void display_1D_uli( unsigned long int *p, unsigned long long int x, const char *name);
void destroy_1D_uli( t_1Duli *s);
t_1Duli *create_1D_uli( unsigned long long int x );
t_1Duli *create_empty_1D_uli();
void displayda_1D_uli( t_1Duli *s, const char *name);
void deallocate_2D_uli( unsigned long int **p, unsigned long long int x );
unsigned long int **allocate_2D_uli( unsigned long long int x, unsigned long long int y );
void display_2D_uli( unsigned long int **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_uli( t_2Duli *s);
t_2Duli *create_empty_2D_uli();
t_2Duli *create_2D_uli( unsigned long long int x, unsigned long long int y );
void displayda_2D_uli( t_2Duli *s, const char *name );
void deallocate_3D_uli( unsigned long int ***p, unsigned long long int x, unsigned long long int y );
unsigned long int ***allocate_3D_uli( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_uli( unsigned long int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_uli( t_3Duli *s);
t_3Duli *create_empty_3D_uli();
t_3Duli *create_3D_uli( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_uli( t_3Duli *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    long long int *da;
    unsigned long long int x;
}t_1Dlli;

typedef struct
{
    long long int **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Dlli;

typedef struct
{
    long long int ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Dlli;

void deallocate_1D_lli( long long int *p );
long long int *allocate_1D_lli( unsigned long long int n );
void lli_1D_value_insert(long long int **t, unsigned long long int *t_length, unsigned long long int offset, long long int value);
void display_1D_lli( long long int *p, unsigned long long int x, const char *name);
void destroy_1D_lli( t_1Dlli *s);
t_1Dlli *create_1D_lli( unsigned long long int x );
t_1Dlli *create_empty_1D_lli();
void displayda_1D_lli( t_1Dlli *s, const char *name);
void deallocate_2D_lli( long long int **p, unsigned long long int x );
long long int **allocate_2D_lli( unsigned long long int x, unsigned long long int y );
void display_2D_lli( long long int **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_lli( t_2Dlli *s);
t_2Dlli *create_empty_2D_lli();
t_2Dlli *create_2D_lli( unsigned long long int x, unsigned long long int y );
void displayda_2D_lli( t_2Dlli *s, const char *name );
void deallocate_3D_lli( long long int ***p, unsigned long long int x, unsigned long long int y );
long long int ***allocate_3D_lli( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_lli( long long int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_lli( t_3Dlli *s);
t_3Dlli *create_empty_3D_lli();
t_3Dlli *create_3D_lli( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_lli( t_3Dlli *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    unsigned long long int *da;
    unsigned long long int x;
}t_1Dulli;

typedef struct
{
    unsigned long long int **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Dulli;

typedef struct
{
    unsigned long long int ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Dulli;

void deallocate_1D_ulli( unsigned long long int *p );
unsigned long long int *allocate_1D_ulli( unsigned long long int n );
void ulli_1D_value_insert(unsigned long long int **t, unsigned long long int *t_length, unsigned long long int offset, unsigned long long int value);
void display_1D_ulli( unsigned long long int *p, unsigned long long int x, const char *name);
void destroy_1D_ulli( t_1Dulli *s);
t_1Dulli *create_1D_ulli( unsigned long long int x );
t_1Dulli *create_empty_1D_ulli();
void displayda_1D_ulli( t_1Dulli *s, const char *name);
void deallocate_2D_ulli( unsigned long long int **p, unsigned long long int x );
unsigned long long int **allocate_2D_ulli( unsigned long long int x, unsigned long long int y );
void display_2D_ulli( unsigned long long int **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_ulli( t_2Dulli *s);
t_2Dulli *create_empty_2D_ulli();
t_2Dulli *create_2D_ulli( unsigned long long int x, unsigned long long int y );
void displayda_2D_ulli( t_2Dulli *s, const char *name );
void deallocate_3D_ulli( unsigned long long int ***p, unsigned long long int x, unsigned long long int y );
unsigned long long int ***allocate_3D_ulli( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_ulli( unsigned long long int ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_ulli( t_3Dulli *s);
t_3Dulli *create_empty_3D_ulli();
t_3Dulli *create_3D_ulli( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_ulli( t_3Dulli *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    float *da;
    unsigned long long int x;
}t_1Df;

typedef struct
{
    float **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Df;

typedef struct
{
    float ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Df;

void deallocate_1D_f( float *p );
float *allocate_1D_f( unsigned long long int n );
void f_1D_value_insert(float **t, unsigned long long int *t_length, unsigned long long int offset, float value);
void display_1D_f( float *p, unsigned long long int x, const char *name);
void destroy_1D_f( t_1Df *s);
t_1Df *create_1D_f( unsigned long long int x );
t_1Df *create_empty_1D_f();
void displayda_1D_f( t_1Df *s, const char *name);
void deallocate_2D_f( float **p, unsigned long long int x );
float **allocate_2D_f( unsigned long long int x, unsigned long long int y );
void display_2D_f( float **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_f( t_2Df *s);
t_2Df *create_empty_2D_f();
t_2Df *create_2D_f( unsigned long long int x, unsigned long long int y );
void displayda_2D_f( t_2Df *s, const char *name );
void deallocate_3D_f( float ***p, unsigned long long int x, unsigned long long int y );
float ***allocate_3D_f( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_f( float ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_f( t_3Df *s);
t_3Df *create_empty_3D_f();
t_3Df *create_3D_f( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_f( t_3Df *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    double *da;
    unsigned long long int x;
}t_1Dd;

typedef struct
{
    double **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Dd;

typedef struct
{
    double ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Dd;

void deallocate_1D_d( double *p );
double *allocate_1D_d( unsigned long long int n );
void d_1D_value_insert(double **t, unsigned long long int *t_length, unsigned long long int offset, double value);
void display_1D_d( double *p, unsigned long long int x, const char *name);
void destroy_1D_d( t_1Dd *s);
t_1Dd *create_1D_d( unsigned long long int x );
t_1Dd *create_empty_1D_d();
void displayda_1D_d( t_1Dd *s, const char *name);
void deallocate_2D_d( double **p, unsigned long long int x );
double **allocate_2D_d( unsigned long long int x, unsigned long long int y );
void display_2D_d( double **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_d( t_2Dd *s);
t_2Dd *create_empty_2D_d();
t_2Dd *create_2D_d( unsigned long long int x, unsigned long long int y );
void displayda_2D_d( t_2Dd *s, const char *name );
void deallocate_3D_d( double ***p, unsigned long long int x, unsigned long long int y );
double ***allocate_3D_d( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_d( double ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_d( t_3Dd *s);
t_3Dd *create_empty_3D_d();
t_3Dd *create_3D_d( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_d( t_3Dd *s, const char *name );



/************************************************************************************************************/

typedef struct
{
    long double *da;
    unsigned long long int x;
}t_1Dld;

typedef struct
{
    long double **da;
    unsigned long long int x;
    unsigned long long int y;
}t_2Dld;

typedef struct
{
    long double ***da;
    unsigned long long int x;
    unsigned long long int y;
    unsigned long long int z;
}t_3Dld;

void deallocate_1D_ld( long double *p );
long double *allocate_1D_ld( unsigned long long int n );
void ld_1D_value_insert(long double **t, unsigned long long int *t_length, unsigned long long int offset, long double value);
void display_1D_ld( long double *p, unsigned long long int x, const char *name);
void destroy_1D_ld( t_1Dld *s);
t_1Dld *create_1D_ld( unsigned long long int x );
t_1Dld *create_empty_1D_ld();
void displayda_1D_ld( t_1Dld *s, const char *name);
void deallocate_2D_ld( long double **p, unsigned long long int x );
long double **allocate_2D_ld( unsigned long long int x, unsigned long long int y );
void display_2D_ld( long double **p, unsigned long long int x, unsigned long long int y, const char *name);
void destroy_2D_ld( t_2Dld *s);
t_2Dld *create_empty_2D_ld();
t_2Dld *create_2D_ld( unsigned long long int x, unsigned long long int y );
void displayda_2D_ld( t_2Dld *s, const char *name );
void deallocate_3D_ld( long double ***p, unsigned long long int x, unsigned long long int y );
long double ***allocate_3D_ld( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void display_3D_ld( long double ***p, unsigned long long int x, unsigned long long int y, unsigned long long int z, const char *name);
void destroy_3D_ld( t_3Dld *s);
t_3Dld *create_empty_3D_ld();
t_3Dld *create_3D_ld( unsigned long long int x, unsigned long long int y, unsigned long long int z );
void displayda_3D_ld( t_3Dld *s, const char *name );


#endif

