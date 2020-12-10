// Second exercise! (Just kidding, it's third)
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

// You should have finished previous exercise!, but I wont give you solution here, or anywhere!
// What is boring in life except for reading long text? writing parameters! or guessing how many you want!
// TODO: With help of, multiple arguments, more specifically, template<typename... DataTypes>
// create a function (actually two, you should know the reason why by now), to be able to handle
// any number of arguments sent to ONE function.
void logData(string prefix, int actualData)
{
  cout << prefix << " " << actualData;
}

int main()
{
  // This works:
  logData("Time:", 10);
  
  TimeManagerHandler timer;
  
  // TODO: After you have fixed the function, this should be able to work!
  logDataAllData(DebugPrefix(), timer, " : ", 500, "\n");
}