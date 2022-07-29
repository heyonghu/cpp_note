# 1. 输入输出机制

## 1.1 输入输出的含义

- 以前所用到的输入和输出，都是以终端为对象的，即从键盘输入数据，运行结果输出到显示器屏幕上。

- 从操作系统的角度看，每一个与主机相连的输入输出设备都被看作一个文件。除了以终端为对象进行输入和输出外，还经常用磁盘(光盘)作为输入输出对象，磁盘文件既可以作为输入文件，也可以作为输出文件。

- 程序的输入指的是从输入文件将数据传送给程序。

- 程序的输出指的是从程序将数据传送给输出文件。

## 1.2 C++的输入输出机制

C++的输入与输出包括以下3方面的内容:

（1） 对系统指定的标准设备的输入和输出。即从键盘输入数据，输出到显示器屏幕。这种输入输出称为标准的输入输出，简称标准I/O。

（2） 以外存磁盘文件为对象进行输入和输出，即从磁盘文件输入数据，数据输出到磁盘文件。以外存文件为对象的输入输出称为文件的输入输出，简称文件I/O。

（3） 对内存中指定的空间进行输入和输出。通常指定一个字符数组作为存储空间(实际上可以利用该空间存储任何信息)。这种输入和输出称为字符串输入输出，简称串I/O。

C++采取不同的方法来实现以上3种输入输出。

为了实现数据的有效流动，C++系统提供了庞大的I/O类库，称为流类库，调用不同的类去实现不同的功能。

```cpp
1.Example
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int test0(void)
{
    std::ifstream ifs(“io1.cc”);//定义并打开了一个ifstream对象
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    //std::string s;
    //while(ifs >> s)
    //{
    //    std::cout << s <<std::endl;
    //}

    std::vector<std::string> vec_str;
    std::string line;
    while(getline(ifs, line))
    {
        //std::cout << line << std::endl;
        vec_str.push_back(line);
    }

    std::vector<std::string>::iterator sit = vec_str.begin();
    for(; sit != vec_str.end(); ++sit)
    {
        std::cout << *sit << std::endl;
    }
    ifs.close();

    return 0;
}

int main(void)
{
    
    std::ifstream ifs("io1.cc");
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    std::ofstream ofs("test.txt");
    std::string line;
    while(getline(ifs, line))
    {
        ofs << line << std::endl;
    }
    return 0;
}
```

## 

## 1.3 C++的I/O对C的发展

- 类型安全

在C语言中，用`printf`和`scanf`进行输入输出，往往不能保证所输入输出的数据是可靠的、安全的。

在C++的输入输出中，编译系统对数据类型进行严格的检查，凡是类型不正确的数据都不可能通过编译。因此C++的I/O操作是类型安全`(type safe)`的。

- 可扩展性

C++的I/O操作是可扩展的，不仅可以用来输入输出标准类型的数据，也可以用于用户自定义类型的数据。C++对标准类型的数据和对用户声明类型数据的输入输出，采用同样的方法处理。

```cpp
1.Example
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int test0(void)
{
    std::ifstream ifs(“io1.cc”);//定义并打开了一个ifstream对象
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    //std::string s;
    //while(ifs >> s)
    //{
    //    std::cout << s <<std::endl;
    //}

    std::vector<std::string> vec_str;
    std::string line;
    while(getline(ifs, line))
    {
        //std::cout << line << std::endl;
        vec_str.push_back(line);
    }

    std::vector<std::string>::iterator sit = vec_str.begin();
    for(; sit != vec_str.end(); ++sit)
    {
        std::cout << *sit << std::endl;
    }
    ifs.close();

    return 0;
}

int main(void)
{
    
    std::ifstream ifs("io1.cc");
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    std::ofstream ofs("test.txt");
    std::string line;
    while(getline(ifs, line))
    {
        ofs << line << std::endl;
    }

    return 0;

}
```

# 2. 流类库

