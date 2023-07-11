#ifndef __COLUNAS__
#define __COLUNAS__

#include <iostream>
#include <string>
#include "listaDuplamenteEncadeada.hpp"

using namespace std;

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
    virtual string getNome() = 0;
    virtual string getDescricao() = 0;
    virtual void setNome(string n) = 0;
    virtual void setDescricao(string d) = 0;
    virtual void ordenar() = 0;
};

class ColunaNomeada : public Coluna
{
private:
    string nome;
    string descricao;

public:
    ColunaNomeada(string n, string d) : nome(n), descricao(d) {}

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
        cout << "Descricao: " << descricao << endl;
        cout << "Quantidade de tarefas: " << lista.getTamanho() << "\n\n";

        for (int i = 0; i < lista.getTamanho(); i++)
        {
            Tarefa* tarefa = lista.obterPorIndice(i);
            cout << "Indice da tarefa: " << i << "\n" << tarefa << endl;
        }
    }

    void ordenar()
    {
        lista.ordenarPorPrioridade();
    }

    string getNome() override
    {
        return nome;
    }

    string getDescricao()
    {
        return descricao;
    }

    void setNome(string n)
    {
        nome = n;
    }

    void setDescricao(string d)
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
    ColunaArquivo(string n, string d) : nome(n), descricao(d) {}
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

    string getNome() override
    {
        return nome;
    }

    string getDescricao()
    {
        return descricao;
    }

    void setNome(string n)
    {
        nome = n;
    }

    void setDescricao(string d)
    {
        descricao = d;
    }

    int getTamanho()
    {
        return lista.getTamanho();
    }

    void imprimir() const override
    {
        cout << "-+- Coluna Arquivo -+-" << endl;
        for (int i = 0; i < lista.getTamanho(); i++)
        {
            Tarefa* tarefa = lista.obterPorIndice(i);
            cout << tarefa->getTitulo() << endl;
        }
    }

    void ordenar(){
        return;
    }
};

#endif
