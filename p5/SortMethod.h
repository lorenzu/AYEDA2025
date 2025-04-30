#include "Sequences.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

#ifndef SORTMETHOD_H
#define SORTMETHOD_H
template <typename Key>
class SortMethod {
public:
  SortMethod(StaticSequence<Key>& seq) : sequence(seq) {}
  //método virtual puro que ordena la secuencia
  virtual void Sort() const = 0;
  
protected:
  StaticSequence<Key>& sequence;
};

// implementa la clase SelectionSortMethod<Key> que hereda de SortMethod<Key> y sobreescribe el método Sort() para implementar el algoritmo de ordenación SelectionSort.
template <typename Key>
class SelectionSortMethod : public SortMethod<Key> {
public:
  SelectionSortMethod(StaticSequence<Key>& seq) : SortMethod<Key>(seq) {}
  //método que ordena la secuencia con el algoritmo de ordenación SelectionSort
  void Sort() const override {
    // algoritmo de ordenación SelectionSort
    for (size_t i = 0; i < this -> sequence.size() - 1; ++i) {
      size_t min = i;
      for (size_t j = i + 1; j < this -> sequence.size(); ++j) {
        if (this -> sequence[j] < this -> sequence[min]) {
          min = j;
        }
      }
      std::swap(this -> sequence[i], this -> sequence[min]);
    }
  }



};

//implementa la clase QuickSortMethod<Key> que hereda de SortMethod<Key> y sobreescribe el método Sort() para implementar el algoritmo de ordenación QuickSort.
template <typename Key>
class QuickSortMethod : public SortMethod<Key> {
public:
  QuickSortMethod(StaticSequence<Key>& seq) : SortMethod<Key>(seq) {}
  //método que ordena la secuencia con el algoritmo de ordenación QuickSort
  void Sort() const override {
    // algoritmo de ordenación QuickSort
    PrintSequence(this -> sequence);
    QuickSort(this -> sequence, 0, this -> sequence.size() - 1);
    std::cout << "Final Sequence: ";
    PrintSequence(this -> sequence);
  }

  void PrintSequence(const StaticSequence<Key>& sequence) const {
    for (size_t i = 0; i < this -> sequence.size(); ++i) {
      std::cout << this -> sequence[i] << " ";
    }
    std::cout << std::endl;
  }


 
  void QuickSort(StaticSequence<Key>& sequence, int low, int high) const {
    if (low < high) {
      int pi = Partition(sequence, low, high);
      QuickSort(sequence, low, pi - 1);
      QuickSort(sequence, pi + 1, high);
    }
  }

  int Partition(StaticSequence<Key>& sequence, int low, int high) const {
    Key pivot = sequence[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
      if (sequence[j] < pivot) {
        i++;
        std::swap(sequence[i], sequence[j]);  
      }
    }
    std::swap(sequence[i + 1], sequence[high]);
    return i + 1;
  }


};

//clase HeapSortMethod<Key> que hereda de SortMethod<Key> y sobreescribe el método Sort() para implementar el algoritmo de ordenación HeapSort.
template <typename Key>
class HeapSortMethod : public SortMethod<Key> {
public:
  HeapSortMethod(StaticSequence<Key>& seq) : SortMethod<Key>(seq) {}
    void PrintSequence(const StaticSequence<Key>& sequence) const {
    for (size_t i = 0; i < this -> sequence.size(); ++i) {
      std::cout << this -> sequence[i] << " ";
    }
    std::cout << std::endl;
  }
  //método que ordena la secuencia con el algoritmo de ordenación HeapSort
  void Sort() const override {
    // algoritmo de ordenación HeapSort
    std::cout << "Initial Sequence: ";
    PrintSequence(this -> sequence);
    for (int i = this -> sequence.size() / 2 - 1; i >= 0; --i) {
      Heapify(this -> sequence, this -> sequence.size(), i);
    }
    for (int i = this -> sequence.size() - 1; i > 0; --i) {
      std::swap(this -> sequence[0], this -> sequence[i]);
      Heapify(this -> sequence, i, 0);
    }
    std::cout << "Final Sequence: ";
    PrintSequence(this -> sequence);
  }