- 流的概念：

   可以把流看做“水管”，这样输入流指的是从程序外部输入数据，类似于水通过水管流进程序，输出流恰好相反，是从程序内部输出到外部。这里要注意的是，输入输出的参照物是程序。 

- 关于“流”，可以学院派地解释为“流是（表达）读写数据的一种可移植的方法，它为一般的I/O操作提供了灵活有效的手段。一个流是一个由指针操作的文件或者是一个物理设备，而这个指针正是指向了这个流。”

- 就C++程序而言， I/O操作可以简单地看作是从程序移进或移出字节，这种搬运的过程便称为流(stream)。程序只需要关心是否正确地输出了字节数据，以及是否正确地输入了要读取字节数据，特定I/O设备的细节对程序员是隐藏的。

## 2.1 流类库层次

iostream库主要包括如下图所示的几个头文件，在前面所有示例代码中使用的头文件`<iostream>`便是其中之一;

![image-20220713210022782](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220713210022782.png)

## 2.2 iostream继承层次

![image-20220713210110824](C:\Users\86353\AppData\Roaming\Typora\typora-user-images\image-20220713210110824.png)

## 2.3 流的分类

在C++中，输入输出流被定义为类。C++的I/O库中的类称为流类(stream class)。用流类定义的对象称为流对象。

1. 标准输入输出流 -- 头文件`<iostream>`

 `cin/cout/cerr` -- 对象

2. 文件输入输出流 -- 头文件`<fstream>`

  `ifstream/ofstream/fstream` -->类

3. 字符串流 -- 头文件`<sstream>`

  `istringstream/ostringstream/stringstream` --> 类

# 3. 标准输入输出流

## 3.1 标准输出流

`ostream`类定义了3个输出流对象，即`cout,cerr,clog,`平常用的最多的就是`cout`

- `cout`流对象

  - `cout`是console output的缩写，意为在控制台的输出。

  - (1) `cout`不是C++预定义的关键字，它是`ostream`流类的对象，在iostream中定义。

  -  (2) 用`“cout<<”`输出基本类型的数据时，可以不必考虑数据是什么类型，系统会判断数据的类型，并根据其类型选择调用与之匹配的运算符重载函数。

  -  (3) `cout`流在内存中对应开辟了一个缓冲区，用来存放流中的数据，当向`cout`流插入一个`endl`时，不论缓冲区是否已满，都立即输出流中所有数据，然后插入一个换行符，并刷新流(清空缓冲区)。

```cpp
1.Example
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int test0(void)
{
    std::ifstream ifs(“io1.cc”);//定义并打开了一个ifstream对象
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    //std::string s;
    //while(ifs >> s)
    //{
    //    std::cout << s <<std::endl;
    //}

    std::vector<std::string> vec_str;
    std::string line;
    while(getline(ifs, line))
    {
        //std::cout << line << std::endl;
        vec_str.push_back(line);
    }

    std::vector<std::string>::iterator sit = vec_str.begin();
    for(; sit != vec_str.end(); ++sit)
    {
        std::cout << *sit << std::endl;
    }
    ifs.close();

    return 0;
}

int main(void)
{
    
    std::ifstream ifs("io1.cc");
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    std::ofstream ofs("test.txt");
    std::string line;
    while(getline(ifs, line))
    {
        ofs << line << std::endl;
    }

    return 0;

}
```

## 3.2 标准输入流

- `cin`流对象

  `cin`是`istream`类的对象，它从标准输入设备(键盘)获取数据，程序中的变量通过流提取符“>>”从流中提取数据。流提取符“>>”从流中提取数据时通常跳过输入流中的空格、tab键、换行符等空白字符。 

- 注意: 只有在输入完数据再按回车键后，该行数据才被送入键盘缓冲区，形成输入流，提取运算符“>>”才能从中提取数据。需要注意保证从流中读取数据能正常进行。

