 /***********************************************************************************************************************************************************************************************************************************
 * \file dir.c
 * \brief Library for handling directories/files
 * \author dark.anonymous.fr@gmail.com
 * \version 0.1
 * \date 12/04/2016
 **********************************************************************************************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <direct.h>

#include "ptrop.h"
#include "dir.h"
#include "logger.h"
#include "str.h"
#include "file.h"
#include "tim.h"

#define TRUE 1
#define FALSE 0
#define MAX_PATH_LEN 2048

 /** ********************************************************************************************************************************************************************************************************************************
 * \fn unsigned short dir_create( const char *dir_path )
 ***********************************************************************************************************************************************************************************************************************************
 * \brief Creates a directory
 ***********************************************************************************************************************************************************************************************************************************
 * \param   dir_path[const char *] &rarr; Path to the directory
 * \return	status[t_boolean] &rarr; t_boolean
 *
 * \note Returns 1 if the directory has been created without error, else returns 0
 **********************************************************************************************************************************************************************************************************************************/
t_boolean dir_create( const char *dir_path )
{
    errno=0;
    t_boolean status = FALSE;
    t_2Dc *path_index = NULL;
    if ( ( path_index = winpath_decompose( dir_path ) ) ) //T0
    {
        char *s = NULL;
        t_uint64 i = 0;
        for ( i = 0 ;  i <= path_index->x ; i++ )
        {
            if ( (s = str_concat_multiple( ( const char** )( path_index->da ),i ) ) ) //T1
            {
                if ( _mkdir( s ) == 0 )
                    status = TRUE;

                else if ( errno == EEXIST ){ status = TRUE; }
                //else if ( errno == ENOENT ){ fprintf(logger, "\ndir.h::dir_create --> Path access not found \"%s\" directory [ERRNO:%s]", s, strerror(errno)); }
                else fprintf(logger, "\ndir.h::dir_create --> The function failed to create the \"%s\" directory [ERRNO:%s]", s, strerror(errno));
                deallocate_1D_c(s);
            }
            else fprintf(logger, "\ndir.h::dir_create.T1 --> str_concat_multiple returned NULL");
        }
        destroy_2D_c(path_index);
    }
    else fprintf(logger, "\ndir.h::dir_create.T0 --> winpath_decompose returned NULL");
    return status;
}

 /** *******************************************************************************************************************************************************************************************************************************
 * \fn unsigned short dir_close( DIR *pDir )
 * ********************************************************************************************************************************************************************************************************************************
 * \brief Close the handle associated to the opened directory
 **********************************************************************************************************************************************************************************************************************************
 * \param   pDir[DIR*] &rarr; Pointer to the directory to close
 * \return	status[t_boolean] &rarr; State of the closing of the directory
 *
 * \note Returns TRUE if the directory has been closed without error, else returns FALSE
 *********************************************************************************************************************************************************************************************************************************/
t_boolean dir_close( DIR *pDir )
{
    t_boolean status = FALSE;
    if ( pDir )
    {
        if ( closedir( pDir ) == -1 )
            fprintf(logger, "\ndir.h::dir_close --> [ERRNO:%s]", strerror(errno));

        else status = TRUE;
    }
    else fprintf(logger, "\ndir.h::dir_close --> The directory is already closed\n");
    return status;
}

 /** *******************************************************************************************************************************************************************************************************************************
 * \fn DIR *dir_open( const char *dir_path )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Open a directory
 **********************************************************************************************************************************************************************************************************************************
 * \param   dir_path[const char*] &rarr; Path to the directory
 * \return	pDir[DIR*] &rarr; Pointer to the opened directory
 *
 * \note The function will return a NULL pointer if it fails to open the specified directory
 *********************************************************************************************************************************************************************************************************************************/
