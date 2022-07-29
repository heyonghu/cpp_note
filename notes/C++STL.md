# 1. 标准模板库(STL)概述

- `STL`，即`Standard Template Library`，不是面向对象的编程，而是一种新的编程模式：泛型编程（Generic Programming）。STL是C++标准库的组成部分，STL是很庞大复杂的系统，单单就STL就可写出厚达千页的技术书籍，所以，本章不可能做到面面俱到，重点在于介绍泛型编程的思想和本质，介绍一些常用的方法，为初学者学习STL提供一些感性认识，起到抛砖引玉的作用。

- STL是一项比较新的技术，VC6是微软公司比较老的一款编译器，其对STL的支持并不是太好，因此，在本章学习时，推荐采用较新的VS2012以后的编译器。

## 1.1 理解STL

- STL库是用模板（template）写出来的，模板是STL库的基础。STL大致由以下几部分组成： 

  - 容器（container）

  - 迭代器（iterator） ---> 指针

  - 适配器（Adapter）

  - 算法（algorithm）

  - 函数对象（`functor`）

  - 配置器（allocator） --- 透明的

- 容器、迭代器、容器适配器都是用类模板实现的，迭代器用于遍历容器中的每一个元素，算法用于操作数据。 

## 1.2 容器

- 如果没有STL的支持，在处理一些复杂问题时，要自行设计存储模式，如数组管理，插入删除操作等，这不但很繁琐，而且bug频出，是程序出问题最多的地方。STL运用模板类库机制，为数据存储，查找和其他操作提供了一整套方案，大大提高了程序的正确性。不仅如此，类库对常用的很多操作进行了优化处理，大大提高了程序的效率。

- 容器是可容纳一些数据的类模板，STL中有`vector、list、deque、set/multiset、map/multimap`等容器。

## 1.3 迭代器

- 在有的专业书籍中，迭代器也称游标，可以将迭代器初步理解为广义指针，迭代器和指针功能很像，迭代器是通过重载一元的”*”和”->”来从容器中间接地返回一个值。

- 迭代器有5种，依次为：

  - 随机访问迭代器（Random Access Iterator）

  - 双向迭代器（Bidirectional Iterator）

  - 前向迭代器（Forward Iterator）

  - 输入迭代器（Input Iterator）

  - 输出迭代器（Output Iterator）

## 1.4 适配器

- 适配器就是Interface(接口)，对容器、迭代器和算法进行包装，但其实质还是容器、迭代器和算法，只是不依赖于具体的标准容器、迭代器和算法类型，容器适配器可以理解为容器的模板，迭代器适配器可理解为迭代器的模板，算法适配器可理解为算法的模板。

- 常见的容器适配器有：`stack、queue、priority_queue`（不支持迭代器访问）

## 1.5 算法

- STL包含了很多对容器进行处理的函数，它们的处理思路大体相同：使用迭代器来标识要处理的数据或数据段、以及结果的存放位置，有的函数还作为对象参数传递给另一个函数，实现数据的处理。

# 2. 序列式容器

- 容器是STL的基础，容器分2种：

  - 序列式容器（sequential container）

  - 关联式容器（associative container）

- 序列式容器会强调元素的次序，依次维护第一个元素、第二个元素……，直到最后一个元素，面向序列式容器的操作主要是迭代操作。

- 本节讨论序列式容器vector、list和deque的用法，以及序列式容器的共同操作。

- 关联式容器在后面讲解

![image-20220714225614037](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220714225614037.png)

## 2.1 序列式容器的创建和元素的访问

- 使用序列式容器，须包含相关的头文件，vector、list及deque分别对应：

```cpp
#include <vector>
#include <list>
#include <deque>
```