```cpp
1.Example
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int test0(void)
{
    std::ifstream ifs(“io1.cc”);//定义并打开了一个ifstream对象
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    //std::string s;
    //while(ifs >> s)
    //{
    //    std::cout << s <<std::endl;
    //}

    std::vector<std::string> vec_str;
    std::string line;
    while(getline(ifs, line))
    {
        //std::cout << line << std::endl;
        vec_str.push_back(line);
    }

    std::vector<std::string>::iterator sit = vec_str.begin();
    for(; sit != vec_str.end(); ++sit)
    {
        std::cout << *sit << std::endl;
    }
    ifs.close();

    return 0;
}

int main(void)
{
    
    std::ifstream ifs("io1.cc");
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    std::ofstream ofs("test.txt");
    std::string line;
    while(getline(ifs, line))
    {
        ofs << line << std::endl;
    }

    return 0;

}
```

## 3.3 用于字符输入的流成员函数

- 除了可以用`cin`输入标准类型的数据外，还可以用`istream`类流对象的一些成员函数，实现字符的输入。

  - 1. 用get函数读入一个字符

       流成员函数get有3种形式: 无参数的，有一个参数的，有3个参数的。

    - (1) 不带参数的get函数

      其调用形式为`cin.get()`用来从指定的输入流中提取一个字符，函数的返回值就是读入的字符。若遇到输入流中的文件结束符，则函数值返回文件结束标志EOF(End Of File) 。

```cpp
1.Example
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int test0(void)
{
    std::ifstream ifs(“io1.cc”);//定义并打开了一个ifstream对象
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    //std::string s;
    //while(ifs >> s)
    //{
    //    std::cout << s <<std::endl;
    //}

    std::vector<std::string> vec_str;
    std::string line;
    while(getline(ifs, line))
    {
        //std::cout << line << std::endl;
        vec_str.push_back(line);
    }

    std::vector<std::string>::iterator sit = vec_str.begin();
    for(; sit != vec_str.end(); ++sit)
    {
        std::cout << *sit << std::endl;
    }
    ifs.close();

    return 0;
}

int main(void)
{
    
    std::ifstream ifs("io1.cc");
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    std::ofstream ofs("test.txt");
    std::string line;
    while(getline(ifs, line))
    {
        ofs << line << std::endl;
    }

    return 0;

}
```

Example 用get函数读入字符。

```cpp
#include <iostream>
int main( ) {
  int c;
  cout << “enter a sentence:” << endl;
  while((c=cin.get()) != EOF)
  cout.put(c);
  return 0;
}
```

运行情况如下: 

`enter a sentence:`

`I study C++ very hard.` (输入一行字符)

`I study C++ very hard. `      (输出该行字符)

C语言中的`getchar`函数与流成员函数`cin.get( )`的功能相同，C++保留了C的这种用法。

  - (2) 有一个参数的get函数

​	其调用形式为` cin.get(ch)`

​	其作用是从输入流中读取一个字符，赋给字符变量ch。如果读取成功则函数返回非0值(真)，如失败(遇文件结束符) 则函数返回0值(假)。前面的例子可以改写如下:

```cpp
#include <iostream>
int main( ) { 
	char c;
 	cout<<″enter a sentence:″<<endl;
 	while(cin.get(c))  //读取一个字符赋给字符变量c，如果读取成功，
		{    cout.put(c);     }      // cin.get(c)为真
 	cout<<″end″<<endl;
 	return 0;
	}
```

```cpp
1.Example
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int test0(void)
{
    std::ifstream ifs(“io1.cc”);//定义并打开了一个ifstream对象
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    //std::string s;
    //while(ifs >> s)
    //{
    //    std::cout << s <<std::endl;
    //}

    std::vector<std::string> vec_str;
    std::string line;
    while(getline(ifs, line))
    {
        //std::cout << line << std::endl;
        vec_str.push_back(line);
    }

    std::vector<std::string>::iterator sit = vec_str.begin();
    for(; sit != vec_str.end(); ++sit)
    {
        std::cout << *sit << std::endl;
    }
    ifs.close();

    return 0;
}

int main(void)
{
    
    std::ifstream ifs("io1.cc");
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    std::ofstream ofs("test.txt");
    std::string line;
    while(getline(ifs, line))
    {
        ofs << line << std::endl;
    }

    return 0;

}
```

