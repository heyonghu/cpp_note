# 1. 面向对象思想

## 1.1. 面向对象程序设计

- 认为现实世界是由对象组成的

- 用程序来模拟现实世界中对象与对象之间的交互

- 对象由相关的数据和操作组成，对象具有相对独立性，对外提供一定的服务

​    程序 ＝ 对象 + 对象 + … + 对象

- 在C语言中，程序是由一个个函数组成的，是结构化的面向过程的编程方法。

- C++语言进行面向对象的程序设计，编写的程序是由对象组成的。

- 面向对象的四大特性：抽象、封装、继承、多态

## 1.2. 面向对象基本概念

- 类是怎么来的？

  - 从哲学角度说，先有对象，然后才有类，类和对象是“一般和特殊”这一哲学原理在程序世界中的具体体现。
  - 类其实是抽象认知能力作用于程序世界的基本元素——对象后所衍生出来的抽象概念，是抽象思维在程序世界中物化后的产物。
  
- 类的提取往往是从两个方面来考虑的，

  - 一是特征（C++常称为“属性”）、

  - 另一个是功能（C++中常称为“行为”），具备类中定义的“属性”和“行为”的对象都是该类的对象，因此，可以说，电动车也是“车”类的对象。

## 1.3. 类的概念

- C++用类来描述对象，类是对现实世界中相似事物的抽象，同是“双轮车”的摩托车和自行车，有共同点，也有许多不同点。“车”类是对摩托车、自行车、汽车等相同点的提取与抽象，如所示。
- 类的定义分为两个部分：数据（相当于属性）和对数据的操作（相当于行为）。
- 从程序设计的观点来说，类就是数据类型，是用户定义的数据类型，对象可以看成某个类的实例（某个类的变量）

## 1.4. 类和对象的关系

类是对象的封装，对象是类的实例。

 类需要从属性和行为两个方面进行描述 。类的使用主要有以下几个步骤：

- 定义类：C++中，分别用数据成员和成员函数来表现对象的属性和行为。类的定义强调“信息隐藏”，将实现细节和不允许外部随意访问的部分屏蔽起来，保证了对象的数据安全。

- 实现类：即进一步定义类的成员函数，使各个成员函数相互配合以实现接口对外提供的功能，类的定义和实现是由类设计者完成的。

- 使用类：通过该类声明一个属于该类的变量（即对象），并调用其接口（即public型的数据成员或函数成员），这是使用者的工作

# 2. C++类的定义

先来看一下类是如何定义的，对一些通用的问题，前人已经定义好了很多的类，比如微软的MFC类库，程序员不必关心其内部细节，只要抱着“拿来主义”的态度就好，但对某些特殊问题来说，必须由自己提炼模型，进行类的定义。

在C++中，类内的成员变量和成员函数分开存储
只有非静态成员变量才属于类的对象上

## 2.1 类定义的基本形式

C++中使用关键字class定义一个类，其基本形式如下：

```cpp
class 类名
{
private:
	   私有成员变量和函数
protected:
	   保护成员变量和函数
public:
	   公共成员变量和函数
};	//不要漏写了这个分号;
```

`Computer.cpp`

```cpp
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


//代码风格
//
//code review   代码走查
//
//代码写出来之后，其实都是给人看的  --> 可读性 -> 写代码的实力
//

class Computer
{// 默认访问权限是private
	void setBrand(const char * brand)
	{
		strcpy(_brand, brand);
	}

	void setPrice(float price)
	{
		_price = price;
	}

	void print()
	{
		cout << "brand: " << _brand << endl;
		cout << "price: " << _price << endl;
	}
	
	char _brand[20];// m_brand数据成员
	float _price;// price_
};
 
int main(void)
{
	int a;

	Computer com;
	com.setBrand("战神");// .   成员访问运算符
	com.setPrice(8888);
	com.print();

	//com._price = 10000;//error 对于私有成员，不能在类之外访问, 体现的是类的封装特性

	return 0;
}
```

`Computer.h`

```cpp
#ifndef __COMPUTER_H__
#define __COMPUTER_H__

class Computer
{// 类内部
public:// 类对外提供的接口（服务、功能）
	//成员函数
	void setBrand(const char *);
	void setPrice(float);
	void print();
	
private:
	char _brand[20];// m_brand数据成员
	float _price;// price_
};

#endif
```

```cpp
//注意：
//C++规定，类成员的访问权限默认是private，不加申明的成员默认是private，因此上述代码中的第一个private可以省略。
//数据成员的类型前面不可使用auto、extern和register等，也不能在定义时对变量进行初始化，如果将float price写成float price = 0，编译器会报错。
//类定义中提供的成员函数是函数的原型申明。
//关键字private和public出现的顺序和次数可以是任意的，如上述代码也可以写成如下形式：
class computer
{
	char brand[20];	//默认为private类型
public:
	void print();
private:			//这里的private不能省略，因为不是在类定义的开始位置
	float price;
public:
	void SetBrand(char* sz);
	void SetPrice(float pr);
};

//private数据成员只能由本类的函数访问，protected数据成员只能在派生类中访问，而public数据成员在派生类和类外均可访问。
```



## 2.2 class和struct

- class的定义看上去很像struct定义的扩展，事实上，类定义时的关键字class完全可以替换成struct，也就是说，结构体变量也可以有成员函数。class和struct的唯一区别在于：**struct的默认访问方式是public，而class为private**。
- 提示：通常使用class来定义类，而把struct用于只表示数据对象、没有成员函数的类。

```cpp
class Computer
{// 默认访问权限是private
public:
	void setBrand(const char * brand)
	{
		strcpy(_brand, brand);
	}

	void setPrice(float price)
	{
		_price = price;
	}

	void print()
	{
		cout << "brand: " << _brand << endl;
		cout << "price: " << _price << endl;
	}
	
	char _brand[20];// m_brand数据成员
	float _price;// price_
};
 
int main(void)
{
	int a;

	Computer com;
	com.setBrand("战神");// .   成员访问运算符
	com.setPrice(8888);
	com.print();

	//com._price = 10000;//error 对于私有成员，不能在类之外访问, 体现的是类的封装特性

	return 0;
}
```



## 2.3 C++类的实现

- 类的实现就是定义其成员函数的过程，类的实现有两种方式：

  - 在类定义时同时完成成员函数的定义。

  - 在类定义的外部定义其成员函数。

    - 在类定义的外部定义成员函数时，应使用作用域操作符（::）来标识函数所属的类，即有如下形式：

      ```cpp
      返回类型 类名::成员函数名(参数列表)
      {
       函数体
      }
      ```

    - 其中，返回类型、成员函数名和参数列表必须与类定义时的函数原型一致。

  Computer2.cpp
  
  ```cpp
  #include "Computer.h" //如果分成头文件与实现文件，在实现文件的第一行，一定要放自己的头文件
  
  #include <string.h>
  #include <iostream>
  using std::cout;
  using std::endl;
  
   
  //在类之外实现成员函数
  void Computer::setBrand(const char * brand)
  {
  	strcpy(_brand, brand);
  }
  
  void Computer::setPrice(float price)
  {
  	_price = price;
  }
  
  void Computer::print()
  {
  	cout << "brand: " << _brand << endl;
  	cout << "price: " << _price << endl;
  }
  ```
  
  `Computer.h`
  
  ```cpp
  #ifndef __COMPUTER_H__
  #define __COMPUTER_H__
  
  class Computer
  {// 类内部
  public:// 类对外提供的接口（服务、功能）
  	//成员函数
  	void setBrand(const char *);
  	void setPrice(float);
  	void print();
  	
  private:
  	char _brand[20];// m_brand数据成员
  	float _price;// price_
  };
  
  #endif
  
  ```
  

## 2.4 C++类的使用

  定义了一个类之后，便可以如同用`int`、`double`等类型符声明简单变量一样，创建该类的对象，称为类的实例化。由此看来，类的定义实际上是定义了一种类型，类不接收或存储具体的值，只作为生成具体对象的“蓝图”，只有将类实例化，创建对象（声明类的变量）后，系统才为对象分配存储空间。

## 2.5 对象的作用域、可见域和生存期

- 对象的作用域、可见域和生存期与普通变量，如`int`型变量的作用域、可见域和生存期并无不同，对象同样有局部、全局和类内（稍后就将对对象成员进行介绍）之分，对于在代码块中声明的局部对象，在代码块执行结束退出时，对象会被自动撤销，对应的内存会自动释放（当然，如果对象的成员函数中使用了`new`或`malloc`申请了动态内存，却没有使用delete或free命令释放，对象撤销时，这部分动态内存不会自动释放，造成内存泄露）。

- 跟踪调试，查看同一个类的不同对象的成员变量和成员函数在内存中的地址分配情况。结论：成员变量占据不同的内存区域(堆、栈)；成员函数共用同一内存区域(代码段)。

## 2.6 对象的创建和撤销

在之前的`Computer`类中，通过自定义的公共成员函数`SetBrand`和`SetPrice`实现对数据成员的初始化，实际上，`C++`为类提供了两种特殊的成员函数来完成同样的工作：

- 一是构造函数，在对象创建时自动调用，用以完成对象成员变量等的初始化及其他操作（如为指针成员动态申请内存空间等）；如果程序员没有显式的定义它，系统会提供一个默认的构造函数。

- 另一个是析构函数，在对象撤销时自动调用，用以执行一些清理任务，如释放成员函数中动态申请的内存等。如果程序员没有显式的定义它，系统也会提供一个默认的析构函数。

# 3. 构造函数

- 当对象被创建时，构造函数自动被调用。构造函数有一些独特的地方：函数的名字与类名相同，没有返回类型和返回值，即使是void也不能有。其主要工作有：

  - 给对象一个标识符。

  - 为对象数据成员开辟内存空间。

  - 完成对象数据成员的初始化（函数体内的工作，由程序员完成）。
- 上述3点也说明了构造函数的执行顺序，在执行函数体之前，构造函数已经为对象的数据成员开辟了内存空间，这时，在函数体内对数据成员的初始化便是顺理成章了。
- 备注代码给出了point类的显式构造函数

```cpp
class point
{
private:
	int xPos;
	int yPos;
public:
	point();
};

point::point()
{
	xPos = 0;
	yPos = 0;
}

```

- 编译器自动生成的缺省(默认)构造函数是无参的，实际上，构造函数可以接收参数，在对象创建时提供更大的自由度，如备注代码8-5
- 一旦用户定义了构造函数，系统便不再提供默认构造函数。
- 跟踪执行，理解构造函数的执行顺序。

```cpp
#include <iostream>
using namespace std;
class point //point类定义，在定义同时实现其成员函数
{
private: //私有成员，分别代表x轴和y轴坐标
	int xPos;
	int yPos;
public:
	point(int x, int y) //有参构造函数
	{
		cout << "对象创建时构造函数被自动调用" << endl;
		xPos = x;
		yPos = y;
	}
	void print() //输出信息
	{
		cout << "xPos: " << xPos << ",yPos: " << yPos << endl;
	}
};

#include "point.h"
int main()
{
//	point pt0;			//错误的调用，因为我们已经显示的定义了一个带参数的构造函数
//	pt0.print();		//输出pt0的信息
	point pt1(3, 4);	//调用有参构造函数声明point类变量（类对象）pt1
	pt1.print();		//输出pt1的信息
	return 0;
}


```

- 一旦程序员为一个类定义了构造函数，编译器便不会为类自动生成缺省构造函数，因此，如果还想使用无参的构造函数，如“point pt1;”的形式必须在类定义中显式定义一个无参构造函数。这样，构造函数就会出现两个，会不会有问题呢？不会，构造函数支持重载，在创建对象时，根据传递的具体参数决定采用哪个构造函数

**构造函数允许按参数缺省方式调用**

```cpp
point(int x＝0,int y＝0)
{
	cout<<"对象创建时构造函数被自动调用"<<endl;
	xPos=x;
	yPos=y;
}


point pt;	//x和y都采用默认值0
point pt(3);	//x为3，y采用默认值0
point pt(3,4);//x为3，y为4，两个参数都不采用默认值
```

## 3.1 初始化表达式

- 除了在构造函数体内初始化数据成员外，还可以通过成员初始化表达式来完成。
- 成员初始化表可用于初始化类的任意数据成员（后面要介绍的static数据成员除外），该表达式由逗号分隔的数据成员表组成，初值放在一对圆括号中。
- 只要将成员初始化表达式放在构造函数的头和体之间，并用冒号将其与构造函数的头分隔开，便可实现数据成员表中元素的初始化
- 每个成员在初始化表中只能出现一次
- 初始化的顺序不是由成员变量在初始化表中的顺序决定的，而是由成员变量在类中被申明时的顺序决定的。理解这一点有助于避免意想不到的错误。

