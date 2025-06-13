#include <iostream>
#include <vector>

//ordenar primera mitad con seleccion y segunda con insercion finalmente merge de las dos

void Ordenar(std::vector<int> &sec, int size){
  int mitad = (size - 1)/2;
  for (int i = 0; i <= mitad; i++ ){
    int minIndex = i;
    int j = i + 1;
    for (j ; j <= mitad; j++){
      if(sec[j] < sec[minIndex]){
        minIndex = j;
      }
    }
    std::swap(sec[i], sec[minIndex]);
  } // Primera mitad ordenada con Seleccion

  for(int i = mitad + 1; i < size; i++){
    int aux = sec[i];
    int j = i;
    while((aux < sec[j-1]) && (j > mitad + 1)){
      sec[j] = sec[j-1];
      j--;
    }
    sec[j] = aux;
  } // Segunda mitad ordenada con Insercion

  int i = 0;
  int j = mitad + 1;
  int k = 0;
  std::vector<int> aux(size - 1);

  while((i <= mitad) && (j < size)){
    if(sec[i] < sec[j]){
      aux[k] = sec[i];
      i++;
    } else {
      aux[k] = sec[j];
      j++;
    }
    k++;
  }

  if(i > mitad){
    while(j < size){
      aux[k] = sec[j];
      k++;j++;
    }
  } else {
    while(i <= mitad){
      aux[k] = sec[i];
      k++;i++;
    }
  }

  for(int i = 0;  i < size; i++){
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