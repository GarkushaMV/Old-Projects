#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Strread.h"

#define NUMBER_OF_HASH 5
typedef int    *HASH_0;
typedef HASH_0 HASHES();



int headder ( int lines, struct hash_t* HASH, char* output, char** text );


int HASH_table  ( const char name[] );


//! few types of hash
int     HASH_1      ( char* str );


int     HASH_2      ( char* str );


int     HASH_3      ( char* str );


int     HASH_4      ( char* str );


int     HASH_5      ( char* str );

struct hash_t* HASH_constructer();







int main()
{
    HASH_table ( "input.txt" );
    return 0;
}



int HASH_table  ( const char name[] )
{
    int i = 0, lines = 0, condition = OK;

    //! array of lines from the input file
    char** text = Reader ( "Input.txt", &lines );
    if ( text == 0 )
    {
        printf ( "Error: empty file.\n" );
        system ( "Pause" );
        return 0;
    }

    struct hash_t* HASH = HASH_constructer();
    char* outnames[] = { "Output1.txt", "Output2.txt", "Output3.txt", "Output4.txt", "Output5.txt" };

    HASH_0 HASHS[ NUMBER_OF_HASH ] = { HASH_1, HASH_2, HASH_3, HASH_4, HASH_5 };

    for ( i = 0; i < NUMBER_OF_HASH; i++ )
    {
        HASH -> func = HASHS[i];
        condition += headder ( lines, HASH, outnames [ i ], text );
    }
    return condition;
}



int headder ( int lines, struct hash_t* HASH, char* output, char** text )
{
    int i = 0;
    for ( i = 0; i < lines; i++)
        LIST_addEnd ( ( HASH -> LIST ) [ ( HASH -> func ) ( text [ i ] ) ], text [ i ] );
    PrintList ( output, HASH );
    return OK;
}



struct hash_t* HASH_constructer()
{
    struct hash_t* HASH = ( struct hash_t* ) calloc ( 1, sizeof ( struct hash_t* ) );

    HASH -> func = NULL;

    HASH -> LIST = ( struct list_t** ) calloc ( MAX_VALUE_OF_HASH, sizeof ( struct list_t* ) );
    int i = 0;

    for ( ; i< MAX_VALUE_OF_HASH; i++ )
        HASH -> LIST [i] = LIST_constructer();
    return HASH;
}



int HASH_1 ( char* text )
{
    ASSERT ( text != NULL );
    return 1;
}



int HASH_2 ( char* text )
{
    ASSERT ( text != NULL );
    return abs( text [ 0 ] % MAX_VALUE_OF_HASH );
}



int HASH_3 ( char* text )
{
    ASSERT ( text != NULL );
    return ( strlen ( text ) % MAX_VALUE_OF_HASH );
}



int HASH_4 ( char* text )
{
    ASSERT ( text != NULL );
    long long summ = 0;
    int i = 0;
    for ( ; text [ i ] != '\0'; i++ )
        summ += text [ i ];
    return ( summ % MAX_VALUE_OF_HASH );
}



int HASH_5 ( char* text )
{
    ASSERT ( text != NULL );

    int i = 0, HASH = 0, lenght = strlen ( text );

    for ( ; i < lenght; i++ )
        HASH = ( HASH << 1 ) ^ ( abs ( ( int ) text[i] ) );

    return ( abs ( HASH ) % MAX_VALUE_OF_HASH );
}
