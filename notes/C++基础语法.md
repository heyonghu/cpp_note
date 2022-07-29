# 1. 命名空间

## 1.1 定义命名空间

C++中定义名称空间的基本格式为：

```cpp
namespace 名称空间名

{

变量类型 变量；

函数返回类型 函数原型；

}
```



- 定义在名称空间中的变量或者函数都称为实体

- 名称空间中的实体作用域是全局的, 并不意味着其可见域是全局的

- 如果不使用作用域限定符和using机制，抛开名称空间嵌套和内部屏蔽的情况，实体的可见域是从实体创建到该名称空间结束

- 在名称空间外，该实体是不可见的。

## 1.2 作用域限定符

在某个名称空间中定义或创建的程序实体，如果要在其他名称空间中或外部函数中访问，可以使用作用域限定符来使实体可见，如：

```cpp
std::cout << 1 << std::endl;
```

 ```cpp
 #include <iostream>
 
 namespace A
 {
 
 void displayA()
 {
 	std::cout << "A::displayA() " << std::endl;// 作用域限定符
 }
 
 }//end of namespace A
 
 using namespace A;
 
 void cout() 
 {
 	std::cout << "cout() " << std::endl;
 }
 
 int main(void)
 {
 	displayA();
 	cout();
 	return 0;
 }
 ```



## 1.3 using声明机制

- 如果不希望在每次使用名称空间中实体时都使用作用域限定符，可使用using声明机制扩展其可见域，using声明的基本格式为：

```cpp
using 名称空间::实体名;
```

- 如`using A::dispA;`，至于`using`声明语句将该实体的可见域扩展到什么程度，这取决于`using`语句的书写位置，换言之，这取决于`using`语句的可见域。

### 1.3.1 using声明机制二义性

- 如果`using`声明使用不当，很容易引起多重声明错误，比如:

已经定义了全局函数`disp`，却还使用全局using声明语句`using A::disp`，假设没有屏蔽发生，那么调用`disp()`时，编译器不确定是全局函数版本还是`A::disp()`，引发多重声明错误。

- 变量名同样存在这种问题

假设有两个名称空间A、B中都定义了`int`型变量`num`，在程序的某处需要使用`num`，如果写出如下代码：

```cpp
using A::num;

using B::num;

num=5;
```

因此，应合理使用`using`声明机制。

### 1.3.2 using编译指令

`using`声明机制使得某个空间中的特定实体可见，`using`编译指令比using声明更进一步，通过`using namespace 名称空间名;`的形式，使得名称空间中的所有实体都可见，不再需要作用域限定符。如

```cpp
using namespace std;
```

```cpp
#include <iostream>
using namespace std;// using编译指令, 会把命名空间std中的所有实体一次性全部引进来, 有可能造成二义性问题

namespace A
{

void displayA()
{
	cout << "A::displayA() " << endl;
}

}//end of namespace A

using namespace A;

void cout() 
{
	
}


int main(void)
{
	displayA();
	// cout(); // error 存在二义性
	return 0;
}

```



## 1.4 名称空间的作用域与可见域

- 原则上讲，名称空间的作用域是全局的，但其可见域却并非如此，而且，不论使用限定符还是使用using声明语句，都要求名称空间可见

- 回头看以下前面给出的代码，如果将namespace B的定义放在namespace A定义之后，编译器将指出错误，using语句同样如此，如果在using声明时，namespace尚未定义，或者说namespace已经定义，但声明的实体尚未包含在此namespace中，编译器同样会指出错误，

- 因此，名称空间同样要先定义、后使用。

## 1.5 名称空间的定义策略

- 假设想实现如下功能：`A::dispA`函数中要访问`B::num`，这要求B定义在A前；同时，在B中增加`dispB`函数，其中调用`A::dispA()`函数，这要求A定义在B之前，如此看来，上述功能似乎不太可能会实现。

