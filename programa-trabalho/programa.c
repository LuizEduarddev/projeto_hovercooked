#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include<unistd.h>

struct Node {
    char prato[100];
    struct Node* next;
};

struct threadInserirPratoArg {
    struct Node* head;
};

struct Node* criaNo(char *prato) {
    struct Node* newNo = (struct Node*)malloc(sizeof(struct Node));
    if (newNo == NULL) {
        printf("Erro!\n");
        exit(1);
    }
    strcpy(newNo->prato, prato);
    newNo->next = NULL;
    return newNo;
}

void adicionarItem(struct Node* head, char* prato) {
    struct Node* newNo = criaNo(prato);
    newNo->next = head;
    head = newNo;
    printf("prato '%s' chegou na cozinha.\n", prato);
}

void printarLista(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%s -> ", current->prato);
        current = current->next;
    }
    printf("NULL\n");
}

void insertPrato(int number, struct Node* head)
{
    if (number == 0)
    {
        adicionarItem(head, "pao de queijo com linguica");
    }
    else if (number == 1)
    {
        adicionarItem(head, "broa de milho + cafe");
    }
    else if (number == 2)
    {
        adicionarItem(head, "biscoito frito de polvilho");
    }
    else if (number == 3)
    {
        adicionarItem(head, "torresmo com rabada");
    }
    else if (number == 4)
    {
        adicionarItem(head, "guaranazinho com croquete");
    }
    else if (number == 5)
    {
        adicionarItem(head, "bolo de milho com cafe coado");
    }
    else if (number == 6)
    {
        adicionarItem(head, "cafe coado");
    }
    else if (number == 7)
    {
        adicionarItem(head, "doce de abobora com coco ralado");
    }
    else if (number == 8)
    {
        adicionarItem(head, "rapadura com goiabada e queijo");
    }
    else if (number == 9)
    {
        adicionarItem(head, "pamonha e cafe com leite");
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
    insertPrato(number, threadArgs->head);
    return NULL;
}

void *thread_bancada_um(void *args)
{

}

void *thread_bancada_dois(void *args)
{
    
}

int main() {
    struct Node* head = NULL; 
    struct threadInserirPratoArg *args_inserir = malloc(sizeof(struct threadInserirPratoArg));
    args_inserir->head = head;
    int vitoria = 0;

    while (vitoria == 0)
    {
        pthread_t thread_gera_pedido;
        pthread_create(&thread_gera_pedido, NULL, thread_adicionar_prato, (void *)args_inserir);
        sleep(5);
    }

    return 0;
}
