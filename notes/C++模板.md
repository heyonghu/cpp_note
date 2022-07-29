# 1. 模板

- 现在的C++编译器实现了一项新的特性：模板（Template），简单地说，模板是一种通用的描述机制，也就是说，使用模板允许使用通用类型来定义函数或类等，在使用时，通用类型可被具体的类型，如int、double甚至是用户自定义的类型来代替。模板引入一种全新的编程思维方式，称为“泛型编程”或“通用编程”。

- 形象地说，把函数比喻为一个游戏过程，函数的流程就相当于游戏规则。

- 在以往的函数定义中，总是指明参数是int型还是double型等等，这就像是为张三（好比int型）和李四（好比double型）比赛制定规则。可如果王五（char*型）和赵六（bool型）要比赛，还得提供一套函数的定义，这相当于又制定了一次规则，显然这是很麻烦的。

- 模板的的引入解决了这一问题，不管是谁和谁比赛，都把他们定义成A与B比赛，制定好了A与B比赛的规则（定义了关于A和B的函数）后，比赛时只要把A替换成张三，把B替换成李四就可以了，大大简化了程序代码量，维持了结构的清晰，大大提高了**程序设计**的效率。该过程称为“类型参数化”。

- 强类型程序设计中，参与运算的所有对象的类型在编译时即确定下来，并且编译程序将进行严格的类型检查。为了解决强类型的严格性和灵活性的冲突。有以下3中方式解决：

  - 带参数宏定义（原样替换）

  - 重载函数（函数名相同，函数参数不同）

  - 模板（将数据类型作为参数）

```cpp
//求最大值
//宏定义
#include <iostream>
using namespace std;

#define MAX(x, y)  ((x) > (y) ? (x) : (y))

int main()
{
	cout << MAX(3, 4) << endl;
	cout << MAX(3.4, 2.9) << endl;
	return 0;
}

//重载函数
#include <iostream>
using namespace std;

int MAX(int a, int b)
{
	return a > b ? a : b;
}

double MAX(double a, double b)
{
	return a > b ? a : b;
}

int main()
{
	cout << MAX(3, 4) << endl;
	cout << MAX(3.4, 2.9) << endl;
	return 0;
}


//模板
#include <iostream>
using namespace std;

template <typename T>
T MAX(T a, T b)
{
	return a > b ? a : b;
}

int main()
{
	cout << MAX(3, 4) << endl;
	cout << MAX(3.4, 2.9) << endl;
	return 0;
}

```

- 在讲解类型参数化之前，先来看一个示例：

```cpp
int add(int x, int y) //定义两个int类型相加的函数
{
    return x + y;
}

double add(double x, double y) //重载double类型
{
    return x + y;
}

char *add(char *px, char *py)//重载字符数组
{
    return strcat(px, py); //调用库函数strcat
}
```

```cpp
#include <iostream>
using namespace std;

int add(int x, int y)			//定义两个int类型相加的函数
{
	return x + y;
}

double add(double x, double y) //重载两个double类型相加的函数
{
	return x + y;
}

char* add(char* px, char* py)			//重载两个字符数组相加的函数
{
	return strcat(px, py);				//调用库函数strcat
}

int main()
{
	cout << add(1, 2) << endl;			//调用add(const int,const int)

	cout << add(3.0, 4.0) << endl;		//调用add(const double,const double)

	char x[10] = "Hello ";				//创建字符数组，注意要留够大小
	char y[] = "C++";
	cout << add(x, y) << endl;			//调用add(char*,char*)

	return 0;
}
```

## 1.1 模板的定义

- 模板的引入使得函数定义摆脱了类型的束缚，代码更为高效灵活。C＋＋中，通过下述形式定义一个模板：

```cpp
template <class T，...>
或
template<typename T>
```

- 早期模板定义使用的是`class`，关键字`typename`是最近才加入到标准中的，相比`class`，`typename`更容易体现“类型”的观点，虽然两个关键字在模板定义时是等价的，但从代码兼容的角度讲，使用class较好一些。

- 模板有函数模板和类模板之分。通过参数实例化构造出具体的函数或类，称为模板函数或模板类。

