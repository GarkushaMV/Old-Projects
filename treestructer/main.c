#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <locale.h>

#ifdef DEBUG
    #define ASSERT(cond) if(!cond) assert ( 0 );
#else
    #define ASSERT(cond) if(cond);
#endif

#include "tree.h"

void TREE_print ( tree* TREE, FILE* output );

#include "derivations.h"
#include "convert.h"



int stringcompare( const char* a, const char* b );

type_t* lexeme ( int* length );

void Printing ( FILE* output );


int main()
{
    //! enables input of russian symbols
    setlocale ( LC_ALL, "Russian" );
    int position = 0, length = 0;

    type_t* lexems = lexeme ( &length );

    ASSERT ( length > 0 );

    tree* TREE = add_sub ( lexems, &position, length );
    free ( lexems );

    FILE* output = fopen ( "Output.tex", "w" );

    Printing ( output );
    TREE_print ( TREE, output );
    fprintf ( output, "$$\n\n}\n\n");
    derivate ( TREE, output );

    fprintf ( output, "\n\nПосле преобразования функции в итоге получили:\n\n$$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n Теперь упростим данное выражение:");
    simplify ( TREE );

    fprintf ( output, "\n\nПолучим финальное выражение:\n\n$$ ");
    TREE_print ( TREE, output );
    fprintf ( output, " $$\n\n }\n\n\\end{document}");
    TREE_delete ( TREE );

    TREE = NULL;
    system("pause");
    return 0;
}



void Printing ( FILE* output )
{
    fprintf ( output, "\\documentclass[12pt]{article}\n\\usepackage{mystyle}\n\\relpenalty=10000\n\\binoppenalty=10000\n\\pagestyle{empty}");
    fprintf ( output, "\n\\newcommand{\\HRule}{\\rule{\\linewidth}{0.5mm}}\n\\DeclareMathOperator{\\Ord}{Ord}\n\\def\\ra{\\rightarrow}\n");
    fprintf ( output, "\\def\\Ra{\\Rightarrow}\n\\def\\ov{\\overline}\n\\def\\ov{\\overline}\n\\begin{document}\n\n{\n\n");
    fprintf ( output, "{\\large \\bfseries \\normalfont \n\n Изначальная формула:\n\n$$ ");
}




int stringcompare( const char* a, const char* b )
{
    int i = 0, cond = 0;
    while ( a[i] != '\0' && b[i]!='\0' && cond == 0 )
    {
        cond = a[i] - b[i];
        i++;
    }
    return cond;
}



