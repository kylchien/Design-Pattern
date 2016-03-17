#include <iostream>

using namespace std;

/*
A prototype pattern is used in software development when the 
type of objects to create is determined by a prototypical instance, 
which is cloned to produce new objects. This pattern is used, for example, 
when the inherent cost of creating a new object in the standard way 
(e.g., using the new keyword) is prohibitively expensive for a given application.

Implementation: Declare an abstract base class that specifies a pure virtual clone() method. 
Any class that needs a "polymorphic constructor" capability derives itself from the abstract 
base class, and implements the clone() operation.

Use Prototype Pattern when a system should be independent of how its products are created, composed, and represented, and:

Classes to be instantiated are specified at run-time
Avoiding the creation of a factory hierarchy is needed
It is more convenient to copy an existing instance than to create a new one.


Hmm maybe like car, it has numerous configuration, when a customer add a few more cars (same config) in his order,
it is convenient to "clone" the one we already configured 
*/

int main()
{
	getchar();
	return 0;
}