DIR *dir_open( const char *dir_path )
{
    DIR *pDir = NULL;
    if ( dir_path )
    {
        if ( !(pDir=opendir( dir_path )) )
            if ( strcmp(strerror(errno),"Not a directory") != 0 ){};
                //fprintf(logger, "\ndir.h::dir_open --> opendir returned NULL \"%s\" [ERRNO:%s]", dir_path, strerror(errno));
    }
    //else fprintf(logger, "\ndir.h::dir_open --> dir_path is NULL");
    return pDir;
}

 /** *******************************************************************************************************************************************************************************************************************************
 * \fn unsigned short is_dir(const char *ent_path)
 **********************************************************************************************************************************************************************************************************************************
 * \brief Tells if yes or no the entity is a directory.
 **********************************************************************************************************************************************************************************************************************************
 * \param   ent_path[const char*] &rarr; Path to the entity
 * \return	is_dir[t_boolean] &rarr; Status of the entity
 *
 * \note The function returns TRUE if the entity is a directory and FALSE if not.
 *********************************************************************************************************************************************************************************************************************************/
t_boolean is_dir(const char *ent_path)
{
    unsigned short is_dir = FALSE;
    if ( ent_path )
    {
        if ( dir_open( ent_path ) )
            is_dir=TRUE;
    }
    else fprintf(logger, "\ndir.h::is_dir --> ent_path is NULL");
    return is_dir;
}

 /** *******************************************************************************************************************************************************************************************************************************
 * \fn t_2Dc *dir_read( const char *dir_path )
 **********************************************************************************************************************************************************************************************************************************
 * \brief List the content of a directory
 **********************************************************************************************************************************************************************************************************************************
 * \param   dir_path[const char*] &rarr; The path to the directory to read
 * \return  is_dir[t_2Dc *] &rarr; The structure that contains the listing of the directory
 *
 *********************************************************************************************************************************************************************************************************************************/
t_2Dc *dir_read( const char *dir_path )
{
    t_2Dc *dir_list = NULL;
    DIR *pDir=NULL;
    if ( dir_path )
    {
        if ( (pDir = dir_open( dir_path )) )
        {
            struct dirent *entity = NULL;
            t_uint64 index = 0;
            char **list = NULL;
            if ( (list = allocate_2D_c(1,MAX_PATH_LEN)) )
            {
                char **realloc_2D = NULL;
                t_boolean cpy   = TRUE;
                t_boolean token = TRUE;
                while( (entity = readdir( pDir )) && token==TRUE )
                {
                    if ( index > 0 )
                    {
                        index++;
                        if ( (realloc_2D=(char**)realloc(list, (index+1)*sizeof(char*))) )
                        {
                            list=realloc_2D;
                            if ( (list[index] = allocate_1D_c(MAX_PATH_LEN)) )
                            {
                                if ( ((cpy = str_copy_dyn_to_static(entity->d_name, list[index], 1024)))!=TRUE )
                                    fprintf(logger,"\ndir.h::dir_read --> str_copy_dyn_to_static returned FALSE" );

                                printf("\n%s", list[index]);
                            }
                            else
                            {
                                token = FALSE;
                                deallocate_2D_c(list, index-1);
                                fprintf(logger,"\ndir.h::dir_read --> allocate_1D_c returned NULL");
                            }
                        }
                        else
                        {
                            token = FALSE;
                            deallocate_2D_c(list, index-1);
                            fprintf(logger,"\ndir.h::dir_read --> realloc returned NULL");
                        }
                    }
                    else
                    {
                        if ( (cpy = (str_copy_dyn_to_static(entity->d_name, list[0], 1024)))!=TRUE )
                            fprintf(logger,"\ndir.h::dir_read --> str_copy_dyn_to_static returned FALSE");

                        index++;
                    }
                }

                if ( token == TRUE )
                {
                    if ( dir_list = create_2D_c(index+1, MAX_PATH_LEN) )
                    {
                        dir_list->da = list;
                        dir_list->x = index;
                        dir_list->y = MAX_PATH_LEN;
                    }
                    else fprintf(logger,"\ndir.h::dir_read --> create_2D_c returned NULL");
                }
                else fprintf(logger,"\ndir.h::dir_read --> token = FALSE");
                dir_close(pDir);
            }
            else fprintf(logger,"\ndir.h::dir_read --> allocate_2D_c returned NULL");
        }
        else fprintf(logger,"\ndir.h::dir_read --> dir_open returned NULL by trying to open \"%s\" [ERRNO:%s]", dir_path, strerror(errno));
    }
    else fprintf(logger,"\ndir.h::dir_read --> dir_path is NULL");
    return dir_list;
}


