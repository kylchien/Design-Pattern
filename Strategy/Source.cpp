#include <iostream>

using namespace std;

/*
The strategy pattern (also known as the policy pattern) is a software design pattern 
that enables an algorithm's behavior to be selected at runtime. The strategy pattern

1. defines a family of algorithms,
2. encapsulates each algorithm, and
3. makes the algorithms interchangeable within that family.
*/


class AIStrategy {
public:
	virtual void execute() = 0;
};

class Aggro : public AIStrategy{
public:
	void execute() override { cout << "aggro style\n"; }
};

class Midrange : public AIStrategy {
public:
	void execute() override { cout << "midrange style\n"; }
};

class Control : public AIStrategy {
public:
	void execute() override { cout << "control style\n"; }
};

class HearthStoneAI {
public:
	HearthStoneAI(){}
	~HearthStoneAI() {}
	void play(AIStrategy& s) {
		cout << "AI plays ";
		s.execute();
		cout << endl;
	}
};

int main()
{
	Aggro aggro;
	Midrange mid;
	HearthStoneAI ai;
	ai.play(aggro);
	ai.play(mid);

	getchar();
	return 0;
}