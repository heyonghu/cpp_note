- 智能指针(Smart Pointer)

  - 是存储指向动态分配（堆）对象指针的类

  - 在面对异常的时候格外有用，因为他们能够确保正确的销毁动态分配的对象

  - RAII类模拟智能指针，见备注

```cpp
1. 有问题的情况：
class Example {
  SomeResource* p_;
  SomeResource* p2_;	
public:
  Example() :
    p_(new SomeResource()),
    p2_(new SomeResource()) {
    std::cout << "Creating Example, allocating SomeResource!/n";
  }

  Example(const Example& other) :
    p_(new SomeResource(*other.p_)),
    p2_(new SomeResource(*other.p2_)) {}

  Example& operator=(const Example& other) {
    // Self assignment?
    if (this==&other)
      return *this;

    *p_=*other.p_;
    *p2_=*other.p2_;
    return *this;
  }

  ~Example() {
     std::cout << "Deleting Example, freeing SomeResource!/n";
     delete p_;
     delete p2_;
  }
};

2. RAII类
/**
**我们可以利用一个对象在离开一个域中会调用析构函数的特性，
**在构造函数中完成初始化，在析构函数中完成清理工作，将需要
**操作和保护的指针作为成员变量放入RAII中。
*/
template <typename T>
class RAII {
public:
  explicit RAII(T* p) : p_(p) {}

  ~RAII() {
    delete p_;
  }

  void reset(T* p) {
    delete p_;
    p_=p;
  }

  T* get() const {
     return p_;
  }



	

  T& operator*() const {
     return *p_;
  }

  void swap(RAII& other) {
    std::swap(p_,other.p_);
  }

private:
  RAII(const RAII& other);
  RAII& operator=(const RAII& other);
private:
  T* p_;
};

3. 不会出出内存泄露的情况

/*
** 现在即使p_成功而p2_失败，那么在Stack winding时也会调用
** RAII的析构函数保证了p_指向的Someresource被析构。
** Example中，已经不需要析构函数了
*/
class Example {
      RAII<SomeResource> p_;
      RAII<SomeResource> p2_;
public:
  Example()
    : p_(new SomeResource()),
      p2_(new SomeResource()) {}

  Example(const Example& other)
    : p_(new SomeResource(other.p_.get())),
      p2_(new SomeResource(other.p2_.get())) {}

  Example& operator=(const Example& other) {
    // Self assignment?
    if (this==&other)
      return *this;
#if 0
    *p_=*other.p_;
    *p2_=*other.p2_;
#endif

   p_.reset(other.p_.get());
   p2_.reset(other.p2_.get());    
return *this;
  }

  ~Example() {
    std::cout << "Deleting Example, freeing SomeResource!/n";
  }

private:
  RAII<SomeResource> p_;
  RAII<SomeResource> p2_;
};
```

- C++11提供了以下几种智能指针,位于头文件<memory>，它们都是类模板

  - `std::auto_ptr(复制/赋值) c++0x`

  - `std::unique_ptr c++11`

  - `std::shared_ptr c++11`

  - `std::weak_ptr  c++11`
  - `g++ -std=c++11 xx.cc`

# 1. 智能指针`std::auto_ptr`

- `std::auto_ptr`在构造时获取对某个对象的所有权(ownership),在析构时释放该对象

- `std::auto_ptr`要求其对“裸”指针的完全占有性à
  - 在拷贝构造或赋值操作时,会发生所有权的转移

- 本身存在缺陷

```cpp
#include <iostream>
#include <memory>

int main(void)
{
    double *pd = new double(77.77);
    std::auto_ptr<double> apd(pd);
    std::cout << "*apd = " << *apd << std::endl;
    //std::cout << "apd = " << apd << std::endl;
    std::cout << "apd.get() = " << apd.get() << std::endl;//get()方法返回auto_ptr对象中的基础指针


    int *pi = new int(7);
    std::auto_ptr<int> api_1(pi);
    std::auto_ptr<int> api_2(api_1);//进行复制的时候

    //std::cout << "*api_1 = " << *api_1 << std::endl;//Error,segment default
    std::cout << "*api_2 = " << *api_2 << std::endl;


    float *pf = new float(static_cast<float>(0.77));
    std::auto_ptr<float> apf;
    //apf = pf;
    apf.reset(pf);//只能调用reset方法来改变指针

    std::cout << "*apf = " << *apf << std::endl;

    return 0;
}
```

# 2. 智能指针`std::unique_ptr`

- `std::unique_ptr`是一个独享所有权的智能指针，它提供了一种严格语义上的 所有权，包括：

  - 拥有它所指向的对象

  - 无法进行复制、赋值操作

  - 保存指向某个对象的指针，当它本身被删除释放的时候，会使用给定的删除器释放它指向的对象

  - 具有移动(`std::move`)语义，可做为容器元素

```cpp
1.无法进行复制、赋值操作

  std::unique_ptr<int> ap(new int(88 );
  std::unique_ptr<int> one (ap) ; // 会出错
  std::unique_ptr<int> two = one; //会出错

2.可以进行移动构造和移动赋值操作
  unique_ptr<int> GetVal( ){
    unique_ptr<int> up(new int(88 );
    return up;
  }
 
  unique_ptr<int> uPtr = GetVal();   //ok

  实际上上面的的操作有点类似于如下操作
  unique_ptr<int> up(new int(88 );
  unique_ptr<int> uPtr2 = std::move(up) ; //这里是显式的所有权转移. 把up所指的内存转给uPtr2了,而up不再拥有该内存.

3.可做为容器元素
  unique_ptr<int> sp(new int(88));
  vector<unique_ptr<int> > vec;
  vec.push_back(std::move(sp));
  //vec.push_back( sp ); 这样不行,会报错的.
  //cout<<*sp<<endl;但这个也同样出错,说明sp添加到容器中之后,它自身报废了.
```

