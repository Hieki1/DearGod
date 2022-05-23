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
int verificar_existencia_de_arquivo();
int verificar_existencia_da_palavra();
void normalizar_palavras();
void buscar_significado();
void consultar_palavra();
void iniciar_jogo();
void exibir_forca();
void exibir_caracteres();


int main(void) {
  
  int op;
  do{ 
  printf("\n========================================================");
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
      default:
        printf("\nEscolha Inválida! Tente Novamente!");
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
  printf("\nDigite a Nova Palavra para o Cadastro: ");
  fgets(item_cadastro.palavra,sizeof(item_cadastro.palavra),stdin); 
  item_cadastro.palavra[strcspn(item_cadastro.palavra,"\n")] = 0; // pra remover o \n que fgets pega, só para meu toque não atacar
  normalizar_palavras(item_cadastro.palavra);
  if(verificar_existencia_da_palavra(item_cadastro.palavra)==1){
    printf("\nErro! A Palavra: \"%s\" Já Existe no Dicionário!\nRetornando para o Menu de Opções Principal.\n",item_cadastro.palavra);
  }
  else{
    printf("\nDigite o Significado da Nova Palavra para o Cadastro: ");
    fgets(item_cadastro.significado,sizeof(item_cadastro.significado),stdin); // não removo o \n para não ter q colocar um \n no fprintf
    fprintf(arquivo_dicionario,"%s %s",item_cadastro.palavra,item_cadastro.significado);
    fclose(arquivo_dicionario);
    printf("\nSucesso! A Palavra: \"%s\" Foi Registrada no Dicionário!\nRetornando para o Menu de Opções Principal.\n",item_cadastro.palavra);
  }    
}


void consultar_palavra(){
  if (verificar_existencia_de_arquivo()==0){
    printf("\nErro! O Dicionário Não Contém Nenhuma Palavra.\nRetornando para o Menu de Opções Principal.\n");
  }
  else{
    printf("\nDigite a Palavra para Consulta: ");
    fgets(item_consulta.palavra,sizeof(item_consulta.palavra),stdin);
    item_consulta.palavra[strcspn(item_consulta.palavra,"\n")] = 0;
    //normalizar_palavra(item_consulta.palavra);
    if(verificar_existencia_da_palavra(item_consulta.palavra)==0){
      printf("\nErro! O Dicionário Não Contém a Palavra: \"%s\"!\nRetornando para o Menu de Opções Principal.\n",item_consulta.palavra);
    }
    else{
      arquivo_dicionario=fopen("dicionario.txt","r");
      while(fscanf(arquivo_dicionario,"%s %[^\n]", item_dicionario.palavra, item_dicionario.significado)!=EOF){
        if (strcmp(item_dicionario.palavra, item_consulta.palavra)==0){
          printf("\nO Significado de \"%s\" é: %s", item_consulta.palavra,item_dicionario.significado);
          fclose(arquivo_dicionario);
        }
      }
    }  
  }
} //lembrar de tentar a função verificar com a normal

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

void normalizar_palavras(char *palavra){
   for (int i = 0; i<strlen(palavra); i++){
    if (palavra[i] >= 65 && palavra[i] <= 90){
      palavra[i] = palavra[i] + 32; 
    }
  }///normaliza a palavra 
} 

void exibir_forca(int erros,char *letras_tentadas, char *item_jogo_palavra_oculta){
  switch (erros){
    case 0:
    system("clear");
    printf("\n========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================\n");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
    printf("\n\n");
    exibir_caracteres(item_jogo_palavra_oculta);
    printf("\n"); 
    printf("\n========================================================\n");
    printf("Letras Já Tentadas:");
    exibir_caracteres(letras_tentadas);
    printf("\n");
    printf("========================================================\n");
    printf("Digite Uma Letra: ");
    break;
    case 1:
    system("clear");
    printf("\n========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================\n");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
    printf("\n\n");
    exibir_caracteres(item_jogo_palavra_oculta);
    printf("\n");         
    printf("\n========================================================\n");
    printf("Letras Já Tentadas:");
    exibir_caracteres(letras_tentadas);
    printf("\n");
    printf("========================================================\n");
    break;
    case 2:
    system("clear");
    printf("\n========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================\n");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||    | ");
	  printf("\n\t||      ");
	  printf("\n\t||      ");
    printf("\n\n");
    exibir_caracteres(item_jogo_palavra_oculta);
    printf("\n"); printf("\n========================================================\n");
    printf("Letras Já Tentadas:");
    exibir_caracteres(letras_tentadas);
    printf("\n");
    printf("========================================================\n");
    break;
    case 3:
    system("clear");
    printf("\n========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================\n");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||    | ");
	  printf("\n\t||   /  ");
	  printf("\n\t||      ");
    printf("\n\n");
    exibir_caracteres(item_jogo_palavra_oculta);
    printf("\n"); printf("\n========================================================\n");
    printf("Letras Já Tentadas:");
    exibir_caracteres(letras_tentadas);
    printf("\n");
    printf("========================================================\n");
    break;
    case 4:
    system("clear");
    printf("\n========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================\n");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||    | ");
	  printf("\n\t||   / \\ ");
	  printf("\n\t||      "); 
    printf("\n\n");
    exibir_caracteres(item_jogo_palavra_oculta);
    printf("\n"); printf("\n========================================================\n");
    printf("Letras Já Tentadas:");
    exibir_caracteres(letras_tentadas);
    printf("\n");
    printf("========================================================\n");
    break;
    case 5:
    system("clear");
    printf("\n========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================\n");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||   /| ");
	  printf("\n\t||   / \\ ");
	  printf("\n\t||      ");
    printf("\n\n");
    exibir_caracteres(item_jogo_palavra_oculta);
    printf("\n"); printf("\n========================================================\n");
    printf("Letras Já Tentadas:");
    exibir_caracteres(letras_tentadas);
    printf("\n");
    printf("========================================================\n");
    break;
    case 6:
    system("clear");
    printf("\n========================================================");
    printf("\nJogo da Forca\n");
    printf("========================================================\n");
	  printf("\n\t||===== ");
	  printf("\n\t||    | ");
	  printf("\n\t||    O ");
	  printf("\n\t||   /|\\ ");
	  printf("\n\t||   / \\ ");
	  printf("\n\t||      ");
    printf("\n\n");
    exibir_caracteres(item_jogo_palavra_oculta);
    printf("\n"); printf("\n========================================================\n");
    printf("Letras Já Tentadas:");
    exibir_caracteres(letras_tentadas);
    printf("\n");
    printf("========================================================\n");
    break;
  }
}

void exibir_caracteres(char *string){
  for(int i=0;i<(strlen(string));i++){
    if(string[i]!='\0'){
      printf("\t%c",string[i]);
    }
  }  
}

  
void iniciar_jogo(){
  int linha_palavra_sorteada, total_palavras_arquivo_dicionario=0;
  if (verificar_existencia_de_arquivo()==0){
    printf("\nErro! O Dicionário Não Contém Nenhuma Palavra.\nRetornando para o Menu de Opções Principal.\n");
  }
  else{
    arquivo_dicionario=fopen("dicionario.txt","r");
    while(fscanf(arquivo_dicionario,"%s %*[^\n]", item_dicionario.palavra)!=EOF){
      total_palavras_arquivo_dicionario++;    
    }
    fclose(arquivo_dicionario);
    srand(time(NULL));
    linha_palavra_sorteada = rand() % total_palavras_arquivo_dicionario+1;
    printf("A palavra sorteda é %d\n", linha_palavra_sorteada);
    arquivo_dicionario = fopen("dicionario.txt","r");
    for (int i = 0; i < linha_palavra_sorteada; i++){
      fscanf(arquivo_dicionario,"%s %[^\n]", item_jogo.palavra,item_jogo.significado);
    }
    fclose(arquivo_dicionario);
  
    char item_jogo_palavra_oculta[strlen(item_jogo.palavra)];
    for (int i=0;i<strlen(item_jogo.palavra);i++){
      item_jogo_palavra_oculta[i]='_';
    }

    char letras_tentadas[strlen(item_jogo_palavra_oculta)+6], letra;
    int erros=0, acertos=0, sinaliza_erros, contador=0;
    while(1){
      exibir_forca(erros,letras_tentadas,item_jogo_palavra_oculta);
      scanf(" %c",&letra);

      sinaliza_erros=0;
      for (int i=0;i<strlen(letras_tentadas);i++){
        if(letras_tentadas[i]==letra){
          sinaliza_erros=1;
        }
      }
      if(sinaliza_erros==1){
        printf("Erro! A Letra Já Foi Digitadas.\n");
      }
      else{
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
          exibir_forca(erros,letras_tentadas,item_jogo_palavra_oculta);
          printf("Loser");
          break;
        }
        else if (acertos==strlen(item_jogo.palavra)){
          exibir_forca(erros,letras_tentadas,item_jogo_palavra_oculta);
          printf("Você ganhou parabéns");
          break;
        }  
      }
    }
  }
}
    
  




  
    
  


  
