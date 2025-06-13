#include <iostream>
#include <vector>

void Ordenar(std::vector<int> &sec, int size){
  int i = 0;
  int f = size -1;
  int piv = sec[(i+f)/2];
  while( i <= f){
    while(sec[i] <= piv){
      int aux = sec[i];
      int j = i;
      while((aux < sec[j-1]) && (j > 0)){
        sec[j] = sec[j-1];
        j--;
      }
      sec[j] = aux;
        i++;

    }
    while(sec[f] >= piv){
      int aux = sec[f];
      int j = f;
      while((aux > sec[j+1]) && (j < size - 1)){
        sec[j] = sec[j+1];
        j++;
      }
      sec[j] = aux;
            f--;
    }


    if(i <= f){
      std::swap(sec[i], sec[f]);
    }
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