/** ********************************************************************************************************************************************************************************************************************************
 * \fn char *entity_get_path( const char *dir_path, const char *eName )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Returns the full path of an entity by concatenating the root folder and the name of the entity
 **********************************************************************************************************************************************************************************************************************************
 * \param   dir_path[const char*] &rarr; Path to the directory containing the entity
 * \param   eName[const char*] &rarr; Name of the entity
 *
 * \note The function handles cases where dir_path has a missing '\'
 **********************************************************************************************************************************************************************************************************************************/
char *entity_get_path( const char *dir_path, const char *eName )
{
    char *str_out = NULL;
    if ( dir_path && eName ) //T0
    {
        if ( dir_path[ str_length( dir_path )-1 ] != '\\')
        {
            if ( !( str_out = str_concat( str_concat( dir_path, "\\" ), eName ) ) ) //T1
                fprintf(logger,"\ndir.h::entity_get_path.T1 --> str_concat returned NULL");
        }
        else
        {
            if (  !( str_out = str_concat( dir_path, eName ) ) ) //T2
                fprintf(logger,"\ndir.h::entity_get_path.T2 --> str_concat returned NULL");
        }
    }
    else
    {
        if ( !dir_path )
            fprintf(logger,"\ndir.h::entity_get_path.T0 --> dir_path is NULL");
        if ( !eName )
            fprintf(logger,"\ndir.h::entity_get_path.T0 --> eName is NULL");
    }
    return str_out;
}

/** ********************************************************************************************************************************************************************************************************************************
 * \fn t_boolean dir_browse( const char *dir_path )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Displays in a command prompt the whole content of a directory
 **********************************************************************************************************************************************************************************************************************************
 * \param   dir_path[const char*] &rarr; Path to the directory
 * \return  status[t_boolean] &rarr; Status of dir_brownse
 *
 *********************************************************************************************************************************************************************************************************************************/
t_boolean dir_browse( const char *dir_path )
{
    t_boolean status = TRUE;
    if ( dir_path )
    {
        DIR *pDir = NULL;
        if ( dir_browse_recursive( pDir, dir_path ) == FALSE )
            fprintf(logger,"\ndir.h::dir_browse --> dir_browse_recursive returned NULL");
    }
    else fprintf(logger,"\ndir.h::dir_browse.T0 --> dir_path is NULL");
    return status;
}

/** ********************************************************************************************************************************************************************************************************************************
 * \fn t_boolean dir_browse_recursive( DIR *pDir, const char *dir_path )
 **********************************************************************************************************************************************************************************************************************************
 * \brief 'Child' function of dir_browse
 **********************************************************************************************************************************************************************************************************************************
 * \param   pDir[DIR*] &rarr; Pointer to directory
 * \param   dir_path[const char*] &rarr; Path to the directory
 * \return  status[t_boolean] &rarr; Status of dir_browse_recursive
 *
 *********************************************************************************************************************************************************************************************************************************/
t_boolean dir_browse_recursive( DIR *pDir, const char *dir_path )
{
    t_boolean status = TRUE;
    if ( dir_path ) // T0
    {
        if ( (pDir = dir_open( dir_path )) ) //T2                                         /* L'entité à parcourir est-elle un répertoire */
        {
            struct dirent *pEnt = NULL;                                            /* Structure renseignant le contenu du répertoire */
            seekdir( pDir, 2 );
            char *entity_path = NULL;                                                     /* Déplacer le curseur de parcours du répertoire de 2 pour éviter le repertoire parent et courant ./ && ../ */
            while( (pEnt=readdir( pDir )) )                                        /* Parcourir le dossier tant que l'on est pas arrivé à la fin de celui-ci */
            {
                if ( (entity_path = entity_get_path( dir_path, pEnt->d_name )) ) // T3    /* Déterminer la chemin absolue de l'entité parcourue courante */
                {
                    if ( (is_dir( entity_path )) )
                        if ( (status=dir_browse_recursive( pDir, entity_path )) == FALSE ) // T4
                            fprintf(logger, "\ndir.h::dir_browse_recursive.T3 --> dir_browse_recursive returned FALSE");
                                                                                        /* Si c'est un dossier */ /* Appel récursif de la fonction pour le dossier courant */
                    printf("\n%s", entity_path);
                    deallocate_1D_c( entity_path );
                }
                else
                {
                    status = FALSE;
                    fprintf(logger, "\ndir.h::dir_browse_recursive.T3 --> entity_get_path returned NULL");
                }
            }
            dir_close( pDir );  /* Le dossier a été parcouru entièrement, il faut le fermer */
        }
        else
        {
            status = FALSE;
            fprintf(logger, "\ndir.h::dir_browse_recursive.T2 --> dir_open returned NULL");
        }
    }
    else
    {
        status = FALSE;
        fprintf(logger, "\ndir.h::dir_browse_recursive.T0 --> dir_path is NULL");
    }
    return status;
}


