// Trabalho de Desenvolvimeto de Algoritmos - Jogo da Forca - 2022
// Miguel Montenegro Melnik 11.119.035-1

// Inlusão das bibliotecas utilizadas.
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definição do dicionario como strcut que possui dois vetores char (palavra e significado), bem como das variáves que são desse tipo (item_cadastro, item_consulta, item_jogo, item_dicionario).
struct dicionario{
// O vetor palavra foi definido como tendo 46 posições, pois a maior palavra da língua portuguesa possui essa quantidade de caracteres.
char palavra[46];
char significado[200];
}item_cadastro, item_consulta, item_jogo, item_dicionario; 

// Definição do arquivo_dicionario como variável global do tipo ponteiro FILE, para a utilização em diversas partes do código.
FILE *arquivo_dicionario; 

// Declaração das funções primárias do programa

// Declaração da função tipo void responsável pelo cadastro de novas palavras no arquivo de dicionário do tipo texto.
void cadastrar_palavra();

// Declaração da função tipo void responsável pela consulta de palavras já cadastradas no arquivo de dicionário do tipo texto.
void consultar_palavra();

// Declaração da função tipo void responsável pelo início do jogo da forca com as palavras já cadastradas no arquivo de dicionário do tipo texto.
void iniciar_jogo();

// Declaração das funções secundárias do programa, respomsáveis por certas funções utilizadas dentro das funções primárias.

// Declaração da função tipo int responsável pela verificação da existência, ou não, do arquivo de dicionário do tipo texto.
int verificar_existencia_de_arquivo();

// Declaração da função tipo int responsável pela verificação da existência, ou não, da palavra, endereçada pelo ponteiro char recebido, no arquivo de dicionário do tipo texto.
int verificar_existencia_da_palavra(char *palavra_inserida);

// Declaração da função tipo void responsável por tornar todos os caracteres, endereçados pelo ponteiro char recebido, minúsculos, evitando, assim, com que palavras iguais, como "MACACO" e "macaco", sejam indentificadas pelo programa como diferentes. 
void normalizar_palavra(char *palavra);

// Declaração da função tipo void responsável por exibir uma mensagem solicitando o pressionamento de qualquer caractere, para continuar a execução do programa e, com isso, graças a suas posições no código, retornar para o menu principal.
void retornar_menu();

// Declaração da função tipo void responsável por exbir o desenho da forca de acordo com o número de erros recebidos.
void exibir_forca(int erros);

// Declaração das funções terciárias, responsáveis pela estilização do texto exibido.

// Declaração da função tipo void responsável por pintar o conteúdo endereçado pelo ponteiro char recebido, da cor verde e em negrito.
void string_verde_negrito(char *string);

// Declaração da função tipo void responsável por pintar o conteúdo endereçado pelo ponteiro char recebido, da cor verde, em negrito e sublinhado.
void string_verde_negrito_sublinhado(char *string);

// Declaração da função tipo void responsável por pintar o conteúdo endereçado pelo ponteiro char recebido, da cor vermelha e em negrito.
void string_vermelha_negrito(char *string);

// Declaração da função tipo void responsável por pintar o conteúdo endereçado pelo ponteiro char recebido, da cor vermelha, em negrito e sublinhado.
void string_vermelha_negrito_sublinhado(char *string);

