#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <list>
#include <vector>
template <class Key>
class Sequence {
 public:
  virtual bool search(const Key& k) const = 0;
  virtual bool insert(const Key& k) = 0;
  virtual bool isFull() const = 0;
};

template <class Key>
class dynamicSequence: public Sequence<Key> {
 public:
  dynamicSequence() = default;
  bool search(const Key& k) const;
  bool insert(const Key& k);
  bool isFull() const;
  size_t size() const { return list_.size(); }
  const std::list<Key>& getList() const { return list_; }
  Key operator[](int i);
  bool isInList(const Key& k) const;

 private:
  std::list<Key> list_;
};

template <class Key>
bool dynamicSequence<Key>::search(const Key& k) const {
  for (auto& element : list_) {
    if (element == k) {
      return true;
    }
  }
  return false;
}

template <class Key>
bool dynamicSequence<Key>::insert(const Key& k) {
  if(!search(k)) {
    list_.push_back(k);
    return true;
  } else {
    std::cout << "The element " << k << " could not be inserted correctly in the sequence" << std::endl;
    return false;
  }
}

template <class Key>
bool dynamicSequence<Key>::isFull() const {
  return false;
}

template <class Key>
Key dynamicSequence<Key>::operator[](int i) {
  auto it{list_.begin()};
  std::advance(it, i);
  return *it;
}

template <class Key>
bool dynamicSequence<Key>::isInList(const Key& k) const {
  for (auto& element : list_) {
    if (element == k) {
      return true;
    }
  }
  return false;
}

template <class Key>
class staticSequence: public Sequence<Key> {
 public:
  staticSequence();
  staticSequence(size_t blocksize);
  bool search(const Key& k) const override;
  bool insert(const Key& k) override;
  bool isFull() const;
  size_t size() const { return n_elements_; }
  const Key getData(int i) const { return block_[i]; }

 private:
  size_t blocksize_;
  int n_elements_;
  std::vector<Key> block_;
};

template <class Key>
staticSequence<Key>::staticSequence() {
  n_elements_ = 0;
  blocksize_ = 0;
}

template <class Key>
staticSequence<Key>::staticSequence(size_t blocksize) {
  n_elements_ = 0;
  blocksize_ = blocksize;
}

template <class Key>
bool staticSequence<Key>::search(const Key& k) const {
  int position{0};
  for (auto& element : block_) {
    if (element == k) {
      std::cout << " element " << k << " found in " << position << std::endl;
      return true;
    }
    position++;
  }
  return false;
}

template <class Key>
bool staticSequence<Key>::insert(const Key& k) {
  if (!isFull() && !search(k)) {
    n_elements_++;
    block_.push_back(k);
    std::cout << " element " << k << " inserted " << std::endl;
    return true;
  } else {
    std::cout << "The element " << k << " could not be inserted correctly in the sequence" << std::endl;
    return false;
  }
}

template <class Key>
bool staticSequence<Key>::isFull() const {
  if (n_elements_ == blocksize_) {
    std::cout << n_elements_ << " elements in the sequence" << std::endl;
    std::cout << blocksize_ << " elements in the block" << std::endl;
    return true;
  }
  return false;
}



#endif // SEQUENCE_H