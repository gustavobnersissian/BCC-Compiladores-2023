#include <stdio.h>
#include <string.h>
#include<stdbool.h>

void leitorOperadores(char str[]){

  // onde os caracteres serao armazenados
  char c;
  // iterador para mudar de caracteres
  int proxString = 0;
  char *verifica[9999];
  int qtdeCaracteres = 0;
  char caractIndice[9999][99];
  bool ehExponenciacao = false;
	
  for(int i = 0; i < strlen(str); i++){
    c = str[i];
    if (c == '+') {
      verifica[proxString] = "soma \n";
      proxString++;
    } 
    else if(c == '-'){
      verifica[proxString]= "subtração \n";
      proxString++;
    }
    else if(c == '*'){
      if(ehExponenciacao == true){
        if(verifica[proxString-1] == "Multiplicação\n"){
        verifica[proxString-1] = "Potenciação\n" ;
        ehExponenciacao = false;
        }
        else{
          verifica[proxString]= "Multiplicação\n";
          proxString++;
          ehExponenciacao = true; 
        }
      }
      else{
        verifica[proxString]= "Multiplicação\n";
        proxString++;
        ehExponenciacao = true; 
      }
	}
    else if(c == '/'){
      verifica[proxString]= "divisão \n";
      proxString++;
    }
    else if(c ==' '){
      verifica[proxString] = "espaco \n";
      proxString++;
    }      
    else {
      sprintf(caractIndice[qtdeCaracteres], "indeterminado(%c) \n", c);
      verifica[proxString] = caractIndice[qtdeCaracteres];
      proxString++;
      qtdeCaracteres++;
    }
  }
  printf("Operadores encontrados: \n");
  for (int i = 0; i < proxString; i++) {
    printf("%s", verifica[i]);
  }
}

int main(int argc,char *argv[]) {
	
  FILE *arq;
  char c;
  char code[9999];
  int codeIndex = 0;
  arq = fopen(argv[1], "r");
  while(c!= EOF){
    c = fgetc(arq);
    code[codeIndex] = c;
    codeIndex++;
  }
  code[codeIndex-1] = NULL;
	
  fclose(arq);
  leitorOperadores(code);
  return 0;
}
