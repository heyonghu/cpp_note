#  1. 继承和派生

- 前面的内容主要围绕在面向对象编程的“抽象性”（如何将问题空间的事物抽象成类，这是个建模的过程）和“封装性”（保证数据的私密性，只提供供外部访问的接口），本章和随后一章来探讨“继承性”和“多态性”。继承的概念不难理解，多少有点“不劳而获”的意思，实际也是如此，面向对象程序设计的一个重要特点就是可以在既有类的基础上定义新的类，而不用将既有类的内容重新书写一遍，这称为“继承”（inheritance），既有类称为“基类”或“父类”，在它的基础上建立的类称为“派生类”或“子类”，在本章节的描述中，统一使用“基类”和“派生类”的概念。
- 继承是很自然的概念，广泛存在于现实世界中，如家族图谱，动植物分类图等。
- 对面向对象的程序设计(OOP)而言，继承的引入意义巨大：首先，程序员可以按现实世界、按自然的方式去思考和解决问题，组织信息，提高了效率，其次，可以复用基类的代码，并可以在派生类中增加新代码或者覆盖基类的成员函数，为基类成员函数赋予新的意义，实现最大限度的代码复用。
- MFC中广泛应用了单基继承。参见MSDN中的MFC继承结构图。 C#  COM组件

## 1.1 继承的定义

- 继承的定义形式一般如下：

```cpp
class 派生类 : 派生方式 基类 {…};  //public, protected, private
```

- 派生类生成过程包含3个步骤：

  - 吸收基类的成员

  - 改造基类的成员

  - 添加自己新的成员

- 见备注代码

- 通过例子来看什么是继承，如备注代码。

  示例代码中，point类是二维点类，三维点类point3D是从point类继承而来的，则point类称为“基类”、point3D类称为“派生类”。在point3D类内不用再对xPos和yPos进行定义性声明，只要增加一个private成员zPos即可，还可在point3D类内定义与point类某个成员函数同名的函数以实现功能覆盖，如point3D中的disp函数实现了point类中disp函数不同的功能。根据需要可再point3D类增加其他一些成员函数和数据成员，如calcSum函数。

```cpp
//继承与派生的概念 由point类 派生出 point3D类
#include <iostream>
using namespace std;

class point		//point类定义
{
private:		//private成员列表，表示点的坐标信息
	int xPos;
	int yPos;
	
public:
	point(int x = 0, int y = 0)	//构造函数，带缺省参数
	{
		xPos = x;
		yPos = y;
	}
	
	virtual void disp()		//成员disp函数，用来输出点的信息
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}
	
	int GetX()		//读取private成员xPos
	{
		return xPos;
	}
	
	int GetY()		//读取private成员yPos
	{
		return yPos;
	}
};

class point3D:public point	//3维点类point3D，从point类继承而来
{
private:
	int zPos;				//在point类基础上增加了zPos坐标信息
	
public:
	point3D(int x, int y, int z):point(x, y)//派生类构造函数，初始化表中调用基类构造函数
	{
		zPos = z;
	}
	
	void disp()				//隐藏了基类的中的同名disp函数
	{
		cout << "( " << GetX() << " , " << GetY() << " , " << zPos << " )" << endl;
	}
	
	int calcSum()			//增添了计算3个数据成员和的函数
	{
		return GetX() + GetY() + zPos;
	}
};

int main()
{
	point pt1(7, 8);			//建立point类对象pt1
	pt1.disp();					//显示pt1的信息

	point3D pt2(3, 4, 5);		//建立point3D类对象pt2
	pt2.disp();					//显示pt2的信息

	int res = pt2.calcSum();	//计算pt2中3个坐标信息的加和
	cout << res << endl;		//输出结果

	return 0;
}
```

## 1.2 继承的层次性

- 任何一个类都可以派生出新类，派生类还可以再派生出新的类，因此，基类和派生类是相对而言的。一个基类可以是另一个基类的派生类，这样便构建了层次性的类结构，如所示，类B是A的派生类，同时又派生了新类C，B又可以看作是C的基类。

![image-20220705221820612](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220705221820612.png)

## 1.3 继承的局限

- 不论何种继承方式，下面这些基类的特征是不能从基类继承下来的：

  - 构造函数

  - 析构函数

  - 用户重载的new 、delete运算符

```cpp
operator new /operator delete 
```

- 用户重载的=运算符

- 友元关系(单向性，不具备传递性)

## 1.4 派生方式

- 派生有public、protected、private三种方式，不同的派生方式下，派生类对基类成员的访问权限以及外部对基类成员的访问权限有所不同，本节详细讨论不同的派生方式。
- 默认是私有继承。

### 1.4.1 public派生与private派生

- C++中，利用基类派生其子类（派生类）的基本格式为：

```cpp
class 派生类名：派生方式 基类名
{
private:
 新增私有成员列表;
public:
 新增公开成员列表;
};参见备注代码
```

![image-20220705222122072](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220705222122072.png)

```cpp
//public, protected, private派生方式
#include <iostream>
using namespace std;

class point		//point类定义
{
private:		//private成员列表，表示点的坐标信息
	int xPos;
	int yPos;
	
public:
	point(int x = 0, int y = 0)	//构造函数，带缺省参数
	{
		xPos = x;
		yPos = y;
	}
	
	void disp()		//成员disp函数，用来输出点的信息
	{
		cout << "( " << xPos << " , " << yPos << " )" << endl;
	}
	
	int GetX()		//读取private成员xPos
	{
		return xPos;
	}
	
	int GetY()		//读取private成员yPos
	{
		return yPos;
	}
};

class point3D : public point	//3维点类point3D，从point类继承而来，注意格式
{
private:
	int zPos;				//在point类基础上增加了zPos坐标信息

public:
	point3D(int x, int y, int z):point(x, y)//派生类构造函数，初始化表中调用基类构造函数
	{
		zPos = z;
	}
	
	void disp()				//隐藏了基类的中的同名disp函数
	{
		cout << "( " << GetX() << " , " << GetY() << " , " << zPos << " )" << endl;
	}
	
	int calcSum()	//增添了计算3个数据成员和的函数
	{
		return GetX() + GetY() + zPos;
	}
};

int main()
{
	//自己动手, 分别使用public, protected和private派生point3D类,
	//则在public派生方式时下列访问派生类的GetX()不会出错,
	//但protected和private派生方式时就会编译报错.
	point3D pt(3, 4, 5);
	pt.GetX();		//!!!!!!

	//disp()在3种方式下都可访问, 因为disp()在Point3D类中被覆盖成public类型了
	pt.disp();

	//calcSum()在3种方式下都可访问, 因为它是在Point3D类中新定义的public成员函数
	pt.calcSum();

	return 0;
}
```

### 1.4.2 派生类访问权限

- 通过继承，派生类自动得到了除基类私有成员以外的其它所有数据成员和成员函数，在派生类中可以直接访问。

- private成员是私有成员，只能被本类的成员函数所访问，派生类和类外都不能访问。

- public成员是公有成员，在本类、派生类和外部都可访问

- protected成员是保护成员，只能在本类和派生类中访问。是一种区分血缘关系内外有别的成员。

- 派生类的访问权限规则如下：

  - 1．不管是什么继承方式，子类中都不能访问父类的私有成员。

  - 2．子类内部除了父类的私有成员不可以访问外，其他的都可以访问。

  - 3．除了公有继承基类中的公有成员，子类对象可以访问外，其他的,子类对象一律不能访问 。

```cpp
//不同继承方式，访问权限的问题
#include <iostream>
using namespace std;

class CA
{
private:
	int x;
protected:
	int y;
public:
	int z;
};

class CB : private CA	//protected  private
{
public:
	void fun()
	{
		z = 7;
		y = 3;
//		x = 4;
		cout << z << endl;
	}
};

int main()
{
	CB b;
//	b.z = 10;
//	b.y = 3;
//	b.x  = 4;
	return 0;
}

//总结如下:
//1. public继承方式的时候，在子类中不能访问基类的私有成员，可以访问基类的公有成员和保护成员
//   定义的子类对象，不能访问基类的私有成员和保护成员，可以访问基类的公有成员
//2. protected继承方式的时候，在子类中不能访问基类的私有成员，可以访问基类的公有成员和保护成员
//   定义的子类对象，不能访问基类的任何成员
//3. private继承方式的时候，在子类中不能访问基类的私有成员，可以访问基类的公有成员和保护成员
//   定义的子类对象，不能访问基类的任何成员
```

### 1.4.3 多基派生

- 派生类只有一个基类时，称为单基派生，在实际运用中，我们经常需要派生类同时具有多个基类，这种方法称为多基派生或多重继承，下图所示是双基继承的示意，在实际应用中，还允许使用三基甚至是更多基继承。

![image-20220705222440733](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220705222440733.png)

#### 1.4.3.1多基派生的声明和定义

- 在C++中，声明和定义具有两个以上基类的派生类与声明单基派生类的形式类似，只需将要继承的多个基类用逗号分开即可，如

```cpp
class 派生类名:继承方式1 基类名1,继承方式2 基类名2,…,继承方式n 基类名n
{
private:
 新增私有成员列表;
public:
 新增公开成员列表;
};
```

- 例如，从A类和B类派生出C类的方式如下：

```cpp
class C : public A, public B
{
 //……
};见备注代码
```

```cpp
//多基派生的声明和定义
#include <iostream>
using namespace std;

class A				//类A的定义
{
public:
	void print()	//A中定义了print函数
	{
		cout << "Hello,this is A" << endl;
	}
};

class B				//类B的定义
{
public:
	void show()		//B中定义了show函数
	{
		cout << "Hello,this is B" << endl;
	}
};

class C : public A, public B	//类C由类A和类B共同派生而来
{	
public:
	void disp()
	{
		show();		//在类内部基类的成员函数
	}
};

int main()
{
	C c;
	c.print();		//在类外部 通过 派生类对象 访问 基类 成员
	c.disp();		//在类外部 访问 派生类对象 的新添加的成员
	return 0;
}
```

#### 1.4.3.2 多基派生的二义性问题

- 一般来说，在派生类中对基类成员的访问应当具有唯一性，但在多基继承时，如果多个基类中存在同名成员的情况，造成编译器无从判断具体要访问的哪个基类中的成员，则称为对基类成员访问的二义性问题，如备注代码。

```cpp
//多基类继承时的二义性问题
#include <iostream>
using namespace std;

class A				//类A的定义
{
public:
	void print()	//A中定义了print函数
	{
		cout<<"Hello,this is A"<<endl;
	}
};

class B				//类B的定义
{
public:
	void print()	//B中同样定义了print函数
	{
		cout<<"Hello,this is B"<<endl;
	}
};

class C : public A, public B	//类C由类A和类B共同派生而来
{
public:
	void disp()
	{
		print();	//编译器无法决定采用A类中定义的版本还是B类中的版本
	}
};

int main()
{
	C c;
	c.disp();		//派生类内访问对象成员的二义性
	c.print();		//外部通过派生类对象访问基类成员的二义性
	return 0;
}
```

### 1.4.4 共同基类(虚基类)

- 多基派生中，如果在多条继承路径上有一个共同的基类，如图10.4所示，不难看出，在D类对象中，会有来自两条不同路径的共同基类（类A）的双重拷贝。

![image-20220705222906194](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220705222906194.png)

#### 1.4.4.1 共同基类的二义性

- 共同基类和多基派生的共同作用，使得在派生类中会出现多个共同基类的拷贝，这很容易带来二义性问题，如备注代码

- 如下图所示，D类通过B类和C类各继承了一次A类的函数SetX()和Print()，从而产生了二份拷贝，进而导致了二义性。

![image-20220705222955070](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220705222955070.png)

