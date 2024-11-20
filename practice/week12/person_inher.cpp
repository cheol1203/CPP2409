#include <iostream>
using namespace std;

class Person
{
protected:
    string name;
    string address;
public:
    void SetName(string name) { this->name = name; } // Setter 추가
    string GetName() { return name; }               // Getter 추가
};

class Student : public Person
{
public:
    void SetAddress(string add)
    {
        address = add;
    }
    string GetAddress()
    {
        return address;
    }
};
int main()
{
    Student obj;
    obj.SetName("미수");
    obj.SetAddress("서울시 종로구 1번지");
    cout << obj.GetName() << endl;
    cout << obj.GetAddress() << endl;

    return 0;
}

