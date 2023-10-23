#include<iostream>
#include<math.h>
using namespace std;

int linear_search (int *a, int n, int x, int& counter) {
    int i = 0;
    counter = 0;
    while (i < n) {
        counter++;
        if (a[i] == x) {
            return i;
        }
        else {
            i++;
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
            tab[i] = rand() ;
        }
        int counter = 0;
        int x = rand();
        int pos = linear_search(tab, N, x, counter);
        cout << "Found " << x << "in the array of " << N << "elements in " << counter << "steps" << endl;

        delete[] tab;

    } else{
                cerr << "Error in parcing input arguments. Incorrect number of inputs\n";

    }

    return 0;
}