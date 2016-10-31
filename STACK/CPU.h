#include "STACK.h"

struct register_t
{
    type_t ax;
    type_t bx;
    type_t cx;
    type_t dx;
};

struct cpu_t
{
    struct register_t* REG;
    struct stack_t* STACK;
};


int REGISTER_dump ( struct register_t *REG )
{
    printf ( "ax: %d\n", REG -> ax );
    printf ( "bx: %d\n", REG -> bx );
    printf ( "cx: %d\n", REG -> cx );
    printf ( "dx: %d\n", REG -> dx );
    return OK;
}



int CPU_dump ( struct cpu_t *CPU )
{
    printf ( "\n\n...Dump CPU information...\n" );
    printf ( "adress of CPU = %p\n", CPU);
    printf ( "\nDumping register:\n");
    ASSERT ( REGISTER_dump ( CPU -> REG ) );
    ASSERT ( STACK_dump ( CPU -> STACK ) );
    system ( "pause" );
    system ( "cls" );
    return OK;
}



struct register_t* REGISTER_constructer ()
{
    struct register_t *REG = ( struct register_t* ) malloc ( sizeof ( struct register_t ) );
    REG -> ax = 0;
    REG -> bx = 0;
    REG -> cx = 0;
    REG -> dx = 0;
    return REG;
}



struct cpu_t* CPU_constructer ( )
{
    struct cpu_t* CPU = ( struct cpu_t* ) malloc ( sizeof ( struct cpu_t ) );
    CPU -> STACK = STACK_constructer ();
    CPU -> REG = REGISTER_constructer ();

    return CPU;
}



int CPU_destructer ( struct cpu_t *CPU )
{
    STACK_destructer ( CPU -> STACK );
    free             ( CPU -> REG );
    free ( CPU );
    return OK;
}



int CPU_ok ( struct cpu_t *CPU )
{
    if ( !STACK_ok ( CPU -> STACK ) || \
          CPU -> REG == NULL           \
        )
        return ERROR;
    else
        return OK;
}



int REGISTER_push ( int element, int pos, struct cpu_t *CPU )
{
    switch (pos)
        {
        case 1:
            {
                CPU -> REG -> ax = element;
                break;
            }
        case 2:
            {
                CPU -> REG -> bx = element;
                break;
            }
        case 3:
            {
                CPU -> REG -> cx = element;
                break;
            }
        case 4:
            {
                CPU -> REG -> dx = element;
                break;
            }
        default:
            {
                ASSERT ( FALSE );
            }
        }
    return OK;
}



int REGISTER_pop ( int pos, struct cpu_t *CPU )
{
    switch (pos)
        {
        case 1:
                return CPU -> REG -> ax;
        case 2:
                return CPU -> REG -> bx;
        case 3:
                return CPU -> REG -> cx;
        case 4:
                return CPU -> REG -> dx;
        default:
                ASSERT ( FALSE );
        }
}



