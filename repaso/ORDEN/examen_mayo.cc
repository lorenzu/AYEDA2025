#include <iostream>
#include <vector>


// posiciones impares del vector insercion de mayor a menor
// posiciones pares del vector seleccion de menor a mayor
//creo que era ak reves
// por ultimo mezcla del mergesort

void Ordenar(std::vector<int> &sec, int size){
  for(int i = 3; i < size; i+=2){
    int aux = sec[i];
    int j = i - 2;
    while((j >= 1) && (aux < sec[j])){
    sec[j+2] = sec[j];      
    j-=2;
    }
    sec[j+2] = aux;
  }
  std::cout << "IMPARES ORDENADOS CON INSERCION DE MENOR A MAYOR" << std::endl;
  for(int i = 1; i < size ; i+=2){
    std::cout << sec[i] << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < size; i+=2){
    int maxIndex = i;
    for(int j = i + 2; j < size; j+=2){
      if(sec[j] > sec[maxIndex]){
        maxIndex = j;
      }
    }
    std::swap(sec[i], sec[maxIndex]); 
  }
  std::cout << "PARES ORDENADOS CON SELECCION DE MAYO A MENOR" << std::endl;
  for(int i = 0; i < size ; i+=2){
    std::cout << sec[i] << " ";
  }
  std::cout << std::endl;
  int i;
  if(size % 2 == 0){
    i = size - 2;
  } else {
    i = size - 1;
  }
  int j = 1;
  int k = 0;
  std::vector<int> aux(size-1);
  while(i >= 0 && j < size){
    if(sec[i] < sec[j]){
      aux[k] = sec[i];
      i-=2;
    } else {
      aux[k] = sec[j];
      j+=2;
    }
    k++;
  }
  if (i < 0){
    while(j < size){
      aux[k] = sec[j];
      j+=2; k++;
    } 
  } else {
    while(i >= 0){
      aux[k] = sec[i];
      i-=2; k++;
    }
  }

  for(int i = 0; i < size; i++){
    sec[i] = aux[i];
  }
}




int main(){
  std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
  int size = sequence.size();
  
  Ordenar(sequence, size);
  
  for(auto i : sequence){
    std::cout << i << " ";
  }
  std::cout << std::endl; 
  }