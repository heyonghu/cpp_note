# 1. std::string类

- 字符串处理在程序中应用广泛，C风格字符串是以'\0'（空字符）来结尾的字符数组，在使用时，程序员需要考虑字符数组大小的开辟，结尾空字符的处理，使用起来有诸多不便

- 实际上，C++提供了`std::string`类用于字符串的处理。

- `std::string`类定义在头文件string中，注意和头文件`cstring`区分，`cstring`中定义的是一些对C风格字符串的处理函数，本章对string类的使用方法进行讨论

- 本节的题目也可以说是`string`类比C风格字符串要好，之所以抛弃C风格字符串而选用C++标准程序库中的string类，是因为`string`和C风格字符串相比，不必担心内存是否足够、字符串长度，结尾的空白符等等。string作为一个类出现，其集成的成员操作函数功能强大，几乎能满足所有的需求，从另一个角度上说，完全可以把string当成是C++的内置数据类型，放在和`int`、`double`等同等位置上。

- 如无特别说明，本章中提及的字符串均是指string字符串。

- 和流类库差不多，`string`类其实是`basic_string`类模板关于`char`型的实例化，对应着`wchar_t`类型还有`wstring`类，本章讨论string类的用法，`wstring`类的用法与此完全一致。

- 和`STL`一样，`basic_string`模板中同样定义了`size_type`类，用来表示元素个数等与系统相关的无符号整型，此外，还有表示元素类型的`value_type`，对`string`类而言，`value_type`等价与char，但对`wstring`类来说，`value_type`为`wchar_t`。

## 1.1 声明字符串

string是字符串类，首先来看一下如何通过构造函数来声明一个字符串，string类的构造函数如所示：

![image-20220628130344214](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220628130344214.png)

## 1.2 字符串的输入输出

- `C`风格字符串的输入大致有 >> 、`cin.getline()`和`cin.get()`这3种

- 对`string`字符串来说，除了重载了`“>>”`实现输出外，`string`头文件还定义了外部函数或全局函数`getline`用以输入string字符串。抛弃了`“cin.getline()”`和`“cin.get()”`两种输入方式，原因在于`getline`外部函数能自动调整目标string的大小，使其能恰好存储输入的字符。

- `>>`输入同样会自动调整string对象的大小。

- 外部`getline`函数第一个参数必须为输入流对象，第二个参数是待输入的`string`对象，第3个参数是分界符，`getline`函数将输入流中的字符存储到string变量中，直到满足下列条件之一：

  - 到达文件尾，此时输入流的`eofbit`置位有效。

  - 遇到分界字符，默认为换行符’\n’，此时，分解符会从流中删除，但并不会存储到string对象中。

  - 读取的字符达到最大允许值（`string`类中的常量`npos`决定了`string`所能存储的最大字符数，一般都很大，不会对输入产生影响，另一个因素是可用内存数，因此，最大允许值便是从`npos`和可用内存字节数中选取较小的一个），输入流的`failbit`置位有效。

## 1.3 string类功能

在讨论了如何创建字符串，及对字符串进行输入输出之后，本节讨论string类的其他一些public成员函数，通过这些函数可以方便地对字符串进行赋值、清空，实现不同字符串间的比较，字符的插入、删除、追加，以及搜索与查找等，下面分别展开讨论。

### 1.3.1 string字符串和C风格字符串的转换

- C风格字符串转换为string字符串相对来说比较简单，通过构造函数即可实现。但由于string字符串实际上是类对象，其并不以空字符’\0’结尾，因此，string字符串向C风格字符串的转化是通过3个成员函数完成的，分别为：

  ```cpp
  const char *data(); //以字符数组的形式返回字符串内容，但末尾并不添加’\0’ 
  const char *c_str() //返回一个以‘\0’结尾的字符数组
  
  int copy(char*s, size_type n); //字符串的内容复制或写入既有的C风格字符串或字符数组内
  
  在C++11以后，data和c_str成员函数的功能相同
  三种都可以使用
  ```

## 1.4 string操作

### 1.4.1 赋值和清空

- 对string字符串的赋值有两种途径
  1. 使用“=”：

​			等号右侧的操作数可以是string、C风格字符串、还可以是单个字符。

​		2.使用成员函数`assign()`（赋值）

​			成员函数`assgin`有多种重载形式，从本质上说，和有参构造函数的参数是相同的，参考。

- 把字符串清空的方法有2个，以string字符串 `str`为例：

