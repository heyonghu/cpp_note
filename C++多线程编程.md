# C语言多线程

## API

### 线程创建

- 函数原型：

```cpp
int pthread_create(
    pthread_t *restrict tidp,
    const pthread_attr_t *restrict attr,
    void *(*start_rtn)(void),
    void *restrict arg
);
```

- 返回值：若是成功建立线程返回0，否则返回错误的编号。

- 形式参数：

```cpp
pthread_t *restrict tidp // 要创建的线程的线程id指针；
const pthread_attr_t *restrict attr  // 创建线程时的线程属性；
void *(start_rtn)(void)  // 返回值是void类型的指针函数；
void *restrict arg   // start_rtn的形参。
```

### 线程挂起

该函数的作用使得当前线程挂起，等待另一个线程返回才继续执行。也就是说当程序运行到这个地方时，程序会先停止，然后等线程id为thread的这个线程返回，然后程序才会断续执行。

- 函数原型：

```cpp
int pthread_join(pthread_t thread, void **value_ptr);
```

- 形参：参数说明如下：thread等待退出线程的线程号；value_ptr退出线程的返回值。

- 返回值：若成功，则返回0；若失败，则返回错误号。

### 线程退出

- 函数原型：

```cpp
void pthread_exit(void *rval_ptr);
```

### 获取当前线程id

- 函数原型

```cpp
pthread_t pthread_self(void);
```

### 互斥锁

```cpp
创建 pthread_mutex_init；
销毁 pthread_mutex_destroy；
加锁 pthread_mutex_lock；
解锁 pthread_mutex_unlock;
```

### 条件锁

```cpp
创建 pthread_cond_init；
销毁 pthread_cond_destroy；
触发 pthread_cond_signal；
广播 pthread_cond_broadcast；
等待 pthread_cond_wait。
```

## pthread_create

- 头文件
  　　#include<pthread.h>
- 函数声明
  　　int pthread_create(pthread_t*restrict tidp,const pthread_attr_t *restrict_attr,void*（*start_rtn)(void*),void *restrict arg);
- 返回值
  　　若成功则返回0，否则返回出错编号
    　　返回成功时，由tidp指向的内存单元被设置为新创建线程的线程ID。attr参数用于制定各种不同的线程属性。新创建的线程从start_rtn函数的地址开始运行，该函数只有一个万能指针参数arg，如果需要向start_rtn函数传递的参数不止一个，那么需要把这些参数放到一个结构中，然后把这个结构的地址作为arg的参数传入。
    　　linux下用C开发多线程程序，Linux系统下的多线程遵循POSIX线程接口，称为pthread。
    　　由 restrict 修饰的指针是最初唯一对指针所指向的对象进行存取的方法，仅当第二个指针基于第一个时，才能对对象进行存取。对对象的存取都限定于基于由 restrict 修饰的指针表达式中。 由 restrict 修饰的指针主要用于函数形参，或指向由 malloc() 分配的内存空间。restrict 数据类型不改变程序的语义。 编译器能通过作出 restrict 修饰的指针是存取对象的唯一方法的假设，更好地优化某些类型的例程。
- 参数
  　　第一个参数为指向线程标识符的指针。
    　　第二个参数用来设置线程属性。
    　　第三个参数是线程运行函数的起始地址。
    　　最后一个参数是运行函数的参数。
    　　另外，在编译时注意加上-lpthread参数，以调用静态链接库。因为pthread并非Linux系统的默认库



## pthread_join

函数pthread_join用来等待一个线程的结束,线程间同步的操作。

- 头文件 ： #include <pthread.h>

- 函数定义： int pthread_join(pthread_t thread, void **retval);

- 描述 ：pthread_join()函数，以阻塞的方式等待thread指定的线程结束。当函数返回时，被等待线程的资源被收回。如果线程已经结束，那么该函数会立即返回。并且thread指定的线程必须是joinable的。

- 参数 ：
  - thread: 线程标识符，即线程ID，标识唯一线程。
  - retval: 用户定义的指针，用来存储被等待线程的返回值。

- 返回值 ： 0代表成功。 失败，返回的则是错误号。

## 入门样例

CMakeLists.txt

