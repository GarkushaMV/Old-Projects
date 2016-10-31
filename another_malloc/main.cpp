#include <iostream>
#include <cstdio>

int main()
{
using namespace std;
int i = 0, N;
cout << "Enter number of positions: ";
cin >> N;
int* A = new int [N];

for ( i=0; i<N; i++ )
   {
    cout << "Enter " << (i+1) << " position: \n";
    cin >> A[i]
   }

for ( i=0; i<N; i++)
   {
    cout << (i+1) << " position of array" << A[i] << "\n";
   }

  for (i=1; i<N; i++)
  {
         for (int x=i; x>0 && A[x-1]>A[x]; x--)
         swap(A[x-1], A[x]);

  }
  cout << endl;
  for (i=0; i<N; i++)
  {
      cout << A[i] << endl;
  }

cin.get();
cin.get();
}
