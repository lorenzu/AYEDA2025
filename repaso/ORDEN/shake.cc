#include <iostream>
#include <vector>

//ShakeSort se compone de dos BubbleSort

// esto se hace mientras que ini < fin

//uno empieza desde fin hasta ini, actualizando el valor de cam en cada cambio, al final del bucle se actualiza ini = cam + 1
// el otro empieza desde ini hasta fin actualizando el valor de cam en cada cambio, al final se actualiza fin = cam - 1



void ShakeSort(std::vector<int> &seq, int size){
  int ini = 1;
  int fin = size - 1;
  int cam = size;
  
  while(ini < fin){
    for(int j = fin; j >= ini; j--){
      if(seq[j] < seq[j-1]){
        std::swap(seq[j-1], seq[j]);
        cam = j;
      }
    }
    ini = cam + 1;
    for (int j = ini; j <= fin; j++){
      if(seq[j] < seq[j-1]){
        std::swap(seq[j-1], seq[j]);
        cam = j;
      }
    }
    fin = cam - 1;
  }
}



int main(){
std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
int size = sequence.size();

ShakeSort(sequence, size);

for(auto i : sequence){
  std::cout << i << " ";
}
std::cout << std::endl;
}