/*
#include <iostream>

class Base {
protected:
    int x;
public:
    Base() { x = 5; }

    virtual int get() const { return 0; }      // Sobrecarga 1: versión const
    virtual int get() { return x; }            // Sobrecarga 2: versión no const
};

class Derivada : public Base {
protected:
    int y;
public:
    Derivada() { y = 10; }

    int get() const { return y; }              // Oculta Base::get() const // si quitamos el const el valor es 10
    int get() { return y + 1; }                // Oculta Base::get() // si quitamos el const el valor es 11
  };

int main() {
    Base* ptr = new Derivada;
    std::cout << ptr->get();
}
*/

/*

#include <iostream>

class A {
private:
    int a_;
public:
    A(int x = 10): a_(x) {}

    int f(int x)  { return g(x + x); }

    virtual int g(int x) const { return x % a_; }
};

class B : public A {
private:
    int b_;
public:
    B(int x): b_(x) {}

    virtual int f(int x) const { return g(x + x); }

    int g(int x) const { return x % b_; }
};

class C : public B {
private:
    int c_;
public:
    C(int x = 5): B(x), c_(x) {}

    int f(int x) { return g(x * c_); }
};

int main() {
    A *a = new A; // A::A(10) -> a_ = 10
    std::cout << a->f(5) << std::endl;  // A::f(5) return (g(5 + 5 = 10)) ; A::g(10) return 10%10 = 0

    A *b = new B(7); // B::B(7) -> b_ = 7
    std::cout << b->f(4) << std::endl; // A::f(4) return g(4 + 4 = 8) -> B::g(8) return (8 % 7) = 1

    B *c = new C; // C::C(5) -> c_ = 5; B::B(5) -> b_ = 5 
    std::cout << c->f(3) << std::endl;  // C::f(3) return g(3*5 = 15) -> B::g(15) return (15%5) = 0
    A *c2 = new C; // C::C(5) -> c_= 5; B::B(5) -> b_ = 5
    std::cout << c2->f(3) << std::endl; // A::f(3) return g(3 + 3) B::g(6 %5) -> metodo no virtual return 1

    return 0;

}
*/


#include <iostream>

class A {
private:
    int a_;
public:
    A(int x = 10): a_(x) {}

    virtual int f(int x) { return g(x + x + 1); }

    int g(int x) const { return x % a_; }
};

class B : public A {
private:
    int b_;
public:
    B(int x = 3): b_(x) {}

    int f(int x) const { return g(x + x); }

    virtual int g(int x) const { return x * b_; }
};

class C : public B {
private:
    int c_;
public:
    C(int x = 5): B(x), c_(x) {}

    int f(int x) { return g(x * c_); }
    int g(int x) const { return x + c_; }
};

int main() {
    A *a = new B; // B::B -> b_ = 3;
    std::cout << a->f(5) << std::endl;  //
    /*
    no sobreescribe A::f pq no es const A::f(5) return g(5 + 5 + 1) A::g(11 % 10) = 1
    */
    A *b = new C(7); // C::C(7) -> c_ = 7; B::B(7) -> b_ = 7
    /*
    sobreescribe A::f ya que ambos no tienen const y escoge C::f pq no es virtual
    C::f(4) -> return g(4 * 7) // g(28)
    sobreescribe A::g , y estamos en C por lo tanto se escoge C::g(28)
    C::g(28) -> return (28 + 7) = 35
    */
    std::cout << b->f(4) << std::endl;

    B *c = new C;  // C::C -> c_ = 5; B::B(5) -> b_ = 5
    /*
    No sobreescribe B::f pq no es const por lo tanto escogemos B::f(3)
    B::f(3) -> return g(3+3) // g(6)
    Sí sobreescribe B::g ya que ambos son const y en C no es virtual, escogemos C::g(6)
    C::g(6) -> return 6 + 5 = 11
    */
    std::cout << c->f(3) << std::endl;  

    return 0;

}