- 实则不然，这取决于名称空间的定义策略，在前面提及，名称空间中函数的定义和实现可以分开进行，这是我们解决问题的突破口

- 另外，函数原型可以多次声明

## 1.6 名称空间嵌套

- 名称空间可以定义在另一个名称空间内，以单层嵌套为例，要访问内部名称空间中的实体，必须采用“外部名称空间::内部名称空间::实体名”的形式，如果是多层嵌套，还要多次使用作用域限定符。

```cpp
#include <iostream>

using std::cout;  //using声明机制, 只会引入一个单独的实体
using std::endl;

int num = 1;

//命名空间类似于黑洞
namespace B
{
void displayC();//在命名空间中的函数声明
}



namespace A 
{
int num = 10;
void displayA() 
{
	cout << "A::displayA()" << endl;
	B::displayC();
}


namespace C
{
int num = 22;
void displayC() 
{
	cout << "A::C::num = " << num << endl;
	cout << "A::C::displayC()" << endl;
}
}



}//end of namespace 


namespace B
{
int num = 100;
void displayB(int num)
{
	cout << "形参num = " << num << endl;
	cout << "B::num = " << B::num << endl;
	cout << "A::num = " << A::num << endl;
	cout << "全局变量num = " << ::num << endl;//匿名的命名空间, C的库函数都位于匿名命名空间
	A::displayA();
}

void displayC() 
{
	cout << "displayC() " << endl;
}

}//end of namespace B
 
using A::displayA;
int main(void)
{
	//displayA();
	//B::displayB(1000);

	A::C::displayC();//命名空间的嵌套 

	return 0;
}

```



## 1.7 匿名的名称空间

- 也可以通过省略名称空间的名称来创建匿名的名称空间，此时，该无名空间中的实体的可见性无法扩展（既不能采用“名称空间::实体”的形式，也不能采用using声明机制扩展），因此，该实体只能在本空间内使用。

- 在匿名空间中创建的全局变量，具有全局生存期，却只能被本空间内的函数等访问，是static变量的有效替代手段。

## 1.8 小结

- 本章探讨了名称空间的用法，这是`C++`新增加的一个特性，其目的是为了减少冲突，这在大型程序组织中十分有效。使用名称空间，关键是掌握空间中实体的作用域与可见域，以及名称空间的作用域与可见域的知识，理解其实质，做到知其然，知其所以然。

- `作用域限定符::`、`using声明机制`和`using编译机制`是3种常用的扩展实体可见域的方式，使名称空间中的特定实体或全部实体在声明可见域内可用。名称空间内实体的访问规则和原来介绍的没有名称空间时的情况类似，名称空间还支持嵌套层次结构，在外部使用内层空间时，必须使用多重作用域限定符的形式。

下面引用当前流行的名称空间使用指导原则：

- 提倡在已命名的名称空间中定义变量，而不是直接定义外部全局变量或者静态全局变量。

- 如果开发了一个函数库或者类库，提倡将其放在一个名称空间中。

- 对于using 声明，首先将其作用域设置为局部而不是全局

- 不要在头文件中使用using编译指令，这样，使得可用名称变得模糊，容易出现二义性，其次，包含头文件的顺序可能会影响程序的行为，如果非要使用using编译指令，建议放在所有#include预编译指令后。

# 2. const关键字

## 2.1 定义常量

 ```cpp 
 const int MAX_VAL = 23;
 
 int const MIN_VAL = 0;
 
 const int kMax = 100;v
 ```

- **常量必须进行初始化**

