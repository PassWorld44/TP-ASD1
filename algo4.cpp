#include<iostream>
#include<math.h>
using namespace std;

void selection_sort (int *a, int n, int& counter) {
    int i, j, m, t;
    counter = 0 ;
    for (i = 0; i < n; i++) {
        for (j = i, m = i; j < n; j++) {
            counter++;
            if (a[j] < a[m]) {
                m = j;
            }
        }
        t = a[i];
        a[i] = a[m];
        a[m] = t;
    }
}

int main(int argc, char **argv) {


    if (argc == 2){
       srand(time(0));
        int N = atoi(argv[1]);

        int *tab = new int[N];
        for (int i = 0; i < N; ++i){
            tab[i] = rand() ;
        }
        int counter = 0;

        selection_sort(tab, N, counter);
        cout << "Sorted the array of " << N << " elements in " << counter << "steps" << endl;

        delete[] tab;

    } else{
        cerr << "Error in parcing input arguments. Incorrect number of inputs\n";
    }

    return 0;
}