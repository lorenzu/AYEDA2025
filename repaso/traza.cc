#include <iostream>

class A
{ private:
    int _a;
  public:
    A(int x): _a(x)       {}
    virtual int f(int x)  { return g(x)*g(); }
    virtual int g(int x=2) const { return x * _a; }
};

class B: public A
{ private:
    int _b;
  public:
    B(int x=3): A(x*x), _b(x)  {} 
    virtual int f(int x) const { return g(x * _b); }
};

class C: public B
{ public:
  C(int x=3): B(x)         {}
  int f(int x) const       { return g(x + x); }
  int g(int x) const       { return x; }
};

int main()
{ 
  A *a = new A(3);
  std::cout << a->f(3) << std::endl; 
  
  A *b = new C(2);
  std::cout << b->f(5) << std::endl;


  B *c = new C;
  std::cout << c->f(7) << std::endl;
  
  return 0;
}

/* SOLUCIÖN
A *a = new A(3);
A::A(3) _a=3
a->f(3) => A::f(3) => A::g(3) _a=3 * A::g(2) _a=3 => 3*3 , 2*3
54

A *b = new C(2);
C::C(2) => B::B(2) _b=2 => A::A(4) => _a=4 _b=2
b->f(5) => A::f(5) => C::g(5) , C::g(2) => 5 * 2
10

B *c = new C;
C::C(3) => B::B(3) _b=3 => A::A(9) => _a=9 _b=3

c->f(7) => C::f(7) => C::g(14)
14
*/