```cpp
cmake_minimum_required(VERSION 3.22)
project(C_thread)

set(CMAKE_CXX_STANDARD 17)

add_executable(C_thread
        # main01.c
        # test01.cpp
        # test02.cpp
        # main02.c
        # main03.c
        # main04.c
        main05.c)
find_package(Threads)
target_link_libraries(C_thread ${CMAKE_THREAD_LIBS_INIT})
```

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *myfunc(void *args) {
    int i;
    for (i = 1; i < 1000; i++) {
        printf("%d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t th1;
    pthread_t th2;

    pthread_create(&th1, NULL, myfunc, NULL);
    pthread_create(&th2, NULL, myfunc, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}
```

```cpp
//
// Created by heyonghu on 22-5-5.
//
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

void *myfunc(void *args) {
    int i;
    char *name = (char *) args;
    for (i = 1; i < 1000; i++) {
        printf("%s: %d\n", name, i);
    }
    return NULL;
}

int main() {
    pthread_t th1;
    pthread_t th2;

    pthread_create(&th1, NULL, myfunc, "th1");
    pthread_create(&th2, NULL, myfunc, "th2");

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}
```

```cpp
//
// Created by heyonghu on 22-5-5.
//
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "time.h"
int array[5000];
typedef struct {
    int first;
    int second;
    int result;
} my_args;

void *myfunc(void *args) {
    int i;
    my_args *ar1 = (my_args *) args;
    int s = 0;
    for (i = ar1->first; i < ar1->second; i++) {
        s += array[i];
    }
    ar1->result = s;
    return NULL;
}

int main() {
    int x1 = 0, x2 = 0;
    srand((int)time(0));
    for (int i = 0; i < 5000; ++i) {
        array[i] = rand() % 50;
    }
    my_args m1 = {0, 2500, 0};
    my_args m2 = {2500, 5000, 0};
    pthread_t th1;
    pthread_t th2;

    pthread_create(&th1, NULL, myfunc, &m1);
    pthread_create(&th2, NULL, myfunc, &m2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("s1 = %d\ns2 = %d\ns1 + s2 = %d\n", m1.result, m2.result, m1.result + m2.result);
    return 0;
}
```

```cpp
//
// Created by heyonghu on 22-5-5.
//
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "time.h"

pthread_mutex_t lock;
int s = 0;

void *myfunc(void *args) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < 10000000; ++i) {
        s++;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t th1;
    pthread_t th2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&th1, NULL, myfunc, NULL);
    pthread_create(&th2, NULL, myfunc, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("%d\n", s);
    return 0;
}
```

```cpp
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

#define MAX_SIZE 50000000
typedef struct {
    int first;
    int last;
    int id;
} MY_ARGS;
int *arr;
int results[2];

void *myfunc(void *args) {
    int i;
    MY_ARGS *my_args = (MY_ARGS *) args;
    int first = my_args->first;
    int last = my_args->last;
    int id = my_args->id;
    for (i = first; i < last; i++) {
        results[id] += arr[i];
    }
    return NULL;
}

int main() {
    int i;
    arr = malloc(sizeof(int) * MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; ++i) {
        arr[i] = rand() % 5;
    }
    results[0] = 0;
    results[1] = 0;

    pthread_t th1;
    pthread_t th2;

    int mid = MAX_SIZE / 2;

    MY_ARGS args1 = {0, mid, 0};
    MY_ARGS args2 = {mid, MAX_SIZE, 1};

    pthread_create(&th1, NULL, myfunc, &args1);
    pthread_create(&th2, NULL, myfunc, &args2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("s1 = %d\n", results[0]);
    printf("s2 = %d\n", results[1]);
    printf("s1+ s2 = %d\n", results[0] + results[1]);
    return 0;
}
```

## 伪共享(false sharing)问题分析

# C++多线程

```cpp
# 用来查看当前线程的id
thread::get_id()
    
# 检查此线程是否还和主线程连接（已经完成join、detach的线程都是false）
thread：：joinable()
    
# 将线程与主线程的连接切断，并且此线程会继续独立执行下去，直到执行结束时候释放分配的资源
thread::detach()
    
# 交换两个线程
thread::swap()
    
#############################################################
std::this_thread 命名空间（Namespace）
    
# 查看当前线程的id
this_thread::get_id()
    
# 暂时中断此线程，OS会调用其他线程执行
this_thread::yield()
    
# 设定一个时间，让此线程在指定的时刻后再继续执行
this_thread::sleep_until()
    
# 暂时中断此线程，等待指定的一段时间后才会被执行
this_thread::sleep_for()
```



## API

### 构造函数

```cpp
thread() noexcept;

thread( thread&& other ) noexcept;

template< class Function, class... Args >
explicit thread( Function&& f, Args&&... args );

thread( const thread& ) = delete;
```

- 形参

```cpp
other	//	另一个线程对象来构造这个线程对象
f	//	在新线程中执行的可调用对象
args...	//	传递给新函数的参数
```

```cpp
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>

void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 1 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

class foo
{
public:
    void bar()
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread 3 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};

class baz
{
public:
    void operator()()
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread 4 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};

int main()
{
    int n = 0;
    foo f;
    baz b;
    std::thread t1; // t1 is not a thread
    std::thread t2(f1, n + 1); // pass by value
    std::thread t3(f2, std::ref(n)); // pass by reference
    std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
    std::thread t5(&foo::bar, &f); // t5 runs foo::bar() on object f
    std::thread t6(b); // t6 runs baz::operator() on a copy of object b
    t2.join();
    t4.join();
    t5.join();
    t6.join();
    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of f.n (foo::n) is " << f.n << '\n';
    std::cout << "Final value of b.n (baz::n) is " << b.n << '\n';
}
```



### std::thread::joinable

```cpp
bool joinable() const noexcept;
```

检查 std::thread 对象是否标识了一个活动的执行线程。 具体来说，如果 get_id() != std::thread::id() 则返回 true，所以默认构造的线程是不可连接的。

已完成执行代码但尚未加入的线程仍被视为正在执行的活动线程，因此是可加入的。

- return

  如果线程对象标识了一个活动的执行线程，则为 true，否则为 false

```cpp
#include <iostream>
#include <thread>
#include <chrono>

void foo() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    std::thread t;
    // std::boolalpha : 让输出流将bool解析成为true或者 false。
    std::cout << "before starting, joinable: " << std::boolalpha << t.joinable() << '\n'; // false

    t = std::thread(foo);
    std::cout << "after starting, joinable: " << t.joinable() << '\n'; // true

    t.join();
    std::cout << "after joining, joinable: " << t.joinable() << '\n'; // false
    return 1;
}
```

### std::thread::get_id

```cpp
std::thread::id get_id() const noexcept;
```

返回标识与 *this 关联的线程的 std::thread::id 值。

- return
  一个 std::thread::id 类型的值，标识与 *this 关联的线程。 如果没有关联线程，则返回默认构造的 std::thread::id。

```cpp
#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    std::thread t1(foo);
    std::thread::id t1_id = t1.get_id();

    std::thread t2(foo);
    std::thread::id t2_id = t2.get_id();

    std::cout << "t1's id: " << t1_id << '\n'; // t1's id: 140474601842432
    std::cout << "t2's id: " << t2_id << '\n'; // t2's id: 140474593449728

    t1.join();
    t2.join();
}
```

### std::thread::native_handle

```cpp
native_handle_type native_handle();
```

返回实现定义的底层线程句柄。

- return

  返回 实现定义的底层线程句柄

```cpp
#include <iostream>
#include <thread>
#include <ctime>
using namespace std;
void show(int n){
    cout<<"n="<<n<<endl; // n=18
}
int main()
{
    thread t(show,18);
    cout<<"t.get_id="<<t.get_id()<<endl; // t.get_id=140648545146624
    auto tn=t.native_handle();
    t.join();
    cout<<"tn="<<tn<<endl; // tn=140648545146624
}
```

### std::thread::hardware_concurrency

```cpp
static unsigned int hardware_concurrency() noexcept;
```

返回实现支持的并发线程数。 该值应仅被视为一个提示。

- return

​	支持的并发线程数。 如果值定义不明确或不可计算，则返回0。

```cpp
#include <iostream>
#include <thread>

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n"; // 4 concurrent threads are supported.
}
```

### std::thread::join

```cpp
void join();
```

阻塞当前线程，直到 *this 标识的线程完成执行。
由 *this 标识的线程的完成与 join() 的相应成功返回同步。
*this 本身不执行同步。 从多个线程同时在同一个线程对象上调用 join() 构成了导致未定义行为的数据竞争。

- Parameters

​	(none)

- Return value

​	(none)

```cpp
#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "foo doing\n";
}