```cpp
//10-3 共同基类带来的二义性
#include <iostream>
using namespace std;

class A			//公共基类
{
protected:		//protected成员列表
	int x;

public:			//public成员列表
	A(int xp = 0)	//构造函数
	{
		x = xp;
	}

	void SetX(int xp)	//设置protected成员x的值
	{
		x = xp;
	}

	void print()
	{
		cout << "this is x in A: " << x << endl;
	}
};

//class B: virtual public A
class B: public A		//类B由类A派生而来
{
};

//class C: virtual public A	//类C由类A派生而来
class C: public A		//类C由类A派生而来
{
};

class D : public B, public C	//类D由类B和类C派生而来
{
};

int main()
{
	D d;		//声明一个D类对象exD
	d.SetX(5);	//SetX()具有二义性, 系统不知道是调用B类的还是C类的SetX()函数
	d.print();		//print()具有二义性, 系统不知道是调用B类的还是C类的print()函数
	return 0;
}
```

#### 1.4.4.2 共同基类二义性问题的解决方案

- 使用关键字virtual将共同基类A声明为虚基类，可有效解决上述问题。在定义由共同基类直接派生的类（类B和类C）时，使用下列格式定义：

```cpp
class 派生类名 : virtual 派生方式 基类名
{
 //类定义
};
见备注代码
```

![image-20220705223111564](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220705223111564.png)

```cpp
//使用虚基类解决共同基类带来的二义性问题
#include <iostream>
using namespace std;

class A		//公共虚基类A
{
protected:		//protected成员列表
	int x;

public:
	A(int xp = 0)	//构造函数，带缺省构造参数
	{
		x=xp;
	}

	void SetX(int xp)        //SetX函数用以设置protected成员x
	{
		x = xp;
	}

	void print()	//print函数输出信息
	{
		cout << "this is x in A: " << x << endl;
	}
};

class B: virtual public A	//B由A虚基派生而来
{
};

class C: virtual public A	//C由A虚基派生而来
{
};

class D:public B,public C	//D由B和C共同派生
{
};

int main()
{
	D d;		//声明一个D类对象exD

	d.SetX(5);		//SetX函数，因为virtual派生，在D中只有一个版本，不会二义
	d.print();		//print函数，因为virtual派生，在D中只有一个版本，不会二义

	d.A::print();	//还可用类名显式说明调用函数的版本
	d.B::print();
	d.C::print();

	return 0;
}
```

#### 1.4.4.3 虚基派生二义性与多基派生二义性不同

- 尽管看起来很相似，但虚基派生和多基派生带来的二义性有些细微的差别：

  - 多基派生的二义性主要是成员名的二义性，通过加作用域限定符来解决。

  - 虚基派生的二义性则是共同基类成员的多重拷贝带来的存储二义性，使用virtual派生来解决。

● 另外，二义性的检查是在访问权限检查之前进行的，因此，成员的访问权限是不能消除二义性的

### 1.4.5 单基派生类的构造函数和析构函数

- 派生时，构造函数和析构函数是不能继承的，为了对基类成员进行初始化，必须对派生类重新定义构造函数和析构函数，并在构造函数的初始化列表中调用基类的构造函数。

- 由于派生类对象通过继承而包含了基类数据成员，因此，创建派生类对象时，系统首先通过派生类的构造函数来调用基类的构造函数，完成基类成员的初始化，而后对派生类中新增的成员进行初始化。

  - 1、如果派生类有显式定义构造函数，而基类没有，则创建派生类的对象时，派生类相应的构造函数会被自动调用，此时都自动调用了基类缺省的无参构造函数。如例1：

  - 2、如果派生类没有显式定义构造函数而基类有，则基类必须拥有默认构造函数。如例2:
  - 3、如果派生类有构造函数，基类有默认构造函数，则创建派生类的对象时，基类的默认构造函数会自动调用，如果你想调用基类的有参构造函数，必须要在派生类构造函数的初始化列表中显示调用基类的有参构造函数。 如例3：
  - 4、如果派生类和基类都有构造函数，但基类没有默认的无参构造函数，即基类的构造函数均带有参数，则派生类的每一个构造函数必须在其初始化列表中显示的去调用基类的某个带参的构造函数。如果派生类的初始化列表中没有显示调用则会出错，因为基类中没有默认的构造函数。如例4：

```cpp
//例1
#include <iostream>
using namespace std;
class Baseclass
{
private :
		int a;
public:
//Baseclass()//用于检测基类的缺省的无参构造函数是否被自动调用
//		{
//			cout<<"default base"<<endl;
//		}
};
class Derivedclass : public Baseclass
{
public:
		Derivedclass()
		{
			cout<<"default"<<endl;
		}
		Derivedclass(int i)
		{
			cout<<"constructing"<<endl;
		}
};
int main()
{
		Derivedclass x1(5);
		Derivedclass x2;
		return 0;
}

//例2
#include <iostream>
using namespace std;
class Baseclass
{
private :
		int a;
public:
		Baseclass()//必须有
		{
			cout<<"default base"<<endl;
		}
		Baseclass(int i)//此时有参的构造函数没有任何作用
		{
			cout<<"constructing base"<<endl;
		}
};
class Derivedclass : public Baseclass
{
};
int main()
{
		Derivedclass x1;
		return 0;
}

//例3
#include <iostream>
using namespace std;
class Baseclass
{
private :
		int a;
public:
		Baseclass()		//用于检测基类的是否被自动调用
		{
			cout<<"default base"<<endl;
		}
		Baseclass(int i)
		{
			cout<<"constructing base"<<endl;
		}
};
class Derivedclass : public Baseclass
{
public:
		Derivedclass(int i)  //自动调用基类的默认构造函数
		{
			cout<<"default derived"<<endl;
		}
		Derivedclass(int i,int j):Baseclass(j)  //此时显示调用基类有参构造函数
		{
			cout<<"constructing derived"<<endl;
		}
};
int main()
{
		Derivedclass x1(5,7);
		Derivedclass x2(5);	
		return 0;
}

//例4
 #include <iostream>
using namespace std;
class Baseclass
{
private :
			int a;
public:
		Baseclass(int i)
		{
			cout<<"constructing base"<<endl;
		}
};
class Derivedclass : public Baseclass
{
public:
		Derivedclass(int i):Baseclass(i)  //自动调用基类的默认构造函数
		{
			cout<<"default derived"<<endl;
		}
		Derivedclass(int i,int j):Baseclass(j)  //此时显示调用基类有参构造函数
		{
			cout<<"constructing derived"<<endl;
		}
};
int main()
{
		Derivedclass x1(5,7);
		Derivedclass x2(5);
		return 0;
}

```

#### 1.4.5.1 单基派生类的构造函数

- 派生类构造函数的一般格式为：

```cpp
派生类名(总参数表): 基类构造函数(参数表)
{
 //函数体
};
```

- 必须将基类的构造函数放在派生类的初始化表达式中，以调用基类构造函数完成基类数据成员的初始化，派生类构造函数实现的功能，或者说调用顺序为：
  - 完成对象所占整块内存的开辟，由系统在调用构造函数时自动完成。
  - 调用基类的构造函数完成基类成员的初始化。
  - 若派生类中含对象成员、const成员或引用成员，则必须在初始化表中完成其初始化。
  -  派生类构造函数体执行。

- 见备注代码

```cpp
//派生类构造函数的调用顺序
#include <iostream>
using namespace std;

class A					//类A的定义
{
private:				//private成员列表
	int x;

public:
	A(int xp=0)			//构造函数，带缺省参数
	{
		x = xp;
		cout << "A的构造函数被执行" << endl;
	}
};

class B					//类B定义
{
public:
	B()					//无参构造函数
	{
		cout << "B的构造函数被执行" << endl;
	}
};

class C:public A		//类C由类A派生而来
{
private:
	int y;
	B b;

public:
	C(int xp, int yp) : A(xp), b()	//构造函数，基类构造函数在初始化表中调用
	{
		y = yp;
		cout << "C的构造函数被执行" << endl;
	}
};

int main()
{
	C c(1, 2);			//创建C类对象c
	return 0;
}

```

#### 1.4.5.2 单基派生类的析构函数

- 当对象被删除时，派生类的析构函数被执行。析构函数同样不能继承，因此，在执行派生类析构函数时，基类析构函数会被自动调用(与虚函数)。

- 执行顺序是先执行派生类的析构函数，再执行基类的析构函数，这和执行构造函数时的顺序正好相反

```cpp
//派生类的析构函数
#include <iostream>
using namespace std;

class A					//A类的定义
{
private:				//private成员列表
	int x;	
public:					//public成员列表
	A(int xp = 0)		//构造函数，带缺省参数
	{
		x = xp;
		cout << "A的构造函数被执行" << endl;
	}
	~A()				//析构函数
	{
		cout << "A的析构函数被执行" << endl;
	}
};

class B					//B类的定义
{
public:					//public成员列表
	B()					//无参构造函数
	{
		cout << "B的构造函数被执行" << endl;
	}
	~B()				//析构函数
	{
		cout << "B的析构函数被执行" << endl;
	}
};

class C:public A		//类C由类A派生而来
{
private:
	int y;	
	B b;				//对象成员

public:
	C(int xp, int yp):A(xp), b()	//派生类的构造函数，基类和对象成员都在初始化表中完成初始化
	{
		y = yp;
		cout << "C的构造函数被执行" << endl;
	}

	~C()				//析构函数
	{
		cout << "C的析构函数被执行" << endl;
	}
};

int main()
{
	C c(1, 2);			//声明一个C类对象c
	return 0;			//main函数执行完毕，c撤销，析构函数触发执行
}
```

### 1.4.6 多基派生类的构造函数和析构函数

- 多基派生时，派生类的构造函数格式如（假设有N个基类）：

```cpp
派生类名(总参数表)：基类名1(参数表1)，基类名2(参数表2)，……，基类名N(参数表N)
{
 //函数体
}
```

- 和前面所讲的单基派生类似，总参数表中包含了后面各个基类构造函数需要的参数。

- 多基派生和单基派生构造函数完成的任务和执行顺序并没有本质不同，唯一一点区别在于首先要执行所有基类的构造函数，再执行派生类构造函数中初始化表达式的其他内容和构造函数体，各基类构造函数的执行顺序与其在初始化表中的顺序无关，而是由定义派生类时指定的基类顺序决定的。

- 析构函数的执行顺序同样是与构造函数的执行顺序相反。

### 1.4.7 有继承关系的构造析构调用总结

- 1、如果派生类还包括成员对象，则对成员对象的构造函数的调用，仍然在初始化列表中进行，此时，当创建派生类的一个对象时，首先基类构造函数被调用，成员对象所在类构造函数次之（在有多个成员对象的情况下，成员对象的调用顺序取决于他们在派生类中的申明顺序，与初始化列表中的顺序无关），最后执行派生类构造函数的函数体。

- 2、如果是多继承，在调用基类构造函数的时候，处于同一层次的各基类构造函数的调用顺序取决于定义派生类时所指定的继承基类顺序，与派生类构造函数中所定义的初始化列表顺序无关。

- 3、如果派生类有一个虚基类作为祖先类，那么**在派生类构造函数的初始化列表中需要列出对虚基类构造函数的调用**，如果未列出则表明调用的是虚基类的无参构造函数，不管初始化列表中次序如何，对虚基类构造函数的调用总是先于普通基类的构造函数。

- 4、继承机制下析构函数的调用顺序：

  - 先调用派生类的析构函数

  - 然后调用派生类中成员对象的析构函数

  - 再调用普通基类的析构函数

  - 最后调用虚基类的析构函数

### 1.4.8 派生类对基类成员的覆盖

- **oversee** **隐藏：****父子类，函数名称相同，

  不带**virtual**关键字的函数

- **override** **覆盖：****父子类，函数的名称、返回值** 

​         **类型、参数的类型个数都相同**

​         **有virtual关键字**

- **overload** **重载：****同一个类，函数名称相同****，****参**

​         **数不同（类型，顺序，个数）**

- 如果基类和派生类中存在同名的成员数据或者非虚的成员函数，那么派生类的成员数据和成员函数将隐藏基类的成员数据和成员函数，子类对象不能直接调用到基类的被隐藏的成员数据和成员函数，只能通过obj.CBase::Func(3);方式访问。而且与基类和派生类的访问属性无关（？）；与基类和派生类的函数间的参数和返回类型无关 