```cpp
#include <iostream>
using std::cout;
using std::endl;

//一个程序经历的阶段:
//编辑 --> 预处理(预编译) --> 编译 --> 汇编 --> 链接 --> 执行


//宏定义发生的时机:预处理, 只是简单的字符串的替换
//（使用宏定义的过程中，有很大的概率会出现问题）
//
//
//const关键字发生的时机: 编译, 有类型检查
//(使用const关键字可以减少犯错的概率)
//
//
//尽量使用const关键字替换宏定义

#define MAX 1000
 
int test0(void)
{
	int num = 2;
	cout << num * MAX << endl;

	return 0;
}

void test1()
{
	//const int num;//error, 常量必须要进行初始化
	const int value = 1;
	//value = 2;//error  常量的值不能进行修改
	cout << "value = " << value << endl;
}

int main(void)
{
	test1();
	return 0;
}
```

## 2.2 定义指向常量的指针(常量指针)

```cpp
int a = 10;
const int *pa = &a;
```

- **常量指针所指向的内容是不可修改的**

## 2.3 定义指针常量

```cpp
int b = 10;
int * const pb = &b;
```

- **因为指针常量是一个常量，在声明的时候一定要给它赋初始值**
- **虽然指针常量的值不能变，可是它指向的对象是可变的**

```cpp
#include <iostream>
using std::cout;
using std::endl;

//int (*p) []  vs     int * p []     
//数组指针   vs   指针数组
//int (*p)()  vs   int * pfunc()
//函数指针   vs   指针函数

//常量指针  vs  指针常量

void test0(void)
{
	int num1 = 10;
	int num2 = 11;
	const int * pa = &num1;//常量指针(pointer to const)
	//*pa = 20;//error  不能通过指针pa更改所指变量的值
	pa = &num2;//可以改变指针pa的指向

	int const * pb = &num1;
	//*pb = 20;//error
	pb = &num2;

	int * const pc = &num1;//指针常量(const pointer)
	*pc = 20;// 可以通过指针pc改变所指变量的值
	//pc = &num2;//error, 不能改变指针的指向
	
	const int * const pd = &num1;// 两者都不能进行修改
}
 
int main(void)
{
	test0();
	return 0;
}
```



## 2.4 定义指向常量的指针常量

```cpp
const int a = 10;
const int * const pa = &a;
```

- 因为是一个指针常量，那么它指向的对象当然是一个指针对象，而它又指向常量，说明它指向的对象不能变化。

## 2.5 const和define的区别

1) 编译器处理方式不同·

   - `define`宏是在预处理阶段展开。

   - `const`常量是编译运行阶段使用。

2) 类型和安全检查不同

   - `define`宏没有类型，不做任何类型检查，仅仅是展开。

   - `const`常量有具体的类型，在编译阶段会执行类型检查。

•注意：尽量以`const`替换`#define`

## 2.6 引用

引用就是某一变量（目标）的一个别名，对引用的操作与对变量直接操作完全一样。

```cpp
int a ;
int &refa = a;
```

- &在此不是求地址运算，而是起标识作用。
- 类型标识符是指目标变量的类型
- 声明引用时，必须同时对其进行初始化
- 引用跟某一变量绑定之后，不能再绑定到其它变量之上

## 2.7 引用作为函数参数

- C语言中函数参数传递是值传递，如果有大块数据作为参数传递的时候，采用的方案往往是指针，因为这样可以避免将整块数据全部压栈，可以提高程序的效率。

- 但是现在C++中又增加了一种同样有效率的选择，就是引用。

- Example:

 ```cpp
 swap(int &x, int &y)
 ```

- 传递引用给函数与传递指针的效果是一样的。这时，被调函数的形参就成为原来主调函数中的实参变量或对象的一个别名来使用，所以在被调函数中对形参变量的操作就是对其相应的目标对象的操作

- 使用引用传递函数的参数，在内存中并没有产生实参的副本，它是直接对实参操作；而使用一般变量传递函数的参数，当发生函数调用时，需要给 形参分配存储单元，形参变量是实参变量的副本；

- 使用指针作为函数的参数虽然也能达到与使用引用的效果，但是，在被调函数中同样要给形参分配存储单元，且需要重复使用"*指针变量名"的 形式进行运算，这很容易产生错误且程序的阅读性较差；另一方面，在主调函数的调用点处，必须用变量的地址作为实参。