- 见备注代码

```cpp
//模板
#include <iostream>
#include <string>					//使用标准类库中提供的string类时必须包含此头文件
using namespace std;

template <typename T>
T add(const T &a, const T &b)
{
	return a + b;
}

int main()
{
	cout << add(10, 20) << endl;	//调用add(const int,const int)
	cout << add(1.0, 2.0) << endl;	//调用add(const double,const double)
	string x("Hello,"), y("world");
	cout << add(x, y) << endl;		//调用add(string,string)

	return 0;
}
```

# 2.函数模板

- 之前代码中的add函数便是一个函数模板，编译器根据函数模板的定义，检查传入的参数类型，生成相应的函数，并调用之。函数模板的定义形式如下：

```cpp
 template <模板参数表>
 返回类型 函数名（参数列表）
 { //函数体 }
```

- 关键字template放在模板的定义与声明的最前面，其后是用逗号分隔的模板参数表，用尖括号（<>）括起来。模板参数表不能为空，模板参数有两种类型：

  - class或typename修饰的类型参数，代表一种类型；

  - 非类型参数表达式,必须是整型类型，使用已知类型符，代表一个常量

```cpp
//带非类型参数
template <typename T, int NUM>
T fun(T a)
{
	return a * NUM;
}

//调用
cout << fun<int, 4>(3) << endl;
```

- 返回类型和函数的参数列表中可以包含类型参数，在函数中可以使用模板参数表中的常量表达式，如：

```cpp
template <class T1,class T2,int number>
double fun(T1 a,int b,T2 c)
{
 return a * (number + b) * c;
 //函数体，其中number可以作为一个int型常量来使用
}
```

```cpp
//带非类型参数
template <typename T, int NUM>
T fun(T a)
{
	return a * NUM;
}

//调用
cout << fun<int, 4>(3) << endl;
```

## 2.1 函数模板的使用

- 函数模板的使用规则和普通函数是相同的，在使用函数模板之前，必须对函数模板进行声明，此声明必须在外部进行，也就是说不能在任何一个函数（包括main函数）中声明，声明的格式为：

```cpp
template <class T1[，class T2，……]>
函数原型
```

- 和普通函数一样，如果在使用函数模板前对函数模板进行了定义，函数模板的声明可以省略。

## 2.2 实例化

- 函数模板实际上不是个完整的函数定义，因为其中的类型参数还不确定，只是定义了某些类型的角色（或变量）在函数中的操作形式，因此，必须将模板参数实例化才能使用函数，用模板实例化后的函数也称为模板函数.

- 分为隐式实例化和显式实例化

```cpp
//12-3 函数模版的隐式实例化
#include <iostream>
using namespace std;

template <class T>
T Max(T x, T y);	//函数模版的申明

int main()
{	
	int intX = 1, intY = 2;
	double dblX = 3.9, dblY = 2.9;
	cout << Max(intX, intY) << endl;	//实参为int型，生成int型模板函数，并对第二个参数进行检查
	//或者cout << Max<int>(intX, intY) << endl;
	cout << Max(dblX, dblY) << endl;	//实参为double型，生成double型模板函数，并对第二个参数进行检查
	//或者cout << Max<double>(dblX, dblY) << endl;

	return 0;
}

template <class T>
T Max(T x, T y)		//函数模版的实现
{
	return (x > y ? x : y);
}
```

## 2.3 重载

- 函数模板支持重载，既可以模板之间重载（同名模板），也可以实现模板和普通函数间的重载，但模板的重载相比普通函数的重载要复杂一点，首先看一个例子：

```cpp
template <class T1,class T2>
T1 Max(T1 a,T2 b){……}

  与

template <class T3,class T4>
T3 Max(T3 c,T4 d){……}
```

- 看似不同的两个模板，仔细分析后发现，其本质是一样的，如果调用“Max(2,3.5);”，都实例化为“Max(int,double);”，会出现重复定义的错误。

   仅仅依靠返回值不同的模板重载也是不合法的，如：