```cpp
str="";    //用空字符串为其赋值
str.erase(); //删除全部元素

此外，erase函数还可用于删除部分元素。
```

### 1.4.2 元素删除

- erase方法用于从字符串中删除字符，原型如下：

```cpp
1.iterator erase( iterator First , iterator Last ); 
// 删除[First, Last)的字符，返回的迭代器指向最后一个被删除元素的后一个元素。
2.iterator erase( iterator It ); 
// 删除string 中 It 所指的字符，返回指向下一个元素的迭代器，如果后面没有其他元素，则返回end()。
3.string& erase( size _ type pos = 0, size _ type n = npos ); 
// 删除string中从pos位置开始的n个字符或删除到末尾，返回删除后的string 的引用。
```

### 1.4.3 元素追加与相加

- 提到追加与相加，首先想到的是重载的+=操作符，+=操作符能将另一个`string`字符串，C风格字符串、甚至是单个字符添加到`string`字符串后。

- `string`类还定义了更灵活的`append`函数将另一个`string`字符串，C风格字符串、甚至是单个字符添加到`string`字符串后，此外，通过指定初始位置和追加字符数，以及指定区间的方法，可以将另一个`string`字符串或C风格字符串的一部分追加到是字符串中，`append`函数的各个重载版本定义如下。

![image-20220628133034162](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220628133034162.png)

- ```cpp
  string& replace( size_type pos, size_type count, const basic_string& str );
  s.replace(range, args) // 删除s中的范围range内的字符，替换为args指定的字符。
      
  
  #include <cassert>
  #include <cstddef>
  #include <iostream>
  #include <string>
  #include <string_view>
   
  std::size_t replace_all(std::string& inout, std::string_view what, std::string_view with);
  std::size_t remove_all(std::string& inout, std::string_view what);
  void test_replace_remove_all();
   
  int main()
  {
      std::string str{"The quick brown fox jumps over the lazy dog."};
   
      str.replace(10, 5, "red"); // (5)
      std::cout << str << "\n\n";
      str.replace(str.begin(), str.begin() + 3, 1, 'A'); // (6)
   
      std::cout << str << "\n\n";
   
      test_replace_remove_all();
  }
   
   
  std::size_t replace_all(std::string& inout, std::string_view what, std::string_view with)
  {
      std::size_t count{};
      for (std::string::size_type pos{};
           inout.npos != (pos = inout.find(what.data(), pos, what.length()));
           pos += with.length(), ++count) {
          inout.replace(pos, what.length(), with.data(), with.length());
      }
      return count;
  }
   
  std::size_t remove_all(std::string& inout, std::string_view what) {
      return replace_all(inout, what, "");
  }
   
  void test_replace_remove_all()
  {
      std::string str2{"ftp: ftpftp: ftp:"};
      std::cout << "#1 " << str2 << '\n';
   
      auto count = replace_all(str2, "ftp", "http");
      assert(count == 4);
      std::cout << "#2 " << str2 << '\n';
   
      count = replace_all(str2, "ftp", "http");
      assert(count == 0);
      std::cout << "#3 " << str2 << '\n';
   
      count = remove_all(str2, "http");
      assert(count == 4);
      std::cout << "#4 " << str2 << '\n';
  }
  ```

### 1.4.4 元素插入

成员函数insert用于将string对象、字符数组或字符插入到string字符串中，这和追加append有些相似，只是元素插入不再局限于尾部，可以插入到中间，因此需要一个指示插入位置的参数，该参数可以是位置，也可以是迭代器，数据将被插入该位置的前面，insert函数的重载形式如下：

```cpp
（1）string& insert( size_type pos, const char* s);

（2）string& insert( size_type pos, const char* s , size_type n );

（3）string& insert(size_type pos, const string& str );

（4）string& insert(size_type pos,const string& str, size_type pos1, size_type n)

（5）string& insert(size_type pos, size_type n , char c );

（6）void insert(Iterator pos, Iterator First , Iterator Last );

（7）void insert(Iterator pos,size_type n,char c);
```

### 1.4.5 string类大小和容量

string类提供了一些和大小、容量相关的函数，如所示：

![image-20220628133344762](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220628133344762.png)

### 1.4.6 元素存取

- 可以使用下标操作符[]和函数at()对字符串中包含的字符进行访问，需要注意的是操作符[]并不检查索引是否有效（有效索引`0~str.length()`），如果索引失效，会引起未定义的行为，而`at()`会检查，如果使用 at()的时候索引无效，会抛出`out_of_range`异常。

