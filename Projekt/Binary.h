#ifndef BINARY_H
#define BINARY_H
#include <utility>

class Binary
{
public:
	virtual std::pair<int, char*> toBinary() const = 0;
	virtual void fromBinary(int size, char * bytes) = 0;
};

#endif