/** ********************************************************************************************************************************************************************************************************************************
 * \fn t_boolean dir_remove( const char *dir_path )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Removes the specified directory
 **********************************************************************************************************************************************************************************************************************************
 * \param   dir_path[const char*] &rarr; Path to the directory
 * \return  status[t_boolean] &rarr; Status of dir_remove
 *
 *********************************************************************************************************************************************************************************************************************************/
t_boolean dir_remove( const char *dir_path )
{
    t_boolean status = TRUE;
    if ( dir_path ) // T0
    {
        DIR *pDir=NULL;
        if ( (status=dir_remove_recursive( pDir, dir_path ) ) == FALSE )
            fprintf(logger,"\ndir.h::dir_remove --> dir_remove_recursive returned FALSE");

        else
        {
            if ( !_rmdir( dir_path ) )
                fprintf(logger,"\ndir.h::dir_remove --> _rmdir returned NULL");
        }
    }
    else
    {
        status = FALSE;
        fprintf(logger, "\ndir.h::dir_remove.T0 --> dir_path is NULL");
    }
    return status;
}

/** ********************************************************************************************************************************************************************************************************************************
 * \fn t_boolean dir_remove_recursive( DIR *pDir, const char *dir_path )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Child function of dir_remove
 **********************************************************************************************************************************************************************************************************************************
 * \param   dir_path[const char*] &rarr; Path to the directory
 *
 *********************************************************************************************************************************************************************************************************************************/
t_boolean dir_remove_recursive( DIR *pDir, const char *dir_path )
{
    t_boolean status = TRUE;
    if ( dir_path )
    {
        if ( (pDir = dir_open( dir_path )) )
        {
            struct dirent *pEnt = NULL;
            seekdir(pDir,2);
            char *entity_path = NULL;
            while( (pEnt = readdir( pDir )) )
            {
                if ( (entity_path = entity_get_path( dir_path, pEnt->d_name )) )
                {
                    if ( (is_dir( entity_path )) )
                    {
                        if ( ( ( status = dir_remove_recursive ( pDir, entity_path ) ) == FALSE ) )
                            fprintf(logger,"\ndir.h::dir_remove_recursive --> dir_remove_recursive returned FALSE");
                    }
                    else
                        if ( remove( entity_path ) != 0 )
                        {
                            status = FALSE;
                            fprintf(logger,"\ndir.h::dir_remove_recursive --> remove returned NULL");
                        }

                    deallocate_1D_c( entity_path );
                }
                else
                {
                    status = FALSE;
                    fprintf(logger,"\ndir.h::dir_remove_recursive --> entity_get_path returned NULL");
                }
            }
            dir_close( pDir );
            if ( _rmdir( dir_path ) != 0 )
                fprintf(logger,"\ndir.h::dir_remove_recursive --> _rmdir returned NULL");
        }
        else
        {
            status = FALSE;
            fprintf(logger,"\ndir.h::dir_remove_recursive --> dir_open returned NULL");
        }
    }
    else
    {
        status = FALSE;
        fprintf(logger,"\ndir.h::dir_remove_recursive --> dir_path is NULL");
    }
    return status;
}

/** ********************************************************************************************************************************************************************************************************************************
 * \fn char *dir_search( const char *dir_path, const char *eName )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Searchs an entity from the specified directory
 **********************************************************************************************************************************************************************************************************************************
 * \param   dir_path[const char*] &rarr; Path to the directory from where the search will begun
 * \return  eName[const char*] &rarr; Name of the entity to search
 *
 *********************************************************************************************************************************************************************************************************************************/
