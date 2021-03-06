### 第13章 拷贝控制

1. **拷贝构造函数**

   **(1) 合成拷贝构造函数**

   * 如果一个类没有定义拷贝构造函数，编译器会定义一个拷贝构造函数。
   * 一般情况下会将其参数的成员逐个拷贝到正在创建的对象中。(非静态成员)
   * 对类类型，使用其拷贝构造函数拷贝；内置类型，直接拷贝；数组类型，逐个拷贝数组的元素。
   
   **(2) 哪些情况会使用拷贝初始化**
   
   * 将一个对象作为实参传递给一个非引用类型的形参。
   * 从一个返回类型为非引用类型的函数返回一个对象。
   * 用花括号列表初始化一个数组的元素或一个聚合类中的成员
   * 某些类类型对它所分配的对象使用拷贝初始化。例如初始化标准库容器或是调用insert或push成员。而emplace成员则是直接初始化。

```c++
string dots (10, '.' );
//直接初始化
string s (dots) ;
//直接初始化
string s2 = dots;
//铂贝初始化
string null_book = "9-999-99999-9";//拷贝初始化string nines = string (100,'9');
//拷贝初始化

```

**2.拷贝赋值**

拷贝赋值的本质是重载=运算符。如果一个类没有定义拷贝赋值运算符，编译器会自定义一个合成拷贝赋值运算符。它所做的赋值操作和拷贝初始化类似。

**3.析构函数**

释放对象使用的资源，并销毁对象的非static数据成员。析构函数先执行函数体，然后再执行析构部分，析构部分说隐式的。成员销毁时执行什么操作依赖于成员的类型。

* 销毁类类型需要执行成员自己的析构函数。
* 销毁内置类型成员什么也不需要做。

**(1) 什么时候调用析构函数**

无论何时一个对象被销毁，就会自动调用其析构函数：

* 变量在离开其作用域时被销毁。
* 当一个对象被销毁时，其成员被销毁。
* 容器被销毁时，其元素被销毁。
* 对于动态分配的对象，当对指向它的指针应用delete运算符时被销毁。
* 对于临时对象，当创建它的完整表达式结束时被销毁。

**析构函数体本身不直接销毁成员， 成员是在析构函数体之后隐含的析构阶段中被销毁的。在整个对象析构过程中，析构函数体是作为成员销毁步骤之外的部分而进行的。**



**(2) 如果一个类需要自定义析构函数， 几乎可以肯定它也需要自定义拷贝赋值运算符和拷贝构造函数。**

**(3) 合成的拷贝控制成员可能是删除的:**

* 如果类的某个成员的析构函数是删除的或不可访问的（例如，是 private 的),则类的合成析构函数被定义为删除的。
* 如果类的某个成员的拷贝构造函数是删除的或不可访问的，则类的合成拷贝构造函数被定义为删除的。如果类的某个成员的析构函数是删除的或不可访问的，则类合成的拷贝构造函数也被定义为删除的。
* 如果类的某个成员的拷贝赋值运算符是删除的或不可访问的,或是类有一个const的或引用成员，则类的合成拷贝赋值运算符被定义为删除的。
* 如果类的某个成员的析构函数是删除的或不可访问的，或是类有一个引用成员，它没有类内初始化器，或是类有一个const成员，它没有类内初始化器且其类型未显式定义默认构造函数，则该类的默认构造函数被定义为删除的。

4. 对象移动

(1)  右值引用

* 右值引用只能绑定到一个将要销毁的对象，所以可以将右值引用的资源移动到另一个对象中(临时对象在语句结束之后被销毁)。

* 右值引用不能绑定到一个左值上。

  ```c++
  int i =42;
  int &r = i;//正确:r引用i
  int &&rr = i;//错误:不能将一个右值引用绑定到一个左值上
  int &r2 = i * 42;//错误:i*42是一个右值
  const int &r3 = i * 42;//正确:我们可以将一个const的引用绑定到一个右值上
  int & &rr2 = i * 42;//正确:将rr2绑定到乘法结果上
  
  ```

* 右值引用可以绑定到返回非引用类型的函数，使用算术、关系、位以及后置递增/递减运算符的表达式。

* 变量是左值，不能将一个右值引用绑定到一个右值引用类型的变量。

  ```c++
  int &&rrl = 42;//正确:字面常量是右值
  int & &rr2 = rr1; //错误:表达式rr1是左值!
  ```

* 调用std::move可以返回给定对象的右值引用，但不能对移后源对象做任何假设，可以销毁和赋值，但不能使用它的值。