// Definição da função do tipo void principal responsável por: exibir as opções do programa para o usuário, receber sua entrada e, de acordo com essa, chamar as funções primárias.
int main(void) {
  
  // Declaração da variável local do tipo inteiro para receber a a opção selecionada pelo usuário de acordo com o menu.
  int op; 
  
  // Início de um processo de loop que só termina com a inserção da opção 4, solicitando o encerramento da execução do programa.
  do{ 
    
  // Limpeza de qualquer informação exibida na tela.
  system("clear"); 
    
  // Exibe o menu com as opções disponíveis para seleção.
  printf("========================================================");
  printf("\nMenu de Opções Principal\n");
  printf("========================================================");
  printf("\n1 - Cadastrar Nova Palavra\n");
  printf("\n2 - Consultar Palavra\n");
  printf("\n3 - Iniciar Jogo da Forca\n");
  printf("\n4 - Encerrar o Programa\n");
  printf("========================================================"); 
  printf("\nDigite o Número da Opção Desejada: ");
    
  // Recebe o input do tipo int do usuário, descartando o caractere criado com o enter, que poderia preencher o buffer.
  scanf("%d%*c", &op); 
    
    // Chama, de acordo com a variável inteira recebida, uma das funções primárias.
    switch(op){

      // Chama a função de cadastro de nova palavra e depois encerra a interação do loop, fazendo com que se recomece o ciclo, com uma nova interação.
      case 1: 
        cadastrar_palavra();
        break;

      // Chama a função de consulta de nova palavra e depois encerra a interação do loop, fazendo com que se recomece o ciclo, com uma nova interação.
      case 2: 
        consultar_palavra();
        break;
      
       // Chama a função de jogo da forca e depois encerra a interação, fazendo com que se recomece o ciclo, com uma nova interação.
      case 3: 
        iniciar_jogo(); 
        break;

      // Encerra a interação e também o loop, solicitando, assim, o encerramento da execução do programa.
      case 4:
        break;
    }
  }while(op!=4);
}


void cadastrar_palavra(){
  
  // Chama a função que verifica se o arquivo do dicionário do tipo texto foi criado ou não. Caso o retorno dessa função seja 0, o que indica a inexistencia do dicionário, cria o arquivo, abrindo em modo de escrita (w). Caso contrário, abre o arquivo em modo de append (a), permitindo a adição de novas palavras sem a perda do conteúdo já existente.
  if (verificar_existencia_de_arquivo()==0){
    arquivo_dicionario=fopen("dicionario.txt","w");
  }
  else{
    arquivo_dicionario=fopen("dicionario.txt","a");
  }
  
  // Limpeza de qualquer informação exibida na tela. 
  system("clear");

  // Exibe o cabeçalho e a mensagem solicitando a inserção da palavra para cadastro.
  printf("========================================================");
  printf("\nCadastro de Palavra\n");
  printf("========================================================");
  printf("\nDigite a Nova Palavra para o Cadastro: ");

  // Recebe do usuário o vetor de caracteres palavra, por meio da variável do tipo dicionário.
  fgets(item_cadastro.palavra,sizeof(item_cadastro.palavra),stdin); 

  // Remove o \n (enter) registrado no vetor palavra pela função fgets, durante a etapa anterior, com o intuito de manter a formatação do arquivo do dicionário com palavra e singificado na mesma linha.
  item_cadastro.palavra[strcspn(item_cadastro.palavra,"\n")] = 0; 

  // Chama a função que normaliza ou formata o vetor palavra inserido, de modo a tornar todos os caracteres minúsculos, evitando, assim, com que palavras iguais, sejam indentificadas, a seguir, como únicas.
  normalizar_palavra(item_cadastro.palavra);

  // Chama a função que verifica se a palavra existe ou não no dicionário. Caso o retorno dessa função seja 1, o que indica que o conteúdo do vetor palavra já foi registrado anteriormente, entra na condição de encerramento de cadastro para evitar duplicatas. Caso contrário prossegue com a execução normal do proceso de cadastro.
  if(verificar_existencia_da_palavra(item_cadastro.palavra)==1){

    // Exibe uma mensagem de erro na cor vermelha em negrito, avisando para o usuário que a palavra digitada, exposta em vermelho em negrito e sublinhada, já está presente no arquivo de texto do dicionário.
    string_vermelha_negrito("\nErro! A Palavra: ");  
    string_vermelha_negrito_sublinhado(item_cadastro.palavra);
    string_vermelha_negrito(" Já Existe no Dicionário!\n");

    // Chama a função que solicita e aguarda o pressionamento de qualquer caractere para retomar a execução do programa e, com isso, retornar para o menu principal.
    retornar_menu();
  }
  else{

    // Exibe uma mensagem solicitando a inserção do significado da palavra sendo cadastrada.
    printf("\nDigite o Significado da Nova Palavra para o Cadastro: ");

     // Recebe do usuário o vetor de caracteres significado, por meio da variável do tipo dicionário. O \n (enter) obtido com o fgets não é removido, neste momento, pois inibe a necessidade da colocação de um \n na estrutura do comando de escrita no arquivo texto, simplificando, com isso, o processo de pular linhas entre palavras diferentes que são mantidas cada qual na sua própria linha.
    fgets(item_cadastro.significado,sizeof(item_cadastro.significado),stdin);

    // Escreve no arquivo texto o vetor de caracteres palavra e significado separados por um espaço em branco.
    fprintf(arquivo_dicionario,"%s %s",item_cadastro.palavra,item_cadastro.significado);

    // Fecha o arquivo de texto do dicionário.
    fclose(arquivo_dicionario);

    // Exibe uma mensagem de sucesso na cor verde em negrido, avisando par o usuário que a palavra digitada, exposta em verde em negrito sublinhado, foi registrada no dicionário.
    string_verde_negrito("\nSucesso! A Palavra: ");  
    string_verde_negrito_sublinhado(item_cadastro.palavra);
    string_verde_negrito(" Foi Registrada no Dicionário!\n");

        // Chama a função que solicita e aguarda o pressionamento de qualquer caractere para retomar a execução do programa e, com isso, retornar para o menu principal.
    retornar_menu();
  }    
}

