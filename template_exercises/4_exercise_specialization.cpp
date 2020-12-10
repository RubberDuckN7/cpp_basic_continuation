// First exercise! Just to get started!
#include <iostream>
#include <string>

using namespace std;

// Let's start with something simple!
void printInteger(int data)
{
  cout << data << " : ";
}

void printInteger(string data)
{
  cout << data << " : ";
}

void printFloat(float data)
{
  cout << data << " : ";
}

// Obviously, you could go on with the types here... but, now that you know basic template,
// TODO: Use the tempalte to rewrite these functions, so that you minimize the amount of code written!
// Want to read about repeating yourself? READ THIS! https://en.wikipedia.org/wiki/Don%27t_repeat_yourself

int main()
{
  printInteger(10);
  printInteger("Hello");
  printInteger(1.2f);
}