#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

using namespace std;

int Count ( const char* s)
{
	int k = 0; 
	for (int i = 0; s[i] != '\0'; i++)
		if (s[i]== '+'||s[i]== '-'|| s[i]== '=')
			k++;

	return k;
}

char* Change(char* str)
{
	size_t len = strlen(str);
	if (len < 3)
		return str;
	char* tmp = new char[len * 2 + 1];
	char* t = tmp;
	tmp[0] = '\0';
	size_t i = 0;
	while (str[i] != '\0')
		{
			if (str[i] == '+' || str[i] == '-' || str[i] == '=')
			{
				*t++ = '*'; // Записуємо першу зірочку
				*t++ = '*'; // Записуємо другу зірочку
				i++;
			}
			else
			{
				*t++ = str[i++]; // Звичайний символ
			}
	}
	*t = '\0';
	strcpy(str, tmp);
	return tmp;
}

int main()
{
	char str[101];
	cout << "Enter string: ";
	cin.getline(str, 100);
	char work[201];
	strcpy(work, str);
	char* dest = Change(work);
	cout << "Count of +, -, = : " << Count(str) << endl;
	cout << "Changed string: " << dest << endl;
	delete[] dest;
	return 0;
}