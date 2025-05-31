#include <iostream>
#include <vector>


// posiciones impares del vector insercion de mayor a menor
// posiciones pares del vector seleccion de menor a mayor
//creo que era ak reves
// por ultimo mezcla del mergesort

void Insercion(std::vector<int> &seq, int size) {
  for (int i = 1; i < size; i++){
    if(i % 2 != 0){
    int j = i-1;
    int aux = seq[i];
    while (j >= 0 && aux > seq[j]){
      seq[j+1] = seq[j];
      j--;
    }
    seq[j+1] = aux;
    }
  }
}

void Seleccion(std::vector<int> &seq, int size){
  for (int i = 0; i < size; i++){
    if(i % 2 == 0){
    int minIndex = i;
    int j = i + 1;
    for (j; j < size; j++){
      if(seq[j] < seq[minIndex]){
        minIndex = j;
      }
    }
    int temp = seq[minIndex];
    seq[minIndex] = seq[i];
    seq[i] = temp; 
  }
  }
}

//void Merge()





int main(){
  std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
  int size = sequence.size();
  
  Seleccion(sequence, size);
  
  for(auto i : sequence){
    std::cout << i << " ";
  }
  
  }