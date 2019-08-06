#include "population.hpp"

int main(){
    int i;
    Population *pop;
    pop = new Population();
    for(i = 1; i <= GEN_MAX; i++){
        pop -> alternate();
        //printf("第%d世代: 最良適応度%f\n", i, pop->ind[0]->fitness);
    }
    pop->printResult();
    delete pop;
    return 0;
}
