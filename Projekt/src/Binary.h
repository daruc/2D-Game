#ifndef BINARY_H
#define BINARY_H

#include <utility>
#include <vector>


class Binary
{
public:
	virtual std::vector<char> toBinary() const = 0;
	virtual void fromBinary(char* bytes) = 0;
	virtual size_t binarySize() const = 0;
	virtual ~Binary() {};
};

#endif