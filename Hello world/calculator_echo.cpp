#include "stack.h"
#include <ctype.h>

#define PI 3.14159265358979323846264338328
#define MAX_LENGTH_OF_FORMULA 1000
#define MAX_NUMBER_OF_VARIABLES 20
#define WRONG_FUNCTION 0
#define WRONG_BRACKETS 0
#define formula_i__POINT 1

struct lexeme_t
{
int type;
double value;
};

enum types_of_lexemes
{
NUMBER          = 123,
VARIABLE        = 537,
ADD_OR_SUB      = 671,
MUL_OR_DIV      = 428,
LEFT_BRACKET    = 999,
RIGHT_BRACKET   = 500,
FUNCTION_START  = 159,
FUNCTION_END    = 150,
END             = 1,
};

enum types_of_nodes
{
NUMBERn = 123,
SYMBOLn = 224,
FUNCTIONn = 357,
VARIABLEn = 489,
};

enum numbers_of_functions
{
SQRT   = 93,
LN     = 10,
EXP    = 27,
SIN    = 30,
COS    = 60,
TG     = 45,
CTG    = 55,
ARCSIN = 31,
ARCCOS = 61,
ARCTG  = 46,
ARCCTG = 56,
};

struct Node_t
{
int type;
double value;
Node_t* left;
Node_t* right;
};

char* formula_input = NULL;
lexeme_t** formula  = NULL;
char** variables = NULL;

int address = 0;
int number_of_variable = 0;


char* read_formula ();
void check_formula ();
int isoperation (char symbol);

void lexical_analysis ();
lexeme_t*  read_lexeme (lexeme_t* cur_lexeme);

int read_function_name ();
void end_of_name ();
double read_number (char first_digit);
int read_variable ();

Node_t* sintax_analysis ();

Node_t* GetV ();
Node_t* GetO ();
Node_t* GetE ();
Node_t* GetT ();
Node_t* GetP ();
Node_t* GetN ();

Node_t* Node_construct (int Type, double Value, Node_t* Left, Node_t* Right);
void Node_dump (Node_t* node, int slip);
void PRINT_node (Node_t* node, int slip);
void Node_destruct (Node_t* node);



int main ()
{
formula_input = read_formula ();
check_formula ();
printf ("_______________________________\n");
lexical_analysis ();

Node_t* tree = sintax_analysis ();
Node_dump (tree, 0);

return 0;
}



char* read_formula ()
{
char* result = (char*) calloc (MAX_LENGTH_OF_FORMULA, sizeof(char));
assert (result);

printf ("@Program: Tree creator    Version: 3.6.0\n");
printf ("@Date:    12 december 2014\n");
printf ("@Author:  Pletnev Nikita\n");
printf ("_______________________________\n");
printf ("Input your formula\n");

int too_long_formula = 0;
for (int i = 0; i < MAX_LENGTH_OF_FORMULA; i++)
    {
    result [i] = getchar();

    if (result [i] == '\n')
        {
        too_long_formula = 1;
        break;
        }
    if (result [i] == ' ')
        i--;
    }
assert (too_long_formula);
return result;
}

void check_formula ()
{
Stack_t* STACK_of_brackets = Stack_construct (MAX_LENGTH_OF_FORMULA);

for (int i = 0; i < MAX_LENGTH_OF_FORMULA; i++)
    {
    if (formula_input [i] == '(')     Stack_push (STACK_of_brackets, 90);
    if (formula_input [i] == '[')     Stack_push (STACK_of_brackets, 23);
    if (formula_input [i] == ')')
        {
        double last_bracket = Stack_pop (STACK_of_brackets);
        assert (last_bracket == 90 || WRONG_BRACKETS);
        }
    if (formula_input [i] == ']')
        {
        double last_bracket = Stack_pop (STACK_of_brackets);
        assert (last_bracket == 23 || WRONG_BRACKETS);
        }
    }
assert (STACK_of_brackets -> counter == 0 || WRONG_BRACKETS);
Stack_destruct (STACK_of_brackets);

for (int i = 0; i < MAX_LENGTH_OF_FORMULA - 1; i++)
    assert (!(isoperation (formula_input [i]) && isoperation (formula_input [i + 1])));
}

