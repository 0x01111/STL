#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <class _T>
void printSelf(vector<_T> v) 
{
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
        cout << *iter<< endl;
    }
}
int main()
{
    vector<string> v1;
    v1.push_back("1");
    v1.push_back("2");
    v1.push_back("3");
    printSelf(v1);
    cout << v1.size() << endl;
    cout << v1.empty() << endl;

}
