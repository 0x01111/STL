# vector
vector<T> (向量容器) ：是一个长度可变的序列，用来存放T类型的对象。必要时，可以自动增加容量，但只能在序列的末尾高效地增加或删除元素。
内部通过指针实现
```cpp
起始指针
  using _Base::_M_start;
  最后一个元素的下一个指针
  using _Base::_M_finish;
  能够存储元素的最大个数
  using _Base::_M_end_of_storage;
```
## begin end
在这里也可以看出 begin 返回的是第一个原始， end 返回的是最后一个远的下一个元素
```cpp
  iterator begin() { return _M_start; }
  const_iterator begin() const { return _M_start; }
  iterator end() { return _M_finish; }
  const_iterator end() const { return _M_finish; 
```
其他 begin end 相关的方法就不粘贴了；
## size 
由于 end 指向最后一个元素的下一个元素，所有 size = end  - begin ；
end 只想一个空的指针，当 end = begin 表示是空的 vector
```cpp
  size_type size() const
    { return size_type(end() - begin()); }
  size_type max_size() const
    { return size_type(-1) / sizeof(_Tp); }
  size_type capacity() const
    { return size_type(_M_end_of_storage - begin()); }
  bool empty() const
    { return begin() == end(); }
 ```
 ## 下标获取
 这里使用到了 加法运算，具体再后面
 ```cpp
   reference operator[](size_type __n) { return *(begin() + __n); }
  const_reference operator[](size_type __n) const { return *(begin() + __n); 
  ```
  ## 构造函数
```cpp
1. 空
  explicit vector(const allocator_type& __a = allocator_type())
    : _Base(__a) {}
2. 最大存储 n 个 value 元素的 vecotr
  vector(size_type __n, const _Tp& __value,
         const allocator_type& __a = allocator_type()) 
    : _Base(__n, __a)
    { _M_finish = uninitialized_fill_n(_M_start, __n, __value); }
3. 最大存储 n 个元素的 vecotr
  explicit vector(size_type __n)
    : _Base(__n, allocator_type())
    { _M_finish = uninitialized_fill_n(_M_start, __n, _Tp()); }
4. 使用另外一个 vecotr 对当前 vector 进行赋值
  vector(const vector<_Tp, _Alloc>& __x) 
    : _Base(__x.size(), __x.get_allocator())
    { _M_finish = uninitialized_copy(__x.begin(), __x.end(), _M_start); }
  ```
## 析构函数
释放空间
```cpp
 ~vector() { destroy(_M_start, _M_finish); }
 ```
 ## 重载操作符 operator
 ```cpp
 // 相等
template <class _Tp, class _Alloc>
inline bool 
operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
{
  return __x.size() == __y.size() &&
         equal(__x.begin(), __x.end(), __y.begin());
}
// 小于
template <class _Tp, class _Alloc>
inline bool 
operator<(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
{
  return lexicographical_compare(__x.begin(), __x.end(), 
                                 __y.begin(), __y.end());
}
template <class _Tp, class _Alloc>
inline void swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y)
{
  __x.swap(__y);
}

template <class _Tp, class _Alloc>
inline bool
operator!=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return !(__x == __y);
}

template <class _Tp, class _Alloc>
inline bool
operator>(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return __y < __x;
}

template <class _Tp, class _Alloc>
inline bool
operator<=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return !(__y < __x);
}

template <class _Tp, class _Alloc>
inline bool
operator>=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return !(__x < __y);
}
```
赋值操作

```cpp
template <class _Tp, class _Alloc>
vector<_Tp,_Alloc>& 
vector<_Tp,_Alloc>::operator=(const vector<_Tp, _Alloc>& __x)
{
  // 两个 vector 不相等
  if (&__x != this) {
    const size_type __xlen = __x.size();
    if (__xlen > capacity()) {  // 存储空间不够用
      // 临时空间
      iterator __tmp = _M_allocate_and_copy(__xlen, __x.begin(), __x.end());
      // 销毁、释放空间
      destroy(_M_start, _M_finish);
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      // 重新赋值
      _M_start = __tmp;
      _M_end_of_storage = _M_start + __xlen;
    } // 已经使用空间购
    else if (size() >= __xlen) {
      iterator __i = copy(__x.begin(), __x.end(), begin());
      destroy(__i, _M_finish);
    } // 已经使用的空间不够用， 先复制使用的，后面再 copy 防止空间不够用
    else {
      copy(__x.begin(), __x.begin() + size(), _M_start);
      uninitialized_copy(__x.begin() + size(), __x.end(), _M_finish);
    }
    // 结束指针更新
    _M_finish = _M_start + __xlen;
  }
  return *this;
}
```
## insert

```
//pos 位置插入 n 个 值为 x 的元素
template <class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_fill_insert(iterator __position, size_type __n, 
                                         const _Tp& __x)
{
  // 初始空间不为0 
  if (__n != 0) {
    // 剩余空间够不够用
    if (size_type(_M_end_of_storage - _M_finish) >= __n) {
      // 够用
      _Tp __x_copy = __x;
      const size_type __elems_after = _M_finish - __position;
      iterator __old_finish = _M_finish;
      // 插入位置在 finish 之前，并且 有 n 个位置可以插入
      if (__elems_after > __n) {
        uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
        _M_finish += __n;
        copy_backward(__position, __old_finish - __n, __old_finish);
        fill(__position, __position + __n, __x_copy);
      }
      else {
        uninitialized_fill_n(_M_finish, __n - __elems_after, __x_copy);
        _M_finish += __n - __elems_after;
        uninitialized_copy(__position, __old_finish, _M_finish);
        _M_finish += __elems_after;
        fill(__position, __old_finish, __x_copy);
      }
    }
    else {
      // 不够用，直接申请空间
      const size_type __old_size = size();        
      const size_type __len = __old_size + max(__old_size, __n);
      iterator __new_start = _M_allocate(__len);
      iterator __new_finish = __new_start;
      __STL_TRY {
        __new_finish = uninitialized_copy(_M_start, __position, __new_start);
        __new_finish = uninitialized_fill_n(__new_finish, __n, __x);
        __new_finish
          = uninitialized_copy(__position, _M_finish, __new_finish);
      }
      __STL_UNWIND((destroy(__new_start,__new_finish), 
                    _M_deallocate(__new_start,__len)));
      destroy(_M_start, _M_finish);
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      _M_start = __new_start;
      _M_finish = __new_finish;
      _M_end_of_storage = __new_start + __len;
    }
  }
}

```

