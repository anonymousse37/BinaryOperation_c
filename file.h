#ifndef FILE_H
#define FILE_H

typedef unsigned long long int t_uint64;
typedef unsigned short t_boolean;

typedef struct
{
    FILE *pFile;
    char *path;
    char *content;
    t_uint64 sz;
}t_file;

typedef struct
{
    char *unit;
    double coeff;
}t_file_unit;

t_file *file_create(const char *path);
void file_destroy(t_file *pFile);
void file_close(FILE *pFile);
FILE *file_open(const char *path, const char *rights);
t_boolean file_exist(const char *path);
t_uint64 file_count_line(const char *path);
t_uint64 file_length( const char *path );
t_uint64 file_length_1( const char *path );
t_uint64 file_length_2( const char *path );
void file_unit_destroy(t_file_unit *file_unit);
t_file_unit *file_unit_create_empty();
t_file_unit *file_unit_create(const char *unit, double coeff);
t_file_unit *file_copy_get_size_unit(const char *src);
void file_copy_get_stats(const char *src, const char *dst, double t0, t_file_unit *file_unit, t_uint64 total_written_byte, t_uint64 f_src_size);
short file_copy(const char *src, const char *dst);
t_uint64 file_size( const char *path );
char *file_to_string( const char *path );
char *file_to_string_avoid_null( const char *path, t_uint64 *f_sz );
char *file_to_string_1( const char *path, t_uint64 *f_sz );
char *file_to_string_2( const char *path );
char *file_to_string_21( const char *path );
t_uint64 file_count_occurrence( const char *path, char c );
t_boolean file_self_char_replace(const char *path, const char old, const char new);

# endif
