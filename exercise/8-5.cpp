#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main()
{
	ifstream  in("input.txt");
	if(!in)
	{
		cerr<<"�޷��������ļ�"<<endl;
		return -1;
	}
	string line;
	vector<string> words;
	while(in>>line)
	{
		words.push_back(line);
	}
	in.close();
	for(auto word:words)
	{
		cout<<word<<endl;
	}
	return 0;
} 
