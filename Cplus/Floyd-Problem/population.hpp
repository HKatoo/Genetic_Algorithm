#include "individual.hpp"

class Population{
public:
    Population();
    ~Population();
    void alternate(); //世代交代
    void printResult(); 

    Individual **ind; //個体群

private:
    void evaluate(); //個体を評価
    int select(); //親個体を選択

    Individual **nextInd; //次世代の個体群
};

//現世代と次世代の個体群のメモリを確保
inline Population::Population(){
    int i;
    ind = new Individual* [POP_SIZE];
    nextInd = new Individual* [POP_SIZE];
    for(i = 0; i < POP_SIZE; i++){
        ind[i] = new Individual();
        nextInd[i] = new Individual();
    }
    evaluate();
}

//メモリを解放
inline Population::~Population(){
    int i;
    for(i = 0; i < POP_SIZE; i++){
        delete ind[i];
        delete nextInd[i];
    }
    delete [] ind;
    delete [] nextInd;
}

//evaluateでsortする時の比較関数
int cmpIndividual(const void* a, const void* b){
    const Individual* i1 = *(const Individual**)a;
    const Individual* i2 = *(const Individual**)b;
    if(i1->fitness > i2->fitness) return 1;
    else if(i1->fitness < i2->fitness) return -1;
    else return 0;
}

//全ての個体を評価して，fitnessの昇順にsort
inline void Population::evaluate(){
    int i;
    for(i = 0; i < POP_SIZE; i++)
        ind[i]->evaluate();
    qsort(ind, POP_SIZE, sizeof *ind, cmpIndividual);
}

inline void Population::alternate(){
    int i, j, p1, p2;
    Individual **tmp;

    //エリート保存戦略
    for(i = 0; i < ELITE; i++){
        for(j = 0; j < N; j++){
            nextInd[i]->chrom[j] = ind[i]->chrom[j];
        }
    }

    //親を選択し，交叉
    for(; i < POP_SIZE; i++){
        p1 = select();
        p2 = select();
        nextInd[i]->crossover(ind[p1], ind[p2]);
    }

    //突然変異
    for(i = ELITE; i < POP_SIZE; i++){
        nextInd[i]->mutate();
    }

    //世代交代
    tmp = ind;
    ind = nextInd;
    nextInd = tmp;

    //評価
    evaluate();
}

//適応度が小さい（良い）個体の上位1/2から子を作成
int Population::select(){
    int num, denom, r;
    denom = POP_SIZE/3 * (POP_SIZE/3+1);
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> randInt(1, denom);
    r = randInt(mt);
    for(num = POP_SIZE; num > 0; num--){
        if(r <= num)
            break;
        r -= num;
    }
    return POP_SIZE - num;
}

void Population::printResult(){
    printf("===============\n");
    int i;
    printf("集合A: ");
    for(i = 0; i < N; i++){
        if(ind[0]->chrom[i] == 1)
            printf("√%d", i+1);
    }
    printf("\n集合B: ");
    for(i = 0; i < N; i++){
        if(ind[0]->chrom[i] == 0)
            printf("√%d", i+1);
    }
    printf("\n差: %f\n", ind[0]->fitness);
}
