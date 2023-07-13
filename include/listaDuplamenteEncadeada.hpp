/**
 * @file listaDuplamenteEncadeada.hpp
 * @brief Define a classe ListaDupla e a classe No para implementar uma lista duplamente encadeada de tarefas de um quadro de tarefas.
 * @author Franklin Oliveira
 */

#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include "tarefa.hpp"

/**
 * @class No
 * @brief Classe que representa um nó de uma lista duplamente encadeada.
 */
class No
{
private:
    Tarefa *tarefa; ///< Ponteiro para a tarefa armazenada no nó.
    No *proximo;    ///< Ponteiro para o próximo nó.
    No *anterior;   ///< Ponteiro para o nó anterior.

public:
    /**
     * @brief Construtor da classe No.
     * @param t Ponteiro para a tarefa a ser armazenada no nó.
     */
    No(Tarefa *t) : tarefa(t), proximo(nullptr), anterior(nullptr) {}

    /**
     * @brief Obtém a tarefa armazenada no nó.
     * @return Ponteiro para a tarefa.
     */
    Tarefa *getTarefa() const
    {
        return tarefa;
    }

    /**
     * @brief Define a tarefa a ser armazenada no nó.
     * @param t Ponteiro para a tarefa.
     */
    void setTarefa(Tarefa *t)
    {
        tarefa = t;
    }

    /**
     * @brief Obtém o próximo nó.
     * @return Ponteiro para o próximo nó.
     */
    No *getProximo() const
    {
        return proximo;
    }

    /**
     * @brief Define o próximo nó.
     * @param p Ponteiro para o próximo nó.
     */
    void setProximo(No *p)
    {
        proximo = p;
    }

    /**
     * @brief Obtém o nó anterior.
     * @return Ponteiro para o nó anterior.
     */
    No *getAnterior() const
    {
        return anterior;
    }

    /**
     * @brief Define o nó anterior.
     * @param a Ponteiro para o nó anterior.
     */
    void setAnterior(No *a)
    {
        anterior = a;
    }
};

/**
 * @class ListaDupla
 * @brief Classe que implementa uma lista duplamente encadeada de tarefas de um quadro de tarefas.
 */
class ListaDupla
{
private:
    No *sentinelaInicio; ///< Ponteiro para o sentinela de início da lista.
    No *sentinelaFim;    ///< Ponteiro para o sentinela de fim da lista.
    int tamanho;         ///< Tamanho da lista.

public:
    /**
     * @brief Construtor padrão da classe ListaDupla.
     */
    ListaDupla() : tamanho(0)
    {
        sentinelaInicio = new No(nullptr);
        sentinelaFim = new No(nullptr);

        sentinelaInicio->setProximo(sentinelaFim);
        sentinelaFim->setAnterior(sentinelaInicio);
    }

