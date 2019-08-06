#include <iostream>
#include <random>
#include <algorithm>
#include <functional>
#include <cstdlib>

using namespace std;

class Student{
//private:
//    string name;
//    int age;
public:
    Student(){};
    //Student(string s, int i): name(s), age(i){};
    string name;
    int age;
    void setInfo(string s, int i){
        name = s;
        age = i;
    }
    void printInfo(){
        cout << name << ": " << age << endl;
    }
    //bool operator<(const Student* &another) const{
    //    return age < another->age;
    //}
};

//bool cmp(const Student* &a, const Student* &b){
    //return a->age < b->age;
//}

int cmpStudent(const void* a, const void* b){
    const Student* s1 = *(const Student**)a;
    const Student* s2 = *(const Student**)b;
    int diff = s2->age - s1->age;
    return diff;
}


int main(){
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> randInt100(0,99);
    //uniform_real_distribution<> randReal100(0,99);
    for(int i=0; i<50; i++)
        cout << randInt100(mt) << endl;

    //Student students[3] = {Student("a", 10), Student("b",12), Student("c", 11)};
    //sort(students, students+3);
    //for(auto ele : students)
    //    ele.printInfo();

    //Student *students;
    //students = new Student[3];
    //students[0].setInfo("a", 20);
    //students[1].setInfo("b", 30);
    //students[2].setInfo("c", 25);
    //sort(students, students+3);
    //for(int i=0; i < 3; i++)
    //    students[i].printInfo();

    //Student* *students;
    //students = new Student*[3];
    //students[0] = new Student();
    //students[1] = new Student();
    //students[2] = new Student();
    //students[0]->setInfo("a", 13);
    //students[1]->setInfo("b", 15);
    //students[2]->setInfo("c", 11);
    //sort(students, students+3);
    //qsort(students, 3, sizeof *students, cmpStudent);
    //for(int i=0; i < 3; i++)
        //students[i]->printInfo();
}
