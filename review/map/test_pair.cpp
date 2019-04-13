#include <iostream>
#include <string>
#include <map>

using namespace std;

template <class _T1, class _T2>
void printSelf(pair<_T1, _T2> p) 
{
    cout << "key:" << p.first << "\t value:"<< p.second << endl;
}
int main()
{
    std::pair<std::string, std::string> s1("first", "second");
    printSelf(s1);
    std::pair<int, double> s2;
    printSelf(s2);
    std::pair<string, string> s3;
    s3 = make_pair<string, string>("s3-key", "s3-value");
    printSelf(s3);
    std::pair<int, int> s4(1, 1);
    std::pair<int, int> s5(1, 1);
    std::pair<int, int> s6(2, 1);
    cout << (s4 == s4) << endl;
    cout << (s4 != s5) << endl;
    cout << (s4 < s6) << endl;
    cout << (s4 <= s6) << endl;
    return 0;
}
