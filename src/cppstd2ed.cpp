//============================================================================
// Name        : cppstd2ed.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <list>
#include <complex>

using namespace std;

void f(int)
{
	cout << "call f(int)" << endl;
}

void f(void*)
{
	cout << "call f(void*)" << endl;
}

double f()
{
	cout << "call f()" << endl;
	return 0;
}

void print(initializer_list<int> vals)
{
	for(auto p = vals.begin(); p != vals.end(); ++p){
		cout << *p << endl;
	}
}

class P
{
public:
	P(int, int){cout << "call P(int, int)" << endl;}
	P(initializer_list<int>){cout << "call P(initializer_list<int>)" << endl;}
};

class P1
{
public:
	P1(int a, int b ){
		cout << "call P1(int a, int b)" << endl;
	}
	explicit P1(int a, int b, int c){
		cout << "call P1(int a, int b, int c)" << endl;
	}
	//如果有下面的构造函数，则P1会失去“初值列带有0个，1个或多个初值”的隐式转换能力
	//explicit P1(initializer_list<int>){
	//	cout << "call P1(initializer_list<int>)" << endl;
	//}
};

void fp(const P1&)
{
	cout << "call fp(const P1&)" << endl;
}

//可以写一个“打印某集合内所有元素”的泛型函数如下
template<typename T>
void printElements(const T& coll)
{
	for(const auto& elem : coll){
		cout << elem << endl;
	}//这个for语句等同于如下代码
	/*
	{
	 	 for(auto _pos = coll.begin(); _pos != coll.end(); ++_pos){
	 	 	 const auto& elem = *_pos;
	 	 	 cout << elem << endl;
	 	 }
	}
	*/
}

class C
{
friend ostream& operator<<(ostream& os, const C& c);
public:
	C(){}
	explicit C(const string& s){ str = s;}
	string str;
};

ostream& operator<<(ostream& os, const C& c)
{
	os << c.str;
	return os;
}

