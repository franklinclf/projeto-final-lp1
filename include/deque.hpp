/**
 * @file deque.hpp
 * @brief Este arquivo contém a definição da classe Deque, que implementa um deque usando uma lista duplamente encadeada com sentinelas.
 * @author Franklin Oliveira
 */

#ifndef __DEQUE__
#define __DEQUE__

#include <iostream>

/**
 * @brief Classe para representar um deque.
 *
 * @tparam T O tipo dos elementos do deque.
 */
template <typename T>
class Deque
{
private:
    /**
     * @brief Estrutura interna que representa um nó do deque.
     */
    struct Node
    {
        T data; /**< O dado armazenado no nó. */
        Node *anterior; /**< O ponteiro para o nó anterior. */
        Node *proximo; /**< O ponteiro para o nó seguinte. */
    };

    Node *cabeca; /**< O ponteiro para o nó cabeça (sentinela inicial). */
    Node *cauda; /**< O ponteiro para o nó cauda (sentinela final). */
    int tamanho; /**< O tamanho atual do deque. */

public:
    /**
     * @brief Construtor da classe Deque.
     *        Inicializa o deque com nós sentinelas vazios.
     */
    Deque()
    {
        cabeca = new Node();
        cauda = new Node();
        cabeca->proximo = cauda;
        cauda->anterior = cabeca;
        tamanho = 0;
    }

    /**
     * @brief Destrutor da classe Deque.
     *        Libera a memória ocupada pelos nós do deque.
     */
    ~Deque()
    {
        clear();
        delete cabeca;
        delete cauda;
    }

    /**
     * @brief Obtém o tamanho atual do deque.
     *
     * @return O tamanho do deque.
     */
    int getTamanho() const
    {
        return tamanho;
    }

    /**
     * @brief Verifica se o deque está vazio.
     *
     * @return true se o deque está vazio, false caso contrário.
     */
    bool isEmpty() const
    {
        return tamanho == 0;
    }

    /**
     * @brief Remove todos os elementos do deque.
     */
    void clear()
    {
        while (!isEmpty())
        {
            removeFront();
        }
    }

    /**
     * @brief Insere um elemento no início do deque.
     *
     * @param value O valor do elemento a ser inserido.
     */
    void insertFront(const T &value)
    {
        Node *novoNode = new Node();
        novoNode->data = value;

        novoNode->proximo = cabeca->proximo;
        novoNode->anterior = cabeca;
        cabeca->proximo->anterior = novoNode;
        cabeca->proximo = novoNode;

        tamanho++;
    }

    /**
     * @brief Insere um elemento no final do deque.
     *
     * @param value O valor do elemento a ser inserido.
     */
    void insertBack(const T &value)
    {
        Node *novoNode = new Node();
        novoNode->data = value;

        novoNode->proximo = cauda;
        novoNode->anterior = cauda->anterior;
        cauda->anterior->proximo = novoNode;
        cauda->anterior = novoNode;

        tamanho++;
    }

    /**
     * @brief Remove o elemento do início do deque.
     *        Se o deque estiver vazio, nenhum elemento será removido.
     */
    void removeFront()
    {
        if (!isEmpty())
        {
            Node *nodeToRemove = cabeca->proximo;
            cabeca->proximo = nodeToRemove->proximo;
            nodeToRemove->proximo->anterior = cabeca;

            delete nodeToRemove;
            tamanho--;
        }
    }

    /**
     * @brief Remove o elemento do final do deque.
     *        Se o deque estiver vazio, nenhum elemento será removido.
     */
    void removeBack()
    {
        if (!isEmpty())
        {
            Node *nodeToRemove = cauda->anterior;
            cauda->anterior = nodeToRemove->anterior;
            nodeToRemove->anterior->proximo = cauda;

            delete nodeToRemove;
            tamanho--;
        }
    }

    /**
     * @brief Imprime os elementos do deque.
     */
    void printDeque() const
    {
        Node *current = cabeca->proximo;
        while (current != cauda)
        {
            std::cout << current->data << " ";
            current = current->proximo;
        }
        std::cout << std::endl;
    }
};

#endif