    /**
     * @brief Destrutor da classe ListaDupla.
     */
    ~ListaDupla()
    {
        limpar();
        delete sentinelaInicio;
        delete sentinelaFim;
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
     * @brief Verifica se a lista está vazia.
     * @return true se a lista estiver vazia, false caso contrário.
     */
    bool vazia() const
    {
        return tamanho == 0;
    }

    /**
     * @brief Insere uma tarefa no início da lista.
     * @param t Ponteiro para a tarefa a ser inserida.
     */
    void inserirInicio(Tarefa *t)
    {
        No *novoNo = new No(t);

        novoNo->setProximo(sentinelaInicio->getProximo());
        novoNo->setAnterior(sentinelaInicio);

        sentinelaInicio->getProximo()->setAnterior(novoNo);
        sentinelaInicio->setProximo(novoNo);

        tamanho++;
    }

    /**
     * @brief Insere uma tarefa no fim da lista.
     * @param t Ponteiro para a tarefa a ser inserida.
     */
    void inserirFim(Tarefa *t)
    {
        No *novoNo = new No(t);

        novoNo->setProximo(sentinelaFim);
        novoNo->setAnterior(sentinelaFim->getAnterior());

        sentinelaFim->getAnterior()->setProximo(novoNo);
        sentinelaFim->setAnterior(novoNo);

        tamanho++;
    }

    /**
     * @brief Insere uma tarefa na lista pelo índice.
     * @param t Ponteiro para a tarefa a ser inserida.
     * @param indice Índice de inserção.
     */
    void inserirPorIndice(Tarefa *t, int indice)
    {
        if (indice < 0 || indice > tamanho)
        {
            throw std::out_of_range("Índice inválido");
        }

        if (indice == 0)
        {
            inserirInicio(t);
        }
        else if (indice == tamanho)
        {
            inserirFim(t);
        }
        else
        {
            No *novoNo = new No(t);
            No *atual = sentinelaInicio->getProximo();

            for (int i = 0; i < indice; i++)
            {
                atual = atual->getProximo();
            }

            novoNo->setProximo(atual);
            novoNo->setAnterior(atual->getAnterior());

            atual->getAnterior()->setProximo(novoNo);
            atual->setAnterior(novoNo);

            tamanho++;
        }
    }

    /**
     * @brief Remove a tarefa do início da lista.
     */
    void removerInicio()
    {
        if (vazia())
        {
            throw std::out_of_range("Lista vazia");
        }

        No *noRemovido = sentinelaInicio->getProximo();
        No *proximoNo = noRemovido->getProximo();

        sentinelaInicio->setProximo(proximoNo);
        proximoNo->setAnterior(sentinelaInicio);

        delete noRemovido->getTarefa();
        delete noRemovido;
        tamanho--;
    }

    /**
     * @brief Remove a tarefa do fim da lista.
     */
    void removerFim()
    {
        if (vazia())
        {
            throw std::out_of_range("Lista vazia");
        }

        No *noRemovido = sentinelaFim->getAnterior();
        No *anteriorNo = noRemovido->getAnterior();

        anteriorNo->setProximo(sentinelaFim);
        sentinelaFim->setAnterior(anteriorNo);

        delete noRemovido->getTarefa();
        delete noRemovido;
        tamanho--;
    }

    /**
     * @brief Remove a tarefa da lista pelo índice.
     * @param indice Índice da tarefa a ser removida.
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
        }
        else if (indice == tamanho - 1)
        {
            removerFim();
        }
        else
        {
            No *atual = sentinelaInicio->getProximo();

            for (int i = 0; i < indice; i++)
            {
                atual = atual->getProximo();
            }

            No *noRemovido = atual;
            No *proximoNo = atual->getProximo();
            No *anteriorNo = atual->getAnterior();

            anteriorNo->setProximo(proximoNo);
            proximoNo->setAnterior(anteriorNo);

            delete noRemovido->getTarefa();
            delete noRemovido;
            tamanho--;
        }
    }

    /**
     * @brief Remove a tarefa da lista, mas mantém o nó na lista sem referência à tarefa.
     * @param indice Índice da tarefa a ser removida.
     */
    void lightDelete(int indice)
    {
        if (indice < 0 || indice >= tamanho)
        {
            throw std::out_of_range("Índice inválido");
        }

        No *atual = sentinelaInicio->getProximo();

        for (int i = 0; i < indice; i++)
        {
            atual = atual->getProximo();
        }

        No *noRemovido = atual;
        No *proximoNo = atual->getProximo();
        No *anteriorNo = atual->getAnterior();

        anteriorNo->setProximo(proximoNo);
        proximoNo->setAnterior(anteriorNo);

        noRemovido->setProximo(nullptr);
        noRemovido->setAnterior(nullptr);

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
     * @brief Obtém a tarefa da lista pelo índice.
     * @param indice Índice da tarefa.
     * @return Ponteiro para a tarefa encontrada.
     */
    Tarefa *obterPorIndice(int indice) const
    {
        if (indice < 0 || indice >= tamanho)
        {
            throw std::out_of_range("Índice inválido");
        }

        No *atual = sentinelaInicio->getProximo();

        for (int i = 0; i < indice; i++)
        {
            atual = atual->getProximo();
        }

        return atual->getTarefa();
    }

    /**
     * @brief Ordena a lista de tarefas por prioridade.
     */
    void ordenarPorPrioridade()
    {
        if (tamanho <= 1)
        {
            return;
        }

        bool trocou;
        do
        {
            No *atual = sentinelaInicio->getProximo();
            No *anterior = sentinelaInicio;

            trocou = false;

            while (atual != sentinelaFim->getAnterior())
            {
                if (atual->getTarefa()->getPrioridade() > atual->getProximo()->getTarefa()->getPrioridade())
                {
                    No *proximo = atual->getProximo();
                    No *proximoDoProximo = proximo->getProximo();

                    anterior->setProximo(proximo);
                    proximo->setProximo(atual);
                    atual->setProximo(proximoDoProximo);

                    proximoDoProximo->setAnterior(atual);
                    atual->setAnterior(proximo);
                    proximo->setAnterior(anterior);

                    trocou = true;
                }
                else
                {
                    anterior = atual;
                    atual = atual->getProximo();
                }
            }
        } while (trocou);
    }
};

#endif