#ifndef SORTMETHOD_H
#define SORTMETHOD_H
#include "Sequence.h"
#include <iostream>

template <class Key>
void InsertionSort(StaticSequence<Key>* s, bool trace = false) {
  int size = s->getSize();
  std::cout << "Insertion Sort" << std::endl;
  std::cout << "ORIGINAL: ";
  for (int i = 0; i < size; i++) {
    std::cout << (*s)[i] << " ";
  }
  std::cout << std::endl;
  for (int i = 1; i < size; i++) {
    Key key = (*s)[i];
    int j = i - 1;
    while (j >= 0 && (*s)[j] > key) {
      (*s)[j + 1] = (*s)[j];
      j--;
    }
    (*s)[j + 1] = key;
    if (trace) {
      std::cout << "Step " << i << ": ";
      for (int k = 0; k < size; k++) {
        std::cout << (*s)[k] << " ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << "SORTED: ";
  for (int i = 0; i < size; i++) {
    std::cout << (*s)[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Insertion Sort Finished" << std::endl;
}

template <class Key>
void ShakeSort(StaticSequence<Key>* s, bool trace = false) {
  int size = s->getSize();
  std::cout << "Shake Sort" << std::endl;
  std::cout << "ORIGINAL: ";
  for (int i = 0; i < size; i++) {
    std::cout << (*s)[i] << " ";
  }
  std::cout << std::endl;
  bool swapped = true;
  while (swapped) {
    swapped = false;
    for (int i = 0; i < size - 1; i++) {
      if ((*s)[i] > (*s)[i + 1]) {
        std::swap((*s)[i], (*s)[i + 1]);
        swapped = true;
      }
    }
    if (!swapped) break;
    swapped = false;
    for (int i = size - 2; i >= 0; i--) {
      if ((*s)[i] > (*s)[i + 1]) {
        std::swap((*s)[i], (*s)[i + 1]);
        swapped = true;
      }
    }
    if (trace) {
      std::cout << "Step: ";
      for (int k = 0; k < size; k++) {
        std::cout << (*s)[k] << " ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << "SORTED: ";
  for (int i = 0; i < size; i++) {
    std::cout << (*s)[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Shake Sort Finished" << std::endl;
}


template <class Key>
void QuickSortAlgorithm(StaticSequence<Key>& s, int low, int high, int& it, bool trace) {
  if (low < high) {
    Key pivot = s[(low + high) / 2];
    int i = low;
    int j = high;
    while (i <= j) {
      while (s[i] < pivot) i++;
      while (s[j] > pivot) j--;
      if (i <= j) {
        std::swap(s[i], s[j]);
        i++;
        j--;
      }
    }
    if (trace) {
      std::cout << "Step: " << ++it << ": ";
      for (int k = 0; k < s.getSize(); k++) {
        std::cout << s[k] << " ";
      }
      std::cout << std::endl;
    }
    QuickSortAlgorithm(s, low, j, trace);
    QuickSortAlgorithm(s, i, high, trace);
    it++;
  }
}



template <class Key>
void QuickSort(StaticSequence<Key>& s, bool trace = false) {
  std::cout << "Quick Sort" << std::endl;
  std::cout << "ORIGINAL: ";
  for (int i = 0; i < s.getSize(); i++) {
    std::cout << s[i] << " ";
  }
  std::cout << std::endl;

  // Implement QuickSort logic here
  // ...
  int it = 0;
  QuickSortAlgorithm(s, 0, s.getSize() - 1, it, trace);
  std::cout << "SORTED: ";
  for (int i = 0; i < s.getSize(); i++) {
    std::cout << s[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Quick Sort Finished" << std::endl;
} 

template <class Key>
void Heapify(StaticSequence<Key>& s, int size, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < size && s[left] > s[largest]) {
    largest = left;
  }
  if (right < size && s[right] > s[largest]) {
    largest = right;
  }
  if (largest != i) {
    std::swap(s[i], s[largest]);
    Heapify(s, size, largest);
  }
}


template <class Key>
void HeapSort(StaticSequence<Key>& s, bool trace = false) {
  std::cout << "Heap Sort" << std::endl;
  std::cout << "ORIGINAL: ";
  for (int i = 0; i < s.getSize(); i++) {
    std::cout << s[i] << " ";
  }
  std::cout << std::endl;

  // Implement HeapSort logic here
  // ...
  int size = s.getSize();
  for (int i = size / 2 - 1; i >= 0; i--) {
    Heapify(s, size, i);
  }

  int it = 0;
  for (int i = size - 1; i > 0; i--) {
    std::swap(s[0], s[i]);
    Heapify(s, i, 0);
    it++;
    if ((it == 1 || it == size / 4 || it == size / 2 || it == size / 4*3 || it == size - 1 ) && trace) {
      std::cout << "Step " << it << ": ";
      for (int k = 0; k < s.getSize(); k++) {
        std::cout << s[k] << " ";
      }
      std::cout << std::endl;
    }
  }

  std::cout << "SORTED: ";
  for (int i = 0; i < s.getSize(); i++) {
    std::cout << s[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Heap Sort Finished" << std::endl;
}


template <class Key>
void ShellSort(StaticSequence<Key>& s, double alpha, bool traza){
  std::cout << "Shell Sort" << std::endl;
  std::cout << "ORIGINAL: ";
  for (int i = 0; i < s.getSize(); i++) {
    std::cout << s[i] << " ";
  }
  std::cout << std::endl;

  // Implement ShellSort logic here
  // ...
  int size = s.getSize();
  int gap = size / alpha;
  while (gap > 0) {
    for (int i = gap; i < size; i++) {
      Key temp = s[i];
      int j;
      for (j = i; j >= gap && s[j - gap] > temp; j -= gap) {
        s[j] = s[j - gap];
      }
      s[j] = temp;
    }
    if (traza) {
      std::cout << "ALPHA: " << gap << " ";
      std::cout << "Step: ";
      for (int k = 0; k < size; k++) {
        std::cout << s[k] << " ";
      }
      std::cout << std::endl;
    }
    gap /= alpha;
  }

  std::cout << "SORTED: ";
  for (int i = 0; i < s.getSize(); i++) {
    std::cout << s[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Shell Sort Finished" << std::endl;
}


template <class Key>
class SortMethod {
public:
  SortMethod(unsigned size, StaticSequence<Key>* s, bool trace = false) {
    SetSize(size);
    s_ = s;
    SetTrace(trace);
  }

  virtual void Sort() = 0;

  protected:
  virtual void SetTrace(bool trace) {
    trace_ = trace;
  }
  virtual bool GetTrace() const {
    return trace_;
  }
  virtual void SetSize(unsigned size) {
    size_ = size;
  }
  virtual unsigned GetSize() const {
    return size_;
  }
  virtual void SetSequence(StaticSequence<Key>* s) {
    s_ = s;
  }
  virtual StaticSequence<Key>* GetSequence() const {
    return s_;
  }

  private:
  unsigned size_;
  StaticSequence<Key>* s_;
  bool trace_;
};

template <class Key>
class InsertionSortMethod : public SortMethod<Key> {
public:
  InsertionSortMethod(unsigned size, StaticSequence<Key>* s, bool trace = false): SortMethod<Key>(size, s, trace) {};

  void Sort();
};

template <class Key>
InsertionSortMethod<Key>::InsertionSortMethod(unsigned size, StaticSequence<Key>* s, bool trace) {
  InsertionSortMethod<Key>::SetSize(size);
  InsertionSortMethod<Key>::SetSequence(s);
  InsertionSortMethod<Key>::SetTrace(trace);
}

template <class Key>
void InsertionSortMethod<Key>::Sort() {
  InsertionSort<Key>(InsertionSortMethod<Key>::GetSequence(), InsertionSortMethod<Key>::GetTrace());
}

template <class Key>
class ShakeSortMethod : public SortMethod<Key> {
public:
  ShakeSortMethod(unsigned size, StaticSequence<Key>* s, bool trace = false);

  void Sort();
};

template <class Key>
ShakeSortMethod<Key>::ShakeSortMethod(unsigned size, StaticSequence<Key>* s, bool trace) {
  ShakeSortMethod<Key>::SetSize(size);
  ShakeSortMethod<Key>::SetSequence(s);
  ShakeSortMethod<Key>::SetTrace(trace);
}

template <class Key>
void ShakeSortMethod<Key>::Sort() {
  ShakeSort<Key>(ShakeSortMethod<Key>::GetSequence(), ShakeSortMethod<Key>::GetTrace());
}

template <class Key>
class QuickSortMethod : public SortMethod<Key> {
public:
  QuickSortMethod(unsigned size, StaticSequence<Key>* s, bool trace = false);
  void Sort();
};

template <class Key>
QuickSortMethod<Key>::QuickSortMethod(unsigned size, StaticSequence<Key>* s, bool trace) {
  QuickSortMethod<Key>::SetSize(size);
  QuickSortMethod<Key>::SetSequence(s);
  QuickSortMethod<Key>::SetTrace(trace);
}

template <class Key>
void QuickSortMethod<Key>::Sort() {
  QuickSort<Key>(QuickSortMethod<Key>::GetSequence(), QuickSortMethod<Key>::GetTrace());
}

template <class Key>
class HeapSortMethod : public SortMethod<Key> {
public:
  HeapSortMethod(unsigned size, StaticSequence<Key>* s, bool trace = false);
  void Sort();
};

template <class Key>
HeapSortMethod<Key>::HeapSortMethod(unsigned size, StaticSequence<Key>* s, bool trace) {
  HeapSortMethod<Key>::SetSize(size);
  HeapSortMethod<Key>::SetSequence(s);
  HeapSortMethod<Key>::SetTrace(trace);
}

template <class Key>
void HeapSortMethod<Key>::Sort() {
  HeapSort<Key>(HeapSortMethod<Key>::GetSequence(), HeapSortMethod<Key>::GetTrace());
}


template <class Key>
class ShellSortMethod : public SortMethod<Key> {
public:
  ShellSortMethod(unsigned size, StaticSequence<Key>* s, bool trace = false);

  void Sort();
};

template <class Key>
ShellSortMethod<Key>::ShellSortMethod(unsigned size, StaticSequence<Key>* s, bool trace) {
  ShellSortMethod<Key>::SetSize(size);
  ShellSortMethod<Key>::SetSequence(s);
  ShellSortMethod<Key>::SetTrace(trace);
}

template <class Key>
void ShellSortMethod<Key>::Sort() {
  std::cout << "Put ALPHA value: ";
  double alpha_;
  std::cin >> alpha_;
  while (alpha_< 0 || alpha_ > 1) {
    ShellSort(ShellSortMethod<Key>::GetSequence(), alpha_, ShellSortMethod<Key>::GetTrace());
  }
}

#endif