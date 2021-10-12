#include "Badeev_header.h"


void	printMenu()
{
	cout << "1. Decrypt file\n"
		<< "2. Incrypt file\n"
		<< "0. Exit\n";
}

void	Crypt(int flag, string s1, string s2, string key)
{
	unsigned char	buff;
	unsigned char	result;
	int				index;

	index = 0;
	ifstream fin(s1, ios::binary);
	ofstream fout(s2, ios::binary);
	if (!fin.is_open() || !fout.is_open())
		cout << "Open file error! " << endl;
	else
	{
		while (1)
		{
			fin >> noskipws >> buff;
			if (!fin.eof())
			{
				result = buff + flag *key[index];
				fout << result;
				if (index + 1 == key.size())
					index = 0;
				else
					index++;
			}
			else
				break;
		}
		fout.close();
		fin.close();
	}
}

vector<unsigned char>Read_file(string name_file)
{
	vector<unsigned char>text_symb;

	ifstream fin(name_file, ios::binary);
	if (fin.is_open())
	{
		vector<unsigned char> v((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
		text_symb = v;
		fin.close();
	}
	return text_symb;
}

int		main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string							code_file, standart_file, decrypt_file, keyword;
	string							s1, s2, key;
	vector<unsigned char>			code_text;
	vector<unsigned char>			standart_text;
	vector<double>					indexes_confidence;
	vector<vector<unsigned char>>	table;
	map<double, unsigned char>		freq_standart;
	int								key_len;

	while (1)
	{
		printMenu();
		switch (GetCorrectNumber("Choose your action: ", 0, 2))
		{
		case 1:
		{
			while (1)
			{
				cout << "Enter code file: ";
				cin >> code_file;
				cout << "Enter standart file: ";
				cin >> standart_file;
				code_text = Read_file(code_file);//считываем зашифрованный файл
				standart_text = Read_file(standart_file);//считываем эталонный файл
				indexes_confidence = index_of_confidence(code_text);//получаем первые 20 индексов соответствия
				cout << "Index confidence: \n" << indexes_confidence << "\n" << "Enter length of keyword: ";
				cin >> key_len;
				table = Create_table(key_len, code_text);//делаем двумерный алфавит где строки это алфавит для соответствующей буквы кодового слова
				freq_standart = Get_frequency_standart(standart_text);//частотный анализ для эталонного текста
				keyword = Get_keyword(key_len, table, freq_standart);//получаем слово
				cout << keyword << endl
					<< "Enter output file: ";
				cin >> decrypt_file;
				Crypt(1, code_file, decrypt_file, keyword);
				if (!GetCorrectNumber("Change files? (0 - No, 1 - Yes): ", 0, 1))
					break;
			}
			break;
		}
		case 2:
		{
			cin >> s1 >> s2 >> key;
			Crypt(-1, s1, s2, key);//2 - Decrypt file
			break;
		}
		case 0:
		{
			return 0;
		}
		default:
		{
			cout << "Input error!";
		}
		}
	}
}