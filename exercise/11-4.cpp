#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream in(argv[1]);
	if(!in)
	{
		cout<<"�������ļ�ʧ��!"<<endl;
		exit(1); 
	}
	map<string, int> word_count;
	string word;
	while(in>>word)
	{
		word_count[word]++;
	}
	for(const auto &w:word_count)
	{
		cout<<w.first<<"������"<<w.second<<"��"<<endl;
	}
	return 0;
 } 