- 创建序列式容器的对象，大体有5种方式：
  -  (1)创建空的容器，此时容器中的元素个数为0。

    ```cpp
    vector<int> obV;
    list<float> obL;
    deque<double> obD;
    ```

  -  (2)`vector<double> obV(10);` //vector型对产生特定大小的容器，此时容器中的元素被创建，编译器使用默认值为元素隐式初始化，像int、float和double等内建的数据类型会被初始化为0，对于类对象元素，将调用其无参构造函数（用户定义的或编译器缺省提供的）或每个参数都有默认值的构造函数。象obV中含10个double型元素, 初始化为0
  
      ```cpp
    list<int> obL(20);   //list型对象obL中含20个int型元素, 初始化为0
    deque<float> obD(30);  //deque型对象obD中含30个float型元素, 初始化为0
    ```
  
  - (3)在(2)的基础上更进一步，创建特定大小的容器，并且为其中的每个元素指定初始值，此时在元素多少的参数后增加一个参数。
  
     ```cpp
     vector<int> obV(10,8);     //10个int型元素, 每个都初始化为8
     list<double> obL(20,3.1);   //20个double型元素, 每个都初始化为3.1
     deque<string> obD(30,"Hello"); //30个string型元素, 每个都初始化为"Hello"
     ```
  
  - (4)根据已有同类型的容器创建新容器，并将其中的元素完全复制过来，设obV1、obL1和obD1都是现成的容器，里面存储的数据均为int型，则可用下述命令创建新容器
  
    ```cpp
    vector<int> obV2(obV1); //或vector<int> obV2=obV1;
    list<int> obL2(obL1);  //或list<int> obL2=obL1;
    deque<int> obD2(obD1);  //或deque<int> obD2=obD1;
    ```
  
  - (5)通过一对迭代器（可暂时理解为指针），以使编译器决定元素的个数和初值，这对迭代器用以标识一组元素区间。
  
    ```cpp
    int sz[5]={11,2,3,4,45};
    
    vector<int> obV(sz, sz+5);
    
    list<int> obL(sz, sz+5);
    
    deque<int> obD(sz, sz+5);
    ```
  
    - vector和deque类的容器创建后就可以通过容器名[下标]或容器名.at(序号)的形式对元素进行随机访问(这是因为这2种类模板对下标运算符[]进行了重载)；也支持迭代器访问。
  
    - 但list类的容器不支持下标运算符[]，无法使用[]对元素进行随机访问。但支持双向迭代器访问，如：
  
      ```cpp
      list<int>::iterator iter = obL.begin();
      ```
      
    - 见备注代码
  

```cpp
//容器的创建与元素的访问
#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;
#define UINT unsigned int

int main()
{
	//1. 创建vector容器
	vector<int> obv;	//创建一个空的vector
	cout << "obv的元素个数为：" << obv.size() << endl << endl; 	//size()用以返回元素的个数
	
	//2. 创建deque容器
	double sz[5] = {1, 2, 3, 4, 5};		//创建double型数组sz
	deque<double> obD(sz, sz + 5);		//创建deque型容器obD，并用sz的首地址和末地址为其初始化，第种方式

	//2.1 使用下标[]访问deque容器的元素
	for (UINT i = 0; i < obD.size(); i++) //对obD中的元素进行随机访问，下标表示法
	{
		cout << obD[i] << "  ";
	}
	cout << endl;

	//2.2 使用迭代器访问deque容器的元素
	deque<double>::iterator id = obD.end();
	while (id != obD.begin())
	{
		id--;	//注意, obD.end()指向的是最后一个元素的下一个迭代器.
		cout << (*id) << "  ";
	}

	cout << endl << endl;				//换行
	
	//3. 创建list容器
	list<float> obL(3, 5);				//创建一大小为的list型容器obL，其中每个元素都初始化为

	//3.1 list不支持下标访问
	//obL[0] = 3;							//错误, list不支持下标访问

	//3.2 使用迭代器访问list容器的元素
	list<float>::iterator iter = obL.begin(); //创建list<float>型迭代器，类似指针的概念，并使其指向obL的第一个元素
	while (iter != obL.end())			//while结构，直到iter指向obL的尾部
	{
		(*iter) += 2;					//赋值
		cout << (*iter) << "  ";		//通过迭代器间接访问容器中的元素，和指针相似
		iter++;								//指向下一个元素
	}
	cout << endl;				//换行

	//3.3 再创建一个list容器obL2, 将其内容与obL的内容进行交换
	list<float> obL2(4, 9);
	obL.swap(obL2);
	
	//3.4 重新输出obL中的内容
	for (iter = obL.begin(); iter != obL.end(); iter++)
	{
		cout << (*iter) << "  ";
	}
	cout << endl << endl;				//换行
	
	//4.
	system("pause");
	return 0;
}
```

## 2.2 所有容器都支持的特征

- 代码中，`“obL.begin()”`返回的是指向容器第一个元素的迭代器，这是所有容器（容器和容器适配器）都支持的特征之一。

- 所有容器都支持的特征见表13.1，其中`ob、ob1和ob2`是容器对象名。

