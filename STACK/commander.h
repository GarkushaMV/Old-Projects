    //!COMMANDS MUST BE ISALPHA-CORRECT, that's mean, than they consist only of latin characters.

    DEF_CMD ( EXT,   0,   return OK;)


    DEF_CMD ( OUT,   901, STACK_popO ( output, CPU -> STACK ) )


    DEF_CMD ( PUSHC, 902, a = 0; scanf ( "%d", &a); STACK_push ( CPU -> STACK, a ) )


    DEF_CMD ( CLON,  903, a = STACK_pop ( CPU -> STACK );  STACK_push ( CPU -> STACK, a );  STACK_push ( CPU -> STACK, a ); )


    DEF_CMD ( MARK,  1000, )


    DEF_CMD ( POP,   909,   STACK_pop ( CPU->STACK ) )


    DEF_CMD ( RGO,   2,   ++position; STACK_push ( CPU -> STACK, REGISTER_pop ( buff [ position ], CPU ) ) )


    DEF_CMD ( PUSH,  3,   ++position; STACK_push ( CPU -> STACK, buff [ position ] )  )


    DEF_CMD ( PUSHR, 4,   ++position; REGISTER_push ( STACK_pop( CPU -> STACK ), buff [ position ], CPU ) )


    DEF_CMD ( ADD,   910,  init STACK_push ( CPU -> STACK, a + b ) )


    DEF_CMD ( SUB,   911,  init STACK_push ( CPU -> STACK, a - b ) )


    DEF_CMD ( MULT,  912,  init STACK_push ( CPU -> STACK, a * b ) )


    DEF_CMD ( DIV,   913,  init STACK_push ( CPU -> STACK, ( a / b ) ) )


    DEF_CMD ( SIN,   914,  STACK_push ( CPU -> STACK, sin ( STACK_pop( CPU -> STACK ) ) ) )


    DEF_CMD ( SQRT,  915,  STACK_push ( CPU -> STACK, sqrt ( STACK_pop( CPU -> STACK ) ) ) )


    DEF_CMD ( JMP,   1001, position++; position = buff [ position ] )


    DEF_CMD ( JB,    1002, init ret position++; if ( a >  b ) position = buff [position] )


    DEF_CMD ( JBE,   1003, init ret position++; if ( a >= b ) position = buff [position] )


    DEF_CMD ( JLE,   1004, init ret position++; if ( a <= b ) position = buff [position] )


    DEF_CMD ( JL,    1005, init ret position++; if ( a <  b ) position = buff [position] )


    DEF_CMD ( JE,    1006, init ret position++; if ( a == b ) position = buff [position] )


    DEF_CMD ( JNE,   1007, init ret position++; if ( a != b ) position = buff [position] )


    DEF_CMD ( CALL,  2007, STACK_push ( STACK_CALL, ( position + 1 ) ); position = buff [ ( position + 1 ) ] - 1 )


    DEF_CMD ( RTRN,  999,  position = STACK_pop ( STACK_CALL ) )
