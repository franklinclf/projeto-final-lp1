#include <iostream>
#include <string>
#include "../include/quadro.hpp"

/**
     * @brief O algoritmo Selection Sort divide a lista em duas partes: uma parte ordenada e uma parte não ordenada. A cada iteração, ele encontra o elemento mínimo na parte não ordenada e o coloca na posição correta na parte ordenada. Esse processo é repetido até que toda a lista esteja ordenada. Sua complexidade de tempo também é O(n^2) no pior caso. Assim como o Bubble Sort, o Selection Sort é simples de implementar, mas pode ser ineficiente para grandes conjuntos de dados.
     */
template <typename T>
void ListaDuplamenteEncadeada<T>::selectionSortPorPrioridade()
{
    if (tamanho <= 1)
        return;

    Node *atual = cabeca->proximo;
    while (atual != cauda)
    {
        Node *minimo = atual;
        Node *prox = atual->proximo;

        while (prox != cauda)
        {
            if (prox->data.getPrioridade() < minimo->data.getPrioridade())
                minimo = prox;

            prox = prox->proximo;
        }

        if (minimo != atual)
        {
            // Remover minimo da posição atual
            minimo->anterior->proximo = minimo->proximo;
            minimo->proximo->anterior = minimo->anterior;

            // Inserir minimo antes do nó atual
            minimo->anterior = atual->anterior;
            minimo->proximo = atual;
            atual->anterior->proximo = minimo;
            atual->anterior = minimo;
        }

        atual = atual->proximo;
    }
}

/**
     * @brief O algoritmo Bubble Sort é um método de ordenação simples que percorre repetidamente a lista, comparando pares de elementos adjacentes e trocando-os se estiverem fora de ordem. Ele continua esse processo até que toda a lista esteja ordenada. Sua complexidade de tempo é O(n^2) no pior caso, onde n é o número de elementos na lista. O Bubble Sort é fácil de implementar, mas pode ser ineficiente para grandes conjuntos de dados devido ao seu desempenho quadrático.
     */
template <typename T>
void ListaDuplamenteEncadeada<T>::bubbleSortPorPrioridade()
{
    if (tamanho <= 1)
        return;

    bool trocou;
    Node *fim = cauda->anterior;

    do
    {
        trocou = false;
        Node *atual = cabeca->proximo;

        while (atual != fim)
        {
            Node *proximo = atual->proximo;

            if (atual->data.getPrioridade() > proximo->data.getPrioridade())
            {
                // Trocar os nós
                atual->proximo = proximo->proximo;
                proximo->proximo->anterior = atual;
                proximo->anterior = atual->anterior;
                proximo->proximo = atual;
                atual->anterior->proximo = proximo;
                atual->anterior = proximo;

                trocou = true;
            }

            atual = proximo;
        }

        fim = fim->anterior;
    } while (trocou);
}



int main(){
    Quadro kanban("Quadro de Gerenciamento de Projetos");

    ColunaNomeada *backlog = new ColunaNomeada("Backlog");
    ColunaNomeada *analise = new ColunaNomeada("Em Analise");
    ColunaNomeada *fazendo = new ColunaNomeada("Fazendo");
    ColunaNomeada *testando = new ColunaNomeada("Testando");
    ColunaNomeada *piloto = new ColunaNomeada("Em Piloto");
    ColunaNomeada *entregue = new ColunaNomeada("Entregue");

    kanban.adicionarColuna(backlog);
    kanban.adicionarColuna(analise);
    kanban.adicionarColuna(fazendo);
    kanban.adicionarColuna(testando);
    kanban.adicionarColuna(piloto);
    kanban.adicionarColuna(entregue);

    return 0;
}