```cpp
#include <iostream>
using namespace std;
class CBase
{
protected:
	int m_i;
public:
	int Func(int i)
	{
		return m_i;
	}
};
class CDerived:public CBase
{
public:
	int m_i;				//隐藏基类的m_i;
	int Func()				//覆盖基类的Func
	{
		m_i=9;				//访问自身的成员
		CBase::m_i=22;		//通过作用域解析符访问基类的成员
		return m_i;
	}
};
void main()
{
	CDerived obj;
	obj.Func();
	//obj.Func(3);			//错误！基类的Func被覆盖
	obj.CBase::Func(3);		//正确，通过作用域解析符访问基类的成员
}

```

### 1.4.9 分清继承还是组合

- 面向对象设计的难点在于类的设计，而不是对象的创建，就像工业生产中图纸是关键，有了图纸，产品可以很容易地创建出来。在程序设计中，如何处理类派生和类组合一直是个很让人觉得折磨的问题。(object-oriented  object-based)

- 前面已提及继承的重要性，使得代码结构清晰，大大提高了程序的可复用性，因此，很多初学者容易犯的错误就是把继承当成灵丹妙药，不管三七二十一拿来继承一下再说，其实，在面向问题空间的对象组织方面，不只有继承，还有对象组合，更高阶的结构还有聚合等，但从C++的本质来看，本节讨论下继承和组合的关系。

### 1.4.10 继承不是万金油

- 如果两个类没有关联，仅仅是为了使一个类的功能更多而让其去继承另一个类，这种方法要不得，继承不是万金油，毫无疑义的继承就像乱拉亲戚，会让条理有序的关系变得一团糟。从逻辑上说，继承是一种a kind of的关系（AKO）或者说IS-A（“是一个”），汽车是车，因此，汽车类可以从普通的车类继承而来，轮子类就不能从汽车类继承来，轮子是汽车的一个部件，轮子可以作为汽车类的对象成员，这就是“组合”（compositioin A has B）。

 如图：

![image-20220705224339760](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220705224339760.png)

```cpp
class CWheels
{
};
class CEngineer
{
};
class CCar
{
private:
	CEngineer engineer;      //采用的是聚集
	CWheels wheel[4];
public:
	void run()
	{
	}
};
class CQQ : public Ccar      //采用的是继承
{
public:
	void run()
	{
	}
};
```

### 1.4.11 组合

- 软件复用：代码的重复

  - C语言中采用：函数 宏

  - C++中采用：继承 组合

- 某类以另一个类对象作数据成员，称为组合，在逻辑上，如果类A是类B的一部分（a part of）或者说HAS-A（“有一个”），不要从A类派生出类B，而应当采用组合的方式，《高质量C++编程指南》中“眼睛、鼻子、嘴巴、耳朵和头部”的范例很好地解释了组合的本质：眼睛、鼻子、嘴巴、耳朵分别是头部的一部分，头部并不是从眼睛、鼻子、嘴巴、耳朵继承来的。

- 见备注代码

```cpp
//组合还是继承？
#include <iostream>
using namespace std;

class Eye
{
public:
	void Look() {cout << "Eye.Look()." << endl;}
};

class Nose
{
public:
	void Smell() {cout << "Nose.Smell()." << endl;}
};

class Mouth
{
public:
	void Eat() {cout << "Mouth.Eat()." << endl;}
};

class Ear
{
public:
	void Listen() {cout << "Ear.Listen()." << endl;}
};

//组合方式：逻辑很清晰，后续扩展很方便。
class Head
{
private:
	Eye m_eye;
	Nose m_nose;
	Mouth m_mouth;
	Ear m_ear;

public:
	void Look()
	{
		m_eye.Look();
	}

	void Smell()
	{
		m_nose.Smell();
	}

	void Eat()
	{
		m_mouth.Eat();
	}

	void Listen()
	{
		m_ear.Listen();
	}
};

//继承方式，会给后续设计带来很多逻辑上的问题
class HeadX : public Eye, public Nose, public Mouth, public Ear
{
};

int main()
{
	Head h;
	h.Look();
	h.Smell();
	h.Eat();
	h.Listen();
	
	cout << endl;

	HeadX hx;
	hx.Look();
	hx.Smell();
	hx.Eat();
	hx.Listen();

	cout << endl;

	return 0;
}
```

### 1.4.12 基类与派生类对象间的相互转换

- “类型适应”是指两种类型之间的关系，说A类适应B类是指A类的对象能直接用于B类对象所能应用的场合，从这种意义上讲，派生类适应于基类，派生类的对象适应于基类对象，派生类对象的指针和引用也适应于基类对象的指针和引用。

  - 可以把派生类的对象赋值给基类的对象

  - 可以把派生类的对象赋值给基类的引用

  - 可以声明基类的指针指向派生类的对象 (向上转型)

- 也就是说如果函数的形参是基类对象或者基类对象的引用或者基类对象的指针类型，在进行函数调用时，相应的实参可以是派生类对象 

- 见备注代码

```cpp
//单基继承的类型适应
#include <iostream>
using namespace std;

class Point					//类Point定义
{
private:
	int x;
	int y;

public:
	Point(int xp = 0, int yp = 0)	//构造函数
	{
		x = xp;
		y = yp;
	}

	void DispPoint()		//成员函数DispPoint的定义
	{
		printf("Point (%d, %d)\n", x, y);
	}

	int GetX()				//成员函数用以读取private成员x的值
	{
		return x;
	}

	int GetY()				//成员函数用以读取private成员y的值
	{
		return y;
	}
};

class Point3D:public Point	//类Point3D由类Point派生而来
{
private:					//在基类Point的基础上增加的数据成员	
	int z;

public:
	Point3D(int xp = 1, int yp = 1, int zp = 1):Point(xp, yp)	//构造函数，在初始化表中调用基类的构造函数
	{
		z = zp;
	}

	void Disp3DPoint()		//成员函数Disp3DPoint
	{
		printf("Point3D (%d, %d, %d)\n", GetX(), GetY(), z);
	}
};

int main()					//主函数
{
	Point pt1(1, 1);		//声明一个Point类对象pt1
	pt1.DispPoint();		//通过pt1调用DispPoint函数

	Point3D pt2(2, 3, 4);	//声明一个派生类对象pt2
	pt2.Disp3DPoint();		//通过pt2调用Disp3DPoint函数

	pt1 = pt2;				//派生类对象为基类对象赋值
	pt1.DispPoint();

	Point& rpt1 = pt2;		//派生类对象初始化基类对象引用
	rpt1.DispPoint();

	Point* ppt1 = &pt2;		//派生类对象地址为基类指针赋值
	ppt1->DispPoint();
	return 0;
}
```

#### 1.4.12.1 派生类与派生类对象间的相互转换

- 1. 如果用户定义了基类的拷贝构造函数，而没有定义派生类的拷贝构造函数，那么在用一个派生类对象初始化新的派生类对象时，两对象间的派生类部分执行缺省的行为，而两对象间的基类部分执行用户定义的基类拷贝构造函数。

- 2. 如果用户重载了基类的对象赋值运算符=，而没有定义派生类的对象赋值运算符，那么在用一个派生类对象给另一个已经存在的派生类对象赋值时，两对象间的派生类部分执行缺省的赋值行为，而两对象间的基类部分执行用户定义的重载赋值函数
- 3. 如果用户定义了派生类的拷贝构造函数或者重载了派生类的对象赋值运算符=，则在用已有派生类对象初始化新的派生类对象时，或者在派生类对象间赋值时，将会执行用户定义的派生类的拷贝构造函数或者重载赋值函数，而**不会再自动调用基类的拷贝构造函数和基类的重载对象赋值运算符**，这时，通常需要用户在派生类的拷贝构造函数或者派生类的赋值函数中**显式调用**基类的拷贝构造或赋值运算符函数。

```cpp
//example1:
class CBase
{
protected:
	char *m_pszData;
public:
	CBase(const char *pszData)                          //1
	{
		m_pszData=new char[strlen(pszData)+1];
		strcpy(m_pszData,pszData);
	}
	CBase(const CBase &base)                            //3
	{
		m_pszData=new char[strlen(base.m_pszData)+1];
		strcpy(m_pszData,base.m_pszData);
	}
	CBase &operator =(const CBase &base)                //4
	{ 
		if(this==&base)
			return *this;
		delete []this->m_pszData;
		m_pszData=new char[strlen(base.m_pszData)+1];
		strcpy(m_pszData,base.m_pszData);
		return *this;
	}
	~CBase(){delete []m_pszData;}
};
class CDerived:public CBase
{
public:
	CDerived(const char *pszData):CBase(pszData){}      //2
};
void main()
{
	CDerived d1("Hello!");
	CDerived d2=d1; 	//派生类使用缺省的拷贝构造函数、基类调用用户定义的拷贝构造函数
	d1=d2; 		//派生类使用缺省的赋值操作，基类调用用户重载的赋值运算符
}

```

```cpp
//example2:
#include <iostream>
using namespace std;
class CBase
{
protected:
	char *m_pszData1;
public:
	CBase()
	{
		this->m_pszData1 = new char[1];
		*(this->m_pszData1) = '\0';
		cout<<"A_1"<<endl;
	}
	CBase(const char *pszData)
	{
		m_pszData1=new char[strlen(pszData)+1];
		strcpy(m_pszData1,pszData);
		cout<<"B_1"<<endl;
	}
	CBase(const CBase &base)
	{
		m_pszData1=new char[strlen(base.m_pszData1)+1];
		strcpy(m_pszData1,base.m_pszData1);
		cout<<"C_1"<<endl;
	}
	CBase &operator =(const CBase &base)
	{
		if(this==&base)
			return *this;
		delete []this->m_pszData1;
		m_pszData1=new char[strlen(base.m_pszData1)+1];
		strcpy(m_pszData1,base.m_pszData1);
		cout<<"D_1"<<endl;
		return *this;
	}
	~CBase(){delete []m_pszData1;}
};
class CDerived:public CBase
{
private:
	char *m_pszData2;
public:
	CDerived()
	{
		cout<<"A_2"<<endl;
	}
	CDerived(const char *pszData1,const char *pszData2):CBase(pszData1)
	{
		m_pszData2=new char[strlen(pszData2)+1];
		strcpy(m_pszData2,pszData2);
		cout<<"B_2"<<endl;
	}
	CDerived(const CDerived &derived)
		//: CBase(derived)  显式调用
	{
		m_pszData2=new char[strlen(derived.m_pszData2)+1];
		strcpy(m_pszData2,derived.m_pszData2);
		cout<<"C_2"<<endl;
	}
	CDerived &operator = (const CDerived &derived)
	{
		if(this == &derived)
			return *this;
		//Base::operator=(derived); 显式调用
		m_pszData2 = new char[strlen(derived.m_pszData2)+1];
		strcpy(m_pszData2,derived.m_pszData2);
		cout<<"D_2"<<endl;
		return *this;
	}
	~CDerived(){delete []m_pszData2;}
};
void main()
{
	CDerived d1("Hello!","World!");
	CDerived d2=d1; 	// 派生类调用用户自定义的拷贝构造函数、基类不调用拷贝构造函数
	d1=d2; 		// 派生类调用用户自定义的赋值操作，基类不调用重载的赋值运算符
}

```

## 1.5 继承与静态成员

- 如果基类定义了一个静态成员，则在整个继承体系中只存在该成员的唯一定义；
- 无论基类派生出多少个派生类，对于每个静态成员来说都只存在唯一实例；
- 静态成员遵循通用的访问控制规则，如果基类中的成员是private的，则派生类无权访问它；
- 假设某静态成员是可访问的，则我们既能通过基类访问它，也能通过派生类使用它；

## 1.6 防止继承发生

C++11提供关键字final；

```cpp
class c1 final{}; c1类不能作为基类
```

