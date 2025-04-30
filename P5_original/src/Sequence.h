#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <list>
#include <vector>
template <class Key>
class Sequence {
 public:
  virtual Key& operator[](const unsigned&) = 0;
};

template <class Key>
class StaticSequence : public Sequence<Key> {
 public:
  StaticSequence(unsigned int s, std::fstream &filename);
  StaticSequence(unsigned int s, std::string option);
  ~StaticSequence() {
    delete[] data_;
  }
  Key& operator[](const unsigned& i) override {
    if(i < size_) {
      return data_[i];
    } else {
      std::cerr << "Index out of bounds" << std::endl;
      throw std::out_of_range("Index out of bounds");
    }
  }

  unsigned int getSize() const {
    return size_;
  }

  

  private:
  unsigned int size_;
  std::vector<Key> data_;
};


template <class Key>
StaticSequence<Key>::StaticSequence(unsigned int s, std::fstream &filename) {
  size_ = s;
  data_.resize(size_);
  long value;
  for (unsigned int i = 0; i < size_; i++) {
    filename >> value;
    data_[i] = Key(value); // NIF
  }
}

template <class Key>
StaticSequence<Key>::StaticSequence(unsigned int s, std::string option) {
  long value;
  if (option == "random") {
    size_ = s;
    data_.resize(size_);
    for (unsigned int i = 0; i < size_; i++) {
      value = rand() % 100;
      data_[i] = Key(value); // NIF
    }
  } else if(option == "manual") {
    std::cout << "Enter the elements of the sequence: " << std::endl;
    for (unsigned int i = 0; i < size_; i++) {
      std::cout << "Element " << i + 1 << ": ";
      std::cin >> value;
      data_[i] = Key(value); // NIF
    }
  } else {
    std::cout << "Invalid option" << std::endl;
  }
}






#endif // SEQUENCE_H