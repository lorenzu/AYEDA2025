#ifndef HASH_H
#define HASH_H

#include <cstdlib>
#include <array>

#include <iostream>
#include <vector>

#include "Sequence.h"
#include "DispersionFunctions.h"
#include "ExplorationFunctions.h"

template <class Key, class Container = staticSequence<Key>>
class HashTable : public Sequence<Key> {
 public:
  HashTable(unsigned table_size, unsigned blocksize, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration);
  bool search(const Key& key) const override;
  bool insert(const Key& key) override;
  bool isFull() const override { return false; }
  std::ostream& write(std::ostream& os) const;

  void menu();

 private:
  unsigned tablesize_;
  unsigned blocksize_;
  std::vector<Container> table_;
  ExplorationFunction<Key>* ef_;
  DispersionFunction<Key>* df_;
};

template <class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned table_size, unsigned blocksize, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration) : tablesize_(table_size), blocksize_(blocksize), df_(&dispersion), ef_(&exploration) {
  table_.resize(table_size, 0);
  staticSequence<Key> Sequence(blocksize_);
  for (int i = 0; i < table_size; i++) {
    table_[i] = Sequence;
  }
}

template <class Key, class Container>
bool HashTable<Key, Container>::search(const Key& key) const {
  unsigned index = df_->operator()(key);
  return table_[index].search(key);
}

template <class Key, class Container>
bool HashTable<Key, Container>::insert(const Key& key) {
  if (search(key) == true) {
    return false;
  }
  unsigned index = df_->operator()(key);
  table_[index].insert(key);
  std::cout << "Elemento insertado en la dirección " << index << std::endl;
  return true;
}

template <class Key, class Container>
std::ostream& HashTable<Key, Container>::write(std::ostream& os) const {
  for (int i = 0; i < table_.size(); i++) {
    os << "Direccion " << i << ": ";
    if (table_[i].size() > 0) {
      for (int j = 0; j < table_[i].size(); j++) {
        os << "|| Valor : " << table_[i].getData(j) << " ";
      }
    }
    os << std::endl;
  }
  return os;
}


template <class Key>
class HashTable<Key, dynamicSequence<Key>> : public Sequence<Key> {
 public:
  HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration);
  bool search(const Key& key) const override;
  bool insert(const Key& key) override;
  bool isFull() const override { return false; }
  std::ostream& write(std::ostream& os) const;

  void menu();

 private:
  unsigned tablesize_;
  std::vector<dynamicSequence<Key>> table_;
  ExplorationFunction<Key>* ef_;
  DispersionFunction<Key>* df_;
};

template <class Key>
HashTable<Key, dynamicSequence<Key>>::HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration) : tablesize_(table_size), df_(&dispersion), ef_(&exploration) {
  table_.resize(table_size);
  for (int i = 0; i < table_size; i++) {
    dynamicSequence<Key> Sequence;
    table_[i] = Sequence;
  }
}

template <class Key>
bool HashTable<Key, dynamicSequence<Key>>::search(const Key& key) const {
  unsigned index = df_->operator()(key);
  for (int i = 0; i < table_[index].size(); i++) {
    if (table_[index].isInList(key)) {
      return true;
    }
  }
  return false;
}

template <class Key>
bool HashTable<Key, dynamicSequence<Key>>::insert(const Key& key) {
  if (search(key) == true) {
    return false;
  }
  unsigned index = df_->operator()(key);
  table_[index].insert(key);
  std::cout << "Elemento insertado en la dirección " << index << std::endl;
  return true;
}

template <class Key>
std::ostream& HashTable<Key, dynamicSequence<Key>>::write(std::ostream& os) const {
  for (int i = 0; i < table_.size(); i++) {
    os << "Direccion " << i << ": ";
    if (!table_[i].getList().empty()) {
      for (const auto& element : table_[i].getList()) {
        os << " || Valor: " << element << " ";
      }
    }
    os << std::endl;
  }
  return os;
}

template <class Key, class Container>
void HashTable<Key, Container>::menu() {
  int opcion;
  do {
    std::cout << "\n╭─────────────────────────────────────────────╮\n";
    std::cout << "│                   PR04                      │\n";
    std::cout << "├─────────────────────────────────────────────┤\n";
    std::cout << "│   [1] ➤ Insertar elemento                   │\n";
    std::cout << "│   [2] ➤ Buscar elemento                     │\n";
    std::cout << "│   [3] ➤ Mostrar tabla                       │\n";
    std::cout << "│   [4] ➤ Salir                               │\n";
    std::cout << "╰─────────────────────────────────────────────╯\n";
    std::cout << "Seleccione una opción (1-4): ";
    std::cin >> opcion;
    Key k;
    switch (opcion) {
      case 1:
        std::cout << "Introduzca el elemento que quiere insertar: ";
        std::cin >> k;
        if (insert(k) == true) {
          std::cout << "El elemento se ha insertado correctamente en la tabla" << std::endl;
          std::cout << std::endl;
        } else {
          std::cout << "El elemento no se ha podido insertar en la tabla" << std::endl;
          std::cout << std::endl;
        }
        break;
      case 2:
        std::cout << "Introduzca el elemento que quiere buscar: ";
        std::cin >> k;
        if (search(k) == true) {
          std::cout << "El elemento está en la tabla" << std::endl;
          std::cout << std::endl;
        } else {
          std::cout << "El elemento no está en la tabla" << std::endl;
          std::cout << std::endl;
        }
        break;
      case 3:
        write(std::cout);
        break;
      case 4:
        std::cout << std::endl;
        exit(1);
        break;
      default:
        std::cout << "Opción no válida" << std::endl;
        break;
    }
  } while (opcion != 4);
}


template<class Key>
void HashTable<Key, dynamicSequence<Key>>::menu() {
  int opcion;
  do {
    std::cout << "\n╭─────────────────────────────────────────────╮\n";
    std::cout << "│                   PR04                      │\n";
    std::cout << "├─────────────────────────────────────────────┤\n";
    std::cout << "│   [1] ➤ Insertar elemento                   │\n";
    std::cout << "│   [2] ➤ Buscar elemento                     │\n";
    std::cout << "│   [3] ➤ Mostrar tabla                       │\n";
    std::cout << "│   [4] ➤ Salir                               │\n";
    std::cout << "╰─────────────────────────────────────────────╯\n";
    std::cout << "Seleccione una opción (1-4): ";
    std::cin >> opcion;
    Key k;
    switch (opcion) {
      case 1:
        std::cout << "Introduzca el elemento que quiere insertar: ";
        std::cin >> k;
        if (insert(k) == true) {
          std::cout << "El elemento se ha insertado correctamente en la tabla" << std::endl;
          std::cout << std::endl;
        } else {
          std::cout << "El elemento no se ha podido insertar en la tabla" << std::endl;
          std::cout << std::endl;
        }
        break;
      case 2:
        std::cout << "Introduzca el elemento que quiere buscar: ";
        std::cin >> k;
        if (search(k) == true) {
          std::cout << "El elemento está en la tabla" << std::endl;
          std::cout << std::endl;
        } else {
          std::cout << "El elemento no está en la tabla" << std::endl;
          std::cout << std::endl;
        }
        break;
      case 3:
        write(std::cout);
        break;
      case 4:
        std::cout << std::endl;
        exit(1);
        break;
      default:
        std::cout << "Opción no válida" << std::endl;
        break;
        exit(1);
    }
  } while (opcion != 4);
}



#endif