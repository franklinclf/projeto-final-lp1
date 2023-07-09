#ifndef __COLUNAS__
#define __COLUNAS__

#include <iostream>
#include <string>
#include "listaDuplamenteEncadeada.hpp"

class Coluna
{
protected:
    ListaDupla lista;

public:
    virtual ~Coluna() {}

    virtual void inserirTarefa(Tarefa* t) = 0;
    virtual void removerTarefa(int indice) = 0;
    virtual void imprimir() const = 0;
    virtual void moverTarefa(int indice, Coluna* colunaDestino) = 0;

    virtual Tarefa* obterTarefa(int indice) = 0;
    virtual int getTamanho() = 0;
    virtual std::string getNome() = 0;
    virtual std::string getDescricao() = 0;
    virtual void setNome(std::string n) = 0;
    virtual void setDescricao(std::string d) = 0;
};

class ColunaNomeada : public Coluna
{
private:
    std::string nome;
    std::string descricao;

public:
    ColunaNomeada(std::string n, std::string d) : nome(n), descricao(d) {}

    void inserirTarefa(Tarefa* t) override
    {
        lista.inserirFim(t);
    }

    void removerTarefa(int indice) override
    {
        lista.removerPorIndice(indice);
    }

    Tarefa* obterTarefa(int indice)
    {
        return lista.obterPorIndice(indice);
    }

    void moverTarefa(int indice, Coluna* colunaDestino) override
    {
        Tarefa* tarefa = lista.obterPorIndice(indice);
        colunaDestino->inserirTarefa(tarefa);
        lista.lightDelete(indice);
    }

    void imprimir() const override
    {
        std::cout << "Descricao: " << descricao << std::endl;
        std::cout << "Quantidade de tarefas: " << lista.getTamanho() << "\n\n";

        for (int i = 0; i < lista.getTamanho(); i++)
        {
            Tarefa* tarefa = lista.obterPorIndice(i);
            std::cout << "Indice da tarefa: " << i << "\n" << tarefa << std::endl;
        }
    }

    void ordenar()
    {
        lista.ordenarPorPrioridade();
    }

    std::string getNome() override
    {
        return nome;
    }

    std::string getDescricao()
    {
        return descricao;
    }

    void setNome(std::string n)
    {
        nome = n;
    }

    void setDescricao(std::string d)
    {
        descricao = d;
    }

    int getTamanho()
    {
        return lista.getTamanho();
    }
};

class ColunaArquivo : public Coluna
{
    private:
    string nome;
    string descricao;
public:

    ColunaArquivo() {}
    ColunaArquivo(std::string n, std::string d) : nome(n), descricao(d) {}
    ~ColunaArquivo() {}

    void inserirTarefa(Tarefa* t) override
    {
        lista.inserirFim(t);
    }

    void removerTarefa(int indice) override
    {
        lista.removerPorIndice(indice);
    }

    Tarefa* obterTarefa(int indice) override
    {
        return lista.obterPorIndice(indice);
    }

    void moverTarefa(int indice, Coluna* colunaDestino) override
    {
        Tarefa* tarefa = lista.obterPorIndice(indice);
        colunaDestino->inserirTarefa(tarefa);
        lista.lightDelete(indice);
    }

    std::string getNome() override
    {
        return nome;
    }

    std::string getDescricao()
    {
        return descricao;
    }

    void setNome(std::string n)
    {
        nome = n;
    }

    void setDescricao(std::string d)
    {
        descricao = d;
    }

    int getTamanho()
    {
        return lista.getTamanho();
    }

    void imprimir() const override
    {
        for (int i = 0; i < lista.getTamanho(); i++)
        {
            Tarefa* tarefa = lista.obterPorIndice(i);
            std::cout << tarefa->getTitulo() << std::endl;
        }
    }
};

#endif
