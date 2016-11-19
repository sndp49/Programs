#include <iostream>
#include <string>
using namespace std;

void compress(string &str)
{
	int n = str.length(), i = n-1, w = n*2-1, j;

	str.resize(n*2);

	while (i >= 0)
	{
		j = i-1;

		while (j>=0 && str[i] == str[j])
			j--;

		str[w--] = (i - j) + '0';
		str[w--] = str[i];

		i = j;
	}

	if (w >= 0)
		str = str.substr(w+1);

	return;
}


int main(int argc, char *argv[])
{
	const string s = "aabbbccdd";
	string str;

	if (argc == 2)
		str.assign(argv[1]);
	else
		str.assign(s);

	cout << "\nCompressed string of the given string \'" << str;	compress(str);	cout << "\' is " << str << endl;

	return 0;
}
