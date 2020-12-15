#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Let's write some ugly code.

// Just forward declaration
class Dog;
class DogCollar;

// Let's pretend this is somewhere...

// A Dog has a collar, and a collar is put on a dog :(
// The point of this, that both will have a pointer that point to each other.
// And a problem will arise when this happens: "Cyclic reference", or something similar.
class Dog
{
public:
  Dog() { cout << endl << "Creating Dog"; }
  ~Dog() { cout << endl << "Releasing Dog"; }

  void putCollar(shared_ptr<DogCollar> collar);

  void bark() { cout << endl << "woof woof"; }

private:
  shared_ptr<DogCollar> collar;
};

void Dog::putCollar(shared_ptr<DogCollar> collar)
{
  this->collar = collar;
}

class DogCollar
{
public:
  DogCollar() { cout << endl << "Creating DogCollar"; }
  ~DogCollar() { cout << endl << "Releasing DogCollar"; }

  void setOwner(shared_ptr<Dog> dog);

  void askDogForLocationRemotely();

private:
  shared_ptr<Dog> dog;
};

void DogCollar::setOwner(shared_ptr<Dog> dog)
{
  this->dog = dog;
}

void DogCollar::askDogForLocationRemotely()
{
  dog->bark();
}

void dogIsInTheFunction(bool dontPutCollarOn = false)
{
  auto dog = make_shared<Dog>();
  auto collar = make_shared<DogCollar>();

  if (dontPutCollarOn == false) {
    dog->putCollar(collar);
  }
  collar->setOwner(dog);

  // Use cases
  collar->askDogForLocationRemotely();
}

int main()
{
  dogIsInTheFunction();

  cout << endl << "Is there any sight of Realising DogCollar / Dog here?" << endl;

  // Notice the difference? Once two shared pointers point to each other,
  // both refuse to release because the reference count will never be decreased, because
  // they both point to each other. Welcome to weak_ptr exercise!
  dogIsInTheFunction(true);

  cout << endl << "The second call has released the memory though..." << endl;

  // TODO: So the exercise, change one of the owners from having shared pointer to having a weak_ptr,
  // so that the first call to dogIsInTheFunction() is also releasing the memory.

  return 0;
}