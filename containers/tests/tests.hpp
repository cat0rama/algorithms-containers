#ifndef TESTS_HPP_
#define TESTS_HPP_

#include <exception>
#include <iostream>

#include "../s21_containers.h"

// Тестовые классы

class Test {
 public:
  Test() { std::cout << "construct" << std::endl; }

  Test(std::string, int) { std::cout << "string:int" << std::endl; }

  Test(int _a) : a(_a) { a = _a; }

  Test(Test&& c) {
    a = c.a;
    std::cout << "move";
  }

  Test(const Test& e) {
    a = e.a;
    std::cout << "copy";
  };

  Test& operator=(const Test& elem) {
    a = elem.a;
    std::cout << "move";
    return *this;
  }

  Test& operator=(Test&& elem) {
    a = elem.a;
    return *this;
  };

  friend bool operator>(const Test& a, const Test& b) { return a.a > b.a; }

  friend bool operator<(const Test& a, const Test& b) { return a.a < b.a; }

  int getA() { return a; }

  ~Test() { std::cout << "destructor" << std::endl; }

 public:
  int a;
};

class ExceptionTest {
 public:
  ExceptionTest() { std::cout << "construct" << std::endl; }

  ExceptionTest(std::string, int) { std::cout << "string:int" << std::endl; }

  ExceptionTest(int _a) : a(_a) { a = _a; }

  ExceptionTest(ExceptionTest&& c) noexcept {
    a = c.a;
    std::cout << "move";
    // throw std::exception("this is sparta!");
  }

  ExceptionTest(const ExceptionTest& e) {
    a = e.a;
    // throw std::exception("this is sparta!");
  };

  ExceptionTest& operator=(const ExceptionTest& elem) {
    a = elem.a;
    std::cout << "move";
    // throw std::exception("this is sparta!");
    return *this;
  }

  ExceptionTest& operator=(ExceptionTest&&) noexcept {
    // throw std::exception("this is sparta!");
    return *this;
  };

  friend bool operator==(const ExceptionTest& a, const ExceptionTest& b) {
    return a.a == b.a;
  }

  friend bool operator>(const ExceptionTest& a, const ExceptionTest& b) {
    return a.a > b.a;
  }

  int getA() { return a; }

  ~ExceptionTest() = default;

 public:
  int a;
};

// Класс для проверки приватных функций тестируемого класса
template <typename T>
class TestOther : public T {
 public:
  TestOther() = default;

  ~TestOther() = default;

 public:
  void im() const noexcept { std::cout << "im TestOther" << std::endl; }
};

#endif
