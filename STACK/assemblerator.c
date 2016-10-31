#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>



enum { ERROR = -1, OK = 1 };


int  translator ( const char input_file_name[], const char output_file_name[]);


int  ReadCommand ( int* position, FILE* input, FILE* output, int* marks);


int* Marker ( FILE* input );



int main()
{
    int x = translator ( "assembler.txt", "machine.txt" );
    if ( x == ERROR )
        printf ( "WRONG COMMAND!" );
    return 0;
}



int translator ( const char input_file_name[], const char output_file_name[])
{
    int* marks = ( int* ) calloc ( 100, sizeof ( int ) );
    FILE* input = fopen ( input_file_name, "r" );
    if ( input == NULL )
        return ERROR;
    FILE* output = fopen ( output_file_name, "w" );
    int position = 0;
    marks = Marker ( input );
    fclose ( input );
    input = fopen ( input_file_name, "r" );
    while ( !feof ( input ) )
        ReadCommand ( &position, input, output, marks );
    return OK;
}



int ReadCommand ( int* position, FILE* input, FILE* output, int* marks)
{
    char text[64] = "a";
    int command = -1;
    int data = 0;
    fscanf( input, "%s", text);
    #define DEF_CMD(name, num, code)  if( strcmp( text, #name ) == 0 ) command = num;
    #include "commander.h"
    #undef DEF_CMD

    if ( command == -1)
        return ERROR;
    else if ( command == 1000)
    {
        (*position)++;
        fscanf ( input, "%*d" );
    }
    else if ( command == 0 )
        fprintf ( output, "0" );
    else if ( command > 0 );
    {
        fprintf ( output, "%d ", command);
        if ( command > 1000 )
        {
            fscanf  ( input, "%*c%d", &command );
            fprintf ( output, "%d", marks [command] );
            (*position)++;
        }
        else if ( command < 900 )
        {
            fscanf  ( input,  "%d",  &data );
            fprintf ( output, "%d", data );
            (*position)++;
        }
    }

    fprintf ( output, "\n" );
    (*position)++;
    return OK;
}



int* Marker ( FILE* input )
{
    char text[64] = "a";
    int much_marks = 0;
    int* marks = ( int* ) calloc ( 100, sizeof ( int ) );
    int position = 0, command = 0;
    for (; !feof ( input ); position++ )
    {
        fscanf( input, "%s", text);
        if ( !strcmp ( text, "MARK") )
        {
            fscanf  ( input,  "%d",  &command );
            marks [ command ] = position - much_marks +1;
            much_marks += 2;
            position++;
        }
    }
    return marks;
}