## 1.7 final和override 说明符

- override说明派生类中的虚函数，表示覆盖了基类的虚函数；
- final如果某成员函数被定义为final，则之后的所有想覆盖该函数的操作都将引起错误；

# 2. 多态

- 多态性是面向对象设计语言的基本特征之一。仅仅是将数据和函数捆绑在一起，进行类的封装，使用一些简单的继承，还不能算是真正应用了面向对象的设计思想。多态性是面向对象的精髓。多态性可以简单地概括为“一个接口，多种方法”，前面讲过的函数重载就是一种简单的多态，一个函数名（调用接口）对应着几个不同的函数原型（方法）。

- 警车鸣笛，普通人反应一般，逃犯听见会大惊失色。警车鸣笛（同一种行为），导致普通人和逃犯不同反应(多种形态)。

- 再如，指令“画出昆虫的图片”，对蚂蚁和对蜘蛛这2种昆虫画出的是不同的图片。

- 通常是指对于同一个消息、同一种调用，在不同的场合，不同的情况下，执行不同的行为 

- 更通俗地说，**多态性是指同一个操作作用于不同的对象就会产生不同的响应**；多态性分为静态多态性和动态多态性，其中函数重载和运算符重载属于静态多态性, 虚函数属于动态多态性。函数重载和运算符重载在前面已经讲过，虚函数是本章的重点，C++是依靠虚函数来实现动态多态的。在进一步讲述多态前，先来看几个概念。

```cpp
设计多态的主要目的是：定义好一个祖先类，并定义一些虚函数（接口），但在这个接口函数中并不给出具体的实现，或者只是一些简单的实现，这个工作留给后代去具体实现。

class CWorm
{
public:
	virtual void Draw()
	{
		cout<<"CWorm::Draw()"<<endl;
	}
	virtual void Draw1()
	{
		cout<<"CWorm::Draw1()"<<endl;
	}
};
class CAnt:public CWorm
{
public:
	void Draw()
	{
		cout<<"CAnt::Draw()"<<endl;
	}
};
class CSpider:public CWorm
{
public:
	void Draw()
	{
		cout<<"CSpider::Draw()"<<endl;
	}
};
void display(CWorm* p)	//display函数，以base指针为参数
{
	p->Draw();
}
void main()
{
	CWorm *pWorm;
	CAnt ant;
	CSpider spider;
	pWorm=&ant;
	pWorm->Draw();
	pWorm=&spider;
	pWorm->Draw();
}
```



## 2.1 静态联编(静态绑定)

- 程序调用函数时，具体应使用哪个代码块是由编译器决定的。以函数重载为例，C++编译器根据传递给函数的参数和函数名决定具体要使用哪一个函数，称为联编（binding）。

- 编译器可以在编译过程中完成这种联编，在编译过程中进行的联编叫静态联编（static binding）或早期联编（early binding）。

## 2.2 动态联编

- 在一些场合下，编译器无法在编译过程中完成联编，必须在程序运行时完成选择，因此编译器必须提供这么一套称为“动态联编”（dynamic binding）的机制，也叫晚期联编（late binding），C++通过虚函数来实现动态联编。

## 2.3 虚函数

### 2.3.1 虚函数的声明和定义

- 虚函数的定义很简单，只要在成员函数原型前加一个关键字virtual即可。

- 如果一个基类的成员函数定义为虚函数，那么，它在所有派生类中也保持为虚函数；即使在派生类中省略了virtual关键字，也仍然是虚函数。

- 派生类要对虚函数进行中可根据需重定义，重定义的格式有一定的要求：

  - 与基类的虚函数有相同的参数个数；

  - 与基类的虚函数有相同的参数类型；

  - 与基类的虚函数有相同的返回类型。

- 若虚函数名称相同，参数不同，具体情况见备注

```cpp
构造函数为什么不能为虚函数？
class A
{
	A() { }	
};
class B : public A
{
	B():A() { }
};

Main()
{
 B b;
 B*pb = &b;
}

构造B类的对象时，
1. 根据继承的性质，构造函数执行顺序是：
A() B()
2. 根据虚函数的性质，如果A的构造函数为虚函数，
且B类也给出了构造函数，则应该只执行B类的构造函数，
不再执行A类的构造函数。这样A就不能构造了。
3. 这样1和2就发生了矛盾.

//Example1:
#include <iostream>
using namespace std;
class Base
{
public:
virtual int func(int x)
{
	cout<<"This is Base class";
	return x;
}
};
class Subclass: public Base
{
public:
virtual float func(int x)  
{
	cout<<"this is Sub class";
	float y = x;
	return y;
};
void test(Base& x)
{		cout<<"x="<<x.func(5)<<endl;
}
void main()
{
	Base bc;
	Subclass sc;
	test(bc);
	test(sc);
}


//Example2:
#include <iostream>
using namespace std;
class Base
{
public:
virtual int func(int x)
{
	cout<<"This is Base class";
	return x;
}
};
class Subclass: public Base
{
public:

//此处虚函数和基类的虚函数不是完全相同，既不构成覆盖，又不构成重载，但是可以编译成功。
//C++认为派生类中的虚函数是重定义函数，是隐藏的，失去了虚特性。在调用的工程中始终调用
//的是基类的虚函数。
virtual int func(float x)
{
	cout<<"this is Sub class";
	int y = (int)x;
	return y;
};
void test(Base& x)
{
	cout<<"x="<<x.func(5)<<endl;
}
int main()
{
	Base bc;
	Subclass sc;
	test(bc);
	test(sc);

	sc.func(5);
	Base &refbase = sc;
	refbase.func(5);
	return 0;
}
//讲解：对于派生类而言，基类的虚函数被派生类的虚函数隐藏了，如果用派生类的对象直接去调用则只存在派生类的虚函数。对于通过多态（基类指针或引用指向派生类之后）去调用虚函数，则始终是调用的基类的虚函数，此时派生类的虚函数被隐藏了。也就是说：相对基类而言，派生类的虚函数被隐藏，相对派生类而言，基类的虚函数被隐藏。只跟调用的对象有关，跟指向的内容没关。
```

### 2.3.2 为什么需要虚函数

- 结合一段示例示例代码来看一下虚函数的作用，以帮助大家理解多态的意义所在。

- 理解在下列基类函数前加和不加关键字virtual的不同：

```cpp
virtual void base::disp()
{
 cout<<"hello,base"<<endl;
}
```

- 通过指针访问disp()：

  - 1.不加virtual时，具体调用哪个版本的disp()只取决于指针本身的类型，和指针所指对象的类型无关。

  - 2.而加virtual时，具体调用哪个版本的`disp()`不再取决于指针本身的类型，而是取决于指针所指对象的类型。

```cpp
//为什么需要虚函数
#include <iostream>
using namespace std;

class base				//基类base定义
{
public:
//	virtual
	void disp()			//基类base中的普通成员函数disp
	{
		cout << "hello,base" << endl;
	}
};

class child1:public base//派生类child1从base派生而来
{
public:
	void disp()			//派生类child1中定义的disp函数将base类中定义的disp函数隐藏
	{
		cout << "hello,child1" << endl;
	}
};

class child2:public base//派生类child2从base派生而来
{
public:
	void disp()			//派生类child2中定义的disp函数同样会隐藏base类中定义的disp函数
	{
		cout << "hello,child2" << endl;
	}	
};

void display(base* pb)	//display函数，以base指针为参数
{
	pb->disp();
}

int main()
{
	base * pBase = NULL, obj_base;			//创建一个基类指针pBase，初始化为NULL,创建一base类对象obj_base
	obj_base.disp();			//通过对象名调用disp函数

	pBase = &obj_base;			//使用obj_base的地址为pBase赋值
	pBase->disp();				//通过指针调用disp函数

	child1 * pChild1 = NULL, obj_child1;	//创建一child1类指针pChild1，初始化为NULL,创建一child1类对象obj_child1
	obj_child1.disp();			//通过对象名调用disp函数

	pChild1 = &obj_child1;		//使用obj_child1的地址为pChild1赋值
	pChild1->disp();			//通过指针调用disp函数

	child2 * pChild2 = NULL, obj_child2;	//创建一child2类指针pChild2，初始化为NULL,创建一child2类对象obj_child2
	obj_child2.disp();			//通过对象名调用disp函数

	pChild2 = &obj_child2;		//使用obj_child2的地址为pChild2赋值
	pChild2->disp();			//通过指针调用disp函数

	cout << endl;

	//测试在void base::disp()函数前加和不加virtual时下列指针式输出的不同!!!!!!!!!!!!!!!!!!
	pBase = &obj_child1;		//使用obj_child1的地址为pBase赋值
	pBase->disp();				//通过指针pBase调用disp函数
	display(&obj_base);			//函数调用
	display(&obj_child1);
	display(&obj_child2);

	cout << endl;

	//(*指针).disp()式的调用
	(*pBase).disp();

	return 0;
}
//总结：
//形成多态的条件：有继承关系并且派生类中对基类的virtual函数现实了覆盖，利用基类的引用或指针指向派生类对象，再用基类的对象去调用virtual函数的时候会实现多态

```

### 2.3.3 虚函数的访问

- 对虚函数的访问方式不同，程序具体调用哪个函数可能也会有所不同，为了方便说明，本节统一采用如下类层次：

```cpp
#include <iostream>

using namespace std;

class base //基类定义
{
public:
    virtual void disp() //虚函数
    {
        cout << "hello, base" << endl;
    }
};

class child : public base//派生类定义
{
public:
    void disp() //虚函数的覆盖(对普通函数来说，是隐藏)
    {
        cout << "hello, child" << endl;
    }
};
```

```cpp
//虚函数的访问
#include <iostream>
using namespace std;

class base					//基类定义
{
public:
    virtual void disp()		//虚函数
    {
        cout << "hello, base" << endl;
    }
};

class child : public base	//派生类定义
{
public:
    void disp()	//虚函数的覆盖(对普通函数来说，是隐藏)
    {
        cout << "hello, child" << endl;
    }
};

int main()
{
    return 0;
}
//如果父类没有virtual关键字，则此时对于子类对象而言，基类的disp是被子类的disp函数隐藏的，即使基类此时的
//disp函数带有参数，也不能直接用子类对象去访问父类的disp函数。此时必须使用子类对象.基类名::disp的形式访问

```

#### 2.3.3.1 对象名访问

- 和普通函数一样，虚函数一样可以通过对象名来调用，此时编译器采用的是静态联编。

- 通过对象名访问虚函数时, 调用哪个类的函数取决于定义对象名的类型。对象类型是基类时，就调用基类的函数；对象类型是子类时，就调用子类的函数。如：

```cpp
obj_base.disp(); //调用基类虚函数

obj_child.disp(); //调用子类虚函数

p在子类中还可以使用作用域运算符来指定调用哪个类的函数。如：

obj_child.base::disp(); //调用基类虚函数

obj_child.child::disp();//调用子类虚函数
```

- 见备注代码

```cpp
//通过对象名访问虚函数时, 调用哪个函数取决于对象名的类型
#include <iostream>
using namespace std;

class base
{
public:
	virtual void disp()
	{
		cout << "hello,base" << endl;
	}
};

class child:public base
{
public:
	void disp()
	{
		cout << "hello,child" << endl;
	}
};

int main()
{
	base obj_base;					//创建基类对象obj_base
	child obj_child;				//创建派生类对象obj_child

	obj_base.disp();				//通过对象名调用虚函数
	obj_child.disp();				//通过对象名调用虚函数

	obj_base = obj_child;
	obj_base.disp();

	obj_child.base::disp();			//通过类名加作用域限定符指明要调用的版本
	obj_child.child::disp();		//通过类名加作用域限定符指明要调用的版本

	return 0;
}
```

#### 2.3.3.2 指针访问

- 使用指针访问非虚函数时，编译器根据指针本身的类型决定要调用哪个函数，而不是根据指针指向的对象类型；
- 使用指针访问 虚函数时，编译器根据指针所指对象的类型决定要调用哪个函数(动态联编)，而与指针本身的类型无关。

