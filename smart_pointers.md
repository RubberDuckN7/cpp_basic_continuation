# Smart pointers

## Introduction why
  When a program uses variables it is using memory in one of two ways:
   - Static allocation (Using stack)
   - Dynamic allocation (Using heap)
   
  A static allocation is looking like this:
  
  ```C++
    int number = 10; // Here, the memory is put on stack, and doesn't need to be deallocated explicitly.
  ```
  
  Just a small note, do NOT mix a "static allocation" and "static" keyword... yes DO NOT!!! >:(
  
  Dynamic allocation look like this:
  
  ```C++
    // Allocate memory
    int * number = new int(10);
    
    // Deallocate memory
    delete number;
  ```
  
  Explanation about *
  To indicate that a variable is a pointer, put * after the type and between the name.
  But another usage of * is that accessing the variable.
  *number tells to access "value" of allocated memory. To write to a pointer, that's why it is
  used *number = 10.
  Difference between accessing a pointer directly and with * before the name, is that directly,
  it is adressing memory. If value of adress will be changed, a pointer will point somewhere else.
  
  Another valid example:
  ```C++
    // Allocate memory
    int * number = new int;
    *number = 10;
    
    // Deallocate memory
    delete number;
  ```
  
  The difference between dynamic and static allocation, apart that from dynamic is put on heap,
  but also it needs to be deallocated. That's why "delete" is being called on the pointer variable.
  
  So the actual problem: You have to keep track off what memory is allocated or not and cleanup after
  the usage. For example, but simplified, what happens:
  ```C++
    // Allocate memory
    int * number = new int;
    *number = 10;
    
    // Deallocate memory
    delete number;
  ```

  Notice that for one "new" there is one "delete". What happens when this happens?
  ```C++
    int * number = new int;
    *number = 10;
    cout << *number << endl; 
    number = new int;
    cout << *number << endl;
    
    delete number; 
  ```
  
  Once a new is called again without calling delete, the memory will stay on the heap.
  And what happens then? It will stay there and not go away until all program is restarted >:(
  which there is an expression for: "Memory leak". Such things can cause crashes, for example
  by filling up memory slowly memory.
  
  That problem of not releasing memory correctly happens alot... like so many times that "people"
  had to create something to manage this "people-created-problem".
  
  In Java or C# (Or some other easy-to-use languages that are mostly used for tutorials) have "Garbage collector"
  that cleans up memory as soon as a variable is set to NULL (changing the adress to 0)
  
  Since C++11, there are smart pointers, that keeps track of a variable. By keeeping the variable wrapper
  within another class, and counting references.
  Reference counting is what happens when a smart pointer keeps track of how many owners does it have.
  Later into that.
  
  But for now, let's look into more about new and arrays. (It does not really have anything to do
  with smart pointers, but still)
  
  To create a dynamic array, here is how:
  ```C++
    // Allocate 10 types of int.
    int * arrayOfNumbers = new int[10];
    
    // Usage and access
    arrayOfNumbers[0] = 20;
    
    // Array can now be used.
    // But to delete dynamic array, [] are needed.
    delete [] arrayOfNumbers;    
  ```
  
  Note the difference, to delete one variable use:
   - delete,
   Deallocate array:
   - delete []
  
## Simple cases - Short version
  Smart pointer is a wrapper for holding the allocated memory and being
  an smarter owner of it. Also, include <memory>, to use them!
  
  There are different smart pointers, with short descriptions:
   This can only have one owner. That means only one real copy of unique_ptr.
   It will release allocated data, once the variable (or owner) is set to NULL / 0.
   - unique_ptr
   
   Difference between unique and shared, is that shared can be assigned to different owners,
   and keep track of "how many owners" it can have.
   If all the copies will be set to NULL / 0, the reference count will be zero, and at this point,
   data will be released.
   - shared_ptr 

   This type of pointer is holding a reference to a shared_ptr, without "owning" it,
   without increasing reference counter.
   
   Weak pointer is used for 2 reasons:
    1: Use the object only if it exists.
       weak_ptr.lock() returns a shared_ptr to manage the referenced object.
	2: If 2 objects, A and B, are shared_ptrs, and they point to eachother,
	   they will not be 0, and if no other pointer will point to them,
	   that would create memory leak.
	   Here is better explanation about this: https://www.learncpp.com/cpp-tutorial/15-7-circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/
   - weak_ptr 

   Unique pointer usage.
  ```C++
  // This is how to create one.
  unique_ptr<int> onlyOneOwner = make_unique<int>(10);
  
  cout << "Old owner: " << *onlyOneOwner << endl;
  
  // This is how to copy it into another owner.
  auto changeUniqueOwner = move(onlyOneOwner);
  
  if(onlyOneOwner) {
    cout << "Still alive??: " << *onlyOneOwner << endl;  
  }
  else {
    cout << "New proud owner of int: " << *changeUniqueOwner << endl;
  }
  ```
  
  From above, first unique_ptr is created by function "make_unique", and then pass in value in constructor.
  
  DO NOT USE THIS: unique_ptr someObject(new int(10));
  Even if people write this in examples everywhere, it is double dynamic allocations... Not sure what that means?
  It is very slow :)
  (PS: Catapult anyone who creates a smart pointer this way)

  Shared pointer.
  
  Shared pointers release memory only when reference count is reaching zero.
  Here is an example on how to create and release smart pointer.
  Note that creating smart pointers, there are functions for that: make_unique and make_shared.
  
  ```C++
  class PrintAtDestructor
  {
    public:
      PrintAtDestructor() { cout << "Creating PrintAtDestructor" << endl; }
      ~PrintAtDestructor() { cout << "Deleting PrintAtDestructor"<< endl; }
  };
  
  int main()
  {
    cout << "Creating first shared pointer" << endl;
    shared_ptr<PrintAtDestructor> ownerOne = make_shared<PrintAtDestructor>();
    
    cout << "Creating second owner" << endl;
    shared_ptr<PrintAtDestructor> ownerTwo = ownerOne;
    
    cout<< "Setting ownerOne to null" << endl;
    ownerOne = nullptr;
    
    cout << "Setting ownerTwo to null" << endl;
    ownerTwo = nullptr;
  }  
  ```
  
  After running this program, the output will look like this:
  
  ```C++
  Creating PrintAtDestructor                                                         
  Creating second owner                                                              
  Setting ownerOne to null                                                           
  Setting ownerTwo to null                                                           
  Deleting PrintAtDestructor  
  ```
  
  Only after setting all the owners to null, is the memory released.
  
  Weak pointers
  
  Weak is used by pointing to a shared pointer and calling lock, to use whenever needed.
  But there is no need to save weak pointer, because it is treated more like a discardable copy.
  
  Too lazy to explain, here is an example. Best way to see is to copy-paste and run this!
  If you notice, the lock will fail if the previous owner is null.
  
  ```C++
  class PrintAtDestructor
  {
    public:
      PrintAtDestructor() { cout << "Creating PrintAtDestructor" << endl; }
      ~PrintAtDestructor() { cout << "Deleting PrintAtDestructor"<< endl; }
      
      void printMessage(std::string message)
      {
        cout << endl << message << endl;
      }
  };
  
  int main()
  {
    cout << "Creating first shared pointer" << endl;
    shared_ptr<PrintAtDestructor> ownerOne = make_shared<PrintAtDestructor>();
    
    weak_ptr<PrintAtDestructor> weakOwner = ownerOne;
    
    if(auto lock = weakOwner.lock())
    {
      lock->printMessage("Owner is still alive");    
    }
    
    ownerOne = nullptr;
    
    if(auto lock = weakOwner.lock())
    {
      lock->printMessage("Owner is still alive");    
    }
    else
    {
      cout << endl << "Weak owner could not get reference" << endl;   
    }
  }
  ```
  
  Even if the ownerOne would be set to null, while weak pointer would have locked and kept that reference,
  it would still be able to use object, but after it's out of scope, it will be released.