char *dir_search( const char *dir_path, const char *eName )
{
    char *r = NULL;
    if ( dir_path && eName )
    {
        DIR *pDir = NULL;
        dir_search_recursive( pDir, dir_path, eName, &r );
        if ( !r )
            fprintf(logger,"\ndir.h::dir_search --> The \"%s\" file has not been found in the \"%s\" directory", eName, dir_path);
    }
    return r;
}

/** ********************************************************************************************************************************************************************************************************************************
 * \fn void dir_search_recursive( DIR *pDir, const char *dir_path, const char *eName, char **search_result )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Child function of dir_search
 **********************************************************************************************************************************************************************************************************************************
 * \param   pDir[const char*] &rarr; Pointer to the directory
 * \param   dir_path[const char*] &rarr; Path to the directory
 * \param   eName[const char*] &rarr; Name of the entity to search
 *
 *********************************************************************************************************************************************************************************************************************************/
void dir_search_recursive( DIR *pDir, const char *dir_path, const char *eName, char **search_result )
{
    if ( dir_path )
    {
        if ( (pDir = dir_open( dir_path )) )
        {
            seekdir( pDir,2 );
            struct dirent *pEnt = NULL;
            while( (pEnt = readdir( pDir )) )
            {
                char *ePath = entity_get_path( dir_path, pEnt->d_name );
                if (is_dir(ePath))
                    dir_search_recursive( pDir, ePath, eName, search_result );

                else
                {
                    if ( strcmp( pEnt->d_name, eName ) == 0 )
                    {
                        while( (pEnt = readdir( pDir )) );
                        (*search_result) = str_copy( ePath );
                    }

                    else deallocate_1D_c( ePath );
                }
            }
            dir_close( pDir );
        }
        else fprintf(logger, "\ndir.h::dir_search_recursive --> Error opening the \"%s\" directory [ERRNO:%s]", dir_path, strerror(errno));
    }
    else fprintf(logger, "\ndir.h::dir_search_recursive --> The dir_path argument is NULL");
}


/** ********************************************************************************************************************************************************************************************************************************
 * \fn void dir_count(char *dir_path, unsigned long long int *dir_count, unsigned long long int *file_count)
 **********************************************************************************************************************************************************************************************************************************
 * \brief Counts the number of files and directories that contains a specified directory
 **********************************************************************************************************************************************************************************************************************************
 * \param   dir_path[const char *] &rarr; Path to the directory
 * \param   dir_count[t_uint64 *] &rarr; Variable that counts the number of directories
 * \param   file_count[t_uint64 *] &rarr; Variable that counts the number of files
 *
 *********************************************************************************************************************************************************************************************************************************/
void dir_count(char *dir_path, unsigned long long int *dir_count, unsigned long long int *file_count)
{
    if ( dir_path && dir_count && file_count )
    {
        DIR *pDir=NULL;
        *dir_count=0; *file_count=0;
        dir_count_recursive(pDir, dir_path, dir_count, file_count);
    }
}

/** ********************************************************************************************************************************************************************************************************************************
 * \fn void dir_count(char *dir_path, unsigned long long int *dir_count, unsigned long long int *file_count)
 **********************************************************************************************************************************************************************************************************************************
 * \brief Child function of dir_count
 **********************************************************************************************************************************************************************************************************************************
 * \param   pDir[const char*] &rarr; Pointer to the directory
 * \param   dir_path[const char*] &rarr; Path to the directory
 * \param   dir_count[const char*] &rarr; Variable that counts the number of directories
 * \param   file_count[const char*] &rarr; Variable that counts the number of files
 *
 *********************************************************************************************************************************************************************************************************************************/