```cpp
#include <iostream>
using namespace std;
class point
{
private:
	int yPos;	//先定义
	int xPos;	//后定义
public:
	point(int x):xPos(x), yPos(xPos) //初始化表取决于成员声明的顺序
	{
	}
	void print()
	{
		cout << "xPos: " << xPos << ", yPos: " << yPos << endl;
	}
};

#include "point.h"
int main()
{
	point pt1(3);		//调用有参构造函数声明变量pt1
	pt1.print();	
	return 0;
}

```

## 3.2 移动构造函数

## 3.3 移动构造函数

## 3.4 移动赋值运算符

```cpp
#include <string.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


class String
{
public:
	String()
	: _pstr(new char[1]())
	{	cout << "String()" << endl;}

	String(const char * pstr)
	: _pstr(new char[strlen(pstr) + 1]())
	{
		strcpy(_pstr, pstr);
		cout << "String(const char * pstr)" << endl;
	}

	//具有值语义（复制控制）的函数
	//复制构造函数
	String(const String & rhs)
	: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		strcpy(_pstr, rhs._pstr);
		cout << "String(const String &)" << endl;
	}

	//赋值运算符函数
	String & operator=(const String & rhs)
	{
		cout << "String & operator=(const String &)" << endl;
		if(this != & rhs) {// 自复制
			delete [] _pstr;
			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr, rhs._pstr);
		}
		return *this;
	}

#if 1
	// 具有移动语义的函数 的执行要优先于 具有值语义的函数
	// 移动构造函数
	String(String && rhs)
	: _pstr(rhs._pstr)
	{
		rhs._pstr = nullptr;
		cout << "String(String &&)" << endl;
	}

	//移动赋值运算符函数
	String & operator=(String && rhs)// 这里的右值引用本身变成了左值
	{
		if(this != &rhs)
		{
			cout << "String & operator=(String &&)" << endl;
			delete [] _pstr;
			_pstr = rhs._pstr;
			rhs._pstr = nullptr;//移动意味着修改
		}
		return *this;
	}
#endif

	~String()
	{
		delete [] _pstr;
		cout << "~String()" << endl;
	}

	friend std::ostream & operator<<(std::ostream & os, const String & rhs);
	
private:
	char * _pstr;
};

std::ostream & operator<<(std::ostream & os, const String & rhs)
{
	os << rhs._pstr;
	return os;
}

String && func()
{
	return String("hello");
}

//右值引用本身是不是右值？
//答： 右值引用本身是左值还是右值，取决于它有没有名字；
//	   有名字的就是左值，没有名字就是右值
	
 
int test0(void)
{
#if 0
	vector<String> vec;
	vec.push_back("Hello,world");
#endif

	String s1 = "hello,world";
	cout << "s1 = " << s1 << endl;
	cout << endl;
	String s2("hello,world");
	cout << "s2 = " << s2 << endl;
	cout << endl;

	s2 = String("wangdao");
	cout << "s2 = " << s2 << endl;
	cout << endl;

//	s2 = std::move(s2);// 一般不会这样使用

	String s3 = std::move(s2);//std::move 显式的将一个左值转换成右值
							  //意味着该语句之后，就不会再使用s2
	cout << "s3 = " << s3 << endl;
	//cout << "s2 = " << s2 << endl;//无法正常执行

	cout << "对s2 重新进行赋值之后，才可以正常使用:" << endl;
	s2 = "shenzen";
	cout << "s2 = " << s2 << endl;


	cout << "...." << endl;
	return 0;
}

void test1(void)
{
	&func();// 右值引用是右值, 没有名字
}

int main(void)
{
	test1();
	return 0;
}
```

## 3.5 编译器优化技术—RVO

- RVO(Return Value Optimization)-
  - 当函数需要返回一个对象的时候，如果自己创建一个临时对象用户返回，那么这个临时对象会消耗一个构造函数(Constructor)的调用、一个复制构造函数的调用(Copy Constructor)以及一个析构函数(Destructor)的调用的代价

- 而如果稍微做一点优化，就可以将成本降低到一个构造函数的代价

# 4. 析构函数

- 构造函数在创建对象时被系统自动调用，而析构函数在对象被撤销时被自动调用，相比构造函数，析构函数要简单的多。析构函数有如下特点：

  - 与类同名，之前冠以波浪号，以区别于构造函数。

  - 析构函数没有返回类型，也不能指定参数，因此，析构函数只能有一个，不能被重载。

  - 对象超出其作用域被销毁时，析构函数会被自动调用。

- 如果用户没有显式地定义析构函数，编译器将为类生成“缺省析构函数”，缺省析构函数是个空的函数体，只清除类的数据成员所占据的空间，但对类的成员变量通过new和malloc动态申请的内存无能为力，因此，对于动态申请的内存，应在类的析构函数中通过delete或free进行释放，这样能有效避免对象撤销造成的内存泄漏。

析构函数在什么时候被调用

- 对于全局定义的对象，每当程序开始运行，在主函数`main`(或`WinMain`)接受程序控制权之前，就调用全局对象的构造函数。整个程序结束时调用析构函数。

- 对于局部定义的对象，每当程序流程到达该对象的定义处就调用构造函数，在程序离开局部对象的作用域时调用对象的析构函数。{}

- 对于关键字static定义的静态局部变量，当程序流程第一次到达该对象定义处调用构造函数，在整个程序结束时调用析构函数。

- 对于用new运算符创建的对象，每当创建该对象时调用构造函数，当用delete删除该对象时，调用析构函数。

```cpp
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class Computer
{
public:
	Computer(const char * brand, float price)
	: _brand(new char[strlen(brand) + 1]())
	, _price(price)
	{
		cout << "Computer(const char *, float)" << endl;
		strcpy(_brand, brand);
	}

	void print() 
	{
		cout << "brand: " << _brand << endl;
		cout << "price: " << _price << endl;
	}

	~Computer() 
	{
		cout << "~Computer()" << endl;
		delete [] _brand;
	}
private:
	char * _brand;
	float _price;
};


Computer gComputer("Thinkpad", 7777);
 
int main(void)
{
	cout << "sizeof(float) = " << sizeof(float) << endl; // 4
	cout << "sizeof(Computer) = " << sizeof(Computer) << endl; // 16
	//Computer c1("xiaomi", 6666);//栈对象，当其生命周期结束时，也会自动调用析构函数
	//c1.print();
	//c1.~Computer();//可以显式调用析构函数，但不推荐这样做
	
	//int * p1 = new int(1);
	//delete p1;
	gComputer.print();
	cout << endl;
	
	Computer * pc = new Computer("Mac", 10000);
	pc->print();

	delete pc;//会调用Computer的析构函数

	return 0;
}
```

# 5. 复制构造函数

- C++中经常使用一个常量或变量初始化另一个变量，例如：

double x＝5.0； double y＝x;

- 使用类创建对象时，构造函数被自动调用以完成对象的初始化，那么能否象简单变量的初始化一样，直接用一个对象来初始化另一个对象呢？答案是肯定的，以point类为例：

```cpp
point pt1(2,3); 
point pt2=pt1;
```

后一个语句也可写成：

```cpp
point pt2( pt1);
```

- 上述语句用pt1初始化pt2，相当于将pt1中每个数据成员的值复制到pt2中，这是表面现象。实际上，系统调用了一个复制构造函数。如果类定义中没有显式定义该复制构造函数时，编译器会隐式定义一个缺省的复制构造函数，它是一个inline、public的成员函数，其原型形式为：

```cpp
类名：：类名（const 类名 &）

如：   point:: point (const point &);
```

## 5.1 复制构造函数调用机制

- 复制构造函数的调用示例：

```cpp
point pt1(3,4);  //构造函数

point pt2(pt1); //复制构造函数

point pt3 = pt1;//复制构造函数
```

- **拷贝构造函数在以下三种情况会自动调用：**
- **当把一个已经存在的对象赋值给另一个新的对象时。**
- **当实参和形参都是对象，进行形参和实参的结合时。**
- **当函数的返回值是对象，函数调用完成返回时。**

```cpp
computer(const computer &cp) //自定义复制构造函数
{
	//重新为brand开辟和cp.brand同等大小的动态内存
	brand = new char[strlen(cp.brand) + 1];
	strcpy(brand, cp.brand); //字符串复制
	price = cp.price;
}
```

```cpp
#include <iostream>
using namespace std;
class point
{
private:
	int xPos;
	int yPos;
public:
	point(int x = 0, int y = 0)
	{
		cout << "调用构造函数" << endl;
		xPos = x;
		yPos = y;
	}
	point(const point & pt)//复制构造函数的定义及实现
	{
		cout << "调用复制构造函数" << endl;
		xPos = pt.xPos;
		yPos = pt.yPos;
	}
	void print()
	{
		cout << "xPos: " << xPos << ",yPos: " << yPos << endl;
	}
};
#include "point.h"

int main()
{
	point pt1(3, 4);
	pt1.print();

	point pt2 = pt1; //等价于point pt2(pt1)，调用复制构造函数
	pt2.print();

	point pt3;
	pt3.print();

	point pt4(pt3); //等价于point pt4＝pt3，调用复制构造函数
	pt4.print();

//	pt2 = pt1;		//调用默认的赋值运算符重载函数
//	pt2.print();
	return 0;
}


#include <iostream>
using namespace std;

class CPoint
{
private:
	int x;
	int y;

public:
	//缺省构造函数,如果定义类时未指定任何构造函数，
	//系统将自动生成不带参数的缺省构造函数
	CPoint()
	{
		cout << "默认构造函数 " << this << " " << endl;
		x = 0;
		y = 0;
	}

	//带一个参数的可用于类型转换的构造函数
	CPoint(int ix)
	{
		cout << "1参数构造函数 " << this << " " << endl;
		x = ix;
		y = 0;
	}

	//带参数的构造函数
	CPoint(int ix, int iy)
	{
		cout << "2参数构造函数 " << this << " " << endl;
		x = ix;
		y = iy;
	}

	//拷贝构造函数,如果此函数不定义，系统将生成缺省拷贝构造函数功能,
	//缺省拷贝构造函数的行为是：用传入的对象参数的成员初始化正要建立的对象的相应成员
	CPoint(const CPoint &cp)
	{
		cout << "拷贝构造函数 " << this << " " << endl;
		x = cp.x;
		y = cp.y;
	}

	CPoint &operator=(const CPoint &cp)
	{
		cout << "赋值重载函数 " << this << " " << endl;
		if (this != &cp)
		{
			x = cp.x;
			y = cp.y;
		}
		return (*this);
	}

	//析构函数，一个类中只能有一个析构函数,如果用户没有定义析构函数，
	//系统会自动未类生成一个缺省的析构函数
	~CPoint()
	{
		cout << "析构函数 " << this << " " << endl;
	}
};

void fun1(CPoint pt)
{
}

CPoint fun2()
{
	CPoint a;
	return a;
}

CPoint fun(CPoint a)
{
	return a;
}

int main(int argc, char* argv[])
{
	//第1类
//	CPoint pt1 = CPoint();	
	//当有析构函数的时候，CPoint()不会生成调用构造函数生成临时的匿名对象。
	//当没有析构函数的时候，CPoint()会生成一个临时的匿名对象，等价于CPoint pt1;这句话只会调用无参构造函数，不会调用拷贝构造函数

//	CPoint pt2 = CPoint(1);	
	//当有析构函数的时候，CPoint(1)不会生成调用构造函数生成临时的匿名对象。
	//当没有析构函数的时候，CPoint()会生成一个临时的匿名对象，等价于CPoint pt(1);这句话只会调用一个参数的构造函数，不会调用拷贝构造函数

//	CPoint pt3 = 1;			
	//普通数据类型转换为类类型，利用相应的构造函数就可以实现。等价于CPoint pt(1);
	
	//第2类
	/*拷贝构造函数与赋值运算符重载函数的区别:
		1. 拷贝构造函数是用已经存在的对象的各成员的当前值来创建一个相同的新对象。
		   在下述3种情况中，系统会自动调用所属类的拷贝构造函数。
			 1.1  当说明新的类对象的同时，要给它赋值另一个已经存在对象的各成员当前值。
			 1.2  当对象作为函数的赋值参数而对函数进行调用要进行实参和形参的结合时。
			 1.3  当函数的返回值是类的对象，在函数调用结束后返回主调函数处的时候。
		2. 赋值运算符重载函数要把一个已经存在对象的各成员当前值赋值给另一个已经存在的同类对象
	*/
	CPoint pt4;			//调用无参构造函数
//	CPoint pt5 = pt4;	//调用拷贝构造函数  属于1.1
//	fun1(pt4);			//调用拷贝构造函数  属于1.2
//	fun2();				//调用拷贝构造函数  属于1.3

//	CPoint pt6 = fun2();//调用无参构造函数，拷贝构造函数，此处如果没有写析构函数，则还会调用一次拷贝构造函数
	//因为函数返回会生成一个临时对象，然后再将这个临时对象赋值给pt6，所以多调用一次拷贝构造函数；如果有析构函数
	//则不会生成中间的临时变量，所以少一次拷贝构造函数的调用

	//还可以通过下面函数验证
//	CPoint pt7 = fun(pt4);
	//如果没有析构函数，会调用3次拷贝构造函数

	return 0;
}

```

