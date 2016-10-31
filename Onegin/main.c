//{=================================================================================
//! @file    OneginSort.c
//! @date    16-11-2014 01:35
//! @author  Maxim Garkusha <m.v.garkusha@gmail.com>, 476 group
//!
//! Sorting lines of Novel in verse Eugene Onegin
//!
//!
//}=================================================================================
//--------------------------------------------------------------------------

#include <locale.h>
#include "Strread.h"



//! sorts array of strings from begin
int SortText_Begin      ( char* text[], int* lines );


//! sorts array of strings from end
int SortText_End        ( char* text[], int* lines );


//! comparator to sort by begin of line
int CompareSort_Begin   ( const void* a, const void* b );


//! comparator to sort by end of line
int CompareSort_End     ( const void* a, const void* b );


//! compares two strings a and b by end of string
int StrcmpReverse       ( char string_1[], char string_2[] );


//! check if is a symbol a russian letter
int Isalpha             ( ucc symbol );


//! print text into two different files with two types of sort
int PrintText           ( char* text[], int* lines );


//! print text into output file with start sort
int PrintText_Begin     ( char* text[], int* lines );


//! print text into output file with end sort
int PrintText_End       ( char* text[], int* lines );





int main()
{
    //! enables input of russian symbols
    setlocale ( LC_ALL, "Russian" );

    int lines = 0;

    //! array of lines from the input file
    char** text = Reader ( "Onegin.txt", &lines );

    if ( text == NULL )
        return 0;

    ASSERT( PrintText ( text, &lines ) );

    Free(text);
    return 0;
}





int SortText_Begin ( char* text[], int* lines )
{
    ASSERT( ( lines > 0 ) && ( text != NULL ) );

    qsort ( text, *lines, sizeof (text[0]), CompareSort_Begin );

    ASSERT( ( lines > 0 ) && ( text != NULL ) );

    return OK;
}



int SortText_End ( char* text[], int* lines )
{
    ASSERT( ( lines > 0 ) && ( text != NULL ) );

    qsort ( text, *lines, sizeof (text[0]), CompareSort_End );

    ASSERT( ( lines > 0 ) && ( text != NULL ) );

    return OK;
}



int CompareSort_Begin ( const void* a, const void* b )
{
    ASSERT ( (a != NULL) && ( b != NULL) );

    return strcmp ( *(const char**) a, *(const char**) b );
}



int CompareSort_End ( const void* a, const void* b )
{
    ASSERT ( (a != NULL) && ( b != NULL) );

    return StrcmpReverse ( *(char**) a, *(char**) b );
}



int StrcmpReverse ( char string_1[], char string_2[] )
{
    ASSERT ( ( string_1 != NULL ) && ( string_2 != NULL ) );

    int string_1_Length = strlen ( string_1 ), \
        string_2_Length = strlen ( string_2 );

    ASSERT ( string_1_Length >= 0 && string_2_Length >= 0 );

    string_1_Length--;
    string_2_Length--;

    while ( !Isalpha ( string_1[ string_1_Length ] ) )
        string_1_Length--;

    while ( !Isalpha ( string_2[ string_2_Length ] ) )
        string_2_Length--;

    while ( string_1_Length && string_2_Length )
    {
        if ( ( uchar ) string_1[ string_1_Length ] > ( uchar ) string_2[string_2_Length] )
            return TRUE;

        else if ( ( uchar ) string_1[ string_1_Length ] < ( uchar ) string_2[ string_2_Length ] )
            return FALSE;

        else
            string_1_Length--;
            string_2_Length--;
    }

    return ( string_1_Length ) ? TRUE : FALSE;
}



int Isalpha ( ucc symbol )
{
    //! letters of english alphabeth (for a french language) &&  \
       russian letters (more than 192 ASCII) && 'Ё' (168 ASCII) or 'ё' (184 ASCII)
    return ( ( isalpha( ( signed const char ) symbol ) ) || ( symbol >= ( ucc ) 'А' ) || \
            ( symbol == ( ucc ) 'Ё' ) || ( symbol == ( ucc ) 'ё' ) );

}



int PrintText_Begin ( char* text[], int* lines )
{
    ASSERT ( ( text != NULL ) && ( lines > 0 ) );

    ASSERT ( SortText_Begin ( text, lines) );

    ASSERT ( PrintFile ( "OneginSortByBegin.txt", text, lines ) );
    return OK;
}



int PrintText_End ( char* text[], int* lines )
{
    ASSERT ( ( text != NULL ) && ( lines > 0 ) );

    ASSERT ( SortText_End ( text, lines) );

    ASSERT ( PrintFile ( "OneginSortByEnd.txt", text, lines ) );

    return OK;
}



int PrintText ( char* text[], int* lines )
{
    ASSERT ( ( text != NULL ) && ( lines > 0 ) );

    ASSERT ( PrintText_Begin ( text, lines ) );

    ASSERT ( PrintText_End ( text, lines ) );

    return OK;
}
