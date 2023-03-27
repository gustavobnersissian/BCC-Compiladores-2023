#include <stdio.h>
#include <string.h>

void Operador(char str[]){
  char c;
  int posString = 0;
  char *verifica[9999];
  int qtdeCaracteres = 0;
  char caractInd[9999][99];
  
  for(int i = 0; i < strlen(str); i++){
    c = str[i];
    if (c == '+') {
      verifica[posString] = "Mais\n";
      posString++;
    } 
    else if(c == '-'){
      verifica[posString]= "Menos\n";
      posString++;
    }
    else if(c ==' '){
      verifica[posString] = "espaco\n";
      posString++;
    }      
    else {
      sprintf(caractInd[qtdeCaracteres], 
		  "undefined(%c)\n", c);
      verifica[posString] = caractInd[qtdeCaracteres];
      posString++;
      qtdeCaracteres++;
    }
  }
     
  for (int i = 0; i < posString; i++) {
    printf("%s", verifica[i]);
  }
}

int main(void) {
    Operador("1+1=2  1");
  return 0;
}
