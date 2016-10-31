#include <stdio.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

#define float char

unsigned int check_to_girki(unsigned const int N);         //naming function

int main()
{
    unsigned int N=0;                       //incoming number, 0<n<2^32, that's mean than unsign. int is enouth


    scanf("%u", &N);
    assert(N > 0);                            //checking incoming number


    if (check_to_girki(N))                    //checking function to ending iterations
        printf("YES");
    else
        printf("NO");


    return 0;
}


unsigned int check_to_girki(unsigned const int N)
{
    if (N == 0)                                //if N==0, than incoming number can be weighted by girki =)
        return TRUE;
    else
        if (N % 4 == 2)                        //if this true, that means than incoming number was bad =(
            return FALSE;
        else
            return check_to_girki(N / 4);    //make some recursion
}
