#ifndef TIM_H
#define TIM_H

#define YEAR 31536000
#define MONTH 2592000
#define DAY 86400
#define HOUR 3600
#define MINUTE 60

typedef struct
{
    double *yea;
    double *mon;
    double *day;
    double *hou;
    double *min;
    double *sec;
}t_time;

t_time *time_add              (t_time *t1, t_time *t2);
t_time *time_sub              (t_time *t1, t_time *t2);
t_time *time_create_structure (                      );
double  time_second           (t_time *t             );
   void time_destroy_structure(                      );
   void time_display          (t_time *t             );
   void time_format           (double  x , t_time *t );
t_boolean is_time_null(t_time *t);
void time_wait( double x );

# endif
