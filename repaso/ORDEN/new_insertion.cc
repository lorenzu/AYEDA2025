#include <iostream>
#include <vector>

void Insertion(std::vector<int> &sec, int size){
  for(int i = 0; i < size; i++){
    int aux = sec[i];
    int j = i;
    while((aux < sec[j-1]) && (j > 0)){
      sec[j] = sec[j-1];
      j--;
    }
    sec[j] = aux;
  }
}

int main(){
std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
int size = sequence.size();
for(auto i : sequence){
  std::cout << i << " ";
}
std::cout << std::endl;

Insertion(sequence, size);

for(auto i : sequence){
  std::cout << i << " ";
}
std::cout << std::endl;
}