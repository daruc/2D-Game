#include "Strings.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <locale>
#include <codecvt>

Strings* Strings::instance = nullptr;

Strings* Strings::Instance()
{
	if (instance == nullptr)
	{
		instance = new Strings();
	}
	return instance;
}

Strings::Strings()
{
	std::wifstream fin;
	fin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	fin.open("Strings.txt");
	

	std::wstring line;
	while (std::getline(fin, line))
	{
		std::pair<std::string, std::wstring> pair = split(line);

		strings[pair.first] = pair.second;
	}
}

std::pair<std::string, std::wstring> Strings::split(std::wstring line)
{
	std::size_t position = line.find(L'=');
	std::pair<std::string, std::wstring> result;
	std::wstring temp = line.substr(0, position);

	std::stringstream strstream;
	for (char ch : temp)
	{
		strstream << ch;
	}
	result.first = strstream.str();
	result.second = line.substr(position+1);

	return result;
}