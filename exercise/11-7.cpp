#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main()
{
	map<string, vector<string> > families;
	families["��"]; 
	families["��"].push_back("ǿ");
	families["��"].push_back("��");
	families["��"].push_back("��");
	families["��"];
	for(map<string, vector<string> >::iterator it = families.begin();it!=families.end();++it)
	{
		cout<<it->first<<"�ҵĺ��ӣ�";
		for(vector<string>::iterator k = (*it).second.begin();k!=(*it).second.end();++k)
		{
			cout<<*k<<" ";
		}
		cout<<endl;
	}
	return 0;
} 