void dir_count_recursive( DIR *pDir, const char *dir_path, unsigned long long int *dir_count, unsigned long long int *file_count )
{
    if ( dir_path && dir_count && file_count )
    {
        if ( (pDir = dir_open( dir_path )) )
        {
            seekdir( pDir,2 );
            struct dirent *pEnt = NULL;
            while( (pEnt=readdir( pDir )) )
            {
                char *ePath = entity_get_path( dir_path, pEnt->d_name );
                if ( is_dir( ePath ) )
                {
                    (*dir_count)++;
                    dir_count_recursive( pDir, ePath, dir_count, file_count );
                }

                else (*file_count)++;
                deallocate_1D_c( ePath );
            }
            dir_close( pDir );
        }
        else fprintf(logger,"\ndir.h::dir_count_entity --> Can't open the specified directory \"%s\" [ERRNO:%s]", dir_path, strerror(errno));
    }
    else fprintf(logger,"\ndir.h::dir_count_entity --> At least one of the arguments is NULL");
}


/** ********************************************************************************************************************************************************************************************************************************
 * \fn t_uint64 dir_size( const char *dir_path )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Determines the size of a directory
 **********************************************************************************************************************************************************************************************************************************
 * \param   dir_path[const char*] &rarr; Path to the directory
 * \return  dir_size[t_uint64] &rarr; Size of the directory
 *
 *********************************************************************************************************************************************************************************************************************************/
unsigned long long int dir_size( const char *dir_path )
{
    unsigned long long int dir_size = 0;
    if ( dir_path )
    {
        if ( is_dir( dir_path ) )
        {
            DIR *pDir = NULL;
            dir_size_recursive( pDir, dir_path, &dir_size );
        }
        else fprintf(logger,"\ndir.h::dir_size --> \"%s\" is not a directory", dir_path);
    }
    else fprintf(logger,"\ndir.h::directory_size --> The directory_path argument is NULL");
    return dir_size;
}


/** ********************************************************************************************************************************************************************************************************************************
 * \fn dir_size_recursive( DIR *pDir, const char *dir_path, unsigned long long int *dir_size )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Child function of dir_size
 **********************************************************************************************************************************************************************************************************************************
 * \param  pDir[DIR*] &rarr; Pointer to the directory
 * \param  dir_path[const char*] &rarr; Path to the directory
 * \param  dir_size[t_uint64] &rarr; Size of the directory
 *
 *********************************************************************************************************************************************************************************************************************************/
void dir_size_recursive( DIR *pDir, const char *dir_path, unsigned long long int *dir_size )
{
    if(dir_path&&dir_size)
    {
        if( (pDir = dir_open(dir_path)) )
        {
            seekdir( pDir,2 );
            struct dirent *pEnt = NULL;
            while( (pEnt = readdir( pDir ))  )
            {
                char *ePath = entity_get_path(dir_path, pEnt->d_name);

                if ( is_dir( ePath ) )
                    dir_size_recursive( pDir, ePath, dir_size );

                else (*dir_size) += file_length( ePath );
                deallocate_1D_c( ePath );
            }
            dir_close( pDir );
        }
        else fprintf(logger,"\ndir.h::dir_size --> Can't open the specified directory \"%s\" [ERRNO:%s]", dir_path, strerror(errno));
    }
    else fprintf(logger,"\ndir.h::dir_size --> At least, one of both arguments is NULL");
}

/** ********************************************************************************************************************************************************************************************************************************
 * \fn dir_copy( const char *dir_src_path, const char *dir_dst_path )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Copies a specified directory to the choosen one
 **********************************************************************************************************************************************************************************************************************************
 * \param   dir_src_path[const char*] &rarr; Path to the source directory to copy
 * \param  dir_dst_path[const char*] &rarr; Path to the destination directory
 *
 *********************************************************************************************************************************************************************************************************************************/
void dir_copy( const char *dir_src_path, const char *dir_dst_path )
{
    if ( dir_src_path && dir_dst_path )
    {
        DIR *pDir = NULL;
        char *current_dir_src_path = NULL;
        char *current_dir_dst_path = NULL;
        if ( (current_dir_src_path = str_copy( dir_src_path )) && ( current_dir_dst_path = str_copy( dir_dst_path )) )
        {
            if ( dir_create( dir_dst_path ) == 1 )
                dir_copy_recursive( pDir, dir_src_path, dir_dst_path, current_dir_src_path, current_dir_dst_path );

            else fprintf(logger, "\ndir.h::dir_copy --> The function failed to create the \"%s\" directory [ERRNO:%s]", dir_dst_path, strerror(errno));
            deallocate_1D_c( current_dir_src_path );
            deallocate_1D_c( current_dir_dst_path );
        }
        else fprintf(logger,"\ndir.h::directory_copy --> Error while initializing the current paths");

    }
    else fprintf(logger,"\ndir.h::directory_copy --> At least one of both arguments is NULL -ERRNO : %s", strerror(errno));
}