- 如果既要利用引用提高程序的效率，又要保护传递给函数的数据不在函数中被改变，就应使用常引用。

```cpp
int a = 10;
const int &refa = a;
```

```cpp
#include <iostream>
using std::cout;
using std::endl;

//引用与指针的差别?
//相同点:  都有地址的概念
//
//不同点: 
//1. 指针是可以独立存在的; 但是引用不行
//2. 引用必须要进行初始化，指针没有必要
//3. 指针可以设置为NULL， 但是引用不行
//4. 引用一旦进行初始化之后，不会再改变其指向；但指针可以
//
//引用是受限制的指针



void test0(void)
{
	int num = 100;
	int & ref = num;// 引用是一个变量的别名, 引用的初始化
	cout << "num = " << num << endl;
	cout << "ref = " << ref << endl;
	cout << "&num = " << &num << endl;
	cout << "&ref = " << &ref << endl;

	ref = 200;
	cout << "修改引用之后:" << endl;
	cout << "num = " << num << endl;
	cout << "ref = " << ref << endl;

	//int & ref1;//error,  引用是不能独立存在的，必须要绑定到某一个变量上
}
 
//引用作为函数的参数

//参数的传递：值传递
#if 0
void swap(int x, int y)
{
	int temp = x;
	x = y;
	y = temp;
}
#endif

//参数的传递: 地址传递 --> 值传递
void swap(int * px, int * py)
{
	int temp = *px;
	*px = *py;
	*py = temp;
}

//引用传递它减少了数据的复制, 可以提高程序的执行效率
//
//引用传递操作的就是实参本身
//
void swap(int & x, int & y)
{
	int temp = x;
	x = y;
	y = temp;
}


void test1(void)
{
	int a = 3, b = 4;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	swap(a, b);// 引用传递比地址传递更直观
	//swap(&a, &b);
	cout << "交换之后:" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}

int main(void)
{
	//test0();
	test1();

	return 0;
}

```



 ## 2.8 引用作为函数返回值

- 以引用返回函数值，定义函数时需要在函数名前加&
- 用引用返回一个函数值的最大好处是，在内存中不产生被返回值的副本。
- 必须遵守的规则：
  - 不能返回局部变量的引用。
  - 不能返回函数内部new分配的内存的引用。例如，被函数返回的引用只是作为一个临时变量出现，而没有被赋予一个实际的变量，那么这个引用所指向的空间（由new分配）就无法释放，造成memory leak。

```cpp
#include <iostream>
using std::cout;
using std::endl;


//引用作为函数的返回值

int arr[5] = {0, 1, 2, 3, 4};

int & func(int idx)  // 返回值是引用，返回的变量生命周期一定要大于函数本身
{
	return arr[idx];
}

int func1() 
{
	int number = 10;
	return number;//一旦执行return语句时，就会被复制
}

//不要返回一个局部变量的引用
int & func2() 
{
	int number = 10;
	return number;
}

int * func3()
{
	int number = 10;
	return &number;
}


//不要轻易返回一个堆空间变量的引用，
//除非有了一个回收空间的策略
int & func4() 
{
	int * p = new int(11);
	return *p;
}

int main(void)
{
	cout << func(0) << endl;

	func(0) = 10;
	cout << "arr[0] = " << arr[0] << endl;

	//cout <<	func2() << endl;
	
	int a = 3, b = 4;
	int c = a + b + func4();//每调用一次func4函数，就会产生一次内存泄漏
	cout << "c = " << c << endl;

	int & ref = func4();
	cout << "ref = " << ref << endl;
	delete &ref;

	return 0;
}
```



## 2.9 引用和指针的区别