- 使用指针访问是虚函数调用的最主要形式。

- 见备注代码

```cpp
//通过指针访问虚函数
#include <iostream>
using namespace std;

class base
{
public:
	virtual void disp()
	{
		cout << "hello,base" << endl;
	}
	void print()
	{
		cout << “base::print()” << std::endl;
	}
};

class child:public base
{
public:
	void disp()
	{
		cout << "hello,child" << endl;
	}
	void print()
	{
		cout << “child::print()”<< std::endl;
	}
};

int main()
{
	base obj_base;			//创建一个基类对象
	base* pBase = &obj_base;	//使用基类对象地址为基类指针赋值
	pBase->disp();			//使用基类指针调用虚函数

	child obj_child;		//创建一派生类对象
	child* pChild = &obj_child;//使用派生类对象地址为派生类指针赋值
	pChild->disp();			//使用派生类指针调用虚函数

	cout << endl;

	pBase = pChild;			//将派生类指针赋值给基类指针
	pBase->disp();			//使用基类指针调用虚函数

	pChild = (child *)&obj_base;//反向转换，使用基类对象地址为派生类指针赋值
	pChild->disp();		//使用派生类指针调用虚函数，只取决于赋值对象

	pChild->base::disp();	//使用类名加作用域限定符指明要调用的版本, 静态联编

	return 0;
}
```

#### 2.3.3.3 引用访问

- 使用引用访问虚函数，与使用指针访问虚函数类似

- 不同的是，引用一经声明后，引用变量本身无论如何改变，其调用的函数就不会再改变，始终指向其开始定义时的函数。因此在使用上有一定限制，但这在一定程度上提高了代码的安全性，特别体现在函数参数传递等场合中，可以将引用理解成一种“受限制的指针”

- 见备注代码

```cpp
//通过引用访问虚函数
#include <iostream>
using namespace std;

class base
{
public:
	virtual void disp()
	{
		cout << "hello,base" << endl;
	}
};

class child:public base
{
public:
	void disp()
	{
		cout << "hello,child" << endl;
	}
};

int main()
{
	base obj_base;				//创建基类对象
	base& rBase1 = obj_base;	//声明基类引用，用基类对象初始化
	rBase1.disp();				//基类引用 调用虚函数: 基类中的disp版本

	child obj_child;			//创建派生类对象
	base& rBase2 = obj_child;	//声明基类引用，用派生类对象初始化
	rBase2.disp();				//基类引用 调用虚函数: 派生类中的disp版本

	cout << endl;

	//引用一经声明后，其调用的函数就不会再改变
	rBase1 = obj_child; //引用本身不可以改变, 这里是将obj_child赋值给
		        //了rBase1指向的obj_base，相当于obj_base = obj_child;
	rBase1.disp();      //还是调用原来的虚函数: 基类版本

	rBase2 = obj_base;  //同上
	rBase2.disp();      //还是调用原来的虚函数: 派生类版本

	return 0;
}
```

#### 2.3.3.4 类成员函数中访问

- 在类内的成员函数中访问该类层次中的虚函数，采用动态联编，要使用this指针。见备注代码

```cpp
//在类内的成员函数中访问该类层次中的虚函数，要使用this指针
#include <iostream>
using namespace std;

class base		//基类定义
{
public:
	virtual void disp()	        //虚函数disp
	{
		cout<<"hello,base"<<endl;
	}

	void call_base_1()
	{
		this->disp();     //或直接用disp()
	}

	void call_base_2()
	{
		base::disp();     //去掉bass::再试试
	}
};

class child:public base	        //派生类定义
{
public:
	void disp()	        //对虚函数进行了覆盖定义
	{
		cout<<"hello,child"<<endl;
	}

	void call_child_1()
	{
		disp();	        //等价于this->disp();
	}

//	函数call_base_1()在child类中虽然没有直接写出来，
//	但还是继承过来了，默认和base类的代码是一样的
//	void call_base_1()
//	{
//		this->disp();
//	}

//	函数call_base_2()在child类中虽然没有直接写出来，
//	但还是继承过来了，默认和base类的代码是一样的
//	void call_base_2()
//	{
//		base::disp();
//	}
};

int main()
{
	base obj_Base;		//声明一个基类对象
	child obj_Child;		//声明一个派生类对象
	obj_Base.call_base_1();	//基类对象调用非虚函数call_base_1()
	obj_Chld.call_child_1();       //派生类对象调用非虚函数call_child_1()

	cout << endl;

	base* pBase = &obj_Base;     //声明一基类指针，并用基类对象地址为其初始化
	pBase->call_base_1();	//使用基类指针在成员函数内调用虚函数
	pBase->call_base_2();	

	cout << endl;

	pBase = &obj_Child;	//用派生类对象地址为基类指针初始化
	pBase->call_base_1();	//使用基类指针在成员函数内调用虚函数
	pBase->call_base_2();

	return 0;
}


```

#### 2.3.3.5 在构造函数或析构函数中访问

- 构造函数和析构函数是特殊的成员函数，在其中访问虚函数时，C++采用静态联编，即在构造函数或析构函数内，即使是使用“this->虚函数名”的形式来调用，编译器仍将其解释为静态联编的“本类名::虚函数名”。**即它们所调用的虚函数是自己类中定义的函数，如果在自己的类中没有实现该函数，则调用的是基类中的虚函数。但绝不会调用任何在派生类中重定义的虚函数。**

- 见备注代码

```cpp
#include <iostream>
using namespace std;
class Base0
{
public:
	Base0(){}	
	virtual void func1()
	{
		cout<<"this is base0 func1()"<<endl;
	}
	virtual void func2()
	{
		cout<<"this is base0 func2()"<<endl;
	}
	~Base0(){}
};
class Base1 : public Base0
{
public:
	Base1()
	{
		func1();
	}
//	virtual void func1()    //没有重写覆盖该虚函数，则调用父类Base0中的func1()方法
//	{
//		cout<<"this is base0 func1()"<<endl;
//	}
	virtual void func2()
	{
		cout<<"this is base1 func2()"<<endl;
	}
	~Base1()
	{
		func2();
	}
};
class Subclass : public Base1
{
public:
//	Subclass()
//	{
//		func1();
//	}
	virtual void func1()   //始终不会被调用
	{
		cout<<"this is subclass func1()"<<endl;
	}
	virtual void func2()   //始终不会被调用
	{
		cout<<"this is subclass func2()"<<endl;
	}
	~Subclass()
	{
	}
};
void main()
{
	Subclass sc;
}
结果为：this is base0 func1()
this is base1 func2()
//上面程序的分析：
继承方式为：   Subclass ----(继承)---- Base1----(继承)----Base0
(其中，Base0中有两个虚函数，func1(),func2();  Base1中只重写覆盖了父类Base0的func2(),其构造函数调用fun1()方法，类Subclass中重写覆盖了func1()和func2()方法。)
当实例化子类对象Subclass的sc时，调用默认构造函数，先调用父类Base1的构造函数，而该构造函数中调用了fun1()方法，因为在其自身的类中没有重写覆盖func1()方法，则调用父类Base0的func1()方法，输出this is base0 func1()。
当程序结束，对象sc要被释放时，调用默认的析构函数~Subclass()，自动调用父类Base1的析构函数，该析构函数中调用func2()方法，而Base1中重写覆盖了func2()方法，所以调用自己类中的func2()方法，输出this is base1 func2()。

```

### 2.3.4 虚函数表vftable

- 如果类中包含有虚成员函数，在用该类实例化对象时，对象的第一个成员将是一个指向虚函数表(`vftable`)的指针(`vfptr`)。虚函数表记录运行过程中实际应该调用的虚函数的入口地址。

- 跟踪执行代码，观察内存中的`vfptr`指向地址处函数名称的变化。

![image-20220706195453114](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220706195453114.png)

```cpp
//通过指针访问虚函数
#include <iostream>
using namespace std;

class base
{
public:
	virtual void disp()
	{
		cout << "hello,base" << endl;
	}
};

class child:public base
{
public:
	void disp()
	{
		cout << "hello,child" << endl;
	}
};

int main()
{
	base obj_base;			//创建一个基类对象
	base* pBase = &obj_base;	//使用基类对象地址为基类指针赋值
	pBase->disp();			//使用基类指针调用虚函数

	child obj_child;		//创建一派生类对象
	child* pChild = &obj_child;//使用派生类对象地址为派生类指针赋值
	pChild->disp();			//使用派生类指针调用虚函数

	cout << endl;

	pBase = pChild;			//将派生类指针赋值给基类指针
	pBase->disp();			//使用基类指针调用虚函数

	pChild = (child *)&obj_base;//反向转换，使用基类对象地址为派生类指针赋值
	pChild->disp();			//使用派生类指针调用虚函数，只取决于赋值对象

	pChild->base::disp();	//使用类名加作用域限定符指明要调用的版本, 静态联编

	return 0;
}
```

### 2.3.5 求包含虚函数的类的`sizeof`

- 包含有虚函数的类，在用`sizeof`求类对象所占用的内存空间的时候，因为此时对象有个指向虚函数表的指针，所以结果应该多四个字节，但是当同一个类中有多个虚函数的时候，也只有4个字节。当另一个类虚基继承时，又会多4个字节。如果派生类中又自己定义了新的虚函数，则又多4个字节。

```cpp
class A
{
    int i;
    void f(){}
    virtual void run(){}
    virtual void run1(){}
    virtual void run2(){}
};
class B : virtual public A
{
    virtual void run(){}
    virtual void run1(){}
};
其中 sizeof(A) = 8;(int i占4个字节，run()是virtual，会有一个指向虚函数表的指针，占4个字节，此时虽然run1和run2也都是virtual但是已经有一个虚函数表，则不再创建。所以为8)
sizeof(B) = 12;(继承来的int i占4个字节，虚继承，会创建虚表，占4个字节，run()是virtual，占4个字节，此时虽然run1也是virtual，但是已经存在虚函数表，则不在创建，所以为12)

class A
{
    int i;
    void f(){}
    virtual void run(){}
    virtual void run1(){}
    virtual void run2(){}
};
class B : virtual public A
{
    virtual void run(){}
    virtual void run1(){}
    virtual void run3(){}
};
其中 sizeof(A) = 8;(int i占4个字节，run()是virtual，会有一个指向虚函数表的指针，占4个字节，此时虽然run1和run2也都是virtual但是已经有一个虚函数表，则不再创建。所以为8)
sizeof(B) = 16;(继承来的int i占4个字节，虚继承，会创建虚表，占4个字节，run()和run1()都是基类已经存在的虚函数，此时覆盖基类虚函数，占4个字节，此时run3是新定义的virtual，则又多了4个字节，所以为16) 



```

## 2.4 纯虚函数与抽象类

- 当在基类中无法为虚函数提供任何有实际意义的定义时，可以将该虚函数声明为纯虚函数，它的实现留给该基类的派生类去做。

### 2.4.1 纯虚函数的声明和定义

- 纯虚函数是一种特殊的虚函数，其格式一般如下：

```cpp
class 类名 
{ 
	virtual 类型 函数名 (参数表)=0; 
	---
}; 
```

- 纯虚函数不能被直接调用，仅提供一个与派生类一致的接口。

- 见备注代码 

```cpp
//纯虚函数的申明和定义
#include <iostream> 
using namespace std;

class A						//类A定义
{
public:
	virtual void disp() = 0;//纯虚函数，类A作为抽象类
};

class B:public A			//B由抽象类A派生而来
{
public:
	virtual void disp()		//此处virtual可省略，继承
	{
		cout << "This is from B" << endl;
	}
};

class C: public B			//类C从类B派生而来
{
public:
	virtual void disp()
	{
		cout << "This is from C" << endl;
	}
};

void display(A *a)			//display函数，以A类指针对参数
{
	a->disp();
}

int main()
{
	B *pB = new B;				//正确。但如果删除B类中disp()的定义就会编译出错, 因为删除后，B就还包含纯虚函数。
	C *pC = new C;			//正确。如果删除C类中的disp()的定义，但保留B中的定义，依然正确，因为B中的disp()不是纯虚函数了
							//但如果B, C类中都没有disp()的定义，就会编译出错，因为C还是纯虚函数。

	display(pB);			//取决于为指针赋值的数据类型
	display(pC);

	return 0;
}
```

