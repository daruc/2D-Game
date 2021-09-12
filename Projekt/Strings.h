#ifndef STRINGS_H
#define STRINGS_H

#include <string>
#include <map>


class Strings
{
private:
	std::map<std::string, std::wstring> strings;
	std::pair<std::string, std::wstring> split(std::wstring line);

public:
	static Strings* Instance();

	inline std::wstring get(std::string str) { return strings[str]; }

protected:
	Strings();

private:
	static Strings* instance;
};
#endif