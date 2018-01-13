#ifndef STR_H
#define STR_H

typedef unsigned long long int t_uint64;



t_uint64 str_length(const char *pChar);
t_uint64 str_count_occurrence(const char *pChar, const char c);
t_boolean is_in_list(const char c, const char *pList);
t_boolean is_alpha( const char c );
t_boolean is_numeric( const char c );
t_boolean str_self_char_replace(char *s, const char old, const char new);
t_uint64 str_count_alpha( const char *pChar );
t_uint64 str_count_numeric( const char *pChar );
t_boolean str_is_alpha(const char *pChar);
t_boolean str_is_numeric(const char *pChar);
char *str_char_to_str(const char c);
t_boolean str_to_file(const char *s, const char *path);
char *str_copy(const char *str_in);
t_uint64 str_common( const char *s1_in, const char *s2_in );
char *str_copy_static_array(const char *str_in, t_uint64 sz_in);
char *str_copy_from_to(const char *str_in, t_uint64 i, t_uint64 j);
t_boolean str_replace(char *s1_in, const char *s2_in);
char *str_concat(const char *s1_in, const char *s2_in);
char *str_unicode_to_ansi(char * str_in, t_uint64 sz);
t_boolean str_self_char_replace(char *s, const char old, const char new);

//const char *str_concat_const(const char *s1_in, const char *s2_in);

char *str_concat_multiple(const char **str_tab, t_uint64 x);
t_boolean str_find( const char *str_in, const char *pattern );
char *str_extract(const char *str_in,  char c_start, char c_end);
t_uint64 *str_occurence_get_index(const char *str_in, const char c, t_uint64 *index_sz);
t_2Dc *winpath_decompose(const char *path);
char *str_extract_2(const char *str_in, const char c_start, const char c_end);


/********************************DA**********************************/
//t_1Dc *strda_copy(const char *S);
//void strda_replace(t_1Dc *s, const char *S);
//void strda_replace_tab(t_1Dc *s, const char *S, unsigned long long int S_length);
//t_1Dc *strda_concat(t_1Dc *s1, t_1Dc *s2);

# endif
