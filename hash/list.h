//! The const values returned if result is false or true in comporators and StrcmpReverse
enum { FALSE = -1, TRUE = 1 };

//! Max length of buff, which given by calloc, there are about 2^30 - 1 bytes, or 1 gigabytes.
enum { MAX_LENGTH = 1073741823 };

//! NOT_FATAL_ERROR - wrong reading of file, FATAL_ERROR = assert.
enum { NOT_FATAL_ERROR = 0, FATAL_ERROR = 3 };



//! define ASSERT
#ifdef DEBUG
    #define ASSERT(cond) /* debug output */  if ( !( cond ) )                   \
                        {                                                       \
                            printf( "FAIL: %s, in %s, %d, %s\n",                \
                            #cond, __FILE__, __LINE__, __PRETTY_FUNCTION__ );   \
                            exit( FATAL_ERROR );                                \
                        }
#else                    //! normal output
    #define ASSERT(cond) (cond);
#endif


//!!!!!!!!!!!!!!!!!! Naming of type_t
#define type_t char*



enum { MIN_VALUE_OF_HASH = 0, MAX_VALUE_OF_HASH = 5 };



//! ERROR - The const value returned if result is incorrect
//! OK    - The const value returned if result is correct and procedure is done
enum { ERROR = -1, OK = 1 };

struct node_t
{
    struct node_t *next;
    struct node_t *prev;
    type_t data;
};


struct list_t
{
    struct node_t *first;
    struct node_t *last;
    int size;
};



int LIST_dump( struct list_t* LIST )
{
    struct node_t *NODE = LIST -> first;
    int i = 0;
    printf ( "LIST = %p\n", LIST );
    if ( LIST != NULL )
    {
        printf ( "LIST -> first = %p\n", LIST -> first );
        printf ( "LIST -> last = %p\n",  LIST -> last );
        printf ( "LIST -> size = %d\n",  LIST -> size );
        while ( NODE != NULL )
        {
            printf ( "# %d\n ", i);
            printf ( "string: \"%s\"\t", NODE -> data );
            printf ( "\nadress = %p\t",    NODE );
            printf ( "adress_next = %p\t", NODE -> next );
            printf ( "adress_prev = %p\n", NODE -> prev );
            i++;
            NODE = NODE->next;
        }
    }
    system ( "pause" );
    system("cls");
    return OK;
}



int LIST_ok ( struct list_t* LIST )
{
    if ( LIST == NULL || LIST -> size <= 0 || \
         LIST -> first == NULL || LIST -> last == NULL )
    {
        LIST_dump ( LIST );
        return ERROR;
    }
    else
        return OK;
}



struct list_t* LIST_constructer ()
{
    struct list_t* LIST = ( struct list_t* ) calloc ( 1, sizeof ( struct list_t ) );
    LIST -> first = NULL;
    LIST -> last  = NULL;
    LIST -> size = 0;
    return LIST;
}



int LIST_destructer ( struct list_t* LIST )
{
    LIST -> first = NULL;
    LIST -> last = NULL;
    LIST -> size = 0;
    return OK;
}



int LIST_addEnd ( struct list_t* LIST, type_t element )
{
    ASSERT ( LIST != NULL )

    struct node_t *NODE = ( struct node_t* ) malloc ( sizeof ( struct node_t ) );
    if( LIST -> size == 0 )
    {
        LIST -> last = NODE;
        LIST -> first = NODE;
        NODE -> next = NULL;
        NODE -> prev = NULL;
    }
    else
    {
        NODE -> prev = LIST -> last;
        ( LIST -> last ) -> next = NODE;
        LIST -> last = NODE;
        NODE -> next = NULL;
    }

    NODE -> data = element;
    ( LIST -> size )++;
    return 0;
}



int LIST_addBegin ( struct list_t* LIST, type_t element )
{
    ASSERT ( LIST != NULL );
    struct node_t *NODE = ( struct node_t* ) malloc ( sizeof ( struct node_t ) );

    if( LIST -> size == 0 )
    {
        LIST -> last = NODE;
        LIST -> first = NODE;
        NODE -> next = NULL;
        NODE -> prev = NULL;
    }
    else
    {
        NODE -> next = LIST -> first;
        ( LIST -> first ) -> prev = NODE;
        LIST -> first = NODE;
        NODE -> prev = NULL;
    }
    NODE -> data = element;
    ( LIST -> size )++;
    return 0;
}



type_t LIST_deleteBegin ( struct list_t* LIST )
{
    ASSERT ( LIST != NULL );
    ASSERT ( LIST -> size > 0 );

    type_t data = ( LIST -> first ) -> data;
    if ( LIST -> size == 1 )
    {
        free ( LIST -> first );
        LIST -> first = NULL;
        LIST_destructer ( LIST );
    }
    else
    {
        LIST -> first = ( LIST -> first )-> next;
        LIST_dump( LIST );
        ASSERT ( LIST -> first );
        ASSERT ( ( LIST -> first ) -> prev );

        free ( ( LIST -> first ) -> prev );
        ( LIST -> first ) -> prev = NULL;

        ( LIST -> size )--;
    }
    return data;
}



type_t LIST_deleteEnd ( struct list_t* LIST )
{
    ASSERT ( LIST != NULL );
    ASSERT ( LIST -> size > 0 );

    type_t data = LIST -> last -> data;

    if ( ( LIST -> size ) == 1 )
    {
        free ( LIST -> last );
        LIST -> last = NULL;
        LIST_destructer ( LIST );
    }
    else
    {
        LIST -> last = ( LIST -> last ) -> prev;

        free ( ( LIST -> last ) -> next );
        ( LIST -> last ) -> next = NULL;

        ( LIST -> size )--;
    }
    return data;
}


