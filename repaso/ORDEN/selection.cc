#include <iostream>
#include <vector>

//selection -> buscar el índice del mínimo, actualizarlo cuando se encuentre uno menor
//y una vez acabado el recorrido seq[i] = seq[min]

void SelectionSort(std::vector<int> &seq, int size){
  for(int i = 0; i < size - 1; i++){
    int minIndex = i; // establecemos como el más pequeño la i que es donde empezamos
    for (int j = i + 1; j < size; j++){
      if(seq[j] < seq[minIndex]){
        minIndex = j; // si recorriendo el vector se encuentra uno más pequeño lo actualizamos
      }
    }
    //hacemos el intercambio
    int temp;
    temp = seq[i];
    seq[i] = seq[minIndex];
    seq[minIndex] = temp;
  }

}


int main(){
  std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
  int size = sequence.size();
  
  SelectionSort(sequence, size);
  
  for(auto i : sequence){
    std::cout << i << " ";
  }
  
  }