(2) 移动构造与移动赋值

移动语义是从给定对象窃取资源，不分配新内存。

* 不抛出异常地移动构造函数和移动赋值运算符必须声明和定义(类外也一样)成noexcept。
* 移后源对象必须保持有效的、可析构的状态，但是用户不能对其值进行假设。
* 只有当类没有定义任何自己版本的拷贝控制成员，且它的数据成员都能移动构造或移动赋值时，编译器才会它合成移动构造函数或移动赋值运算符。
* 定义了一个移动构造函数或移动赋值运算符的类也不许定义自己的拷贝操作，否则，这些成员默认地被定义为删除函数。
* 移后源对象具有不确定的状态，对其调用std::move是很危险的，必须确认移后源对象没有其他用户。
* 通过调用make_move_iterator函数将一个普通迭代器转换为一个移动迭代器。

(3) 右值引用和成员函数

​	一个成员函数可以同时提供拷贝和移动版本。移动版本接受一个非const的右值引用。

* 引用限定符可以是&和&&，用来指出this指向一个左值和右值。只能用于非static成员函数，且同时出现在函数的声明和定义中。

  ```c++
  class Foo {
  	public:
  		Foo &operator=(const Foo&) &;//只能向可修改的左值赋值
  		// Foo的其他参数
  };
  Foo &Foo::operator=(const Foo &rhs)&//执行将rhs赋予本对象所需的工作
  {
  	return *this;
  }
  ```

* 对于&限定的函数，我们只能将它用于左值;对于& &限定的函数，只能用于右值：

  ```c++
  Foo &retFoo( );//返回一个引用; retFoo调用是一个左值
  Foo retval ();//返回一个值;retval 调用是一个右值
  Foo i, j;// i和j是左值
  i = j;//正确:i是左值
  retFoo()= j;//正确:retFoo ()返回一个左值
  retval() =j;//错误:retval ()返回一个右值
  i = retval();//正确:我们可以将一个右值作为赋值操作的右侧运算对象
  
  ```

* 如果一个成员函数有引用限定符，则具有相同参数列表的所有版本都必须有引用限定符，引用限定符可以用来区分重载版本。

### 第15章 面向对象程序设计

面向对象的核心思想：数据抽象、继承和动态绑定，通过使用数据抽象，我们可以将类的接口与实现分离；使用继承，可以定义相似的类型，但彼此又有区别；

1. 定义基类和派生类

* 虚函数：基类希望派生类将某些成员函数定义成适合自身的版本，基类在函数声明时加上virtual(**virtual只能出现在类的内部**)。

* 使用基类对象的引用或指针调用虚函数，将发生动态绑定。(在运行时选择函数的版本)。

* 基类通常定义一个虚析构函数，即使该函数不执行任何实际的操作。

* 派生类的成员函数不能访问基类的私有成员，但可以访问公有成员和受保护成员。
* 如果定义类在类名之后加final关键字，则该类不能继承。

(1) 派生类

* 如果派生是公有的，则基类的公有成员也是派生类接口的组成部分，可以将公有派生类型的对象绑定到基类的引用或指针上。

* 如果派生类没有重写其基类的虚函数，则派生类直接继承。

* 派生类对象包含：自己定义的非静态成员；基类的非静态成员。

  <img src="D:\study\Specialty\note\c ++\image\QQ截图20210304185752.png" alt="QQ截图20210304185752" style="zoom:80%;" />

* 派生类对象中包含其基类对应的部分，可以把派生类转换成基类(隐式的)

* 派生类的构造函数先构造属于基类的部分，然后再初始化自定义的部分。如果未显式指定基类的构造函数，则构造基类部分使用基类默认构造函数。

(2) 类型转换

* 静态类型：变量声明时的类型或者表达式生成的类型；
* 动态类型：变量或者表达式表示的内存中的对象的类型。

* 基类的对象可能是派生类对象的一部，也可能不是，所以不存在从基类向派生类的自动类型转换。

2. 虚函数

* 当使用基类的引用或指针调用一个虚函数时会发生动态绑定，因为直到运行时才直到到底调用那个版本的虚函数。所以虚函数必须定义。
* 基类中的虚函数在派生类中隐含地也是个虚函数，当派生类覆盖了某个虚函数时，该函数在基类中地形参必须与在派生类中地形参严格匹配。返回类型也必须与基类匹配。(例外：如果虚函数返回的是类本身的引用或指针)

3. 抽象基类

