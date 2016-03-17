#include <iostream>
#include <map>
#include <vector>

using namespace std;


/*

Flyweight allows you to share bulky data which are common to each object. 
In other words, if you think that same data is repeating for every object, 
you can use this pattern to point to the single object and hence can easily 
save space.

A classic example usage of the flyweight pattern is the data structures for 
graphical representation of characters in a word processor. It might be desirable 
to have, for each character in a document, a glyph object containing its font outline, 
font metrics, and other formatting data, but this would amount to hundreds or thousands 
of bytes for each character. Instead, for every character there might be a reference to 
a flyweight glyph object shared by every instance of the same character in the document; 
only the position of each character (in the document and/or the page) would need to be 
stored internally.

To enable safe sharing, between clients and threads, Flyweight objects must be immutable. 
Flyweight objects are by definition value objects. The identity of the object instance is 
of no consequence therefore two Flyweight instances of the same value are considered equal.

*/

class IDrinkable 
{
public:
	virtual void print() = 0;
};

class Coke : public IDrinkable
{
public:
	void print() override { cout << "coke";  }
};

class Water : public IDrinkable
{
public:
	void print() override { cout << "water"; }
};

class Juice : public IDrinkable
{
public:
	void print() override { cout << "juice"; }
};

enum class DrinkCode
{ Coke, Water, Juice};

class DrinkFactory
{
private:
	static map<DrinkCode, IDrinkable*> map_;
	DrinkFactory() {
		map_.emplace(DrinkCode::Coke, new Coke);
		map_.emplace(DrinkCode::Water, new Water);
		map_.emplace(DrinkCode::Juice, new Juice);
	}
public:
	~DrinkFactory() {for (auto i : map_) delete i.second; }
	static IDrinkable* getDrink(DrinkCode dc) {
		static DrinkFactory factory;
		return factory.map_[dc];
	}
};
map<DrinkCode, IDrinkable*> DrinkFactory::map_;


class Order
{
private:
	IDrinkable* drink_;
	unsigned int quantity_;

public:
	Order(DrinkCode dc, unsigned int quantity) {
		drink_ = DrinkFactory::getDrink(dc);
		quantity_ = quantity;
	}
	~Order() {}
	void print() {
		cout << "\nnew order: " << quantity_ << " bottle(s) of ";
		drink_->print();
		cout << "\n";
	}
};


/*
The more order we have, the more memory we save;
They all reference to the 3 IDrinkable objects stored in factory
*/
int main()
{
	vector<Order> restaurant{ 
		Order{DrinkCode::Coke, 3}, 
		Order{ DrinkCode::Water, 2}, 
		Order{ DrinkCode::Juice, 1} 
	};

	for (auto order : restaurant) {
		order.print();
	}

	getchar();
	return 0;
}

