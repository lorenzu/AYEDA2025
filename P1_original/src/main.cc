

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

#include "BigU.h"
#include "BigInt.h"
#include "tools.h"

int main(){

  std::cout << "Prueba de BigUnsigned" << std::endl;
  BigUnsigned e;
  std::cin >> e;
  std::cout << e << std::endl;
  BigUnsigned f;
  std::cin >> f;
  std::cout << f << std::endl;
  if(f == e){
    std::cout << "Equal" << std::endl;
  } else {
    std::cout << "Not equal" << std::endl;
  }

  if(f < e){
    std::cout << f << " < " << e << std::endl;
  } else {
    std::cout << f << " > " << e << std::endl;
  }

  std::cout << "Pre-incremento" << std::endl;
  std::cout << "e: " << e << std::endl;
  std::cout << "Post-incremento" << std::endl;
  e = ++e;
  std::cout << "++e: " << e << std::endl;


  --e;
  std::cout << "Pre-decremento" << std::endl;
  std::cout << "e: " << e << std::endl;
  std::cout << "Post-decremento" << std::endl;
  e = --e;
  std::cout << "--e: " << e << std::endl;

  BigUnsigned h("2131231313521321651654654564654");
  BigUnsigned i("23132123132131321131231313213213121");

  BigUnsigned g = h + i;

  std::cout << "Suma: " << g << std::endl;

  if(g == "23134254363444842452882967867777775"){
    std::cout << "Correcto" << std::endl;
  } else {
    std::cout << "Incorrecto" << std::endl;
  }

  BigUnsigned o("1321321566454645664654465465465465");
  BigUnsigned p("131215945456464645231313131313");

  BigUnsigned r = o - p;
  
  std::cout << "Resta: " << r << std::endl;
  if(r == "1321190350509189200009234152334152"){
    std::cout << "Correcto" << std::endl;
  } else {
    std::cout << "Incorrecto" << std::endl;
  }

  BigUnsigned q = o * p;
  std::cout << "Multiplicacion: " << q << std::endl;
  if(q == "173378458594363210595991555446227789684982773969961772211605545"){
    std::cout << "Correcto" << std::endl;
  } else {
    std::cout << "Incorrecto" << std::endl;
  }

  BigUnsigned s = o / p;
  std::cout << "Division: " << s << std::endl;
  if(s == "10069"){
    std::cout << "Correcto" << std::endl;
  } else {
    std::cout << "Incorrecto" << std::endl;
  }

  BigUnsigned t = o % p;
  std::cout << "Modulo: " << t << std::endl;
  if(t == "108211653503151820373546274868"){
    std::cout << "Correcto" << std::endl;
  } else {
    std::cout << "Incorrecto" << std::endl;
  }

  std::cout << "PRUEBAS DE BIGINT" << std::endl;
  BigInteger a(-123);
  BigInteger l(o);

  std::cout << a << std::endl;
  std::cout << l << std::endl;

  std::cout << "operator >> " << std::endl;
  BigInteger b;
  std::cin >> b;
  std::cout << b << std::endl;
  std::cout << "operator == " << std::endl;
  a = b;
  if(b == a){
    std::cout << "Equal" << std::endl;
  } else {
    std::cout << "Not equal" << std::endl;
  }

  std::cout << "operator < " << std::endl;

  if(b < l){
    std::cout << b << " < " << l << std::endl;
  } else {
    std::cout << b << " > " << l << std::endl;
  }

  std::cout << "GCD" << std::endl;

  BigInteger op1("1321321566454645664654465");
  BigInteger op2("131215945456464645");

  BigInteger res = gcd(op1, op2);
  std::cout << "GCD: " << res << std::endl;


  return 0; 
}