- 相同点：都是地址的概念
- 不同点：
  - 指针是一个实体，而引用仅是个别名； 
  - 引用使用时无需解引用（*），指针需要解引用
  - 引用只能在定义时被初始化一次，之后不可变；指针可变
  - 引用不能为空，指针可以为空

# 3.内联函数

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

# 4. new和delete

```cpp
#include <string.h>
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

//malloc/free与new/delete的差别是什么?
//
//1. malloc/free是标准库函数, new/delete 是表达式
//2. malloc只负责开辟空间，但并不会进行初始化;
//   new表达式开辟空间之后，也会进行初始化

void test0(void)
{
	int * p = (int *)malloc(sizeof(int));// 开辟堆空间
	*p = 10;
	cout << "*p = " << *p << endl; // *p = 10

	int * p2 = (int *) malloc(sizeof(int) * 10);
	::memset(p2, 0, sizeof(int) * 10);
	//bzero();
	for(int idx = 0; idx < 10; ++idx)
		p2[idx] = idx;

	free(p);
	free(p2);
}

void test1(void)
{
	int * p = new int(1);
	cout << "*p = " << *p << endl; // *p = 1

	int * p2 = new int[10]();
	for(int idx = 0; idx < 10; ++idx)
		p2[idx] = idx;

	delete p;
	delete [] p2;
}
 
int main(void)
{
	test0();
	test1();

	return 0;
}

```

## 4.1 对象的大小(sizeof)

- 对象占据一定大小的内存空间。总的来说，对象在内存中是以结构形式（只包括非static数据成员）存储在数据段或堆中，类对象的大小（sizeof）一般是类中所有非static成员的大小之和。在程序编译期间，就已经为static变量在静态存储区域分配了内存空间，并且这块内存在程序的整个运行期间都存在。而类中的成员函数存在于代码段中，不管多少个对象都只有一个副本。

- 对象的大小，有一些特殊之处需要强调：

  - C++将类中的引用成员当成“指针”来维护，占据4个内存字节。

  - 如果类中有虚函数(后面课程将会介绍)时，虚析构函数除外，还会额外分配一个指针用来指向虚函数表（vtable），因此，这个时候对象的大小还要加4。

  - 指针成员和引用成员属于“最宽基本数据类型”的考虑范畴。

- 见备注代码

```cpp

#include <iostream>
using namespace std;

class cex
{
private:
	int a;	//int型，在一般系统上占据4个内存字节	4
	char b;	//char型，占1个内存字节					1 + 3 (3浪费)
	float c;	//单精度浮点型，占4个内存字节	4 + 4 (4浪费)
	double d;	//double型，占8个内存字节		8
	short e[5]; //short型数组，每个元素占2个内存字节	8 + 2
	char & f;	//引用，当成指针维护	2 + 4 (2浪费)
	double & g; //引用，当成指针维护	4 + 4 (后4浪费)
	static int h;	//static成员，公共内存，不影响单个对象的大小 0
	
public:
	cex():f(b), g(d) //和构造函数，引用成员必须在初始化表中初始化
	{
	}
	void print()	//成员函数的定义，普通成员函数不影响对象大小
	{
		cout << "Hello" << endl;
	}
};

int cex::h = 0;		//static成员的初始化

int main()
{
	cex c;
	cout << "sizeof(cex):  " << sizeof(cex) << endl; //输出类对象的大小sizeof(cex) = 48
	return 0;
}
```



# 5. 类型转换

- 前面已经对普通变量的类型转换进行了介绍，本节来讨论类对象和其他类型对象的转换

- 转换场合有：

  - 赋值转换

  - 表达式中的转换

  - 显式转换

  - 函数调用，传递参数时的转换

- 转换方向有：

  - 由定义类向其他类型的转换

  - 由其他类型向定义类的转换

- 下面分别展开讨论

