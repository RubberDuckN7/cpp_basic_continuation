#include <iostream>
#include <string>
#include <memory>

using namespace std;

// TODO: This is some ugly piece of code.
// There is not much that could be rewritten (let's pretend at least) except for, refactoring
// so that is is using smart pointers. It doesn't what kind, just pick one that will solve a problem.

class PrintingDebugger
{
public:
  PrintingDebugger() { cout << endl << "Creating PrintingDebugger" << endl; }
  ~PrintingDebugger() { cout << endl << "Deleting PrintingDebugger" << endl; }

  void PrintMessage(string message) { cout << "Printing fancy message: " << message << endl; }
};

class SystemThatRequiresDebugger
{
public:
  SystemThatRequiresDebugger() = default;
  ~SystemThatRequiresDebugger() = default;

private:
  PrintingDebugger* debugger;

public:
  void setDebugger(PrintingDebugger* debugger) { this->debugger = debugger; }
  void executeSomeProcess() { debugger->PrintMessage("Executing process"); }
};

PrintingDebugger * createDebugger()
{
  // TODO: This is dynamically allocated, but is never released.
  // In a larger and more complex system, it is harder to keep track of such memory,
  // and that's why it's better to put it with smart pointer.

  // Tips: Can't decide if it should be unique or shared? Pick one that solves the problem. :|
  return new PrintingDebugger();
}

SystemThatRequiresDebugger createSystem()
{
  return SystemThatRequiresDebugger();
}

void executeSomeSystemProcess()
{
  PrintingDebugger* debugger = createDebugger();

  auto system = createSystem();
  system.setDebugger(debugger);

  system.executeSomeProcess();
}

int main()
{
  executeSomeSystemProcess();

  // Note: Yeah, that's what the text said, the output from destructor should be called once
  // executeSomeSystemProcess scope have ended, because system should die (not a pointer).
  cout << "At this points, the debugger should have been released" << endl;
  return 0;
}