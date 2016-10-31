#include <stdio.h>
#include <stdlib.h>
#include <io.h>

enum { ERROR = 0 };

double N ( char* buff, int* position );

double P ( char* buff, int* position );

double E ( char* buff, int* position );

double T ( char* buff, int* position );

int ReadString ( const char name[], char* buff[]);



int main()
{
    char* buff = NULL;
    int length = ReadString ( "input.txt", &buff);
    int *position = ( int* ) calloc ( 1, sizeof ( int ) );
    double e = E ( buff, position );
    if ( length == ( *position + 2 ) )
        printf ( "%lg", e );
    else
        printf ( "INCORRECT LINE" );
    return 0;
}


int ReadString ( const char name[], char* buff[] )
{
    int* length = ( int* ) calloc ( 1, sizeof ( int ) );

    FILE* input = fopen ( name, "r" );
    if ( input == NULL )
    {
        printf ( "ERROR: Can't open the file: '%s'\n", name );
        exit ( ERROR );
    }

    //! length of input file
    *length =  filelength ( fileno ( input ) );
    if ( length == 0 )
    {
        printf ( "ERROR: Input file is empty\n" );
        exit ( ERROR );
    }

    *buff = ( char* ) calloc ( ( ( *length ) + 1 ) , sizeof( char ) );

    fread ( *buff, *length, sizeof(unsigned char), input );

    (*buff) [ ( *length ) ] = '\0';
    fclose ( input );
    return *length;
}



double N ( char* buff, int* position )
{
    double n = 0;
    while ( buff [ *position ] == ' ' )
        ( *position )++;
    while ( buff [ *position ] >= '0' && buff [ *position ] <= '9' )
    {
        n = n*10 + buff [ *position ] - '0';
        ( *position )++;
    }
    if ( buff [ *position ] == '.' || buff [ *position ] == ',' )
    {
        int mant = 0;
        for ( ( *position )++; buff [ *position ] >= '0' && buff [ *position ] <= '9'; mant++ )
        {
            n = n*10 + buff [ *position ] - '0';
            ( *position )++;
        }
        for ( ; mant > 0; mant-- )
            n/=10;
    }
    while ( buff [ *position ] == ' ' )
        ( *position )++;
    return n;
}



double P ( char* buff, int* position )
{
    while ( buff [ *position ] == ' ' )
        ( *position )++;
    double p = 0;
    if ( buff [ *position ] == '(' )
    {
        ( *position )++;
        while ( buff [ *position ] == ' ' )
            ( *position )++;
        p = E ( buff, position );
        if ( buff [ *position ] == ')' )
        {
            ( *position )++;
            while ( buff [ *position ] == ' ' )
                ( *position )++;
        }
    }
    else
        p = N ( buff, position );

    return p;
}



double T ( char* buff, int* position )
{
    while ( buff [ *position ] == ' ' )
        ( *position )++;
    double t = P ( buff, position );
    while ( ( buff [ *position ] == '*' ) || ( buff [ *position ] == '/' ) )
    {
        while ( buff [ *position ] == ' ' )
            ( *position )++;
        if ( buff [ *position ] == '*' )
        {
            ( *position )++;
            t *= P ( buff, position );
        }
        else if ( buff [ *position ] == '/' )
        {
            ( *position )++;
            t /= P ( buff, position );
        }
    }
    return t;
}



double E ( char* buff, int* position )
{
    while ( buff [ *position ] == ' ' )
            ( *position )++;
    double e = T ( buff, position );
    while ( ( buff [ *position ] == '+' ) || ( buff [ *position ] == '-' ) )
    {
        while ( buff [ *position ] == ' ' )
            ( *position )++;
        if ( buff [ *position ] == '+' )
        {
            ( *position )++;
            e += T ( buff, position );
        }
        else if ( buff [ *position ] == '-' )
        {
            ( *position )++;
            e -= T ( buff, position );
        }
    }
    return e;
}
