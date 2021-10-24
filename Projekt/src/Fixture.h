#ifndef FIXTURE_H
#define FIXTURE_H

class b2Fixture;
class b2Contact;

class Fixture
{
public:
	virtual void beginContact(b2Contact* contact) {}
	virtual void endContact(b2Contact* contact) {}
	virtual ~Fixture() {};
};

#endif // !FIXTURE_H
