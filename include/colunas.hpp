/**
 * @file colunas.hpp
 * @brief Definição das classes Coluna, ColunaNomeada e ColunaArquivo
 * @author Franklin Oliveira
 */

#ifndef COLUNAS_HPP
#define COLUNAS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "listaDuplamenteEncadeada.hpp"

using namespace std;

/**
 * @brief Classe abstrata que representa uma coluna de um quadro de tarefas.
 */
class Coluna
{
protected:
    ListaDupla lista;

public:
    virtual ~Coluna() {}

    /**
     * @brief Insere uma tarefa na coluna.
     * @param t Ponteiro para a tarefa a ser inserida.
     */
    virtual void inserirTarefa(Tarefa *t) = 0;

    /**
     * @brief Remove uma tarefa da coluna.
     * @param indice Índice da tarefa a ser removida.
     */
    virtual void removerTarefa(int indice) = 0;

    /**
     * @brief Imprime as informações da coluna.
     */
    virtual void imprimir() const = 0;

    /**
     * @brief Move uma tarefa de uma coluna para outra.
     * @param indice Índice da tarefa a ser movida.
     * @param colunaDestino Ponteiro para a coluna de destino.
     */
    virtual void moverTarefa(int indice, Coluna *colunaDestino) = 0;

    /**
     * @brief Obtém uma tarefa da coluna pelo seu índice.
     * @param indice Índice da tarefa desejada.
     * @return Ponteiro para a tarefa encontrada.
     */
    virtual Tarefa *obterTarefa(int indice) = 0;

    /**
     * @brief Obtém o tamanho da coluna, ou seja, a quantidade de tarefas nela contidas.
     * @return Tamanho da coluna.
     */
    virtual int getTamanho() = 0;

    /**
     * @brief Obtém o nome da coluna.
     * @return Nome da coluna.
     */
    virtual string getNome() = 0;

    /**
     * @brief Obtém a descrição da coluna.
     * @return Descrição da coluna.
     */
    virtual string getDescricao() = 0;

    /**
     * @brief Define o nome da coluna.
     * @param n Nome da coluna.
     */
    virtual void setNome(string n) = 0;

    /**
     * @brief Define a descrição da coluna.
     * @param d Descrição da coluna.
     */
    virtual void setDescricao(string d) = 0;

    /**
     * @brief Ordena as tarefas da coluna por prioridade.
     */
    virtual void ordenar() = 0;
};

/**
 * @brief Classe que representa uma coluna nomeada de um quadro de tarefas.
 */
class ColunaNomeada : public Coluna
{
private:
    string nome;
    string descricao;

public:
    /**
     * @brief Construtor da classe ColunaNomeada.
     * @param n Nome da coluna.
     * @param d Descrição da coluna.
     */
    ColunaNomeada(string n, string d) : nome(n), descricao(d) {}

    void inserirTarefa(Tarefa *t) override
    {
        lista.inserirFim(t);
    }

    void removerTarefa(int indice) override
    {
        lista.removerPorIndice(indice);
    }

    Tarefa *obterTarefa(int indice) override
    {
        return lista.obterPorIndice(indice);
    }

    void moverTarefa(int indice, Coluna *colunaDestino) override
    {
        Tarefa *tarefa = lista.obterPorIndice(indice);
        colunaDestino->inserirTarefa(tarefa);
        lista.lightDelete(indice);
    }

    void imprimir() const override
    {
        cout << "Descricao: " << descricao << endl;
        cout << "Quantidade de tarefas: " << lista.getTamanho() << "\n\n";

        for (int i = 0; i < lista.getTamanho(); i++)
        {
            Tarefa *tarefa = lista.obterPorIndice(i);
            cout << "Indice da tarefa: " << i << "\n"
                 << tarefa << endl;
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

/**
 * @brief Classe que representa uma coluna de um quadro de tarefas do tipo "Arquivo".
 */
class ColunaArquivo : public Coluna
{
private:
    string nome;
    string descricao;

public:
    ColunaArquivo() {}
    
    /**
     * @brief Construtor da classe ColunaArquivo.
     * @param n Nome da coluna.
     * @param d Descrição da coluna.
     */
    ColunaArquivo(string n, string d) : nome(n), descricao(d) {}
    ~ColunaArquivo() {}

    void inserirTarefa(Tarefa *t) override
    {
        lista.inserirFim(t);
    }

    void removerTarefa(int indice) override
    {
        lista.removerPorIndice(indice);
    }

    Tarefa *obterTarefa(int indice) override
    {
        return lista.obterPorIndice(indice);
    }

    void moverTarefa(int indice, Coluna *colunaDestino) override
    {
        Tarefa *tarefa = lista.obterPorIndice(indice);
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
            Tarefa *tarefa = lista.obterPorIndice(i);
            cout << i << ". " << tarefa->getTitulo() << endl;
        }
    }

    void ordenar()
    {
        lista.ordenarPorPrioridade();
    }
};

#endif
