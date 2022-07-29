# 1. constexpr函数

constexpr函数是指能用于常量表达式的函数；

- constexpr函数的返回类型及所有形参的类型都是字面值类型，而且函数体中必须有且只有一个return语句；

- constexpr函数和内联函数通常定义在头文件中

```cpp
constexpr int new_sz() { return 42; } // 常量表达式
constexpr int foo = new_sz(); // 正确：foo是常量表达式

constexpr size_t scale(size_t cnt) { return new_sz() * cnt; } // 常量表达式
int arr[scale(2)]; // 常量表达式
int i = 2; // i不是常量表达式
int a2[scale(i)]; // 错误：scale(i)不是常量表达式；
```

# 2. 内联函数

```cpp
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

//带参数的宏定义
//执行的时机：预处理, 进行的是字符串的替换，没有函数调用的开销, 可以提高程序的执行效率
//
//对于简短的语句，定义为函数之后，函数的执行会有开销
//
//但是在使用带参数的宏定义时，容易产生错误

#define Max(x,y) ((x)>(y)?(x):(y))
#define Multiply(x,y) (x)*(y)

//inline函数 --> 内联函数
//也会在调用该函数时，用语句替换, 没有函数调用的开销
//
//相比带参数的宏定义的优势： 有类型检查
inline int max(int x, int y)
{
	return x > y ? x : y;
}

inline int multiply(int x, int y)
{
	return x * y;
}
 
int main(void)
{
	int a = 3, b = 4, c = 5;
	printf("Max(a,b) = %d\n", Max(a,b));
	printf("Multiply(a + b, c) = %d\n", Multiply(a + b, c));// a + b*c
	cout << max(a, b) << endl;
	cout << multiply(a + b, c) << endl;

	return 0;
}
```

# 3. 函数指针

- 函数指针指向的是函数而非对象；
- 函数指针指向某种特定类型；函数的类型由它的返回类型和形参类型共同决定，与函数名无关；
- P221

# 4. lambda表达式

```cpp
[capture list](paramter list) -> return type{function body}

[](int i) -> int {if(i<0) return -i; else return i;}

capture list: 是一个lambda所在函数中定义的局部变量的列表；
paramter list:形参
return type:返回类型
function body:函数体
```

