#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	ifstream in("input.txt");
	if(!in)
	{
		cerr<<"�޷��������ļ�"<<endl;
		return -1;
	}
	string line;
	vector<string> words;
	while(getline(in, line))
	{
		words.push_back(line);
	}
	in.close();
	for(auto word:words)
	{
		istringstream line_str(word);
		string  w;
		while(line_str>>w)
		{
			cout<<w<<" ";
		}
		cout<<endl;
	}
	return 0;
}
