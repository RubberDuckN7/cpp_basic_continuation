// Second exercise! (Thought I would forget to update this?)
#include <iostream>
#include <string>

using namespace std;

// Don't touch this:
// ------------------------------------------------------------
class TimeManagerHandler
{
  public:
    friend std::ostream& operator<<(std::ostream& os, TimeManagerHandler const& timer)
    {
        return os << timer.currentTime;
    }
   
  private:
    string currentTime = "2020.10.2:3123:23";
};

string DebugPrefix()
{
  return "Debugging: ";   
}
// ------------------------------------------------------------

// Let's continue with something simple!
// Here is a function that should log data, it's all fine, except you may want to use
// different prefix or data type or whatever! To make it more flexible, use template, to
// make it more generic!
void logData(string prefix, int actualData)
{
  cout << prefix << " " << actualData;
}

// TODO: Use the tempalte to rewrite these functions, so that you minimize the amount of code written!
// Want to read about repeating yourself? READ THIS! https://en.wikipedia.org/wiki/Don%27t_repeat_yourself

int main()
{
  // This works:
  logData("Time:", 10);
  
  TimeManagerHandler timer;
  
  // Another TODO: Fix this code, so that using template, it will work.
  // This doesn't:
  logData(DebugPrefix(), timer);
}