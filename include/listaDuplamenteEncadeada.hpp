/**
 * @file listaDuplamenteEncadeada.hpp
 * @brief Este arquivo contém a definição da classe ListaDuplamenteEncadeada.
 *        A classe ListaDuplamenteEncadeada é uma lista duplamente encadeada com nós sentinelas.
 *        Ela permite a inserção, remoção e impressão dos elementos.
 * @author Franklin Oliveira
 */

#ifndef __LISTA__
#define __LISTA__

/**
 * @brief Classe para representar uma lista duplamente encadeada com nós sentinelas.
 *
 * @tparam T O tipo dos elementos da lista.
 */
template <typename T>
class ListaDuplamenteEncadeada
{
private:
    /**
     * @brief Estrutura interna que representa um nó da lista.
     */
    struct Node
    {
        T data; /**< O dado armazenado no nó. */
        Node *anterior; /**< O ponteiro para o nó anterior. */
        Node *proximo; /**< O ponteiro para o nó seguinte. */
    };

    Node *cabeca; /**< O ponteiro para o nó cabeça (sentinela inicial). */
    Node *cauda; /**< O ponteiro para o nó cauda (sentinela final). */
    int tamanho; /**< O tamanho atual da lista. */

public:
    /**
     * @brief Construtor da classe ListaDuplamenteEncadeada.
     *        Inicializa a lista com nós sentinelas vazios.
     */
    ListaDuplamenteEncadeada()
    {
        cabeca = new Node();
        cauda = new Node();
        cabeca->proximo = cauda;
        cauda->anterior = cabeca;
        tamanho = 0;
    }

    /**
     * @brief Destrutor da classe ListaDuplamenteEncadeada.
     *        Libera a memória ocupada pelos nós da lista.
     */
    ~ListaDuplamenteEncadeada()
    {
        clear();
        delete cabeca;
        delete cauda;
    }

    /**
     * @brief Obtém o tamanho atual da lista.
     *
     * @return O tamanho da lista.
     */
    int getTamanho() const
    {
        return tamanho;
    }

    /**
     * @brief Verifica se a lista está vazia.
     *
     * @return true se a lista está vazia, false caso contrário.
     */
    bool isEmpty() const
    {
        return tamanho == 0;
    }

    /**
     * @brief Remove todos os elementos da lista.
     */
    void clear()
    {
        while (!isEmpty())
        {
            removeFront();
        }
    }

    /**
     * @brief Insere um elemento no início da lista.
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
     * @brief Insere um elemento no final da lista.
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
     * @brief Remove o elemento do início da lista.
     *        Se a lista estiver vazia, nenhum elemento será removido.
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
     * @brief Remove o elemento do final da lista.
     *        Se a lista estiver vazia, nenhum elemento será removido.
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
     * @brief Imprime os elementos da lista.
     */
    void printList() const
    {
        Node *current = cabeca->proximo;
        while (current != cauda)
        {
            std::cout << *(current->data) << " ";
            current = current->proximo;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Ordena os nos pela prioridade do conteudo usando selection sort.
     */
    void selectionSortPorPrioridade() {}

    /**
     * @brief Ordena os nos pela prioridade do conteudo usando bubble sort.
     */
    void bubbleSortPorPrioridade() {}
};

#endif