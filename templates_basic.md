# Templates

## Basics

  Templates are used to create generic function / classes, to be able to handle different types, without having the need to
  create separate copy for each of them, for each type.

  Why is it used? shortly: don't write repeated code.

  For example:

  ```c++
  void printIntegerValue(int value)
  {
    cout << endl << value << endl;
  }
  ```
  
  This function can only print one type, which is int.
  To cover different types but with same functionality, that's where templates comes in.
  
  ```C++
  template<typename DataType>
  void genericPrinting(DataType genericValue)
  {
    cout << endl << genericValue << endl;
  }
  ```

  Keyword "template" will tell that the function or class will be generic and then
  declared typename or class inside <> can
  can be used to indicate that a type can generic.

  From this, one type can be generic, the DataType just is used to identify a type.
  template<typename DataType>, DataType can be renamed to anything that is more suitable.

  When calling a function with typename DataType, compiler deduces type of DataType, by
  looking at what value was passed to it.
  
  For each different type of function call with typname DataType, there will be generated
  a copy of that function at compiletime.

  Example, for previous function genericPrinting, calling this function with different
  arguments, 
  
  ```c++
  genericPrinting("Hello");
  genericPrinting(10);
  ```
  
  This will generate both functions:
  
  ```c++
  void genericPrinting(std::string value) { ... }
  void genericPrinting(int value) { ... }
  ```
  
  * **Note**: typename is used most of the time, but previously, class could also be used, like this:
  ```c++
  template<class DataType>
  void olderVariantofGenericPrinting(DataType genericValue)
  {
    cout << endl << genericValue << endl;
  }
  ```
  It doesn't mean that only classes can be passed, it was (and still is valid) to introduce a
  type parameter.
  
  ##### Exercise 1: template_exercises/1_exercise_basic_function.cpp
  Go there and read the instructions (in the comments)
  
  * **Note**: Templates support default arguments, but default arguments can't be use to deduce type.
  For example, consider this function.
  
  ```c++
  template<typename DataType>
  void genericPrinting(DataType genericValue = "Empty")
  {
    cout << endl << genericValue << endl;
  }
  
  genericPrinting("This is fine"); // Fine
  genericPrinting(9999); // Is totally fine as well
  genericPrinting(); // Error!
  
  // Something along the lines of:
  .... couldn't infer template argument 'DataType ...
  ```

  ##### Exercise 2: template_exercises/2_exercise_basic_function_multiple.cpp
  Okay, might as well throw in another one here.
  
  It is possible to also explicitly specify the desired type for
  a template, in the usage.
  
  ```c++
    genericPrinting<float>(10.23f);
  ```
  Specifying different type than parameter, would result in compilation error.
  
  Deducing return type [C++11] Let's look at the horrors first before tasting some fine wine...
  
  There is a way to let compiler deduce return type, and in C++11, and that is to use decltype.
  Downside is that part of function code has to be included, to be able to decide the type.
  For example, look at this (stolen) code:
  
  ```c++
  template<typename LeftType, typename RightType>
  auto sumValues(LeftType leftValue, RightType rightValue) -> decltype(leftValue + rightValue)
  {
    return leftValue + rightValue;
  }
 
  sumValues(2.1f, 3); // Type will be deduced to float
  ```
  
  TODO: Expand on this, by decay / common type.
  
  * **Note**: There is another way to skip decltype, deducing return type! [C++14 specific] So beware!
  
  Since C++ 14, auto is supported for return types! How to? Here:
  
  ```C++
  // Okay, my imagination ended here, one is for float/double other is for short / long
  template<typename ExactValueType, typename RoundedDataType>
  auto sumDifferentTypes(ExactValueType exactValue, RoundedDataType roundedValue)
  {
    return exactValue + roundedValue;
  }
  
  sumDifferentTypes(1.2f, 20); // return type will be deduced to float.
  ```
  
  * **Note**: If... there are multiple return types, the type of return types must match,
  otherwise there will be error!  
  
  _TODO: Explain about two phase instantioation ?
   will they even care about it? (Ask the people!)

