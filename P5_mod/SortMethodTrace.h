#include "Sequences.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>

#ifndef SORTMETHODTRACE_H

template <typename Key>
class SortMethodTrace {
public:
  SortMethodTrace(StaticSequence<Key>& seq) : sequence(seq) {}
  //método virtual puro que ordena la secuencia
  virtual void SortTrace(bool trace) const = 0;
  
protected:
  StaticSequence<Key>& sequence;
};

// clase SelectionSortMethod<Key> que hereda de SortMethodTrace<Key> y sobreescribe el método Sort() para implementar el algoritmo de ordenación SelectionSort
template <typename Key>
class SelectionSortMethodTrace : public SortMethodTrace<Key> {
public:
  SelectionSortMethodTrace(StaticSequence<Key>& seq) : SortMethodTrace<Key>(seq) {}
  //sobrecarga el método Sort() para que vaya mostrando una traza de la secuencia en cada iteración si se le pasa un parámetro de tipo bool
  void SortTrace(bool trace) const {
    if (trace) {
      for (size_t i = 0; i < this -> sequence.size() - 1; ++i) {
        size_t min = i;
        for (size_t j = i + 1; j < this -> sequence.size(); ++j) {
          if (this -> sequence[j] < this -> sequence[min]) {
            min = j;
          }
        }
        std::swap(this -> sequence[i], this -> sequence[min]);
        for (size_t k = 0; k < this -> sequence.size(); ++k) {
          std::cout << this -> sequence[k] << " ";
        }
        std::cout << std::endl;
      }
    }
  }
};

//clase QuickSortMethodTrace<Key> que hereda de SortMethodTrace<Key> y sobreescribe el método SortTrace() para implementar el algoritmo de ordenación QuickSort.
template <typename Key>
class QuickSortMethodTrace : public SortMethodTrace<Key> {
public:
  QuickSortMethodTrace(StaticSequence<Key>& seq) : SortMethodTrace<Key>(seq) {}
  //método que ordena la secuencia con el algoritmo de ordenación QuickSort

  void PrintSequence(const StaticSequence<Key>& sequence) const {
    for (size_t i = 0; i < this -> sequence.size(); ++i) {
      std::cout << this -> sequence[i] << " ";
    }
    std::cout << std::endl;
  }
  //sobrecarga el método SortTrace() para que vaya mostrando una traza de la secuencia en cada iteración si se le pasa un parámetro de tipo bool, esto alomejor requiere de la sobrecarga de otro método
  void SortTrace(bool trace) const {
    std::cout << "Initial Sequence: ";
    PrintSequence(this -> sequence);
    if (trace) {
      QuickSort(this -> sequence, 0, this -> sequence.size() - 1, trace);
      std::cout << std::endl;
      std::cout << "Final Sequence: ";
      PrintSequence(this -> sequence);
  }
  }

  // sobrecarga de QuickSort para que muestre la traza de la secuencia en cada iteración si se le pasa un parámetro de tipo bool
  void QuickSort(StaticSequence<Key>& sequence, int low, int high, bool trace) const {

    if (low < high) {
      int pi = Partition(sequence, low, high, trace);
      QuickSort(sequence, low, pi - 1, trace);
      QuickSort(sequence, pi + 1, high, trace);
    }
    }


    int Partition(StaticSequence<Key>& sequence, int low, int high, bool trace) const {
    Key pivot = sequence[high];
    std::cout << "Pivot: " << pivot << " " << std::endl;
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
      if (sequence[j] < pivot) {
        i++;
        std::cout << "swap: " << sequence[i] << " " << sequence[j] << std::endl;
        std::swap(sequence[i], sequence[j]);  

        if (trace) {
          PrintSequence(sequence);
        }
      }
    }
    
    std::swap(sequence[i + 1], sequence[high]);
    if (trace) {
      std::cout << "swap del pivote: ";
      PrintSequence(sequence);
    }
    std::cout << std::endl;
    return i + 1;
  }
};

