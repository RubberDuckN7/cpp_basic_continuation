#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Okay, a simple example, but let's pretend like this: A key sits on a ring and in
// a way, "has a ring", but a key ring has a key.
class Key
{
  public:
    Key() { cout << endl << "Creating key" << endl; }
	~Key() { cout << endl << "Destroying key" << endl; }
};

class KeyRing
{
  public:
    KeyRing() { cout << endl << "Creating key ring" << endl; }
	~KeyRing() { cout << endl << "Destroying key ring" << endl; }
};

void 

int main()
{
  
}