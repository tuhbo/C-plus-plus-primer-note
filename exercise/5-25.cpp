#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
	cout<<"���������뱻�����ͳ����� "<<endl;
	int val1, val2;
	while(cin>>val1>>val2)
	{
		try
		{
			if(val2==0)
			{
				throw runtime_error("��������Ϊ0");
			}
			cout<<"��������Ľ����: "<<val1/val2<<endl; 
		}
		catch(runtime_error err)
		{
			cout<<err.what()<<endl;
			cout<<"��Ҫ������(y  or n)?";
			char ch;
			cin>>ch;
			if(ch!='y'&&ch!='Y')
				break;
		}
	}
	return 0;
}