void ecopy( const char *src_path, const char *dst_path )
{
    if ( src_path && dst_path ) //T0
    {
        t_time *time = NULL;
        if ( (time=time_create_structure()) ) //T1
        {
            double t0=GetTickCount();

            if ( is_dir(src_path) == TRUE )
                dir_copy(src_path,dst_path);

            else file_copy(src_path, dst_path);

            double t1=GetTickCount()-t0;

            time_format(t1/1000., time);
            time_display(time);
            time_destroy_structure(time);
        }
        else fprintf(logger,"\ndir.h::ecopy.T1 --> dir_src_path is NULL");
    }
    else
    {
        if(!src_path)
            fprintf(logger,"\ndir.h::ecopy.T0 --> dir_src_path is NULL");
        if(!dst_path)
            fprintf(logger,"\ndir.h::ecopy.T0 --> dir_dst_path is NULL");
    }
}

/** ********************************************************************************************************************************************************************************************************************************
 * \fn dir_copy_recursive( DIR *pDir, const char *dir_src_path, const char *dir_dst_path, const char *current_dir_src_path, const char *current_dir_dst_path )
 **********************************************************************************************************************************************************************************************************************************
 * \brief Child function of dir_copy
 **********************************************************************************************************************************************************************************************************************************
 * \param   pDir[const char*] &rarr; Pointer to the directory
 * \param   dir_src_path[const char*] &rarr; Path to the source directory
 * \param   dir_dst_path[const char*] &rarr; Path to the destination directory
 * \param   current_dir_src_path[const char*] &rarr; Current path of the directory being copied from the source directory
 * \param   current_dir_dst_path[const char*] &rarr; Current path of the directory being copied from the destination destination
 *
 *********************************************************************************************************************************************************************************************************************************/
void dir_copy_recursive( DIR *pDir, const char *dir_src_path, const char *dir_dst_path, const char *current_dir_src_path, const char *current_dir_dst_path )
{
     if( dir_src_path && dir_dst_path && current_dir_src_path && current_dir_dst_path )
     {
        pDir = dir_open( current_dir_src_path );
        seekdir( pDir,2 );
        struct dirent *pEnt = NULL;
        while( (pEnt = readdir( pDir ))  )
        {
            unsigned long long int cmp = str_common     ( dir_src_path        , current_dir_src_path );                            // Chemin relatif entre dir_src_path et current_dir_src_path
               char *relative_src_path = str_copy_from_to( current_dir_src_path, cmp+1           , str_length( current_dir_src_path )); // Chemin relatif entre dir_src_path et current_dir_src_path
                        char *tmp_path = str_concat     ( dir_dst_path        , relative_src_path );                                           // Chemin de l'entité à copier
                 char *entity_src_path = entity_get_path( current_dir_src_path, pEnt->d_name      );                            // On récupère le chemin de l'entité(fichier ou dossier) du repertoire courant
                 char *entity_dst_path = entity_get_path( tmp_path            , pEnt->d_name      );                                        // Chemin de l'entité courante à copier dans le nouveau repertoire
            if ( is_dir( entity_src_path ) )
            {
                if ( dir_create( entity_dst_path )== 1 )
                    dir_copy_recursive( pDir, dir_src_path, dir_dst_path, entity_src_path, entity_dst_path );

                else fprintf(logger,"\ndir.h::dir_copy_recursive --> Error creating the following directory : \"%s\" [ERRNO:%s]", entity_dst_path, strerror(errno));
            }
            else
                if ( !file_copy( entity_src_path, entity_dst_path ))
                    fprintf(logger,"\ndir.h::dir_copy_recursive --> The copy of the \"%s\" file did not end properly : [ERRNO:%s]", entity_dst_path, strerror(errno));

            deallocate_1D_c( entity_src_path );
            deallocate_1D_c( entity_dst_path );
            deallocate_1D_c( relative_src_path );
            deallocate_1D_c( tmp_path );
        }
        dir_close( pDir );
     }
     else fprintf(logger, "\ndir.h::dir_copy_recursive --> At least, one the arguments is NULL");
}

