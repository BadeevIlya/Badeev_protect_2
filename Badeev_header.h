#pragma once

#ifndef BADEEV_HEADER_H
#define BADEEV_HEADER_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <map>

using namespace std;

vector<double>					index_of_confidence(vector<unsigned char>& vec);
vector<vector<unsigned char>>	Create_table(int key_len, vector<unsigned char>& vec);
map<double, unsigned char>		Get_frequency_shifr(vector<unsigned char>& alphavite);
map<double, unsigned char>		Get_frequency_standart(vector<unsigned char>& v);
string							Get_keyword(int key_len, vector<vector<unsigned char>>table, map<double, unsigned char>freq_standart);
ostream&						operator<< (ostream& out, vector<double> vec);
int								GetCorrectNumber(string text, int min, int max);

#endif // !BADEEV_HEADER_H
