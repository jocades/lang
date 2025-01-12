#include <iostream>
#include <memory>
#include <string>
using namespace std;

class User {
 public:
  string name;
  int age;

  explicit User(string name, int age) : name(std::move(name)), age(age) {
    cout << "Constructed User " << this->name << '\n';
  };

  ~User() {
    cout << "Dropping " << name << '\n';
  }

  void display() const {
    cout << "User(name=" << name << ", age=" << age << ")\n";
  }
};

void take_by_ref(const User& user) {  // &user
  // user.name = "John"; -> Error!
  user.display();
}

void take_by_mut_ref(User& user) {  // &mut user
  user.name = "John";
  user.display();
}

auto take_by_value(unique_ptr<User> user) {  // user (dropped when this fn ends)
  user->name = "Foo";
  user->display();
}

unique_ptr<User> task() {
  unique_ptr<User> user = make_unique<User>("Bob", 25);
  take_by_ref(*user);
  take_by_mut_ref(*user);
  return user;
}

auto other() {
  auto user = make_unique<User>("Alice", 10);
  return user;
}

int main() {
  auto user2 = other();
  take_by_value(std::move(user2));
  // user2->display(); -> Error: user2 now points to invalid memory!

  unique_ptr<User> user1 = task();
}
