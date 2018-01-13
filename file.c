 /** *********************************************************************************************************************************************************************************************************************************
 * \file file.c
 * \brief Library for handling files
 * \author dark.anonymous.fr@gmail.com
 * \version 0.1
 * \date 12/04/2016
 **********************************************************************************************************************************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "ptrop.h"
#include "file.h"
#include "str.h"
#include "logger.h"

/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_file *file_create(const char *path)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Creates a structure to handle files
 ***********************************************************************************************************************************************************************************************************************************
 * \param     path[const char*] &rarr; Path to the file
 * \return  pFile[t_file *] &rarr; The structure to manage the file
 *
 **********************************************************************************************************************************************************************************************************************************/
t_file *file_create(const char *path)
{
	unsigned int alloc_state = 0;
	t_file *pFile = NULL;
	if(path)
    {
        if ( (pFile = (t_file*)malloc(sizeof(t_file))) )
        {
            if ( (pFile->path = str_copy(path)) )
            {
                if ( (pFile->content = file_to_string(path)) )
                {
                    pFile->sz = file_length(path);
                    alloc_state = 1;
                }
                if(!alloc_state){free(pFile->path), pFile->path=NULL;}
            }
            if(!alloc_state){free(pFile), pFile=NULL;}
        }
        else fprintf(logger,"\nfile.h::file_create --> The allocation of the file structure has failed");
    }
    else fprintf(logger,"\nfile.h::file_create --> path is NULL");
	return pFile;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn void file_destroy(t_file *pFile)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Destroy an allocated t_file structure
 ***********************************************************************************************************************************************************************************************************************************
 * \param     pFile[t_file *] &rarr; The t_file structure to deallocate
 *
 **********************************************************************************************************************************************************************************************************************************/
void file_destroy(t_file *pFile)
{
    if (pFile)
    {
        if (pFile->path)
            deallocate_1D_c(pFile->path);

        if (pFile->content)
            deallocate_1D_c(pFile->content);

        free(pFile), pFile=NULL;
    }
    else fprintf(logger,"\nfile.h::file_destroy --> You are trying to free something which is not allocated");
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn void file_close(FILE *pFile)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Close an open file
 ***********************************************************************************************************************************************************************************************************************************
 * \param     pFile[t_file *] &rarr; The t_file structure of the file to close
 *
 **********************************************************************************************************************************************************************************************************************************/
void file_close(FILE *pFile)
{
    fclose(pFile);
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn FILE *file_open(const char *path, const char *rights)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Open a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param     path[const char*] &rarr; Path to the file
 * \param     rights[const char*] &rarr; File's opening rights
 * \return     pFile[FLIE *] &rarr; Pointer to the file
 *
 **********************************************************************************************************************************************************************************************************************************/
FILE *file_open(const char *path, const char *rights)
{
    FILE *pFile = NULL;
    if( path && rights )
    {
        errno=0;
        if ( ( !(pFile=fopen(path,rights))) )
            if(logger)
                fprintf(logger,"\nfile.h::file_open --> fopen returned NULL. File:\"%s\"  Rights:\"%s\" [ERRNO:%s]", path, rights, strerror(errno));
    }
    else
    {
        if(!path)
            fprintf(logger,"\nfile.h::file_open --> path is NULL");
        if(!rights)
            fprintf(logger,"\nfile.h::file_open --> rights is NULL");
    }
    return pFile;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_boolean file_self_char_replace(const char *path, const char old, const char new)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Replace a character by another one in the specified file
 ***********************************************************************************************************************************************************************************************************************************
 * \param     path[const char*] &rarr; Path to the file
 * \param     old[const char] &rarr; The char to replace
 * \param     new[const char] &rarr; The replacing char
 * \return    status[t_boolean] &rarr; Status of the function after its execution
 *
 **********************************************************************************************************************************************************************************************************************************/
t_boolean file_self_char_replace(const char *path, const char old, const char new)
{
    t_boolean status = FALSE;
    if(path) //T1
    {
        char *s = NULL;
        if ( (s=file_to_string(path)) ) //T2
        {
            t_boolean a = FALSE;
            if ( (a=str_self_char_replace(s, ',', ';')) == TRUE )
            {
                t_boolean b = FALSE;
                if ( (b=str_to_file(s, path)) == TRUE )
                    status = TRUE;
            }
        }
        else fprintf(logger,"\nfile.h.::file_self_char_replace.T2 --> file_to_string returned NULL");
    }
    else fprintf(logger,"\nfile.h.::file_self_char_replace.T1 --> path is NULL");
    return status;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_boolean file_exist(const char *path)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Tells if yes or no, a file already exists
 ***********************************************************************************************************************************************************************************************************************************
 * \param     path[const char*] &rarr; Path to the file
 * \return     t_boolean[const char*] &rarr; Status of the function after its execution
 *
 **********************************************************************************************************************************************************************************************************************************/
t_boolean file_exist(const char *path)
{
    t_boolean status=FALSE;
    if( path )
    {
        FILE *pFile = NULL;
        if ( (pFile = fopen(path,"r")) )
            file_close(pFile), pFile=NULL, status=TRUE;
    }
    else fprintf(logger,"\nfile.h::file_exist --> path is NULL");
    return status;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 file_count_line(const char *path)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Counts the number of lines in a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param     path[const char*] &rarr; Path the file
 * \return     line[t_uint64] &rarr; Total of lines contained in the file
 *
 * \note The function count the number of lines based on the \n character and not \r
 *
 ***********************************************************************************************************************************************************************************************************************************/
t_uint64 file_count_line(const char *path)
{
    t_uint64 line = 0;
    if( path )
    {
        char c;
        FILE *pFile = NULL;
        if ( (pFile = file_open(path,"r")) )
        {
            while( fscanf(pFile,"%c",&c) != EOF )
                if ( c == '\n' )
                    line++;
        }
        else fprintf(logger,"\nfile.h::file_count_line --> file_open returned NULL. File:\"%s\" Rights:\"r\" [ERRNO:%s]", path, strerror(errno));
        file_close(pFile);
    }
    else fprintf(logger,"\nfile.h::file_count_line --> path is NULL");
    return line;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 file_length( const char *path )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Determines the number of characters that contains a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param     path[const char*] &rarr; Path to the file
 * \return     f_struct.st_size[t_uint64] &rarr; Size of the file in octet or Number of chars in the file
 *
 **********************************************************************************************************************************************************************************************************************************/
t_uint64 file_length( const char *path )
{
    struct _stati64 f_struct;
    if( path )
    {
        if ( _stati64(path, &f_struct) != 0)
            fprintf(logger,"\nfile.h::file_length --> The stat function returned a negative value for the %s file [ERRNO:%s]", path, strerror(errno));
    }
    else fprintf(logger,"\nfile.h::file_length --> path is NULL ");
    return f_struct.st_size;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 file_length_1( const char *path )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Determines the number of characters that contains a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param     path[const char*] &rarr; Path to the file
 * \return     f_struct.st_size[t_uint64] &rarr; Size of the file in octet or Number of chars in the file
 *
 * \note This function is intended to return a 32 bits unsigned integer so do not use it if files size more than 4GB
 *
 **********************************************************************************************************************************************************************************************************************************/
t_uint64 file_length_1( const char *path )
{
    struct stat f_struct;
    if( path )
    {
        if (stat(path, &f_struct) != 0)
            fprintf(logger,"\nfile.h::file_length_1 --> The stat function returned a negative value for the %s file [ERRNO:%s]", path, strerror(errno));
    }
    else fprintf(logger,"\nfile.h::file_length_1 --> path is NULL ");
    return f_struct.st_size;
}


/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 file_length_2( const char *path )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Determines the number of characters that contains a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param     path[const char*] &rarr; Path to the file
 * \return     file_length[const char*] &rarr; Size of the file in octet or Number of chars in the file
 *
 **********************************************************************************************************************************************************************************************************************************/
t_uint64 file_length_2( const char *path )
{
    t_uint64 read_byte, file_length = 0;
    FILE *f = NULL;
    if ( path )
    {
        if ( (f=file_open(path,"rb")) )
        {
            char *buffer = NULL ;
            if ( (buffer=allocate_1D_c(512)) )
            {
                while (0<(read_byte=fread(buffer,1,512*sizeof(char),f)))
                    file_length+=read_byte;

                deallocate_1D_c(buffer);
            }
            else fprintf(logger,"\nfile.h::file_length_2 --> allocate_1D_c returned NULL");
            file_close(f);
        }
        else fprintf(logger,"\nfile.h::file_length_2 --> file_open returned NULL. File:\"%s\" Rights:\"rb\" [ERRNO:%s]", path, strerror(errno));
    }
    else fprintf(logger,"\nfile.h::file_length_2 --> path is NULL");
    return file_length;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn void file_unit_destroy(t_file_unit *file_unit)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Destroys a t_file_unit structure
 ***********************************************************************************************************************************************************************************************************************************
 * \param     file_unit[t_file_unit*] &rarr; The t_file_unit structure to deallocate
 *
 **********************************************************************************************************************************************************************************************************************************/
void file_unit_destroy(t_file_unit *file_unit)
{
    if(file_unit)
    {
        free(file_unit->unit), file_unit->unit=NULL;
        free(file_unit), file_unit=NULL;
    }
    else fprintf(logger,"\nfile.h::file_unit_destroy --> You are trying to free a pointer that seems already freed");
}


/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_file_unit *file_unit_create_empty()
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Creates an empty t_file_unit structure
 ***********************************************************************************************************************************************************************************************************************************
 * \return     file_unit[t_file_unit*] &rarr; An empty t_file_unit structure
 *
 ***********************************************************************************************************************************************************************************************************************************/
t_file_unit *file_unit_create_empty()
{
    unsigned short alloc_status = 0;
    t_file_unit *file_unit=NULL;
    if ( (file_unit=(t_file_unit*)malloc(sizeof(t_file_unit))))
    {
        if ((file_unit->unit=allocate_1D_c(6)))
        {
            alloc_status=1;
        }
        else fprintf(logger,"\nfile.h::file_unit_create_empty --> allocate_1D_c returned NULL");
        if (!alloc_status)
            free(file_unit), file_unit=NULL;
    }
    else fprintf(logger,"\nfile.h::file_unit_create_empty --> Allocation of t_file_unit structure failed [ERRNO:%s]", strerror(errno));
    return file_unit;
}


/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_file_unit *file_unit_create(const char *unit, double coeff)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Creates a t_file_unit structure
 ***********************************************************************************************************************************************************************************************************************************
 * \param      unit[const char*] &rarr; Name of th unit
 * \param     coeff[double] &rarr; Coefficient of the unit
 *
 * \note It is up to you to choose the displayed unit of the file GB, MB, KB, B.... \n
 * \note The basic size of a file is in byte so the coefficient must be
 * \note GB : coeff = 1024*1024*1024
 * \note MB : coeff = 1024*1024
 * \note KB : coeff = 1024
 * \note and so on.
 **********************************************************************************************************************************************************************************************************************************/
t_file_unit *file_unit_create(const char *unit, double coeff)
{
    unsigned short alloc_status=0;
    t_file_unit *file_unit=NULL;
    if(unit)
    {
        if( (file_unit=file_unit_create_empty()) )
        {
            if ( str_replace(file_unit->unit,unit) )
            {
                file_unit->coeff=coeff;
                alloc_status=1;
            }
            else fprintf(logger,"\nfile.h::file_unit_create --> str_replace returned NULL");
            if(!alloc_status)
                file_unit_destroy(file_unit);
        }
        else fprintf(logger,"\nfile.h::file_unit_create --> file_unit_create_empty returned NULL");
    }
    else fprintf(logger,"\nfile.h::file_unit_create --> unit is NULL");
    return file_unit;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_file_unit *file_copy_get_size_unit(const char *src)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Determines the right unit to use
 ***********************************************************************************************************************************************************************************************************************************
 * \param      src[const char*] &rarr; Path to the file
 * \return     file_unit[t_file_unit *] &rarr; The structure that stocks the optimized unit to use for the file and the coefficient to convert it back in bytes
 *
 **********************************************************************************************************************************************************************************************************************************/
t_file_unit *file_copy_get_size_unit(const char *src)
{
    const char *unit=NULL;
    double coeff=0;
    t_uint64 f_src_size=0;
    unsigned short status = 0;
    t_file_unit *file_unit = NULL;
    if ( src )
    {
        if( (f_src_size = file_length(src)) )
        {
            if ( f_src_size < 1024 )
                status=1,coeff=1., unit="Byte";

            else if ( f_src_size < 1024*1024 )
                status=1,coeff=1./1024., unit="KByte";

            else if ( f_src_size < 1024*1024*1024 )
                status=1,coeff=1./(1024.*1024.), unit="MByte";

            else {status=1,coeff=1./(1024.*1024.*1024.), unit="GByte";}
        }
        else fprintf(logger,"\nfile.h::file_copy_get_size_unit --> Returned size for the \"%s\" file is 0", src);
    }
    else fprintf(logger,"\nfile.h::file_copy_get_size_unit --> src is NULL");

    if(status)
        if(!(file_unit=file_unit_create(unit,coeff)))
            fprintf(logger,"\nfile.h::file_copy_get_size_unit --> file_unit_create returned NULL");

    return file_unit;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn file_copy_get_stats(const char *src, const char *dst, double t0, t_file_unit *file_unit, t_uint64 total_written_byte, t_uint64 f_src_size)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Displays and updates values during the copy
 ***********************************************************************************************************************************************************************************************************************************
 * \param      src[const char*] &rarr; Path to the source file
 * \param      dst[const char*] &rarr; Path to the destination file
 * \param      t0[double] &rarr; Value that initialize the timer of the GetickCount function
 * \param      file_unit[t_file_unit*] &rarr; The structure that determines the optimized unit of the file
 * \param      total_written_byte[t_uint64] &rarr; The "current" total of written bytes at the moment of the c
 * \param      f_src_size[t_uint64] &rarr; Size of the source file
 *
 **********************************************************************************************************************************************************************************************************************************/
void file_copy_get_stats(const char *src, const char *dst, double t0, t_file_unit *file_unit, t_uint64 total_written_byte, t_uint64 f_src_size)
{
    if (src&&dst&&file_unit)
    {
        double current_size = total_written_byte*(file_unit->coeff);
        double t = (GetTickCount()-t0)/1000.;
        double speed = total_written_byte/(1024.*1024.*t);
        double progress = 100.*total_written_byte/f_src_size;
        system("cls");
        printf("\n Copying file");
        printf("\n -->From     : %s", src);
        printf("\n -->To       : %s", dst);
        printf("\n -->Progress : %.2f/%.2f %s [%.2f%%]", current_size, f_src_size*file_unit->coeff, file_unit->unit, progress);
        printf("\n -->Speed    : %.2f MByte/s\n",speed);
    }
    else fprintf(logger,"\nfile.h::file_copy_get_stats --> [ERRNO:%s]", strerror(errno));
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn short file_copy(const char *src, const char *dst)
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Copies a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param      src[const char*] &rarr; Path to the source file
 * \param      dst[const char*] &rarr; Path to the destination file
 * \return     copy_status[short] &rarr; Status of the function after its execution
 *
 **********************************************************************************************************************************************************************************************************************************/
short file_copy(const char *src, const char *dst)
{
    unsigned short copy_status=0;
    if (src && dst)
    {
        t_uint64 f_src_size = file_length(src);
        if ( file_exist(src)==1 && file_exist(dst)==0 )
        {
            FILE *f_src = NULL;
            FILE *f_dst = NULL;
            if ( (f_src = file_open(src,"rb")) && (f_dst = file_open(dst,"wb")) )
            {
                double t0 = GetTickCount();
                t_file_unit *file_unit = NULL;
                if ( (file_unit = file_copy_get_size_unit(src)) )
                {
                    t_uint64 read_byte, written_byte, total_written_byte=0;
                    char *buffer = NULL;
                    if ( (buffer = allocate_1D_c(512)) )
                    {
                        file_copy_get_stats(src, dst, 1, file_unit, total_written_byte, f_src_size);
                        while (0<(read_byte=fread(buffer, sizeof(char), 512, f_src)))
                        {
                            written_byte=fwrite(buffer, read_byte, sizeof(char), f_dst);
                            total_written_byte+=written_byte*read_byte;

                            if (total_written_byte%10485760==0)
                                file_copy_get_stats(src, dst, t0, file_unit, total_written_byte, f_src_size);
                        }
                        file_copy_get_stats(src, dst, t0, file_unit, total_written_byte, f_src_size);
                    }
                    else fprintf(logger,"\nfile.h::file_copy  --> allocate_1D_c returned NULL");
                    deallocate_1D_c(buffer);
                }
                else fprintf(logger,"\nfile.h::file_copy  --> file_copy_get_size_unit returned NULL");
                file_close(f_src);
                file_close(f_dst);
            }
            else
            {
                if (!f_src)
                    fprintf(logger,"\nfile.h::file_copy  --> f_src is NULL [ERRNO:%s]", strerror(errno));
                if (!f_dst)
                    fprintf(logger,"\nfile.h::file_copy  --> f_dst is NULL [ERRNO:%s]", strerror(errno));
            }
        }
        else fprintf(logger,"\nfile.h::file_copy  --> Be the \"%s\" file doesn't exist, be the \"%s\" file already exists [ERRNO:%s]", src, dst, strerror(errno));

        t_uint64 f_dst_size = file_length(dst);
        if ( f_dst_size == f_src_size )
            copy_status=1;
    }
    else fprintf(logger,"\nfile.h::file_copy --> At least one of both argument is NULL [ERRNO:%s]", strerror(errno));
    return copy_status;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 file_size( const char *path )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Determines the size of a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param      path[const char*] &rarr; Path to the file
 * \return     sz[t_uint64] &rarr; Size of the file
 *
 **********************************************************************************************************************************************************************************************************************************/
t_uint64 file_size( const char *path )
{
    t_uint64 sz = 0;
    if ( path )
    {
        if ( (sz=file_length(path)) )
            sz/=sizeof(char);

        else fprintf(logger,"\nfile.h::file_size --> file_length returned 0, something bad happened");
    }
    else fprintf(logger,"\nfile.h::file_size --> path is NULL");
    return sz;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn    char *file_to_string( const char *path )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Loads the content of a file in a string
 ***********************************************************************************************************************************************************************************************************************************
 * \param      path[const char*] &rarr; Path to the file
 * \return     str_out[char*] &rarr; The string stocking the content of the file
 *
 **********************************************************************************************************************************************************************************************************************************/
char *file_to_string( const char *path )
{
    char *str_out=NULL;
    if ( path )
    {
        FILE *pFile=NULL;
        if ( (pFile=file_open(path,"r+b")) )
        {
            char *t_realloc = NULL;
            char buffer='\0';
            t_uint64 f_sz = 0;
            size_t read_byte = 0;
            while( 0<(read_byte=fread(&buffer, sizeof(char), 1, pFile)) )
            {
                f_sz++;
                if ( (t_realloc=(char *)realloc(str_out, f_sz*sizeof(char))) )
                    str_out=t_realloc, str_out[f_sz-1]=buffer;

                else
                {
                    deallocate_1D_c(str_out);
                    fprintf(logger,"file.h::file_to_string --> The reallocation has failed at offset=%I64u [ERRNO:%s]\n", f_sz, strerror(errno));
                    read_byte=-1;
                }
            }
            if ( (t_realloc=(char *)realloc(str_out, (f_sz+1)*sizeof(char))) )
                    str_out=t_realloc, str_out[f_sz]='\0';

            else
            {
                deallocate_1D_c(str_out);
                fprintf(logger,"file.h::file_to_string --> The reallocation has failed at offset=%I64u [ERRNO:%s]\n", f_sz, strerror(errno));
            }
        }
        else fprintf(logger,"file.h::file_to_string --> file_open returned NULL for the file \"%s\" [ERRNO:%s]\n", path, strerror(errno));
        file_close(pFile);
    }
    return str_out;
}


/** *********************************************************************************************************************************************************************************************************************************
 * \fn    char *file_to_string_avoid_null( const char *path )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Loads the content of a file in a string
 ***********************************************************************************************************************************************************************************************************************************
 * \param      path[const char*] &rarr; Path to the file
 * \return     str_out[char*] &rarr; The string stocking the content of the file
 *
 * \note Use this version of file_to_string if your string is supposed to contain more than one NULL character.
 **********************************************************************************************************************************************************************************************************************************/
char *file_to_string_avoid_null( const char *path, t_uint64 *f_sz )
{
    char *str_out=NULL;
    if ( path )
    {
        FILE *pFile=NULL;
        if ( (pFile=file_open(path,"r+b")) )
        {
            char *t_realloc = NULL;
            char buffer='\0';
            *f_sz = 0;
            size_t read_byte = 0;
            while( 0<(read_byte=fread(&buffer, sizeof(char), 1, pFile)) )
            {
                (*f_sz)++;
                if ( (t_realloc=(char *)realloc(str_out, (*f_sz)*sizeof(char))) )
                    str_out=t_realloc, str_out[*f_sz-1]=buffer;

                else
                {
                    deallocate_1D_c(str_out);
                    fprintf(logger,"file.h::file_to_string --> The reallocation has failed at offset=%I64u [ERRNO:%s]\n", *f_sz, strerror(errno));
                    read_byte=-1;
                }
            }
            if ( (t_realloc=(char *)realloc(str_out, (*f_sz+1)*sizeof(char))) )
                    str_out=t_realloc, str_out[*f_sz]='\0';

            else
            {
                deallocate_1D_c(str_out);
                fprintf(logger,"file.h::file_to_string --> The reallocation has failed at offset=%I64u [ERRNO:%s]\n", *f_sz, strerror(errno));
            }
        }
        else fprintf(logger,"file.h::file_to_string --> file_open returned NULL for \"%s\" [ERRNO:%s]\n", path, strerror(errno));
        file_close(pFile);
    }
    return str_out;
}


/** *********************************************************************************************************************************************************************************************************************************
 * \fn    char *file_to_string_1( const char *path, t_uint64 *f_sz )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Loads in a string the content of a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param      path[const char*] &rarr; Path to the file
 * \return     str_out[char*] &rarr; The string stocking the content of the file
 *
 **********************************************************************************************************************************************************************************************************************************/
char *file_to_string_1( const char *path, t_uint64 *f_sz )
{
    *f_sz = 0;
    char *str_out=NULL;
    if ( path && f_sz )
    {
        FILE *pFile=NULL;
        if ( (pFile=file_open(path,"rb")) )
        {
            char *t_realloc = NULL;
            char buffer;
            size_t read_byte =0 ;
            while( 0<(read_byte=fread(&buffer, sizeof(char), 1, pFile)) )
            {
                (*f_sz)++;
                if ( (t_realloc=(char *)realloc(str_out, (*f_sz)*sizeof(char))) )
                   str_out=t_realloc, str_out[*f_sz-1]=buffer;

                else
                {
                    deallocate_1D_c(str_out);
                    fprintf(logger,"file.h::file_to_string_1 --> The reallocation has failed at offset=%I64u [ERRNO:%s]\n", *f_sz, strerror(errno));
                    read_byte=-1;
                }
            }
            str_out[*f_sz]='\0';
        }
        else fprintf(logger,"file.h::file_to_string_1 --> file_open returned NULL [ERRNO:%s]\n", strerror(errno));
        file_close(pFile);
    }
    else
    {
        if(!path)
            fprintf(logger,"file.h::file_to_string_1 --> path is NULL\n");
        if(!f_sz)
            fprintf(logger,"file.h::file_to_string_1 --> f_sz is NULL\n");
    }
    return str_out;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn    char *file_to_string_2( const char *path )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Loads in a string the content of a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param      path[const char*] &rarr; Path to the file
 * \return     str_out[const char*] &rarr; String stocking the content of the file
 *
 **********************************************************************************************************************************************************************************************************************************/
char *file_to_string_2( const char *path )
{
    char *str_out = NULL;
    if( path )
    {
        t_uint64 i = 0;
        char buffer = ' ';
        if ( (str_out = allocate_1D_c( file_length(path)+1 )) )
        {
            FILE *pFile = NULL;
            if ( (pFile = file_open(path,"r")) )
            {
                while( fscanf(pFile,"%c",&buffer) != EOF )
                    str_out[i] = buffer, i++;

                file_close(pFile);
            }
            else fprintf(logger,"file.h::file_to_string_2 --> file_open returned NULL for \"%s\" [ERRN0:%s]\n", path, strerror(errno));
        }
        else fprintf(logger,"file.h::file_to_string_2 --> allocate_1D_c returned NULL\n");
    }
    else fprintf(logger,"file.h::file_to_string_2 --> path is NULL\n");
    return str_out;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn    char *file_to_string_21( const char *path )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Loads in a string the content of a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param      path[const char*] &rarr; Path to the file
 * \return     str_out[const char*] &rarr; The string stocking the content of the file
 *
 **********************************************************************************************************************************************************************************************************************************/
char *file_to_string_21( const char *path )
{
    char *str_out = NULL;
    if( path )
    {
        t_uint64 i, file_sz = file_length(path);
        char buffer;
        if ( (str_out = allocate_1D_c( file_sz+1 )) )
        {
            FILE *pFile = NULL;
            if ( (pFile = file_open(path,"r")) )
            {
                for( i = 0; i<file_sz ; i++ )
                    fscanf(pFile,"%c",&buffer), str_out[i] = buffer, printf("%c", buffer);

                file_close(pFile);
            }
            else fprintf(logger,"file.h::file_to_string_2 --> file_open returned NULL for \"%s\" [ERRN0:%s]\n", path, strerror(errno));
        }
        else fprintf(logger,"file.h::file_to_string_2 --> allocate_1D_c returned NULL\n");
    }
    else fprintf(logger,"file.h::file_to_string_2 --> path is NULL\n");
    return str_out;
}

/** *********************************************************************************************************************************************************************************************************************************
 * \fn  t_uint64  file_count_occurrence( const char *path, char c )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Counts the number of occurences of a character in a file
 ***********************************************************************************************************************************************************************************************************************************
 * \param      path[const char*] &rarr; Path to the file
 * \return     c[t_uint64] &rarr; Counter of the occurences of the c character
 *
 **********************************************************************************************************************************************************************************************************************************/
t_uint64 file_count_occurrence( const char *path, char c )
{
    t_uint64 occurrence = 0;
    if( path )
    {
        char *file_content = NULL;
        if ( (file_content=file_to_string(path)) )
            occurrence = str_count_occurrence(path,c);

        else fprintf(logger,"file.h::file_count_occurence --> file_to_string returned NULL \n");
        deallocate_1D_c(file_content);
    }
    else fprintf(logger,"file.h::file_count_occurence --> path is NULL\n");
    return occurrence;
}