//clase HeapSortMethod<Key> que hereda de SortMethodTrace<Key> y sobreescribe el método Sort() para implementar el algoritmo de ordenación HeapSort.
template <typename Key>
class HeapSortMethodTrace : public SortMethodTrace<Key> {
public:
  HeapSortMethodTrace(StaticSequence<Key>& seq) : SortMethodTrace<Key>(seq) {}
    void PrintSequence(const StaticSequence<Key>& sequence) const {
    for (size_t i = 0; i < this -> sequence.size(); ++i) {
      std::cout << this -> sequence[i] << " ";
    }
    std::cout << std::endl;
  }

    void SortTrace(bool trace) const {
    // Implementa el algoritmo de ordenación HeapSort
    std::cout << "Initial Sequence: ";
    PrintSequence(this -> sequence);
    for (int i = this -> sequence.size() / 2 - 1; i >= 0; --i) {
      Heapify(this -> sequence, this -> sequence.size(), i, trace);
    }
    for (int i = this -> sequence.size() - 1; i > 0; --i) {
      std::swap(this -> sequence[0], this -> sequence[i]);
      Heapify(this -> sequence, i, 0, trace);
    }
    std::cout << "Final Sequence: ";
    PrintSequence(this -> sequence);
  }

    void Heapify(StaticSequence<Key>& sequence, int n, int i, bool trace) const {
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
      std::cout << "swap: " << sequence[i] << " " << sequence[largest] << std::endl;
      std::swap(sequence[i], sequence[largest]);
      PrintSequence(sequence);
      Heapify(sequence, n, largest, trace);
    }
  }
};





//clase ShellSort que hereda de SortMethodTrace<Key> y sobreescribe el método Sort() para implementar el algoritmo de ordenación por incrementos. y el usuario puede elegir el incremento.
template <typename Key>
class ShellSortMethodTrace : public SortMethodTrace<Key> {
public:
  ShellSortMethodTrace(StaticSequence<Key>& seq, double increment) : SortMethodTrace<Key>(seq), increment(increment) {}
  //método que ordena la secuencia con el algoritmo de ordenación ShellSort


    void SortTrace(bool trace) const {
    // Implementa el algoritmo de ordenación ShellSort
    std::cout << "Initial Sequence: ";
    PrintSequence(this -> sequence);
    for (int gap = this -> sequence.size() * increment; gap > 0; gap *= increment) {
      for (int i = gap; i < this -> sequence.size(); ++i) {
        Key temp = this -> sequence[i];
        int j;
        for (j = i; j >= gap && this -> sequence[j - gap] > temp; j -= gap) {
          std::cout << "swap: " << this -> sequence[j] << " " << this -> sequence[j - gap] << std::endl;
          PrintSequence(this -> sequence);
          this -> sequence[j] = this -> sequence[j - gap];
        }
        this -> sequence[j] = temp;
      }
      PrintSequence(this -> sequence);
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

//clase RadixSort que hereda de SortMethodTrace<Key> y sobreescribe el método Sort() para implementar el algoritmo de ordenación RadixSort.
template <typename Key>
class RadixSortMethodTrace : public SortMethodTrace<Key> {
public:
  RadixSortMethodTrace(StaticSequence<Key>& seq) : SortMethodTrace<Key>(seq) {}

    void PrintSequence(const StaticSequence<Key>& sequence) const {
    for (size_t i = 0; i < this -> sequence.size(); ++i) {
      std::cout << this -> sequence[i] << " ";
    }
    std::cout << std::endl;
  }

     //método que ordena la secuencia con el algoritmo de ordenación RadixSort
  void SortTrace(bool trace) const {
    // Implementa el algoritmo de ordenación RadixSort
    std::cout << "Initial Sequence: ";
    PrintSequence(this -> sequence);
    RadixSort(this -> sequence, trace);
    std::cout << "Final Sequence: ";
    PrintSequence(this -> sequence);
  }
  void RadixSort(StaticSequence<Key>& sequence, bool trace) const {
    // Find the maximum element to determine the number of digits
    Key maxElement = sequence[0];
    for (int i = 1; i < sequence.size(); ++i) {
      if (sequence[i] > maxElement) {
        maxElement = sequence[i];
      }
    }

    // Perform counting sort for every digit
    for (int exp = 1; maxElement / exp > 0; exp *= 10) {
      PrintSequence(sequence);
      CountingSort(sequence, exp, trace);
    }
    PrintSequence(sequence);
  }
    void CountingSort(StaticSequence<Key>& sequence, int exp, bool trace) const {

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