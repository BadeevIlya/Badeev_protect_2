#include "Badeev_header.h"

int		GetCorrectNumber(string text, int min, int max)
{
	int	n;

	cout << text;
	while ((cin >> n).fail() || n<min || n>max || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter a value (" << min << "-" << max << "):";
	}
	return n;
}

ostream& operator<< (ostream& out, vector<double> vec)
{
	int i;

	i = 0;
	while (i < vec.size())
		out << i << ". " << vec[i++] << endl;;
	return out;
}
