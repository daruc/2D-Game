#ifndef UPDATABLE_H
#define UPDATABLE_H

class Updatable
{
public:
	virtual void update() = 0;
	~Updatable() {}
};

#endif // !UPDATABLE_H
