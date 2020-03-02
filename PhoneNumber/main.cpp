#include <iostream>
#include "PhoneNumber.h"
using namespace std;

int main() {
  PhoneNumber phone;

  cout << "Enter phone number in the form (555) 555-5555: \n";

  cin >> phone;

  cout << phone << "\n";
}