- 2. 用成员函数`getline`函数读入一行字符

`getline`函数的作用是从输入流中读取一行字符，其用法与带3个参数的get函数类似。即

` getline(char * s，int n，char delim)`

Example 用`getline`函数读入一行字符。

```cpp
int main( ){
  char ch[20];
  cout << “enter a sentence:” << endl;
  cin >> ch;
  cout << “The string read with cin is:” << ch << endl;
  cin.getline(ch, 20, '/');//读19个字符或遇′/′结束
  cout << “The second part is:” << ch << endl;
  cin.getline(ch,20);                //读19个字符或遇′/n′结束
  cout << “The third part is:” << ch << endl;
  return 0;
}
```

```cpp
1.Example
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int test0(void)
{
    std::ifstream ifs(“io1.cc”);//定义并打开了一个ifstream对象
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    //std::string s;
    //while(ifs >> s)
    //{
    //    std::cout << s <<std::endl;
    //}

    std::vector<std::string> vec_str;
    std::string line;
    while(getline(ifs, line))
    {
        //std::cout << line << std::endl;
        vec_str.push_back(line);
    }

    std::vector<std::string>::iterator sit = vec_str.begin();
    for(; sit != vec_str.end(); ++sit)
    {
        std::cout << *sit << std::endl;
    }
    ifs.close();

    return 0;
}

int main(void)
{
    
    std::ifstream ifs("io1.cc");
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    std::ofstream ofs("test.txt");
    std::string line;
    while(getline(ifs, line))
    {
        ofs << line << std::endl;
    }

    return 0;

}
```

## 3.4 流的状态

- 流的状态：

  - `badbit`  系统级故障，不可恢复

  - `failbi`t   可以恢复的错误

  - `eofbit`  碰到了文件结尾

  - `goodbit` 有效状态 

- 查询流的状态

  - `cin.bad()`

  - `cin.fail()`

  - `cin.eof()`

  - `cin.good()`

- 重置流的状态 `cin.clear()`

- 清空缓冲区   `cin.ignore(1024, '\n')`

```cpp
1. 示例一
#include <iostream>
#include <string>

void printCin()
{
    std::cout << "bad = " << std::cin.bad() << std::endl;
    std::cout << "fail = " << std::cin.fail() << std::endl;
    std::cout << "eof = " << std::cin.eof() << std::endl;
    std::cout << "good = " << std::cin.good() << std::endl
              << std::endl;
}

int main(void)
{
    int inum;
    printCin();
    
    while(std::cin >> inum)
    {
        std::cout << inum << std::endl;
    }

    printCin();

    std::cin.clear();
    printCin();
    //std::cin.ignore(1024, '\n');

    std::string s;
    std::cin >> s;
    std::cout << s << std::endl;

    return 0;
}

2.示例二
#include <iostream>

int main()
{
    int ival;
    while(std::cin >> ival, !std::cin.eof())
    {
        if(std::cin.bad())
        {
            std::cout << "IO stream corrupted! " << std::endl;
            return -1;
        }
        if(std::cin.fail())
        {
            std::cout << "data illegal, try again!" << std::endl;
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            continue;
        }
        std::cout << "ival = " << ival << std::endl;
    }

    return 0;
}
```

# 4. 文件输入输出流

- 文件的概念

所谓“文件”，一般指存储在外部介质上数据的集合。一批数据是以文件的形式存放在外部介质上的。操作系统是以文件为单位对数据进行管理的。要向外部介质上存储数据也必须先建立一个文件（以文件名标识），才能向它输出数据。

