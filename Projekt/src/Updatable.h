#ifndef UPDATABLE_H
#define UPDATABLE_H

class Updatable
{
public:
	virtual void update(float delta_seconds) = 0;
	~Updatable() {}
};

#endif // !UPDATABLE_H