int isoperation (char symbol)
{
if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') return 1;
return 0;
}

void lexical_analysis ()
{
variables = (char**) calloc (MAX_NUMBER_OF_VARIABLES, sizeof(char*));
assert (variables);

int number_of_lexemes = 0;
lexeme_t* cur_lexeme = NULL;
do
    {
    number_of_lexemes++;
    formula = (lexeme_t**) realloc (formula, number_of_lexemes);
    assert (formula);

    cur_lexeme = read_lexeme (cur_lexeme);
    formula [number_of_lexemes - 1] = cur_lexeme;
    }
    while (cur_lexeme != NULL && cur_lexeme -> type != END);
address = 0;
}

lexeme_t* read_lexeme (lexeme_t* cur_lexeme)
{
char first_symbol = formula_input [address];
address ++;
lexeme_t* lexeme = (lexeme_t*) calloc (1, sizeof(lexeme_t));
assert (lexeme);

if (first_symbol == '\n')
    {
    lexeme -> type = END;
    lexeme -> value = END;
    }
if (isdigit (first_symbol) or \
    first_symbol == '.' or first_symbol == ',')
    {
    lexeme -> type = NUMBER;
    lexeme -> value = read_number (first_symbol);
    }
if (isalpha (first_symbol) or first_symbol == '_')
    {
    lexeme -> type = VARIABLE;
    lexeme -> value = read_variable ();
    }
if (first_symbol == '$')
    {
    lexeme -> type = FUNCTION_START;
    lexeme -> value = read_function_name ();
    }
if (first_symbol == ']')
    {
    lexeme -> type = FUNCTION_END;
    lexeme -> value = FUNCTION_END;
    }
if (first_symbol == '(')
    {
    lexeme -> type = LEFT_BRACKET;
    lexeme -> value = '(';
    }
if (first_symbol == ')')
    {
    lexeme -> type = RIGHT_BRACKET;
    lexeme -> value = ')';
    }
if (first_symbol == '*')
    {
    lexeme -> type = MUL_OR_DIV;
    lexeme -> value = '*';
    }
if (first_symbol == '/')
    {
    lexeme -> type = MUL_OR_DIV;
    lexeme -> value = '/';
    }
if (first_symbol == '+')
    {
    lexeme -> type = ADD_OR_SUB;
    lexeme -> value = '+';
    }
if (first_symbol == '-')
    {
    if (cur_lexeme == NULL or \
        cur_lexeme -> type == FUNCTION_START or \
        cur_lexeme -> type == RIGHT_BRACKET)
        {
        lexeme -> type = NUMBER;
        lexeme -> value = read_number (first_symbol);
        }
    else
        {
        lexeme -> type = ADD_OR_SUB;
        lexeme -> value = '-';
        }
    }
return lexeme;
}

double read_number (char first_digit)
{
int signum = 1;
if (first_digit == '-')
    {
    signum = -1;
    address ++;
    first_digit = formula_input [address];
    address ++;
    }
int result_ignor_point = first_digit - '0';
bool afterpoint = 0;
int num_AP = 0;
do
    {
    if (formula_input [address] == '.' or formula_input [address] == ',')
        {
        afterpoint = 1;
        address ++;
        }
    result_ignor_point = result_ignor_point * 10 + formula_input [address];
    address ++;
    if (afterpoint)
        num_AP ++;
    }
    while (isdigit (formula_input [address]) or \
           formula_input [address] == '.' or formula_input [address] == ',');
address --;

double result = signum * result_ignor_point / pow (10, num_AP);
return result;
}

int read_variable ()
{
int place = address, length_name = 0;
while (isalnum (formula_input [place]) or formula_input [place] == '_')
    {
    place ++;
    length_name ++;
    }
variables [number_of_variable] = (char*) calloc (length_name + 1, sizeof(char));
assert (variables [number_of_variable]);

for (int i = 0; i < length_name; i++)
    variables [number_of_variable] [i] = formula_input [address + i];
variables [number_of_variable] [length_name] = '\0';

address += length_name;
number_of_variable ++;
return number_of_variable - 1;
}

