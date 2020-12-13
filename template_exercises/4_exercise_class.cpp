#include <iostream>
#include <string>

using namespace std;

// This exercise is just to practice making class.
// TODO: Rewrite this class, to make it generic, for storing the data.
// (Also, this expression should already be familiar on what to do).

class DataStorage
{
  public:
  
  private:
    int dataNumber;
    
  public:
    int getData() { return dataNumber; }
    void saveData(int data) { this->dataNumber = data; }
};

int main()
{
  DataStorage dataStorage;
  dataStorage.saveData(20);
  cout << dataStorage.getData() << endl;
  
  // TODO:
  // Rewrite this to make sure that there will be a support for these different types
  // using the same class.
  
  DataStorage floatStorage;
  floatStorage.saveData(1.2f);
  
  DataStorage stringStorage;
  stringStorage.saveData("Some fancy description");
}