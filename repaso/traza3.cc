#include <iostream>

class Base {
protected:
    int baseVal_;
public:
    Base(int val = 1) : baseVal_(val) {}

    virtual int compute(int x) const { return x + baseVal_; } // const versión
    virtual int compute(int x) { return x * baseVal_; }       // no const versión
};

class Intermediate : public Base {
protected:
    int factor_;
public:
    Intermediate(int val = 2) : Base(val), factor_(val + 1) {}

    int compute(int x) const override { return x - factor_; }
    int compute(int x) override { return x + factor_ + baseVal_; }
};

class Derived : public Intermediate {
    int multiplier_;
public:
    Derived(int val = 3) : Intermediate(val), multiplier_(val * 2) {}

    int compute(int x) override { return (x + baseVal_) * multiplier_; }
};

int main() {
    Base* ptr1 = new Base(5); // Base::Base(5) -> baseVal_ = 5
    std::cout << "ptr1->compute(2): " << ptr1->compute(2) << std::endl; // Base::compute(2) {return 2 * 5} = 10

    Base* ptr2 = new Intermediate(4); // Intermediate::Intermediate(4) -> factor_(4+1 = 5) ; Base::Base(4) -> baseVal_ = 4
    std::cout << "ptr2->compute(3): " << ptr2->compute(3) << std::endl; //Intermediate::compute(3) override {return 3 + 5 + 4} = 12

    Intermediate* ptr3 = new Derived(2); // Derived::Derived(2) -> multiplier_(2*2) = 4 ; Intermediate::Intermediate(2) -> factor_(2+1) = 3; Base::Base(2) -> baseVal_ = 2
    std::cout << "ptr3->compute(1): " << ptr3->compute(1) << std::endl; // return {(1+2) * 4} = 12

    return 0;
}
