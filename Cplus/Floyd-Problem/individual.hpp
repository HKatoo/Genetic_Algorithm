#include <cstdio>
#include <algorithm>
#include <functional>
#include <random>

using namespace std;

#define GEN_MAX 5000 //世代交代数
#define POP_SIZE 1000 //個体群のサイズ
#define ELITE 50 //エリート保存数
#define MUTATE_PROB 0.01 //突然変異確率
#define N 64 //集合の要素となる最大数の平方値

random_device rnd;
mt19937 mt(rnd());
uniform_int_distribution<> randInt(0, 1);
uniform_real_distribution<> randReal(0,1);

class Individual{
public:
    Individual();
    ~Individual();
    void evaluate(); //fitnessを算出
    void crossover(Individual *p1, Individual *p2); //交叉による子の生成
    void mutate(); //突然変異
    int chrom[N]; //染色体
    double fitness; //適応度
    
    void printResult();
};

inline Individual::Individual(){
    int i;
    for(i = 0; i < N; i++){
        chrom[i] = randInt(mt);
    }
    fitness = 0.0;
}

inline Individual::~Individual(){
}

//適応度を算出する
void Individual::evaluate(){
    int i;
    for(i = 0; i < N; i++){
        fitness += (chrom[i] * 2 - 1) * sqrt((double)i + 1);
    }
    fitness = fabs(fitness);
}

// 一様交叉
void Individual::crossover(Individual *p1, Individual *p2){
    int i;
    for(i = 0; i < N; i++){
        if(randInt(mt) == 0){
            chrom[i] = p1->chrom[i];
        }
        else{
            chrom[i] = p2->chrom[i];
        }
    }
}

//突然変異
void Individual::mutate(){
    int i;
    for(i = 0; i < N; i++){
        if(randReal(mt) < MUTATE_PROB){
            chrom[i] = 1 - chrom[i];
        }
    }
}
