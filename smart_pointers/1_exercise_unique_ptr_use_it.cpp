#include <iostream>
#include <string>

// In this exercise, look how an object is created.
// Refactor this, so that it is using unique_ptr.
// Don't be too fancy about it though.
// Make sure that there wont be any keywords: new and delete in this program
// (Comments doesn't count)

using namespace std;

class PrintingDebugger
{
  public:
    PrintingDebugger() { cout << endl << "Creating PrintingDebugger" << endl; }
	~PrintingDebugger() { cout << endl << "Deleting PrintingDebugger" << endl; }
	
	void PrintMessage(string message) { cout << "Printing fancy message: " << message << endl; }
};

PrintingDebugger * createDebugger()
{
  auto debugger = new PrintingDebugger();
  
  // Yeah, copy-pasting happens less obvious in bigger system, buuuuut... 
  // I will just leave it here...
  debugger = new PrintingDebugger();
  
  return debugger;
}

int main()
{
  auto debugger = createDebugger();

  debugger->PrintMessage("I am using debugger :|");

  delete debugger;
  
  return 0;  
}