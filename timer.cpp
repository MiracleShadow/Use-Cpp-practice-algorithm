#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(int argc,char** argv)//char** argv<==>char* agrv[]
{
    if(argc!=2)
    {
        cout<<"Usage:timer program_examed_name"<<endl;
        return 1;
    }
    cout<<"Beginning test...\n"<<endl;
    clock_t begin = clock();
    system(argv[1]);
    clock_t end = clock();
    cout<<"\n\nRunning time: "<<(double)(end-begin)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
}
