#include <iostream>
#include <cctype> 
using namespace std;

int main()
{
	string str, prev;
	bool flag=false;
	while(cin>>str)
	{
		#ifndef NDEBUG
			cout<<"���Եĵ���Ϊ: "<<str<<endl;
		#endif
		if(prev==str&&isupper(str[0]))
		{
			cout<<str<<"�ظ�����"<<endl; 
			flag = true;
			break;
		}
		prev = str;
	}
	if(!flag)
	{
		cout<<"���ظ����ֵĵ���"<<endl; 
	}
	return 0;
} 