- 缺省的复制构造函数并非万金油，在一些情况下，必须由程序员显式定义缺省复制构造函数，先来看一段错误代码示例，见备注代码。

  - 其中语句computer comp2(comp1)等价于：

  - comp2.brand = comp1.brand;

  - comp2.price = comp1.price;

  - 后一句没有问题，但comp2.brand = comp1.brand却有问题：经过这样赋值后，两个对象的brand指针都指向了同一块内存，当两个对象释放时，其析构函数都要delete[]同一内存块，便造成了2次delete[]，从而引发了错误。


```cpp
#include <iostream>
using namespace std;

class computer
{
private:
	char * brand;
	float price;

public:
	computer(const char * sz, float p)
	{
		brand = new char[strlen(sz) +1]; //构造函数中为brand指针动态分配内存
		strcpy(brand, sz);
		price = p;
	}
	
//	computer(const computer &cp)	//默认的复制构造函数的实现如下:
//	{
//		brand = cp.brand;	//对指针变量不能这样直接赋值，这是引起错误的根源
//		price = cp.price;
//	}

	~computer()
	{
		delete[] brand; //析构函数中释放申请到的动态内存
		cout << "清理现场" << endl;
	}
	
	void print()
	{
		cout << "品牌：" << brand << endl;
		cout << "价格：" << price << endl;
	}
};

#include "computer.h"
int main()
{
	computer comp1("Dell", 7000); //声明computer类对象comp，并初始化
	comp1.print();
	computer comp2(comp1); //调用缺省的复制构造函数
	comp2.print();
	return 0;
}

```

- (解决方案――显式定义复制构造函数)如果类中含有指针型的数据成员、需要使用动态内存，程序员最好显式定义自己的复制构造函数，避免各种可能出现的内存错误，见代码。

```cpp
#include <iostream>
#include <cstring>
using namespace std;
class computer
{
private:
	char * brand;
	float price;
public:
	computer(const char * sz, float p)
	{
		brand = new char[strlen(sz) + 1];
		strcpy(brand, sz);
		price = p;
	}
	computer(const computer & cp) //自定义复制构造函数
	{
		brand = new char[strlen(cp.brand) + 1]; //重新为brand开辟于cp.brand同等大小的动态内存
		strcpy(brand, cp.brand); //字符串复制
		price = cp.price;
	}
	~computer()
	{
		delete[] brand;
		cout << "清理现场" << endl;
	}
	void print()
	{
		cout << "品牌：" << brand << endl;
		cout << "价格：" << price << endl;
	}
};

#include "computer.h"
int main()
{
	computer comp1("Dell", 7000);//调用有参构造函数声明computer类对象comp1，并初始化
	comp1.print();
	computer comp2(comp1);//调用复制构造函数声明computer类对象comp2，并用comp1为其初始化
	comp2.print();
	return 0;
}


```



## 5.2 关于构造函数和复制构造函数

- 复制构造函数可以看成是一种特殊的构造函数，这里姑且区分为“复制构造函数”和“普通构造函数”，因此，它也支持初始化表达式。

- 创建对象时，只有一个构造函数会被系统自动调用，具体调用哪个取决于创建对象时的参数和调用方式。C++对编译器何时提供缺省构造函数和缺省复制构造函数有着独特的规定，如表所示。

![image-20220704121520159](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220704121520159.png)

## 5.3 构造函数调用示例

```cpp
CTest t0();	//这是函数的声明，不是实例化类
CTest t1;	//缺省构造函数
CTest t2(1);	//一个参数的构造函数
CTest t3(1, 2);	//两个参数的构造函数
CTest t4 = 1;	//等价于CTest t4(1);	//explicit
CTest t5 = t1;	//CTest(t1);
CTest t6 = CTest();//CTest(1); CTest(1,2);
t6 = CTest(1);
t6 = 1;		//首先调用单个参数的构造函数，生成临时
			//对象CTest(1), 然后调用赋值运算符函数
t6 = t1;		//调用赋值运算符函数
见备注代码。请注意输出的地址值，观察构造函数和析构函数的配对情况。
```

```cpp
//为了防止CPoint pt = 2;和CPoint pt2 = pt1;这种隐性转换，可以在相应的构造函数前增加explicit标识符
#include <iostream>
using namespace std;

class CPoint
{
protected:
	int x;
	int y;

public:
	//缺省构造函数,如果定义类时未指定任何构造函数，
	//系统将自动生成不带参数的缺省构造函数
	CPoint()
	{
		cout << "默认构造函数 " << this << " ";
		x = 0;
		y = 0;
	}

	//带一个参数的可用于类型转换的构造函数
//	explicit	//加上 explicit 可防止 CPoint pt1 = 1; 这种隐性转换
	CPoint(int ix)
	{
		cout << "1参数构造函数 " << this << " ";
		x = ix;
		y = 0;
	}

	//带参数的构造函数
	CPoint(int ix, int iy)
	{
		cout << "2参数构造函数 " << this << " ";
		x = ix;
		y = iy;
	}

	//拷贝构造函数,如果此函数不定义，系统将生成缺省拷贝构造函数功能,
	//缺省拷贝构造函数的行为是：用传入的对象参数的成员初始化正要建立的对象的相应成员
//	explicit	//加上 explicit 可防止 CPoint pt2 = pt1; 这种隐性转换
	CPoint(const CPoint &cp)
	{
		cout << "拷贝构造函数 " << this << " ";
		x = cp.x;
		y = cp.y;
	}

	CPoint &operator=(const CPoint &cp)
	{
		cout << "赋值重载函数 " << this << " ";
		if (this != &cp)
		{
			x = cp.x;
			y = cp.y;
		}
		return (*this);
	}

	//析构函数，一个类中只能有一个析构函数,如果用户没有定义析构函数，
	//系统会自动未类生成一个缺省的析构函数
	~CPoint()
	{
		cout << "析构函数 " << this << " ";
	}
};

int main(int argc, char* argv[])
{
	CPoint p0();		//这是函数的声明，不是实例化类

	cout << endl << "CPoint pt1;\t\t";
	CPoint pt1;			//缺省构造函数
	
	cout << endl << "CPoint pt2(1);\t\t";
	CPoint pt2(1);		//一个参数的构造函数

	cout << endl << "CPoint pt3(1, 2);\t";
	CPoint pt3(1, 2);	//两个参数的构造函数

	cout << endl << "CPoint pt4 = 1;\t\t";
	CPoint pt4 = 1;		//等价于CPoint t4(1);	//explicit

	cout << endl << "CPoint pt5 = t1;\t";
	CPoint pt5 = pt1;	//CPoint(t1);

	cout << endl << "CPoint pt6 = CPoint();\t";
	CPoint pt6 = CPoint();	//CPoint(1); CPoint(1,2);

	cout << endl << "pt6 = CPoint(1);\t";
	pt6 = CPoint(1);

	cout << endl << "pt6 = 1;\t\t";
	pt6 = 1;			//首先调用单个参数的构造函数，生成临时对象CPoint(1), 然后调用赋值运算符函数
	
	cout << endl << "pt6 = t1;\t\t";
	pt6 = pt1;			//调用赋值运算符函数

	cout << endl << endl;
	return 0;
}

```



# 6.重载赋值运算符 =

- 成员函数形式的运算符声明和实现与成员函数类似，首先应当在类定义中声明该运算符，声明的具体形式为：

```cpp
返回类型 operator 运算符（参数列表）;
```

- 既可以在类定义的同时定义运算符函数使其称为inline型，也可以在类定义之外定义运算符函数，但要使用作用域限定符“::”，类外定义的基本格式为：

```cpp
返回类型 类名::operator 运算符（参数列表）
{

…

}
```

```cpp
//9-7 成员函数形式 的 运算符重载
#include <iostream>
using namespace std;

class complex					//定义复数类 complex
{
private:
	double real, imag;			//private 成员，分别代表实部和虚部

public:
	complex(double r = 0.0, double i = 0.0)	//构造函数，带缺省参数值
	{
		real = r;
		imag = i;
	}

	complex operator+= (const complex &);	//成员函数形式重载加+=

	complex operator+(const complex &);	//成员函数形式重载加+
	complex operator-(const complex &);	//成员函数形式重载减－
	complex operator-();					//成员函数形式重载一元－（取反）
	complex operator*(const complex &);	//成员函数形式重载乘*
	complex operator/(const complex &);	//成员函数形式重载除*

	complex& operator++();					//成员函数形式重载前置++
	complex operator++(int);				//成员函数形式重载后置++

	void disp()								//成员函数，输出复数
	{
		cout << real << " + " << "i*" << imag << endl;
	}
};

complex complex::operator+=(const complex& CC)		//加+=的实现
{
	real += CC.real;
	imag += CC.imag;
	return (*this);
}

complex complex::operator+(const complex& CC)		//加+的实现
{
	return complex(real + CC.real, imag + CC.imag);
}

complex complex::operator-(const complex& CC)		//减-的实现
{
	return complex(real - CC.real, imag - CC.imag);
}

complex complex::operator*(const complex& CC)		//乘*的实现
{
	return complex(real * CC.real - imag * CC.imag, real * CC.imag + imag * CC.real);
}

complex complex::operator/(const complex& CC)		//除/的实现
{
	return complex((real * CC.real + imag + CC.imag) / (CC.real * CC.real + CC.imag * CC.imag),
		(imag * CC.real - real * CC.imag) / (CC.real * CC.real + CC.imag * CC.imag));
}

complex complex::operator-()						//单目-，即取反的实现
{
	return complex(-real, -imag);
}

complex& complex::operator++()						//前置++的实现
{
	cout << "前置++" << endl;
	++real;
	++imag;
	return (*this);
}

complex complex::operator++(int)	//后置++的实现，体会和前置++的区别
{
	cout << "后置++" << endl;
	complex cTemp = (*this);	//最终的返回值的是原来的值，因此需要先保存原来的值
	++(*this);					//返回后原来的值需要加1
	return cTemp;
}

int main()
{
	complex cx1(1.0, 2.0), cx2(3.0, 4.0), cxRes;

	cxRes += cx2;		//相当于cxRes.operator+=(cx2)
	cxRes.disp();
	
	cxRes = cx1 + cx2;	//相当于cx1.operator+(cx2)
	cxRes.disp();
	
	cxRes = cx1 - cx2;	//相当于cx1.operator-(cx2)
	cxRes.disp();
	
	cxRes = cx1 * cx2;	//相当于cx1.operator*(cx2)
	cxRes.disp();
	
	cxRes = cx1 / cx2;	//相当于cx1.operator/(cx2)
	cxRes.disp();
	
	cxRes = -cx1;		//相当于cx1.operator-()
	cxRes.disp();
	
	cout << endl;
	
	complex cx3(1.0, 1.0), cx4(5.0, 5.0);
	
	cxRes = ++cx3;		//相当于cx3.operator++()
	cxRes.disp();
	cx3.disp();

	cout << endl;
	
	cxRes = cx4++;		//相当于cx4.operator++(0)
	cxRes.disp();
	cx4.disp();

	cout << endl;
	
	//注意下述语句在友元函数形式和成员函数形式中的对比。
	cxRes = cx1 + 5;	//相当于cx1.operator+(5) 或 cx1.operator+(complex(5))
	cxRes.disp();

//	cxRes = 5 + cx1;	//错误. 相当于5.operator+(cx1);
//	cxRes.disp();

	return 0;
}

```

- 赋值运算是一种很常见的运算，如果不重载赋值运算符，编译器会自动为每个类生成一个缺省的赋值运算符重载函数，先看下面的语句：

 对象1＝对象2;

- 实际上是完成了由对象2各个成员到对象1相应成员的复制，其中包括指针成员，这和第8章中复制构造函数和缺省复制构造函数有些类似，如果对象1中含指针成员，并且牵扯到类内指针成员动态申请内存时，问题就会出现。

- 注意下述两个代码的不同：

```cpp
类名 对象1＝对象2; //复制构造函数

   和

类名 对象1; //默认构造函数

对象1＝对象2; //赋值运算符函数

Int a = 3; int b; b = a; 
```