![image-20220714230515219](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220714230515219.png)

## 2.3 序列式容器中元素的插入和删除

- 在创建普通数组时，需要指定元素的个数，元素的插入和删除很繁琐。但在序列式容器中，只要调用操作函数，所有的事情都由STL类库自动完成，而且容器对象都能随着元素的插入和删除自动地增大或缩小。

- 下面介绍5类相关函数：

  - (1)在容器尾部进行插入和删除(list、deque和vector都适用)：

  - ```cpp
    void push_back(t)和void pop_back(void)
    ```

  - (2)在容器头部进行插入和删除(list和deque适用，vector不适用):

  - ```cpp
    void push_front(t)和void pop_front(void)
    ```

  -  (3)获取容器头部和尾部元素(list、deque和vector都适用)： 

  - ```cpp
    front(void)和back(void)
    ```

  - ```cpp
    //13-2 在容器尾部插入和删除元素
    #include <iostream>
    #include <vector>
    #include <list>
    #include <deque>
    using namespace std;
    
    int main()
    {
    	//0. 定义vector容器
    	vector<int>::iterator it;
    	vector<int> obV(3, 1);	//创建一个vector类对象，包含个int型元素，每个都为1
    	//list<int>::iterator it;
    	//list<int> obV(3, 1);		//创建一个vector类对象，包含个int型元素，每个都为1
    	//deque<int>::iterator it;
    	//deque<int> obV(3, 1);	//创建一个vector类对象，包含个int型元素，每个都为1
    
    	//1. 在尾部插入元素
    	obV.push_back(2);		//将int型数据安插在容器对象obV末尾
    
    	//2. 输出，看是否安插成功
    	it = obV.begin();
    	while (it != obV.end())
    	{
    		cout << (*it) << "  ";	//输出处理，看是否安插成功
    		it++;
    	}
    	cout << endl;
    
    	//3. 从尾部弹出元素
    	obV.pop_back();		//将最后一个元素弹出
    
    	//4. 输出，看是否弹出成功
    	it = obV.begin();
    	while (it != obV.end())
    	{
    		cout << (*it) << "  ";	//输出处理，看是否弹出成功
    		it++;
    	}
    	cout<<endl;
    
    	//5. 将处定义的vector容器分别改成list和deque容器, 重新测试以上代码
    	//测试结果表明push_back()和pop_back()同时适用这种容器
    
    	getchar();
    	return 0;
    }
    
    //13-3 在容器头部插入和删除元素
    #include <iostream>
    #include <vector>
    #include <list>
    #include <deque>
    using namespace std;
    
    int main()
    {
    	//0. 定义list容器
    	list<int>::iterator iter;
    	int sz[5] = {1,2,3,4,5};
    	list<int> obL(sz, sz+5);	//创建一个list对象，包含个int型元素
    
    	//1. 在容器头部插入元素
    	obL.push_front(9);		//将int型数据安插在容器对象obL头部
    
    	//2. 输出处理，看是否安插成功
    	iter = obL.begin();
    	while (iter != obL.end())
    	{
    		cout << (*iter) << "  ";	//输出处理，看是否安插成功
    		iter++;
    	}
    	cout << endl;
    
    	//3. 从容器头部删除元素
    	obL.pop_front();			//将第一个元素弹出
    
    	//4. 输出处理，看是否弹出成功
    	iter=obL.begin();	
    	while(iter != obL.end())
    	{
    		cout << (*iter) << "  ";	//输出处理，看是否弹出成功
    		iter++;
    	}
    	cout << endl;
    
    	//5. 将处定义的list容器分别改成vector和deque容器, 重新测试以上代码
    	//测试结果表明push_front()和pop_front()只适用于list和deque，不适用于list
    
    	getchar();
    	return 0;
    }
    
    //13-4 读取容器头部和尾部元素的值front(), back(). 同时适用于list, vector和deque三种容器
    #include <iostream>
    #include <vector>
    #include <list>
    #include <deque>		//使用deque必须包含的头文件
    using namespace std;
    
    int main()
    {
    	double sz[6] = {0,1,2,3,4,5};
    	deque<double> obD(sz, sz+6);
    
    	double dFront = obD.front();	//读取最前端元素的值
    	double dBack = obD.back();	//读取最末端元素的值
    
    	cout << dFront << endl;
    	cout << dBack << endl;
    
    	getchar();
    	return 0;
    }
    
    //迭代器失效
    int main(void)
    {
    	std::vector<std::string> vcs;
    	vcs.push_back("this is A");	
    	std::vector<std::string>::iterator it = vcs.begin();
    	int i = 9;
    	for(; it != vcs.end(); ++it)
    	{
    		std::cout << "caplity of vector is : " << vcs.size() << std::endl;
    		std::cout << "---> " << *it << std::endl;//直接coredump
    		if(i == 9)
    		{
    			vcs.push_back("this is BBBB");
    			std::cout << "vcs.push! " << std::endl;
    		}
    		i = 8;
    	}
    }
    ```

  - (4)在容器中间插入元素。有如下3种重载形式：

    - 将元素t插到p之前，返回的迭代器指向被插入的元素。

     `iterator insert(iterator p, elemType t);`

    - 在p之前插入n个t，无返回值。

      `void insert(iterator p, int n, elemType t);`

    - 在p之前插入[first, last)之间的所有元素。

      `void insert(iterator p, iterator first, iterator last);`

  - ```cpp
    //13-5 容器的3种重载形式的插入操作
    #include <iostream>
    #include <vector>
    #include <list>
    #include <deque>
    using namespace std;
    
    void disp(vector<int> & x)			//定义disp函数用以输出容器对象所有元素
    {
    	vector<int>::iterator it = x.begin();
    	while (it != x.end())
    	{
    		cout << (*it) << "  ";
    		it++;
    	}
    }
    
    int main()
    {
    	//1. 创建一个vector<int>容器对象
    	vector<int> obD(5, 0);
    
    	//2. insert()的重载形式
    	vector<int>::iterator pD = obD.end();	//创建迭代器pD
    	pD = obD.insert(pD, 1);			//在尾部插入元素，并使迭代器指向新插入的
    	disp(obD);
    	cout << endl;
    
    	//3. insert()的重载形式
    	obD.insert(pD, 2, 3);			//在新插入的元素之前插入两个元素
    	disp(obD);
    	cout << endl;
    
    	//4. insert()的重载形式
    	pD = obD.begin();	//很重要，插入后，原来的迭代器可能失效
    	int sz[3] = {7,8,9};
    	obD.insert(pD, sz, sz + 3);		//将两个指针（相当于迭代器）插入到头部
    	disp(obD);
    	cout << endl;
    
    	//5. 上述插入操作对list, vector, deque三种容器都适合. 可自行测试
    
    	getchar();
    	return 0;
    }
    ```

  - (5)erase删除操作，有2种重载形式：

    - 删除迭代器p所指向的元素，返回p指向的下一个迭代器：

     `iterator erase(iterator p);`

    - 删除`[frist,last)`之间的所有元素，返回last指向的下一个迭代器：

    - `iterator erase(iterator first, iterator last);`
    
  - (6)clear操作：用于将容器对象清空。
  
     `void clear(void);`
  
    用法很简单，不再举例
  
    对于`std::list`还有一种删除方法: 成员函数 `remove/remove_if`
    
  - ```cpp
    //删除容器中间的元素
    #include <iostream>
    #include <list>
    using namespace std;
    
    void disp(list<int>& x)					//定义disp函数用以输出容器对象所有元素
    {
    	list<int>::iterator it=x.begin();
    	for(;it!=x.end();it++)				//list不支持下标随机访问
    	{
    		cout<<(*it)<<"  ";
    	}
    }
    
    int main()
    {
    	//1. 创建容器
    	int sz[9]={1,2,3,4,5,6,7,8,9};
    	list<int> obL(sz,sz+9);				//使用两个迭代器（指针）创建list<int>对象
    	disp(obL);
    	cout<<endl;
    
    	//2. erase重载版本
    	list<int>::iterator iter=obL.begin();//创建迭代器iter，指向最前端元素
    	iter++;								//指向第二个元素
    	iter=obL.erase(iter);				//将第二个元素抹掉，并用指向第三个元素的迭代器为iter赋值
    	disp(obL);
    	cout<<endl;
    
    	//3. erase重载版本
    	obL.erase(iter,obL.end());			//将第个元素直到最后一个元素都抹掉
    	disp(obL);
    	cout<<endl;
    
    	//4. clear
    	obL.clear();
    	cout << "clear()后容器的元素个数为: " << obL.size() << endl;
    
    	getchar();
    	return 0;
    }
    
    // list::move/move_if
    
    #include <iostream>
    #include <list>
    
    int main(void)
    {
          std::list<int> l = {1, 100, 2, 3, 10, 1, 11, -1, 12};
          l.remove(1);
          l.remove_if([](int n){    return n > 10;});
          for(int n : l)
          {      std::cout << n << ' ' ;      }
          std::cout << std::endl;
          return 0;
    }
    ```
  
