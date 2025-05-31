#include <iostream>
#include <vector>

void Merge(std::vector<int> &seq, int ini, int mid, int fin){
  int i = ini;
  int j = mid + 1;
  int k = ini;
  std::vector<int> aux(fin + 1); //IMPORTANTE EL SIZE DEL AUX
  // 3 condiciones

  // 1 comparamos seq[i] y seq[j], metemos el menor valor en aux[k], en cada comparacion i++ o j++  y al final k++
  while ((i <= mid) && (j <= fin)){
    if(seq[i] < seq[j]){
      aux[k] = seq[i];
      i++;
    } else {
      aux[k] = seq[j];
      j++;
    }
    k++;
  }

  // 2 si i es mayor que mid recorremos la j hasta el final introduciendo todos los números en aux
  if(i > mid){
    while(j <= fin){
      aux[k] = seq[j];
      j++;
      k++;
    }
  } else {
// si i no es mayor que mid recorremos i hasta mid metiendo todos los números en aux
    while(i <= mid){
      aux[k] = seq[i];
      i++;
      k++;
    }
  }

  //3 introducimos en la secuencia inicial los numeros del auxiliar desde ini hasta fin
  for(int k = ini; k <= fin; k++){
    seq[k] = aux[k];
  }
}

void MergeSort(std::vector<int> &seq, int ini, int fin){
  if (ini < fin){
    int mid = (ini + fin) / 2;
    MergeSort(seq, ini, mid);
    MergeSort(seq, mid + 1, fin);
    Merge(seq, ini, mid, fin);
  }

}



int main(){
  std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
  int size = sequence.size();
  
  MergeSort(sequence, 0, size - 1);
  
  for(auto i : sequence){
    std::cout << i << " ";
  }
  
  }