### 2.4.2 抽象类

- 一个类可以包含多个纯虚函数。只要类中含有一个纯虚函数，该类便为抽象类。一个抽象类只能作为基类来派生新类，不能创建抽象类的对象，如中的A类便是抽象类，创建A类的对象是非法的，如：

```cpp
A a; //错误：A为抽象类
```

- 但可声明一个指向抽象类的指针，如：

```cpp
A* a=NULL;

A* a=new B;
```

- 应注意：“A* a=new A;”非法，因为该语句试图创建A的对象。

```cpp
//抽象类
#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.1415926	//宏定义

class Figure		//图形基类定义
{
public:
	virtual float Area() =0;	//纯虚函数，因此Figure类是抽象类，无法声明其对象
	virtual void DispName() =0;	
};

class Circle:public Figure		//在抽象类Figure的基础上派生Circle圆类
{
private:				//private成员列表
	float radius;		//半径
public:
	Circle(float r = 0)		//构造函数
	{
		radius = r;
	}
	virtual void DispName()	//覆盖实现了虚函数DispName，此处virtual去掉没有影响
	{
		cout << "圆:" << endl;
 	}
	virtual float Area()		//覆盖实现了虚函数Area,用来计算圆的面积，
	{			//virtual去掉同样没有影响
	
		return PI * radius * radius;
	}
};

class Rectangle:public Figure		//在抽象类Figure的基础上派生Rectangle矩形类
{
private:
	float x;			//两个边长x和y
	float y;
public:
	Rectangle(float xp = 0, float yp = 0)//构造函数
	{
		x = xp;
		y = yp;
	}
	virtual void DispName()	//覆盖实现了虚函数DispName，此处virtual去掉没有影响
	{
		cout << "矩形:" << endl;
	}
	virtual float Area()		//覆盖实现了虚函数Area,用来计算矩形面积，
	{			//virtual去掉同样没有影响
	
		return x * y;
	}
};

class Triangle:public Figure	//在抽象类Figure的基础上派生Triangle三角形类
{
private:			//三角形的三个边长
	float x;
	float y;
	float z;
public:
	Triangle(float xp = 0, float yp = 0, float zp = 0)//构造函数
	{
		x = xp;
		y = yp;
		z = zp;
	}
	virtual void DispName()	//覆盖实现了虚函数DispName，此处virtual去掉没有影响
	{
		cout << "三角形:" << endl;
	}
	virtual float Area()		//覆盖实现了虚函数Area,用来计算三角形面积，
	{			//virtual去掉同样没有影响
	
		float p = (x + y + z) / 2;
		return sqrt(p * (p - x) * (p - y) * (p - z));
	}
};

int main()
{
//	Figure f;				//错误, 抽象类不能实例化
//	Figure *pF = new Figure();		//错误, 抽象类不能使用new分配内存空间
	Figure *pF = NULL;	//虽然不能创建Figure类对象，但可声明Figure型的指针
	
	Circle c(3);			//声明一个圆对象，半径为3。
	Rectangle r(1.2f, 3.6f);		//声明一个矩形对象，其边长分别为1.2和3.6
	Triangle t(6, 7, 8);			//声明一个三角形对象，其边长分别为6、7和8
	//上面3句正确，可以这样实例化，因为Circle, Rectangle和Triangle不再是抽象类了,
	//其基类的2个虚函数DispName()和Area()都已经有定义了。
	//如果删除其中任何一个定义, 就会编译出错。
	
	pF = &c;				//用圆对象c的地址为pF赋值
	pF->DispName();			//调用DispName时，对应着Circle类中的版本
	cout << pF->Area() << endl;		//调用Area时，对应着Circle类中的版本
	cout << endl;
	
	pF = &r;				//用矩形对象r的地址为pF赋值
	pF->DispName();			//调用DispName时，对应着Rectangle类中的版本
	cout << pF->Area() << endl;		//调用Area时，对应着Rectangle类中的版本
	cout << endl;
	
	pF = &t;				//用三角形对象t的地址为pF赋值
	pF->DispName();			//调用DispName时，对应着Triangle类中的版本
	cout << pF->Area() << endl;		//调用Area时，对应着Triangle类中的版本
	cout << endl;

	return 0;
}
```

- 和普通的虚函数不同，在派生类中一般要对基类中纯虚函数进行重定义，或者在派生类中再次将该虚函数声明为纯虚函数。这说明，抽象类的派生类也可以是抽象类，只有在派生类中给出了基类中所有纯虚函数的实现时，该派生类便不再是抽象类。和纯虚函数一样，抽象类只起到提供统一接口的作用。

- 见备注代码

```cpp
//抽象类
#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.1415926	//宏定义

class Figure		//图形基类定义
{
public:
	virtual float Area() =0;	//纯虚函数，因此Figure类是抽象类，无法声明其对象
	virtual void DispName() =0;
};

class Circle:public Figure		//在抽象类Figure的基础上派生Circle圆类
{
private:				//private成员列表
	float radius;		//半径
public:
	Circle(float r = 0)		//构造函数
	{
		radius = r;
	}
	virtual void DispName()	//覆盖实现了虚函数DispName，此处virtual去掉没有影响
	{
		cout << "圆:" << endl;
 	}
	virtual float Area()		//覆盖实现了虚函数Area,用来计算圆的面积，
	{			//virtual去掉同样没有影响
	
		return PI * radius * radius;
	}
};

class Rectangle:public Figure		//在抽象类Figure的基础上派生Rectangle矩形类
{
private:
	float x;			//两个边长x和y
	float y;
public:
	Rectangle(float xp = 0, float yp = 0)//构造函数
	{
		x = xp;
		y = yp;
	}
	virtual void DispName()	//覆盖实现了虚函数DispName，此处virtual去掉没有影响
	{
		cout << "矩形:" << endl;
	}
	virtual float Area()		//覆盖实现了虚函数Area,用来计算矩形面积，
	{			//virtual去掉同样没有影响
	
		return x * y;
	}
};

class Triangle:public Figure	//在抽象类Figure的基础上派生Triangle三角形类
{
private:			//三角形的三个边长
	float x;
	float y;
	float z;
public:
	Triangle(float xp = 0, float yp = 0, float zp = 0)//构造函数
	{
		x = xp;
		y = yp;
		z = zp;
	}
	virtual void DispName()	//覆盖实现了虚函数DispName，此处virtual去掉没有影响
	{
		cout << "三角形:" << endl;
	}
	virtual float Area()		//覆盖实现了虚函数Area,用来计算三角形面积，
	{			//virtual去掉同样没有影响
	
		float p = (x + y + z) / 2;
		return sqrt(p * (p - x) * (p - y) * (p - z));
	}
};

int main()
{
//	Figure f;				//错误, 抽象类不能实例化
//	Figure *pF = new Figure();		//错误, 抽象类不能使用new分配内存空间
	Figure *pF = NULL;	//虽然不能创建Figure类对象，但可声明Figure型的指针
	
	Circle c(3);			//声明一个圆对象，半径为3。
	Rectangle r(1.2f, 3.6f);		//声明一个矩形对象，其边长分别为1.2和3.6
	Triangle t(6, 7, 8);			//声明一个三角形对象，其边长分别为6、7和8
	//上面3句正确，可以这样实例化，因为Circle, Rectangle和Triangle不再是抽象类了,
	//其基类的2个虚函数DispName()和Area()都已经有定义了。
	//如果删除其中任何一个定义, 就会编译出错。
	
	pF = &c;				//用圆对象c的地址为pF赋值
	pF->DispName();			//调用DispName时，对应着Circle类中的版本
	cout << pF->Area() << endl;		//调用Area时，对应着Circle类中的版本
	cout << endl;
	
	pF = &r;				//用矩形对象r的地址为pF赋值
	pF->DispName();			//调用DispName时，对应着Rectangle类中的版本
	cout << pF->Area() << endl;		//调用Area时，对应着Rectangle类中的版本
	cout << endl;
	
	pF = &t;				//用三角形对象t的地址为pF赋值
	pF->DispName();			//调用DispName时，对应着Triangle类中的版本
	cout << pF->Area() << endl;		//调用Area时，对应着Triangle类中的版本
	cout << endl;

	return 0;
}
```

### 2.4.3 抽象类第二种形式

- 对一个类来说，如果只定义了protected型的构造函数而没有提供public构造函数，无论是在外部还是在派生类中作为其对象成员都不能创建该类的对象，但可以由其派生出新的类，这种能派生新类，却不能创建自己对象的类是另一种形式的抽象类，在示例代码中便定义了一个构造函数为protected型的类。

```cpp
//只定义了protected类型构造函数的类也是抽象类
#include <iostream>
using namespace std;

class Base			//基类定义
{
private:
	int x;

protected:
	Base(int xp = 0)		//构造函数声明为protected型
	{
		x = xp;
	}

public:
	void disp()
	{
		cout << "x is " << x << endl;
	}
};

class Child:public Base
{
public:
//	Base b;		//错误，在派生类中不能创建Base类对象
	Child(int xpp):Base(xpp)	//但派生类中可调用protected构造函数
	{
	}
};

int main()
{
//	Base b;		//错误，在外部不能创建Base类对象
	Child c(1);
	c.disp();
	return 0;
}
```

### 2.4.4 使用static成员函数为包含private构造函数的类创建对象

- 前面讲了构造函数可以为public型、也可以为protected型。其实，构造函数也可以是private型的。

- 此时，不能直接在外部函数和派生类中使用“类名+对象名”的形式来创建该类对象，但可以通过类的static函数成员来创建类的实例。

- 与此类似，也可以使用static成员函数为包含protected型构造函数的类创建对象

- 见备注代码

```cpp
//使用static成员函数为包含private构造函数的类创建对象
#include <iostream>
using namespace std;

class Example	//类定义
{ 
private:
	int x;
	Example(int xp)	//类的构造函数定义为private型
	{
		x = xp;
	}

public:
	static Example* CreateObject(int xp)//static函数，不用创建对象便可调用
	{
		return new Example(xp);	//申请动态内存
	} 

	static void DeleteObject(Example* pE)//static函数，不用创建对象便可调用
	{
		delete pE;	//释放申请到的内存资源
	}

	void disp()	//成员函数
	{
		cout << "x is " << x << endl;
	}
};

int main()
{
//	Example e;	//错误, Example的构造函数是private类型, 不能访问
//	Example *pe = new Example();
//错误, Example的构造函数是private类型, 不能new
	Example *ppe = NULL;	//正确

	//使用类名访问static函数创建对象，返回指向动态内存的指针
	Example * pE = Example::CreateObject(5);

	//功能访问
	pE->disp();
	
	//释放资源
	Example::DeleteObject(pE);
	
	return 0;
}

//单件设计模式
内存中只能有一份对象
//单件设计模式：类在内存中只能有1个实例
//实现步骤：
将构造函数私有化。
在类中定义一个静态的指针对象（可为私有，可为公有），并在类外初始化为空
定义一个返回值为类指针的静态成员函数，如果2中的指针对象为空，则初始化对象，以后再有对象调用该静态成员函数的时候，不再初始化对象，而是直接返回对象，保证类在内存中只有一个实例。
Example：
#include<iostream>
using namespace std;
class CA
{
private:
		static CA *pA;
		int x;
		int y;
		CA(int x = 0, int y = 0)
		{
			this->x = x;
			this->y = y;
			cout << "构造函数被调用" << this << endl;
		}	
public:
		static CA* GetInstance(int x = 0, int y = 0)
		{
			if(pA == NULL)
			{
				pA = new CA(x, y);
			}
			return pA;
		}
		void disp() const
		{
			cout << "(" << this->x << "," << this->y << ")" << endl;
		}
};
CA* CA::pA = NULL;//静态成员要在外面初始化
void main()
{
		CA *p1 = CA::GetInstance(3, 4);
		CA *p2 = CA::GetInstance(2, 1);
		CA *p3 = CA::GetInstance(6, 2);
		cout << p1 << endl;
		cout << p2 << endl;
		cout << p3 << endl;
		p1->disp();
		p2->disp();
		p3->disp();
}
//此时p1、p2、p3是同一个，输出来的值相等，所以调用disp都输出同样的内容

```