void bar()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "bar doing\n";
}

int main()
{
    std::cout << "starting first helper...\n";
    std::thread helper1(foo);

    std::cout << "starting second helper...\n";
    std::thread helper2(bar);

    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();

    std::cout << "done!\n";
}
/*
starting first helper...
starting second helper...
waiting for helpers to finish...
foo doing
bar doing
done!
 * */

```

### std::thread::detach

```cpp
void detach();
```

将执行线程与线程对象分离，允许执行独立继续。 一旦线程退出，任何分配的资源都将被释放。
调用 detach *this 后不再拥有任何线程。

```cpp
#include <iostream>
#include <chrono>
#include <thread>

void independentThread()
{
    std::cout << "Starting concurrent thread.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Exiting concurrent thread.\n";
}

void threadCaller()
{
    std::cout << "Starting thread caller.\n";
    std::thread t(independentThread);
    t.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Exiting thread caller.\n";
}

int main()
{
    threadCaller();
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
/*

Starting thread caller.
Starting concurrent thread.
Exiting thread caller.
Exiting concurrent thread.
 * */
```

### std::thread::swap

交换两个线程对象的基础句柄。

- 形式参数
other  - 要与之交换的线程

```cpp
#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    std::thread t1(foo);
    std::thread t2(bar);

    std::cout << "thread 1 id: " << t1.get_id() << '\n'
              << "thread 2 id: " << t2.get_id() << '\n';

    std::swap(t1, t2);

    std::cout << "after std::swap(t1, t2):" << '\n'
              << "thread 1 id: " << t1.get_id() << '\n'
              << "thread 2 id: " << t2.get_id() << '\n';

    t1.swap(t2);

    std::cout << "after t1.swap(t2):" << '\n'
              << "thread 1 id: " << t1.get_id() << '\n'
              << "thread 2 id: " << t2.get_id() << '\n';

    t1.join();
    t2.join();
}

/*
thread 1 id: 140427419838208
thread 2 id: 140427411445504
after std::swap(t1, t2):
thread 1 id: 140427411445504
thread 2 id: 140427419838208
after t1.swap(t2):
thread 1 id: 140427419838208
thread 2 id: 140427411445504
 * */
```

