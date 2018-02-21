#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include "Queue.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::setw;

struct Person {
    string name;
    int gender;
    Person(string n, string g): name(n) {
        if(g == "male")
            gender = 1;
        else
            gender = 0;
    }
    bool isMale() const { return gender == 1; }
};

bool operator<(const Person &lhs, const Person &rhs);

void shuffle(vector<Person> &persons);  //打乱进入的人的数组

std::ostream &print(std::ostream&, ADT::Queue<Person>&, ADT::Queue<Person>&);


int main()
{
    vector<Person> newComers;
    std::ifstream input("names.txt");
    string n, g;
    while (input >> n >> g)
        newComers.emplace_back(n, g);
    shuffle(newComers);
    ADT::Queue<Person> male, female;


    unsigned int num = 0, total = 0;
    cout << newComers.size() << endl;
    cout << "Input the number of the new comers:";
    while (cin >> num) { // 输入本次来的人数
        if (total + num > newComers.size()) { // 如果已经没人来了
            std::cerr << "No new comers!" << endl;
            std::terminate();
        }
        for (int i = total; i != total + num; ++i) { // 男女分别进队
            if (newComers[i].isMale())
                male.enQueue(newComers[i]);
            else
                female.enQueue(newComers[i]);
        }
        total += num;
        print(cout, male, female);
        cout << "Input the number of the new comers:";
    }
    /*
    while (输入本次来的人数n) {
        if (用于存储名字的 vector 已经用完)
            提示并退出;
        for (i 从0到n-1) {
            if (新来的人 person 是男的)
                maleQueue.enQueue(person);
            else
                femaleQueue.enQueue(person);
        }
        while (maleQueue 和 femaleQueue 都非空) { //这个循环在函数print中
            两队都出队并输出名字;
        }
    }
     */



    return 0;
}

bool operator<(const Person& lhs, const Person& rhs)
{
    return lhs.name < rhs.name;
}

void shuffle(vector<Person>& persons)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(persons.begin(), persons.end(), std::default_random_engine(seed));
}

std::ostream& print(std::ostream& os, ADT::Queue<Person>& m, ADT::Queue<Person>& f)
{
    os << "Let's Dance!!!\n"
       << "Wu Blub Dub Da" << endl;
    while (!(m.isEmpty()) && !(f.isEmpty())) {
        os << std::left;
        os << "Male: " << setw(10) << m.deQueue().name;
        os << "&";
        os << " "
           << "Female: " << setw(10) << f.deQueue().name;
        os << endl;
    }
    if (!m.isEmpty())
        os << m.size() << " men are still waiting." << endl;
    if (!f.isEmpty())
        os << f.size() << " women are still waiting. " << endl;
    os << endl;
    return os;
}
