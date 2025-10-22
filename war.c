#include <stdio.h>
#include <string.h>

// ~~~~ Constantes Globais ~~~~ (caso precise)
#define MAX_TERRITORIOS 5
#define TAM_STRING 100

//~~~~ Definindo estrutura (struct)~~~~

struct Territorio {
char  nome_do_territorio [TAM_STRING];
char cor_do_exercito [TAM_STRING];
int numero_de_tropa;
};

//~~~~Crianndo uma função para limpar o buffer de entrada ~~~

void limparBufferEntrada () { 
    int c;
    while ((c= getchar()) != EOF);
    
}

 //~~~ Função Principal onde possamos armazenar os 5 teritorios ~~~~
int main(){
    struct Territorio t[5]; 
    int i; 

// ~~~~ Cadastro dos Territorios ~~~
    printf("=== CADASTRO DE TERRITORIOS ===\n");

    for (i = 0; i < 5; i++) {
        printf("\n Territorio %d: \n", i +1);

        printf("Nome do Territorio:");
        scanf("%s",t[i].nome_do_territorio);

        printf("Cor do Exercito:");
        scanf("%s",t[i].cor_do_exercito);
        
        printf("Numero de tropas:\n");
        scanf("%d",&t[i].numero_de_tropa);
    }

    limparBufferEntrada();
    
    printf("\n=== TERRITORIOS CADASTRADOS ===\n");


    for (i = 0; i < 5; i++) {
        printf("\n Territorio %d: \n", i +1);

        printf("Nome do territorio: %s\n",t[i].nome_do_territorio);
        printf("Cor do Exercito :%s\n",t[i].cor_do_exercito);
        printf("Numero de Tropas: %d \n",t[i].numero_de_tropa);
    
   }
   return 0;
}
