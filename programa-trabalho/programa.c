#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct Node {
    int id_prato;
    char prato[100];
    struct Node* next;
};

struct threadInserirPratoArg {
    struct Node** head;
};

struct Node* criaNo(char *prato, int id) {
    struct Node* newNo = (struct Node*)malloc(sizeof(struct Node));
    if (newNo == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    newNo->id_prato = id;
    strcpy(newNo->prato, prato);
    newNo->next = NULL;
    return newNo;
}

void adicionarItem(struct Node** head, char* prato, int id) {
    struct Node* newNo = criaNo(prato, id);
    newNo->next = *head;
    *head = newNo;
    printf("Prato '%s' com ID %d chegou na cozinha.\n", prato, id);
}

void printarLista(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("ID %d: %s -> ", current->id_prato, current->prato);
        current = current->next;
    }
    printf("NULL\n");
}

void insertPrato(int number, struct Node** head, int *id_counter)
{
    (*id_counter)++;
    if (number == 0)
    {
        adicionarItem(head, "pao de queijo com linguica", *id_counter);
    }
    else if (number == 1)
    {
        adicionarItem(head, "broa de milho + cafe", *id_counter);
    }
    else if (number == 2)
    {
        adicionarItem(head, "biscoito frito de polvilho", *id_counter);
    }
    else if (number == 3)
    {
        adicionarItem(head, "torresmo com rabada", *id_counter);
    }
    else if (number == 4)
    {
        adicionarItem(head, "guaranazinho com croquete", *id_counter);
    }
    else if (number == 5)
    {
        adicionarItem(head, "bolo de milho com cafe coado", *id_counter);
    }
    else if (number == 6)
    {
        adicionarItem(head, "cafe coado", *id_counter);
    }
    else if (number == 7)
    {
        adicionarItem(head, "doce de abobora com coco ralado", *id_counter);
    }
    else if (number == 8)
    {
        adicionarItem(head, "rapadura com goiabada e queijo", *id_counter);
    }
    else if (number == 9)
    {
        adicionarItem(head, "pamonha e cafe com leite", *id_counter);
    }
}

void deletarItem(struct Node** head, char* key) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    if (temp != NULL && strcmp(temp->prato, key) == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->prato, key) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("O item '%s' nao foi encontrado na lista.\n", key);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void *thread_adicionar_prato(void* args)
{
    struct threadInserirPratoArg *threadArgs = (struct threadInserirPratoArg *)args;
    int number = rand() % 10;
    static int id_counter = 0; // Inicializa o contador de IDs estático
    insertPrato(number, threadArgs->head, &id_counter);
    return NULL;
}

void *thread_escolha(void *args)
{
    sleep(5); // Exemplo de operação da thread
    return NULL;
}

void gera_pedido(struct Node* head)
{

    pthread_t thread_gera_pedido;
    struct threadInserirPratoArg *args_inserir = malloc(sizeof(struct threadInserirPratoArg));
    args_inserir->head = &head;

    while (1)
    {
        pthread_create(&thread_gera_pedido, NULL, thread_adicionar_prato, (void *)args_inserir);
        sleep(5); // Intervalo entre pedidos
    }
}

int main() {
    struct Node* head = NULL;
    int vitoria = 0;
    gera_pedido();
    
    while (vitoria == 0)
    {
        // pthread_t pega_escolha_usuario;
        // pthread_create(&pega_escolha_usuario, NULL, thread_escolha, NULL);
        printarLista()
    }

    return 0;
}