- 外存文件包括磁盘文件、光盘文件和U盘文件。目前使用最广泛的是磁盘文件。

- 对用户来说，常用到的文件有两大类，一类是程序文件(program file)。一类是数据文件(data file)。程序中的输入和输出的对象就是数据文件。

- 根据文件中数据的组织形式，可分为ASCII文件和二进制文件。

## 4.1 文件流类与文件流对象

- 文件流是以外存文件为输入输出对象的数据流。输出文件流是从内存流向外存文件的数据，输入文件流是从外存文件流向内存的数据。每一个文件流都有一个内存缓冲区与之对应。

- 请区分文件流与文件的概念。文件流本身不是文件，而只是以文件为输入输出对象的流。若要对磁盘文件输入输出，就必须通过文件流来实现。

- 在C++的I/O类库中定义了几种文件类，专门用于对磁盘文件的输入输出操作。

## 4.2 文件输入输出流 `<fstream>`

(1) ifstream类，它是从istream类派生的，用来支持从磁盘文件的输入。

(2) ofstream类，它是从ostream类派生的，用来支持向磁盘文件的输出。

(3) fstream类，它是从iostream类派生的，用来支持对磁盘文件的输入输出。

要以磁盘文件为对象进行输入输出，必须定义一个文件流类的对象，通过文件流对象将数据从内存输出到磁盘文件，或者通过文件流对象从磁盘文件将数据输入到内存。

- 文件模式

`ios::in`    打开文件做读操作

`ios::out`   打开文件做写操作，会删除原有数据

`ios::app`   在每次写之前找到文件尾

`ios::trunc`  打开文件时清空已存在的文件流

`ios::ate`   打开文件后立即定位到文件末尾

`ios::binary` 以二进制模式进行IO操作

```cpp
2. Example2
#include <iostream>
#include <fstream>

int test0(void)
{
	//std::ofstream ofs("text1.txt", std::ios::ate | std::ios::app);
	//std::ofstream ofs("text1.txt", std::ios::ate);
	std::ofstream ofs("text1.txt", std::ios::app);
	if(!ofs)
	{
		std::cout << "ofstream error!" << std::endl;
		return -1;
	}

	std::cout << ofs.tellp() << std::endl;

	ofs << "that's new" << std::endl;

	ofs.close();
	return 0;
}

int test1(void)
{
	test0();

	std: :ifstream ifs("text1.txt", std::ios::ate);
	if(!ifs)
	{
		std::cout << "ifstream error" << std::endl;
		return -1;
	}

	std::cout << ifs.tellg() << std::endl;

	ifs.close();

	return 0;
}

int main(void)
{
	std::fstream outfile("f1.dat", std::ios::out | std::ios::in);
	if(!outfile)
	{
		std::cout << "fstream error" << std::endl;
		return -1;
	}

	int ival;
	for(int idx = 0; idx != 10; ++idx)
	{
		std::cin >> ival;
		outfile << ival << ' ';
	}
	std::cout << outfile.tellp() << std::endl;

	outfile.seekg(0, std::ios::beg);

	for(int idx = 0; idx != 10; ++idx)
	{
		outfile >> ival;
		std::cout << ival << ' ';
	}
	outfile.close();
	return 0;
}
```



## 4.3 文件的打开与关闭

- 1. 打开磁盘文件

​	打开文件是指在文件读写之前做必要的准备工作，包括: 

​	(1) 为文件流对象和指定的磁盘文件建立关联，以便使文件流流向指定的磁盘文件。

​	(2) 指定文件的工作方式。

以上工作可以通过两种不同的方法实现。

(1) 调用文件流的成员函数open。如

` ofstream ofs; //定义ofstream类对象outfile`

 `ofs.open(″test.txt″); //使文件流与test.txt文件建立关联`