void consultar_palavra(){

  // Chama a função que verifica se o arquivo do dicionário do tipo texto foi criado ou não. Caso o retorno dessa função seja 0, o que indica a inexistencia do dicionário, entra na condição de encerramento desse processo, pois se o dicionário não existe, nenhuma palavra foi cadastrada, logo, não há o que consultar. Caso contrário prossegue com a execução normal do proceso de consulta.
  if (verificar_existencia_de_arquivo()==0){
    
    // Exibe uma mensagem de erro na cor vermelha em negrito, avisando para o usuário que o dicionário não contém nenhuma palavra. Isso para fins de indicação é o suficiente para o utilizador, já que o correto seria exibir uma mensagem dizendo que o dicionário não existe.
    string_vermelha_negrito("\nErro! O Dicionário Não Contém Nenhuma Palavra.\n");

     // Chama a função que solicita e aguarda o pressionamento de qualquer caractere para retomar a execução do programa e, com isso, retornar para o menu principal.
    retornar_menu();
  }
  else{
    
    // Limpeza de qualquer informação exibida na tela. 
    system("clear");

     // Exibe o cabeçalho e a mensagem solicitando a inserção da palavra para consulta.
    printf("========================================================");
    printf("\nConsulta de Palavra\n");
    printf("========================================================");
    printf("\nDigite a Palavra para Consulta: ");

    // Recebe do usuário o vetor de caracteres palavra, por meio da variável do tipo dicionário.
    fgets(item_consulta.palavra,sizeof(item_consulta.palavra),stdin);

     // Remove o \n (enter) registrado no vetor palavra pela função fgets, durante a etapa anterior, com o intuito de realizar a consulta corretamente, evitando com que a palavra tenha um caractere a mais que pode afetar a comparação realidada com as palavra do dicionário que não o tem. Exemplo: macaco (dicionário) macaco\n (consulta) -> o programa consideraria que a palavra consultada não existe sem essa função.
    item_consulta.palavra[strcspn(item_consulta.palavra,"\n")] = 0;

    // Chama a função que normaliza ou formata o vetor palavra inserido, de modo a tornar todos os caracteres minúsculos, evitando, assim, com que palavras iguais, sejam indentificadas, a seguir, como únicas.
    normalizar_palavra(item_consulta.palavra);

    // Chama a função que verifica se a palavra consultada existe ou não no dicionário. Caso o retorno dessa função seja 0, o que indica que a palavra consultada não existe no arquivo,  entra na condição de encerramento da consulta. Caso contrário prossegue com a execução normal do proceso de cadastro.
    if(verificar_existencia_da_palavra(item_consulta.palavra)==0){
      
      // Exibe uma mensagem de erro na cor vermelha em negrito, avisando para o usuário que o dicionário não contém a palavra consulta, exibida na cor vermelha em negrito sublinado. 
      string_vermelha_negrito("\nErro! O Dicionário Não Contém a Palavra: ");
      string_vermelha_negrito_sublinhado(item_consulta.palavra);
      printf("\n");

      // Chama a função que solicita e aguarda o pressionamento de qualquer caractere para retomar a execução do programa e, com isso, retornar para o menu principal.
      retornar_menu();
    }
    else{
      
      // Abre o arquivo de texto do dicionário no modo de leitura.
      arquivo_dicionario=fopen("dicionario.txt","r");

      // Realiza a leitura linha a linha até o fim do arquivo de texto do dicionário, guardando a palavra e significado encontrados.
      while(fscanf(arquivo_dicionario,"%s %[^\n]", item_dicionario.palavra, item_dicionario.significado)!=EOF){
        
        // Caso a comparação da palavra consultada com uma palavra extraída do dicionário seja positiva, exibe uma mensagem com o significado extraído.
        if (strcmp(item_dicionario.palavra, item_consulta.palavra)==0){
          printf("\nO Significado de \"%s\" é: %s\n", item_consulta.palavra,item_dicionario.significado);

          // Fecha o arquivo de texto do dicionário.
          fclose(arquivo_dicionario);

          // Chama a função que solicita e aguarda o pressionamento de qualquer caractere para retomar a execução do programa e, com isso, retornar para o menu principal.
          retornar_menu();
        }
      }
    }  
  }
} 

