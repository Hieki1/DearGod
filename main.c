#include <stdio.h>
#include <stdio.h>
#include <string.h>

struct dicionario{
char palavra[46];
char significado[200];
}item_cadastro, *ptr_item_cadastro, item_consulta;

void cadastrar_palavra();
int verificar_existencia_de_arquivo();
int verificar_existencia_da_palavra();
void normalizar_palavra();
void buscar_significado();
void consultar_palavra();
void iniciar_jogo();


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
  
  FILE *arquivo_dicionario;

  ptr_item_cadastro=&item_cadastro;
  
  if (verificar_existencia_de_arquivo("dicionario.txt")==0){
    arquivo_dicionario=fopen("dicionario.txt","w");
  }
  else{
    arquivo_dicionario=fopen("dicionario.txt","a");
  }
  
  printf("\nDigite a Nova Palavra para o Cadastro: ");
  fgets(item_cadastro.palavra,sizeof(item_cadastro.palavra),stdin); 
  
  item_cadastro.palavra[strcspn(item_cadastro.palavra,"\n")] = 0; // pra remover o \n que fgets pega, só para meu toque não atacar
  normalizar_palavra(item_cadastro.palavra);
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
  FILE *arquivo_dicionario;
  if (verificar_existencia_de_arquivo("dicionario.txt")==0){
    printf("\nErro! O Dicionário Não Contém Nenhuma Palavra.\nRetornando para o Menu de Opções Principal.\n");
    
  }
  else{
    printf("\nDigite a Palavra para Consulta: ");
    fgets(item_consulta.palavra,sizeof(item_consulta.palavra),stdin);
    item_consulta.palavra[strcspn(item_consulta.palavra,"\n")] = 0;
    normalizar_palavra(item_consulta.palavra);
    if(verificar_existencia_da_palavra(item_consulta.palavra)==0){
      printf("\nErro! O Dicionário Não Contém a Palavra: \"%s\"!\nRetornando para o Menu de Opções Principal.\n",item_consulta.palavra);
      
    }
    else{
      char palavra_existente[46], significado_palavra_existente[500]; 
      arquivo_dicionario=fopen("dicionario.txt","r");
      while(fscanf(arquivo_dicionario,"%s %[^\n]", palavra_existente, significado_palavra_existente)!=EOF){
        if (strcmp(palavra_existente, item_consulta.palavra)==0){
          printf("\nO Significado de \"%s\" é: %s", item_consulta.palavra,significado_palavra_existente);
          fclose(arquivo_dicionario);
        }
      }
      fclose(arquivo_dicionario);
    }  
  }
}


  

int verificar_existencia_de_arquivo(char *nome_arquivo){
  if(fopen(nome_arquivo,"r")==NULL){
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
} // LEMBRAR DEPOIS DE NORMALIZAR ACENTUAÇÃO TBM
  
void iniciar_jogo(){}