如果打开操作失败，open函数的返回值为0(假)，如果是用调用构造函数的方式打开文件的，则流对象的值为0。

```cpp
1.Example
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int test0(void)
{
    std::ifstream ifs(“io1.cc”);//定义并打开了一个ifstream对象
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    //std::string s;
    //while(ifs >> s)
    //{
    //    std::cout << s <<std::endl;
    //}

    std::vector<std::string> vec_str;
    std::string line;
    while(getline(ifs, line))
    {
        //std::cout << line << std::endl;
        vec_str.push_back(line);
    }

    std::vector<std::string>::iterator sit = vec_str.begin();
    for(; sit != vec_str.end(); ++sit)
    {
        std::cout << *sit << std::endl;
    }
    ifs.close();

    return 0;
}

int main(void)
{
    
    std::ifstream ifs("io1.cc");
    if(!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    std::ofstream ofs("test.txt");
    std::string line;
    while(getline(ifs, line))
    {
        ofs << line << std::endl;
    }

    return 0;
}
```

(2) 在定义文件流对象时指定参数

在声明文件流类时定义了带参数的构造函数，其中包含了打开磁盘文件的功能。因此，可以在定义文件流对象时指定参数，调用文件流类的构造函数来实现打开文件的功能。如

` ofstream ofs(″test.txt″);`

一般多用此形式，比较方便，作用与open函数相同。每一个打开的文件都有一个文件指针。

- 2. 关闭磁盘文件

  在对已打开的磁盘文件的读写操作完成后，应关闭该文件。关闭文件用成员函数close。如

  ofs.close( ); //将输出文件流所关联的磁盘文件关闭

  所谓关闭，实际上是解除该磁盘文件与文件流的关联，原来设置的工作方式也失效，这样，就不能再通过文件流对该文件进行输入或输出。此时可以将文件流与其他磁盘文件建立关联，通过文件流对新的文件进行输入或输出。如

  `ofs.open(″test2.txt″,ios::app);`

  此时文件流outfile与test2.txt建立关联，并指定了test2.txt的工作方式。

# 5.字符串输入输出流

- 文件流是以外存文件为输入输出对象的数据流，字符串流不是以外存文件为输入输出的对象，而以内存中用户定义的字符数组(字符串)为输入输出的对象，即将数据输出到内存中的字符数组，或者从字符数组(字符串)将数据读入。字符串流也称为内存流。

- 字符串流也有相应的缓冲区，开始时流缓冲区是空的。如果向字符数组存入数据，随着向流插入数据，流缓冲区中的数据不断增加，待缓冲区满了(或遇换行符)，一起存入字符数组。如果是从字符数组读数据，先将字符数组中的数据送到流缓冲区，然后从缓冲区中提取数据赋给有关变量

- 文件流类有`ifstream,ofstream`和`fstream`，而字符串流类有`istringstream,ostringstream`和`stringstream`。文件流类和字符串流类都是`ostream,istream`和`iostream`类的派生类，因此对它们的操作方法是基本相同的。向内存中的一个存储空间写数据就如同向文件写数据一样，但有几点不同:

  - (1) 输出时数据不是流向外存文件，而是流向内存中的一个存储空间。输入时从内存中的存储空间读取数据。 

  - (2) 字符串流对象关联的不是文件，而是内存中的一个存储空间，因此不需要打开和关闭文件。

- 字符串输入输出流的常用场景

  -  1）数值与字符串互相转化

  -  2）格式化输出或获取数据

```cpp
3. Example3

#include <iostream>
#include <sstream>
#include <string>

int test0(void)
{
    int ival = 512;
    int ival2 = 1024;
    std::stringstream ss;
    ss << "ival= " << ival << " " << "ival2= " << ival2 << std::endl;

    std::string str = ss.str();
    std::cout << str << std::endl;

    while(ss >> str)
    {
        std::cout << str << std::endl;		
    }
    return 0;
}
```