```cpp
template <class T1,class T2>
T1 Greater(T1 a,T2 b){……}

   与

template <class T3,class T4>
T3* Greater(T3 c,T4 d){……}
```

```cpp
template<class T> 
T Func(T t)
{
		return t;
}
template<class T>
int Func(int i,T t)
{
		return i*t;
}

//1函数模板和确定数据类型的函数的重载
#include <iostream.h>

template < class T >
T Max(T x, T y);

int Max(int x, int y)
{
	return x > y ? x : y;
}

int main()
{
	int intX = 1, intY = 2;
	double dblX = 3.0, dblY = 2.9;
	
	cout << Max(intX, intY) << endl;			//调用Max(int,int)

	cout << Max<double>(dblX, dblY) << endl;		//显示实例化为double型，生成double型模板函数
	cout << Max('A', '8') << endl;				//隐式实例化char型，生成char型模板函数
	return 0;
}

template <class T>
T Max(T x, T y)
{
	return x > y ? x : y;
}

//2函数模板和函数模板的重载
#include <iostream.h>

template < class T >
T Max(T x, T y);

template <class T>
T Max(T x, T y, T z)
{
	return x > y ? (x > z ? x : z) : (y > z ? y : z);
}

int main()
{
	int intX = 1, intY = 2, intZ = 3;
	double dblX = 3.0, dblY = 2.9;
	
	cout << Max<int>(intX, intY) << endl;	//调用实例化的Max(int,int)
	cout << Max<int>(intX, intY, intZ) << endl;	//调用实例化的Max(int,int,int)
	cout << Max<double>(dblX, dblY) << endl;	//显示实例化为double型，生成double型模板函数
	cout << Max('A', '8') << endl;			//隐式实例化char型，生成char型模板函数
	return 0;
}

template <class T>
T Max(T x, T y)
{
	return x > y ? x : y;
}

//3 普通函数模板和数组的重载
#include <iostream>
using namespace std;

template <typename T>
T MAX(T a, T b)
{
	return a > b ? a : b;
}

template <typename T>
T MAX(T a[], int n)
{
	T max = a[0];
	for(int i = 1; i < n; i++)
	{
		if(max < a[i])
		{
			max = a[i];
		}
	}

	return max;
}

int main()
{
	cout << MAX(3, 4) << endl;	//或cout << MAX<int>(3, 4) << endl;

	int a[] = {2, 9, 7, 3, 8, 5};
	cout << MAX(a, sizeof(a) / sizeof(a[0])) << endl;//或cout << MAX<int>(a, sizeof(a) / sizeof(a[0])) << endl;
	return 0;
}
```

## 2.4 优先级与执行顺序

- 总体来说，一般函数优先于模板函数的执行

- 见备注代码

```cpp
int Max(int i1,int i2)
{
	cout<<"Normal Max"<<endl;
	return i1>i2? i1:i2;
}
template<class T> 
T Max(T t1, T t2)
{
	cout<<"Template Max,sizeof(t1):"<<sizeof(t1)<<endl;
	return t1>t2? t1:t2;
}
int main(int argc, char* argv[])
{
	int i1=1,i2=9;
	char c1='a',c2='b';
	int iRet=Max(i1,i2);			//调用普通函数int Max(int i1,int i2)
	char cRet=Max(c1,c2);			//调用模板实例化生成的char Max(char a,char b)
	int iRet2=Max(c1,c2);			//调用模板实例化生成的char Max(char a,char b)，最后将返回值隐式转换成int型
	int cRet2=Max<char>(i1,i2);		//调用模板实例化生成的char Max(char a,char b)，
	return 0;
}

```

## 2.5 普通类的成员函数模板

- 成员模板(member template) 既可以定义在普通类(ordinary class), 也可以定义在类模板(class template)

- 在普通类中, 使用成员函数模板时, 不用提供模板参数, 函数可以根据使用的参数,自动推导(deduce)模板实参(template argument)对应的模板形参(template parameter)；

## 2.6 可变模板参数---- C++11新特性

- 可变模板参数(variadic templates)是C++11新增的最强大的特性之一,它对参数进行了高度泛化,它能表示0到任意个数、任意类型的参数

