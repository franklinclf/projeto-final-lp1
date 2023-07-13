/**
 * @file listaSimplesmenteEncadeada.hpp
 * @brief Define a classe Lista e a classe NoSimples para implementar uma lista simplesmente encadeada de colunas de um quadro de tarefas.
 * @author Franklin Oliveira
 */

#ifndef __LISTASE__
#define __LISTASE__
#include <iostream>
#include "colunas.hpp"

/**
 * @class NoSimples
 * @brief Classe que representa um nó de uma lista simplesmente encadeada.
 */
class NoSimples
{
public:
    Coluna *coluna;     ///< Ponteiro para a coluna armazenada no nó.
    NoSimples *proximo; ///< Ponteiro para o próximo nó.

    /**
     * @brief Construtor da classe NoSimples.
     * @param c Ponteiro para a coluna a ser armazenada no nó.
     */
    NoSimples(Coluna *c) : coluna(c), proximo(nullptr) {}
};

/**
 * @class Lista
 * @brief Classe que implementa uma lista simplesmente encadeada de colunas de um quadro de tarefas.
 */
class Lista
{
private:
    NoSimples *inicio; ///< Ponteiro para o primeiro nó da lista.
    int tamanho;       ///< Tamanho da lista.

public:
    /**
     * @brief Construtor da classe Lista.
     */
    Lista() : inicio(nullptr), tamanho(0) {}

    /**
     * @brief Destrutor da classe Lista.
     */
    ~Lista()
    {
        limpar();
    }

    /**
     * @brief Verifica se a lista está vazia.
     * @return true se a lista estiver vazia, false caso contrário.
     */
    bool vazia() const
    {
        return tamanho == 0;
    }

    /**
     * @brief Obtém o tamanho da lista.
     * @return Tamanho da lista.
     */
    int getTamanho() const
    {
        return tamanho;
    }

    /**
     * @brief Insere uma coluna no início da lista.
     * @param coluna Ponteiro para a coluna a ser inserida.
     */
    void inserirInicio(Coluna *coluna)
    {
        NoSimples *novoNo = new NoSimples(coluna);
        novoNo->proximo = inicio;
        inicio = novoNo;
        tamanho++;
    }

    /**
     * @brief Remove a coluna do início da lista.
     */
    void removerInicio()
    {
        if (vazia())
        {
            throw std::out_of_range("Lista vazia");
        }

        NoSimples *noRemovido = inicio;
        inicio = inicio->proximo;
        delete noRemovido->coluna;
        delete noRemovido;
        tamanho--;
    }

    /**
     * @brief Remove a coluna da lista pelo índice.
     * @param indice Índice da coluna a ser removida.
     */
    void removerPorIndice(int indice)
    {
        if (indice < 0 || indice >= tamanho)
        {
            throw std::out_of_range("Índice inválido");
        }

        if (indice == 0)
        {
            removerInicio();
            return;
        }

        NoSimples *anterior = inicio;
        NoSimples *atual = inicio->proximo;
        for (int i = 1; i < indice; i++)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        anterior->proximo = atual->proximo;
        delete atual->coluna;
        delete atual;
        tamanho--;
    }

    /**
     * @brief Remove todos os nós da lista e libera a memória.
     */
    void limpar()
    {
        while (!vazia())
        {
            removerInicio();
        }
    }

    /**
     * @brief Obtém a coluna da lista pelo índice.
     * @param indice Índice da coluna.
     * @return Ponteiro para a coluna encontrada.
     */
    Coluna *obterPorIndice(int indice) const
    {
        if (indice < 0 || indice >= tamanho)
        {
            throw std::out_of_range("Índice inválido");
        }

        NoSimples *atual = inicio;
        for (int i = 0; i < indice; i++)
        {
            atual = atual->proximo;
        }

        return atual->coluna;
    }

    /**
     * @brief Move uma coluna da lista de uma posição para outra.
     * @param indiceAntigo Índice atual da coluna.
     * @param indiceNovo Novo índice da coluna.
     */
    void moverColuna(int indiceAntigo, int indiceNovo)
    {
        NoSimples *noA = inicio;
        NoSimples *noB = inicio;
        for (int i = 0; i < indiceAntigo; i++)
        {
            noA = noA->proximo;
        }
        for (int i = 0; i < indiceNovo; i++)
        {
            noB = noB->proximo;
        }

        Coluna *temp = noA->coluna;
        noA->coluna = noB->coluna;
        noB->coluna = temp;
    }
};

#endif