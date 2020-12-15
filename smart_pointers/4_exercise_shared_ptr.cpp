#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Here is exercise, two "participants" want to use a debugger.
// Normally, it can be solved with any pointer really, but the POINT of this,
// is that to just write something and pass shared_ptr as arguments.

// TODO: Rewrite this, so that there will not be any new / delete, but will still be dynamically
// allocated.

class PrintingDebugger
{
public:
  PrintingDebugger() { cout << endl << "Creating PrintingDebugger" << endl; }
  ~PrintingDebugger() { cout << endl << "Deleting PrintingDebugger" << endl; }

  void PrintMessage(string message) { cout << "Printing fancy message: " << message << endl; }
};

void PersonOneWantsDebugger(PrintingDebugger * debugger)
{
  debugger->PrintMessage("Person one using debugger");
}

void PersonTwoWantsDebugger(PrintingDebugger* debugger)
{
  debugger->PrintMessage("Person two using debugger");
}

int main()
{
  PrintingDebugger* debugger = new PrintingDebugger();

  PersonOneWantsDebugger(debugger);
  PersonTwoWantsDebugger(debugger);

  return 0;

  // Oooh right... forgot that this will never happen :|
  delete debugger;
}