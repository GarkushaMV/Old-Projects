//uses "tree.h" & <math.h>
#define LEFT TREE -> left
#define RIGHT TREE -> right
#define type -> func

void derivate_MULT ( tree* TREE, FILE* output );

void derivate_DIV  ( tree* TREE, FILE* output );

void derivate_SIN  ( tree* TREE, FILE* output );

void derivate_COS  ( tree* TREE, FILE* output );

void derivate_POW  ( tree* TREE, FILE* output );

void derivate_LN   ( tree* TREE, FILE* output );

void simplify      ( tree* TREE );


void derivate ( tree* TREE, FILE* output )
{
    switch ( ( TREE -> func ) )
    {
    #define op( arg, num, code ) case num:  code; break;
        #include "functions.h"
    #undef op
    default:
        TREE -> number = 0;
        break;
    }
}



void derivate_MULT ( tree* TREE, FILE* output )
{
    fprintf ( output, "Используем формулу Лагранжа для производной произведения:\n\n$$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");

    tree* foo_TREE = TREE_copy ( TREE );
    TREE_delete ( LEFT );
    LEFT = foo_TREE;
    TREE_delete ( RIGHT );
    RIGHT = TREE_copy ( foo_TREE );
    TREE -> func = num_add;
    foo_TREE = NULL;

    fprintf ( output, "Далее для производной данного выражения найдём производную от \n\n$$ ");
    TREE_print ( LEFT -> left, output );
    fprintf ( output, " $$\n\n");
    derivate ( LEFT -> left, output );

    fprintf ( output, "Также найдём производную от \n\n$$ ");
    TREE_print ( RIGHT -> right, output );
    fprintf ( output, " $$\n\n");
    derivate ( RIGHT -> right, output );

    fprintf ( output, "Получаем для данного логарифмического выражения производную: \n\n$$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");
}



void derivate_DIV ( tree* TREE, FILE* output )
{
    fprintf ( output, "Используем формулу Лагранжа для производной частного двух функций:\n\n $$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");

    TREE -> func = num_mult;
    tree* foo_TREE = TREE_copy ( TREE );
    TREE_delete ( LEFT );
    LEFT = TREE_constructer ();
    LEFT -> left = foo_TREE;
    LEFT -> right = TREE_copy ( foo_TREE );
    LEFT -> func = num_sub;

    TREE -> func = num_dive;
    foo_TREE = RIGHT;
    RIGHT = TREE_constructer ();
    RIGHT -> func = num_pow;
    RIGHT -> left = foo_TREE;
    RIGHT -> right = TREE_constructer ();
    RIGHT -> right -> number = 2;

    fprintf ( output, "Далее найдём производную от \n\n$$ ");
    TREE_print ( LEFT -> left  -> left, output );
    fprintf ( output, " $$\n\n");
    derivate ( LEFT -> left  -> left, output  );

    fprintf ( output, "Также найдём производную от \n\n$$ ");
    TREE_print ( LEFT -> right -> right, output );
    fprintf ( output, " $$\n\n");
    derivate ( LEFT -> right -> right, output );

    fprintf ( output, "Получаем для данного логарифмического выражения производную: \n\n$$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");
}



void derivate_SIN ( tree* TREE, FILE* output )
{
    fprintf ( output, "Используем формулу производной синуса для функции:\n\n $$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");

    ASSERT ( TREE );
    ASSERT ( !( RIGHT ) );

    TREE -> func = num_cos;
    RIGHT = TREE_copy ( TREE );
    TREE -> func = num_mult;

    fprintf ( output, "Далее найдём производную от \n\n$$");
    TREE_print ( LEFT, output );
    fprintf ( output, " $$\n\n");
    derivate ( LEFT, output );

    fprintf ( output, "Получаем для данного логарифмического выражения производную: \n\n$$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");
}



void derivate_COS ( tree* TREE, FILE* output )
{
    fprintf ( output, "Используем формулу производной косинуса для функции:\n\n $$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");

    ASSERT ( TREE );
    ASSERT ( !( RIGHT ) );
    TREE -> func  = num_sin;
    RIGHT = TREE_constructer();
    RIGHT -> left = TREE_copy ( TREE );
    TREE_destructer ( RIGHT -> left -> right );
    RIGHT -> left -> right = NULL;
    RIGHT -> func  = num_mult;
    RIGHT -> right = TREE_constructer();
    RIGHT -> right -> number = -1;
    TREE -> func  = num_mult;

    fprintf ( output, "Далее найдём производную от \n\n$$");
    TREE_print ( LEFT, output );
    fprintf ( output, " $$\n\n");
    derivate ( LEFT, output );

    fprintf ( output, "Получаем для данного логарифмического выражения производную: \n\n$$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");
}