```cpp
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

void test0(void)
{
	int a = 10;
	double d1 = (double)a;
	double d2 = double(a);
	cout << "d1 = " << d1 << endl;
	cout << "d2 = " << d2 << endl;
}

void test1(void)
{
	int a = 10;
	double d1 = static_cast<double>(a);
	cout << "d1 = " << d1 << endl;

	int * p = static_cast<int*>(malloc(sizeof(int)));
	*p = 10;

	//static_cast/const_cast/dynamic_cast/reinterpret_cast
}
 
int main(void)
{
	test1();

	return 0;
}

```

- 由其他类型（如int、double）等向自定义类的转换是由构造函数来实现的，只有当类的定义和实现中提供了合适的构造函数时，转换才能通过。什么样的构造函数才是合适的构造函数呢？主要有以下几种情况，为便于说明，假设由int类型向自定义point类转换：

  - point类的定义和实现中给出了仅包括只有一个int类型参数的构造函数 Point pt1 = 5;

  - point类的定义和实现中给出了包含一个int类型参数，且其他参数都有缺省值的构造函数

  - point类的定义和实现中虽然不包含int类型参数，但包含一个非int类型参数如float类型，此外没有其他参数或者其他参数都有缺省值，且int类型参数可隐式转换为float类型参数。

- 在构造函数前加上关键字explicit可以关闭隐式类型转换

- 见备注代码

```cpp
//9-12 由其他类型转换到自定义类型
#include <iostream>
using namespace std;

class point;

class anotherPoint //anotherPoint类定义
{
private: //private成员列表
	double x;
	double y;

public:
	anotherPoint(double xx = 1, double yy = 1) //构造函数，带缺省参数值
	{
		x = xx;
		y = yy;
	}

	void print()			//输出函数，点的信息
	{
		cout << "( " << x << " , " << y << " )";
	}

	friend class point;		//使point类成为本类的友元类, 这样point
							//类就可以访问anotherPoint 类的private变量了
};

class point		//point类定义
{
private:		//private成员列表
	int xPos;
	int yPos;

public:
//	explicit //如果在构造函数前加上explicit, 就不允许 point pt1 = 5这种隐式转换了
	point(int x = 0, int y = 0)	//构造函数，带缺省参数，两个int型变量
	{
		xPos = x;
		yPos = y;
	}

	point(anotherPoint aP)		//构造函数，参数为anotherPoint类对象
	{
		xPos = aP.x;			//由于point类是anotherPoint类的友元类,
		yPos = aP.y;			//因此这里可以访问anotherPoint的私有变量x和y
	}

	void print()				//输出函数，点的信息
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}
};

int main()
{
	//1. 将int类型数字5转换成point类型
	point p1;			//创建point类对象p1，采用带缺省参数的构造函数，即x＝0、y＝0
	cout << 5 << " 转换成 ";
	p1 = 5;				//等价于p1＝point(5,0);
	p1.print();			//输出点p1的信息
	
	//2. 将double类型变量dX转换成point类型
	double dX = 1.2;	//声明一个double变量dX
	cout << dX << " 转换成 ";
	p1 = dX;			//等价于p1=point(int(dX),0)
	p1.print();			//输出点p1的信息
	
	//3. 将anotherPoint类型转换成point类型
	anotherPoint p2(12.34, 56.78);	//创建anotherPoint类的对象p2
	p2.print();
	cout << " 转换成 ";
	p1 = p2;			//等价于p1=point(p2);
	p1.print();			//输出点p1的信息

	//4. 测试在point构造函数前加上explicit以阻止隐性转换的情况
	
	return 0;
}
```

## 5.1 类型转换函数

- 可以通过operator int()这种类似操作符重载函数的类型转换函数来实现由自定义类型向其他类型的转换。如将point类转换成int类型等。

- 在类中定义类型转换函数的形式一般为：

```cpp
operator 目标类型名();
```

- 有以下几个使用要点：

  - 转换函数必须是成员函数，不能是友元形式。

  - 转换函数不能指定返回类型，但在函数体内必须用return语句以传值方式返回一个目标类型的变量。

  - 转换函数不能有参数。 

