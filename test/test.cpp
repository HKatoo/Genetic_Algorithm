#include <iostream>
#include <random>
using namespace std;

int main(){
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> randInt100(0,99);
    uniform_real_distribution<> randReal100(0,99);
    for(int i=0; i<50; i++)
        cout << randReal100(mt) << endl;
}