void derivate_POW ( tree* TREE, FILE* output )
{
    fprintf ( output, "Используем формулу производной косинуса для функции:\n\n $$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");

    tree* foo_TREE   = TREE_copy ( TREE );
    TREE_delete_leafs ( TREE );
    RIGHT            = foo_TREE;
    TREE -> func     = num_mult;
    LEFT             = TREE_copy ( foo_TREE );
    LEFT -> func     = num_mult;
    foo_TREE         = TREE_constructer();
    foo_TREE -> left = LEFT -> left;
    foo_TREE -> func = num_ln;
    LEFT -> left     = foo_TREE;

    fprintf    ( output, "Далее найдём производную от \n\n$$");
    TREE_print ( LEFT, output );
    fprintf    ( output, " $$\n\n");
    derivate   ( LEFT, output );

    fprintf ( output, "Получаем для данного логарифмического выражения производную: \n\n$$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");
}



void derivate_LN  ( tree* TREE, FILE* output )
{
    fprintf ( output, "Используем формулу производной логарифмического выражения для функции:\n\n $$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");

    RIGHT = LEFT;
    LEFT  = TREE_copy ( RIGHT );
    TREE -> func  = num_dive;

    fprintf ( output, "Далее найдём производную от \n\n$$");
    TREE_print ( LEFT, output );
    fprintf ( output, " $$\n\n");
    derivate ( LEFT, output );

    fprintf ( output, "Получаем для данного логарифмического выражения производную: \n\n$$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n");
}



