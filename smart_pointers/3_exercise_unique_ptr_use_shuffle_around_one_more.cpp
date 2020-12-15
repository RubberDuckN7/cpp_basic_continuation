#include <iostream>
#include <string>
#include <memory>

// In this exercise, unique pointer is changed incorrectly.
// Solve it.
using namespace std;

class PrintingDebugger
{
  public:
    PrintingDebugger() { cout << endl << "Creating PrintingDebugger" << endl; }
	~PrintingDebugger() { cout << endl << "Deleting PrintingDebugger" << endl; }
	
	void PrintMessage(string message) { cout << "Printing fancy message: " << message << endl; }
};

unique_ptr<PrintingDebugger> createDebugger()
{
  return make_unique<PrintingDebugger>();
}

unique_ptr<PrintingDebugger> passMeADebuggerForUsage(unique_ptr<PrintingDebugger> debugger)
{
  debugger->PrintMessage("Using debugger somewhere else");
  return debugger;
}

int main()
{
  // TODO: Unique pointer is called unique for a reason.
  // Here it is being assigned incorrectly.
  
  auto debugger = createDebugger();
  debugger->PrintMessage("I am using debugger :|");
  
  debugger = passMeADebuggerForUsage(debugger);
  
  debugger->PrintMessage("Got my debugger back");

  return 0;  
}