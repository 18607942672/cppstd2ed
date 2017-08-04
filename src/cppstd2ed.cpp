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
	//���������Ĺ��캯������P1��ʧȥ����ֵ�д���0����1��������ֵ������ʽת������
	//explicit P1(initializer_list<int>){
	//	cout << "call P1(initializer_list<int>)" << endl;
	//}
};

void fp(const P1&)
{
	cout << "call fp(const P1&)" << endl;
}

//����дһ������ӡĳ����������Ԫ�ء��ķ��ͺ�������
template<typename T>
void printElements(const T& coll)
{
	for(const auto& elem : coll){
		cout << elem << endl;
	}//���for����ͬ�����´���
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

	/*C++11֮������ģ����ģ���д������ֱ�����ұ�д>>���м䲻�ÿո�*/
	vector<list<int> > a;//���ֶ��巽ʽ���κ�һ���汾��C++�ж�����ʹ��
	vector<list<int>> b;//���ֶ��巽ʽ��C++11���Ժ�İ汾�п���ʹ��

	/*C++11������nullptr�ؼ�����ȡ��0��NULL��������ʾһ��ָ��ָ����ν��no value������һ��ȷ����ֵ��ע���ʱ��ͬ��ָ��һ����ȷ����ֵ
	  nullptr���Զ�ת��Ϊ����pointer���ͣ�������ת�����κ��������ͣ���������Ϊnullptr_t����һ����������*/
	f(0);//����f(int)
	f(NULL);//���NULL��0�������f(int)����������»����ģ�����ɣ�������
	f(nullptr);//����f(void*)

	/*C++11����������һ����������������Ҫָ�������ͣ�ֻ��˵������auto*/
	auto i = 42;//i�ᱻ�Ƶ���int��
	auto d = f();//d�ᱻ�Ƶ���double��
	//auto i; ���ֶ��������ʽ�����������Ϊiû�о����ֵ�����Ա������޷����������Ƶ�
	static auto vat = 0.19;//���Ը�auto�ͱ������϶�����޶�������static

	vector<string> v;
	auto pos = v.begin();//pos�ᱻ�Ƶ���vector<string>::iterator��

	auto l = [] (int z) -> bool {
		cout << "call lambda l" << endl;
	};//l�ᱻ�Ƶ���һ��lambda���ʽ������һ��int�ͱ���Ϊ������������bool��

	/*C++11������һ���Գ�ʼ�������κγ�ʼ�������������ô�����������*/
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

	/*Range-Based forѭ���������䡢���顢������(range, array, or collection)�ĵ�һ��Ԫ�ؽ�����һ����*/
	for(int i : {2, 3, 5, 7, 9, 13, 17, 19}){
		cout << i << endl;
	}//��򵥵�һ��Ӧ�ã����δ�ӡ�����е�����

	vector<double> vec{0.1, 1.1, 2.1, 3.1};
	for(auto& elem : vec){
		elem *= 3;
	}//�Լ����е�ÿ��Ԫ�����γ���3��ע��elemҪ���������ã�����ֻ��Լ�����Ԫ�صĿ��������޸ģ����ϱ������

	for(const auto& elem : vec){
		cout << elem << endl;
	}//�ٶԼ����е�Ԫ�����δ�ӡ

	//һ����ԣ��������coll�ṩ��Ա����begin()��end()����ôһ��range-based forѭ������Ϊ��
	/*
	for(decl : coll){
		statement
	}
	��ͬ��
	{
		for(auto _pos = coll.begin(), _end = coll.end(); _pos != _end; ++_pos){
			decl = *_pos;
			statement
		}
	}
	 */
	//���coll������������������ôҲ��ͬ������ʹ��һ��ȫ����begin()��end()�����߶�����collΪʵ�Σ�
	/*
	���ͬ��
	{
		for(auto _pos = begin(coll), _end = end(coll); _pos != _end; ++_pos){
			decl = *_pos;
			statement
		}
	}
	 */
	//������Գ�ֵ��(initializer list)ʹ��range-based forѭ������Ϊinitializer_list<>�ṩ�˳�Ա����begin()��end()
	//��һ���C-style arrayҲ����ʹ��range-based forѭ��
	int array[] = {1, 2, 3, 4, 5};

	long sum = 0;//������Ԫ���ۼ����
	for(int x : array){
		sum += x;
	}
	cout << sum << endl;

	for(auto elem : {sum, sum * 2, sum * 4}){//��ӡһЩsum�ı���
		cout << elem << endl;
	}
	//��Ԫ����forѭ���б�ʼ��Ϊdecl���������κ���ʽ����ת��(explicit type conversion)
	vector<string> vs{"aa", "bb", "cc"};
	/*
	for(const C& elem : vs){//�ᱨ����C�Ĺ��캯����explicit��ԭ���޷���string��ʽת����C
		cout << elem << endl;
	}
	*/

	/*C++11֧��move semantic(��Ǩ����)�����Ա���Ǳ�Ҫ�Ŀ�����������ʱ����*/
	/*
	void createAndInsert(set<X>& coll)
	{
		X x;//����һ��X���͵Ķ���
		...
		coll.insert(x);//����x������ļ�����
	}//�˴��������뵽�����е���x��һ���ڲ�����(internal copy)
	���磺
	X x;
	coll.insert(x);//�������x��һ�ݿ���
	...
	coll.insert(x+x);//���������ʱ��������ֵ����һ�ֿ���
	...
	coll.insert(x);//�������x��һ�ݿ���������x�Ѿ������ٱ�ʹ�ã�
	���ں�������insert���������õ���ָ����������ֵ��Ҳ����x+x�ĺ��Լ�x�����ٱ�������ʹ�á���
	����coll�ڲ�����Ϊ������һ�ݿ����ҡ���ĳ�ַ�ʽmove�����ݽ����½�Ԫ���С���
	C++11�Ѿ�ʵ�����������ܡ����ǣ�����Ա��������ָ����move�ǿ��еģ����Ǳ�������Ǹ���ʱ���󻹻ᱻʹ�á���
	���������������
	X x;
	coll.insert(x);//�������x��һ�ݿ�������Ϊx����ֵ�������ܱ�ʹ�ã�
	...
	coll.insert(x + x);//�ƶ������߿�������ʱ������ֵ�������ݵ�������
	...
	coll.insert(move(x)); //�ƶ������߿�����x�����ݵ�������
	��ʵmove()���������κ�moving��������ֻ�ǽ���ʵ��ת����һ����ν����ֵ���á�����һ������ζ�������ֵ�ǲ��ٱ���Ҫ�ģ���ʱ�����󣬿��ԸĶ��ˡ�
	set<>ģ���е�insert��������Ӧ������ֵ����Ϊ�����İ汾�����£�
	insert(const T& x);//������ֵ���ò����汾�����뵽�����е���x�Ŀ���
	insert(T&& x);//������ֵ���ò����汾���ƶ�x�е����ݵ�������
	C++11��׼����඼�ṩ��move���캯����������һ������Ԫ�ص������ƶ�����Ԫ���У����и��ӵ��࣬��Ӧ���ṩmove���캯�������ƶ������ʵ��ֵ����ʼ��һ����Ԫ�ء�
	���磺
	class X{
	public:
		X(const X& lvalue);//�������캯��
		X(X&& rvalue);//�ƶ����캯��
		...
	};
	���磺string���move���캯��ֻ�ǽ����е��ڲ��ַ����鸳���¶��󣬶����ǽ���һ�����ַ����飬Ȼ��������Ԫ�ء�
	ͬ�������Ҳ���������еļ����࣬��Ϊ�������е�ÿ��Ԫ�ؽ���һ�ݿ�����ֻ�ǽ��ڲ��ڴ渳���¶�����С�
	���move���캯�������ڣ�copy���캯���ͻᱻ���ϡ�
	���⻹Ҫ��֤�����ڱ���������value����͵ȡ�������κθĶ����ر��Ƿ�����������������Ӱ���¶������ӵ��value����״̬��
	ͬ���أ��κ�nontrivial class��Ҫͬʱ�ṩһ��������ֵ���캯�����ƶ���ֵ���캯�������£�
	class X{
	public:
		X& operator=(const X& lvalue);//������ֵ���캯��
		X& operator=(X&& rvalue);//�ƶ���ֵ���캯��
		...
	};
	����string�ͼ����࣬�����������Լ򵥽����ڲ����ݺ���Դ�Ϳ����ˡ�������ҲӦ�����*this�����ݣ�
	��Ϊ���������ܳ�����Դ����lock���������úܿ��ͷ����ǣ�C++11��׼��������ʵ��������������

	��һ�����⣬rvalue��lvalue reference�����ع������£�
	1.�����ֻʵ����
		void foo(X&);
	  ��û��ʵ�� void foo(X&&),����Ϊ��ͬC++98��foo()����lvalue��������rvalue�����á�

	*/


	cout << "The End!" << endl;

	return 0;
}