## 2.4 vector容器

- 介绍完vector、list以及deque的通用用法，下面分别讨论下其特别之处。首先是vector，字面翻译为向量，其用法类似于数组，但其功能比数组更强大。简单地说，vector是数组的类表示，它提供了自动管理内存的功能，可以动态改变vector对象的长度，并随着元素的增删而增大或缩小(?)，提供了对元素的随机访问，和数组一样，在vector尾部添加和删除元素（push_back和pop_back）的时间是固定的，但在vector中间或头部增删元素(insert,erase)的时间和复杂度线性正比于vector容器对象中元素的多少。

## 2.5 deque容器

- deque表示双端队列（double-ended queue），deque容器对象支持下标随机访问，在deque头部和尾部添加删除元素时的时间都是固定的，因此，如果有很多操作是针对序列的头部位置的，建议使用deque容器。但是，如果是在deque的中间进行元素的增删处理，操作的复杂度和时间正比于deque对象中元素的多少。

## 2.6 list容器

- list类模板表示双向链表，除了首尾元素外，list容器对象中的每个元素都和前面的元素相链接。list不支持下标随机访问，只能通过迭代器双向遍历。

- 和vector和deque不同的是，在list的任何位置增删元素的时间都是固定的。

- 说明：除了上述介绍的基本操作外，序列式容器还有其它用于特定场合的成员函数操作，限于篇幅原因，本章只对STL作入门式介绍，更详细的内容可查阅相关资料。