### 2.4.5 虚析构函数

- 虽然构造函数不能被定义成虚函数，但析构函数可以定义为虚函数，一般来说，如果类中定义了虚函数，析构函数也应被定义为虚析构函数，尤其是类内有申请的动态内存，需要清理和释放的时候。

- 备注代码example1的析构函数是非虚的，释放时会造成child类的析构函数得不到执行，从而内存泄漏。

- 改进代码见example2，这样base类和child类的析构函数都得到了执行，避免了内存泄漏。

```cpp
//example1 析构函数调用不当带来的内存泄漏
#include <iostream>
using namespace std;

class Base	//基类定义
{
private:		//字符指针
	char* data;

public:
	Base()	//无参构造函数
	{
		data = new char[64];	//动态内存申请
		cout<<"Base类构造函数被调用"<<endl;
	};

//	virtual
	~Base()		//析构函数
	{
		delete [] data;	//data指向的内存被释放
		cout<<"Base类析构函数被调用"<<endl;
	};
};

class Child : public Base	//Child类由基类Base派生而来
{
private:
	char* m_data;	//增添的字符指针成员

public:
	Child():Base()	//构造函数，初始化表中执行基类的构造函数
	{
		m_data = new char[64];//动态申请内存，并将首地址赋给m_data
		cout<<"Child类构造函数被调用"<<endl;
	};

	~Child()			//析构函数
	{
		delete [] m_data;	//内存资源释放
		cout<<"Child类析构函数被调用"<<endl;
	};
};

int main()
{
	Base *pB = new Child;//动态申请一块Child大小的内存，赋给Base基类指针
	delete pB;		//基类析构函数执行

	//执行结果为：
	// Base类构造函数被调用
	// Child类构造函数被调用
	// Base类析造函数被调用

	//Child类的析构函数没有被执行。这是因为上述代码的析构函数是非虚的，
	//而pB是Base *类型，因此析构时只执行Base类的析构函数, 而child类的
	//析构函数得不到执行，从而导致内存泄漏
//解决方法：将Base类的析构函数申明为虚函数即可. 即在 ~Base() 前面加上 virtual 

	return 0;
}



//example 2使用虚析构函数解决内存泄漏问题
#include <iostream>
using namespace std;

class Base					//基类定义
{
private:
	char* data;				//字符指针

public:
	Base()					//无参构造函数
	{
		data = new char[64];	//动态内存申请
		cout << "Base类构造函数被调用" << endl;
	};

	virtual ~Base()			//虚析构函数
	{
		delete [] data;		//data指向的内存被释放
		cout << "Base类析构函数被调用" << endl;
	};
};

class Child : public Base		//Child类由基类Base派生而来
{
private:
	char* m_data;				//增添的字符指针成员

public:
	Child():Base()				//构造函数，初始化表中执行基类的构造函数
	{
		m_data = new char[64];	//动态申请内存，并将首地址赋给m_data
		cout << "Child类构造函数被调用" << endl;
	};

	~Child()					//析构函数，继承虚拟virtual
	{
		delete [] m_data;		//内存资源释放
		cout << "Child类析构函数被调用" << endl;
	};
};

class GrandChild:public Child	//GrandChild类由Child类派生而来
{
private:
	char* mm_data;				//在Child类基础上增加的字符指针成员mm_data

public:
	GrandChild():Child()		//构造函数
	{
		mm_data = new char[64];	//动态内存申请
		cout << "GrandChild类构造函数被调用" << endl;
	};

	~GrandChild()				//虚析构函数，virtual从继承结构中得来
	{
		delete [] mm_data;		//内存释放
		cout << "GrandChild类析构函数被调用" << endl;
	};
};

int main()
{
	Base *pB = new Child;			//动态申请了一块Child大小的内存，赋给Base基类指针
	delete pB;						//Child类的析构函数执行，释放内存，不会泄露

	cout << endl;

	Child* pC = new GrandChild;		//动态申请了一块GrandChild大小的内存，赋给Child类指针
	delete pC;						//GrandChild类的析构函数执行，释放内存，不会泄露

	cout << endl;

	GrandChild *pG = (GrandChild *)new Base;
	delete pG;	//如果去掉基类析构函数前的virtual, 执行到delete [] mm_data时会报内存错误, 因为mm_data根本就没有new

	return 0;
}
```

#### 2.4.5.1 虚析构函数调用规则

-  如果有一个基类的指针指向派生类的对象，并且想通过该指针delete派生类对象,系统将只会执行基类的析构函数，而不会执行派生类的析构函数。为避免这种情况的发生，往往把基类的析构函数声明为虚的，此时，系统将先执行派生类对象的析构函数，然后再执行基类的析构函数。

- 如果基类的析构函数声明为虚的，派生类的析构函数也将自动成为虚析构函数，无论派生类析构函数声明中是否加virtual关键字。

```cpp
class CWorm
{
public:
	virtual void Draw()
	{
		cout<<"CWorm::Draw()"<<endl;
	}
//	virtual 
	~CWorm()
	{
		cout<<"CWorm::~CWorm()"<<endl;
	}
};
class CAnt:public CWorm
{
private:
	int *ptr;
public:
	void Draw()
	{
		ptr = new int;
		//CWorm::Draw();	
	//如果希望在执行自己的功能的同时，也执行基类的功能，可用此方式调用
		cout<<"CAnt::Draw()"<<endl;
	}
	~CAnt()
	//如果父类的析构函数不是virtual，则不调用子类的析构函数，ptr不能释放
	{
		delete ptr;  
		cout<<"CAnt::~CAnt()"<<endl;
	}
};
void main()
{
	CWorm *pWorm=new CAnt;
	pWorm->Draw();
	delete pWorm;
}

```

### 2.4.6 多基派生的二义性

- 分析如下所示的DAG图，各个类的定义为：

- 见备注代码

- 比较复杂，具体分析见代码中的注释。

```cpp
//11-12 多基派生引起的虚函数访问二义性问题
#include <iostream>
using namespace std;

class A
{
public:
	virtual void a() //虚函数
	{
		cout << "a() in A" << endl;
	}
	virtual void b() //虚函数
	{
		cout << "b() in A" << endl;
	}
	virtual void c() //虚函数
	{
		cout << "c() in A" << endl;
	}
};

class B
{
public:
	virtual void a() //虚函数
	{
		cout << "a() in B" << endl;
	}
	virtual void b() //虚函数
	{
		cout << "b() in B" << endl;
	}
	void c() //非虚函数
	{
		cout << "c() in B" << endl;
	}
	void d() //非虚函数
	{
		cout << "d() in B" << endl;
	}
};

class C:public A, public B
{
public:
	virtual void a() //虚函数，覆盖
	{
		cout << "a() in C" << endl;
	}
	void c() //特殊
	{
		cout << "c() in C" << endl;
	}
	void d() //非虚函数，隐藏
	{
		cout << "d() in C" << endl;
	}
};

int main()
{
	C c;	//声明一个派生类对象c
//	c.b();	//b()在A, B类中都定义为虚函数, C中无法确定使用哪个版本, 
		//引起二义性错误. 解决: c.B::b();
	cout << "c.b();//会引起二义性错误" << endl;

	cout << endl;

	A* pA = &c;	//用派生类对象c的地址为A类指针赋值
	pA->a();	//a()在A, B , C三个类中都是虚函数, 调用C类的c(), 输出: a() in C
	pA->b();	//b()在A, B类中都是虚函数, C类中没有定义, 编译器无法确定使用
	//哪个版本, 只能采用静态联编. 由于pA的类型是A *，所以输出: b() in A
	pA->c();	//c()在A中为虚函数, B中为普通函数, C中进行了重定义. 此时输出
//取决于指针pA的类型A, 由于c()在A中为虚函数, 故按照虚函数的规则处理,输出c() in C

	cout << endl;

	B* pB = &c;	//用派生类对象c的地址为B类指针赋值
	pB->a();	//a()在A, B , C三个类中都是虚函数, 调用C类的c(), 输出: a() in C
	pB->b();	//b()在A, B类中都是虚函数, C类中没有定义, 编译器无法确定使用//哪个版本, 只能采用静态联编. 由于pB的类型是B *，所以输出: b() in B
	pB->c();	//c()在A中为虚函数, B中为普通函数, C中进行了重定义. 此时输出
//取决于指针pB的类型B, 由于c()在B中为普通函数, 故按照普通函数的规则处理,输出c() in B
	pB->d();	//d()在B, C类中都定义为普通函数, C中的d()会隐藏基类B中的d(), 
		//但pB类型为B *, 故输出d() in B

	cout << endl;

	C *pC = &c;
	pC->a();//a()在A, B , C三个类中都是虚函数, 调用C类的c(), 输出: a() in C
//	pC->b();//b()在A, B类中都定义为虚函数, C中无法确定使用哪个版本, 
		//引起二义性错误. 解决: pC->B::b();
	cout << "pC->b();//会引起二义性错误" << endl;
	pC->c();	//c()在A中为虚函数, B中为普通函数, C中进行了重定义(?). 此时输//出取决于指针pC的类型C, c()在C中无论是虚函数还是普通函数, 都输出c() in C
	pC->d();	//d()在B, C类中都定义为普通函数, C中的d()会隐藏基类B中的d(), 
		//但pC类型为C *, 故输出d() in C

	return 0;
}
```

### 2.4.7 重载、覆盖与隐藏

- 对类层次中的同名成员函数来说，有3种关系：重载（overload）、覆盖（override）和隐藏（hide、oversee），理清3种关系，有助于写出高质量代码。

#### 2.4.7.1 重载

- 重载的概念相对简单，只有在同一类定义中的同名成员函数才存在重载关系，主要特点是函数的参数类型和数目有所不同，但不能出现函数参数的个数和类型均相同，仅仅依靠返回值类型不同来区分的函数，这和普通函数的重载是完全一致的。另外，重载和成员函数是否是虚函数无关，举例来说：

```cpp
class A
{
……
	virtual int fun();

	void fun(int);

	void fun(double,double);
……
};
```

- 上述A类定义中的3个fun函数便是重载关系。

#### 2.4.7.2 覆盖

- 覆盖是指：在派生类中覆盖基类中的同名函数，要求两个函数的参数个数、参数类型、返回类型都相同，且基类函数必须是虚函数。如：A->B

- 以类B再派生出类C时，类C继承的便是覆盖后的B类的虚函数版本，除非在C类中对该虚函数进行重定义。B->C

- 见备注代码

- B中的fun1覆盖了A中的fun1，同时继承了A中的fun2

- C类继承了B中的fun1，同时重定义覆盖了fun2

```cpp
// 覆盖
#include <iostream>
using namespace std;

class A
{
public:
	virtual void fun1(int, int) {}
	virtual int  fun2(char *){return 0;}
};

class B : public A
{
public:
	void fun1(int, int){}
};

class C : public B
{
public:
	int fun2(char *) {return 1;}
};

int main()
{
	A *pA = new C;
	pA->fun1(11, 22);
	pA->fun2("11-22");
	return 0;
}
```

#### 2.4.7.3 隐藏

- 隐藏指的是在某些情况下，派生类中的函数屏蔽了基类中的同名函数，这些情况包括：

  - 2个函数参数相同，但基类函数不是虚函数。和覆盖的区别在于基类函数是否是虚函数。

  - 2个函数参数不同，无论基类函数是否是虚函数，基类函数都会被屏蔽。和重载的区别在于两个函数不在同一类中。

