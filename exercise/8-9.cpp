#include <iostream>
#include <stdexcept>
#include <sstream>
using namespace std;
istream &f(istream & in)
{
	string v;
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
	ostringstream msg;
	msg<<"C++ Primer �����"<<endl;
	istringstream in(msg.str());
	f(in);
	return 0; 
} 