- 由于可变模版参数比较抽象，使用起来需要一定的技巧，所以它也是C++11中最难理解和掌握的特性之一

## 2.7 参数包(parameter pack)

- 模板参数包，如:`template<typename… Args>class tuple;`
  - Args标识符的左侧使用了省略号,在C++11中Args被称为“模板参数包”,表示可以接受任意多个参数作为模板参数,编译器将多个模板参数打包成“单个”的模板参数包.

- 函数参数包，如 `template<typename…T> void f(T…args);`
  - `args`被称为函数参数包,表示函数可以接受多个任意类型的参数.

- 在C++11标准中，要求函数参数包必须唯一，且是函数的最后一个参数; 模板参数包则没有

- 当声明一个变量(或标识符)为可变参数时，省略号位于该变量的左侧

- 当使用参数包时，省略号位于参数名称的右侧，表示立即展开该参数，这个过程也被称为解包

## 2.8 包扩展表达式

- 设`args`被声明为一个函数参数包，其扩展方式有

```cpp
printArgs(args…)
   相当于printArgs(args1,args2,…,argsN)

printArgs(args)…
   相当于printArgs(args1),…, printArgs(argsN)

(printArgs(args),0)…  逗号表达式

这是一个逗号表达式
	相当于(printArgs(args1),0),…(printArgs(argsN),0)
```

- 包扩展表达式`“exp…”`相当于将省略号左侧的参数包`exp`视为一个整体来进行扩展

## 2.9 可变模板参数的优势

- 获取可变模板参数的个数

```cpp
sizeof...(Args)

sizeof...(args)
```

- 优势如下

  - 1. 参数个数，那么对于模板来说，在模板推导的时候，就已经知道参数的个数了，也就是说在编译的时候就确定了，这样编译器就存在可能去优化代码

  - 2. 参数类型，推导的时候也已经确定了，模板函数就可以知道参数类型了

# 3. 类模板

- 理解了函数模板的应用，类模板的提出似乎是水到渠成的事。我们先编写一个普通的处理`int`类型数据的栈类`StackA`，然后将其改造成模版类，改造完成的代码见备注代码。示例代码相对完整地实现了一个栈类`Stack`，列出了类模板和成员函数模板。模板的引入使得类的定义更为灵活，可以在类创建时指明其中的元素类型T，以及非类型常量`num`的大小，需要注意的是，不管是类定义还是成员函数定义，都要遵守模板的定义形式。

- 注意，类模板和成员函数模板不是传统意义上的类定义和成员函数定义，由类模板实例化而生成的具体类称为模板类。定义模板类对象的格式为：

​	 `类模板名<T> 对象名;  eg: Stack<int, 10> stack;`

​	`其中类模板参数可以给默认值，但函数模板在C++11之前不能给默认值，C++11之后是可以给默认值的。`

​	`如果出现非类型参数，则必须是整型。`

