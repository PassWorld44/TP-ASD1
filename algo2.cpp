#include<iostream>
#include<math.h>
using namespace std;

int bsearch (int *a, int n, int x, int& counter) {
    int i = 0, j = n - 1;
    counter = 0;
    while (i <= j) {
        counter++;
        int k = i + ((j - i) / 2);
        if (a[k] == x) {
            return k;
        }
        else if (a[k] < x) {
            i = k + 1;
        }
        else {
            j = k - 1;
        }
    }
    return -1;
}

int main(int argc, char **argv) {


    if (argc == 2){
       srand(time(0));
        int N = atoi(argv[1]);

        int *tab = new int[N];
        for (int i = 0; i < N; ++i){
            tab[i] = i ;
        }
        int counter = 0;
        int x = rand()%N;
        int pos = bsearch(tab, N, x, counter);
        cout << "Found " << x << "in the array of " << N << "elements in " << counter << "steps" << endl;

        delete[] tab;

    } else{
        cerr << "Error in parcing input arguments. Incorrect number of inputs\n";

    }

    return 0;
}