```cpp
//9-9 赋值运算符重载。如果没有，执行时会出错.
#include <iostream>
using namespace std;

class computer
{
private:
	char *brand;						//字符指针brand
	float price;

public:
	computer()							//无参构造函数
	{
		brand = NULL;					//brand初始化为NULL
		price = 0;
		cout << "无参构造函数被调用" << endl;
	}

	computer(const char* sz,float p)
	{
		brand = new char[strlen(sz)+1];	//构造函数中为brand分配一块动态内存
		strcpy(brand, sz);				//字符串复制
		price = p;
		cout << "带参构造函数被调用" << endl;
	}

	computer(const computer& cp)		//复制构造函数
	{
		brand = new char[strlen(cp.brand) + 1];	//为brand分配动态内存
		strcpy(brand, cp.brand);		//字符串复制
		price = cp.price;
		cout << "复制构造函数被调用" << endl;
	}

//	//如果我们没有重载=，则系统会隐式的重载成如下形式:
//	computer &operator=(const computer &cp)
//	{
//		price = cp.price;
//		brand = cp.brand;
//		cout<<"系统默认赋值函数被调用"<<endl;
//		return (*this);
//	}
//
//	//应该使用下述函数取代上述系统隐式的定义
//	computer &operator=(const computer &cp)		//成员函数形式重载赋值运算符
//	{
//		if (this==&cp)							//首先判断是否是自赋值，是的话返回当前对象
//			return  (*this);
//
//		price=cp.price;							//如果不是自赋值，先对price赋值
//		delete[] brand;							//防止内存泄露，先释放brand指向的内容
//		brand=new char[strlen(cp.brand)+1];		//为brand重新开辟一块内存空间
//		if (brand!=NULL)						//如果开辟成功
//		{
//			strcpy(brand,cp.brand);				//复制字符串
//		}
//		cout<<"赋值运算符重载函数被调用"<<endl;
//
//		return  (*this);										//返回当前对象的引用，为的是实现链式赋值
//	}

	~computer()							//析构函数，释放动态内存，delete[] NULL不会出错
	{
		delete[] brand;
		cout << "析构函数被调用" << endl;
	}

	void print()						//成员函数，输出信息
	{
		cout << "品牌：" << brand << endl;
		cout << "价格：" << price << endl;
	}
};

int main()
{
	computer com1("Dell", 2000);	//调用含参构造函数声明对象com1
	computer com2 = com1;			//调用复制构造函数

	if (true)
	{
		computer com3;				//调用无参构造函数
		com3 = com1;				//调用赋值运算符重载函数
	}

	return 0;
}


```

## 6.1 三五法则