int read_function_name ()
{
switch (formula_input [address])
    {
    case 's':
        {
        address ++;
        switch (formula_input [address])
            {
            case 'q':
                {
                address ++;
                assert (formula_input [address] == 'r' || WRONG_FUNCTION);
                address ++;
                assert (formula_input [address] == 't' || WRONG_FUNCTION);

                end_of_name ();
                return SQRT;
                break;
                }
            case 'i':
                {
                address ++;
                assert (formula_input [address] == 'n' || WRONG_FUNCTION);

                end_of_name ();
                return SIN;
                break;
                }
            default:
                {
                assert (WRONG_FUNCTION);
                break;
                }
            }
        break;
        }
    case 'c':
        {
        address ++;
        switch (formula_input [address])
            {
            case 'o':
                {
                address ++;
                assert (formula_input [address] == 's' || WRONG_FUNCTION);

                end_of_name ();
                return COS;
                break;
                }
            case 't':
                {
                address ++;
                assert (formula_input [address] == 'g' || WRONG_FUNCTION);

                end_of_name ();
                return CTG;
                break;
                }
            default:
                {
                assert (WRONG_FUNCTION);
                break;
                }
            }
        break;
        }
    case 'l':
        {
        address ++;
        assert (formula_input [address] == 'n' || WRONG_FUNCTION);

        end_of_name ();
        return LN;
        break;
        }
    case 'e':
        {
        address ++;
        assert (formula_input [address] == 'x' || WRONG_FUNCTION);

        address ++;
        assert (formula_input [address] == 'p' || WRONG_FUNCTION);

        end_of_name ();
        return EXP;
        break;
        }
    case 't':
        {
        address ++;
        assert (formula_input [address] == 'g' || WRONG_FUNCTION);

        end_of_name ();
        return TG;
        break;
        }
    case 'a':
        {
        address ++;
        assert (formula_input [address] == 'r' || WRONG_FUNCTION);

        address ++;
        assert (formula_input [address] == 'c' || WRONG_FUNCTION);

        address ++;
        switch (formula_input [address])
            {
            case 's':
                {
                address ++;
                assert (formula_input [address] == 'i' || WRONG_FUNCTION);

                address ++;
                assert (formula_input [address] == 'n' || WRONG_FUNCTION);

                end_of_name ();
                return ARCSIN;
                break;
                }
            case 't':
                {
                address ++;
                assert (formula_input [address] == 'g' || WRONG_FUNCTION);

                end_of_name ();
                return ARCTG;
                break;
                }
            case 'c':
                {
                address ++;
                switch (formula_input [address])
                    {
                    case 'o':
                        {
                        address ++;
                        assert (formula_input [address] == 's' || WRONG_FUNCTION);

                        end_of_name ();
                        return ARCCOS;
                        break;
                        }
                    case 't':
                        {
                        address ++;
                        assert (formula_input [address] == 'g' || WRONG_FUNCTION);

                        end_of_name ();
                        return ARCCTG;
                        break;
                        }
                    default:
                        {
                        assert (WRONG_FUNCTION);
                        break;
                        }
                    }
                }
            default:
                {
                assert (WRONG_FUNCTION);
                break;
                }
            }
        break;
        }
    default:
        {
        assert (WRONG_FUNCTION);
        break;
        }
    }
}

void end_of_name ()
{
address ++;
assert (formula_input [address] == '[' || WRONG_FUNCTION);

address ++;
}

Node_t* sintax_analysis ()
{
return GetE ();
}

Node_t* GetO ()
{
assert (formula);

if (formula [address] -> type == FUNCTION_START)
    {
    address ++;
    Node_t* val = Node_construct (FUNCTIONn, formula [address] -> value, NULL, NULL);
    address ++;
    val -> right = GetO ();
    return val;
    }
else
    {
    Node_t* val = GetE ();
    return val;
    }
}