(1) 纯虚函数：在函数声明的最后书写 = 0(只能出现类内部的虚函数声明处)，可以为纯虚函数提供定义，但必须在类的外部。

(2) 抽象基类：含有纯虚函数的类是抽象基类。

(3) 抽象基类只负责定义接口，不能直接创建一个抽象基类的对象。

4. 访问控制与继承

(1) 受保护的成员(protected)

派生类的成员或友元只能通过派生类对象访问基类的受保护成员。派生类对于一个基类对象中的受保护成员没有任何访问特权。

```c++
class Base {
protected:
	int prot_mem;// protected成员
};
class Sneaky : public Base {
	friend void clobber (Sneaky&);//能访问Sneaky : :prot_mem
	friend void clobber (Base&) ;//不能访问 Base: :prot_mem
	int j;//j默认是private
};
//正确:clobber能访问Sneaky对象的private和protected成员
void clobber (Sneaky &s) { s.j = s.prot_mem = 0; }
//错误:clobber不能访问Base的protected成员
void clobber(Base &b) { b.prot_mem = 0; }

```

(2) 公有、私有和受保护继承

* 影响某个类对继承的成员的访问权限有两个因素：
  *  基类中该成员的访问说明符
  * 派生类的派生列表中的访问说明符

* 派生访问说明符的目的是控制派生类对象对于基类成员的访问权限

```c++
class Base {
public:
void pub_mem() ;/ public成员
protected:
int prot_mem;// protected成员
private:
char priv_mem;//private成员
};
struct Pub_Derv : public Base {
//正确:派生类能访问protected成员
    int f(){ return prot_mem;}
//错误:private成员对于派生类来说是不可访问的
    char g() { return priv_mem; }
} ;
struct Priv_Derv : private Base {
// private不影响派生类的访问权限
int f1 ( ) const { return prot_mem;}
};

Pub_Derv dl;//继承自 Base的成员是public的
Priv_Derv d2;//继承自 Base的成员是private的
dl.pub_mem() ;//正确:pub mem 在派生类中是public的
d2.pub_mem ();//错误:pub_mem在派生类中是private的

```

* 如果继承是公有的，则成员将遵循其原有的访问说明

* 对于代码中的某个节点来说，如果基类的公有成员是可访问的，则派生类向基类的类型转换也是可访问的；反之则不行。

5. 虚析构函数

* 基类的析构函数必须是虚函数，当delete一个动态分配的对象的将执行析构函数，如果该指针指向继承体系中的某个类型，则有可能出现指针的静态类型与被删除对象的动态类型不符的情况。

* 析构函数的虚属性也会被继承，无论派生类使用合成的析构函数还是定义自己的析构函数，都将是虚析构函数。
* 如果一个类定义了析构函数，即使它通过=default的形式使用合成的版本，编译器也不会为这个类合成移动操作。

6.派生类删除的拷贝控制与基类的关系

* 如果基类中的默认构造函数、拷贝构造函数、拷贝赋值运算符或析构函数是删除的或不可访问的，则派生类中对应的函数也是删除的或不可访问的。
* 如果基类中有一个不可访问或者删除的析构函数，则派生类中国合成的默认和拷贝构造函数将是被删除的，因为编译器无法销毁派生类对象的基类部分。
* 和过去一样，编译器将不会合成一个删除掉的移动操作。当我们使用=default请求一个移动操作时，如果基类中的对应操作是删除的或不可访问的，那么派生类中该函数将是被删除的，原因是派生类对象的基类部分不可移动。同样，如果基类的析构函数是删除的或不可访问的，则派生类的移动构造函数也将是被删除的。

### 第16章 模板

1. 函数模板

使用一个函数模板的时候，编译器会用函数实参推导出模板实参，并实例化出一个特定的函数版本。

(1) 模板参数

* 表示类型的模板参数
* 非类型模板参数：模板实参必须是常量表达式

(2) 模板编译

当编译器遇到一个模板定义时，它并不生成代码，只有使用模板时，编译器才生成代码。一般将类定义和函数声明放在头文件中，而普通函数和类的成员函数的定义放在源文件中。**而模板不同，为了生成一个实例化版本，编译器需要掌握函数模板或类模板成员的定义。函数模板和类模板成员函数的定义通常放在头文件中**

2. 类模板

(1) 编译器不能为类模板推断模板参数类型，在使用类模板的时候需要显示提供参数类型。

(2) 默认情况下对于一个实例化的类模板，其成员只有在使用时才被实例化。

(3) 在一个类模板的作用域内，可以直接使用模板名而不必指定模板参数。