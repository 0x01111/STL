# map 
map 容器提供了一种更有效的存储和访问数据的方法。在关联容器中，对象的位置取决于和它关联的键的值。键可以是基本类型，也可以是类类型。字符串经常被用来作为键。关联容器中的对象位置的确定取决于容器中的键的类型，而且对于特定容器类型的内部组织方式，不同的 STL 有不同的实现。

map<K，T> 类模板定义在 map 文件头中，它定义了一个保存 T 类型对象的 map，每个 T 类型的对象都有一个关联的 K 类型的键。容器内对象的位置是通过比较键决定的。可以用适当的键值从 map 容器中检索对象。




## pair
pair 对象可以封装任意类型的对象，可以生成任何想生成的 pair<T1,T2> 对象，它只有两个 public 数据成员 first 和 second。它却可以构造各种不同的 pair<T1，T2>，可以是数组对象或者包含 pair<T1,T2> 的 vector 容器。例如，pair 可以封装两个序列容器或两个序列容器的指针。
```cpp
template <class _T1, class _T2>
struct pair {
  typedef _T1 first_type;
  typedef _T2 second_type;

  _T1 first;
  _T2 second;
  // 构造函数
  pair() : first(_T1()), second(_T2()) {}
  pair(const _T1& __a, const _T2& __b) : first(__a), second(__b) {}

#ifdef __STL_MEMBER_TEMPLATES
  template <class _U1, class _U2>
  pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}
#endif
};
```
### 构造函数
```cpp
  pair() : first(_T1()), second(_T2()) {}
  pair(const _T1& __a, const _T2& __b) : first(__a), second(__b) {}
```
第一个无参构造函数，两个成员变量设置为默认值；
第二个构造函数，根据参数对 first、second 进行初始化；

### 成员函数
#### make_pair
```cpp
template <class _T1, class _T2>
inline pair<_T1, _T2> make_pair(const _T1& __x, const _T2& __y)
{
  return pair<_T1, _T2>(__x, __y);
}
```
make_pair<T1，T2> 函数模板是一个辅助函数，可以生成并返回一个 pair<T1，T2> 对象

#### operator操作
相等：判断逻辑是两个 pair 的 first 、second 都要相等
```cpp
template <class _T1, class _T2>
inline bool operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ 
  return __x.first == __y.first && __x.second == __y.second; 
}
```

小于： __x.first < __y.first  或者 ( __x.first < __y.first && _x.second < __y.second )

```cpp
template <class _T1, class _T2>
inline bool operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ 
  return __x.first < __y.first || 
         (!(__y.first < __x.first) && __x.second < __y.second); 
}
```
不相等：连个对象不等
```cpp
template <class _T1, class _T2>
inline bool operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__x == __y);
}
```
大于： 
```cpp
template <class _T1, class _T2>
inline bool operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __y < __x;
}
```
小于等于
```cpp
template <class _T1, class _T2>
inline bool operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__y < __x);
}
```
大于等于
```cpp
template <class _T1, class _T2>
inline bool operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__x < __y);
}

```
