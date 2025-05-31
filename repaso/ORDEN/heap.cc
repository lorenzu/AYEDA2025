#include <iostream>
#include <vector>


//Mientras que 2*i sea mas pekeño o iwal que el size
// hijo 1 = 2*i, hijo 2 = hijo1 +1

/*

Buscamos el hijo más grande y lo estableccemos como heap

si hijo 1 == size establecemos el heap como hijo 1
else si hijo1 es mayor que hijo2 heap = hijo 1 sino heap = hijo 2


si el heap es más pequeño o igual que el padre break;
sino hacemos swap heap con padre y i = heap;

*/

void baja(int i , std::vector<int> &seq, int size){
  int heap;
  while(2*i <= size -1){
    int hijo1 = 2*i;
    int hijo2 = hijo1 + 1;
    if(hijo1 == size - 1){
      heap = hijo1;
    } else if(seq[hijo1] > seq[hijo2]){
      heap = hijo1;
    } else {
      heap = hijo2;
    }

    if(seq[heap] <= seq[i]){
      break;
    } else {
      std::swap(seq[i], seq[heap]);
      i = heap;
    };
  };
};

/*
El primer for sirve para dejar el heap ordenado con padre e hijo (Inserción)
 
el segundo for sirve para la extracción, hacemos el swap del elemento 1 con el de i -1 
y después hacemos la baja desde 1 hasta i -1 

*/ 
void HeapSort(std::vector<int> &seq, int size){
  for(int i = (size/2) -1; i >= 0; i--){
    baja(i, seq, size);
  }
  for (int i = size - 1; i >= 0; i--){
    std::swap(seq[0], seq[i]);
    baja(0, seq, i);
  }
}

int main(){
std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
int size = sequence.size();

HeapSort(sequence, size);

for(auto i : sequence){
  std::cout << i << " ";
}
std::cout << std::endl;
}