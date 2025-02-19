#include<iostream>

using namespace std;

int main(int argc,char* argv[]){
    int round = argc,count=0;
    float sum=0;
    if(round > 1){
        for(int i=1;i<round;i++){
            sum += atof(argv[i]);
            count++;
        }
            cout << "---------------------------------\n";
            cout << "Average of " << count << " numbers = " << sum/(round-1);
            cout << "\n---------------------------------";
        }else{
        cout << "Please input numbers to find average.";
        }
    return 0;
}