- 特例：对`const`修饰的`string`常量`str`来说，操作符[]对索引值`str.length()`仍然有效，返回值是`’\0’`，其他情况下（即`str`不是`const`修饰的字符串常量），`str.length()`索引都是无效的。

### 1.4.7 字符串比较

- string字符串支持常见的比较操作符`（>,>=,<,<=,==,!=）`，也支持string与C风格字符串的比较。使用上述比较操作符时，根据字符的字典顺序（字典排序靠前的字符小）从前往后逐一比较，遇到不等的字符就按该位置上的这两个字符的比较结果确定两个字符串的大小，即

```cpp
string(“abcde”) < string(“ac”)
```

- 此外，string类还提供了成员函数compare()用于字符串比较，支持多参数处理，支持用索引值和长度定位子串来进行比较，返回一个整数（0：相等、>0：大于、<0：小于）来表示比较结果。

### 1.4.8 提取子串

- string类提供了`substr`成员函数用于提取子串，以string `str(“98765432112345678”)`为例：

```cpp
（1）str.substr(); //返回str的全部内容

（2）str.substr(9); //截断前九个字符，即“12345678”

（3）str.substr(5,6);//从下标为5的字符开始往后截取，一共截取6个字符，即“432112”
```

### 1.4.9 搜索与查找

- `string`类提供的搜索与查找函数很多，限于篇幅的原因，本章便不再铺开来讲，总体上说，`string`类提供了6种搜索函数，返回值均为`size_type`，简要列举如下：

  - （1）`find`系列：返回待查找元素或子串在字符串中第一次出现的位置，举例来说，字符串`str`为`“Welcome to C++ World”`，使用`find`函数系列查找单个字符’o’在`str`中第一次出现位置，返回结果为4，还可查找子串“to”在`str`中的位置，返回结果为8。

  - （2）`rfind`系列：返回待查找元素或子串在字符串中最后一次出现的位置，如使用`rfind`函数查找单个字符’o’在`str`中最后一次出现位置，返回结果为16。

  - （3）find_first_of系列：返回待查找元素在字符串中第一次出现的位置，如果查找的子串，不是查找整个字符串的匹配，而是搜索子串中的字符首次出现的位置，同样以字符串“Welcome to C++ World”为例，使用find_first_of()系列函数查找字符串“abc”在其中首次出现的位置，返回结果为3，此时第一次出现了字符串`“abc”`中的元素’c’。

  - （4）find_last_of系列：返回待查找元素在字符串中最后一次出现的位置，如果查找的子串，不是查找整个字符串的匹配，而是搜索子串中的字符最后出现的位置。

  - （5）find_first_not_of系列：与find_first_of()的工作方式类似，不过搜索的是第一个不位于字符串中的字符第一次出现的位置。

  - （6）find_last_not_of系列：与find_first_of()的工作方式类似，不过搜索的是第一个不位于字符串中的字符最后一次所在位置。

```cpp
#include <stdlib.h>  //C的头文件写在C++头文件之前
#include <string.h>

#include <iostream>
#include <string>   
using std::cout;
using std::endl;
using std::string;

void test0(void)
{
	char str1[] = "hello,world";
	char str2[100] = "shenzhen";
	const char * str3 = "wangdao"; //C 风格的字符串类型

	cout << sizeof(str1) << endl;
	//strcat(str1, str2);//str1 会越界
	//cout << "str1 = " << str1 << endl;
	cout << "str3 = " << str3 << endl;
	
	//字符串拼接的操作
	int len = strlen(str1) + strlen(str2) + 1;
	char * pstr = (char *)malloc(len);
	memset(pstr, 0, len);
	strcpy(pstr, str1);
	strcat(pstr, str2);
	cout << "pstr = " << pstr << endl;

	free(pstr);
}

void test1(void)
{
	string s1 = "hello,world";//C风格字符串转换成C++风格的字符串
	string s2 = "shenzhen";
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;

	//C++字符串拼接
	string s3 = s1 + s2;
	cout << "s3 = " << s3 << endl;
	string s4 = s1 + "shenzhen";
	cout << "s4 = " << s4 << endl;
	string s5 = "hello,world" + s2;
	cout << "s5 = " << s5 << endl;
	string s6 = s1 + 'A';
	cout << "s6 = " << s6 << endl;
	cout << endl;

	s1.append(s2);
	cout << "s1 = " << s1 << endl;
}
 
int main(void)
{
	//test0();
	test1();
	return 0;
}
```

