#include "Badeev_header.h"

vector<double> index_of_confidence(vector<unsigned char>&vec)
{
	vector<int>		symb_counts(256);
	vector<double>	indexes;
	double			IC, tmp;
	unsigned int	group;
	unsigned int	n;
	unsigned int	count;

	group = 1;
	while (group <= 256)
	{
		if (group > 20)
			return indexes;
		n = 0;
		IC = 0;
		while (n * group <= vec.size() - 1)
		{
			symb_counts[vec[n * group]]++;
			n++;
		}
		count = 0;
		while (count < 256)
		{
			tmp = ((double)symb_counts[count] * ((double)symb_counts[count] - 1)) / ((double)n * ((double)n - 1));
			IC = IC + tmp;
			tmp = 0;
			symb_counts[count] = 0;
			count++;
		}
		indexes.push_back(IC);
		group++;
	}
}

vector<vector<unsigned char>>Create_table(int key_len, vector<unsigned char>& vec)
{
	int	i;
	int	j;
	int	index;
	int range;

	range = vec.size() / key_len;
	vector<vector<unsigned char>>	table(key_len, vector<unsigned char>(range));
	i = 0;
	while (i < key_len)
	{
		j = 0;
		index = 0;
		while (j < range)
		{
			if (index % key_len == i)
				table[i][j++] = vec[index];
			index++;
		}
		i++;
	}
	return table;
}

map<double, unsigned char> Get_frequency_shifr(vector<unsigned char>& alphavite)
{
	vector<int>					symb_counts(256);
	map<double, unsigned char>	dict_shifr;
	unsigned int				i;

	i = 0;
	while (i < alphavite.size())
		symb_counts[alphavite[i++]]++;
	i = 0;
	while (i < 256)
	{
		dict_shifr.insert(make_pair(((double)symb_counts[i] / (double)alphavite.size()), i));
		i++;
	}
	return dict_shifr;
}

map<double, unsigned char> Get_frequency_standart(vector<unsigned char>&v)
{
	map<double, unsigned char>	dict_standart;
	vector<int>					symb_counts(256);
	unsigned int				i;

	i = 0;
	while (i < v.size())
		symb_counts[v[i++]]++;
	i = 0;
	while (i < 256)
	{
		dict_standart.insert(make_pair(((double)symb_counts[i] / (double)v.size()), i));
		i++;
	}
	return dict_standart;
}

string Get_keyword(int key_len, vector<vector<unsigned char>>table, map<double, unsigned char>freq_standart)
{
	int							num_keysymb;
	map<double, unsigned char>	freq_shifr;
	string						keyword;

	num_keysymb = 0;
	while (num_keysymb < key_len)
	{
		freq_shifr = Get_frequency_shifr(table[num_keysymb]);
		if (freq_standart.rbegin()->second < freq_shifr.rbegin()->second)
			keyword.push_back(freq_standart.rbegin()->second - freq_shifr.rbegin()->second);
		else
			keyword.push_back(freq_shifr.rbegin()->second - freq_standart.rbegin()->second);
		num_keysymb++;
	}
	return keyword;
}
