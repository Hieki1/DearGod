#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct dicionario{
char palavra[46];
char significado[200];
}item_cadastro, item_consulta, item_jogo, item_dicionario;

FILE *arquivo_dicionario; // arquivo global

void cadastrar_palavra();
void consultar_palavra();
void iniciar_jogo();

int verificar_existencia_de_arquivo();
int verificar_existencia_da_palavra(char *palavra_inserida);
void normalizar_palavra(char *palavra);
void retornar_menu();
void exibir_forca(int erros);


void string_verde_negrito(char *string);
void string_verde_negrito_sublinhado(char *string);
void string_vermelha_negrito(char *string);
void string_vermelha_negrito_sublinhado(char *string);

int main(void) {
  int op;
  do{ 
  system("clear");
  printf("========================================================");
  printf("\nMenu de Opções Principal\n");
  printf("========================================================");
  printf("\n1 - Cadastrar Nova Palavra\n");
  printf("\n2 - Consultar Palavra\n");
  printf("\n3 - Iniciar Jogo da Forca\n");
  printf("\n4 - Encerrar o Programa\n");
  printf("========================================================"); 
  printf("\nDigite o Número da Opção Desejada: ");
  scanf("%d%*c", &op);
    switch(op){
      case 1: 
        cadastrar_palavra();
        break;
      case 2: 
        consultar_palavra();
        break;
      case 3: 
        iniciar_jogo(); 
        break;
      case 4:
        break;
    }
  }while(op!=4);
}
 
void cadastrar_palavra(){
  if (verificar_existencia_de_arquivo()==0){
    arquivo_dicionario=fopen("dicionario.txt","w");
  }
  else{
    arquivo_dicionario=fopen("dicionario.txt","a");
  }
  system("clear");
  printf("========================================================");
  printf("\nCadastro de Palavra\n");
  printf("========================================================");
  
  printf("\nDigite a Nova Palavra para o Cadastro: ");
  fgets(item_cadastro.palavra,sizeof(item_cadastro.palavra),stdin); 
  item_cadastro.palavra[strcspn(item_cadastro.palavra,"\n")] = 0; // pra remover o \n que fgets pega, só para meu toque não atacar
  normalizar_palavra(item_cadastro.palavra);
  if(verificar_existencia_da_palavra(item_cadastro.palavra)==1){
    string_vermelha_negrito("\nErro! A Palavra: ");  
    string_vermelha_negrito_sublinhado(item_cadastro.palavra);
    string_vermelha_negrito(" Já Existe no Dicionário!\n");
    retornar_menu();
  }
  else{
    printf("\nDigite o Significado da Nova Palavra para o Cadastro: ");
    fgets(item_cadastro.significado,sizeof(item_cadastro.significado),stdin); // não removo o \n para não ter q colocar um \n no fprintf
    fprintf(arquivo_dicionario,"%s %s",item_cadastro.palavra,item_cadastro.significado);
    fclose(arquivo_dicionario);
    string_verde_negrito("\nSucesso! A Palavra: ");  
    string_verde_negrito_sublinhado(item_cadastro.palavra);
    string_verde_negrito(" Foi Registrada no Dicionário!\n");
    retornar_menu();
  }    
}

void consultar_palavra(){
  system("clear");
  printf("========================================================");
  printf("\nConsulta de Palavra\n");
  printf("========================================================");
  if (verificar_existencia_de_arquivo()==0){
    string_vermelha_negrito("\nErro! O Dicionário Não Contém Nenhuma Palavra.");
    retornar_menu();
  }
  else{
    printf("\nDigite a Palavra para Consulta: ");
    fgets(item_consulta.palavra,sizeof(item_consulta.palavra),stdin);
    item_consulta.palavra[strcspn(item_consulta.palavra,"\n")] = 0;
    //normalizar_palavra(item_consulta.palavra);
    if(verificar_existencia_da_palavra(item_consulta.palavra)==0){
      string_vermelha_negrito("\nErro! O Dicionário Não Contém a Palavra: ");
      string_vermelha_negrito_sublinhado(item_consulta.palavra);
      printf("\n");
      retornar_menu();
    }
    else{
      arquivo_dicionario=fopen("dicionario.txt","r");
      while(fscanf(arquivo_dicionario,"%s %[^\n]", item_dicionario.palavra, item_dicionario.significado)!=EOF){
        if (strcmp(item_dicionario.palavra, item_consulta.palavra)==0){
          printf("\nO Significado de \"%s\" é: %s\n", item_consulta.palavra,item_dicionario.significado);
          fclose(arquivo_dicionario);
          retornar_menu();
        }
      }
    }  
  }
} 