## Multiple arguments

  Template can also support multiple types, and can be used like this.
  
  ```c++
  template<typename PrefixType, typename PrintedValueType>
  void print(PrefixType prefix, PrintedValueType value) 
  {
     cout << prefix << " : " << value << endl;
  }
  
  print("Seconds", 40);
  ```

  Each type PrefixType and PrintedValueType can be different.

  To have multiple arguments, there is another way to create, than
  declare all parameters manually. Reason? Can be many! For example, instead
  of creating many different functions with different number of parameters or
  having one function that covers them with default values. (oh right, default values, scroll up!)
  
  TODO: Find a little better reasons, current ones: [This section is in dire need of expansion]
   * Macros, hard to debug (but so are templates!).
   * Multiple calls with initialize, start and end, ... kinda too much work.
   * Only one type for all arguments.
   * va_arguments are resolved at runtime.
   * templates are pre-generated at compile-time!
   
  This is an example of how to use VA_arguments, but, don't use them for the exercise!
    
  There are va_* macros, that reside in stdarg.h (or cstdarg.h depends where you are, geographically)
  These are built to accept multiple arguments.
  
  From cplusplus.com/reference/cstdarg/va_arg
  [Stolen code]
  
  ```c++
  int findMax(int numberOfArgs, ...)
  {
    int indexOfArg, currentValue, largestSoFar;
    
    va_list vl;
    va_start(vl, numberOfArgs);
    largest = va_arg(vl, int);
    
    for (indexOfArg = 1; indexOfArg < n; indexOfArg++)
    {
      currentValue = va_arg(vl,int);
      largest = (largest>val)?largest:val;
    }
    va_end(vl);
    return largest;
  }
  
  int main ()
  {
    cout << FindMax (7,702,422,631,834,892,104,772); // will print: 892
    return 0;
  }
  ```
  
  TODO: ´Replace this / Insert explanation of this.
  va_list <- holds info about arguments, and prepares for va_arg calls
  
  va_start <- prepares va_list, (it is passed as first argument)
  to be able to retreive information about arguments.
  
  va_arg <- modifies parameter, (va_list) so that call to va_arg, retreives next argument
  in the list.
  
  Template can also be used to handle multiple arguments, but with that, also be able to handle
  different types! Declaration will look like this: 
  
  template<typename... DataTypes>
  ... indicates that the function can accept multiple parameters, and even
  be of different type.
  
  But, to be able to go through each argument, it cannot be looped through the usual way.
  So that's why to go through each argument, recursion has to be used. Since the Ts... can be empty,
  to go through with recursion it needs to have a base, once the arguments runs out.
  
  How this look like:
  
  ```c++
  template<typename PrintableType>
  void print(PrintableType value)
  {
      cout << "End " << value << endl;
  }
    
  template<typename T, typename... DataTypes>
  void print(T firstArg, Types... args)
  {
    cout << "Cout " << firstArg << endl;
    print(args...);
  }
  ```
  
  Calling, will call recursively print.
  Inside print(args...), the ... unpacks the arguments.
  print("Mooo", 10, 20.01f);
  
  Once the arguments are being unpacked until end, then it is reaching end,
  and ending the recursion.
  
  In case you have a question, why two functions? well, to start and end recursion!
  
  How about test the same code? as an exercise?
  ##### Exercise 3: template_exercises/3_exercise_still_basics_parameters.cpp.cpp

## Specialization
  As functions can be used with template, so can classes.
  
  Simply declare class by:
  ```C++
  template<typename DataType>
  class MyPrivateDataHolder
  {
  public:
  
  private:
    DataType genericNameForData;
  
  public:
    DataType get() { return genericNameForData; }
    void set(DataType value) { this->genericNameForData = value; }
  };

  MyPrivateDataHolder<int> dataStorage;
  ```

  Now, the MyPrivateDataHolder will hold any type that is specified, but,
  there is also a way to handle specific types in such class.
  2.5

## Patterns



