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
	//���������Ĺ��캯������P1��ʧȥ����ֵ�д���0����1��������ֵ������ʽת������
	//explicit P1(initializer_list<int>){
	//	cout << "call P1(initializer_list<int>)" << endl;
	//}
};

void fp(const P1&)
{
	cout << "call fp(const P1&)" << endl;
}
int main() {
	vector<list<int> > a;//���ֶ��巽ʽ���κ�һ���汾��C++�ж�����ʹ��
	vector<list<int>> b;//���ֶ��巽ʽ��C++11���Ժ�İ汾�п���ʹ��

	f(0);//����f(int)
	f(NULL);//���NULL��0�������f(int)����������»����ģ�����ɣ�������
	f(nullptr);//����f(void*)

	auto i = 42;//i�ᱻ�Ƶ���int��
	auto d = f();//d�ᱻ�Ƶ���double��
	//auto i; ���ֶ��������ʽ�����������Ϊiû�о����ֵ�����Ա������޷����������Ƶ�
	static auto vat = 0.19;//���Ը�auto�ͱ������϶�����޶�������static

	vector<string> v;
	auto pos = v.begin();//pos�ᱻ�Ƶ���vector<string>::iterator��

	auto l = [] (int z) -> bool {
		cout << "call lambda l" << endl;
	};//l�ᱻ�Ƶ���һ��lambda���ʽ������һ��int�ͱ���Ϊ������������bool��

	//C++11������һ���Գ�ʼ�������κγ�ʼ�������������ô�����������
	int values[]{1, 2, 3};
	vector<int> v1{2, 3, 5, 7, 11, 13, 17};
	vector<string> cities{
		"Berlin", "New York", "London", "Braunschweig", "Cairo", "Cologne"
	};
	complex<double> c{4.0, 3.0};//����c(4.0, 3.0)������һ������������һ����

	int i1;//i1��ֵ�ǲ�ȷ����
	int j{};//j��ֵ����ʼ��Ϊ0
	int* p;//p��ֵ�ǲ�ȷ���ģ�����pָ������˭����֪��
	int* q{};//q��ֵ����ʼ��Ϊnullptr

	//ע��խ�����⣬Ҳ���Ǿ��Ƚ��ͻ������ֵ�䶯������������ô����ų�ʼ���ǲ�����ֵ�
	int x1(5.3);//���ᱨ����x1�����5
	int x2 = 5.3;//���ᱨ����x2Ҳ�����5
	//int x3{5.0};//�ᱨ����Ϊ����������խ��������
	//int x4 = {5.3};//�ᱨ����ΪҲ����������խ��������
	char c1{7};//���ᱨ����Ȼ7��һ��int�ͣ������ᷢ��խ�����⣬��Ϊ7���Ա�char���;�ȷ����
	//char c2{99999};//�ᱨ��������խ�����⡣��Ȼ��������99999���ܾ�ȷת����һ��char�͵�ֵ�������
	vector<int> v2{1, 2, 4, 5};//���ᱨ��
	//vector<int> v3{1, 2.3, 4, 5.5};//�ᱨ����������double��ֵ�����խ������

	//�û��Զ�������֮��ֵ�У���initializer_list<>�������һϵ��ֵ���г�ʼ���Ĺ�������ֵ�п��������κ�����Ҫ����һϵ��ֵ���κεص���г�ʼ��
	print({12, 3, 5, 7, 11, 13, 17});//�紫��һ�����е�ֵ���д�ӡ

	//����ָ��ʵ�θ������͡�ָ��һ����ֵ�С��Ĺ��캯��ͬʱ����ʱ������ƥ���ֵ�а汾
	P p1(77, 5);//����P::P(int, int)
	P q1{77, 5};//����P::P(initializer_list)
	P r{77, 5, 42};//����P::P(initializer_list)
	P s = {77, 5};//����P::P(initializer_list)

	P1 x(77, 5);//����P1::P1(int, int)
	P1 y{77, 5};//����P1::P1(int, int)
	P1 z{77, 5, 42};//����P1::P1(int, int, int)
	P1 vv = {77, 5};//����P1::P1(int, int),������ʽ����ת��
	//P1 w = {77, 5, 42};//�ᱨ����Ϊ���캯��ǰ�����explicit�����Բ�������ʽ����ת��

	fp({47, 11});//��ʽת����P1���͵ı���
	//fp({47, 11, 3});//�ᱨ����Ϊ���������Ĺ��캯��ǰ�����explicit�����Բ�������ʽ����ת��
	fp(P1{47, 11});//ֱ����ʾ���ö��������Ĺ��캯��
	fp(P1{47, 11,3});//ֱ����ʾ�������������Ĺ��캯��

	return 0;
}