# 3. 关联式容器

- 关联式容器（associative）又称“联合容器”，将值（value）和关键字（keyword）成对关联，举例来说，在学生管理系统设计时，可以将学号作为关键字，起索引的目的，而将学生姓名、性别、籍贯等信息作为值与学号配对。

- 标准的STL提供了4种联合容器类模板：set、map、multiset和multimap，总体来说，set中仅仅包含关键字，而没有值的概念，map中存储的是“关键字――值”对，map和set中不会出现多个相同的关键字，multiset和multimap可以分别看作是对set和map的扩展，multimap和multiset允许相同关键字的存在。

- 4种关联式容器都会根据指定的或默认的排列函数，以关键字为索引，对其中的元素进行排序。

## 3.1 set容器

- 使用set容器必须#include <set>。

- 其使用形式如下：
  - set<存储类型[,排序函数或对象]> 容器对象名;
  - 第1个参数用以指定存储类型，第2个参数是可选的，用来指定对关键字进行排序的函数或函数对象(函数对象后面介绍)，在默认情况下，将使用less<>类模板，字面意义上可理解为按从小到大进行排列。可以自己设定排序方式：`set<int, greater<int>>`
  
- 根据set的特点，STL提供了3种创建set的方式：

  - 创建空set容器对象，如：`set<int> obS;`

  - 将迭代器的区间作为参数的构造函数，如：

  - ```cpp
    int sz[9]={1,2,3,4,5,6,3,5,6};
    set<int> A(sz,sz+9);
    ```

  - 根据已有同类型的容器创建新容器，如

  - ```cpp
    set<int> B(A);
    ```


- set不支持[]下标式的随机访问，必须通过迭代器访问元素。

```cpp
//set容器的使用: 关键字不允许重复，按照关键字排序
#include <iostream>
#include <set>							//使用set必须包括此头文件
using namespace std;

int main()
{
	int sz[9] = {2, 1, 3, 5, 4, 6, 3, 5, 6};	//定义int型数组，数组名相当于指针（迭代器）
	set<int> A(sz, sz + 9);				//将迭代器区间作为参数创建容器对象A
	cout << A.size() << endl;			//输出A中元素个数

	set<int>::iterator it = A.begin();	//创建set<int>::iterator迭代器it，指向A头部
	while (it != A.end())				//输出全部元素
	{
		cout << (*it) << "  ";
		it++;
	}
	cout << endl;

	getchar();
	return 0;
}
```



# 4. 无序关联式容器

# 5. 迭代器

# 6. 算法

# 7. 适配器

# 8。 空间配置器