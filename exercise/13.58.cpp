#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Foo{
	private:
		vector<int> data;
	public:
//		Foo sorted();
		Foo sorted() const ;
};

//Foo Foo::sorted()
//{
//	cout<<"��ֵ���ð汾"<<endl;
//	sort(data.begin(), data.end());
//	return *this;
//}

Foo Foo::sorted() const  
{
	cout<<"��ֵ���ð汾"<<endl;
	return *this;
}

int main()
{
	const Foo f;
	f.sorted();
	Foo().sorted(); 
	return 0;
}
