#include <iostream>
#include <vector>
//ORDENAR PRIMERA MITAD BUBBLESORT MENOR A MAYOR Y SEGUNDA MITAD SHELLSORT
void ShellSort(std::vector<int> &sec, int size, int delta){
  int mitad = (size-1) /2 + 1;
  for(int i = mitad; i < size; i++){
    int aux = sec[i];
    int j = i;
    while((j +delta < size) && (sec[j+delta] > aux)){
          std::swap(sec[j+delta], sec[i]);
          j = j+delta;
    }
    }
  }

void Delta(std::vector<int> &sec, int size){
  int mitad = (size-1)/2;
  int delta = (size-1) - mitad;
  while(delta > 1){
    delta = delta / 2;
    std::cout << "Valor de Delta " << delta << std::endl;
    ShellSort(sec, size, delta);
  }
}



void Ordenar(std::vector<int> &sec, int size){
  int mitad = (size - 1)/2;
  for (int i = 1; i <= mitad; i++){
    for(int j = mitad; j >= i; j--){
      if(sec[j-1] > sec[j]){
      std::swap(sec[j-1], sec[j]);
      }
    }
  }
  std::cout << "Primera mitad ordenada con BUBBLE" << std::endl;
  for(int i = 0; i <= mitad; i++){
    std::cout << sec[i] << " ";
  }
  std::cout << std::endl;
  Delta(sec, size);
  std::cout << "Segunda mitad ordenada con SHELL" << std::endl;
  for(int i = mitad + 1; i < size; i++){
    std::cout << sec[i] << " ";
  }
  std::cout << std::endl;

  int i = 0;
  int j = size - 1;
  int k = 0;
  std::vector<int> aux(size - 1);
  while (i <= mitad && j >= mitad){
    if(sec[i] < sec[j]){
      aux[k] = sec[i];
      i++;
    } else {
      aux[k] = sec[j];
      j--; 
    }
    k++;
  }
  if(i > mitad){
    while(j >= mitad){
      aux[k] = sec[j];
      j--;
      k++;
    }
  } else {
    while(i <= mitad){
      aux[k] = sec[i];
      i++;
      k++;
    }
  }
  
  for(int i = 0; i < size; i++){
    sec[i] = aux[i];
  }
}




int main(){
std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
int size = sequence.size();
for(auto i : sequence){
  std::cout << i << " ";
}
std::cout << std::endl;

Ordenar(sequence, size);

for(auto i : sequence){
  std::cout << i << " ";
}
std::cout << std::endl;
}