#include <iostream>
#include <string>
#include <map>

using namespace std;

template <class _T1, class _T2>
void printSelf(pair<_T1, _T2> p) 
{
    cout << "key:" << p.first << "\t value:"<< p.second << endl;
}

template <class _T1, class _T2>
void printSelf(multimap<_T1, _T2> m)
{
    for (auto iter = m.begin(); iter != m.end(); ++iter) {
        printSelf(*iter);
    }

}
int main()
{
   multimap<string, string> m1;
   m1.insert(pair<string, string>("k1", "v1"));
   m1.insert(pair<string, string>("k1", "v1"));
   m1.insert(pair<string, string>("k2", "v2"));
   m1.insert(pair<string, string>("k2", "v2"));
   m1.insert(pair<string, string>("k3", "v3"));
   m1.insert(pair<string, string>("k3", "v3"));
   m1.insert(pair<string, string>("k4", "v4"));
   pair<string, string> p1("k5", "v5");
   m1.insert(p1);
   printSelf(m1);
   string k5="k5";
   auto iter = m1.find(k5);
   if (iter != m1.end()) {
        cout <<"find p1:" << iter->first << "\t"<< iter->second << endl;
   }
   multimap<string, string> m2(m1);
   printSelf(m2);
   cout << "m2.size:" << m2.size() << endl;
   cout << "m2.empty:" << m2.empty() << endl;
   cout << "m2.countk5:" << m2.count("k5") << endl;
   cout << "m2.countk2:" << m2.count("k2") << endl;

    iter = m2.lower_bound("k3");
   printSelf(*iter);
   auto pr = m2.equal_range("k1");
   for (auto iter2= pr.first; iter2!= pr.second; ++ iter2 ) {
        cout << iter2->first << ":" << iter2->second << endl;
    }
   return 0;
}
