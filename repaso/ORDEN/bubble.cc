#include <iostream>
#include <vector>

// PAra el bubble recorremos el vector de izqda a derecha con i 
// y desde el final hasta i con j, la única condicion es que si j < j-1 swap

void BubbleSort(std::vector<int> &seq, int size){
  for(int i = 1; i <= size; i++){
    for (int j = size; j >= i; j--){
      if(seq[j] < seq[j-1]){
        std::swap(seq[j-1], seq[j]);
      }
    }
  }
  
}

int main(){
std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
int size = sequence.size();

BubbleSort(sequence, size - 1);

for(auto i : sequence){
  std::cout << i << " ";
}
std::cout << std::endl;
}