Node_t* GetV ()
{
assert (formula);

if (formula [address] -> type == VARIABLE)
    return Node_construct (VARIABLEn, formula [address] -> value, NULL, NULL);
else
    return GetE ();
}

Node_t* GetE ()
{
assert (formula);

Node_t* val = GetT ();
while (formula [address] -> type == ADD_OR_SUB)
    {
    if (formula [address] -> value == '+')
        {
        address ++;
        val = Node_construct (SYMBOLn, '+', val, GetT ());
        }
    else
        {
        address ++;
        val = Node_construct (SYMBOLn, '-', val, GetT ());
        }
    }
return val;
}

Node_t* GetT ()
{
assert (formula);

Node_t* val = GetP ();
while (formula [address] -> type == MUL_OR_DIV)
    {
    if (formula [address] -> value == '*')
        {
        address ++;
        val = Node_construct (SYMBOLn, '*', val, GetP ());
        }
    else
        {
        address ++;
        val = Node_construct (SYMBOLn, '/', val, GetP ());
        }
    }
return val;
}

Node_t* GetP ()
{
assert (formula);

if (formula [address] -> type == LEFT_BRACKET)
    {
    address ++;
    Node_t* val = GetE ();
    address ++;
    return val;
    }
else
    {
    Node_t* val = GetN ();
    return val;
    }
}

Node_t* GetN ()
{
assert (formula);

if (formula [address] -> type == FUNCTION_START)
    return GetO ();
if (formula [address] -> type == VARIABLE)
    return GetV ();
if (formula [address] -> type == NUMBER)
    return Node_construct (NUMBERn, formula [address] -> value, NULL, NULL);
}


Node_t* Node_construct (int Type, double Value, Node_t* Left, Node_t* Right)
{
Node_t* new_node = (Node_t*) calloc (1, sizeof(Node_t));
new_node -> type = Type;
new_node -> value = Value;
new_node -> left = Left;
new_node -> right = Right;
return new_node;
}

void Node_destruct (Node_t* node)
{
if (node -> left != NULL)   Node_destruct (node -> left);
if (node -> right != NULL)   Node_destruct (node -> right);
free (node);
}

void Node_dump (Node_t* node, int slip)
{
PRINT_node (node, slip);
if (node -> left != NULL)   Node_dump (node -> left, slip + 1);
if (node -> right != NULL)   Node_dump (node -> right, slip + 1);
}

void PRINT_node (Node_t* node, int slip)
{
for (int i = 0; i < slip; i++)
    printf ("    ");
switch (node -> type)
    {
    case NUMBERn:
        {
        printf ("%lg\n", node -> value);
        break;
        }
    case SYMBOLn:
        {
        printf ("%c\n", node -> value);
        break;
        }
    case FUNCTIONn:
        {
        int function_number = node -> value;
        switch (function_number)
            {
            case SQRT:
                {
                printf ("sqrt\n");
                break;
                }
            case LN:
                {
                printf ("ln\n");
                break;
                }
            case EXP:
                {
                printf ("exp\n");
                break;
                }
            case SIN:
                {
                printf ("sin\n");
                break;
                }
            case COS:
                {
                printf ("cos\n");
                break;
                }
            case TG:
                {
                printf ("tg\n");
                break;
                }
            case CTG:
                {
                printf ("ctg\n");
                break;
                }
            case ARCSIN:
                {
                printf ("arcsin\n");
                break;
                }
            case ARCCOS:
                {
                printf ("arccos\n");
                break;
                }
            case ARCTG:
                {
                printf ("arctg\n");
                break;
                }
            case ARCCTG:
                {
                printf ("arcctg\n");
                break;
                }
            default:
                break;
            }
        break;
        }
    case VARIABLEn:
        {
        int j = 0;
        while (variables [(int) node -> value] [j] != '\0')
            {
            printf ("%c", variables [(int) node -> value] [j]);
            j++;
            }
        printf ("\n");
        break;
        }
    }
}
