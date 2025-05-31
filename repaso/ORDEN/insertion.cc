#include <iostream>
#include <vector>

void InsertionSort(std::vector<int> &seq, int size){
//
  int i, j;
  int aux; // numero a comparar
  for(int i = 1; i < size; i++){
    aux = seq[i];
    j = i - 1; // la i contiene el n numero ordenado, la j recorre hacia atrás desde i -1
  while(j >= 0 && aux < seq[j]){
    seq[j+1] = seq[j]; //se recorre la i hacia atrás con la j hasta que se encuentre un número más pequeño que aux o se llegue hasta 0
    j--;
  }
  seq[j+1] = aux; //cumpliendo las condiciones se sale del bucle y se actualiza el valor de j+1 con aux
  }
}

// hay que tener en cuenta que el valor que se actualiza es j+1 con aux



int main(){
std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
int size = sequence.size();

InsertionSort(sequence, size);

for(auto i : sequence){
  std::cout << i << " ";
}
}