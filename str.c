/***********************************************************************************************************************************************************************************************************************************
 * \file str.c
 * \brief Library for handling strings
 * \author dark.anonymous.fr@gmail.com
 * \version 0.1
 * \date 12/04/2016
 **********************************************************************************************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ptrop.h"
#include "logger.h"
#include "file.h"
#include "str.h"

#define TRUE 1
#define FALSE 0

 /** ******************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 str_length(const char *pChar)
 **********************************************************************************************************************************************************************************************************************************
 * \brief Counts the number of characters in the string
 **********************************************************************************************************************************************************************************************************************************
 * \param   pChar[char *] &rarr; A string
 * \return	length[t_uint64] &rarr; The string length
 *
 * \note 'length' does not take into account the '\0' character
 *
 *********************************************************************************************************************************************************************************************************************************/
t_uint64 str_length(const char *pChar)
{
    t_uint64 length = 0;
    if( pChar ) //T0
        while( *pChar != '\0' )
            length++, pChar++;

    else fprintf(logger,"str.h::str_length.T0 -> pChar is NULL");
    return length;
}

 /** ******************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 str_count_occurrence(const char *pChar, const char c)
 **********************************************************************************************************************************************************************************************************************************
 * \brief Counts the number of occurrences of a character in the string
 **********************************************************************************************************************************************************************************************************************************
 * \param    c[const char] &rarr; The character to find in the string
 * \param    pChar[const char*] &rarr; A string
 * \return	 count[t_uint64] &rarr; The character's occurrence number 'c' in the string 'pchar'
 *
 *********************************************************************************************************************************************************************************************************************************/
t_uint64 str_count_occurrence(const char *pChar, const char c)
{
    t_uint64 count = 0;
    if ( pChar ) //T0
    {
        while( *pChar != '\0' )
        {
            if ( *pChar == c )
                count++;

            pChar++;
        }
    }
    else fprintf(logger,"str.h::str_count_occurrence.T0 -> The argument is NULL");
    return count;
}

 /** ******************************************************************************************************************************************************************************************************************************
 * \fn t_boolean is_in_list(const char c, const char *pList)
 **********************************************************************************************************************************************************************************************************************************
 * \brief Tells if yes or not the character is present in the string
 **********************************************************************************************************************************************************************************************************************************
 * \param        c[const char] &rarr; The character to find in the string
 * \param    pList[const char*] &rarr; The list of characters to check
 * \return	status[t_boolean] &rarr; The result of the process
 *
 * \note If status=TRUE &rarr; The character was found in the string
 * \note If status=FALSE &rarr; The character was not found in the string
 *
 * \note The function stops at the first occurrence of the character
 *********************************************************************************************************************************************************************************************************************************/
t_boolean is_in_list(const char c, const char *pList)
{
    t_boolean status=FALSE;
    if ( pList ) //T0
    {
        t_uint64 i;
        for ( i=0 ; i<str_length(pList) ; i++ )
            if ( c == pList[i] )
                status=TRUE, i=str_length(pList);
    }
    else fprintf(logger,"str.h::is_in_list.T0 -> pList is NULL");
    return status;
}

 /** ******************************************************************************************************************************************************************************************************************************
 * \fn t_boolean is_alpha( const char c )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Tells if yes or not a character is alphabetical
 **********************************************************************************************************************************************************************************************************************************
 * \param   c[const char] &rarr; The character to check
 * \return  status[t_boolean] &rarr; The result of the process
 *
 * \note If status=TRUE &rarr; The character is alphabetical
 * \note If status=FALSE &rarr; The character is not alphabetical
 *
 *********************************************************************************************************************************************************************************************************************************/
