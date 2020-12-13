#include <iostream>
#include <string>

using namespace std;

// TODO: Make this... generic! >:(
class Pair
{
  public:
  
  private:
    int firstData;
    int secondData;  
  public:
    void saveFirst(int firstData) { this->firstData = firstData; }
    void saveSecond(int secondData) { this->secondData = secondData; }
    
    int getFirstData() { return firstData; }
    int getSecondData() { return secondData; }
};

int main()
{
  Pair pairOfNumbers;
  
  pairOfNumbers.saveFirst(10);
  pairOfNumbers.saveSecond(20);
  
  cout << "FirsT: " << pairOfNumbers.getFirstData() << " Second: " << pairOfNumbers.getSecondData() << endl;
  
  // This obviously only supports int, but... rewrite the Pair to support different types.
  // Rewrite Pair and this line of code, to support the string and float, using templates.
  Pair... genericPair;
  
  genericPair.saveFirst("This is a string");
  genericPair.saveSecond(2.5f);
  
  cout << "FirsT: " << genericPair.getFirstData() << " Second: " << genericPair.getSecondData() << endl;
}