  void Heapify(StaticSequence<Key>& sequence, int n, int i) const {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && sequence[left] > sequence[largest]) {
      largest = left;
    }
    if (right < n && sequence[right] > sequence[largest]) {
      largest = right;
    }
    if (largest != i) {
      std::swap(sequence[i], sequence[largest]);
      Heapify(sequence, n, largest);
    }
  }
};

// clase ShellSort que hereda de SortMethod<Key> y sobreescribe el método Sort() para implementar el algoritmo de ordenación por incrementos. y el usuario puede elegir el incremento.
template <typename Key>
class ShellSortMethod : public SortMethod<Key> {
public:
  ShellSortMethod(StaticSequence<Key>& seq, double increment) : SortMethod<Key>(seq), increment(increment) {}
  //método que ordena la secuencia con el algoritmo de ordenación ShellSort
  void Sort() const override {
    // Implementa el algoritmo de ordenación ShellSort
    std::cout << "Initial Sequence: ";
    PrintSequence(this -> sequence);
    for (int gap = this -> sequence.size() * increment; gap > 0; gap *= increment) {
      for (int i = gap; i < this -> sequence.size(); ++i) {
        Key temp = this -> sequence[i];
        int j;
        for (j = i; j >= gap && this -> sequence[j - gap] > temp; j -= gap) {
          this -> sequence[j] = this -> sequence[j - gap];
        }
        this -> sequence[j] = temp;
      }
    }
    std::cout << "Final Sequence: ";
    PrintSequence(this -> sequence);
  }

  void PrintSequence(const StaticSequence<Key>& sequence) const {
    for (size_t i = 0; i < this -> sequence.size(); ++i) {
      std::cout << this -> sequence[i] << " ";
    }
    std::cout << std::endl;
  }

  private:
    double increment;
};

//clase RadixSort que hereda de SortMethod<Key> y sobreescribe el método Sort() para implementar el algoritmo de ordenación RadixSort.
template <typename Key>
class RadixSortMethod : public SortMethod<Key> {
public:
  RadixSortMethod(StaticSequence<Key>& seq) : SortMethod<Key>(seq) {}

    void PrintSequence(const StaticSequence<Key>& sequence) const {
    for (size_t i = 0; i < this -> sequence.size(); ++i) {
      std::cout << this -> sequence[i] << " ";
    }
    std::cout << std::endl;
  }

  //método que ordena la secuencia con el algoritmo de ordenación RadixSort
  void Sort() const override {
    // Implementa el algoritmo de ordenación RadixSort
    std::cout << "Initial Sequence: ";
    PrintSequence(this -> sequence);
    RadixSort(this -> sequence);
    std::cout << "Final Sequence: ";
    PrintSequence(this -> sequence);
  }
  void RadixSort(StaticSequence<Key>& sequence) const {
    // Find the maximum element to determine the number of digits
    Key maxElement = sequence[0];
    for (int i = 1; i < sequence.size(); ++i) {
      if (sequence[i] > maxElement) {
        maxElement = sequence[i];
      }
    }

    // Perform counting sort for every digit
    for (int exp = 1; maxElement / exp > 0; exp *= 10) {
      CountingSort(sequence, exp);
    }
  }


  void CountingSort(StaticSequence<Key>& sequence, int exp) const {
    int n = sequence.size();
    std::vector<Key> output(n);
    std::vector<int> count(10, 0);

    // Store count of occurrences in count[]
    for (int i = 0; i < n; ++i) {
      count[(sequence[i] / exp) % 10]++;
    }

    // Change count[i] so that count[i] contains the actual position of this digit in output[]
    for (int i = 1; i < 10; ++i) {
      count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; --i) {
      output[count[(sequence[i] / exp) % 10] - 1] = sequence[i];
      count[(sequence[i] / exp) % 10]--;
    }

    // Copy the output array to sequence[]
    for (int i = 0; i < n; ++i) {
      sequence[i] = output[i];
    }
  }
};

#endif