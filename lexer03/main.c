#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char *leitorDeNuneros(char str[], int *i, char valor[999]) {
  strcpy(valor, "");
  char numero;
  char caracteres[99] = "";
  char numeros[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  int tamanhoNumero = sizeof(numeros) / sizeof(numeros[0]);
  char letras[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                   'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                   's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int tamanhoLetras = sizeof(letras) / sizeof(letras[0]);
  bool ponto = false;
  int proxString = 0;
  char verifica[999];
  bool letra = false;
  bool encontrou = false;
  bool fimNum = false;
  int depoisDoPonto = 0;
  bool ehNum = false;
  bool invalido = false;
  
  for (int a = *i; a < strlen(str); a++) {
    caracteres[0] = str[a];
    for (int b = 0; b < tamanhoNumero; b++) {
      numero = numeros[b];
      if (caracteres[0] == numero) {
        ehNum = true;
        strcat(valor, caracteres);
        verifica[proxString] = caracteres[0];
        proxString++;
        encontrou = true;
        if (ponto == true) {
          depoisDoPonto++;
          if (depoisDoPonto > 2) {
            invalido = true;
          }
        }
      }
    }
    if (encontrou == false) {
      if (caracteres[0] == '.') {
        if (ponto == true) {
          invalido = true; 
        }
        strcat(valor, caracteres);
        verifica[proxString] = caracteres[0];
        proxString++;
        ponto = true;
        encontrou = true;
      } else if (caracteres[0] == ' ') {
        if(invalido == true){
          return "Invalido\n";
        }
        else{
          if(ponto == true){
            return "Numero Flutuante\n";
          }
          return "Numero Inteiro\n";
        }
       
      } else {
        for (int d = 0; d < tamanhoLetras; d++) {
          char let = letras[d];
          if (caracteres[0] == let) {
            encontrou = true;
            if(ehNum == true){
              invalido = true;
            }
            else{
              return "Letra\n"; 
            }
            
          }
        }
      }
    }
    if (encontrou == false) {
      if(ehNum == true){
        (*i)--;
        if(invalido == true){
          return "Invalido\n";
        }
        else{ 
          if(ponto == true){
            return "Numero Flutuante\n";
          }
        return "Numero Inteiro\n";
        }
      }
      return "indeterminado\n";
    }
    encontrou = false;
    (*i)++;
  }
  if(ponto == true){
    return "Numero Flutuante\n";
  }
  return "Numero Inteiro\n";
}

void Operador(char str[]) {
  char caract;
  int posString = 0;
  char *verifica[9999];
  int qtdCaractInd = 0;
  char caractInd[9999][99];
  bool exponenciacao = false;
  char valor[999];
  for (int i = 0; i < strlen(str); i++) {
    caract = str[i];
    if (caract == '+') {
      verifica[posString] = "Soma\n";
      posString++;
    } else if (caract == '-') {
      verifica[posString] = "Subtração\n";
      posString++;
    } else if (caract == '*') {
      if (exponenciacao == true) {
        if (strcmp(verifica[posString - 1], "Multiplicação\n") == 0) {
          verifica[posString - 1] = "Potenciação\n";
          exponenciacao = false;
        } else {
          verifica[posString] = "Multiplicação\n";
          posString++;
          exponenciacao = true;
        }
      } else {
        verifica[posString] = "Multiplicação\n";
        posString++;
        exponenciacao = true;
      }

    } else if (caract == '/') {
      verifica[posString] = "Divisão\n";
      posString++;
    } else if (caract == ' ') {
      verifica[posString] = "espaco\n";
      posString++;
    } else {
      verifica[posString] = leitorDeNuneros(str, &i, valor);
      posString++;
    }
  }
  for (int i = 0; i < posString; i++) {
    printf("%s", verifica[i]);
  }
}

int main(int argc, char *argv[]) {
  FILE *arq;
  char c;
  char code[9999];
  int codeIndex = 0;
  arq = fopen(argv[1], "r");
  while (c != EOF) {
    c = fgetc(arq);
    code[codeIndex] = c;
    codeIndex++;
  }
  code[codeIndex - 1] = NULL;
  fclose(arq);
  Operador(code);
  return 0;
}