void iniciar_jogo(){
  
  // Declaração de variáveis do tipo inteiro, sendo uma delas um contador (total_palavras_arquivo_dicionario).
  int linha_palavra_sorteada, total_palavras_arquivo_dicionario=0;

   // Chama a função que verifica se o arquivo do dicionário do tipo texto foi criado ou não. Caso o retorno dessa função seja 0, o que indica a inexistência do dicionário, entra na condição de encerramento desse processo, pois se o dicionário não existe, nenhuma palavra foi cadastrada, logo, não há nehuma palavra para ser usada no jogo. Caso contrário prossegue com o inicio do jogo.
  if (verificar_existencia_de_arquivo()==0){

    // Exibe uma mensagem de erro na cor vermelha em negrito, avisando para o usuário que o dicionário não contém nenhuma palavra.
    string_vermelha_negrito("\nErro! O Dicionário Não Contém Nenhuma Palavra.\n");

    // Chama a função que solicita e aguarda o pressionamento de qualquer caractere para retomar a execução do programa e, com isso, retornar para o menu principal.
    retornar_menu();
  }
  else{

    // Abre o arquivo de texto do dicionário no modo de leitura.
    arquivo_dicionario=fopen("dicionario.txt","r");

    // Realiza a leitura, linha a liha, até o fim do arquivo de texto do dicionário, incrementando o contador do total de palavras toda vez que o processo é executado com sucesso.
    while(fscanf(arquivo_dicionario,"%s %*[^\n]", item_dicionario.palavra)!=EOF){
      total_palavras_arquivo_dicionario++;    
    }

    // Fecha o arquivo de texto do dicionário.
    fclose(arquivo_dicionario);

    // Chama a função que cria seeds númericas aleatórias, definindo que o processo será realizado com base no horário do sistema.
    srand(time(NULL));

    // Sorteia uma palavra aletória, limitada a quantidade de palavras do arquivo, que é, por consequência, da formatação do arquivo, também, igual a quantidade de linhas registradas. É importante mencionar que o comando utilizado realiza o sorteio seguindo a seguinte formatação: 0<=valor_sorteado<valor_máximo, logo foi necessário somar um junto da variável total_palavras_arquivo_dicionario a fim de permitir que a palavra na última linha pudesse participar também da seleção aleátoria.
    linha_palavra_sorteada = rand() % total_palavras_arquivo_dicionario+1;

    // Abre o arquivo de texto do dicionário no modo de leitura.
    arquivo_dicionario = fopen("dicionario.txt","r");

    // Realiza a leitura, linha a linha, do arquivo de texto do dicionário, armazenando sempre palavra e significado, até, finalmente, chegar na linha do termo sorteado.
    for (int i = 0; i < linha_palavra_sorteada; i++){
      fscanf(arquivo_dicionario,"%s %[^\n]", item_jogo.palavra,item_jogo.significado);
    }
    
    // Fecha o arquivo de texto do dicionário.
    fclose(arquivo_dicionario);

    // Declaração de um vetor de caracteres, com o tamanho da palavra que estava na linha sorteada aleátoriamente, com o propósito de indicar quais letras fazem parte ou não da palavra sorteada para o jogo da forca.
    char item_jogo_palavra_oculta[strlen(item_jogo.palavra)];

    // Escrita de '-' ao longo do vetor de caracteres declarado anteriormente.
    for (int i=0;i<strlen(item_jogo.palavra);i++){
      item_jogo_palavra_oculta[i]='_';
    }

    //Declaração de um vetor de caracteres, com a quantidade de letras do alfabeto, ocupado totalmente por zeros, para armazenar as letras já tentadas pelo usuário para advinhar a plavra sorteada.
    char letras_tentadas[26]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   

    // Declaração de uma variável do tipo char, que será usada para receber as letras inseridas pelo usuário para advinhação da palavra do jogo.
    char letra;

    // Declaração de variáveis do tipo int, sendo elas: 3 contadores e 1 falg ou indicador. 
    int erros=0, acertos=0, sinaliza_erros, contador=0;

    // Inicia um loop
    while(1){

      // Chama a função que exibe tanto o cabeçalho do jogo quanto a imagem da forca de em função da quantidade de erros.
      exibir_forca(erros);

      // Exibe o vetor que serve de indicação para as letras que fazem parte, ou não, da palavra sorteada, de maneira tabulada.
      for (int i=0;i<strlen(item_jogo.palavra);i++){
      printf("\t%c",item_jogo_palavra_oculta[i]);
      }
      
      // Pula uma linha na exibição.
      printf("\n"); 

      // Exibe uma linha separando o conteúdo anterior (forca e indicação da palavra sorteada) do conteúdo seguinte (letras já tentadas).
      printf("\n========================================================\n");

      // Exibe todas as letras já tentadas pelo usuário, sendo elas certas ou não. Para tal, só expõe as posições do vetor de caracteres que não estejam ocupadas pelos zeros inseridos na declaração da variável.
      printf("Letras Já Tentadas:");
      for (int i=0;i<26;i++){
          if(letras_tentadas[i]!='0'){
            printf("%c ",letras_tentadas[i]);
          }
      }
      
      // Pula uma linha na exibição.
      printf("\n");

      // Exibe uma linha separando o conteúdo anterior (letras já tentadas) do conteúdo seguinte (mensagem solicitando a inserção de uma letra para a advinhação).
      printf("========================================================\n");

      // Exibe uma mensagem solicitando a inserção de um caractere para a advinhação.
      printf("Digite Uma Letra: ");

      // Recebe o caractere digitado pelo usuário. Neste ponto do código é válido mencionar que o espaço existente entre as aspas da esquerda e o porcentagem, dentro do comando scanf, é necessário pela natureza do replit e seu compilador que não funcionam adequadamente sem isso.
      scanf(" %c",&letra);

      // Chama a função que formata o caractere inserido para minúsculo, permitindo com que a letra inserida, seja ela maiúscula ou minúscula, seja indetifica corretamente caso exista, ou não, na palavra sorteada.
      normalizar_palavra(&letra);

      // Atribui valor 0 para a variável sinalizadora.
      sinaliza_erros=0;

      // Compara a letra digitada aos caracteres do vetor que armazena as letras tentadas antes. Caso essa comparação seja positiva, a letra já foi digitada, assim, há a alteração do valor da variável de sinalização. 
      for (int i=0;i<strlen(letras_tentadas);i++){
        if(letras_tentadas[i]==letra){
          sinaliza_erros=1;
        }
      }

      // Caso a variável sinalizadora seja 1, encerra a interação e recomeça o processo, solicitando, assim, a inseração de outra letra. Caso contrário, continua para a próxima etapa da execução.  
      if(sinaliza_erros!=1){
        
        // Armazena no vetor de letras tentadas, na posição dada pelo contador, a letra inserida pelo usuário, que, logicamente, ainda não tinha sido inserida. 
        letras_tentadas[contador]=letra;

        // Incrementa o contador.
        contador++;

        // Atribui valor 1 para a variável sinalizadora.
        int sinaliza_erros=1;

        // Realiza a comparação do caractere inserido com todos os caracteres da palavra sorteada. Caso haja esse caractere na palavra sorteada, altera o caractere '-' do vetor de indicação pela letra digitada, incrementa o contador de número de acertos e atribui valor zero para a variável de sinalização. Caso contrário, apenas, incrementa o contador de número de erros.
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

        // Verifica se os erros são iguais a 6, ou seja, se o boneco foi enforcado. Caso afirmativo, executa a secção, a seguir, que finaliza o jogo.
        if(erros==6){

         // Chama a função que exibe tanto o cabeçalho do jogo quanto a imagem da forca de em função da quantidade de erros.
      exibir_forca(erros);

      // Exibe o vetor que serve de indicação para as letras que fazem parte, ou não, da palavra sorteada, de maneira tabulada.
      for (int i=0;i<strlen(item_jogo.palavra);i++){
      printf("\t%c",item_jogo_palavra_oculta[i]);
      }
      
      // Pula uma linha na exibição.
      printf("\n"); 

      // Exibe uma linha separando o conteúdo anterior (forca e indicação da palavra sorteada) do conteúdo seguinte (letras já tentadas).
      printf("\n========================================================\n");

      // Exibe todas as letras já tentadas pelo usuário, sendo elas certas ou não. Para tal, só expõe as posições do vetor de caracteres que não estejam ocupadas pelos zeros inseridos na declaração da variável.
      printf("Letras Já Tentadas:");
      for (int i=0;i<26;i++){
          if(letras_tentadas[i]!='0'){
            printf("%c ",letras_tentadas[i]);
          }
      }
      
      // Pula uma linha na exibição.
      printf("\n");
          
          // Exibe uma mensagem, na cor vermelha em negrito, avisando para o usuário que ele perdeu o jogo e o boneco foi enforcado. Além disso, apresenta qual era a palavra sorteada, exibida em vermelho em negrito e sublinhado, e seu significado, em vermelho e negrito.
          string_vermelha_negrito("\nVocê Perdeu! O Boneco Foi Enforcado!\n");
          string_vermelha_negrito("\nA Palavra Secreta Era: ");
          string_vermelha_negrito_sublinhado(item_jogo.palavra);
          string_vermelha_negrito(" Que Significa: ");
          string_vermelha_negrito(item_jogo.significado);

          // Pula uma linha na exibição.
          printf("\n");

          // Recebe o \n (enter) aramazenado pelo buffer.
          getchar();

          // Chama a função que solicita e aguarda o pressionamento de qualquer caractere para retomar a execução do programa e, com isso, retornar para o menu principal.
          retornar_menu();

          // Encerra o loop e, com isso, o jogo.
          break;
        }

        // Verifica se os acertos são iguais ao tamanho da palavra sorteada, ou seja, se a palavra foi acertada pelo usuário. Caso afirmativo, executa a secção, a seguir, que finaliza o jogo.
        else if (acertos==strlen(item_jogo.palavra)){
      
          // Chama a função que exibe tanto o cabeçalho do jogo quanto a imagem da forca de em função da quantidade de erros.
          exibir_forca(erros);

          // Exibe o vetor que serve de indicação para as letras que fazem parte, ou não, da palavra sorteada, de maneira tabulada.
          for (int i=0;i<strlen(item_jogo.palavra);i++){
            printf("\t%c",item_jogo_palavra_oculta[i]);
          }
      
          // Pula uma linha na exibição.
          printf("\n"); 

          // Exibe uma linha separando o conteúdo anterior (forca e indicação da palavra sorteada) do conteúdo seguinte (letras já tentadas).
          printf("\n========================================================\n");

          // Exibe todas as letras já tentadas pelo usuário, sendo elas certas ou não. Para tal, só expõe as posições do vetor de caracteres que não estejam ocupadas pelos zeros inseridos na declaração da variável.
          printf("Letras Já Tentadas:");
          for (int i=0;i<26;i++){
            if(letras_tentadas[i]!='0'){
              printf("%c ",letras_tentadas[i]);
            }
          }
      
          // Pula uma linha na exibição.
          printf("\n");

           // Exibe uma mensagem, na cor verde em negrito, avisando para o usuário que ele ganhou o jogo e o boneco não foi enforcado. Além disso, apresenta qual era a palavra sorteada, exibida em verde em negrito e sublinhado, e seu significado, em verde em negrito.
          string_verde_negrito("\nVocê Ganhou! O Boneco Não Foi Enforcado!\n");
          string_verde_negrito("\nA Palavra Secreta Era: ");
          string_verde_negrito_sublinhado(item_jogo.palavra);
          string_verde_negrito(" Que Significa: ");
          string_verde_negrito(item_jogo.significado);

          // Pula uma linha na exibição.
          printf("\n");

          // Recebe o \n (enter) aramazenado pelo buffer.
          getchar();
          
          // Chama a função que solicita e aguarda o pressionamento de qualquer caractere para retomar a execução do programa e, com isso, retornar para o menu principal.
          retornar_menu();

          // Encerra o loop e, com isso, o jogo.
          break;
        }  
      }
    }
  }
}