void iniciar_jogo(){
  int linha_palavra_sorteada, total_palavras_arquivo_dicionario=0;
  if (verificar_existencia_de_arquivo()==0){
    string_vermelha_negrito("Erro! O Dicionário Não Contém Nenhuma Palavra.");
    retornar_menu();
  }
  else{
    arquivo_dicionario=fopen("dicionario.txt","r");
    while(fscanf(arquivo_dicionario,"%s %*[^\n]", item_dicionario.palavra)!=EOF){
      total_palavras_arquivo_dicionario++;    
    }
    fclose(arquivo_dicionario);
    srand(time(NULL));
    linha_palavra_sorteada = rand() % total_palavras_arquivo_dicionario+1;
    arquivo_dicionario = fopen("dicionario.txt","r");
    for (int i = 0; i < linha_palavra_sorteada; i++){
      fscanf(arquivo_dicionario,"%s %[^\n]", item_jogo.palavra,item_jogo.significado);
    }
    fclose(arquivo_dicionario);
  
    char item_jogo_palavra_oculta[strlen(item_jogo.palavra)];
    for (int i=0;i<strlen(item_jogo.palavra);i++){
      item_jogo_palavra_oculta[i]='_';
    }

    char letras_tentadas[26]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};      char letra;
    int erros=0, acertos=0, sinaliza_erros, contador=0;
    while(1){
      exibir_forca(erros);
      for (int i=0;i<strlen(item_jogo.palavra);i++){
      printf("\t%c",item_jogo_palavra_oculta[i]);
      }
      printf("\n"); 
      printf("\n========================================================\n");
      printf("Letras Já Tentadas:");
      for (int i=0;i<26;i++){
          if(letras_tentadas[i]!='0'){
            printf("%c ",letras_tentadas[i]);
          }
      }
      printf("\n");
      printf("========================================================\n");
      printf("Digite Uma Letra: ");
      scanf(" %c",&letra);
      normalizar_palavra(&letra);

      sinaliza_erros=0;
      for (int i=0;i<strlen(letras_tentadas);i++){
        if(letras_tentadas[i]==letra){
          sinaliza_erros=1;
        }
      }
      if(sinaliza_erros!=1){
        letras_tentadas[contador]=letra;
        contador++;
        int sinaliza_erros=1;
        for (int i=0;i<strlen(item_jogo.palavra);i++){
          if(item_jogo.palavra[i]==letra){
            item_jogo_palavra_oculta[i]=letra;
            acertos++;
            sinaliza_erros=0;
          }
        }
        if(sinaliza_erros!=0){
          erros++;
        }
        if(erros==6){
          exibir_forca(erros);
          for (int i=0;i<strlen(item_jogo.palavra);i++){
          printf("\t%c",item_jogo_palavra_oculta[i]);
          }
          printf("\n"); 
          printf("\n========================================================\n");
          printf("Letras Já Tentadas:");
          for (int i=0;i<strlen(letras_tentadas);i++){
            if(letras_tentadas[i]!='0'){
              printf("%c ",letras_tentadas[i]);
            }
          }
          printf("\n");
          string_vermelha_negrito("\nVocê Perdeu! O Boneco Perin Foi Enforcado!\n");
          string_vermelha_negrito("\nA Palavra Secreta Era: ");
          string_vermelha_negrito_sublinhado(item_jogo.palavra);
          string_vermelha_negrito(" Que Significa: ");
          string_vermelha_negrito_sublinhado(item_jogo.significado);
          printf("\n");
          getchar();
          retornar_menu();
          break;
        }
        else if (acertos==strlen(item_jogo.palavra)){
          exibir_forca(erros);
          for (int i=0;i<strlen(item_jogo.palavra);i++){
          printf("%c\t",item_jogo_palavra_oculta[i]);
          }
          printf("\n"); 
          printf("\n========================================================\n");
          printf("Letras Já Tentadas:");
          for (int i=0;i<strlen(letras_tentadas);i++){
          printf("%c\t",letras_tentadas[i]);
          }
          printf("\n");
          string_verde_negrito("\nVocê Ganhou! O Boneco Perin Não Foi Enforcado!\n");
          string_verde_negrito("\nA Palavra Secreta Era: ");
          string_verde_negrito_sublinhado(item_jogo.palavra);
          string_verde_negrito(" Que Significa: ");
          string_verde_negrito_sublinhado(item_jogo.significado);
          printf("\n");
          getchar();
          retornar_menu();
          break;
        }  
      }
    }
    
  }
}


