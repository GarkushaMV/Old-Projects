
    //!variable
    op ( var,  1,  TREE -> func = 0; TREE -> number = 1 )
    //!left bracket
    op ( lbr,  2, )
    //!right bracket
    op ( rbr,  3, )
    //!subtraction
    op ( sub,  4,  derivate ( TREE -> left, output ); derivate ( TREE -> right, output ) )
    //!addition
    op ( add,  5,  derivate ( TREE -> left, output ); derivate ( TREE -> right, output ) )
    //!multiplication
    op ( mult, 6,  derivate_MULT ( TREE, output ) )
    //!diveision
    op ( dive, 7,  derivate_DIV  ( TREE, output ) )
    //!powering to degree
    op ( pow,  8,  derivate_POW  ( TREE, output ) )
    //!linear logarithm
    op ( ln,   9,  derivate_LN   ( TREE, output ) )
    //!sinus
    op ( sin,  10, derivate_SIN  ( TREE, output ) )
    //!cosinus
    op ( cos,  11, derivate_COS  ( TREE, output ) )

    /*
    op ( tg )
    op ( exp )
    op ( arcsin )
    op ( arccos )
    op ( arctg )
    op ( arcctg )
    op ( ctg )
    */