# 3. 智能指针`std::shared_ptr`

- `std::shared_ptr`是一个引用计数智能指针，用于共享对象的所有权

  - 1.引进了一个计数器shared_count,用来表示当前有多少个智能指针对象共享指针指向的内存块

  - 2.析构函数中不是直接释放指针对应的内存块,如果**shared_count****大于****0**则不释放内存只是将引用计数减1,只有计数等于0时释放内存

  - 3.复制构造与赋值操作符只是提供一般意义上的复制功能,并且将引用计数加1.

- 问题：循环引用

```cpp
问题：循环引用－－无法释放对象，造成内存泄露
#include <iostream>
#include <memory>

class Parent;
class Child;

typedef std::shared_ptr<Parent> parent_ptr;
typedef std::shared_ptr<Child> child_ptr;

class Child
{
public:
    Child() {   std::cout << "Child..." << std::endl;   }
    ~Child() {  std::cout << "~Child..." << std::endl;  }
    parent_ptr parent_;
};

class Parent
{
public:
    Parent() {  std::cout << "Parent..." << std::endl;  }
    ~Parent() { std::cout << "~Parent..." << std::endl; }
    child_ptr child_;
};

int main(void)
{
    parent_ptr parent(new Parent);
    child_ptr child(new Child);
    parent->child_ = child;
    //parent.operator->()->child_ = child;
    child->parent_ = parent;

    return 0;
}
```

# 4. 智能指针`std::weak_ptr`

- `std::shared_ptr`是强引用智能指针

- `std::weak_ptr`是弱引用智能指针

- 强引用，只要有一个引用存在，对象就不能被释放

- 弱引用，并不增加对象的引用计数，但它知道对象是否存在。
  - 如果存在，提升为`shared_ptr`成功；否则，提升失败

- 通过`weak_ptr`访问对象的成员的时候，要提升为`shared_ptr`

```cpp
1.通过弱引用来解决std::shared_ptr的循环引用问题

#include <iostream>
#include <memory>

class Parent;
class Child;

typedef std::shared_ptr<Parent> parent_ptr;
typedef std::shared_ptr<Child> child_ptr;

class Child
{
public:
    Child() {   std::cout << "Child..." << std::endl;   }
    ~Child() {  std::cout << "~Child..." << std::endl;  }
    parent_ptr parent_;
};

class Parent
{
public:
    Parent() {  std::cout << "Parent..." << std::endl;  }
    ~Parent() { std::cout << "~Parent..." << std::endl; }
    std::weak_ptr<Child> child_;
};

int main(void)
{
    parent_ptr parent(new Parent);
    child_ptr child(new Child);
    parent->child_ = child;
    child->parent_ = parent;

    return 0;
}

2. weak_ptr的使用

#include <iostream>
#include <memory>

class X
{
public:
    X() {   std::cout << "construct X" << std::endl;    }
    ~X() {  std::cout << "~destruct X" << std::endl;    }
    void Fun()
    {
        std::cout << "Fun() " << std::endl;
    }
};
int main(void)
{
    std::weak_ptr<X> p;
    {
        std::shared_ptr<X> p2(new X);
        std::cout << p2.use_count() << std::endl;

        p = p2;
        std::cout << "after p = p2" << std::endl;
        std::cout << p2.use_count() << std::endl;

        std::shared_ptr<X> p3 = p.lock();//提升成功
        if(!p3)
        {
            std::cout << "object is destroyed" << std::endl;
        }
        else
        {
            p3->Fun();
            std::cout << p3.use_count() << std::endl;
        }
    }
    //new X 已经被释放了
    std::shared_ptr<X> p4 = p.lock();//提升失败
    if(!p4)
        std::cout << "object is destroyed 2" << std::endl;
    else
        p4->Fun();

    return 0;
}
```

- `shared_ptr`的误用

- 删除器

- `class std::enable_shared_from_this`
  - 方法shared_from_this()

```cpp
1. shared_ptr的误用
1.1
	Point *pt = new Point(1,2);
	std::shared_ptr<Point> p1(pt);//在类之外对对象进行托管
	std::shared_ptr<Point> p2(pt);

1.2 

int main()
{
	//...
	shared_ptr<Point> p1(new Point(1, 2));
	shared_ptr<Point> p2(new Point(3, 4));
	p2.reset(p1.get());
	//...
	
}


2. deleter

struct fpcloser
{
	void operator()(FILE *fp)
	{
		if(fp)
		{
			std::cout << "fpcloser()" << std::endl;
			fclose(fp);
		}
	}
};


unique_ptr<FILE, fpcloser> up(fopen(“readme.txt”, “r”), fpcloser());

shared_ptr<Test> sp(new Test, Deleter());



3. enable_shared_from_this


	Point * add(const Point *rhs)
	{
		ix_ += rhs->ix_;
		iy_ += rhs->iy_;
		return this;
	}

	std::shared_ptr<Point> add(const Point * rhs)
	{
		ix_ += rhs->ix_;
		iy_ += rhs->iy_;
		//return std::shared_ptr<Point>(this);//版本一
		return shared_from_this();//发生在类内部，通过对this进行托管（版本二)
	}

int main()
{
	//...
	p2.swap(p1->add(p2.get()));
}
```

