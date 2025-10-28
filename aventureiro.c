#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 100
#define MAX_TERRITORIOS 5  // Quantidade máxima de territórios que o progama pode gerenciar

/*~~~~ Criação da struct Territorio ~~~~*/

typedef struct {
    char nome[TAM_STRING];   // nome do território (ex: "Brasil")
    char cor[TAM_STRING];    // cor do exército que controla o território (ex: "vermelho")
    int tropas;              // quantidade de tropas presentes no território
} Territorio;

/* ~~~~PROTÓTIPOS ~~~~*/

void limparBufferEntrada(void);
Territorio *alocarMapa(int qtd);
void cadastrarTerritorios(Territorio *mapa, int qtd);
void exibirTerritorios(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa);

/* ~~~ função que limpa o Buffer de entrada ~~~~*/

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ~~~~ Função usando o Calloc */
Territorio *alocarMapa(int qtd) {
    if (qtd <= 0 || qtd > MAX_TERRITORIOS) return NULL; // validação de entrada
    Territorio *mapa = (Territorio *) calloc((size_t)qtd, sizeof(Territorio));
    return mapa; 
}
// ~~~~ Função para cadastrar territórios ~~~~

void cadastrarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro Território %d ---\n", i + 1);
        printf("Nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        if (mapa[i].tropas < 0) mapa[i].tropas = 0; // evita números negativos
        limparBufferEntrada();
    }
}

// ~~~~ Função para exibir territórios ~~~~

void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== TERRITÓRIOS ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s  | Cor: %s  | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ~~~~ Função para simular ataque entre territórios ~~~~

void atacar(Territorio *atacante, Territorio *defensor) {

    if (atacante->tropas < 2) {
        printf("\nO atacante precisa ter pelo menos 2 tropas para iniciar o ataque.\n");
        return;
    }

    // ~~~~Gera números aleatórios para os dados (1 a 6)~~~~
    int dadoAt = (rand() % 6) + 1;
    int dadoDf = (rand() % 6) + 1;

    printf("\n--- Simulação de Ataque ---\n");
    printf("%s (atacante) rolou: %d\n", atacante->nome, dadoAt);
    printf("%s (defensor) rolou: %d\n", defensor->nome, dadoDf);

    //~~~~~ Caso o atacante vença ~~~~
    if (dadoAt > dadoDf) {
        printf("Resultado: atacante venceu!\n");

        // defensor muda para a cor do atacante
        strncpy(defensor->cor, atacante->cor, TAM_STRING - 1);
        defensor->cor[TAM_STRING - 1] = '\0'; // garante o final da string

        // metade das tropas do atacante passam para o defensor
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;

        // o atacante fica com a outra metade
        atacante->tropas -= tropasTransferidas;

        // Exibição de resultados
        printf("%s agora pertence à cor '%s' e tem %d tropas.\n",
               defensor->nome, defensor->cor, defensor->tropas);
        printf("%s (atacante) ficou com %d tropas.\n",
               atacante->nome, atacante->tropas);
    }
    //~~~~~ Caso o defensor vença ~~~~
    else {
        printf("Resultado: defensor resistiu!\n");
        if (atacante->tropas > 0) atacante->tropas--; // perde 1 tropa
        printf("%s perdeu 1 tropa e agora tem %d tropas.\n",
               atacante->nome, atacante->tropas);
    }
}

// ~~~~ Função para liberar memória alocada ~~~~
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}
/* ~~~~ Função principal ~~~~*/
int main(void) {
    srand((unsigned int) time(NULL)); // inicializa gerador de números aleatórios

    int qtd;
    printf("Quantos territórios deseja cadastrar (1..%d)? ", MAX_TERRITORIOS);
    if (scanf("%d", &qtd) != 1) {
        printf("Entrada inválida.\n");
        return 1;
    }
    limparBufferEntrada();

    if (qtd <= 0 || qtd > MAX_TERRITORIOS) {
        printf("Quantidade inválida. Encerrando.\n");
        return 1;
    }

    // Chama a função de alocação dinâmica
    Territorio *mapa = alocarMapa(qtd);
    if (mapa == NULL) {
        printf("Falha na alocação de memória.\n");
        return 1;
    }

    // ~~~~Cadastro dos territórios~~
    cadastrarTerritorios(mapa, qtd);

    // Loop principal com menu
    int opcao = -1;
    while (1) {
        exibirTerritorios(mapa, qtd);
        printf("\nMenu:\n");
        printf("1 - Realizar um ataque\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }
        limparBufferEntrada();

        // Sai do loop
        if (opcao == 0) break;

        // Opção de ataque
        if (opcao == 1) {
            int at, def;
            printf("Número do território ATACANTE (ou 0 para cancelar): ");
            if (scanf("%d", &at) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); continue; }
            limparBufferEntrada();
            if (at == 0) continue;

            printf("Número do território DEFENSOR (ou 0 para cancelar): ");
            if (scanf("%d", &def) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); continue; }
            limparBufferEntrada();
            if (def == 0) continue;

            // Valida se os números estão dentro do intervalo
            if (at < 1 || at > qtd || def < 1 || def > qtd) {
                printf("Índice inválido. Escolha territórios entre 1 e %d.\n", qtd);
                continue;
            }
            // Evita atacar a si mesmo
            if (at == def) {
                printf("Um território não pode atacar a si mesmo.\n");
                continue;
            }

            // Ponteiros apontam para os territórios selecionados
            Territorio *pa = &mapa[at - 1];
            Territorio *pd = &mapa[def - 1];

            // Valida se são territórios de cores diferentes
            if (strcmp(pa->cor, pd->cor) == 0) {
                printf("Não é permitido atacar território da mesma cor.\n");
                continue;
            }

            // Chama a função de ataque passando ponteiros
            atacar(pa, pd);
        } else {
            printf("Opção desconhecida. Tente novamente.\n");
        }
    }

    // Libera memória antes de encerrar
    liberarMemoria(mapa);
    printf("Memória liberada. Programa encerrado.\n");
    return 0;
}
