
#ifndef MY_DIRENT_H
#define MY_DIRENT_H

unsigned short dir_create(const char *dir_path);


unsigned short dir_close(DIR *pDir);


DIR *dir_open(const char * dir_path);
t_boolean is_dir(const char *dir_path);
t_2Dc *dir_read(const char *dir_path);
char *entity_get_path(const char *dir_path, const char *eName);
t_boolean dir_browse(const char *dir_path);
t_boolean dir_browse_recursive(DIR *pDir, const char *dir_path);
t_boolean dir_remove(const char *dir_path);
t_boolean dir_remove_recursive(DIR *pDir, const char *dir_path);
char *dir_search(const char *dir_path, const char *eName);
void dir_search_recursive(DIR *pDir, const char *dir_path, const char *eName,char **search_result);
void dir_count(char *dir_path, unsigned long long int *dir_count, unsigned long long int *file_count);
void dir_count_recursive(DIR *pDir, const char *dir_path, unsigned long long int *dir_count, unsigned long long int *file_count);
unsigned long long int dir_size(const char *dir_path);
void dir_size_recursive(DIR *pDir, const char *dir_path, unsigned long long int *dir_size);
void dir_copy(const char *dir_src_path, const char *dir_dst_path);
void dir_copy_recursive(DIR *pDir, const char *dir_src_path, const char *dir_dst_path, const char *current_dir_src_path, const char *current_dir_dst_path);

# endif
