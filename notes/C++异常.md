异常处理机制为程序中异常检测和异常处理这两部分的协作提供支持。在C++语言中,异常处理包括:

- throw表达式( `throw expression`)，异常检测部分使用`throw`表达式来表示它遇到了无法处理的问题。我们说`throw`引发（raise）了异常;
- try语句块(try block)，异常处理部分使用try语句块处理异常。try语句块以关键字try开始，并以一个或多个catch子句( catch clause）结束。try语句块中代码抛出的异常通常会被某个catch子句处理。因为catch子句“处理”异常，所以它们也被称作异常处理代码（exception handler）;
- 一套异常类（exception class)，用于在throw表达式和相关的catch子句之间传递异常的具体信息;

# 1.throw表达式

- 程序的异常检测部分使用throw表达式引发一个异常。throw表达式包含关键字throw和紧随其后的一个表达式，其中表达式的类型就是抛出的异常类型。throw表达式后面通常紧跟一个分号，从而构成一条表达式语句。

```cpp
//首先检查两条数据是否是关于同一种书籍的
if (item1 .isbn () != item2 .isbn ( ))
	throw runtime_error ( "Data must refer to same ISBN");
//如果程序执行到了这里，表示两个工SBN是相同的
cout << item1 + item2 << endl;
```

# 2. try语句

```cpp

```



# 3. 标准异常

