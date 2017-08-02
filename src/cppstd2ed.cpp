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
int main() {
	vector<list<int> > a;//这种定义方式在任何一个版本的C++中都可以使用
	vector<list<int>> b;//这种定义方式在C++11及以后的版本中可以使用

	f(0);//调用f(int)
	f(NULL);//如果NULL是0，则调用f(int)，其它情况下会出现模棱两可，而出错
	f(nullptr);//调用f(void*)

	auto i = 42;//i会被推导成int型
	auto d = f();//d会被推导成double型
	//auto i; 这种定义变量方式会产生错误，因为i没有具体的值，所以编译器无法进行类型推导
	static auto vat = 0.19;//可以给auto型变量加上额外的限定符，如static

	vector<string> v;
	auto pos = v.begin();//pos会被推导成vector<string>::iterator型

	auto l = [] (int z) -> bool {
		cout << "call lambda l" << endl;
	};//l会被推导成一个lambda表达式，它以一个int型变量为参数，并返回bool型

	//C++11引入了一致性初始化，对任何初始化动作都可以用大括号来进行
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

	return 0;
}