void simplify ( tree* TREE )
{
    if( TREE -> func != 0 && TREE -> func != 1 )
    {
        ASSERT ( LEFT );
        simplify ( LEFT );
        if ( TREE -> func < num_ln )
        {
            ASSERT ( RIGHT );
            simplify ( RIGHT );
            if ( ( ( LEFT -> func ) == 0 ) && ( ( RIGHT -> func ) == 0) )
            {
                switch ( TREE -> func )
                {
                    case num_mult : TREE -> number = (LEFT -> number) * (RIGHT -> number);
                                     break;
                    case num_add  : TREE -> number = (LEFT -> number) + (RIGHT -> number);
                                     break;
                    case num_sub  : TREE -> number = (LEFT -> number) - (RIGHT -> number);
                                     break;
                    case num_dive : TREE -> number = (LEFT -> number) / (RIGHT -> number);
                                     break;
                    case num_pow  : TREE -> number = pow ( LEFT -> number, RIGHT -> number );
                                     break;
                    default: ASSERT ( 0 );
                }
                TREE -> func   = 0;
                TREE_delete ( LEFT );
                TREE_delete ( RIGHT );
                LEFT  = NULL;
                RIGHT = NULL;
            }
        }
        else
            if ( LEFT -> func == 0 )
            {
                switch ( TREE -> func )
                {
                    case num_sin: TREE -> number = sin  ( LEFT -> number );
                                  break;
                    case num_ln : TREE -> number = logf ( LEFT -> number );
                                  break;
                    case num_cos: TREE -> number = cos  ( LEFT -> number );
                                  break;
                    default     : ASSERT ( 0 );
                }
                TREE -> func   = 0;
                TREE_delete ( LEFT );
                LEFT = NULL;
            }


        if ( TREE -> func == num_mult )
        {
            if ( ( ( LEFT -> func ) == 0 &&  (LEFT -> number) == 0 ) ||
                                           ( ( RIGHT -> func ) == 0 &&  (RIGHT -> number) == 0 ) )
            {
                TREE_delete_leafs( TREE );
                TREE -> func = 0;
                TREE -> number = 0;
            }

            else if ( ( ( LEFT -> func ) == 0 &&  (LEFT -> number) == 1 ) )
            {
                TREE_delete ( LEFT );
                LEFT = RIGHT -> left;
                TREE -> func = RIGHT -> func;
                TREE -> number = RIGHT -> number;
                tree* foo_TREE = RIGHT -> right;
                RIGHT -> right = NULL;
                RIGHT -> left  = NULL;
                TREE_delete ( RIGHT );
                RIGHT = foo_TREE;
            }

            else if ( ( ( RIGHT -> func ) == 0 &&  (RIGHT -> number) == 1 ) )
            {
                TREE_delete ( RIGHT );
                RIGHT = LEFT -> right;
                TREE -> func = LEFT -> func;
                TREE -> number = LEFT -> number;
                tree* foo_TREE = LEFT -> left;
                LEFT -> right = NULL;
                LEFT -> left  = NULL;
                TREE_delete ( LEFT );
                LEFT = foo_TREE;
            }
        }
        else if ( TREE -> func == num_add || TREE -> func == num_sub )
        {
            if ( ( ( LEFT -> func ) == 0 &&  (LEFT -> number) == 0 ) )
            {
                TREE_delete ( LEFT );
                LEFT = RIGHT -> left;
                TREE -> func = RIGHT -> func;
                TREE -> number = RIGHT -> number;
                tree* foo_TREE = RIGHT -> right;
                RIGHT -> right = NULL;
                RIGHT -> left  = NULL;
                TREE_delete ( RIGHT );
                RIGHT = foo_TREE;
            }

            else if ( ( ( RIGHT -> func ) == 0 &&  (RIGHT -> number) == 0 ) )
            {
                TREE_delete ( RIGHT );
                RIGHT = LEFT -> right;
                TREE -> func = LEFT -> func;
                TREE -> number = LEFT -> number;
                tree* foo_TREE = LEFT -> left;
                LEFT -> right = NULL;
                LEFT -> left  = NULL;
                TREE_delete ( LEFT );
                LEFT = foo_TREE;
            }
        }


        else if ( ( TREE -> func == num_dive ) && ( LEFT -> func ) == 0 && (LEFT -> number) == 0 )
        {
            TREE_delete_leafs( TREE );
            TREE -> func = 0;
            TREE -> number = 0;
        }


        else if ( ( TREE -> func == num_dive ) && ( RIGHT -> func ) == 0 && ( RIGHT -> number ) == 1 )
        {
            TREE_delete ( RIGHT );
            RIGHT = LEFT -> right;
            TREE -> func = LEFT -> func;
            TREE -> number = LEFT -> number;
            tree* foo_TREE = LEFT -> left;
            LEFT -> right = NULL;
            LEFT -> left  = NULL;
            TREE_delete ( LEFT );
            LEFT = foo_TREE;
        }


        else if ( TREE -> func == num_pow )
        {
            if ( ( ( LEFT -> func ) == 0 &&  (LEFT -> number) == 1 ) )
            {
                TREE_delete_leafs( TREE );
                TREE -> func = 0;
                TREE -> number = 1;
            }

            else if ( ( ( RIGHT -> func ) == 0 && (RIGHT -> number) == 1 ) )
            {
                TREE_delete ( RIGHT );
                RIGHT = LEFT -> right;
                TREE -> func = LEFT -> func;
                TREE -> number = LEFT -> number;
                tree* foo_TREE = LEFT -> left;
                LEFT -> right = NULL;
                LEFT -> left  = NULL;
                TREE_delete ( LEFT );
                LEFT = foo_TREE;
            }
            else if ( ( ( RIGHT -> func ) == 0 && (RIGHT -> number) == 0 ) )
            {
                TREE_delete_leafs( TREE );
                TREE -> func = 0;
                TREE -> number = 1;
            }
        }
    }
    if ( RIGHT != NULL && TREE_compare ( LEFT, RIGHT ) )
    {
        ASSERT ( LEFT );
        switch ( TREE -> func )
        {
            case num_mult : TREE -> func = num_pow;
                            TREE_delete ( RIGHT );
                            RIGHT = TREE_constructer();
                            RIGHT -> number = 2;
                                break;
            case num_add  : TREE -> func = num_mult;
                            TREE_delete ( RIGHT );
                            RIGHT = TREE_constructer();
                            RIGHT -> number = 2;
                                break;
            case num_sub  : TREE_delete_leafs ( TREE );
                            TREE -> func = 0;
                            TREE -> number = 0;
                                break;
            case num_dive : TREE_delete_leafs ( TREE );
                            TREE -> func = 0;
                            TREE -> number = 1;
                                break;
            default       :    break;
        }
    }
}