//void copy(const char *src, const char *dsl)
//{
//    if ( src && dst )
//    {
//        if ( logical_drive_get_type(src) == 3 )
//    }
//}
//
//char *logical_drive_get_type(const char *drive_path)
//{
//    char *drive_type = NULL;
//    if ( drive_path )
//    {
//        t_uint64 drive_type_id = GetDriveType(drive_path);
//             if ( drive_type_id == 0 ) { drive_type = str_copy("DRIVE_UNKNOWN"    ); }
//        else if ( drive_type_id == 1 ) { drive_type = str_copy("DRIVE_NO_ROOT_DIR"); }
//        else if ( drive_type_id == 2 ) { drive_type = str_copy("DRIVE_REMOVABLE"  ); }
//        else if ( drive_type_id == 3 ) { drive_type = str_copy("DRIVE_FIXED"      ); }
//        else if ( drive_type_id == 4 ) { drive_type = str_copy("DRIVE_REMOTE"     ); }
//        else if ( drive_type_id == 5 ) { drive_type = str_copy("DRIVE_CDROM"      ); }
//        else if ( drive_type_id == 6 ) { drive_type = str_copy("DRIVE_RAMDISK"    ); }
//        else fprintf(logger,"sep.h::logical_drive_get_type --> An unexpected value has been returned\n");
//    }
//    return drive_type;
//}
//
//t_1Dus *logical_drive_get_index()
//{
//    DWORD word = 0;
//    t_1Dus *logical_drive_index = NULL;
//    if ( (logical_drive_index=create_1D_us(26)) )
//    {
//        if ( (word=GetLogicalDrives()) )
//        {
//            DWORD mask=1;
//            unsigned short i;
//            for (i=0;i<26;i++)
//            {
//                if ( (word&mask) )
//                    logical_drive_index->da[i]=1;
//
//                else logical_drive_index->da[i]=0;
//                mask = mask << 1;
//            }
//        }
//        else fprintf(logger,"\nsep.c::logical_drive_get_index --> The GetLogicalDrives function returned a NULL value");
//    }
//    else fprintf(logger,"\nsep.c::logical_drive_get_index --> The create_1D_us function returned a NULL value");
//    return logical_drive_index;
//}
//
//t_1Dc *logical_drive_get_list()
//{
//    t_1Dc *logical_drive_list = NULL;
//    t_1Dus *logical_drive_index = NULL;
//    if ( (logical_drive_index=logical_drive_get_index()) )
//    {
//        char DRIVE_LETTER_INDEX[27]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//        unsigned short i=0;
//        unsigned long long int counter=0;
//        for (i=0;i<26;i++)
//            if ( logical_drive_index->da[i] == 1 )
//                counter++;
//
//        unsigned short j=0;
//        if ( (logical_drive_list=create_1D_c(counter)) )
//        {
//            for (i=0;i<26;i++)
//                if ( logical_drive_index->da[i] == 1 )
//                    logical_drive_list->da[j]=DRIVE_LETTER_INDEX[i], j++;
//        }
//        else fprintf(logger,"\nsep.c::logical_drive_get_list --> The logical_drive_list function returned a NULL value");
//    }
//    else fprintf(logger,"\nsep.c::logical_drive_get_list --> The logical_drive_index function returned a NULL value");
//    return logical_drive_list;
//}
//
//unsigned short logical_drive_check_availability(char drive_letter)
//{
//    unsigned short check_status = 0;
//    t_1Dc *logical_drive_list = NULL;
//    if ( (logical_drive_list=logical_drive_get_list()) )
//    {
//        char *pattern = str_char_to_str(drive_letter);
//        if (str_find(logical_drive_list->da, pattern)==1)
//            check_status = 1;
//    }
//    else fprintf(logger,"\nsep.c::logical_drive_check_availability --> The logical_drive_get_list function returned a NULL ptr");
//    return check_status;
//}
