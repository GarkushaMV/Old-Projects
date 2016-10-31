#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <malloc.h>
#include <ctype.h>
#include "list.h"


struct hash_t
{
    struct list_t** LIST;
    int ( *func ) ( char* );
};



#define uchar  unsigned char

#define ucc    unsigned const char

#define Free(argument); {                       \
                            free ( argument );  \
                            argument = NULL;    \
                        }



//! reading string from input file
int ReadString          ( const char name[], char* buff[], int* length );


//! counts number of lines in string from input file
int NumberOfLines       ( char  buff[], const char reqSymb1,  const char reqSymb2, int* length );


//! creates array of string that contains lines from the input file
char** MakeArrayOfStrings  ( char  buff[], int* length, int* lines );


//! printing text in file
int PrintFile           ( const char name[], char* text[], int* lines );




char** Reader ( const char name[], int *lines )
{
    int length = 0;
    char* buff = NULL;

    //! input file and convert to string
    if ( ReadString ( name, &buff, &length ) == ERROR )
        return NULL;

    *lines = NumberOfLines ( buff,  '\n', 'r', &length ) ;

    ASSERT( ( lines > 0 ) && ( buff != NULL ) );

    return MakeArrayOfStrings ( buff, &length, lines);

}



int ReadString ( const char name[], char *buff[], int* length )
{
    ASSERT( ( name != NULL ) && ( *length == 0 ) );

    FILE* input = fopen ( name, "r" );
    if ( input == NULL )
    {
        printf ( "ERROR: Can't open the file: '%s'\n", name );
        return ERROR;
    }

    //! length of input file
    *length =  filelength ( fileno ( input ) );
    if ( length == 0 )
    {
        printf ( "ERROR: Input file is empty\n" );
        return ERROR;
    }

    ASSERT( *length <= MAX_LENGTH );

    *buff = ( char* ) calloc ( *length + 1 , sizeof( char ) );

    fread ( *buff, *length, sizeof(uchar), input );

    ( *buff ) [ ( *length ) ] = '\0';

    fclose ( input );
    return OK;
}



int NumberOfLines ( char buff[], const char reqSymb1, const char reqSymb2, int* length  )
{
    ASSERT( ( buff != 0 ) && ( *length > 0 ) );

    int i = 0, count = 0;
    for ( ; i < *length; i++ )
        if ( buff[i] == reqSymb1 || buff[i] == reqSymb2 )
            count++;
    count--;
    return count;
}



char** MakeArrayOfStrings ( char buff[], int* length, int* lines )
{
    ASSERT( ( lines != NULL ) && ( buff != 0 ) && ( *length > 0 ) );

    char** text = ( char** ) calloc ( *lines, sizeof ( char* ) );
    int i = 0,
        j = 0,
        begin_String = 0;

    for( i = 0; i < ( *lines ) ; i++ )
    {

        while ( ( j < *length ) && ( buff[j] != '\n' ) && ( buff[j] != '\r' ) )
            j++;

        ASSERT ( j <= *length );

        if( j < *length )
        {
            //! change symbol '\n' or 'r' on '\0' - EOL -> end of string
            buff[j] = '\0';
            j++;
        }

        if (j != *length && i < *lines)
            text[i]  = &buff[begin_String];
        begin_String = j;

    }

    return text;
}



int PrintFile ( const char name[], char* text[], int* lines )
{
    ASSERT ( ( text != NULL ) && ( lines > 0 ) );

    FILE* output = fopen ( name, "w" );
    if ( output == NULL )
    {
        printf ( "ERROR: Can't open the file: '%s'\n", name );
        return ERROR;
    }

    ASSERT ( output != NULL );

    int i = 0;
    for ( ; i < *lines; i++ )
        fprintf ( output, "%s\n", text[i] );

    fclose ( output );

    return OK;
}



int PrintList ( const char name[] , struct hash_t* HASH )
{
    FILE* output = fopen ( name, "w" );
    ASSERT ( ( output != NULL ) && ( HASH != NULL ) && ( ( HASH -> LIST ) != NULL ) );

    if ( output == NULL )
    {
        printf ( "ERROR: Can't open the file: '%s'\n", name );
        return ERROR;
    }

    ASSERT ( output != NULL );

    int i = 0;
    for( ; i < MAX_VALUE_OF_HASH; i++)
    {

        char* data = NULL;

        while ( ( ( ( HASH -> LIST ) [ i ] ) -> size ) >= 1 )
        {
            data = LIST_deleteEnd ( ( HASH -> LIST ) [ i ] );

            fprintf ( output, "%s\t", data );
        }
        fprintf( output, "\n" );

        LIST_destructer ( HASH -> LIST [i] );
    }
    free ( output );
    return OK;
}
