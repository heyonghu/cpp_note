# 1. 程序的内存布局

1）栈区（stack）：由编译器自动分配释放 ，存放函数的参数值，局部变量的值等。其操作方式类似于数据结构中的栈；

2）堆区（heap）：一般由程序员分配释放，若程序员不释放，程序结束时可能由OS回收。注意它与数据结构中的堆是两回事，分配方式倒是类似于链表；

3）全局/静态区(static）：全局变量和静态变量的存储是放在一块的，在程序编译时分配；

4）文字常量区：存放常量字符串；

5）程序代码区：存放函数体（类的成员函数、全局函数）的二进制代码；

![image-20220710201233382](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220710201233382.png)

```cpp
int a = 0; //全局初始化区
char *p1;  //全局未初始化区
int main() {
    int b;                 //栈
    char s[] = "abc";    //栈
    char *p2;              //栈
    char *p3 = "123456"; //字符串位于常量区，p3位于栈
    static int c = 0;      //全局(静态)初始化区
    p1 = new char[10];     //p1位于全局区，p1指向的对象位于堆
    strcpy(p1, "123456");//
}
```

# 2. 栈与堆的比较

- 申请方式 

  - **stack**: 
    - 由系统自动分配。例如，声明在函数中一个局部变量int b; 系统自动在栈中为b开辟空间 

  - **heap**: 
    - 需要程序员自己申请，并指明大小，在c中malloc函数，如char* p1 = (char *)malloc(10); 
    - 在C++中用new运算符，如
    -  `int *p2 = new int (10);` 
    - 注意p1、p2本身是在栈中的。

- 申请后系统的响应 

  **栈**：只要栈的剩余空间大于所申请空间，系统将为程序提供内存，否则将报异常提示栈溢出。

  **堆**：首先应该知道操作系统有一个记录空闲内存地址的链表，当系统收到程序的申请时，会遍历该链表，寻找第一个空间大于所申请空间的堆结点，然后将该结点从空闲结点链表中删除，并将该结点的空间分配给程序。另外，对于大多数系统，首地址处会记录这块内存空间中本次分配的大小，这样，代码中的delete语句才能正确的释放本内存空间。另外，由于找到的堆结点的大小不一定正好等于申请的大小，系统会自动的将多余的那部分重新放入空闲链表中。

- 申请大小的限制

  - 栈：在Windows下,栈是向低地址扩展的数据结构，是一块连续的内存的区域。这句话的意思是栈顶的地址和栈的最大容量是系统预先规定好的，在WINDOWS下，栈的大小是2M（也有的说是1M，总之是一个编译时就确定的常数），如果申请的空间超过栈的剩余空间时，将提示overflow。因此，能从栈获得的空间较小。

  - 堆：堆是向高地址扩展的数据结构，是不连续的内存区域。这是由于系统是用链表来存储的空闲内存地址的，自然是不连续的，而链表的遍历方向是由低地址向高地址。。由此可见，堆获得的空间比堆的大小受限于计算机系统中有效的虚拟内存较灵活，也比较大。

- 申请效率的比较：

  - 栈由系统自动分配，速度较快。但程序员无法控制。

  - 堆是由new分配的内存，一般速度比较慢，而且容易产生内存碎片,不过用起来最方便。

- 堆和栈中的存储内容
  - 栈： 在函数调用时，第一个进栈的是主函数的下一条指令（函数调用语句的下一条可执行语句）的地址，然后是函数的各个参数，在大多数的C编译器中，参数是由右往左入栈的，然后是函数中的局部变量。注意静态变量是不入栈的。当本次函数调用结束后，局部变量先出栈，然后是参数，最后栈顶指针指向最开始存的地址，也就是主函数中的下一条指令，程序由该点继续运行。
  - 堆：一般是在堆的头部用一个字节存放堆的大小。堆中的具体内容由程序员安排。

# 3. 栈与堆小结

区别：

- 1) 管理方式不同； 

- 2. 空间大小不同； 

- 3) 能否产生碎片不同； 

- 4) 生长方向不同；

- 5) 分配方式不同； 

- 6) 分配效率不同；

区别：

- 1) 管理方式：对于栈来讲，是由编译器自动管理，无需我们手工控制；对于堆来说，释放工作由程序员控制，容易产生memory leak

