#include <iostream>
#include <stdexcept>
using namespace std;
istream &f(istream & in)
{
	int v;
	while(in>>v||!in.eof())
	{
		if(in.bad())
		{
			throw runtime_error("IO������");
		}
		if(in.fail())
		{
			cerr<<"���ݴ���, ������"<<endl;
			in.clear();
			in.ignore(100, '\n');
			continue; 
		}
		cout<<v<<endl;
	}
	in.clear();
	return in;
}
int main()
{
	cout<<"������һЩ����, ��Ctrl+Z����"<<endl;
	f(cin);
	return 0; 
} 