t_boolean is_alpha( const char c )
{
    t_boolean status = FALSE;
    if ( ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
        status = TRUE;

    return status;
}

 /** ******************************************************************************************************************************************************************************************************************************
 * \fn t_boolean is_numeric( const char c )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Tells if yes or not the character is numerical
 **********************************************************************************************************************************************************************************************************************************
 * \param        c[const char] &rarr; The character to check*
 * \return  status[t_boolean] &rarr; The result of the process
 *
 *********************************************************************************************************************************************************************************************************************************/
t_boolean is_numeric( const char c )
{
    t_boolean status = FALSE;
    if ( '0' <= c && c <= '9')
        return status=TRUE;

    return status;
}

 /** ******************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 str_count_alpha( const char *pChar )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Count the number of alphabetical characters contained in the string
 **********************************************************************************************************************************************************************************************************************************
 * \param     pChar[const char*] &rarr; A string
 * \return    count[t_uint64] &rarr; The number of alphabetical characters contained in the string
 *
 **********************************************************************************************************************************************************************************************************************************/
t_uint64 str_count_alpha( const char *pChar )
{
    t_uint64 count=0;
    if( pChar )
    {
        while ( *pChar != '\0' )
        {
            if ( is_alpha(*pChar) == TRUE )
                count++;

            pChar++;
        }
    }
    else fprintf(logger,"str.h::str_count_alpha -> pChar is NULL");
    return count;
}

 /** ******************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 str_count_numeric( const char *pChar )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Count the number of numerical characters contained in the string
 **********************************************************************************************************************************************************************************************************************************
 * \param     pChar[const char*] &rarr; A string
 * \return    count[t_uint64] &rarr; The number of numerical characters contained in the string
 *
 *********************************************************************************************************************************************************************************************************************************/
t_uint64 str_count_numeric( const char *pChar )
{
    t_uint64 count=0;
    if( pChar )
    {
        while ( *pChar != '\0' )
        {
            if ( is_numeric(*pChar) )
                count++;

            pChar++;
        }
    }
    else fprintf(logger,"str.h::str_count_numeric -> pChar is NULL");
    return count;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn t_boolean str_is_alpha(const char *pChar)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Determines if yes or no the string is strictly alphabetical
 *********************************************************************************************************************************************************************************************************************************
 * \param    const char* pChar &rarr; A string
 * \return   t_boolean status &rarr; The result of the process
 *
 ********************************************************************************************************************************************************************************************************************************/
t_boolean str_is_alpha(const char *pChar)
{
    t_boolean status=FALSE;
    if( pChar )
    {
        status=TRUE;
        while (*pChar != '\0')
        {
            if ( is_alpha(*pChar) == FALSE )
                status=FALSE;

            pChar++;
        }
    }
    else fprintf(logger,"str.h::str_is_alpha -> pChar is NULL");
    return status;
}

 /** *******************************************************************************************************************************************************************************************************************************
 * \fn t_boolean str_is_numeric(const char *pChar)
 **********************************************************************************************************************************************************************************************************************************
 * \brief Determines if yes or no the string is strictly numerical
 **********************************************************************************************************************************************************************************************************************************
 * \param     pChar[const char*] &rarr; A string
 * \return   status[t_boolean] &rarr; The result of the process
 *
 *********************************************************************************************************************************************************************************************************************************/
t_boolean str_is_numeric(const char *pChar)
{
    t_boolean status=FALSE;
    if( pChar )
    {
        status=TRUE;
        while (*pChar != '\0')
        {
            if ( is_numeric(*pChar) == FALSE )
                return FALSE;

            pChar++;
        }
    }
    else fprintf(logger,"str.h::str_is_numeric -> pChar is NULL");
    return status;
}

 /** ******************************************************************************************************************************************************************************************************************************
 * \fn char *str_char_to_str(const char c)
 **********************************************************************************************************************************************************************************************************************************
 * \brief Creates a string which is made of the character itself
 **********************************************************************************************************************************************************************************************************************************
 * \param         c[const char] &rarr; A character
 * \return    pChar[char*] &rarr; The character is now a string
 *
 *********************************************************************************************************************************************************************************************************************************/
char *str_char_to_str(const char c)
{
    char *pChar = NULL;
    if ( (pChar=allocate_1D_c(2)) )
        pChar[0]=c;

    else fprintf(logger,"\nstr.h::str_char_to_str -> allocate_1D_c returned NULL");
    return pChar;
}

 /** ******************************************************************************************************************************************************************************************************************************
 * \fn str_self_char_replace(char *s, const char old, const char new)
 **********************************************************************************************************************************************************************************************************************************
 * \brief Replace a character by another one in a specified string
 **********************************************************************************************************************************************************************************************************************************
 *
 * \param          s[const char*] &rarr; The string to modify
 * \param        old[const char ] &rarr; The character to replace
 * \param        new[const char ] &rarr; The new character
 * \return    status[t_boolean  ] &rarr; Status of the result
 *
 *********************************************************************************************************************************************************************************************************************************/
t_boolean str_self_char_replace(char *s, const char old, const char new)
{
    t_boolean status = FALSE;
    if(s)
    {
        t_uint64 i = 0;
        for ( i=0 ; i<str_length(s) ; i++ )
            if ( s[i] == old )
                s[i] = new;

        status = TRUE;
    }
    else fprintf(logger,"\nstr.h::str_self_char_replace -> s is NULL");
    return status;
}


 /** *****************************************************************************************************************************************************************************************************************************
 * \fn t_boolean str_copy_dyn_to_static(const char *str_dyn, char *str_static, t_uint64 static_sz)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Copy the content of a string into a new one.
 *********************************************************************************************************************************************************************************************************************************
 * \param   str_dyn[const char*] &rarr; The destination string of the copy
 * \param   str_static[char*] &rarr; The source string to copy to into the dynamic array
 * \param   static_sz[t_uint64] &rarr; The length of the static array
 * \return  status[t_boolean] &rarr; The status of the function
 *
 * \note The function will return TRUE if everything was OK else, it will return FALSE.
 * \note If it returns FALSE, check the log file to determine the source of the error.
 *********************************************************************************************************************************************************************************************************************************/
t_boolean str_copy_dyn_to_static(const char *str_dyn, char *str_static, t_uint64 static_sz)
{
    t_boolean status = FALSE;
    if( str_dyn && str_static && static_sz > 0 )
    {
        t_uint64 i = 0;
        t_uint64 dyn_sz = str_length(str_dyn);
        if ( dyn_sz <= static_sz-1 )
        {
            for ( i=0 ; i<dyn_sz ; i++ )
                str_static[i]=str_dyn[i];

            str_static[i]='\0';
            status = TRUE;
        }
        else fprintf(logger,"\nstr.h::str_copy_dyn_to_static --> str_dyn > str_static : %I64u > %I64u", str_dyn, str_static);
    }
    else
    {
        if(!str_dyn)
            fprintf(logger,"\nstr.h::str_copy_dyn_to_static -> str_dyn is NULL");
        if(!str_static)
            fprintf(logger,"\nstr.h::str_copy_dyn_to_static -> str_static is NULL");
        if(static_sz == 0)
            fprintf(logger,"\nstr.h::str_copy_dyn_to_static -> static_sz = 0");
    }
    return status;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn char *str_copy(const char *str_in)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Copy the content of a string into a new one.
 *********************************************************************************************************************************************************************************************************************************
 * \param     str_in[const char*] &rarr;
 * \return    str_out[const char*] &rarr;
 *
 ********************************************************************************************************************************************************************************************************************************/
char *str_copy(const char *str_in)
{
    char *str_out=NULL;
    if( str_in )
    {
        t_uint64 i, sz_in=str_length(str_in);
        if ( (str_out=allocate_1D_c(sz_in+1)) )
            for ( i=0 ; i<sz_in ; i++ )
                str_out[i]=str_in[i];

        else fprintf(logger,"\nstr.h::str_copy --> allocate_1D_c returned NULL");
    }
    else fprintf(logger,"\nstr.h::str_copy -> str_in is NULL");
    return str_out;
}


 /** *****************************************************************************************************************************************************************************************************************************
 * \fn char *str_copy_static_array(const char *str_in, t_uint64 sz_in)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Copy a chosen number of characters from a static array into a dynamic one.
 *********************************************************************************************************************************************************************************************************************************
 * \param     str_in[const char*] &rarr; A pointer the static array
 * \param      sz_in[t_uint64] &rarr; The size of the static array
 * \return   str_out[const char*] &rarr; The static array copied in a dynamic array.
 *
 * \note Bloc A allows to determine the effective size of the static array.
 * \note Indeed, the size of string contained in the static array might be inferior than the initial size of this static array.
 * \note So the static array is supposed to have the '\0' control character. If appropriate the function will probably lead to a SIGSEV signal.
 *********************************************************************************************************************************************************************************************************************************/
char *str_copy_static_array(const char *str_in, t_uint64 sz_in)
{
    char *str_out=NULL;
    if( str_in )
    {
        t_uint64 i;
        for ( i=0 ; i<sz_in ; i++ )   // Bloc A
            if ( str_in[i] == '\0' )  // ******
                sz_in=i;              // Bloc A

        if ( (str_out=allocate_1D_c(sz_in+1)) )
            for ( i=0 ; i<sz_in ; i++ )
                str_out[i]=str_in[i];

        else fprintf(logger,"\nstr.h::str_copy_static_array -> allocate_1D_c returned NULL");
    }
    else fprintf(logger,"\nstr.h::str_copy_static_array -> str_in is NULL");
    return str_out;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 str_common( const char *s1_in, const char *s2_in )
 *********************************************************************************************************************************************************************************************************************************
 * \brief Count the number of commons character between the two strings
 *********************************************************************************************************************************************************************************************************************************
 * \param     s1_in[const char*] &rarr; A string
 * \param     s2_in[const char*] &rarr; A string
 * \return    common[t_uint64] &rarr;  The number of characters in common.
 *
 *********************************************************************************************************************************************************************************************************************************/
t_uint64 str_common( const char *s1_in, const char *s2_in )
{
    t_uint64 common=0;
    if (s1_in && s2_in)
    {
        t_uint64 i, s1_sz, s2_sz;
        s1_sz = str_length(s1_in);
        s2_sz = str_length(s2_in);
        if ( s1_sz <= s2_sz )
            for ( i=0 ; i<s1_sz ; i++ )
            {
                if ( s1_in[i] == s2_in[i] )
                    common++;

                else i=s1_sz;
            }

        else
            for ( i=0 ; i<s2_sz ; i++ )
            {
                if ( s2_in[i] == s1_in[i] )
                    common++;

                else i=s2_sz;
            }
        common--;
    }
    else
    {
        if (!s1_in)
            fprintf(logger,"\nstr.h::str_common -> s1_in is NULL");
        if (!s2_in)
            fprintf(logger,"\nstr.h::str_common -> s2_in is NULL");
    }
    return common;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn char *str_copy_from_to(const char *str_in, t_uint64 i, t_uint64 j)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Copy a chosen number of characters from a string into a new one from/to the specified offsets
 *********************************************************************************************************************************************************************************************************************************
 * \param     str_in[const char*] &rarr; A string
 * \param          i[t_uint64] &rarr; Starting offset
 * \param          j[t_uint64] &rarr; Ending offset
 * \return   str_out[char*] &rarr; A string
 *
 *********************************************************************************************************************************************************************************************************************************/
char *str_copy_from_to(const char *str_in, t_uint64 i, t_uint64 j)
{
    char *str_out = NULL;
    t_uint64 k;
    if (str_in)
    {
        if ( (str_out=allocate_1D_c(j-i+1)) )
            for (k=i ; k<j ; k++)
                 str_out[k-i]=str_in[k];

        else fprintf(logger,"\nstr.h::str_copy_from_to -> str_out is NULL");
    }
    else fprintf(logger,"\nstr.h::str_copy_from_to -> str_in is NULL");
    return str_out;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn t_boolean str_replace(char *s1_in, const char *s2_in)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Replace the content of an existing string by the content of another one
 *********************************************************************************************************************************************************************************************************************************
 * \param      s1_in[char*] &rarr; A string
 * \param      s2_in[const char*] &rarr; A String
 * \return    str_out[char*] &rarr; A String
 *
 *********************************************************************************************************************************************************************************************************************************/
t_boolean str_replace(char *s1_in, const char *s2_in)
{
    t_boolean status = FALSE;
    if (s1_in && s2_in)
    {
        t_uint64 s2_sz = str_length(s2_in);
        s1_in[s2_sz]='\0';
        t_uint64 i;
        for ( i=0 ; i<s2_sz ; i++ )
            s1_in[i]=s2_in[i];

        status = TRUE;
    }
    else
    {
        if (!s1_in)
            fprintf(logger,"\nstr.h::str_replace -> s1_in is NULL");
        if (!s2_in)
            fprintf(logger,"\nstr.h::str_replace -> s2_in is NULL");
    }
    return status;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn t_boolean str_to_file(const char *s, const char *path)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Copy a string into a file
 *********************************************************************************************************************************************************************************************************************************
 * \param      s[const char*] &rarr; The string to copy into a file
 * \param      path[const char*] &rarr; The path to the file
 * \return     status[t_boolean] &rarr; The result of the function
 *
 * \note if status = TRUE, then the string has been successfully copied into the file
 * \note if status = FALSE, then an error occurred.
 *********************************************************************************************************************************************************************************************************************************/
t_boolean str_to_file(const char *s, const char *path)
{
    t_boolean status = FALSE;
    FILE *pFile = NULL;
    if (s) ///T1
    {
       if ( (pFile = file_open(path,"w")) ) ///T2
       {
          t_uint64 i=0;
          for ( i=0 ; i<str_length(s) ; i++ )
            fprintf(pFile, "%c", s[i]);

          fclose(pFile);
          status=TRUE;
       }
       else fprintf(logger,"\nstr.h::str_to_file.T2 --> The openning of the \"%s\" file has failed [ERRNO:%s]", path, strerror(errno));
    }
    else fprintf(logger,"\nstr.h::str_to_file.T1 --> s is NULL");
    return status;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn char *str_concat(const char *s1_in, const char *s2_in);
 *********************************************************************************************************************************************************************************************************************************
 * \brief Concatenate two strings into a new one
 *********************************************************************************************************************************************************************************************************************************
 * \param      s1_in[const char*] &rarr; A string S1
 * \param      s2_in[const char*] &rarr; A string S2
 * \return    str_out[char*] &rarr; A string S=S1+S2
 *
 * \note Concatenates the two strings such as s = concat(s1,s2) = s1+s2
 *********************************************************************************************************************************************************************************************************************************/
char *str_concat(const char *s1_in, const char *s2_in)
{
    char *str_out=NULL;
    if (s1_in && s2_in) //T0
    {
        t_uint64 i=0;
        t_uint64 s1_sz = str_length(s1_in);
        t_uint64 s2_sz = str_length(s2_in);
        t_uint64 str_sz = s1_sz + s2_sz;

        if ( (str_out = allocate_1D_c(str_sz + 1)) ) //T1
        {
            str_out[str_sz]='\0';
            for ( i=0     ; i<s1_sz  ; i++ )
            {
                str_out[i]=s1_in[i];
            }
            for ( i=s1_sz ; i<str_sz ; i++ )
            {
                str_out[i]=s2_in[i-s1_sz];
            }
        }
        else fprintf(logger,"\nstr.h::str_concat.T1 -> allocate_1D_c returned NULL");
    }
    else
    {
        if (!s1_in)
            fprintf(logger,"\nstr.h::str_concat.T0 -> s1 is NULL");
        if (!s2_in)
            fprintf(logger,"\nstr.h::str_concat.T0 -> s2 is NULL");
    }
    return str_out;
}

//const char *str_concat_const(const char *s1_in, const char *s2_in)
//{
//    const char *str_out=NULL;
//    if (s1_in && s2_in)
//    {
//        t_uint64 i;
//        t_uint64 s1_sz = str_length(s1_in);
//        t_uint64 s2_sz = str_length(s2_in);
//        t_uint64 str_sz = s1_sz + s2_sz;
//
//        if ( (str_out = allocate_1D_c(str_sz + 1)) )
//        {
//            str_out[str_sz]='\0';
//            for ( i=0     ; i<s1_sz  ; i++ ) {str_out[i]=s1_in[i]      ;}
//            for ( i=s1_sz ; i<str_sz ; i++ ) {str_out[i]=s2_in[i-s1_sz];}
//        }
//        else fprintf(logger,"\nstr.h::str_concat --> The allocation of str_out failed [ERRNO:%s]",strerror(errno));
//    }
//    else fprintf(logger,"\nstr.h::str_concat --> At least, one of both argument is NULL");
//    return str_out;
//}


 /** *****************************************************************************************************************************************************************************************************************************
 * \fn char *str_concat_multiple(const char **str_array, t_uint64 sz)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Concatenate an array of strings into a single string
 *********************************************************************************************************************************************************************************************************************************
 * \param      str_array[const char**] &rarr; An array of strings
 * \param      sz[t_uint64] &rarr; The size of the array
 * \return    str_out[char*] &rarr; A string which is the concatenation of all the strings contained in the array
 *
 * \note Concatenates all the strings contained in the string array into a unique string
 *********************************************************************************************************************************************************************************************************************************/
char *str_concat_multiple(const char **str_array, t_uint64 sz)
{
    char *str_out = NULL;
    if( str_array ) //T0
    {
        if( (str_out=allocate_1D_c(1)) ) // T1
        {
            t_uint64 i;
            for (i=0 ; i<sz ; i++)
                str_out = str_concat(str_out,str_array[i]);
        }
        else fprintf(logger,"\nstr.h::str_concat_multiple.T1 -> allocate_1D_c returned NULL");
    }
    else fprintf(logger,"\nstr.h::str_concat_multiple.T0 -> str_array is NULL");
    return str_out;
}


//t_boolean str_find( const char *str_in, const char *pattern )
//{
//    if (str_in && pattern)
//    {
//        t_uint64     str_sz=str_length(str_in);
//        t_uint64 pattern_sz=str_length(pattern);
//        t_uint64 current_sz=0;
//        t_uint64 i,j;
//        for (i=0 ; i<pattern_sz ; i++)
//        {
//            for ( j=0 ; j<str_sz ; j++ )
//            {
//                if( str_in[j]==pattern[i] )
//                {
//                    current_sz++; i++;
//                    if ( pattern_sz==str_sz)
//                        return TRUE;
//                }
//
//                else
//                {
//                    if(pattern_sz>=1){j--;}
//                    i=0; pattern_sz=FALSE;
//                }
//            }
//            if(j==str_sz)
//                return FALSE;
//        }
//    }
//    else fprintf(logger,"\nstr.h::str_search --> At least, one of both argument is NULL");
//    return FALSE;
//}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn t_boolean str_find( const char *str_in, const char *pattern );
 *********************************************************************************************************************************************************************************************************************************
 * \brief Tells if yes or not the specified pattern has been find in the string
 *********************************************************************************************************************************************************************************************************************************
 * \param      str_in[const char*] &rarr; A string
 * \param      pattern[const char*] &rarr; A string
 * \return    status[t_boolean] &rarr; A boolean
 *
 * /note str_find return TRUE if it does find the patter in the string
 * /note str_find return FALSE if it does find the patter in the string
 * /note str_find will stop at the first match.
 *
 *********************************************************************************************************************************************************************************************************************************/
t_boolean str_find( const char *s, const char *pattern )
{
    if (s && pattern) //T0
    {
        unsigned long long int pattern_lengh=0;
        unsigned long long int i,j;
        for (i=0 ; i<strlen(pattern) ; i++)
        {
            for ( j=0 ; j<strlen(s) ; j++ )
            {
                if( s[j]==pattern[i] )
                {
                    pattern_lengh++;
                    i++;
                    if ( pattern_lengh==strlen(pattern))
                        return 1;
                }

                else
                {
                    if (pattern_lengh>=1)
                        j--;

                    i=0;
                    pattern_lengh=0;
                }
            }

            if(j==strlen(s))
                return 0;
        }
    }
    else
    {
        if (!s)
            fprintf(logger,"\nstr.h::str_search.T0 -> s is NULL");
        if (!pattern)
            fprintf(logger,"\nstr.h::str_search.T0 -> pattern is NULL");
    }
    return 0;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn char *str_extract(const char *str_in, const char c_start, const char c_end)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Extracts the string contained between the chosen characters
 *********************************************************************************************************************************************************************************************************************************
 * \param      str_in[const char*] &rarr; A string
 * \param      c_start[const char] &rarr; A character
 * \param      c_end:[const char] &rarr; A character
 * \return    str_out[const char*] &rarr; A string beginning by c_start and ending by c_end
 *
 * \note The function will extract the first occurrence only
 *********************************************************************************************************************************************************************************************************************************/
char *str_extract(const char *str_in,  const char c_start, const char c_end)
{
    char *str_out = NULL;
    if (str_in) //T0
    {
        unsigned int flag=10;
        t_uint64 str_out_sz = 0;
        if ( (str_out=allocate_1D_c(1)) ) //T1
        {
            char *realloc_test = NULL;
            while( *str_in != '\0' )
            {
                if ( *str_in==c_start )
                    flag = 1;

                if ( flag==1 && *str_in!=c_start )
                {
                    if( (realloc_test = (char *)realloc(str_out, (str_out_sz+1)*sizeof(char))) ) //T2
                    {
                        str_out=realloc_test;
                        str_out[str_out_sz]=*str_in;
                        str_out_sz++;
                    }
                    else
                    {
                        if ( str_out_sz != 0 )
                            deallocate_1D_c(realloc_test);

                        fprintf(logger, "\nstr.h::str_extract .T2-> realloc returned NULL when str_out_sz=%I64u", str_out_sz );
                    }
                }
                str_in++;
            }
            str_out[str_out_sz-1]='\0';
        }
        else fprintf(logger,"\nstr.h::str_extract.T1 -> allocate_1D_c returned NULL");
    }
    else fprintf(logger,"\nstr.h::str_extract.T0 -> str_in is NULL");
    return str_out;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn char *str_extract_2(const char *str_in, const char c_start, const char c_end)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Extracts the string contained between the chosen characters
 *********************************************************************************************************************************************************************************************************************************
 * \param      str_in[const char*] &rarr; A string
 * \param      c_start[const char] &rarr; A character
 * \param      c_end:[const char] &rarr; A character
 * \return    str_out[const char*] &rarr; A string beginning by c_start and ending by c_end
 *
 * \note The function will extract the first occurrence only
 *********************************************************************************************************************************************************************************************************************************/
char *str_extract_2(const char *str_in, const char c_start, const char c_end)
{
    char *str_out = NULL;
    if(str_in) //T0
    {
        t_uint64 i,j,k;
        t_uint64 index_length[2];
        t_uint64 *index_start = NULL;
        t_uint64 *index_end   = NULL;
        if ( (index_start=str_occurence_get_index(str_in,c_start,&index_length[0])) && (index_end=str_occurence_get_index(str_in,c_end,&index_length[1])) ) //T1
        {
            j=index_start[index_length[0]-1], k=index_end[index_length[1]-1];
            if ( (str_out=allocate_1D_c(k-j+2)) ) //T2
            {
                for (i=j ; i<k ; i++)
                    str_out[i-j]=str_in[i];

                str_out[i]='\0';
            }
            else fprintf(logger, "str.h::str_extract_2.T2 -> allocate_1D_c returned NULL");
            deallocate_1D_ulli(index_start);
            deallocate_1D_ulli(index_end);
        }
        else
        {
            if (!index_start)
                fprintf(logger, "str.h::str_extract_2 -> str_occurence_get_index returned NULL");
            if (!index_end)
                fprintf(logger, "str.h::str_extract_2 -> str_occurence_get_index returned NULL");
        }
    }
    else fprintf(logger, "str.h::str_extract_2 -> str_in is NULL");
    return str_out;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn char *str_unicode_to_ansi(char *str_in, t_uint64 sz)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Converts a unicode string into an ansi string
 *********************************************************************************************************************************************************************************************************************************
 * \param      str_in[const char*] &rarr; A string
 * \param      sz[t_uint64] &rarr; The size of the string
 * \return    str_out[const char*] &rarr; A string
 *
 * \note The function will extract the first occurrence only
 * \note If you retrieve the string from a file, you will need to use this function : file_to_string_avoid_null
 *********************************************************************************************************************************************************************************************************************************/
char *str_unicode_to_ansi(char *str_in, t_uint64 sz)
{
    char *str_out = NULL;
    if ( str_in ) //T0
    {
        t_uint64 i = 0;
        char *t_realloc = NULL;
        t_uint64 f_sz = 0;
        t_boolean status = TRUE;
        for (i=0;i<sz;i++)
        {
            if ( str_in[i] != '\r' && i != 0 && i != 1 && (i%2==0 && i!=0) )
            {
                f_sz++;
                if ((t_realloc=(char *)realloc(str_out, f_sz*sizeof(char))) ) //T1
                   str_out=t_realloc, str_out[f_sz-1]=str_in[i];

                else
                {
                    if( f_sz > 1 )
                        deallocate_1D_c(str_out);

                    fprintf(logger,"file.h::str_unicode_to_ansi.T1 -> realloc returned NULL when f_sz=%I64u\n", f_sz);
                    status=FALSE;
                }
            }
        }

        if (status==TRUE)
        {
            if ( (t_realloc=(char *)realloc(str_out, (f_sz+1)*sizeof(char))) ) //T2
                str_out=t_realloc, str_out[f_sz]='\0';

            else
            {
                deallocate_1D_c(str_out);
                fprintf(logger,"file.h::str_unicode_to_ansi.T2 -> realloc returned NULL when f_sz=%I64u\n", f_sz);
            }
        }
    }
    else fprintf(logger,"file.h::str_unicode_to_ansi.T0 -> str_in is NULL\n");
    return str_out;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 *str_occurence_get_index(const char *str_in, const char c, t_uint64 *index_sz)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Fills an array with all the positions of character you are looking for
 *********************************************************************************************************************************************************************************************************************************
 * \param      str_in[const char*] &rarr; A string
 * \param      c[const char] &rarr; A character
 * \param      index_sz[t_uint64*] &rarr; The size of the array named index
 * \return     index:[t_uint64*] &rarr; The array containing the positions of all the occurrences of the character in the string
 *
 *********************************************************************************************************************************************************************************************************************************/
t_uint64 *str_occurence_get_index(const char *str_in, const char c, t_uint64 *index_sz)
{
    t_uint64 *index=NULL;
    if (str_in && index_sz) //T0
    {
        t_uint64 i;
        *index_sz=0;
        t_uint64 *t_realloc=NULL;
        t_uint64 str_sz = str_length(str_in);
        for (i=0 ; i<=str_sz ; i++)
            if(str_in[i]==c)
            {
                (*index_sz)++;
                if ( ( t_realloc=(t_uint64 *)realloc(index,*index_sz*sizeof(t_uint64)) ) ) //T1
                    index=t_realloc, index[*index_sz-1]=i;

                else
                {
                    if ( *index_sz != 0 )
                        deallocate_1D_ulli(t_realloc);

                    fprintf(logger, "str.h::str_occurence_get_index.T1 -> realloc returned NULL when index_sz=%I64u", *index_sz);
                }
            }
    }
    else
    {
        if (!str_in)
            fprintf(logger,"\nstr.h::str_occurence_get_index.T0 -> str_in is NULL");
        if (index_sz)
            fprintf(logger,"\nstr.h::str_occurence_get_index.T0 -> index_sz is NULL");
    }
    return index;
}

 /** *****************************************************************************************************************************************************************************************************************************
 * \fn t_2Dc *winpath_decompose(const char *path)
 *********************************************************************************************************************************************************************************************************************************
 * \brief Extracts each string contained between each backslash
 *********************************************************************************************************************************************************************************************************************************
 * \param      path[const char*] &rarr; A String
 * \return     path[t_2Dc*] &rarr; An array of strings containing all the members of a Windows path.
 *
 *********************************************************************************************************************************************************************************************************************************/
t_2Dc *winpath_decompose(const char *path)
{
    t_uint64 i,j;
    t_uint64 backslash_length=0;
    t_uint64 *backslash=str_occurence_get_index(path,'\\',&backslash_length);                  /* Chercher dans le chemin à decomposer, les position de chaque '\' */
    ulli_1D_value_insert(&backslash, &backslash_length, 1, 0);                                 /* Ajouter la valeur 0 au début du tableau des occurences de '\', pour commencer la boucle d'extraction à la racine du chemin */
    ulli_1D_value_insert(&backslash, &backslash_length, backslash_length+1, str_length(path)); /* Ajouter la valeur équivalente à la longueur de la chaine à la fin du tableau des occurrences de '\' pour ne pas oublier d'extraire la dernière partie */
    t_2Dc *path_index = create_2D_c(backslash_length-1,255);                                   /* Créer un tableau à deux dimensions pour stocker chaque membre du chemin */
    for(i=0 ; i<backslash_length-1 ; i++)                                                      /* Pour chaque occurrence de '\', extraire le membre du chemin */
    {
        char *path_element=allocate_1D_c(backslash[i+1]-backslash[i]+1);                       /* Chaine allouée pour sotcker le membre courant à extraire */
        for(j=backslash[i] ; j<backslash[i+1] ; j++)
            path_element[j-backslash[i]]=path[j];                                              /* Copie du membre courant dans la chaine initialement prévue à cet effet */

        path_element[j-backslash[i]]='\0';
        str_replace(path_index->da[i],path_element);                                           /* Copier le membre extrait dans la structure */
        deallocate_1D_c(path_element);
    }
    return path_index;
}