int verificar_existencia_de_arquivo(){
  
  //Tenta realizar a abertura do arquivo do dicionário (dicionario.txt) no modo de leitura (r). Caso não seja possível retorna 0, o contrário retorna 1.
  if(fopen("dicionario.txt","r")==NULL){
    return 0;
  }
  else{
    return 1;
  }
}


int verificar_existencia_da_palavra(char *palavra_inserida){
  
  // Declaração de um vetor de caracteres de tamanho 46.
  char palavra_existente[46];

  // Abertura do arquivo de texto do dicionário e atribuição deste para váriavl global do tipo FILE.
  arquivo_dicionario=fopen("dicionario.txt","r");

  //Realiza a leitura do arquivo de texto do dicionário, até o seu fim, só armazenando o primeiro string da linha. Ou seja, só as palavras são guardadas, ignorando, desse modo, os significados, que coexistem pela formatação utilizada nas mesmas linhas.
  while(fscanf(arquivo_dicionario,"%s %*[^\n]", palavra_existente)!=EOF){

      //Realiza a comparação da palavra endereçada pelo ponteiro do tipo char com a palavra lida do dicionário. Caso as palavras sejam iguais, fecha o arquivo e retorna 1. Caso contrário, fecha o arquivo e retorna 0, indicando que não existe uma palavra no dicionário igual a inserida pelo usuário.
      if (strcmp(palavra_existente, palavra_inserida)==0){
        fclose(arquivo_dicionario);
        return 1;
      }
    }
  fclose(arquivo_dicionario);
  return 0;
}

// Realiza a formatação da palavra enderaçada pelo ponteiro, transformando todos os caracteres em minúsculas, por meio do uso da tabela ASCII.
void normalizar_palavra(char *palavra){
   for (int i = 0; i<strlen(palavra); i++){
    if (palavra[i] >= 65 && palavra[i] <= 90){
      palavra[i] = palavra[i] + 32; 
    }
  }
} 

// Realiza a exibição da forca de acordo com a quantidade de erros recebidos.
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

  //Exibe a mensagem solicitando o pressionamento de qualquer tecla para retornar para o Menu de Opções Principal.
  printf("\nPressione Qualquer Tecla para Retornar para o Menu de Opções Principal.\n");

  //Recebe qualquer caractere do usuário.
  getchar();
}

void string_verde_negrito(char *string){
 
  // Altera a cor de exibição do texto para verde em negrito.
  printf("\033[1;32m");

  // Exibe o texto endereçado pelo ponteiro recebido.
  printf("%s",string);

  // Redefine a cor de exibição para o padrão.
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


  
    
  


  