type_t* lexeme ( int* length )
{
    char* buff = (char*) calloc ( 1000, sizeof ( char ) );
    int i = 0;
    scanf("%c", &(buff[0]));
    for(; buff [i] != '\n'; i++)
        scanf("%c", &(buff[(i+1)]));
    buff [i] = '\0';
    type_t* lexems = ( type_t* ) calloc ( 1000, sizeof ( type_t ) );
    i = 0;
    (*length) = 0;
    while ( buff [ i ] == ' ' && buff [ i ] != '\0' )
            i++;
    while ( buff [ i ] != '\0')
    {
        int cond = 0;
        #define op(arg, number, code) if(stringcompare(&buff[i], #arg) == 0 && cond == 0) { lexems[ *length ].func = number;                     \
                                                                                             cond = number;                                 \
                                                                                             ASSERT( strlen(#arg)-1 <= strlen ( &(buff[i]) ) );  \
                                                                                             i += strlen(#arg); }
            #include "functions.h"
        #undef op
        if ( cond == 0)
        {
            if ( buff[ i ] == 'x' || buff[ i ] == 'X' )
            {
                lexems[ *length ].func = num_var;
                i++;
            }
            else if ( buff[ i ] == '(' )
            {
                lexems[ *length ].func = num_lbr;
                i++;
            }
            else if ( buff[ i ] == ')' )
            {
                lexems[ *length ].func = num_rbr;
                i++;
            }
            else if ( buff[ i ] == '*' )
            {
                lexems[ *length ].func = num_mult;
                i++;
            }
            else if ( buff[ i ] == '+' )
            {
                lexems[ *length ].func = num_add;
                i++;
            }
            else if ( buff[ i ] == '-' )
            {
                lexems[ *length ].func = num_sub;
                i++;
            }
            else if ( buff[ i ] == '/' )
            {
                lexems[ *length ].func = num_dive;
                i++;
            }
            else if ( buff[ i ] == '^' )
            {
                lexems[ *length ].func = num_pow;
                i++;
            }
            else
                while ( buff[ i ] >= '0' && buff [ i ] <= '9' )
                {
                    lexems[ *length ].number = lexems[ *length ].number * 10 + buff[ i ] - '0';
                    i++;
                }
        }
        ( *length ) ++;
        while ( buff [ i ] == ' ' && buff [ i ] != '\0' )
            i++;
        ASSERT ( i > 1000 );
    }
    free ( buff );
    type_t* foo_lexems = ( type_t* ) calloc ( *length, sizeof ( type_t ) );
    for ( i = 0; i< *length; i++ )
        foo_lexems [ i ] = lexems [ i ];
    free ( lexems );
    return foo_lexems;
}



void TREE_print ( tree* TREE, FILE* output )
{
    if ( TREE -> left != NULL )
    {
        if ( TREE -> right == NULL )
        {
            switch ( TREE -> func )
            {
            case num_sin:
                fprintf ( output, "\\sin(");
                break;
            case num_cos:
                fprintf ( output, "\\cos(");
                break;
            case num_ln :
                fprintf ( output, "\\ln(" );
                break;
            default: ASSERT ( 0 ); break;
            }
            TREE_print ( TREE -> left, output );
            fprintf ( output, ")");
        }
        else
        {
            switch ( TREE -> func )
            {
            case num_dive:
                fprintf ( output, " \\frac{");
                TREE_print ( TREE -> left, output );
                fprintf ( output, "}");
                fprintf ( output, "{");
                TREE_print ( TREE -> right, output );
                fprintf ( output, "} " );
                break;

            case num_mult:
                if ( TREE -> left -> func == num_add || TREE -> left -> func == num_sub )
                    fprintf ( output, "(");
                TREE_print ( TREE -> left, output );
                if ( TREE -> left -> func == num_add || TREE -> left -> func == num_sub )
                    fprintf ( output, ") \\cdot ");
                else
                    fprintf ( output, " \\cdot ");
                if ( TREE -> right -> func == num_add || TREE -> right -> func == num_sub )
                    fprintf ( output, "(");
                TREE_print ( TREE -> right, output );
                if ( TREE -> right -> func == num_add || TREE -> right -> func == num_sub )
                    fprintf ( output, ")");
                break;

            case num_pow:
                if ( TREE -> left -> func == num_add  || TREE -> left -> func == num_sub ||
                     TREE -> left -> func == num_mult || TREE -> left -> func == num_dive )
                    fprintf ( output, "(");
                TREE_print ( TREE -> left, output );
                if ( TREE -> left -> func == num_add  || TREE -> left -> func == num_sub ||
                     TREE -> left -> func == num_mult || TREE -> left -> func == num_dive )
                    fprintf ( output, ")^");
                else
                    fprintf ( output, "^");
                if ( TREE -> right -> func == num_add  || TREE -> right -> func == num_sub ||
                     TREE -> right -> func == num_mult || TREE -> right -> func == num_dive )
                    fprintf ( output, "(");
                TREE_print ( TREE -> right, output );
                if ( TREE -> right -> func == num_add  || TREE -> right -> func == num_sub ||
                     TREE -> right -> func == num_mult || TREE -> right -> func == num_dive )
                    fprintf ( output, ")");
                break;

            case num_add:
                TREE_print ( TREE -> left,  output );
                fprintf ( output, "+");
                TREE_print ( TREE -> right, output );
                break;

            case num_sub:
                TREE_print ( TREE -> left,  output );
                fprintf ( output, "-");
                TREE_print ( TREE -> right, output );
                break;
            default: TREE_dump ( TREE ); ASSERT ( 0 ); break;
            }
        }
    }
    else
    {
        if ( TREE -> func )
            fprintf( output, "x");
        else
            fprintf( output, "%lg", TREE -> number );
    }
}
