#include<iostream>
#include<math.h>
using namespace std;

char chars[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
'n','o','p','q','r','s','t','u','v','w','x','y','z'};

int StepCounter=0;
int PwdCounter=0;

void GenerateAllPassowrds(string pwd, int pos, int size){
    if(pos < size){
        for (char ch : chars){
            GenerateAllPassowrds(pwd+ch, pos+1, size);
                    StepCounter ++;
        }
    }
    else{
        PwdCounter ++;
        //cout << pwd << "\t";      //uncomment this to print all possible passwords
    }
}


int main(int argc, char **argv) {


    if (argc == 2){
        int N = atoi(argv[1]);
        cout << "Generating all possible " << N << "-character passwords..." << endl; 
        GenerateAllPassowrds("", 0, N);
        cout <<"It took " << StepCounter << " steps to find " << PwdCounter << " passwords " << endl;
    } else{
        cerr << "Error in parcing input arguments. Incorrect number of inputs\n";

    }

    return 0;
}