- 见备注代码

```cpp
// 类层次结构中的函数隐藏
#include <iostream>
using namespace std;

class A	//类A的定义
{
public:
	void fun(int xp)	//非虚成员函数fun，参数为int型
	{
		cout << xp << endl;
	}
};

class B:public A		//类B由类A派生而来
{
public:
	void fun(char* s)	//隐藏，oversee，参数为字符串
	{
		cout << s << endl;
	}
//	void fun(int xp)	
	//重载. 如果没有定义该重载函数, main()中的b.fun(2)语句会出错
//	{
//		A::fun(xp);
//	}
};

int main()
{
	B b;			//声明一个B类对象
	b.fun("hello");		//字符串参数版本
	b.fun(2);			//错误，发生隐藏，找不到fun(int).
//解决方法: 在B中重载fun(int)版本的函数, 即取消B类中的注释代码的注释
	return 0;
}
```

### 2.4.8 virtual(虚拟继承－虚函数)

- 从语义上来讲，为什么动态多态和虚继承都使用virtual关键字来表示？

- virtual的解释

```cpp
1. `Existing or resulting in essence or effect though not in actual fact, form, or name.`

实质上的，实际上的：虽然没有实际的事实、形式或名义，但在实际上或效果上存在或产生的;

2. `Existing in the mind, especially as a product of the imagination. Used in literary criticism of text.`

虚的，内心的：在头脑中存在的，尤指意想的产物。用于文学批评中
```

- C++中的virtual关键字采用第一个定义，即被virtual所修饰的事物或现象在本质上是存在的，但是没有直观的形式表现，无法直接描述或定义，需要通过其他的间接方式或手段才能够体现出其实际上的效果。

- 关键就在于存在、间接和共享这三种特征

  - 虚函数是存在的

  - 虚函数必须要通过一种间接的运行时（而不是编译时）机制才能够激活（调用）的函数

  - 共享性表现在基类会共享被派生类重定义后的虚函数

- 虚拟继承如何表现：

  - 存在即表示虚继承体系和虚基类确实存在

  - 间接性表现在当访问虚基类的成员时同样也必须通过某种间接机制来完成（通过虚基表来完成）

  - 共享性表现在虚基类会在虚继承体系中被共享，而不会出现多份拷贝

- 虚继承：在继承定义中包含了virtual关键字的继承关系

- 虚基类：在虚继承体系中的通过virtual继承而来的基类

- 语法：

```cpp
class Subclass : public virtual Baseclass 
{
	public:  //...
	private:  //...
	protected: //...
};
```

其中`Baseclass`称之为`Subclass`的虚基类；而不是说`Baseclass`就是虚基类

```cpp
Example1. 
/*
测试一：单个虚拟继承，不带虚函数	
虚拟继承与继承的区别：
       1. 虚基类处于对象内存的末尾
       2. 多了一个虚基指针

测试二：单个虚拟继承，带虚函数
       如果派生类拥有自己的虚函数(并不是覆盖),它产生的虚指针是位于虚基指针的前面的
       或者说，一个类如果有自己的虚函数，它在内存中的布局一定是位于最开始的位置，原因是为了提高访问虚函数的速度
*/

#include <iostream>
class A
{
public:
	A() : ia_(10){}
	/*virtual*/ void f(){	std::cout << "A::f()" << std::endl;	}
private:
	int ia_;
};

class B : virtual public A
{
public:
	B() : ib_(20){}
	void fb(){	std::cout << "B::fb()" << std::endl;	}
	/*virtual*/ void f(){	std::cout << "B::f()" << std::endl;	}
	/*virtual*/ void fb2(){	std::cout << "B::fb()" << std::endl;	}
private:	int ib_;
};
int main(void)
{
	B b;
	std::cout << "sizeof(b)=" << sizeof(b) << std::endl;
	return 0;
}
int test0(void)
{
	typedef void (*Function)(void);
	B b;
	std::cout << "sizeof(b) = " << sizeof(b) << std::endl;
	int **pVfTable = (int **)&b;
	int pVtableAddr = *(int*)&b;//pVtableAddr保存是虚函数表的入口地址
	int pVfuncFirstAddr = *(int*)pVtableAddr;
	Function pFun = (Function)pVfuncFirstAddr;
	pFun();
	return 0;
}

Example2  
/*
多重继承（带虚函数）
	1. 每个基类都有自己的虚表
	2. 派生类的虚成员函数被加入到第一个基类的虚函数表中
	3. 内存布局中，其基类布局依次按其声明时的顺序进行排列
	4. 派生类会覆盖掉基类的对应的虚函数，第一个虚函数表中的
	    被覆盖的虚函数地址是真实的；之后的虚函数表中的对应的
	    被覆盖的虚函数所存放的并不是虚函数的地址，而是一条跳转指令
*/
#include <iostream>
class Base1
{
public:
	Base1() : iBase1_(10) {}
	virtual void f() {	std::cout << "Base1::f()" << std::endl;	}
	virtual void g() {	std::cout << "Base1::g()" << std::endl;	}
	virtual void h() {	std::cout << "Base1::h()" << std::endl;	}
private:
	int iBase1_;
};
class Base2
{
public:
	Base2() : iBase2_(100) {}
	virtual void f(){	std::cout << "Base2::f()" << std::endl;	}
	virtual void g(){	std::cout << "Base2::g()" << std::endl;	}
	virtual void h(){	std::cout << "Base2::h()" << std::endl;	}
private:
	int iBase2_;
};

class Base3
{
public:
	Base3() : iBase3_(1000) {}
	virtual void f(){	std::cout << "Base3::f()" << std::endl;	}
	virtual void g(){	std::cout << "Base3::g()" << std::endl;	}
	virtual void h(){	std::cout << "Base3::h()" << std::endl;	}
private:
	int iBase3_;
};

class Derived : public Base1, public Base2, public Base3
{
public:
	Derived() : iDerived_(10000){}
	virtual void f(){	std::cout << "Derived::f()" << std::endl;	}
	virtual void g1(){	std::cout << "Derived::g1()" << std::endl;	}
private:
	int iDerived_;
};
int main(void)
{
	Derived d;
	return 0;
}
Example3
//测试三：多重继承具有共同的基类   vs  虚拟继承
/*
虚基指针所指向的虚基表的内容：
	1. 虚基指针的第一条内容表示的是该虚基指针距离所在的子对象的首地址的偏移
	2. 虚基指针的第二条内容表示的是该虚基指针距离虚基类子对象的首地址的偏移
*/

#include <iostream>
class B
{
public:
	B() : ib_(10), cb_('B'){}
	virtual void f(){	std::cout << "B::f()" << std::endl;	}
	virtual void Bf(){	std::cout << "B::Bf()" << std::endl;	}
private:
	int ib_;
	char cb_;
};

class B1 : virtual public B
{
public:
	B1() : ib1_(11), cb1_('1'){}
	virtual void f(){	std::cout << "B1::f()" << std::endl;	}
	virtual void f1(){	std::cout << "B1::f1()" << std::endl;	}
	virtual void Bf1(){	std::cout << "B1::Bf1()" <<std::endl;	}
private:
	int ib1_;
	char cb1_;
};

class B2 : virtual public B
{
public:
	B2() : ib2_(11), cb2_('1'){}
	virtual void f(){	std::cout << "B2::f()" << std::endl;	}
	virtual void f2(){	std::cout << "B2::f2()" << std::endl;	}
	virtual void Bf2(){	std::cout << "B2::Bf2()" <<std::endl;	}
private:
	int ib2_;
	char cb2_;
};
class D : public B1, public B2
{
public:
	D() : id_(100), cd_('D'){}
	virtual void f(){	std::cout << "D::f()" << std::endl;	}
	virtual void f1(){	std::cout << "D::f1()" << std::endl;	}
	virtual void f2(){	std::cout << "D::f2()" <<std::endl;	}
	virtual void Df(){	std::cout << "D::Df()" << std::endl;	}
private:
	int id_;
	char cd_;
};

int main(void)
{
	D d;
	return 0;
}
```

### 2.4.9 虚基派生的构造函数和析构函数

- 对普通的多层继承而言，构造函数的调用是嵌套的，如由C1类派生C2类，C2类又派生C3类时，C1-->C2-->C3，有：

```cpp
C2(总参数表):C1(参数表)
C3(总参数表):C2(参数表)
```

- 而对虚基派生来说，如果按照上述规则，应该有：

```cpp
B(总参数表):A(参数表)
C(总参数表):A(参数表)
D(总参数表):B(参数表),C(参数表)//,A(参数表)
```

- 这样“A(参数表)”将被执行2次，这显然不行。

- 实际情况是：

```cpp
B(总参数表):A(参数表)

C(总参数表):A(参数表)

D(总参数表):B(参数表),C(参数表),A(参数表)
```

- 根据虚基派生的性质，类D中只有一份虚基类A的拷贝，因此A类的构造函数在D类中只能被调用一次。所以，从A类直接派生(B和C)和间接派生(D)的类中，其构造函数的初始化列表中都要列出对虚基类A构造函数的调用。这种机制保证了不管有多少层继承，虚基类的构造函数必须且只能被调用一次。

- 如果未列出,则表明调用的是虚基类的无参构造函数，不管初始化列表中次序如何，对虚基类构造函数的调用总是先于普通基类的构造函数。

- 见备注代码

```cpp
//Example 虚基派生的构造函数和析构函数
#include <iostream>
using namespace std;

class A					//类A定义
{
private:					//private成员列表
	int x;
public:						//public成员列表
	A(int xp = 0)			//构造函数，带缺省参数
	{
		x=xp;
		cout<<"A的构造函数被执行"<<endl;
	}
	~A()					//析构函数
	{
		cout<<"A的析构函数被执行"<<endl;
	}
	void Print()			//显示成员变量x的值
	{
		cout << x << endl;
	}
};

class B:virtual public A	//类B由类A虚基派生而来
{
public:
	B(int xp):A(xp)			//在初始化表中调用基类构造函数
	{
		cout<<"B的构造函数被执行"<<endl;
	}

	~B()					//析构函数
	{
		cout<<"B的析构函数被执行"<<endl;
	}
};

class C:virtual public A	//类C由类A虚基派生而来
{
public:
	C(int xp):A(xp)			//在初始化表中调用基类构造函数
	{
		cout<<"C的构造函数被执行"<<endl;
	}
	~C()					//析构函数
	{
		cout<<"C的析构函数被执行"<<endl;
	}
};

class D:public B,public C	//类D由类B和类C共同派生而来
{
public:
      	//初始化表中不仅要调用B类和C类的构造函数，还应调用共同虚基类的构造函数A(xp)
	D(int xp):B(xp),C(xp),A(xp)	
	{
		cout<<"D的构造函数被执行"<<endl;
	}
	~D()					//析构函数
	{
		cout<<"D的析构函数被执行"<<endl;
	}
};

int main()
{
	D d(2);	//声明D类对象d
	d.Print();	//结果为2。如果去掉类D的构造函数的初始化列表中的A(xp)，则结果为0。
	cout << endl;

	B b(3);
	b.Print();	//结果为3。如果去掉类B的构造函数的初始化列表中的A(xp)，则结果为0。	cout << endl;

	return 0;		//main函数执行完毕退出后，d销毁，析构函数触发执行
}

```

- 如果是在若干类层次中，从虚基类直接或间接派生出来的子类的构造函数初始化列表均有对该虚基类构造函数的调用，那么创建一个子类对象的时候只有该子类列出的虚基类的构造函数被调用，其他类列出的将被忽略，这样就保证虚基类的唯一副本只被初始化一次。即虚基类的构造函数只被执行一次。

- 继承机制下析构函数的调用顺序：

  - 先调用派生类的析构函数

  - 然后调用派生类中成员对象的析构函数

  - 再调用普通基类的析构函数

  - 最后调用虚基类的析构函数

![image-20220706212814841](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220706212814841.png)
