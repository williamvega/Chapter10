# Chapter 10

## Chapter 10.1 Introduction Notes
Goal: Operator Overloading

For example, `<<` is an overloaded operator as it both used as a stream insertion operator and a bitwise left-shift operator.

## Chapter 10.2 Using Overloaded operators of Standard Lib Class `string`

We use the `boolalpha` stream manipulator to specifiy that each value of the bool expression should be displayed as either the word `true` or `false`.

**Providing some context**

To provide some context to the operator overloading discussio, we should definetly use the `string` class as an example. The reason is because the string class has already overloaded many oeprators, and we can study their usagge accordingly.

Some examples include:

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s1{"happy"};
    string s2{"birthday"};
    string s3; // empty string

    // first, note the many overloaded bool operators
    cout << "s1 is " << s1 "; s2 is " << s2 << "; s3 is " << s3 << "\n";
    cout << "comparing s2 and s1 results in:\n" << boolalpha <<
    	 << "== is " << (s2 == s1)
	 << "\n!= is " << (s2 != s1)
	 << "\n> is " << (s2 > s1);
    // and so on, with many overloaded operators of the class string

    // there are many more examples in the tb, but the most notable are...
    string s4{s1}; // the copy constructor
    s4 = s4; // the copy constructor on itself
}
```
We are most concerned wtih memory management and the copy constructors.

## Chapter 10.3 Fundementals of Operator Overloading

C++ does not allow new operators to be created, but we can modify existing.

We must provide define the operators functions to use on the class, with three exceptions:

1. The `=` assingment operator may be used to perform *memberwise agreement* of its data members (each data member is assigned from the source object on the right to the target object on the left. This is especially dangerous when using objects with pointers.
1. The address `&` operator returns a pointer to the object; we may overload if desired.
1. The comma operator evalutes to its left then the expression on its right. Then returns value of the right.

There are also operators that may not be overloaded:

1. `.` operator.
1. `.*` operator. Pointer to a member.
1. `::` operator. Scope.
1. `?:` operator. Ternary operator.

There are also some restrictions on overloading operators:
1. Precedence is unfuckaroundable.
1. Associativity (left to right / right to left) is unfuckaroundable.
1. Arity is unfuckaroundable (number of operands an operator takes).
1. Cannot create new operators.
1. Cannot overload on fundemental types - only user-defined types.
1. Realted operators (such as `+` and `+=` must be overloaded seperately).
1. When overloading `()`,`[]`,`->`, or any assignment operator, operator overloading function MUST be decalred as a class member. All other operator overloading functions may be decalred as member functions or non-member functions.

## Chapter 10.4 Overloading Binary Operators

To overload binary operators (aka two operands), there are two main approaches:

**Binary Overloaded Operators as Member Functions**

```cpp
class String {
public:
	bool operator<(const String&) const;
	...
};
```

If we were to use this operator in code, the compiler would read it as `y.operator<(z)`, where `y` and `z` are `String` objects.

Overloaded operator functions for binary operators can only be member functions if both the left operand and the object in which the function are a member are of the same type.

**Binary Overloaded Operators as Non-Member Functions**

```cpp
bool operator<(const String&, const String&);
```

We can read this in usage as `operator<(y,z)`, if `y` and `z` are `String` objects.

## Chapter 10.5 Overloading the Binary Stream Insertion and Stream Extraction  Operators

When overloading the binary stream insertion and extraction operators, we must consider the fact that:
1. We want the usage to be `cout << object` and `cin >> object`. Well, we cannot modify the C++ standard library to overload the `<<` and `>>` operators, so we must add the overloaded operators as non-member functions to the object's class.
1. Since we are adding the functions as non-member operators to the object's class, the `ostream` and `istream` reference must added as the left parameter of the binary operator overloaded function, and the following parameter can be a reference to the class type.
1. If we need to access the class type's private data members, the overloaded function must be a `friend` of the class.

With these three considerations in mind, consider the files:
1. PhoneNumber.h will contain the header information for the class PhoneNumber and prototypes for the overloaded operators, as well as data members of the class.
1. PhoneNumber.cpp will contain the definition of the friend overloaded operators, and would contain the definitions of any other functions we declared in PhoneNumber.h.
1. main.cpp contains the code to show the functionality of the overloaded operators.

We can see the files in action in the subdirectory included, called PhoneNumber.

## Chapter 10.6 Overloading Unary Operators

Considerations when overloading a unary operator:
1. The overload must be non-static, so it may access non-static data members.
1. The overload will have no arguments, it it is a member function, or one argument, if it is a non-member function.

Two examples showcasing this:

**Unary Overloaded Operators as Member Functions**

```cpp
class Person {
public:
	bool operator!() const;
};
```

**Unary Overloaded Operators as Non-Member Functions**

```cpp
bool operator!(const String&); 
```

## Chapter 10.7 Overloading the Increment and Decrement Operators

The increment and decrement operators present their own challenges, as each has two variants: the prefix and the postfix. This challenge is resolved with distinct signatures to differentiate the two.

The solution is not elegant, but it works. It uses dummy values.

Lets show how each of these are prototyped:

**Prefix Increment as Member Function**
`++p1` would be:
```cpp
...
// in Person class
    Person& operator++();
...
```

**Prefix Increment as Non-Member Function**
`++p1` would be:
```cpp
Person& operator++(Person&);
```

**Postfix Increment as Member Function**
`p1++` would be:
```cpp
...
//in Person class
    Person operator++(int);
...
```

**Postfix Increment as Non-Member Function**
`p1` would be:
```cpp
Person operator++(Person&, int);
```

The int will be automatically provided a zero during operation calling, and the differentiation will be made.

Note that the prefix increment operator returns a reference, while the postfix operator returns the value. The postfix will typically return a temporary object containing the original value of the object before incrementing. These object are treated as rvalues, and cannot be used on the left side of an assignment. Meanwhile, the prefix returns the actual incremented object, and is treated as an lvalue in a continuing expression.

The text offers a performance tip of giving prefix operators precedence, as we get values instead of creating whole new objects.