int main() {

	/*C++11之后，这种模板套模板的写法可以直接在右边写>>，中间不用空格*/
	vector<list<int> > a;//这种定义方式在任何一个版本的C++中都可以使用
	vector<list<int>> b;//这种定义方式在C++11及以后的版本中可以使用

	/*C++11新增了nullptr关键字来取代0或NULL，用来表示一个指针指向所谓的no value，它是一个确定的值，注意此时不同于指向一个不确定的值
	  nullptr被自动转换为各种pointer类型，而不是转换成任何整数类型，它的类型为nullptr_t，是一个基础类型*/
	f(0);//调用f(int)
	f(NULL);//如果NULL是0，则调用f(int)，其它情况下会出现模棱两可，而出错
	f(nullptr);//调用f(void*)

	/*C++11允许你声明一个变量或对象而不需要指明其类型，只需说明它是auto*/
	auto i = 42;//i会被推导成int型
	auto d = f();//d会被推导成double型
	//auto i; 这种定义变量方式会产生错误，因为i没有具体的值，所以编译器无法进行类型推导
	static auto vat = 0.19;//可以给auto型变量加上额外的限定符，如static

	vector<string> v;
	auto pos = v.begin();//pos会被推导成vector<string>::iterator型

	auto l = [] (int z) -> bool {
		cout << "call lambda l" << endl;
	};//l会被推导成一个lambda表达式，它以一个int型变量为参数，并返回bool型

	/*C++11引入了一致性初始化，对任何初始化动作都可以用大括号来进行*/
	int values[]{1, 2, 3};
	vector<int> v1{2, 3, 5, 7, 11, 13, 17};
	vector<string> cities{
		"Berlin", "New York", "London", "Braunschweig", "Cairo", "Cologne"
	};
	complex<double> c{4.0, 3.0};//和用c(4.0, 3.0)来定义一个复数变量是一样的

	int i1;//i1的值是不确定的
	int j{};//j的值被初始化为0
	int* p;//p的值是不确定的，所以p指向哪里谁都不知道
	int* q{};//q的值被初始化为nullptr

	//注意窄化问题，也就是精度降低或造成数值变动。这种情况对用大括号初始化是不会出现的
	int x1(5.3);//不会报错，但x1变成了5
	int x2 = 5.3;//不会报错，但x2也变成了5
	//int x3{5.0};//会报错，因为出现了类型窄化的问题
	//int x4 = {5.3};//会报错，因为也出现了类型窄化的问题
	char c1{7};//不会报错，虽然7是一个int型，但不会发生窄化问题，因为7可以被char类型精确表述
	//char c2{99999};//会报错，出现了窄化问题。当然，这是在99999不能精确转换成一个char型的值的情况下
	vector<int> v2{1, 2, 4, 5};//不会报错
	//vector<int> v3{1, 2.3, 4, 5.5};//会报错，其中两个double型值会出现窄化问题

	//用户自定义类型之初值列，由initializer_list<>来完成用一系列值进行初始化的工作，初值列可以用在任何你想要处理一系列值的任何地点进行初始化
	print({12, 3, 5, 7, 11, 13, 17});//如传递一个序列的值进行打印

	//当“指明实参个数”和“指明一个初值列”的构造函数同时存在时，优先匹配初值列版本
	P p1(77, 5);//调用P::P(int, int)
	P q1{77, 5};//调用P::P(initializer_list)
	P r{77, 5, 42};//调用P::P(initializer_list)
	P s = {77, 5};//调用P::P(initializer_list)

	P1 x(77, 5);//调用P1::P1(int, int)
	P1 y{77, 5};//调用P1::P1(int, int)
	P1 z{77, 5, 42};//调用P1::P1(int, int, int)
	P1 vv = {77, 5};//调用P1::P1(int, int),允许隐式类型转换
	//P1 w = {77, 5, 42};//会报错，因为构造函数前面加了explicit，所以不允许隐式类型转换

	fp({47, 11});//隐式转换成P1类型的变量
	//fp({47, 11, 3});//会报错，因为三个参数的构造函数前面加了explicit，所以不允许隐式类型转换
	fp(P1{47, 11});//直接显示调用二个参数的构造函数
	fp(P1{47, 11,3});//直接显示调用三个参数的构造函数

	/*Range-Based for循环，对区间、数组、集合内(range, array, or collection)的第一个元素进行逐一迭代*/
	for(int i : {2, 3, 5, 7, 9, 13, 17, 19}){
		cout << i << endl;
	}//最简单的一个应用，依次打印集合中的素数

	vector<double> vec{0.1, 1.1, 2.1, 3.1};
	for(auto& elem : vec){
		elem *= 3;
	}//对集合中的每个元素依次乘以3，注意elem要声明成引用，否则只会对集合中元素的拷贝进行修改，集合本身不会变

	for(const auto& elem : vec){
		cout << elem << endl;
	}//再对集合中的元素依次打印

	//一般而言，如果集合coll提供成员函数begin()和end()，那么一个range-based for循环声明为：
	/*
	for(decl : coll){
		statement
	}
	等同于
	{
		for(auto _pos = coll.begin(), _end = coll.end(); _pos != _end; ++_pos){
			decl = *_pos;
			statement
		}
	}
	 */
	//如果coll不满足上述条件，那么也等同于以下使用一个全局性begin()和end()且两者都接受coll为实参：
	/*
	则等同于
	{
		for(auto _pos = begin(coll), _end = end(coll); _pos != _end; ++_pos){
			decl = *_pos;
			statement
		}
	}
	 */
	//可以针对初值列(initializer list)使用range-based for循环，因为initializer_list<>提供了成员函数begin()和end()
	//对一般的C-style array也可以使用range-based for循环
	int array[] = {1, 2, 3, 4, 5};

	long sum = 0;//对所有元素累加求和
	for(int x : array){
		sum += x;
	}
	cout << sum << endl;

	for(auto elem : {sum, sum * 2, sum * 4}){//打印一些sum的倍数
		cout << elem << endl;
	}
	//当元素在for循环中被始化为decl，不得有任何显式类型转换(explicit type conversion)
	vector<string> vs{"aa", "bb", "cc"};
	/*
	for(const C& elem : vs){//会报错，类C的构造函数因explicit的原因，无法将string隐式转换成C
		cout << elem << endl;
	}
	*/

	/*C++11支持move semantic(搬迁语义)，用以避免非必要的拷贝和生成临时对象*/
	/*
	void createAndInsert(set<X>& coll)
	{
		X x;//生成一个X类型的对象
		...
		coll.insert(x);//插入x到传入的集合中
	}//此处真正插入到集合中的是x的一个内部拷贝(internal copy)
	又如：
	X x;
	coll.insert(x);//插入的是x的一份拷贝
	...
	coll.insert(x+x);//插入的是临时生对象（右值）的一分拷贝
	...
	coll.insert(x);//插入的是x的一份拷贝（尽管x已经不会再被使用）
	对于后面两次insert操作，更好的是指出“被传入值（也就是x+x的和以及x）不再被调用者使用”，
	这样coll内部无须为它建立一份拷贝且“以某种方式move其内容进入新建元素中”，
	C++11已经实现了上述功能。但是，程序员必须自行指明“move是可行的，除非被插入的那个临时对象还会被使用”。
	于是有如下情况：
	X x;
	coll.insert(x);//插入的是x的一份拷贝（因为x是左值，还可能被使用）
	...
	coll.insert(x + x);//移动（或者拷贝）临时对象（右值）的内容到集合中
	...
	coll.insert(move(x)); //移动（或者拷贝）x的内容到集合中
	其实move()自身并不做任何moving工作，它只是将其实参转换成一个所谓的右值引用。这样一来，意味着这个右值是不再被需要的（临时）对象，可以改动了。
	set<>模板中的insert方法有相应的以右值引用为参数的版本，如下：
	insert(const T& x);//这是左值引用参数版本，插入到集合中的是x的拷贝
	insert(T&& x);//这是右值引用参数版本，移动x中的内容到集合中
	C++11标准库的类都提供了move构造函数，用来将一个即有元素的内容移动到新元素中，所有复杂的类，均应当提供move构造函数，它移动传入的实参值，初始化一个新元素。
	例如：
	class X{
	public:
		X(const X& lvalue);//拷贝构造函数
		X(X&& rvalue);//移动构造函数
		...
	};
	例如：string类的move构造函数只是将既有的内部字符数组赋予新对象，而不是建立一个新字符数组，然后复制所有元素。
	同样的情况也适用于所有的集合类，不为集合类中的每个元素建立一份拷贝，只是将内部内存赋予新对象就行。
	如果move构造函数不存在，copy构造函数就会被用上。
	另外还要保证，对于被传对象（其value被“偷取”）的任何改动（特别是发生析构）都不至于影响新对象（如今拥有value）的状态。
	同样地，任何nontrivial class都要同时提供一个拷贝赋值构造函数和移动赋值构造函数，如下：
	class X{
	public:
		X& operator=(const X& lvalue);//拷贝赋值构造函数
		X& operator=(X&& rvalue);//移动赋值构造函数
		...
	};
	对于string和集合类，上述操作可以简单交换内部内容和资源就可以了。但，你也应当清除*this的内容，
	因为这个对象可能持有资源（如lock），因而最好很快释放它们，C++11标准库容器都实现了上述操作。

	下一个问题，rvalue和lvalue reference的重载规则，如下：
	1.如果你只实现了
		void foo(X&);
	  而没有实现 void foo(X&&),则行为如同C++98：foo()可因lvalue但不能因rvalue被调用。

	*/


	cout << "The End!" << endl;

	return 0;
}
