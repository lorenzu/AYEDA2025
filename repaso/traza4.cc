// EJERCICIOS DE POLIMORFISMO DE AYEDA

#include <iostream>

using namespace std;
template<class T>
class A {
  private:
    T a_;
  public:
    A(T x) {a_ = x; };

    T f(int x) { 
      std::cout << "A::f" << std::endl;
      // std::cout << "x*x = " << x*x << std::endl;
      return g(x*x);
    };

    virtual T g(T x) {
      std::cout << "A::g" << std::endl;
      // std::cout << "x/a_ = " << x/a_ << std::endl;
      return (x / a_); 
    };
};

template<class T>
class B : public A<T> {
  private:
    T b_;
  public:
    B(T x = 3) : A<T>(x*x), b_(x) {};

    T f (int x) {
      std::cout << "B::f" << std::endl;
      return A<T>::f(x + b_); 
    };

    T g(T x) { 
      std::cout << "B::g" << std::endl;
      return x % b_;
    };
};

using T = int;

int main() {
  std::cout << "Ejercicio de polimorfismo - examen Mayo 22-23\n";
  A<T> a(10); // A::a_ = 10
  std::cout << a.f(5) << std::endl; // A::f(5) = g(5 * 5 = 25); A::g(25) return (25/10) = 2
  B<T> b; // B::b_ = 3; A::a_ = 3*3 = 9
  std::cout << b.f(3) << std::endl; // B::f(3) return A::f(3+3 = 6) = g(6*6 = 36); B::g(36) return 36 % 3 = 0

  A<T> *c = new B<T>(5); //B::b_ = 5; A::a_ = 5*5 = 25
  std::cout << c->f(3) << std::endl; //Está sobreescrito en B pero en A no es virtual
  // por lo tanto A::f(3) return g(3*3 = 9); g está sobreescrito en B y en A es virtual por lo tanto B::g(9) return 9%5 = 4
  return 0;
}