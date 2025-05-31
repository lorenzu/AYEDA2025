#include <iostream>
#include <vector>

/*
Empezamos recorriendo el vector con i = delta hasta el final
Elegimos el auxiliar = seq[i] y j = i;

El código es igual que la insercion teniendo en cuenta que no comparamos con j -1 sino con j - delta
Ahora realizamos una especie de Insercion donde while (j >= delta && aux < seq[j - delta]) {
  seq[j] = seq[j - delta];
  j = j - delta;
}

por ultimo sec[j] =  aux;

*/

void ShellSort(int delta, std::vector<int> &seq, int size){
  for(int i = delta; i < size; i++){
    int aux = seq[i];
    int j = i;
    while ((j >= delta) && (aux < seq[j - delta])){ // Recorremos mientras j >= delta y hasta que encontremos un valor menor que aux
      seq[j] = seq[j - delta];
      j = j - delta;
    }
    seq[j] = aux; 
  }
}


/*
Función para establecer delta en el ShellSort

*/
void Delta(std::vector<int> &seq, int size){
  int delta = size - 1;
  while(delta > 1){
    delta = delta / 2;
    ShellSort(delta, seq, size);
  }
}


int main(){
std::vector<int> sequence = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
int size = sequence.size();

Delta(sequence, size);

for(auto i : sequence){
  std::cout << i << " ";
}
std::cout << std::endl;
}