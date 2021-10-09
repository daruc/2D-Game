#ifndef BINARY_H
#define BINARY_H

#include <utility>
#include <vector>


class Binary
{
public:
	virtual std::vector<char> toBinary() const = 0;
	virtual void fromBinary(int size, char * bytes) = 0;
	virtual ~Binary() {};
};

#endif