```cpp
///普通类-->模版类
//#include <iostream>
//using namespace std;
//
//class StackA
//{
//private:
//	int point;
//	int size;
//	int *sz;
//
//public:
//	StackA(int iNum = 1)
//	{
//		point = 0;
//		size = iNum;
//		sz = new int[size];
//	}
//	~StackA()
//	{
//		delete []sz;
//	}
//	bool isEmpty() {return point == 0;}
//	bool isFull() {return point == size;}
//	int &GetPos() {return point;}
//	bool push(const int & obj);
//	bool pop(int & obj);
//};
//
//bool StackA::push(const int & obj)
//{
//	if (isFull())
//		return false;
//	else
//	{
//		sz[point++] = obj;
//		return true;
//	}
//}
//
//bool StackA::pop(int & obj)
//{
//	if (isEmpty())
//		return false;
//	else
//	{
//		obj = sz[--point];
//		return true;
//	}
//}
//
//int main()
//{
//	StackA st(10);			//普通类, int类型
////	StackA<int> st(10);			//模版类, int类型
//	cout << "开始时st是否为空？ " << st.isEmpty() << endl;
//	
//	st.push(5);			//压入元素5
//	cout << "此时st是否为空？ " << st.isEmpty() << endl;
//	
//	for (int i = 1; i < 10; i++)
//	{
//		st.push(i);		//压入9个元素
//	}
//	cout << "此时st是否已满？" << st.isFull() << endl;
//	
//	int rec = 0;
//	while (st.pop(rec))
//		cout << rec << "  ";
//	cout << endl;
//	
//	return 0;
//}
//

//12-8 类模版
#include <iostream>
using namespace std;

template <class T, int num>		//类型参数表
//或template <class T = int, int num = 10>
class Stack						//Stack类定义
{
private:
	T sz[num];				//存储空间，用数组表示
	int point;				//指针，表示存储位置（即元素个数）

public:
	Stack()				//构造函数
	{
		point=0;					//初始位置为0，栈底
	}

	bool isEmpty();			//判断栈是否为空
	bool isFull();			//判断栈是否已满	
	bool push(const T&);	//将一个元素压入栈
	bool pop(T&);			//从栈中弹出一个元素
	int &GetPos()
	{
		return point;
	}
};

template<class T,int num>		//参数列表不要求字字相同，但形式要相同
bool Stack<T,num>::isEmpty()
{
	return point==0;			//point为0，说明当前无元素
}

template<class T,int num>
bool Stack<T,num>::isFull()
{
	return point==num;			//point为num，说明数组已满
}

template<class T,int num>
bool Stack<T,num>::push(const T& obt)
{
	if (isFull())
		return false;			//如果栈已满，压入不成功，返回false
	else
	{
		sz[point]=obt;			//将传入的元素存储在point指向的当前位置
		point++;				//point加1，向栈顶移动
		return true;			//压入成功，返回true
	}
}

template<class T,int num>
bool Stack<T,num>::pop(T &obt)
{
	if (isEmpty())
		return false;			//如果栈已空，无法弹出，返回false
	else
	{
		point--;				//point减1，向栈底移动，指向存储的最上面一个元素
		obt = sz[point];			//将point指向的当前位置元素复制给传入参数				
		return true;			//弹出成功，返回true
	}
}

int main()
{
	Stack<int, 10> st;		//模版类, 模版参数为<class T, int num>
	cout << "开始时st是否为空？ " << st.isEmpty() << endl;
	
	st.push(5);			//压入元素5
	cout << "此时st是否为空？ " << st.isEmpty() << endl;
	
	for (int i = 1; i < 10; i++)
	{
		st.push(i);		//压入9个元素
	}
	cout << "此时st是否已满？" << st.isFull() << endl;
	
	int rec = 0;
	while (st.pop(rec))
		cout << rec << "  ";
	cout << endl;
	
	return 0;
}
```

## 3.1 模板的嵌套

- 模板的套嵌可以理解成在另外一个模板里面定义一个模板。以模板（类，或者函数）作为另一个模板（类，或者函数）的成员，也称成员模板。

- 成员模版不能声明为virtual

## 3.2 成员函数模板

- 可以将函数模板作为另一个类（必须是类模板）的成员，称为成员函数模板，其用法和普通成员函数类似，见示例代码。

- 在类模板中, 成员函数的模板参数(template parameter)可以和类的模板参数不同, 但在定义中,必须添加两个模板参数列表(template parameter list), 第一个为类的, 第二个为成员函数的

```cpp
    //嵌套模版函数的模版类
#include <iostream>
using namespace std;

//普通类模版
template <class T1, class T2>
class Convert
{
public:
	T2 f(T1 data)
	{
		return T2(data);
	}
};


//嵌套了模版函数的类模版
template<class T1>
class Test						//Test模版类定义
{
public:
    	template<class T2>
	T1 f(T2 b)				//模板成员函数定义
	{
	    return T1(b);			//将b由T2类型强制转换成T1类型
	}
};


//template<class T1>
//template<class T2>
//T1 Test<T1>::f(T2 b)			//模板成员函数的实现
//{
//        return T1(b);			//将b由T2类型强制转换成T1类型
//}

int main()
{
	//普通模版类的使用
	Convert<char, int> c1;
	cout << c1.f('A') << endl;

	Convert<float, int> c2;
	cout << c2.f(9.85f) << endl;

	Convert<int, short> c3;
	cout << hex << showbase << c3.f(0x7fffffff) << endl << dec;
	//通过上述3个例子，发现有些不太人性化, 必须指明第一个模版参数
	//其实这个参数就是函数f的参数，没必要指定。
	//这可以使用嵌套模版函数的模版类来解决。见Test类的实现。


	//嵌套模版类的使用
	Test<int> t;
	cout<<t.f(3.14f)<<endl;

	getchar();
	return 0;
}
```

