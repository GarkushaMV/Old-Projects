//uses "tree.h" & <string.h>

tree* mult_div   ( type_t* buff, int* position, int length );

tree* add_sub    ( type_t* buff, int* position, int length );

tree* degree     ( type_t* buff, int* position, int length );

tree* functions  ( type_t* buff, int* position, int length );

tree* bracket    ( type_t* buff, int* position, int length );

tree* number_var ( type_t* buff, int* position, int length );



tree* add_sub ( type_t* buff, int* position, int length )
{
    if ( *position == length )
        return NULL;
    tree* TREE = mult_div ( buff, position, length );
    while (  *position != length && ( buff [ *position ]. func == num_add  ||
             buff [ *position ]. func == num_sub ) )
        {
            tree* foo_TREE    = TREE_constructer();
            foo_TREE -> left  = TREE;
            TREE              = foo_TREE;
            TREE -> func = buff [ *position ]. func;
            ( *position )++;
            TREE -> right = mult_div( buff, position, length );
        }
    return TREE;
}



tree* mult_div ( type_t* buff, int* position, int length )
{
    if ( *position == length )
        return NULL;
    tree* TREE = degree ( buff, position, length );
    while ( *position != length && ( buff [ *position ]. func == num_mult ||
                                     buff [ *position ]. func == num_dive ) )
        {
            tree* foo_TREE    = TREE_constructer();
            foo_TREE -> left  = TREE;
            TREE              = foo_TREE;
            TREE -> func = buff [ *position ]. func;
            ( *position )++;
            TREE -> right = degree( buff, position, length );
        }
    return TREE;
}



tree* degree   ( type_t* buff, int* position, int length )
{
    if ( *position == length )
        return NULL;
    tree* TREE = bracket ( buff, position, length );
    while ( *position != length && buff [ *position ]. func == num_pow )
        {
            tree* foo_TREE    = TREE_constructer();
            foo_TREE -> left  = TREE;
            ( *position )++;
            foo_TREE -> right = bracket( buff, position, length );
            TREE              = foo_TREE;
            TREE -> func      = num_pow;
        }
    return TREE;
}



tree* functions ( type_t* buff, int* position, int length )
{
    if ( *position == length )
        return NULL;
    tree* TREE = NULL;
    if ( buff [ *position ]. func == num_sin ||
         buff [ *position ]. func == num_ln  ||
         buff [ *position ]. func == num_cos )
    {
        TREE = TREE_constructer();
        TREE -> func = buff [ *position ]. func;
        ( *position )++;
        TREE -> left = bracket ( buff, position, length );
    }
    else
        TREE = number_var ( buff, position, length );
    return TREE;
}



tree* bracket   ( type_t* buff, int* position, int length )
{
    if ( *position == length )
        return NULL;
    tree* TREE = NULL;
    if ( buff [ *position ]. func == num_lbr )
    {
        ( *position )++;
        TREE = add_sub ( buff, position, length );
        ASSERT ( buff [ *position ]. func == num_rbr );
        ( *position )++;
    }
    else
        TREE = functions ( buff, position, length );

    return TREE;
}



tree* number_var   ( type_t* buff, int* position, int length )
{
    if ( *position == length )
        return NULL;
    tree* TREE = TREE_constructer();
    if ( buff [ *position ]. func == num_var)
    {
        TREE -> func = num_var;
        (*position)++;
    }
    else if( buff [ *position ]. func == 0 )
    {
        TREE -> number = buff [ *position ]. number;
        (*position)++;
    }
    else
        ASSERT ( 0 );
    return TREE;
}