- 见备注代码

```cpp
//类型转换函数(由类转换成其他类型)
#include <iostream>
using namespace std;

class point;
ostream & operator<<(ostream &os, const point &pt);

class anotherPoint		//anotherPoint类定义
{
private:			//private成员列表
	double x;
	double y;

public:
	anotherPoint(double xx = 1.11, double yy = 1.11)//构造函数，带缺省参数值
	{
		x = xx;
		y = yy;
	}

	void print()	//成员函数，输出点的信息
	{
		cout << "( " << x << " , " << y << " )" << endl;
	}
};

class point		//Point类定义
{
private:		//private成员列表
	int xPos;
	int yPos;

public:
	point(int x = 0, int y = 0)		//构造函数，带缺省参数值
	{
		xPos = x;
		yPos = y;
	}

	void print()	//成员函数，输出点的信息
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}

	friend ostream & operator<<(ostream &os, const point &pt);	// 重载<<运算符

	operator int()	//定义Point向int型的转换函数int()
	{
		return xPos;
	}

	operator double()	//定义Point向double型的转换函数double()
	{
		return xPos * yPos;
	}

	operator anotherPoint()	//定义Point向anotherPoint型的转换函数anotherPoint()
	{
		return anotherPoint(xPos, yPos);
	}
};

ostream & operator<<(ostream &os, const point &pt)
{
	os << (pt.xPos * 100);
	return os;
}

int main()
{
	point p1(4, 5);			//声明一个point类变量p1
	p1.print();

	//1. point转换成int
	int x1 = p1;		//p1赋值给一个int型变量，point中的转换函数int()被隐式调用
	cout << x1 << endl;

	//2. point转换成double
	double dX = p1;	     //p1赋值给一个double型变量，point中的转换函数double()被隐式调用
	cout << dX << endl;

	//3. point转换成anotherPoint
	anotherPoint p2;		//声明anotherPoint类对象p2，构造函数采用缺省值
	p2 = p1;		//p1赋值给p2，point中的转换函数anotherPoint()被隐式调用
			//等价于p2＝anotherpoint(p1.xPos,p1.yPos)
	p2.print();		//看p2是否修改成功

	return 0;
}

```

# 6. 左值和右值

## 6.1 什么是左值，什么是右值？

- 最常见的误解：
  - 等号左边的就是左值，等号右边的就是右值

- 左值和右值都是针对表达式而言的，

- 左值是指表达式结束后依然存在的持久对象

- 右值是指表达式结束时就不再存在的临时对象

- 区分：
  - 能对表达式进行取地址，则为左值
  - 否则为右值

## 6.2 左值引用

- 根据其修饰符的不同，可分为非常量左值引用和常量左值引用

```cpp
int ia = 10;    int &a = ia;
const int ib = 30; int &b = ib;
const int &ri = 20;
```

- 非常量左值引用只能绑定到非常量左值

- 常量左值引用可以绑定到所有类型的值，包括 非常量左值、常量左值、右值(根据语法规则，无法区分出右值)

非常量左值引用只能绑定到非常量左值，不能绑定到常量左值、非常量右值和常量右值。

- 1. 如果允许绑定到常量左值和常量右值，则非常量左值引用可以用于修改常量左值和常量右值，这明显违反了其常量的含义。
- 2. 如果允许绑定到非常量右值，则会导致非常危险的情况出现，因为非常量右值是一个临时对象，  非常量左值引用可能会使用一个已经被销毁了的临时对象。

## 6.3 右值引用

```cpp
std::vector<String> v;
v.push_back(“hello,world”);
```

- 调用 `String::String(const char *);`

- 调用`String::String(const String&);`

- 调用 `String::~String()`

- 问题症结在于，临时对象的构造和析构带来了不必要的资源拷贝

