# Templates

## Basics

  Templates are used to create generic function / classes, to be able to handle different types, without having the need to
  create separate copy for each of them, for each type.

  Why is it used? shortly: don't write repeated code.

  For example:

  ```c++
  int max(int a, b)
  {
    return b < a ? a : b;
  }
  ```

  To cover different types but with same functionality, that's where templates comes in.
  
  ```c++
  template<typename T>
  T max(T a, T b)
  {
    return b < a ? a : b;
  }
  ```

  Keyword "template" will tell that the function or class will be generic and then declared typename or class inside <> can
  can be used to indicate that a type can generic.

  From this, one type can be generic, the T just is used to identify a type.
  template<typename T>

  The T can be any name, it does not matter, but typename keyword is needed.
  
    When calling a function with typename T, compiler deduces type of T, by
  looking at what value was passed to it.
  
  For each different type of function call with typname T, there will be generated
  a copy of that function at compiletime.
  
  Example:
  
  ```c++
  template<typename T>
  void print(T value) { ... }
  
  print("Hello");
  print(10);
  
  This will generate both functions:
  
  void print(std::string value) { ... }
  void print(int value) { ... }
  ```
  
  Small note about default arguments, the type cannot be deduced.
  For example, consider this function.
  
  ```c++
  template<typename T>
  void print(T value = "")
  {
     std::cout << value << std::endl;
  }
  ```
  
  When using function like this:
  print("Hello");
  The type T will be deduced to std::string, while
  print();
  will not be able to deduce from default argument, thus, will result in an error.
  
  # TODO: Explain about return type deduction.

## Multiple arguments

  Template can also support multiple types, and can be used like this.
  template<typename A, typename B>
  void print(A a, B b) { ... }

  Each type A and B can be different.

  To have multiple arguments, there is another way to create, than
  declare all parameters manually.
  
  Template declaration will look like this: 
  
  template<typename... Ts>
  ... indicates that the function can accept multiple parameters, and even
  be of different type.
  
  But, to be able to go through each argument, it cannot be looped through the usual way.
  So that's why to go through each argument, recursion has to be used. Since the Ts... can be empty,
  to go through with recursion it needs to have a base, once the arguments runs out.
  
  How this look like:
  
  ```c++
  template<typename T>
  void print(T t)
  {
      cout << "End " << t << endl;
  }
    
  template<typename T, typename... Types>
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


## Patterns