- 2) 空间大小：一般来讲在32位系统下，堆内存可以达到4G的空间，从这个角度来看堆内存几乎是没有什么限制的。但是对于栈来讲，一般都是有一定的空间大小的，例如，在VC6下面，默认的栈空间大小是1M

- 3) 分配方式：堆都是动态分配的，没有静态分配的堆。内存有2种分配方式：静态分配和动态分配。静态分配是编译器完成的，比如局部变量的分配。动态分配由`malloc,calloc`函数进行分配，但是栈的动态分配和堆是不同的，他的动态分配是由编译器进行释放，无需我们手工实现。

- 4) 生长方向：对于堆来讲，生长方向是向上的，也就是向着内存地址增加的方向；对于栈来讲，它的生长方向是向下的，是向着内存地址减小的方向增长。

- 5) 碎片问题：对于堆来讲，频繁的new/ delete势必会造成内存空间的不连续，从而造成大量的碎片，使程序效率降低。对于栈来讲，则不会存在这个问题，因为栈是先进后出的，他们是如此的一一对应，以至于永远都不可能有一个内存块从栈中间弹出，在他弹出之前，在它上面的后进的栈内容已经被弹出

- 6) 生长方向：对于堆来讲，生长方向是向上的，也就是向着内存地址增加的方向；对于栈来讲，它的生长方向是向下的，是向着内存地址减小的方向增长。

# 4. new/delete

## 4.1 new/delete工作机制

- 使用new表达式时发生的三个步骤：

  - 1. 调用名为operator new的标准库函数，分配足够大的原始的未类型化的内存，以保存指定类型的一个对象

  - 2. 运行该类型的一个构造函数去初始化对象

  - 3. 返回指向新分配并构造的构造函数对象的指针

- 使用delete表达式时，发生的步骤：

  - 1. 调用对象的析构函数

  - 2. 调用名为operator delete的标准库函数释放该对象所用的内存

## 4.2 operator new/delete库函数

- operator new 和operator delete函数有两个重载版本

```cpp
  void * operator new (size_t);
  void * operator new[](size_t);


  void operator delete(void *);
  void operator delete[](void *);
```

## 4.3 只能生成栈对象 

- 只能生成栈对象，就是说不能生成堆对象，亦即不能通过new表达式[在类之外]生成对象

- 不能生成堆对象能想到的方法：

  - 将构造函数放入private区域

  - operator new函数 放入到private区域

```cpp
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class Student
{
public:
    int iId;
    char szName[10];
public:
    Student()    {
        std::cout << "Student 构造函数被调用" << std::endl;
    }

    ~Student()
    {
        std::cout << "Student 析构函数被调用" << std::endl;
    }

private:
    static void* operator new(std::size_t nSize);
    static void operator delete(void *pVoid);

/*    
    static void* operator new(std::size_t nSize)
    {
        std::cout << "new 操作符被调用, size = " << nSize << std::endl;
        //void *pRet = new char[nSize];
        void *pRet = malloc(nSize);
        return pRet;
    }
    static void operator delete(void *pVoid)
    {
        std::cout << "delete操作符被调用." << std::endl;
        free(pVoid);
    }
    */
};

int main(void)
{
    Student *pstu = new Student;
    pstu->iId = 101;
    strcpy(pstu->szName, "Tony");
    std::cout << std::endl;
    delete pstu;

    //std::cout << std::endl;
    //Teacher *pt = new Teacher();

    //delete pt;
    return 0;
}
```

## 4.4 只能生成堆对象

- 只能生成堆对象，就是说不能生成栈对象，亦即在创建栈对象时，不能[在类之外]调用构造函数或者析构函数

- 不能生成栈对象能想到的方法：

  - 将构造函数放到private区域

  - 将析构函数放到private区域

    - a)对于堆对象而言，执行delete表达式无法通过编译

    - b)在public区域定义一个destroy()

```cpp
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class Student
{
public:
    int iId;
    char szName[10];
public:
    Student()
    {
        std::cout << "Student 构造函数被调用" << std::endl;
    }

    void destroy()
    {
        //(*this).~Student();
        delete this;
    }

private://不能生成栈对象
    ~Student()
    {
        std::cout << "Student 析构函数被调用" << std::endl;
    }

};

class Teacher
{

};

int main(void)
{
    Student *pstu = new Student;
    pstu->iId = 101;
    strcpy(pstu->szName, "Tony");


    pstu->destroy();
    delete pstu;

    //Student stu;
    

    return 0;
}
```

