#include <iostream>
#include <vector>

void Ordenar(std::vector<int> &seq, int size){
  int mitad = (size-1)/2;

  for(int i = 0; i <= mitad; i++){
    int minIndex = i;
    for (int j = i + 1; j <= mitad; j++){
      if(seq[j] < seq[minIndex]){
        minIndex = j;
      }
    }
    int temp = seq[minIndex];
    seq[minIndex] = seq[i];
    seq[i] = temp;
  }
  std::cout << "Primera mitad ordenada con seleccion" << std::endl;
  for(int i = 0; i <= mitad; i++){
    std::cout << seq[i] << " ";
  }
  std::cout << std::endl;
  // PRimera mitad seleccion
  for(int i = mitad + 2; i < size; i++){
    int aux = seq[i];
    int j = i - 1;
    while((j>= mitad + 1) && (aux > seq[j])){
      seq[j + 1] = seq[j];
      j--;
    }
    seq[j+1] = aux;
  }
  std::cout << "Segunda mitad ordenada con insercion" << std::endl;
  for(int i = mitad + 1; i < size; i++){
    std::cout << seq[i] << " ";
  }
  std::cout << std::endl;

  int i = mitad;
  int j = mitad + 1;
  std::vector<int> aux(size-1);
  int k = 0;
  while (i >= 0 && j <= size - 1){
    if (seq[i] > seq[j]){
      aux[k] = seq[i];
      i--;
    } else {
      aux[k] = seq[j];
      j++;
    }
    k++;
  }
  if(i < 0){
    while (j <= size - 1){
      aux[k] = seq[j];
      j++; k++;
    }
  } else {
    while(i >= 0){
      aux[k] = seq[i];
      i--; k++;
    }
  }

  for (int i = 0; i < size; i++){
    seq[i] = aux[i];
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