1. 需要析构函数的类也需要拷贝构造函数和拷贝赋值函数。
2. 需要拷贝操作的类也需要赋值操作，反之亦然。需要拷贝操作代表这个类在拷贝时需要进行一些额外的操作。赋值操作=先析构+拷贝，所以拷贝需要的赋值也需要。反之亦然。
3. 析构函数不能是私有的。如果类的析构函数是私有的，那么成员便无法销毁。所以在程序中不能定义这个类的对象。可以动态分配该对象并获得其指针，但无法销毁这个动态分配的对象(delete 失效）。
4. 如果一个类有私有的或不可访问的析构函数，那么其默认和拷贝构造函数会被定义为私有的。
5.  如果一个类有`const`或引用成员，则不能使用默认的拷贝赋值操作。

# 7. 特殊数据成员的初始化

- 有4类特殊的数据成员（常量成员、引用成员、类对象成员、静态成员），其初始化及使用方式与前面介绍的普通数据数据成员有所不同，下面展开具体讨论。

## 7.1 `const`数据成员的初始化

- 数据成员可以由`const`修饰，这样，一经初始化，该数据成员便具有“只读属性”，在程序中无法对其值修改;

- 事实上，在构造函数体内或复制构造函数体内初始化`const`数据成员是非法的，如代码8-12;

- `const`数据成员只能通过成员初始化表进行初始化，如代码8-13;

```cpp
//8-12 const成员变量的初始化不能在构造函数体内进行
#include <iostream>
using namespace std;

class point
{
private:
	const int xPos; //符号常量成员xPos和yPos
	const int yPos;

public:
	point(int x, int y)
	{
		xPos = x; //错误，无法直接赋值
		yPos = y;
	}

	point(const point & pt)
	{
		xPos = pt.xPos;
		yPos = pt.yPos;
	}

	void print()
	{
		cout << "xPos: " << xPos << ",yPos: " << yPos << endl;
	}
};

int main()
{
	point pt1(3, 4);//调用有参构造函数
	pt1.print();

	point pt2(pt1);//调用复制构造函数
	pt2.print();

	return 0;
}

//8-13 const数据成员只能在初始化表中进行初始化
#include <iostream>
using namespace std;

class point
{
private:
	const int xPos;
	const int yPos;

public:
	point(int x, int y):xPos(x), yPos(y) //const数据成员只能在初始化表中进行初始化
	{
	}

	point(const point & pt):xPos(pt.xPos), yPos(pt.yPos) //const数据成员只能在初始化表中进行初始化
	{
	}

	void print()
	{
		cout << "xPos: " << xPos << ",yPos: " << yPos << endl;
	}
};

int main()
{
	point pt1(3, 4);
	pt1.print();

	point pt2(pt1);
	pt2.print();

	return 0;
}


```

## 7.2 引用成员的初始化

- 对于引用类型的数据成员，同样只能通过成员初始化表达式进行初始化，见代码8-14

```cpp
#include <iostream>
using namespace std;
class point
{
private:
	int xPos;
	int yPos;
	int &ref1;
	double &ref2;
public:
	point(int x, int y, double &z):ref1(xPos), ref2(z) //引用成员的初始化同样要放在初始化表中
	{
		xPos = x;
		yPos = y;
	}
	//复制构造函数与此一致：)引用成员的初始化同样要放在初始化表中
	point(const point &pt):ref1(pt.ref1), ref2(pt.ref2
	{
		xPos = pt.xPos;
		yPos = pt.yPos;
	}
	void print()
	{
		cout << "xPos: " << xPos << ", yPos: " << yPos;
		cout << ", ref1:  " << ref1 << ", ref2:  " << ref2 << endl;
	}
	void SetX(int x)
	{
		xPos = x;
	}
};

#include "point.h"
int main()
{
	double outInt = 5.0;
	point pt1(3, 4, outInt);
	pt1.print();

	point pt2(pt1);
	pt2.print();

	cout << "改变pt1中的x后" << endl;
	pt1.SetX(7);
	pt1.print();
	pt2.print();

	outInt = 6;
	cout << "outInt变化后：" << endl;
	pt1.print();
	pt2.print();

	return 0;
}
```

## 7.3 类对象成员的初始化

- 类数据成员也可以是另一个类的对象，比如，一个直线类对象中包含两个point类对象，在直线类对象创建时可以在初始化列表中初始化两个`point`对象。

备注代码中是对直线类和`point`类的实现

```cpp
#include <iostream>
using namespace std;
class point //点类的定义
{
private:
	int xPos;
	int yPos;
public:
	point(int x = 0, int y = 0) //带缺省调用的构造函数
	{
		cout << "点的构造函数被执行" << endl;
		xPos = x;
		yPos = y;
	}
	point(const point & pt) //复制构造函数
	{
		cout << "点的复制构造函数被执行" << endl;
		xPos = pt.xPos;
		yPos = pt.yPos;
	}
	void print()
	{
		cout << "( " << xPos << ", " << yPos << ")";
	}
};

class line //line类的定义
{
private:
	point pt1; //point类对象作为line类成员，此处若写成point pt1(3,4)，错
	point pt2;
public:
	line(int x1, int y1, int x2, int y2): pt1(x1, y1), pt2(x2, y2) //line对象的有参构造函数
	{
		cout << "线的构造函数被执行" << endl;
	}
	line(const line &ll):pt1(ll.pt1), pt2(ll.pt2) //line对象的复制构造函数
	{
		cout << "线的复制构造函数被执行" << endl;
	}
	void draw()
	{
		pt1.print();
		cout << "  to  ";
		pt2.print();
		cout << endl;
	}
};

#include "PointAndLine.h"
int main()
{
	line l1(1, 2, 3, 4); //调用有参构造函数
	l1.draw();
	line l2(l1); //调用复制构造函数
	l2.draw();
	return 0;
}

```

- 对复制构造函数来说，一旦给出了自己定义的形式，编译器便不会提供缺省的复制构造函数，因此，确保自定义的复制构造函数的有效性很重要。因此，在一些必须使用自定义复制构造函数的场合，掌握特殊成员的用法很必要。所举例子中，尽管有些复制构造函数纯属“画蛇添足”，用系统提供的缺省复制构造函数足以实现想要的功能，但还是给出了完整的书写形式，这就是原因所在。

## 7.4 static数据成员的初始化

- `C++`允许使用`static`（静态存储）修饰数据成员，这样的成员在编译时就被创建并初始化的（与之相比，对象是在运行时被创建的），且其实例只有一个，被所有该类的对象共享，就像住在同一宿舍里的同学共享一个房间号一样。静态数据成员和第6章中介绍的静态变量一样，程序执行时，该成员已经存在，一直到程序结束，任何对象都可对其进行访问。

- 静态数据成员的初始化必须在类申明之外进行，且不再包含static关键字，格式如下：

```cpp
类型 类名::变量名 = 初始化表达式; //普通变量

**类型 类名****::****对象名****(****构造参数****);  //****对象变量**

 如float computer::total_price = 0;

p代码见8-17
```

```cpp
#include <iostream>
using namespace std;
class computer
{
private:
	float price; //float型数据成员price，表示价格
	static float total_price; //statci成员，总价，不依附于某个对象
public:
	computer(const float p) //构造函数，模拟买电脑的操作，对total_price进行累加	
	{
		price = p;
		total_price += p;
	}
	~computer() //析构函数，模拟退还电脑的操作，从total_price中减去所退电脑的price
	{
		total_price -= price;
	}
	void print() //输出函数
	{
		cout << "总价：" << total_price << endl;
	}
};

#include "computer.h"

float computer::total_price = 0;//初始化
int main()
{
	computer comp1(7000); //买入电脑1
	cout << "购买电脑1后" << endl;
	comp1.print();
	computer comp2(4999); //买入电脑2
	cout << "购买电脑2后" << endl;
	comp2.print();
	computer comp3(2500); //买入电脑3
	cout << "购买电脑3后" << endl;
	comp1.print(); //此处调用comp1.print()、comp2.print()和comp3.print()输出结果相同
	comp2.~ computer(); //退掉电脑2
	cout << "退掉电脑2后" << endl;
	comp3.print();
	return 0;
}
```

# 8. 特殊函数成员

- 除了构造函数、复制构造函数和析构函数外，其他成员函数被用来提供特定的功能，一般来说，提供给外部访问的函数称为接口，访问权限为public，而一些不供外部访问，仅仅作为内部功能实现的函数，访问权限设为private。本节主要讨论函数成员的一些特殊用法

## 8.1 静态成员函数

- 成员函数也可以定义成静态的，与静态成员变量一样，系统对每个类只建立一个函数实体，该实体为该类的所有对象共享。

- 静态成员函数体内不能使用非静态的成员变量和非静态的成员函数；只能调用静态成员数据和函数

- 静态成员函数的参数列表中不含有this指针

- 静态成员函数用法示例见备注代码

```cpp
#include <iostream>
using namespace std;
class computer
{
private:
	char *name;
	float price;
	static float total_price; //静态数据成员
public:
	computer(const char *chr, const float p) //构造函数，模拟买电脑操作
	{
		name = new char[strlen(chr) + 1];
		strcpy(name, chr);
		price = p;
		total_price += p;
	}
	~computer() //析构函数，模拟退掉电脑的操作
	{
		if (name)
		{
			delete[] name;
			name = NULL;
		}
		total_price -= price;
	}
	static void print_total() //静态成员函数，原则上只能访问静态数据成员
	{
		cout << "总价：" << total_price << endl;
	}
	static void print(computer &com); //静态成员函数print()原型，如果要访问某具体对象，必须传递参数
};
void computer::print(computer &com) //静态成员函数print()实现
{
	cout << "名称" << com.name << endl;
	cout << "价格" << com.price << endl;
}

#include "computer.h"
float computer::total_price = 0; //初始化
int main()
{
	computer comp1("IBM", 7000); //声明类对象comp1，初始化，买入
	computer::print(comp1); //类名加作用域限定符访问statci成员函数，传递参数comp1
	computer::print_total(); //类名加作用域限定符访问statci成员函数

	computer comp2("ASUS", 4999); //声明类对象comp2，初始化，买入
	computer::print(comp2); //类名加作用域限定符访问statci成员函数，传递参数comp2
	computer::print_total();

	comp2.~computer(); //析构函数调用，退还电脑
	computer::print_total();

	return 0;
}
```

## 8.2 `const`成员函数

- 之前已经介绍了`const`在函数中的应用，实际上，`const`在类成员函数中还有种特殊的用法，把`const`关键字放在函数的参数表和函数体之间（与之前介绍的`const`放在函数前修饰返回值不同），称为`const`成员函数，其特点有二：

  - 1.只能读取类数据成员，而不能修改之

  - 2.只能调用`const`成员函数，不能调用非`const`成员函数

```cpp
如Point类中的打印函数：

void print(Point * const this)

void print() const 

 **=>**

void print(

  const Point * const this) const
```

```cpp
其基本定义格式为：
     （1）类内定义时：
类型 函数名(参数列表) const
{
	函数体
}
     （2）类外定义时，共分两步：
类内声明：
		     类型 函数名(参数列表) const；
类外定义
类型 类名::函数名(参数列表) const
{
	函数体
}
见备注代码

```

```cpp
//代码8-19
#include <iostream>
using namespace std;

class point
{
	int x; //默认为private的数据成员x和y
	int y;

public:
	point(int xp = 0, int yp = 0) //构造函数
	{
		x = xp;
		y = yp;
	}

	void print() const //const成员函数内无法修改数据成员，否则编译器报错
	{
		x = 5; //1. 试图修改x将引发编译器报错
		set(); //2. 试图调用非const函数将引发编译器报错
		cout << "x: " << x << " ,y: " << y << endl;
	}

	void set() //将set()定义成const函数就能解决问题
	{
	}
};

int main()
{
	point pt;		//声明类对象，以缺省参数形式调用构造函数
	pt.print();		//调用const成员函数

	return 0;
}
```

# 9. 对象的组织

- 有了自己定义的类，或者使用别人定义好的类创建对象，其机制与使用`int`等创建普通变量几乎完全一致，同样可以`const`对象、创建指向对象的指针，创建对象数组，还可使用new和delete等创建动态对象。

## 9.1 `const`对象

- 类对象也可以声明为`const`对象，一般来说，能作用于`const`对象的成员函数除了构造函数和析构函数，便只有`const`成员函数了，因为`const`对象只能被创建、撤销以及只读访问，改写是不允许的。

- 见备注代码

```cpp
//代码8-20
#include <iostream>
using namespace std;

class point //类定义
{
	int x; //默认private型成员变量x和y
	int y;

public:
	point(int xp = 0, int yp = 0)//构造函数
	{
		x = xp;
		y = yp;
	}
	
	~point()					//析构函数
	{
		x = -1;
	}

	void SetX(int xp) //非const成员函数SetX，设置x
	{
		x = xp;
	}

	void SetY(int yp) //非const成员函数SetY，设置y
	{
		y = yp;
	}

	void print() const //const成员函数print，不能修改x和y
	{
		cout << "x: " << x << " ,y: " << y << endl;
	}
};

//#include "point.h"
using namespace std;

int main()
{
	point pt(3, 4);			//声明一个普通类变量pt
	pt.SetX(5);				//使用pt可调用非const成员函数
	pt.SetY(6);
	pt.print();				//pt也可调用const成员函数

	const point ptC(1, 2);	//声明一个const对象（类变量）
	//ptC.SetX(8);			//错误，ptC是const对象，只能调用const成员函数
	//ptC.SetY(9);			//错误，ptC是const对象，只能调用const成员函数
	ptC.~point();			//正确，const对象也能调用非const类型的析构函数
	ptC.print();			//正确，const对象只能调用const成员函数

	return 0;
}

```

## 9.2 指向对象的指针

- 对象占据一定的内存空间，和普通变量一致，C++程序中采用如下形式声明指向对象的指针：

​    类名 * 指针名 [=初始化表达式];

- 初始化表达式是可选的，既可以通过取地址（&对象名）给指针初始化，也可以通过申请动态内存给指针初始化，或者干脆不初始化（比如置为NULL），在程序中再对该指针赋值。 

- 指针中存储的是对象所占内存空间的首地址。



- 针对上述定义，则下列形式都是合法的：

```cpp
point pt; //默认构造函数

point *ptr = NULL; //空指针

point *ptr = &pt; //取某个对象的地址

point *ptr = new point(1, 2.2);//动态分配内存并初始化

point *ptr = new point[5]; //动态分配5个对象的数组空间

p使用指针对象：ptr->print();(*ptr).print();都是合法的。
```

```cpp
#include <iostream>
using namespace std;

class point
{
	int x;
	int y;

public:
	point(int xp = 0, int yp = 0)
	{
		x = xp;
		y = yp;
	}
	
	void print()
	{
		cout << "x: " << x << ", y: " << y << endl;
	}
};
```

## 9.3 对象的大小(`sizeof`)

- 对象占据一定大小的内存空间。总的来说，对象在内存中是以结构形式（只包括非static数据成员）存储在数据段或堆中，类对象的大小（`sizeof`）一般是类中所有非static成员的大小之和。在程序编译期间，就已经为static变量在静态存储区域分配了内存空间，并且这块内存在程序的整个运行期间都存在。而类中的成员函数存在于代码段中，不管多少个对象都只有一个副本。

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

## 9.4 成员变量和成员函数内存中存放方式

![image-20220704131333990](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220704131333990.png)

# 10. this指针

- 前面提到，一个类的所有对象共用成员函数代码段，不管有多少个对象，每个成员函数在内存中只有一个版本，那编译器是如何知道是哪个对象在执行操作呢，答案就是“this指针”。

- this指针是隐含在成员函数内的一种指针，称为指向本对象的指针，可以采用诸如“this->数据成员”的方式来存取类数据成员。

- 举例来说：见备注

```cpp
class Ex {
private:
    int x;
    int y;
public:
    void Set() {
        this->x = 1;
        this->y = 2;
    }
};
```

- 对于类成员函数而言，并不是一个对象对应一个单独的成员函数体，而是此类的所有对象共用这个成员函数体。 当程序被编译之后，此成员函数地址即已确定。而成员函数之所以能把属于此类的各个对象的数据区别开, 就是靠这个this指针。函数体内所有对类数据成员的访问， 都会被转化为this->数据成员的方式。

- this作用域是在类内部，当在类的非静态成员函数中访问类的非静态成员的时候，编译器会自动将对象本身的地址作为一个隐含参数传递给函数

- 举例：见备注

# 11. 对象数组

- 对象数组和标准类型数组的使用方法并没有什么不同，也有声明、初始化和使用3个步骤。

  - (1)对象数组的声明：

    - 类名 数组名[对象个数];

      这种格式会自动调用无参或所有参数都有缺省值的构造函数，类定义要符合该要求，否则编译报错。

  - (2)对象数组的初始化：可以在声明时初始化。

```cpp
对于point(int ix,int iy){}这种没有缺省参数值的构造函数：

point pt[2]={point(1,2), point(3,4)}; // 正确

point pt[ ]={point(1,2), point(3,4)};  // 正确

point pt[5]={point(1,2), point(3,4)}; // 错误

//没有写出来的都是采用point()的形式，需要调用无参构造函数
```

 语句#1和#2是正确的，但语句#3错误，因为pt的后3个元素会自动调用无参的或者所有参数都有缺省值的构造函数，但这样的构造函数不存在。

```cpp
//对象数组的声明
#include <iostream>
using namespace std;

class point
{
private:
	int x;
	int y;

public:
//	point(int ix = 0, int iy = 0)
	point(int ix, int iy)
	{
		static int iCount = 0;
		iCount++;
		cout << iCount << " .构造函数被调用" << endl;
		x = ix;
		y = iy;
	}
};

int main()
{
	//错误: 没有合适的构造函数
	point pt1[2];

	//正确
	point pt2[2] = {point(1,2), point(3,4)};

	//正确, 自动确定数组的元素个数
	point pt3[] = {point(1,2), point(3,4)};

	//错误: 后3个元素会自动调用无参的构造函数，但这样的构造函数不存在
	point pt4[5] = {point(1,2), point(3,4)};

	//解决方法: 给上述构造函数的2个参数定义缺省值
	return 0;
}


```

# 12. 为对象动态分配内存

- 和把一个简单变量创建在动态存储区一样，可以用new和delete为对象分配动态存储区，在复制构造函数一节中已经介绍了为类内的指针成员分配动态内存的相关范例，本节主要讨论如何为对象和对象数组动态分配内存。

使用new和 delete 为单个对象分配/释放动态内存

```cpp
int main(){
	point* p = new point(4,5);
	//动态申请一块内存，存储point类对象，并将地址赋值给point型指针p
	p->print();//使用指针加－>调用成员函数
	delete p;	//释放动态申请的内存，防止内存泄露
	p=NULL;	//养成良好习惯，防止野指针
	return 0;
}
此时，如果写了析构函数，并且是用new动态分配数组的内存空间的话，那么还会多开辟4个字节的内存空间，用来存放分配数组的大小。
详见备注代码
```

```cpp
//使用new/delete为类指针分配/释放内存
#include <iostream>
using namespace std;

class point
{
private:								//private数据成员列表
	int x;
	int y;

public:
	point(int xp=0,int yp=0)			//构造函数，带缺省参数值
	{
		x=xp;
		y=yp;
		cout<<"构造函数被调用"<<endl;
	}

	~point()							//析构函数
	{
		cout<<"析构函数被调用"<<endl;
	}

	void print()						//成员函数，类内部实现
	{
		cout<<"x:  "<<x<<", y:  "<<y<<endl;
	}
};

int main()
{
	point* p = new point(4,5);	//动态申请一块内存，存储point类对象，并将地址赋值给point型指针p
	p->print();					//使用指针加－>调用成员函数
	delete p;					//释放动态申请的内存，防止内存泄露
	p=NULL;						//养成良好习惯，防止野指针

	point *pp = new point[3];	//此时你会发现分配了28个字节的内存空间，多出的最开始的4个字节的内存空间，存放3
	delete[] pp;
	return 0;
}
```

## 12.1 使用new和delete[]为对象数组分配/释放动态空间

- 使用new为对象数组分配动态空间时，不能显式调用对象的构造函数，因此，对象要么没有定义任何形式的构造函数（由编译器缺省提供），要么显式定义了一个（且只能有一个）所有参数都有缺省值的构造函数。

- 见备注代码

```cpp
// 使用new和delete[]为对象数组分配/释放动态空间
#include <iostream>
using namespace std;

class point
{
private: //private数据成员列表
	int x;
	int y;

public:
	point(int xp = 0, int yp = 0) //构造函数，带缺省参数值
	{
		x = xp;
		y = yp;
		cout << "构造函数被调用" << endl;
	}

	~point() //析构函数
	{
		cout << "析构函数被调用" << endl;
	}

	void print() //成员函数，类内部实现
	{
		cout << "x:  " << x << ", y:  " << y << endl;
	}

	void Set(int xp, int yp) //成员函数，类内部实现，用来修改成员x和y
	{
		x = xp;
		y = yp;
	}
};

int main()
{
	point * p = new point[2];	//申请一块动态内存，连续存放连个point对象，将首地址赋值给point指针p
	p[0].print();				//可以将指针当成数组名，使用下标运算符访问对应对象，等价性
	p[1].Set(4, 5);				//调用数据元素（对象）的成员函数Set
	p[1].print();
	delete[] p;					//释放申请的动态内存
	p = NULL;					//养成良好习惯，防止野指针
	return 0;
}
```

- malloc和free不能为对象动态申请内存
  - `malloc/free`无法满足动态对象的要求，因为`malloc`和`free`无法像`new/delete`及`new/delete[]`那样自动调用对象的构造函数和析构函数。



# 13. 类域

- 前面介绍了C++中面向对象编程的基本概念，讨论了类的定义、实现以及对象的创建和组织，特殊数据成员和函数成员的用法等，本章将在前文介绍的基础上，探讨关于对象的一些深层次内容。

- 作用域可分为类作用域、类名的作用域以及对象的作用域几部分内容。

- 在类中定义的成员变量和成员函数的作用域是整个类，这些名称只有在类中（包含类的定义部分和类外函数实现部分）是可见的，在类外是不可见的，因此，可以在不同类中使用相同的成员名。另外，类作用域意味着不能从外部直接访问类的任何成员，即使该成员的访问权限是public，也要通过对象名来调用，对于static成员函数，要指定类名来调用。

- 如果发生“屏蔽”现象，类成员的可见域将小于作用域，但此时可借助this指针或“类名::”形式指明所访问的是类成员，这有些类似于使用“::”访问全局变量。

- 来看一段示例代码

```cpp
//变量的作用域
#include <iostream>
using namespace std;

int x = 100; //定义性声明，全局int型变量x
int z = 200; //定义性声明，全局int型变量z

class Example //Example类定义
{
	int x; //默认为private的成员列表
	int y;
public:
	Example(int xp = 0, int yp = 0) //构造函数
	{
		x = xp;
		y = yp;
	}
	void print(int x) //成员函数print，形参为x
	{
		cout << "传递来的参数:  " <<x  << endl; //形参x覆盖掉了成员x和全局变量x
		cout << "成员x:  " << (this->x) << ", 成员y:  " << y << endl;//此处的y指的是成员y，如果要访问成员x，可使用this指针
		cout << "除了this指针外，还可以使用类名::的形式：" << endl;
		cout << "成员x:  " << Example::x << ", 成员y:  " << y << endl;//或使用类名加作用域限定符的形式指明要访问成员x
		cout << "全局x:  " << (::x) << endl; //访问全局变量x
		cout << "全局z:  " << z << endl; //没有形参、数据成员对全局变量z构成屏蔽，直接访问z即可
	}
};

int main()
{
	Example ex1; //声明一个Example类的对象ex1
	ex1.print(5); //调用成员函数print()
	return 0;
}
```

- 和函数一样，类的定义没有生存期的概念，但类定义有作用域和可见域。
- 使用类名创建对象时，首要的前提是类名可见，类名是否可见取决于类定义的可见域，该可见域同样包含在其作用域中，类本身可被定义在3种作用域内，这也是类定义的作用域：

  - （1）全局作用域

    - 在函数和其他类定义的外部定义的类称为全局类，绝大多数的C++类是定义在该作用域中，我们在前面定义的所有类都是在全局作用域中，全局类具有全局作用域。
  - （2）类作用域(类中类、嵌套类-内部类)
  
    - 一个类可以定义在另一类的定义中，这是所谓嵌套类，举例来说，如果类A定义在类B中，如果A的访问权限是public，则A的作用域可认为和B的作用域相同，不同之处在于必须使用B::A的形式访问A的类名。当然，如果A的访问权限是private，则只能在类内使用类名创建该类的对象，无法在外部创建A类的对象。见代码9-2
  - （3）块作用域
  
    - 类的定义在代码块中，这是所谓局部类，该类完全被块包含，其作用域仅仅限于定义所在块，不能在块外使用类名声明该类的对象。见代码9-3
  - （4）类名也存在覆盖
    - 和普通变量的覆盖原则一样，类名也存在“屏蔽”和“覆盖”，不过，依旧可使用作用域声明符“::”指定具体使用的类名，如“::类名”访问的是全局类，使用“外部类::嵌套类”访问嵌套类。

```cpp
//9-2 嵌套类(类中类)
#include <iostream>
using namespace std;

class line //line类定义
{
public:
	class point //point类定义在line类内，且为public属性，外部可访问
	{
	private: //point类内私有成员列表
		int x;
		int y;

	public:
		point(int xp = 0, int yp = 0) //point类构造函数，带缺省参数值
		{
			x = xp;
			y = yp;
		}

		void printpoint(); //point类成员函数原型，外部实现
	};

private:
	point p1, p2; //line内两个point对象成员

public:
	line(int x1, int y1, int x2, int y2):p1(x1, y1), p2(x2, y2)//构造函数，初始化表
	{
	}

	void printline() //输出提示信息
	{
		p1.printpoint(); //调用对象成员的公共接口
		cout << "  ------->  ";
		p2.printpoint(); //调用对象成员的公共接口
		cout << endl;
	}
};

void line::point::printpoint() //point类中函数printpoint()的实现，注意双重作用域限定符
{
	cout << "( " << x << " , " << y << " )";
}

int main()
{
	line line1(1, 2, 3, 4);	//调用line类构造函数，声明一个line类的对象line1
	line1.printline();		//输出提示信息

	line::point pt(1, 3);	//以line::point访问point类定义，声明一个point类的对象pt
	pt.printpoint();		//输出提示信息

	cout << endl;			//为整齐美观，换行
	return 0;
}

//9-3 块作用域
#include <iostream>
using namespace std;

int main()
{
	void Work(int, int);	//work函数原型声明
	Work(5, 6);				//work函数调用
	return 0;
}

void Work(int a, int b)
{
	class point				//类定义在函数内，在函数外无法使用point创建对象
	{
	private:
		int x, y;
	public:
		point(int xp = 0, int yp = 0)
		{
			x = xp;
			y = yp;
		}
		void print()
		{
			cout << x << "," << y << endl;
		}
	};

	point pt(a, b);	//函数内，创建point类的对象pt
	pt.print();		//输出提示信息
}
```

## 13.1 对象的生存期、作用域和可见域

- 类名无生存期，只有作用域和可见域。

- 对象有生存期，对象的生存期也是对象中所有非静态成员变量的生存期，这些成员变量都随着对象的创建而创建，随着对象的撤销而撤销。

- 对象的生存期、作用域和可见域取决于对象的创建位置，同样有全局、局部、类内之分，和前面关于普通变量的介绍并无区别，这里便不在赘述。

- 关于对象创建有几点问题需要强调。

- 先定义，后实例化

- 类的定义一定要在类对象声明之前，因为编译器要知道需要为类分配多大的内存空间，仅仅对类进行声明是不够的，如：

  ```cpp
  class B;//前向声明，减少循环依赖
  
  B objectB; /创建B类的对象。错误
  
  
  
  class B
  
  {
  
   ……
  
  }; //B类定义
  ```
```cpp
#include <iostream>
using namespace std;

class point;	//声明
point ptA;		//错误, 类对象的创建必须在类定义之后, 因为该语句需要调用构造函数
point *pB = NULL;			//正确
point *pC = new point();	//错误, 因为new语句会导致调用构造函数

class point
{
private:
	int x;
	int y;

public:
	point(int ix = 0, int iy = 0):x(ix), y(iy) {}
};

int main()
{
	return 0;
}

```

- 但是，如果不创建B类的对象，而仅仅是声明一个指向类型B对象的指针（或引用），是可行的。如：

```cpp
class B; //声明

B* pB=NULL; //创建B类的对象。正确

B* pC=new B; //创建B类的对象。错误

class B

{

 ……

}; //B类定义
```

- 见备注代码

```cpp
#include <iostream>
using namespace std;

class point;	//申明
point ptA;	//错误, 类对象的创建必须在类定义之后, 因为该语句需要调用构造函数
point *pB = NULL;	//正确
point *pC = new point();	//错误, 因为new语句会导致调用构造函数

class point
{
private:
	int x;
	int y;

public:
	point(int ix = 0, int iy = 0):x(ix), y(iy) {}
};

int main()
{
	return 0;
}
```

## 13.2 对象内存释放与堆内存

- 一种普遍的误解是“如果对象被撤销，其占据的内存空间被释放，那么对象创建时和函数执行中通过new和malloc申请的动态内存也会被自动释放”，实际上，除非显式地用delete或free释放，申请的动态内存不会随着对象的撤销而撤销，相反，撤销了对象，却没有释放动态内存反而会引起内存泄露。

- 当然，在程序结束时，操作系统会回收程序所开辟的所有内存。尽管如此，还是要养成new/delete、malloc/free配对的编程习惯，及时释放已经无用的内存。

# 14. 友元

- 一般来说，类的私有成员只能在类的内部访问，类外的函数是不能访问它们的。

- 但是，可以将一个函数定义为类的友元函数，这时该函数就可以访问该类的私有成员了。

- 同时，也可以把另一个类B定义为本类A的友元类，这样B类就可以访问A类的任何成员了。

- 下面来具体讨论友元函数和友元类的概念。

## 14.1 友元之非成员函数

- 在类的定义中用friend声明了一个外部函数或其他类的成员函数(public和private均可）后，这个外部函数称为类的友元函数。

- 友元函数声明的基本格式为：

```cpp
 friend 函数原型;
```

- 友元函数中可访问类的private成员。

- 用下面的比喻形容友元函数可能比较恰当，将类比作一个家庭，类的private成员相当于家庭的秘密，一般的外人是不允许探听这些秘密的，只有friend（朋友）才有能力探听这些秘密。

- 见备注代码

```cpp
//将一个外部函数申明为类的友元函数
#include <cmath>	//使用计算平方根的函数sqrt要用到的头文件
#include <iostream>
using namespace std;

class Point										//Point类定义
{
private:
	int x, y;
//	friend float dis(Point &p1, Point & p2);	//友元函数的声明，声明位置没有关系，可以是public，也可是private
	
public:
	Point(int i = 0, int j = 0)	//构造函数，带缺省参数值
	{
		x = i;
		y = j;
	}
	
	void disp()			//成员函数
	{
		cout << "(" << x << "," << y << ")";
	}
};

float dis(Point & p1, Point & p2)		//友元函数的实现
{
	//友元函数中可访问类的private成员
	float d = sqrt((p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y));
	return d;
}

int main()
{
	Point p1(1, 2), p2(4, 5);	//声明两个Point类的对象p1和p2
	p1.disp();			//显示点p1的信息
	
	cout << "与";
	p2.disp();			//显示点p2的信息
	
	cout << "距离=" << dis(p1, p2) << endl;	//利用友元函数计算两点举例
	
	return 0;
}
```

## 14.2 友元之成员函数

- A类的成员函数作为B类的友元函数时，必须先定义A类，而不仅仅是声明它。

- 注意：将其他类的成员函数申明为本类的友元函数后，该友元函数并不能变成本类的成员函数。也就是说，朋友并不能变成家人。

- 成员形式的友元函数见备注代码

- 上述代码中，Line类的成员函数dis(…)的实现必须在类外进行，且必须在Point类的定义之后。因为其参数中包含了Point这种类型。

- Line类的dis()函数本来是不能访问`Point.x`和`Pint.y`这种Point类的private成员的，但在Point类中将dis()申明为友元函数后就能访问了。但dis()函数依然不是Point类的成员函数。也就是说，dis() 是Point类的朋友了,可以访问Point类的私有成员变量x和y了。

```cpp
//将Line类的成员函数dis()作为Point类的友元函数
#include <cmath>		//使用计算平方根的函数sqrt要用到的头文件
#include<iostream>
#include <cmath>
using namespace std;

class Point;		//声明Point类

class Line			//定义Line类
{
public:
	float dis(Point& p1, Point& p2); 		//友元函数的原型，作为Line类的成员函数
};

class Point					//定义Point类
{
private:
	int x,y;				//private型数据成员x和y
	friend float Line::dis(Point &p1, Point &p2);	//友元的声明

public:
	Point(int i = 0, int j = 0)	//Point类的构造函数，带缺省参数
	{
		x = i;
		y = j;
	}

	void disp()			//成员函数disp()，用来输出点的信息
	{
		cout << "(" << x << "," << y << ")";
	}
};

//Line类内成员函数dis的实现，作为Point类的友元函数
float Line::dis(Point &p1, Point &p2)
{
	float d = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	//可访问Point类对象的private成员

	return d;
}

int main()
{
	Line line1;			//声明一个Line类的对象line1
	Point p1(1,2), p2(4,5);		//声明两个Point类的对象p1和p2

	p1.disp();			//输出点p1的信息 
	cout << " 与 "; 
	p2.disp();			//输出点p2的信息

	cout << " 的距离 = " << line1.dis(p1, p2) << endl;
	//通过调用line1的成员函数dis计算两个点间的距离

	return 0;
}
```

## 14.3 友元函数的重载

- 要想使得一组重载函数全部成为类的友元，必须一一声明，否则只有匹配的那个函数会成为类的友元，编译器仍将其他的当成普通函数来处理。

```cpp
class Exp {
public:
    friend void test(int);
};

void test();

void test(int);

void test(double);
```

- 上述代码中，只有`“void test(int)”`函数是`Exp`类的友元函数，`“void test()”`和`“void test(double)”`函数都只是普通函数。

## 14.4 友元类

- 类A作为类B的友元时，类A称为友元类。A中的所有成员函数都是B的友元函数，都可以访问B中的所有成员。

- A可以在B的public部分或private部分进行声明，方法如下：

```cpp
friend [class]<类名>; //友元类类名
```

- 见备注代码

```cpp
//9-6 友元类
#include<iostream>
#include <cmath>
using namespace std;

class CLine;	//声明类CLine

class CPoint 	//定义CPoint类
{
private:
	int x, y;
	friend class CLine; //友元类的声明，位置同样不受限制
	
public:
	CPoint(int i = 0, int j = 0) //构造函数，带缺省参数值
	{
		x = i;
		y = j;
	}
	
	void disp() //成员函数，输出点的信息
	{
		cout << "(" << x << "," << y << ")";
	}
};

class CLine	//类CLine的定义，其中所有的函数都是CPoint类的友元函数
{
public:
	float dis(CPoint& p1,CPoint& p2)	//可访问p1和p2的private成员
	{
		float d;
		d=sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
		return d;
	}

	void Set(CPoint* p1,int a,int b)		//可访问p1和p2的private成员
	{
		p1->x=a;
		p1->y=b;
	}
};

int main()
{
	CLine cz1;			//声明一个CLine类的对象cz1
	CPoint p1(1,2),p2(4,5);	//声明两个CPoint类对象p1和p2

	p1.disp();				//输出点p1的信息 
	cout<<"与";
	p2.disp();				//输出点p2的信息
	cout<<"距离="<<cz1.dis(p1,p2)<<endl;	//调用cz1的成员函数dis计算两点间距

	cz1.Set(&p1,3,4);		//调用cz1的成员函数Set改写p1中的private成员x和y
	p1.disp();			//修改后的点p1信息输出

	cout<<endl;		//换行

	return 0;
}
```

## 14.5 友元是否破坏了封装性

- 不可否认，友元在一定程度上将类的私有成员暴露出来，破坏了信息隐藏机制，似乎是种“副作用很大的药”，但俗话说“良药苦口”，好工具总是要付出点代价的，拿把锋利的刀砍瓜切菜，总是要注意不要割到手指的。

- 友元的存在，使得类的接口扩展更为灵活，使用友元进行运算符重载从概念上也更容易理解一些，而且，C++规则已经极力地将友元的使用限制在了一定范围内，它是单向的、不具备传递性、不能被继承，所以，应尽力合理使用友元。

# 15. 运算符重载

- C++内部定义的数据类型(int , float, …)的数据操作可以用运算符号来表示，其使用形式是表达式；用户自定义的类型的数据的操作则用函数表示，其使用形式是函数调用。为了使对用户自定义数据类型的数据的操作与内置的数据类型的数据的操作形式一致，C++提供了运算符的重载，通过把C++中预定义的运算符重载为类的成员函数或者友元函数，使得对用户的自定义数据类型的数据—对象的操作形式与C++内部定义的类型的数据一致。 

- 首先来看一个问题：备注代码定义了一个复数类complex，然后用complex定义了2个复数，如何实现这2个复数的加法呢？

- 这个问题的解决就需要用到运算符重载的知识，下面详细讲解。

```cpp
//运算符重载的必要性
#include <iostream>
using namespace std;

class complex		//定义复数类 complex
{
private:
	double real, imag;	//private 成员，分别代表实部和虚部

public:
	complex(double r = 0.0, double i = 0.0)	//构造函数，带缺省参数值
	{
		real = r;
		imag = i;
	}

	void disp()		//成员函数，输出复数
	{
		cout << real << " + " << "i*" << imag << endl;
	}
};

int main()
{
	complex cx1(1.0, 2.0);
	complex cx2(3.0, 4.0);
	complex cxRes = cx1 + cx2;	//错误
	
	return 0;
}
```

## 15.1 运算符重载规则

- 运算符是一种通俗、直观的函数，比如：

```cpp
int x = 2 + 3;

语句中的“+”操作符
```

- 系统本身就提供了很多个重载版本：

```cpp
int operator + (int，int);

double operator + (double,double);
```

- 可以重载的运算符有：

```cpp
双目运算符+ - * / %

关系运算符== != < > <= >=

逻辑运算符|| && +

单目运算符+ - * &

自增自减运算符++ --

位运算符| & ~ ^ << >>

赋值运算符= += -= *= /= %= &= |= ^= <<= >>=

空间申请和释放new delete new[] delete[]

其他运算符() -> ->* , []
```

- 不能重载的运算符有：

```cpp
成员访问符 .

成员指针访问运算符 .*

域运算符 ::

长度运算符 sizeof 

条件运算符号 ?:
```

- 重载操作符必须具有一个类类型或者是枚举类型的操作数

```cpp
int operator+(int, int);//不能重载
```

- 优先级和结合性是固定的

```cpp
操作符的优先级、结合性或操作数个数不能改变

X == Y + Z;
```

- 不再具备短路求值特性

```cpp
重载操作符并不保证操作数的求值顺序 && ||  ,
```

- 不能臆造并重载一个不存在的运算符，

```cpp
如@, #，$等。
```

## 15.2 运算符重载的方式

- 运算符重载的方式分为下面3种：

1. 采用普通函数的重载形式

2. 采用友元函数的重载形式

3. 采用成员函数的重载形式

- 普通函数形式重载运算符，要求待操作的属性必须是public类型的。

- 参见如下代码：

```cpp
// 普通函数形式 的 运算符重载
#include <iostream>
using namespace std;

class complex		//定义复数类 complex
{
public:
	double real, imag;	//private 成员，分别代表实部和虚部

public:
	complex(double r = 0.0, double i = 0.0)	//构造函数，带缺省参数值
	{
		real = r;
		imag = i;
	}

	void disp()		//成员函数，输出复数
	{
		cout << real << " + " << "i*" << imag << endl;
	}
};

complex operator+(const complex& obj1, const complex& obj2)		//加+的实现
{
	return complex(obj1.real + obj2.real, obj1.imag + obj2.imag);
}

int main()
{
	complex cx1(1.0, 2.0), cx2(3.0, 4.0), cxRes;

	cxRes = cx1 + cx2;	//相当于cx1.operator+(cx2)
	cxRes.disp();

	return 0;
}
```

## 15.3 以普通函数形式重载运算符

- 普通函数形式重载运算符，要求待操作的属性必须是public类型的。

- 参见如下代码：

```cpp
// 普通函数形式 的 运算符重载
#include <iostream>
using namespace std;

class complex		//定义复数类 complex
{
public:
	double real, imag;	//private 成员，分别代表实部和虚部

public:
	complex(double r = 0.0, double i = 0.0)	//构造函数，带缺省参数值
	{
		real = r;
		imag = i;
	}

	void disp()		//成员函数，输出复数
	{
		cout << real << " + " << "i*" << imag << endl;
	}
};

complex operator+(const complex& obj1, const complex& obj2)		//加+的实现
{
	return complex(obj1.real + obj2.real, obj1.imag + obj2.imag);
}

int main()
{
	complex cx1(1.0, 2.0), cx2(3.0, 4.0), cxRes;

	cxRes = cx1 + cx2;	//相当于cx1.operator+(cx2)
	cxRes.disp();

	return 0;
}

```

## 15.4 以成员函数形式重载运算符

- 成员函数形式的运算符声明和实现与成员函数类似，首先应当在类定义中声明该运算符，声明的具体形式为：

返回类型 operator 运算符（参数列表）;

- 既可以在类定义的同时定义运算符函数使其成为inline型，也可以在类定义之外定义运算符函数，但要使用作用域限定符“::”，类外定义的基本格式为：

```cpp
返回类型 类名::operator 运算符（参数列表）

{

…

}               见备注代码
```

```cpp
//成员函数形式 的 运算符重载
#include <iostream>
using namespace std;

class complex	//定义复数类 complex
{
private:
	double real, imag;	//private 成员，分别代表实部和虚部

public:
	complex(double r = 0.0, double i = 0.0)	//构造函数，带缺省参数值
	{
		real = r;
		imag = i;
	}

	complex operator+= (const complex &);	//成员函数形式重载加+=

	complex operator+(const complex &);	//成员函数形式重载加+
	complex operator-(const complex &);	//成员函数形式重载减－
	complex operator-();			//成员函数形式重载一元－（取反）
	complex operator*(const complex &);	//成员函数形式重载乘*
	complex operator/(const complex &);	//成员函数形式重载除*

	complex& operator++();	//成员函数形式重载前置++
	complex operator++(int);	//成员函数形式重载后置++

	void disp()			//成员函数，输出复数
	{
		cout << real << " + " << "i*" << imag << endl;
	}
};

complex complex::operator+=(const complex& CC)		//加+=的实现
{
	real += CC.real;
	imag += CC.imag;
	return (*this);
}

complex complex::operator+(const complex& CC)		//加+的实现
{
	return complex(real + CC.real, imag + CC.imag);
}

complex complex::operator-(const complex& CC)		//减-的实现
{
	return complex(real - CC.real, imag - CC.imag);
}

complex complex::operator*(const complex& CC)		//乘*的实现
{
	return complex(real * CC.real - imag * CC.imag, real * CC.imag + imag * CC.real);
}

complex complex::operator/(const complex& CC)		//除/的实现
{
	return complex((real * CC.real + imag * CC.imag) / (CC.real * CC.real + CC.imag * CC.imag),
		(imag * CC.real - real * CC.imag) / (CC.real * CC.real + CC.imag * CC.imag));
}

complex complex::operator-()		//单目-，即取反的实现
{
	return complex(-real, -imag);
}

complex& complex::operator++()	//前置++的实现
{
	cout << "前置++" << endl;
	++real;
	++imag;
	return (*this);
}

complex complex::operator++(int)	//后置++的实现，体会和前置++的区别
{
	cout << "后置++" << endl;
	complex cTemp = (*this);	//最终的返回值的是原来的值，因此需要先保存原来的值
	++(*this);					//返回后原来的值需要加1
	return cTemp;
}

int main()
{
	complex cx1(1.0, 2.0), cx2(3.0, 4.0), cxRes;

	cxRes += cx2;		//相当于cxRes.operator+=(cx2)
	cxRes.disp();
	
	cxRes = cx1 + cx2;	//相当于cx1.operator+(cx2)
	cxRes.disp();
	
	cxRes = cx1 - cx2;	//相当于cx1.operator-(cx2)
	cxRes.disp();
	
	cxRes = cx1 * cx2;	//相当于cx1.operator*(cx2)
	cxRes.disp();
	
	cxRes = cx1 / cx2;	//相当于cx1.operator/(cx2)
	cxRes.disp();
	
	cxRes = -cx1;		//相当于cx1.operator-()
	cxRes.disp();
	
	cout << endl;
	
	complex cx3(1.0, 1.0), cx4(5.0, 5.0);
	
	cxRes = ++cx3;		//相当于cx3.operator++()
	cxRes.disp();
	cx3.disp();

	cout << endl;
	
	cxRes = cx4++;		//相当于cx4.operator++(0)
	cxRes.disp();
	cx4.disp();

	cout << endl;
	
	//注意下述语句在友元函数形式和成员函数形式中的对比。
	cxRes = cx1 + 5;	//相当于cx1.operator+(5) 或 cx1.operator+(complex(5))
	cxRes.disp();

//	cxRes = 5 + cx1;	//错误. 相当于5.operator+(cx1);
//	cxRes.disp();

	return 0;
}
```

## 15.5 以友元函数形式重载运算符

- 用成员函数重载双目运算符时，左操作数无须用参数输入，而是通过隐含的this指针传入，这种做法的效率比较高

- 此外，操作符还可重载为友元函数形式，这将没有隐含的参数this指针。对双目运算符，友元函数有2个参数，对单目运算符，友元函数有一个参数。

- 重载为友元函数的运算符重载函数的声明格式为：

```cpp
friend 返回类型operator 运算符 (参数表);
```

- 以友元函数形式重写代码，见备注代码

```cpp
//友员函数形式 的 运算符重载
#include <iostream>
using namespace std;

class complex		//定义复数类complex
{
private:
	double real,imag;	//private成员，分别代表实部和虚部

public:
	complex(double r=0.0,double i=0.0)	//构造函数，带缺省参数值
	{
		real=r;
		imag=i;
	}

	friend complex operator + (const complex &,const complex &);	//友元函数形式重载加+
	friend complex operator - (const complex &,const complex &);	//友元函数形式重载减－
	friend complex operator - (const complex &);	//友元函数形式重载一元－（取反）
	friend complex operator * (const complex &,const complex &);	//友元函数形式重载乘*
	friend complex operator / (const complex &,const complex &);	//友元函数形式重载除*
	friend complex& operator ++(complex &);		//友元函数形式重载前置++
	friend complex operator ++(complex &,int);		//友元函数形式重载后置++

	void disp()														//成员函数，输出复数
	{
		cout<<real<<" + "<<"i*"<<imag<<endl;
	}
};

complex operator +(const complex& C1,const complex& C2)		//加+的实现
{
	return complex(C1.real + C2.real, C1.imag + C2.imag);
}

complex operator -(const complex& C1,const complex& C2)		//减-的实现
{
	return complex(C1.real - C2.real, C1.imag - C2.imag);
}

complex operator -(const complex& C1)		//单目-，即取反的实现
{
	return complex(-C1.real, -C1.imag);
}

complex operator *(const complex& C1,const complex& C2)		//乘*的实现
{
	return complex(C1.real * C2.real - C1.imag * C2.imag, C1.real * C2.imag + C1.imag * C2.real);
}

complex operator /(const complex& C1,const complex& C2)		//除*的实现
{
	return complex((C1.real * C2.real + C1.imag + C2.imag) / (C2.real * C2.real + C2.imag * C2.imag),
		(C1.imag * C2.real - C1.real * C2.imag) / (C2.real * C2.real + C2.imag * C2.imag));
}

complex& operator ++(complex& C1)		//前置++的实现
{
	cout << "前置++" << endl;
	C1.real += 1;
	C1.imag += 1;
	return C1;
}

complex operator ++(complex& C1,int)	//后置++的实现，体会和前置++的区别
{
	cout << "后置++" << endl;
	complex ctemp = C1;
	++C1;
	return ctemp;
}

int main()
{
	complex cx1(1.0, 2.0), cx2(3.0, 4.0), cxRes;
	
	cxRes = cx1 - cx2;	//相当于operator-(cx1, cx2)
	cxRes.disp();
	
	cxRes = -cx1;		//相当于operator-(cx1)
	cxRes.disp();
	
	cxRes = cx1 + cx2;	//相当于operator+(cx1, cx2)
	cxRes.disp();
	
	cxRes = cx1 * cx2;	//相当于operator*(cx1, cx2)
	cxRes.disp();
	
	cxRes = cx1 / cx2;	//相当于operator/(cx1, cx2)
	cxRes.disp();
	
	complex cx3(1.0, 1.0), cx4(5.0, 5.0);
	
	cxRes = ++cx3;		//相当于operator++(cx3)
	cxRes.disp();
	cx3.disp();
	
	cxRes = cx4++;		//相当于operator++(cx4, 0)
	cxRes.disp();
	cx4.disp();
	
	//注意下述语句在友元函数形式和成员函数形式的对比。
	cxRes = cx1 + 5;	//相当于operator+(cx1, 5);
	cxRes.disp();

	cxRes = 5 + cx1;	//相当于operator+(5, cx1);
	cxRes.disp();

	return 0;
}
```

## 15.6 友员函数形式和成员函数形式的比较

- 对于绝大多数可重载操作符来说，两种重载形式都是允许的。但对下标运算符[] 、赋值运算符=、函数调用运算符()、指针运算符->，只能使用成员函数形式。

- 对于如下代码：

```cpp
complex c1(1.0, 2.0), cRes;

cRes = c1 + 5; //#1

cRes = 5 + c1; //#2
```

- 友元函数形式重载的都是合法的，可转换成：

```cpp
cRes = operator+(c1, 5); //#1 合法

cRes = operator+(5, c1); //#2 合法
```

- 但成员函数形式的重载，只有语句#1合法，语句#2非法

```cpp
cRes = c1.operator+(complex(5)); //#1 可能合法

cRes = 5.operator+(c1); //#2 非法，5不会隐式转换成complex
```

## 15.7 对运算符重载的补充说明

- 运算符重载可以改变运算符内置的语义，如以友元函数形式定义的加操作符：

```cpp
complex operator +(const complex& C1,const complex& C2)
{
     return complex(C1.real-C2.real,C1.imag-C2.imag);
}
```

- 明明是加操作符，但函数内却进行的是减法运算，这是合乎语法规则的，不过却有悖于人们的直觉思维，会引起不必要的混乱，因此，除非有特别的理由，尽量使重载的运算符与其内置的、广为接受的语义保持一致。

## 15.8 几种特殊的运算符重载

- 本节重点演示几种特殊运算符的重载示例，运算符的重载是很灵活的工具，使用得当，会带来意想不到的便利。

### 15.8.1 赋值运算符=

- 赋值运算是一种很常见的运算，如果不重载赋值运算符，编译器会自动为每个类生成一个缺省的赋值运算符重载函数，先看下面的语句：

```cpp\
对象1＝对象2;
```

- 实际上是完成了由对象2各个成员到对象1相应成员的复制，其中包括指针成员，这和第8章中复制构造函数和缺省复制构造函数有些类似，如果对象1中含指针成员，并且牵扯到类内指针成员动态申请内存时，问题就会出现。

- 注意下述两个代码的不同：

```cpp
类名 对象1＝对象2; //复制构造函数

类名 对象1(对象2);

  和

类名 对象1; //默认构造函数

对象1＝对象2; //赋值运算符函数

p见备注代码
```

```cpp
//9-9 赋值运算符重载。如果没有，执行时会出错.
#include <iostream>
using namespace std;

class computer
{
private:
	char *brand;	//字符指针brand
	float price;

public:
	computer()		//无参构造函数
	{
		brand = NULL;	//brand初始化为NULL
		price = 0;
		cout << "无参构造函数被调用" << endl;
	}

	computer(const char* sz,float p)
	{
		brand = new char[strlen(sz)+1];	//构造函数中为brand分配一块动态内存
		strcpy(brand, sz);				//字符串复制
		price = p;
		cout << "带参构造函数被调用" << endl;
	}

	computer(const computer& cp)		//复制构造函数
	{
		brand = new char[strlen(cp.brand) + 1];	//为brand分配动态内存
		strcpy(brand, cp.brand);		//字符串复制
		price = cp.price;
		cout << "复制构造函数被调用" << endl;
	}

//	//如果我们没有重载=，则系统会隐式的重载成如下形式:
//	computer &operator=(const computer &cp)
//	{
//		price = cp.price;
//		brand = cp.brand;
//		cout<<"系统默认赋值函数被调用"<<endl;
//		return (*this);
//	}
//
//	//应该使用下述函数取代上述系统隐式的定义
//	computer &operator=(const computer &cp)		//成员函数形式重载赋值运算符
//	{
//		if (this==&cp)	//首先判断是否是自赋值，是的话返回当前对象
//			return  (*this);
//
//		price=cp.price;	//如果不是自赋值，先对price赋值
//		delete[] brand;	//防止内存泄露，先释放brand指向的内容
//		brand=new char[strlen(cp.brand)+1];	//为brand重新开辟一块内存空间
//		if (brand!=NULL)			//如果开辟成功
//		{
//			strcpy(brand,cp.brand);	//复制字符串
//		}
//		cout<<"赋值运算符重载函数被调用"<<endl;
//
//		return  (*this);										//返回当前对象的引用，为的是实现链式赋值
//	}

	~computer()	//析构函数，释放动态内存，delete[] NULL不会出错
	{
		delete[] brand;
		cout << "析构函数被调用" << endl;
	}

	void print()	//成员函数，输出信息
	{
		cout << "品牌：" << brand << endl;
		cout << "价格：" << price << endl;
	}
};

int main()
{
	computer com1("Dell", 2000);	//调用含参构造函数声明对象com1
	computer com2 = com1;			//调用复制构造函数

	if (true)
	{
		computer com3;				//调用无参构造函数
		com3 = com1;				//调用赋值运算符重载函数
	}

	return 0;
}
```

### 15.8.2 函数调用运算符()

- 函数调用运算符()同样只能重载为成员函数形式。其形式为：

```cpp
返回类型 operator()(arg1,arg2,……)

参数个数可以有多个，没有限制。
```

- 针对如下定义：

```cpp
void computer::operator()(){};

int computer::operator()(int x){};

char computer::operator()(char x, char y){};

 可以这样调用：

computer com1;

int z = com1(3200);

char c = com1(‘a’, ‘b’);
```

- 一个类如果重载了函数调用operator()，就可以将该类对象作为一个函数使用，这样的类对象也称为函数对象。函数也是一种对象，这是泛型思考问题的方式。

- 见备注代码

```cpp
//重载函数调用运算符()
#include <iostream>
using namespace std;

class Demo		//Demo类定义
{
public:
	double operator()(double x, double y)	//重载函数调用符(),两个double型参数
	{
		return x > y ? x : y;		//返回两个参数中较大的一个
	}

	double operator()(double x, double y, double z)	//重载函数调用符(),3个double型参数
	{
		return (x + y) * z;	//将前两个相加，与第3个参数相乘，返回最后的结果
	}
};

void main()
{
	Demo de;											//声明一个类对象
	cout << de(2.5, 0.2) << endl;	//可以将对象像函数一样使用
	cout << de(1.2, 1.5, 7.0) << endl;
}
```

### 15.8.3 下标运算符[]

- 下标运算符是个二元运算符，C++编译器将表达式

```cpp
 sz[x];

   解释为

 sz.operator[](z);
```

- 一般情况下，下标运算符的重载函数原型如下：

```cpp
返回类型& operator[ ](参数类型);
```

- 下标运算符的重载函数只能有一个参数，不过该参数并没有类型限制，任何类型都可以，如果类中未重载下标运算符，编译器将会给出下标运算符的缺省定义，此时，参数必须是`int`型，并且要声明数组名才能使用下标变量，如

```cpp
 computer com[3];
```

- 则com[1]等价于com.operator[](1)，如果[]中的参数类型非int型，或者非对象数组要使用下标运算符时，需要重载下标运算符[]。

- 见备注代码

```cpp
//9-11 下标运算符[]
#include <iostream>
using namespace std;

class CharSZ	//类CharSZ的定义
{
private:		//private成员列表
	int iLen;
	char *pBuf;

public:
	CharSZ(int size)	//构造函数
	{
		iLen= size;
		pBuf = new char[iLen];	//开辟一块动态内存，字符数组
	}

	~CharSZ()			//析构函数
	{
		delete pBuf;	//释放申请的动态内存
	}

	int GetLen()		//读取private成员iLen的值
	{
		return iLen;
	}

	char& operator [](int i);	//以成员函数形式重载下标运算符
};

char & CharSZ::operator[](int i)//下标运算符重载的实现
{
	static char szNull = '\0';	//用于返回空字符时, 由于返回类型为char &，不能直接return '\0';
	if (i < iLen && i >= 0)	//如果参数i在有效范围内
	{
		return pBuf[i];	//返回字符数组的第i＋1个元素
	}
	else
	{
		cout << "下标越界" << endl;	//参数i不合法
		return szNull;	//输出空字符. 不能直接return '\0';
	}
}

int main()
{
	char *sz = "Hello, world!";
	CharSZ de(strlen(sz) + 1);   //对象de中申请的动态内存大小为n，可存放n-1个有效字符（除开'\0'）

	//将sz的内容复制给de
	int i;
	for (i = 0; i < (strlen(sz) + 1); i++)
	{
		de[i] = sz[i];
	}

	//逐个输出de的值
	for (i = 0; i < de.GetLen(); i++)
	{
		cout << de[i];
	}

	cout << endl;
	return 0;
}
```

15.8.4 new和delete重载

- 通过重载new和delete,我们可以自己实现内存的管理策略。new和delete只能重载为类的静态运算符。而且重载时，无论是否显示指定static关键字，编译器都认为是静态的运算符重载函数。

- 重载new时，必须返回一个void *类型的指针，它可以带多个参数，但第1个参数必须是size_t类型，该参数的值由系统确定。

```cpp
static void * operator new(size_t nSize)

 {

 cout << "new操作符被调用, size = " << nSize << endl;

 void * pRet = new char[nSize];

 return pRet;

 }
```

- 重载delete时必须返回void类型，它可以带有多个参数，第1个参数必须是要释放的内存的地址void *，如果有第2个参数，它必须为size_t类型。

```cpp
 static void operator delete(void * pVoid)

 {

 cout << "delete操作符被调用." << endl;

 delete [] pVoid;

 }
```

```cpp
//new 和 delete 运算符重载
#include <iostream>
using namespace std;

class CStudent
{
public:
	int iId;
	char szName[10];

public:
	static void * operator new(size_t nSize)
	{
		cout << "new 操作符被调用, size = " << nSize << endl;
		void * pRet = new char[nSize];
		return pRet;
	}

	static void operator delete(void * pVoid)
	{
		cout << "delete 操作符被调用." << endl;
		delete [] pVoid;
	}
};

int main()
{
	CStudent *pStu = new CStudent();

	pStu->iId = 101;
	strcpy(pStu->szName, "Tony");

	delete pStu;

	return 0;
}
```

### 15.8.4 输入>>输出<<的重载

- `>>`和`<<`运算符只能重载为友元函数形式。

- 对操作符<<的重载

```cpp
friend ostream& operator<<(ostream& os,const Complex& C1)

{

 os<<C1.real<<"+i*"<<C1.imag<<endl;

 return os;

}
```

- 对操作符>>的重载

```cpp
friend istream& operator>>(istream& is,Complex& C1)

{

 is>>C1.real;

 while (is.get()!='*‘);

 is>>C1.imag;

 return is;

}
```

- 参见备注代码

```cpp
//对操作符>>的重载
#include <iostream>
using namespace std;


class Complex
{
private:
	double imag;		//虚部
	double real;		//实部
public:
	Complex(double r=0.0,double i=0.0)	//构造函数
	{
		real=r;
		imag=i;
	}
	friend ostream& operator<<(ostream& ,Complex& );		//友元函数声明
	friend istream& operator>>(istream& ,Complex& );
};

ostream& operator<<(ostream& os,Complex& C1)			//对操作符<<的重载
{
	os<<C1.real<<"+i*"<<C1.imag<<endl;
	return os;
}

istream& operator>>(istream& is,Complex& C1)			//对操作符>>的重载
{
	is>>C1.real;
	while (is.get()!='*')
	{
	}
	is>>C1.imag;
	return is;
}

int main()
{
	Complex c1(2.5,3.1);
	cin>>c1;
	cout<<c1;
	return 0;
}
```

### 15.8.5 指针运算符->的重载   * 解引用运算符

- 箭头运算符必须是类的成员函数

- 指针运算符返回值必须是一个指针，或者是一个重载了箭头运算符的对象。
  - 如果返回的是一个指针将调用内置的箭头运算符。执行相当于` (*(obj.operator->()).data`;
  - 如果返回是一个重载了箭头运算符的对象，则继续对该对象调用其重载了的箭头运算符，直到返回的是一个指针，将对该指针调用a)的操作。操作相当于

` (*(obj.operator->().operator->())).data`;

- 总的来说重载的箭头运算符就是为了改变从哪个对象中获取成员

```cpp
//->操作符重载
#include <iostream>
using namespace std;

class CData
{
public:
	int GetLen() {return 5;}
};

class CDataPtr
{
private:
	CData *m_pData;

public:
	CDataPtr()
	{
		m_pData = new CData;
	}

	~CDataPtr()
	{
		delete m_pData;
	}

	//->操作符重载
	CData * operator->()	 
	{
		cout << "->操作符重载函数被调用." << endl;
		return m_pData;
	}
};

int main()
{
	CDataPtr p;
	cout << p->GetLen() << endl;	//等价于下面1句:
	cout << (p.operator->())->GetLen() << endl;

	p.m_pData->GetLen();

	return 0;
}
```