int verificar_existencia_de_arquivo(){
  if(fopen("dicionario.txt","r")==NULL){
    return 0;
  }
  else{
    return 1;
  }
}

int verificar_existencia_da_palavra(char *palavra_inserida){
  FILE *dicionario;
  char palavra_existente[46];
  dicionario=fopen("dicionario.txt","r");
  while(fscanf(dicionario,"%s %*[^\n]", palavra_existente)!=EOF){// só ve a palavra ignora significado
      if (strcmp(palavra_existente, palavra_inserida)==0){
        fclose(dicionario);
        return 1;
      }
    }
  fclose(dicionario);
  return 0;
}

void normalizar_palavra(char *palavra){
   for (int i = 0; i<strlen(palavra); i++){
    if (palavra[i] >= 65 && palavra[i] <= 90){
      palavra[i] = palavra[i] + 32; 
    }
  }///normaliza a palavra 
} 

void exibir_forca(int erros){
  switch (erros){
    case 0:
    system("clear");
    printf("========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
    printf("\n\n");
    break;
    case 1:
    system("clear");
    printf("========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
    printf("\n\n");
    break;
    case 2:
    system("clear");
    printf("========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||    | ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
    printf("\n\n");
    break;
    case 3:
    system("clear");
    printf("========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||    | ");
	  printf("\n\t||   /  ");
	  printf("\n\t||      ");
    printf("\n\n");
    break;
    case 4:
    system("clear");
    printf("========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||    | ");
	  printf("\n\t||   / \\ ");
	  printf("\n\t||      "); 
    printf("\n\n");
    break;
    case 5:
    system("clear");
    printf("========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||   /| ");
	  printf("\n\t||   / \\ ");
	  printf("\n\t||      ");
    printf("\n\n");
    break;
    case 6:
    system("clear");
    printf("========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||   /|\\ ");
	  printf("\n\t||   / \\ ");
	  printf("\n\t||      ");
    printf("\n\n");
    break;
  }
}

void retornar_menu(){
  printf("\nPressione Qualquer Tecla para Retornar para o Menu de Opções Principal.\n");
  getchar();
}

void string_verde_negrito(char *string){
  printf("\033[1;32m");
  printf("%s",string);
  printf("\033[0m");
}

void string_verde_negrito_sublinhado(char *string){
  printf("\033[4;32m");
  printf("\033[1;32m");
  printf("%s",string);
  printf("\033[0m");
}

void string_vermelha_negrito(char *string){
  printf("\033[1;31m");
  printf("%s",string);
  printf("\033[0m");
}

void string_vermelha_negrito_sublinhado(char *string){
  printf("\033[4;31m");
  printf("\033[1;31m");
  printf("%s",string);
  printf("\033[0m");
}


  
    
  


  