- 如果有一种机制，可以在语法层面识别出临时对象，在使用临时对象构造新对象（拷贝构造）的时候，将临时对象所持有的资源『转移』到新的对象中，就能消除这种不必要的拷贝。

- 这种语法机制就是『右值引用』



- 右值引用 `int &&refa;`

- 引入右值引用后，『引用』到『值』的绑定规则也得到扩充：

- 左值引用可以绑定到左值: `int x; int &xr = x;`

- 非常量左值引用不可以绑定到右值: `int &r = 0;`

- 常量左值引用可以绑定到左值和右值：`int x;   const int &cxr = x; const int &cr = 0;`

- 右值引用可以绑定到右值：`int &&r = 0;`

- 右值引用不可以绑定到左值：`int x; int &&xr = x;`

- 常量右值引用没有现实意义（毕竟右值引用的初衷在于移动语义，而移动就意味着『修改』）。

## 6.4 移动语义--`std::move`

- 编译器只对右值引用才能调用转移构造函数和转移赋值函数，而所有命名对象都只能是左值引用，如果已知一个命名对象不再被使用而想对它调用转移构造函数和转移赋值函数，也就是把一个左值引用当做右值引用来使用，怎么做呢？标准库提供了函数 `std::move`，这个函数以非常简单的方式将左值引用转换为右值引用。

- 对于右值引用而言，它本身是右值么？

- 示例

  - 1.字符串的定义

  - 2.ArrayWrapper

```cpp
1. 字符串的定义
class String {
public:
    String(const String &rhs) { ... }
    String(String &&rhs) {
        s_ = rhs.s_;
        rhs.s_ = NULL;
    }
    String& operator=(const String &rhs) { ... }
    String& operator=(String &&rhs) {
        if (this != &rhs) {
            delete [] s_;
            s_ = rhs.s_;
            rhs.s_ = NULL;
        }
        return *this;
    }
private:
    char *s_;
};

2. std::move

#include <iostream>


class MetaData
{
public:
	MetaData(int size, const std::string &name)
		: name_(name),
		  size_(size)
	{}

	MetaData(const MetaData &other)
		: name_(other.name_),
		  size_(other.size_)
	{
		std::cout << "MetaData(const MetaData &other)" << std::endl;
	}


	MetaData(MetaData &&other)
		//: name_(other.name_), //调用复制构造函数
		: name_(std::move(other.name_)),//std::move 将对象变成一个右值，但并不移动数据
		  size_(other.size_)
	{
		std::cout << "MetaData(MetaData &&other)" << std::enl;
	}

	std::string getName() const { return name_; }	

	int getSize() const { return size_; }

private:
	std::string name_;
	int size_;
};

class ArrayWrapper
{
public:
	ArrayWrapper()
		: pVals_(new int [64]),
		  metadata_(64, "ArrayWrapper")
	{}

	ArrayWrapper(int n)
		: pVals_(new int[n]),
		  metadata_(n, "ArrayWrapper")
	{}

	ArrayWrapper(const ArryWrapper &other)
		: pVals_(new int[other.metadata_.getSize()]),
		  metadata_(other.metadata_)
	{
		std::cout << "ArrayWrapper(const ArryWrapper &other)" << std::endl;
		for(int idx = 0; idx != size_; ++idx)
		{
			pVals_[idx] = other.pVals_[idx];
		}
	}

	ArrayWrapper(ArrayWrapper &&other)//移动构造函数
		: pVals_(other.pVals_),
		  //metadata_(other.metadata_)// 调用MetaData的复制构造函数
		  metadata_(std::move(other.metadata_))
	{
		std::cout << "ArrayWrapper(ArrayWrapper &&other)" << std::endl;
		other.pVals_ = NULL;
	}

	~ArrayWrapper()
	{
		delete []pVals_;
	}

private:
	int *pVals_;
	MetaData metadata_;
};

```

