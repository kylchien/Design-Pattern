/*
You should use visitors when the following conditions hold:
	- You have a well-defined, known set of classes which will be visited.
	- Operations on said classes are not well-defined or known in advance. 
	   For example, if someone is consuming your API and you want to give consumers 
	   a way to add new ad-hoc functionality to objects. They're also a convenient 
	   way to extend sealed classes with ad-hoc functionaity.
	- You perform operations of a class of objects and want to avoid run-time type testing. 
	  This is usually the case when you traverse a hierarchy of disparate objects having different properties.

Don't use visitors when:
	- You support operations on a class of objects whose derived types are not known in advance.
	- Operations on objects are well-defined in advance, particularly if they can be inherited from a base class or defined in an interface.
	- Its easier for clients to add new functionality to classes using inheritance.
	- You are traversing a hierarchy of objects which have the same properties or interface.
	- You want a relatively simple API.


Watch Out for the Downsides

The arguments and return types for the visiting methods needs to be known in advance, 
so the Visitor pattern is not good for situtations where these visited classes are subject to change. 
Every time a new type of Element is added, every Visitor derived class must be amended.

Also, it can be difficult to refactor the Visitor pattern into code that wasn't already designed with the pattern in mind. 
And, when you do add your Visitor code, it can look obscure. The Visitor is powerful, but you should make sure to use it only when necessary.
*/

#include <iostream>
#include <vector>

using namespace std;

class Garden;
class Zoo;
class HauntedHouse;

class Visitor
{
public:

	virtual void visit(Garden*) = 0;
	virtual void visit(Zoo*) = 0;
	virtual void visit(HauntedHouse*) = 0;
};

class Place
{
public:
	virtual void accept(Visitor* v) = 0;
	virtual float getCost() = 0;
	virtual void enter(const string& name) = 0;
	virtual void leave(const string& name) = 0;
};


class Garden :public Place
{
public:
	void accept(Visitor* v) override { v->visit(this); }
	float getCost() override { return 10; }
	void enter(const string& name) override { cout << "welcome to Garden, " << name.c_str() << "\n";  }
	void leave(const string& name) override { cout << name.c_str() << ", please come to Garden next time!\n"; }
};


class Zoo :public Place
{
public:
	void accept(Visitor* v) override { v->visit(this); }
	float getCost() override { return 20; }
	void enter(const string& name) override { cout << "welcome to Zoo, " << name.c_str() << "\n"; }
	void leave(const string& name) override { cout << name.c_str() << ", please come to Zoo next time!\n"; }
};


class HauntedHouse :public Place
{
public:
	void accept(Visitor* v) override { v->visit(this); }
	float getCost() override { return 5; }
	void enter(const string& name) override { cout << "welcome to HauntedHouse, " << name.c_str() << "\n"; }
	void leave(const string& name) override { cout << name.c_str() << ", please come to HauntedHouse next time!\n"; }
};




class NormalVistor : public Visitor
{
protected:
	string name;
	float cash;

public:
	NormalVistor(const string& aname, float acash) :name(aname), cash(acash) {}
	virtual ~NormalVistor() {}

	virtual void visit(Garden* g) override {
		if (cash > g->getCost()) {
			cash -= g->getCost();
			g->enter(name);
			g->leave(name);
		}
		else {
			cout << name.c_str() << " has insufficient cash to visit Garden\n";
		}
	}
	virtual void visit(Zoo* z) override {
		if (cash > z->getCost()) {
			cash -= z->getCost();
			z->enter(name);
			z->leave(name);
		}
		else {
			cout << name.c_str() << " has insufficient cash to visit Zoo\n";
		}
	}
	virtual void visit(HauntedHouse* h) override {
		if (cash > h->getCost()) {
			cash -= h->getCost();
			h->enter(name);
			h->leave(name);
		}
		else {
			cout << name.c_str() << " has insufficient cash to visit HauntedHouse\n";
		}
	}
};


class ChildrenVistor : public NormalVistor
{
public:
	ChildrenVistor(const string& aname, float acash) : NormalVistor(aname, acash){}
	~ChildrenVistor() {}

	void visit(Garden* g) override {NormalVistor::visit(g);	}
	void visit(Zoo* z) override {NormalVistor::visit(z);}
	void visit(HauntedHouse*) override {
		cout << name.c_str() << " is too young to visit HauntedHouse\n";
	}
};

class SeniorVistor : public NormalVistor
{
public:
	SeniorVistor(const string& aname, float acash) : NormalVistor(aname, acash) {}
	~SeniorVistor() {}

	void visit(Garden* g) override { NormalVistor::visit(g); }
	void visit(Zoo* z) override { NormalVistor::visit(z); }
	void visit(HauntedHouse*) override {
		cout << name.c_str() << " is too old to visit HauntedHouse\n";
	}
};


int main()
{
	vector<Place*> places;
	places.push_back(new HauntedHouse());
	places.push_back(new Zoo());
	places.push_back(new Garden());

	vector<Visitor*> vistors;
	vistors.push_back(new ChildrenVistor("daughter", 30));
	vistors.push_back(new ChildrenVistor("son", 25));
	vistors.push_back(new NormalVistor("dad", 50));
	vistors.push_back(new NormalVistor("mom", 50));
	vistors.push_back(new SeniorVistor("grandpa", 50));

	for (auto p : places) {
		for (auto v : vistors) {
			p->accept(v);
		}
	}

	for (auto p : places) { delete p; }
	for (auto v : vistors) { delete v; }

	getchar();
	return 0;
}
