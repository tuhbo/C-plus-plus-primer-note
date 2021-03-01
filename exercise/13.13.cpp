#include <iostream>
#include <vector>
using namespace std;

struct X{
	X(){
		cout<<"X()"<<endl;
	}
	X(const X&)
	{
		cout<<"X(const X&)"<<endl;
	}
	X& operator=(const X& rhs)
	{
		cout<<"������ֵ����� =(const X&)"<<endl;
		return *this;
	}
	void operator delete(void *p)
	{
		cout<<"�ͷŶ���"<<endl;
	}
};
void f1(X x)
{
	
}
void f2(X &x)
{
		
}

int main()
{
	cout<<"�ֲ�������"<<endl;
	X x;
	cout<<endl;
	
	cout<<"�����ò�������: "<<endl;
	f1(x);
	cout<<endl;
	cout<<"���ò�������: "<<endl;
	f2(x);
	cout<<endl;
	
	cout<<"��̬����: "<<endl;
	X *px = new X;
	
	cout<<"��ӵ�����: "<<endl;
	vector<X> vx;
	vx.push_back(x);
	cout<<endl;
	
	cout<<"�ͷŶ�̬�������: "<<endl;
	delete px;
	cout<<endl;
	
	cout<<"��ӳ�ʼ���͸�ֵ: "<<endl;
	X y = x;
	y = x;
	
	cout<<"�������"<<endl;
	return 0;
}
