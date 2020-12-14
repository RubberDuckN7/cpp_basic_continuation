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
  There are different smart pointers:


  For far superior explanation:

  ```C++
#include <iostream>
#include <string>

#include <memory>

using namespace std;

int main()
{
  unique_ptr<int> smartInt = make_unique<int>(10);
  shared_ptr<int> smartSharedInt = make_shared<int>(20);
  
  
  weak_ptr<int> weakButSmartInt = smartSharedInt;
  
  cout << *smartInt << endl;
  cout << *smartSharedInt << endl;
  
  auto sp = weakButSmartInt.lock();
  
  cout << *sp << endl;
  
  //cout << *weakButSmartInt << endl;
}  
  ```
  

## Different ways

## Exercises