## 3.3 对象成员模板

- 类模板的定义可以放在另一个类中，实例化后的模板类对象可以作为另一个类的成员，请看示例：

- 备注代码中，理解的难点在于“类模板不等于类定义，需要实例化或特化来生成类实例”。上述代码中，Inside类模板的访问权限为public，因此，可以调用下述语句：

​          `Outside<int>::Inside<double> obin(3.5);`

- 在Outside类内使用“Inside<T> t;”语句声明了Inside<T>类的对象，在Outside模板类对象创建时，首先采用隐式实例化先生成Inside<T>类的定义，而后根据此定义创建对象成员t

```cpp
/嵌套模版类的模版类
#include <iostream>
using namespace std;

template<class T>
class Outside			//外部Outside类定义
{
public:
	template <class R>
	class Inside		//嵌套类模板定义
	{
	private:
		R r;
	public:
		Inside(R x)	//模板类的成员函数可以在定义时实现
		{
			r=x;
		}
		//void disp();
		void disp() {cout << "Inside: " << r << endl;}
	};

	Outside(T x) : t(x)			//Outside类的构造函数
	{}
	
	//void disp();
	void disp()
	{
		cout<<"Outside:";
		t.disp();
	}

private:
	Inside<T> t;
};

//template<class T>
//template<class R>
//void Outside<T>::Inside<R>::disp()	//模板类的成员函数也可以在定义外实现
//{			//但必须是在所有类定义的外边,不能放在Outside内Inside外去实现.
//	cout<<"Inside: "<<Outside<T>::Inside<R>::r<<endl;
//}

//template<class T>
//void Outside<T>::disp()
//{
//	cout<<"Outside:";
//	t.disp();
//}

int main()
{
	Outside<int>::Inside<double> obin(3.5);	//声明Inside类对象obin
	obin.disp();

	Outside<int> obout(2);		//创建Outside类对象obout
	obout.disp();

	getchar();
	return 0;
}
```

## 3.4 模板做参数

- 模板包含类型参数（如class Type）和非类型参数（如int NUM，NUM是常量），实际上，模板的参数可以是另一个模板，也就是说，下述形式是合法的：`template<template <class T1> class T2, class T3,int Num>`

- 上述简单示例将原来简单的`“class T2”`或`“Typename T2”`扩充为`“template <class T1> class T2”`，来看一段示例代码。

- 上述代码中定义了函数模板`disp()`，该模板的类型参数表中又包含了一个类模板`TypeClass`，在函数模板`disp`内可以对类`TypeClass`进行实例化处理。

```cpp
//A模板做为B模板的参数

//文件“Stack.h”的内容如下
template <class T,int num>		//类型参数表
class Stack						//Stack类定义
{
	private:
		T sz[num];				//存储空间，用数组表示
	public:
		int ReturnNum();		//判断栈是否为空
};

template<class T1,int num1>		//参数列表不要求字字相同，但形式要相同
int Stack<T1, num1>::ReturnNum()
{
	return num1;				//返回数组大小
}


#include <iostream>
//#include "Stack.h"
using namespace std;

template<template<class Type,int NUM> class TypeClass, class T1, int N>
void disp()				//函数模板，其类型参数表中包含一个类模板
{
	TypeClass<T1,N> ob;		//类模板的隐式实例化,创建对象ob
	cout<<ob.ReturnNum()<<endl;	//调用ob的public成员函数
}

int main()
{
	disp<Stack,int,8>();		//函数模板的隐式实例化，并调用
	system("pause");
	return 0;
}
```

