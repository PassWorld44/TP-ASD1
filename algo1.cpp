#include<iostream>
#include<math.h>
using namespace std;


int main(int argc, char **argv) {

    if (argc == 2){
       
        int N = atoi(argv[1]);

        cout << "Just printing the number you entered: " << N << "\nTakes 1 step." << endl; 
    } else{
        cerr << "Error in parcing input arguments. Incorrect number of inputs\n";

    }

    return 0;
}