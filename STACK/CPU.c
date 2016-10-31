#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "CPU.h"

#define init a = STACK_pop( CPU -> STACK );  b = STACK_pop( CPU -> STACK );
#define ret  STACK_push ( CPU -> STACK, b ); STACK_push ( CPU -> STACK, a );



enum { MAX_COMMANDS = 100500 };


enum commands_t
{
    #define DEF_CMD(name, num, code) CMD_##name = num,
    #include "commander.h"
    #undef DEF_CMD
    CMD_MAX
};


int* ReadCommands ( const char name[] );


int  LetsDoThis   ( int* buff, const char name[] );


int main()
{
    int* buff = ReadCommands ( "machine.txt" );
    if ( buff == NULL )
        return 0;

    if( LetsDoThis ( buff, "result.txt" ) == 0 )
        return 0;
    else
    {
        printf ("ERROR: Wrong command!\n");
        system ("pause");
        return 0;
    }

}



int* ReadCommands ( const char name[] )
{
    FILE* input = fopen ( name, "r" );
    if ( input == NULL )
    {
        printf ( "ERROR: Can't open the file: '%s'\n", name );
        return ERROR;
    }

    int *buff = ( int* ) calloc ( MAX_COMMANDS, sizeof ( int ) );
    ASSERT ( buff != NULL );

    int length = 0;
    while ( !feof(input) )
        fscanf ( input, "%d", &buff [ length++ ] );

    fclose ( input );
    return buff;
}



int LetsDoThis ( int* buff, const char name[] )
{
    FILE* output = fopen ( name, "w" );
    struct cpu_t   *CPU        = CPU_constructer ( );
    struct stack_t *STACK_CALL = STACK_constructer ( );
    int position = 0;
    while ( buff [ position ] != 0 )
    {
        switch ( buff [ position ] )
        {
            int a = 0, b = 0;
            #define DEF_CMD(name, num, code) case CMD_##name: code; break;
            #include "commander.h"
            #undef DEF_CMD
            default:
                break;
        }
        position++;
    }
    CPU_destructer(CPU);
    return 0;
}
