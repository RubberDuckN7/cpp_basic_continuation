#include <iostream>
#include <string>

using namespace std;

// Pre-requisite!
// You have to know what static / dynamic allocation is. (Stack / Heap)
// With that said, there is example in the main.

// When an instance of this class "dies", it will print out a message!
class PrintingClass
{
public:
  PrintingClass(int instanceId);
  ~PrintingClass();

private:
  int instanceId;
  
public:
  void setId(int id) { this->instanceId = id; }
  int getId() { return this->instanceId; }
};

PrintingClass::PrintingClass(int id)
{
  this->instanceId = id;
  cout << "Creating class with Id: " << instanceId << endl;
}

PrintingClass::~PrintingClass()
{
  cout << "(Destructor)Destroying class with Id: " << instanceId << endl;
}
    
void createStaticClassInstance(int instanceId)
{
  PrintingClass printer(instanceId);   
}

PrintingClass * allocateOnHeap(int instanceId)
{
  return new PrintingClass(instanceId);
}

int main()
{
  // INFO: This is how the static allocation does look like.
  // Once it's "allocated" in stack, it will also be removed, when it goes out of scope.
  // The scope is defined with { }, and in this example, it is a function.
  cout << "Starting creating of instance" << endl;
  createStaticClassInstance(2);
  cout << "Ending creation of instance " << endl;
  
  // INFO: Dynamic allocation. When using new, the memory is allocated on the heap, and is released when "delete" is called.
  // We need to hold the instance, to be able to delete it!, if we don't we have a "memory leak", and that will be fill up memory,
  // by using it, without releasing and that causes... Crashes!!!!! >:(
  // Look very carefully at the printing results, and notice the ORDER of it! :3
  cout << "Creating a dynamic allocation instance" << endl;
  auto instance = allocateOnHeap(90);
  
  cout << "Has created instance on heap" << endl;
  
  cout << "Start deleting instance" << endl;
  delete instance;
  cout << "Has deleted instance with id: 90" << endl;
}