# shared_ptr
- 智能指针shared_ptr 是存储动态创建对象的指针，其主要功能是管理动态创建对象的销毁，从而帮助彻底消除内存泄漏和悬空指针的问题。

## 为什么要用shared_ptr

#### 在实际的 C++ 开发中，我们经常会遇到诸如程序运行中突然崩溃、程序运行所用内存越来越多最终不得不重启等问题，这些问题往往都是内存资源管理不当造成的。比如：

- 有些内存资源已经被释放，但指向它的指针并没有改变指向（成为了野指针），并且后续还在使用；

- 有些内存资源已经被释放，后期又试图再释放一次（重复释放同一块内存会导致程序运行崩溃）

- 没有及时释放不再使用的内存资源，造成内存泄漏，程序占用的内存资源越来越多。


## Syntax
- 所需头文件：<memory>
- 一般来说 std::make_shared 是最推荐的一种写法。
- way1:
```cpp
class A
{
 A()
 { cout << "A----" <<endl;}
}

A a;
auto sp1 = std::make_shared<int>(5);
auto sp11 = std::make_shared<A>(a);
```

- way2:
```cpp
int* p1 = new int[3];
std::shared_ptr<int> sp2(p1);
```

- way3:
```cpp
std::shared_ptr<A> sp3(new A);
```

- way4:
```cpp
auto sp31 = std::make_shared<A>(a);
std::shared_ptr<A> sp3(sp31);
```

## 增加计数
- 被引用则会增加计数
- 在函数内改变计数，超过生命周期后计数会恢复，test函数内的p1析构了。
```cpp
void test(int* ptr)
{
	std::shared_ptr<int> p1(ptr);
	int n = p1.use_count();
	std::cout << n << std::endl;
}
```

## shared_ptr常用函数
- get()函数，表示返回当前存储的指针（就是被shared_ptr所管理的指针） 。
但是不建议使用get()函数获取 shared_ptr 关联的原始指针，因为如果在 shared_ptr 析构之前手动调用了delete函数，会导致错误
- use_count()函数，表示当前引用计数
- reset()函数，表示重置当前存储的指针
- operator*，表示返回对存储指针指向的对象的引用。它相当于：* get（）。
- operator->，表示返回指向存储指针所指向的对象的指针，以便访问其中一个成员。跟get函数一样的效果。

## shared_ptr的特性
- 传统的局部变量是开辟在栈区的，函数返回时即销毁，
- 而shared_ptr则是开辟在堆区，在计数器归零时销毁，由程序员自行控制
