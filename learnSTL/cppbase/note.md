# 面向对象 OOP
面向对象通过将数据和操作数据的方法封装在一起，使得代码易于理解、维护和使用。

## 类与对象：
类是创建对象的蓝图。它定义了对象拥有的属性（成员变量）和行为（成员函数）。

## 构造函数和析构函数：

构造函数：在创建对象的时候自动调用，用于初始化对象的成员变量。他的名字必须与类名相同。

析构函数：在对象销毁的时候自动调用，用于清理资源。例如释放动态分配的内存。

## 继承与多态

继承：允许一个类从另一个类继承属性和方法，促进代码重用。

多态：允许不同的对象对同一消息做出不同的响应。通长通过虚函数实现。

```
class Animal{
    public:
    Animal(){}
    ~Animal(){}
    virtual void speak(){}
}

class Dog : public Animal
{
    void speak() override { }
}

```
# 内存管理与进阶特性
在c++中，你拥有对内存的直接控制权，这带来的极高的性能，但是要求使用严谨。
## 指针与引用
指针：存储另一个变量的地址。使用 * 声明和解引用，使用 & 取地址。
引用：为已经存在的变量起一个别名。使用 & 声明，一旦初始化便不能更改指向。引用通常比指针更安全且易于阅读。

## 动态分配内存
使用new关键在在堆区动态分配内存，使用delete释放内存

## 模板编程基础
模板允许你的编写可以处理任何数据类型的代码，这是实现STL的关键。
```
template <typename T>
T add(T a,T b)
{
    return a+b;
}
```

# 实例解析
## Example 1:动态数组类的实现
```
class MyArray
{
    private:
        int *data_;
        int size_;
    public:
        MyArray(int size):size_(size)
        {
            data_ = new int[size];
        }
        ~MyArray()
        {
            delete[] data_;
        }
}
```
## 使用引用和指针传递
```
void updateValuePtr(int *ptr)
{
    if(ptr != nullptr)
    {
        *ptr = 100; 
    }
}

void updateValueRef(int &ref)
{
    ref = 100;
}
```


# new && delete
new用于堆内存动态分配，delete用于释放new申请的内存。

new[]分配动态数组，delete[]释放动态数组。
核心规则：单个对象 new 配 delete，数组 new [] 必须配 delete []，禁止混用。
```
#include <iostream>
using namespace std;

int main()
{
    // 1. 仅分配内存，不初始化，值随机
    int* p1 = new int;
    cout << *p1 << endl; // 乱码随机值

    // 2. 分配并显式初始化（圆括号赋值）
    int* p2 = new int(100);
    cout << *p2 << endl; // 100

    // 3. 值初始化为0：空括号 new T()
    double* p3 = new double();
    cout << *p3 << endl; // 0.0

    // 释放单个内存：只用 delete，不带[]
    delete p1;
    delete p2;
    delete p3;

    // 好习惯：释放后置空，防止野指针、重复delete崩溃
    p1 = nullptr;
    p2 = nullptr;
    p3 = nullptr;
    return 0;
}
```
```
#include <iostream>
using namespace std;

class Person
{
public:
    int age;
    // 无参构造
    Person()
    {
        cout << "无参构造调用" << endl;
        age = 0;
    }
    // 有参构造
    Person(int a)
    {
        cout << "有参构造调用" << endl;
        age = a;
    }
    // 析构函数
    ~Person()
    {
        cout << "析构函数调用" << endl;
    }
};

int main()
{
    // 无参构造创建堆对象
    Person* p1 = new Person;
    // 有参构造创建堆对象
    Person* p2 = new Person(18);

    cout << p2->age << endl;

    // 释放单个对象
    delete p1;
    delete p2;
    p1 = nullptr;
    p2 = nullptr;
    return 0;
}
```
```
int main()
{
    // 分配5个int数组，未初始化，值随机
    int* arr1 = new int[5];

    // C++11列表初始化，剩余元素自动补0
    int* arr2 = new int[5]{1, 2, 3}; // [1,2,3,0,0]

    // 全部初始化为0
    int* arr3 = new int[5]();

    // 遍历数组
    for (int i = 0; i < 5; i++)
    {
        cout << arr2[i] << " ";
    }

    // 数组释放必须加 []：delete[]
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    arr1 = arr2 = arr3 = nullptr;
    return 0;
}
```
```
int main()
{
    // 创建3个Person对象，自动调用3次无参构造
    Person* arr = new Person[3];

    // 释放数组，必须 delete[]，触发3次析构
    delete[] arr;
    arr = nullptr;
    return 0;
}
```

# 指针和引用
## 引用的本质
```
引用本质是一个 Type* const 常量指针，属于语法糖。
编译器自动完成：取地址初始化、使用时自动解引用，屏蔽指针语法。
```
## 核心区别对别
把指针看作是带有门牌编号的钥匙（你可以换门牌号，也可以手里没有钥匙）。引用则是某个人（变量）的小名，一旦叫了这个绰号，就只能指代这个人。

特性|指针pointer *|引用 Reference &
---|---|---
本质|存储另一个变量的地址|为已存在的变量起一个别名。
初始化|可以不进行初始化（但是很危险），也可以初始化为nullptr|必须在声明的时候初始化，不能脱离目标存在
重新赋值|随时可以改变执行，指向另外一个内存地址|不饿能更改指向其他变量
内存占用|本身是一个变量。在32、64位系统上占用4、8个字节|概念上不占用额外的内存
语法操作|通过使用*来解引用获取值，使用->访问成员|直接像普通变量一样使用，使用.访问成员

## 各自应用场景
什么时候使用指针？
1.动态内存管理：当使用new在堆内存分配内存你的时候，返回的必须是指针。这也是后续编写STL时管理底层内存的唯一方式。

2.构建复杂的数据结构：在实现链表、树、图时，节点之间必须通过指针链接，因为需要能够改变节点之间的链接关系。这超出了引用的能力范围。

3.表示”“可选”或“缺失”的状态：如果一个函数参数或返回值没有东西，可以传递返回nullptr。引用做不到这一点。

什么时候用引用？
1.函数参数的传递：当传递大型的对象时，按值传递会产生巨大的拷贝开销。使用引用（特别时const T& 常量引用）既可以避免拷贝，又可以保证数据不被意外修改。

2.运算符重载与链式调用：例如复制运算符operate=通常返回自身的引用*this，这样才能实现a=b=c。这样的连续赋值

3.使代码更加简洁

## 指针和引用在STL中的核心作用
在STL源码中，指针和引用时左右手，分工明确。

## A引用：STL容器的面子（提供接口）
当操作STL容器的时候，几乎无时无刻在使用引用。

* 元素访问：std::vector<int> v;v[0]=10;。这里的v[0]返回的是什么？必须是引用int&。如果返回的是值，你修改的只是一个副本，容器里的原值根本不会改变；如果返回的是指针，你的语法就会变成反人类的*v[0]=10。引用完美解决这个问题。
* 避免不必要的拷贝：观察STL的插入函数。它通常是接受一个常量引用，这样你相当于把一个巨大的对象放到容器时，在进入函数内部进行构造之前，不会产生对于的拷贝动作。
## B指针：STL迭代器的祖师爷和底层功臣
* 底层内存控制：在实现vector时，你需要一个指针来区分堆区分配的连续内存。在实现list的时候，你需要Node* next和Node *prev来串联节点。
* 迭代器的本质：STL的精髓在于算法与容器的分裂，而链接他们的桥梁时迭代器。迭代器的设计初衷，就是去模仿指针的行为。你能对指针做什么，就能对迭代器做什么。

# 