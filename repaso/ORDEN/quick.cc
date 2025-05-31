#include <iostream>
#include <vector>

//asignamos i f y p
//recorremos el vector mientras i<=f 
//avanzamos i mientras seq[i] < p && decrementamos f mientras seq[f] > p
// paran los while y si i<= f hacemos el swap
//finalizamos con la recursividad y las condiciones de i < fin y ini < f 

void QuickSort(std::vector<int> &seq, int ini, int fin){
  int i = ini;
  int f = fin;
  int p = seq[(i + f) / 2];

  while (i <= f){
    while(seq[i] < p) i++;
    while (seq[f] > p) f--;

    if (i <= f){
      int temp = seq[f];
      seq[f] = seq[i];
      seq[i] = temp;
      i++;
      f--;
    }
  }

  if(i < fin) QuickSort(seq, i, fin);
  if (ini < f) QuickSort(seq, ini, f);
}


int main(){
  std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
  int size = sequence.size();
  
  QuickSort(sequence, 0, size - 1);
  
  for(auto i : sequence){
    std::cout << i << " ";
  }
  
  }