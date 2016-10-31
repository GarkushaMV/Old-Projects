#define tree struct tree_t
#define type_t union data
#define oper enum oper_t


enum oper_t
{
    #define op(func, number, code) num_##func = number,
    #include "functions.h"
    #undef op
    DIVIDEBYZERO
};

enum { OK = 0, ERROR = 1 };

union data
{
    double number;
    oper func;
};

struct tree_t
{
    union
    {
        double number;
        oper func;
    };
    tree* left;
    tree* right;
};



tree* TREE_constructer ()
{
    tree* TREE = ( tree* ) calloc ( 1, sizeof ( tree ) );
    ASSERT ( TREE );
    return TREE;
}



int TREE_destructer ( tree* TREE )
{
    if  (TREE == NULL           ||
         TREE -> left  != NULL  ||
         TREE -> right != NULL )
        return ERROR;
    free ( TREE );
    return OK;
}



//!work now for type_t = union data
void TYPE_T_add ( tree* TREE, const type_t data )
{
    TREE -> number = data. number;
    TREE -> func   = data. func;
}



void TREE_addLeft ( tree* TREE, const type_t data, tree* LEFT, tree* RIGHT )
{
    ASSERT ( TREE );
    TREE -> left = TREE_constructer();
    TYPE_T_add ( TREE -> left, data );
    TREE -> left -> left = LEFT;

}



void TREE_addRight ( tree* TREE, const type_t data )
{
    ASSERT ( TREE );
    TREE -> right = TREE_constructer();
    TYPE_T_add ( TREE -> right, data );
}



int TREE_delete ( tree* TREE );



int TREE_delete_leafs ( tree* TREE )
{
    ASSERT ( TREE );
    int condition = 0;
    if( TREE -> left != NULL )
        condition = ( condition || TREE_delete ( TREE -> left ) );
    TREE -> left = NULL;

    if( TREE -> right != NULL )
        condition = ( condition || TREE_delete ( TREE -> right ) );
    TREE -> right = NULL;

    return condition;
}



int TREE_delete ( tree* TREE )
{
    ASSERT ( TREE );
    int condition = TREE_delete_leafs ( TREE );
    condition = ( condition || TREE_destructer ( TREE ) );
    return condition;
}



tree* TREE_copy ( tree* TREE )
{
    ASSERT ( TREE );

    tree* COPY = TREE_constructer();
    COPY -> number = TREE -> number;
    COPY -> func   = TREE -> func;

    if ( TREE -> left != NULL )
        COPY -> left  = TREE_copy ( TREE -> left );

    if ( TREE -> right != NULL )
        COPY -> right = TREE_copy ( TREE -> right );
    return COPY;
}



void TREE_dump ( tree* TREE )
{
    ASSERT ( TREE );
    printf ( "\nAdress: %p\t", TREE );
    if ( TREE -> func == 0 )
        printf ( "Number: %lg\n", TREE -> number );
    else
        printf ( "Function: %d\n", TREE -> func );
    printf ( "Left adress: %p,   Right adress: %p\n", TREE -> left, TREE -> right );
    system ("pause");
    if ( TREE -> left != NULL )
        TREE_dump ( TREE -> left );
    if ( TREE -> right != NULL )
        TREE_dump ( TREE -> right );
}



int TREE_compare ( tree* ONE, tree* TWO )
{
    if ( ONE != NULL && TWO != NULL )
    {
        if ( ONE -> func == TWO -> func )
        {
            if ( ONE -> func == 0 )
            {
                if ( ONE -> number == TWO -> number )
                    return 1;
                else
                    return 0;
            }
            else
            {
                if ( ( TREE_compare ( ONE -> left, ONE -> right ) &&
                       TREE_compare ( TWO -> left, TWO -> right ) )
                       ||
                     ( ONE -> func != num_dive &&
                      TREE_compare ( ONE -> left, TWO -> right ) &&
                      TREE_compare ( TWO -> left, ONE -> right ) ) )
                    return 1;
                else
                    return 0;
            }
        }
        else
            return 0;
    }
    else if ( ONE != NULL )
        return 0;
    else if ( TWO != NULL )
        return 0;
    else
        return 1;
}
