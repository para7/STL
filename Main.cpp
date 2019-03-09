#include <iostream>
#include <string>
#include "vector.hpp"
#include "memory.hpp"

using std::cout;
using std::endl;

class Undefault
{
public:
    int x;

    Undefault() = delete;

    explicit Undefault(int _x) : x(_x) {}
};

class Uncopy
{
public:

    int x;

    Uncopy& operator= (const Uncopy&) = delete;

    Uncopy& operator=(Uncopy&& other) noexcept {
        if (this != &other) {
            this->x = other.x;
        }
        return *this;
    }

    Uncopy() : x(-1) {};

    explicit Uncopy(int _x) : x(_x) {};

private:
};

using namespace my;

int main()
{
    vector<Uncopy> ar(2);

    ar.push_back(Uncopy(10));
    ar.push_back(Uncopy(20));
    ar.push_back(Uncopy(30));
    ar.push_back(Uncopy(40));
    ar.push_back(Uncopy(50));
    ar.push_back(Uncopy(60));
    ar.push_back(Uncopy(70));
    ar.push_back(Uncopy(80));
    ar.push_back(Uncopy(90));
    ar.push_back(Uncopy(100));

    cout << "size:" << ar.size() << endl;
    cout << "capacity:" << ar.capacity() << endl;

    for (int i = 0; i < ar.size(); i++)
    {
        cout << ar[i].x << endl;
    }

    /*
    Array<Undefault> arud;

    arud.push_back(Undefault(10));
    arud.push_back(Undefault(20));
    arud.push_back(Undefault(30));
    arud.push_back(Undefault(40));
    arud.push_back(Undefault(50));

    cout << "size:" << arud.size() << endl;
    cout << "capacity:" << arud.capacity() << endl;

    for (int i = 0; i < arud.size(); i++)
    {
        cout << arud[i].x << endl;
    }
    */
}