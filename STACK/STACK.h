#ifdef DEBUG
    #define ASSERT(cond) if (!(cond))\
                   {\
                       printf("FAIL: %s, in %s, %d, %s\n",\
                       #cond, __FILE__, __LINE__, __PRETTY_FUNCTION__);\
                       exit(3);\
                   }
#else
    #define ASSERT ;
#endif



#define type_t int



enum{ ERROR = 0, OK = 1 };

enum{ MAX_SIZE = 1023 };

enum{ FALSE = 0, TRUE = 1 };



struct stack_t
{
    type_t* data;
    int maxsize;
    int top;
};





//!logging information
int STACK_dump ( struct stack_t *STACK )
{
    printf ( "\nDump stack information:\n" );
    printf ( "Maximum of elements: %d\n", ( STACK -> maxsize ) );
    printf ( "Number of elements in stack: %d\n", ( STACK -> top ) );
    int i = 0;
    for ( ; i <= ( STACK -> top ); i++)
        printf("Element %d:\t%d\n", i, ( ( STACK -> data ) [i] ));
    system ( "pause" );
    return OK;
}



//!Cheking stack
int STACK_ok ( struct stack_t *STACK )
{
    if(
            STACK -> top     <  0                   ||        \
            STACK -> top     >  STACK -> maxsize    ||        \
            STACK -> data    == NULL                ||        \
            STACK -> maxsize >  MAX_SIZE            ||        \
            STACK            == NULL                          \
      )
      {
            STACK_dump( STACK );
            return FALSE;
      }

    else
            return TRUE;

}


//!Create stack
struct stack_t* STACK_constructer ()
{
    struct stack_t *STACK = ( struct stack_t* ) malloc ( sizeof ( struct stack_t ) );
    STACK -> top     = 0;
    STACK -> data    = ( type_t* )  calloc ( MAX_SIZE, sizeof ( type_t ) );
    STACK -> maxsize = MAX_SIZE;

    return STACK;
}



//!Destroy stack
int STACK_destructer ( struct stack_t *STACK )
{
    ASSERT ( STACK_ok( STACK ) );

    free ( STACK->data );
    free ( STACK );

    STACK = NULL;

    return OK;

}


//!Deleting element
type_t STACK_pop ( struct stack_t *STACK )
{
    ASSERT ( STACK_ok ( STACK ) );

    type_t information = ( STACK -> data )[ ( STACK -> top ) ];

    ( STACK -> data )[ ( STACK -> top ) ] = 0;

    ( STACK -> top )--;

    ASSERT ( STACK_ok ( STACK ) );

    return information;
}


//!Adding new element
int STACK_push ( struct stack_t *STACK,   type_t element )
{
    ASSERT ( STACK_ok ( STACK ) );

    ( STACK -> top )++;
    ( STACK -> data )[ ( STACK -> top ) ]     =   element;

    ASSERT( STACK_ok ( STACK ) );
    return OK;
}



//! direct insert in output
type_t STACK_popO ( FILE* output, struct stack_t *STACK )
{
    fprintf ( output, "%d\n", STACK_pop ( STACK ) );
    return OK;
}



