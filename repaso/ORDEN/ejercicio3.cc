#include <iostream>
#include <vector>

void Ordenar(std::vector<int> &sec, int size){
  int mitad = (size - 1) /2;
  for(int i = 0; i <= mitad; i++){
    for (int j = mitad; j > i; j--){
      if(sec[j-1] < sec[j]){
        std::swap(sec[j-1], sec[j]);
      }
    }
  }
  std::cout << "Primera mitad ordenada con BUBBLE" << std::endl;
  for(int i = 0; i <= mitad; i++){
    std::cout << sec[i] << " ";
  }
  std::cout << std::endl;

  for(int i = mitad + 2; i < size; i++){
    int aux = sec[i];
    int j = i - 1;
    while((j >= mitad + 1) && (aux < sec[j])){
      sec[j+1] = sec[j];
      j--;
    }
    sec[j+1] = aux;
  }
  std::cout << "Segunda mitad ordenada con INSERCION" << std::endl;
  for(int i = mitad + 1; i < size; i++){
    std::cout << sec[i] << " ";
  }
  std::cout << std::endl;

  int i = mitad;
  int j = mitad + 1;
  int k = 0;
  std::vector<int> aux(size - 1);
  while((i >= 0) && (j <= size - 1)){
    if(sec[i] < sec[j]){
      aux[k] = sec[i];
      i--;
    } else {
      aux[k] = sec[j];
      j++;
    }
    k++;
  }
  if(i < 0){
    while(j <= size -1){
      aux[k] = sec[j];
      j++; k++;
    }
  } else {
    while( i >= 0){
      aux[k] = sec[i];
      i--; k++;
    }
  }
  for (int i = 0; i < size; i++){
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