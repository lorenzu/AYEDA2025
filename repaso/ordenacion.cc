#include <iostream>
#include <vector>

void Shellsort(std::vector<int> &sec, int n, int delta){
  for(int i = delta; i < n; i++){
    int x = sec[i];
    int j = i;
    while(( j>= delta ) && (x < sec[j - delta])){
      std::cout << "Intercambio: " << sec[j] << " <-> " << sec[j - delta] << std::endl;
      sec[j] = sec[j - delta];
      j = j - delta;
    };
    sec[j] = x;
  };
};

//shellsort
int Delta(int n, std::vector<int> &sec){
  int delta = n;
  while (delta > 1){
    delta = delta / 2;
    std::cout << "Delta: " << delta << std::endl;
    Shellsort(sec, n, delta);
  }
  return delta;
}



//mergesort
void Mix(std::vector<int> &sec, int ini, int cen, int fin){
  int i = ini;
  int j = cen + 1;
  std::vector<int> aux(sec.size());
  std::cout << "Mezcla: ";
  for (int k = ini; k <= fin; k++){
    aux[k] = sec[k];
  }
  std::cout << "Secuencia: ";
  for (int k = ini; k <= fin; k++){
    std::cout << aux[k] << " ";
  }
  std::cout << std::endl;
  int k = ini;
  while (i <= cen && j <= fin){
    if (sec[i] < sec[j]){
      aux[k] = sec[i];
      i++;
    } else {
      aux[k] = sec[j];
      j++;
    }
    k++;
  }
  if (i > cen){
    while (j <= fin){
      aux[k] = sec[j];
      j++;
      k++;
    }
  } else {
    while (i <= cen){
      aux[k] = sec[i];
      i++;
      k++;
    }
  }
  for (int i = ini; i <= fin; i++){
    sec[i] = aux[i];
  }
}
void Msort (std::vector<int> &sec, int ini, int fin){
  if (ini < fin){
    int cen = (ini + fin) / 2;
    std::cout << "Division: " << ini << " " << cen << " " << fin << std::endl;
    std::cout << "PArticion: ";
    for (int i = ini; i <= fin; i++){
      std::cout << sec[i] << " ";
    }
    std::cout << std::endl;
    Msort(sec, ini, cen);
    Msort(sec, cen + 1, fin);
    Mix(sec, ini, cen, fin);
  }
}

//shakesort
void Ssort(std::vector<int> &sec, int n){
  int ini = 1 ; 
  int fin = n-1 ; 
  int cam = n ;
  while (ini < fin){
     for (int j = fin; j >= ini; j--)
         if (sec[j] < sec[j-1]) {
            std::cout << "Intercambio: " << sec[j] << " <-> " << sec[j - 1] << std::endl;
            std::swap(sec[j-1],sec[j]) ;
            cam = j ;
         } 
     ini = cam + 1;
     for (int j = ini; j <= fin; j++)
         if (sec[j] < sec[j-1]) {
            std::cout << "Intercambio: " << sec[j] << " <-> " << sec[j - 1] << std::endl;
            std::swap(sec[j-1],sec[j]) ;
            cam = j;
         } 
     fin = cam - 1 ;
  } 
}

//bubble sort
void Bsort(std::vector<int> &sec, int n){
  for(int i = 1; i < n; i++){
    for (int j = n -1; j >= i; j--){
      if (sec[j] < sec[j - 1]){
        std::cout << "Intercambio: " << sec[j] << " <-> " << sec[j - 1] << std::endl;
        std::swap(sec[j], sec[j - 1]);
        //secuencia
        std::cout << "Secuencia: ";
        for (int k = 0; k < sec.size(); k++){
          std::cout << sec[k] << " ";
        }
        std::cout << std::endl;
      }
    }
  }
  std::cout << "Secuencia: ";
  for (int j = 0; j < sec.size(); j++){
    std::cout << sec[j] << " ";
  }
  std::cout << std::endl;
}

//selectionsort
void Ssort(std::vector<int> &sec, int i, int f){
  int min = i;
  for (int j = i + 1; j <= f; j++){
    if (sec[j] < sec[min]){
      min = j;
    }
  }
  std::cout << "Intercambio: " << sec[i] << " <-> " << sec[min] << std::endl;
  std::cout << " min: " << sec[min] << std::endl;
  std::swap(sec[i], sec[min]);
  std::cout << "Secuencia: ";
  for (int j = 0; j < sec.size(); j++){
    std::cout << sec[j] << " ";
  }
  std::cout << std::endl;
}

//insertsort
void Isort(std::vector<int> &sec, int i, int x){
  int j = i;
  int aux = sec[x];
  while (j > 0 && sec[j - 1] > aux){
    sec[j] = sec[j - 1];
    j--;
  }
  sec[j] = aux;
  std::cout << "Secuencia: ";
  for (int j = 0; j < sec.size(); j++){
    std::cout << sec[j] << " ";
  }
  std::cout << std::endl;
  std::cout << "Intercambio: " << sec[j] << " <-> " << aux << std::endl;
  std::cout << "i: " << i << " j: " << j << std::endl;
}


//quicksort
void Qsort(std::vector<int> &sec, int &ini, int &fin){
  int i = ini;
  int f = fin;
  int p = sec[(i + f) / 2];
  std::cout << "Pivot: " << p << std::endl;
  while (i <= f){
    while (sec[i] < p) i++;
    while (sec[f] > p) f--;
    if(i <= f) {
      std::cout << "Intercambio: " << sec[i] << " <-> " << sec[f] << std::endl;
      std::swap(sec[i], sec[f]);
      i++;
      f--;
    };
  };
  std::cout << "i: " << i << " f: " << f << std::endl;
  std::cout << "Secuencia: ";
  for (int j = 0; j < sec.size(); j++){
    std::cout << sec[j] << " ";
  }
  std::cout << std::endl;
  std::cout << "Particion: ";
  for (int j = ini; j <= f; j++){
    std::cout << sec[j] << " ";
  }
  std::cout << std::endl;
  std::cout << "Particion final: ";
  for (int j = i; j <= fin; j++){
    std::cout << sec[j] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;


  if (ini < f) Qsort(sec, ini, f);
  if (i < fin) Qsort(sec, i, fin);
};

int main(){
  std::vector<int> sec = {212, 237, 342, 132, 368, 347, 174, 672, 230, 154};
  /*
  int ini = 0;
  int fin = sec.size() - 1;
  Qsort(sec, ini, fin);
  std::cout << "Secuencia ordenada: ";
  for (int i = 0; i < sec.size(); i++){
    std::cout << sec[i] << " ";
  }
  std::cout << std::endl;
  */

  /*
  for (int i = 1; i < sec.size(); i++){
    Isort(sec, i, i);
  }
  */

  //selection sort
  /*
  for (int i = 0; i < sec.size() - 1; i++){
    Ssort(sec, i, sec.size() - 1);
  }
    */
  //bubble sort
    //Bsort(sec, sec.size());
  //shakesort
  //Ssort(sec, sec.size());
  //mergesort
  //Msort(sec, ini, fin);
  //shellsort
  std::cout << "Secuencia: ";
  for (int j = 0; j < sec.size(); j++){
    std::cout << sec[j] << " ";
  }
  Delta(sec.size(), sec);

  std::cout << std::endl;
  std::cout << "Secuencia ordenada: ";
  for (int i = 0; i < sec.size(); i++){
    std::cout << sec[i] << " ";
  }
  std::cout << std::endl;

}