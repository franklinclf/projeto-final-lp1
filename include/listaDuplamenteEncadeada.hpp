#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include "tarefa.hpp"

class No
{
private:
    Tarefa *tarefa;
    No *proximo;
    No *anterior;

public:
    No(Tarefa *t) : tarefa(t), proximo(nullptr), anterior(nullptr) {}

    Tarefa *getTarefa() const
    {
        return tarefa;
    }

    void setTarefa(Tarefa *t)
    {
        tarefa = t;
    }

    No *getProximo() const
    {
        return proximo;
    }

    void setProximo(No *p)
    {
        proximo = p;
    }

    No *getAnterior() const
    {
        return anterior;
    }

    void setAnterior(No *a)
    {
        anterior = a;
    }
};

class ListaDupla
{
private:
    No *sentinelaInicio;
    No *sentinelaFim;
    int tamanho;

public:
    ListaDupla() : tamanho(0)
    {
        sentinelaInicio = new No(nullptr);
        sentinelaFim = new No(nullptr);

        sentinelaInicio->setProximo(sentinelaFim);
        sentinelaFim->setAnterior(sentinelaInicio);
    }

    ~ListaDupla()
    {
        limpar();
        delete sentinelaInicio;
        delete sentinelaFim;
    }

    int getTamanho() const
    {
        return tamanho;
    }

    bool vazia() const
    {
        return tamanho == 0;
    }

    void inserirInicio(Tarefa *t)
    {
        No *novoNo = new No(t);

        novoNo->setProximo(sentinelaInicio->getProximo());
        novoNo->setAnterior(sentinelaInicio);

        sentinelaInicio->getProximo()->setAnterior(novoNo);
        sentinelaInicio->setProximo(novoNo);

        tamanho++;
    }

    void inserirFim(Tarefa *t)
    {
        No *novoNo = new No(t);

        novoNo->setProximo(sentinelaFim);
        novoNo->setAnterior(sentinelaFim->getAnterior());

        sentinelaFim->getAnterior()->setProximo(novoNo);
        sentinelaFim->setAnterior(novoNo);

        tamanho++;
    }

    void inserirPorIndice(Tarefa *t, int indice)
    {
        if (indice < 0 || indice > tamanho)
        {
            throw std::out_of_range("Indice invalido");
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

    void removerPorIndice(int indice)
    {
        if (indice < 0 || indice >= tamanho)
        {
            throw std::out_of_range("Indice invalido");
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

    void lightDelete(int indice)
{
    if (indice < 0 || indice >= tamanho)
    {
        throw std::out_of_range("Indice invalido");
    }

    No* atual = sentinelaInicio->getProximo();

    for (int i = 0; i < indice; i++)
    {
        atual = atual->getProximo();
    }

    No* noRemovido = atual;
    No* proximoNo = atual->getProximo();
    No* anteriorNo = atual->getAnterior();

    anteriorNo->setProximo(proximoNo);
    proximoNo->setAnterior(anteriorNo);

    noRemovido->setProximo(nullptr);
    noRemovido->setAnterior(nullptr);

    tamanho--;
}

    void limpar()
    {
        while (!vazia())
        {
            removerInicio();
        }
    }

    Tarefa *obterPorIndice(int indice) const
    {
        if (indice < 0 || indice >= tamanho)
        {
            throw std::out_of_range("Indice invalido");
        }

        No *atual = sentinelaInicio->getProximo();

        for (int i = 0; i < indice; i++)
        {
            atual = atual->getProximo();
        }

        return atual->getTarefa();
    }

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