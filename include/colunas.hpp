/**
 * @file colunas.hpp
 * @brief Definição das classes Coluna e ColunaNomeada para um Gerenciador de Tarefas.
 * @author Franklin Oliveira
 */

#ifndef __COLUNAS__
#define __COLUNAS__

#include "tarefa.hpp"
#include "listaDuplamenteEncadeada.hpp"
#include <vector>
#include <string>

using std::string;
using std::ostream;

/**
 * @class Coluna
 * @brief Classe base abstrata que representa uma coluna em um Gerenciador de Tarefas.
 * @author Franklin Oliveira
 */
class Coluna {
protected:
    int quantidade; /**< Quantidade de tarefas na coluna. */
    ListaDuplamenteEncadeada<Tarefa*> lista; /**< Lista duplamente encadeada de ponteiros para tarefas. */

public:
    /**
     * @brief Construtor padrão da classe Coluna.
     */
    Coluna() {}

    /**
     * @brief Destrutor da classe Coluna.
     */
    ~Coluna() {}

    /**
     * @brief Define a quantidade de tarefas na coluna.
     * @param quantidade A quantidade de tarefas.
     */
    void setQuantidade(int quantidade) {}

    /**
     * @brief Obtém a quantidade de tarefas na coluna.
     * @return A quantidade de tarefas.
     */
    int getQuantidade() {}

    /**
     * @brief Adiciona uma tarefa à coluna.
     * @param t Ponteiro para a tarefa a ser adicionada.
     */
    void adicionarTarefa(Tarefa* t) {}

    /**
     * @brief Remove uma tarefa da coluna.
     * @param t Ponteiro para a tarefa a ser removida.
     */
    void removerTarefa(Tarefa* t) {}

    /**
     * @brief Imprime as tarefas da coluna.
     */
    virtual void imprimir() = 0;
};

/**
 * @class ColunaNomeada
 * @brief Classe que representa uma coluna nomeada em um Gerenciador de Tarefas.
 * @author Franklin Oliveira
 */
class ColunaNomeada : public Coluna {
private:
    string nome; /**< Nome da coluna. */

public:
    /**
     * @brief Construtor da classe ColunaNomeada.
     * @param nome O nome da coluna.
     */
    ColunaNomeada(const string& nome) : nome(nome) {}

    /**
     * @brief Destrutor da classe ColunaNomeada.
     */
    ~ColunaNomeada() {}

    /**
     * @brief Define o nome da coluna.
     * @param nome O nome da coluna.
     */
    void setNome(const string& nome) {}

    /**
     * @brief Obtém o nome da coluna.
     * @return O nome da coluna.
     */
    string getNome() {}

    /**
     * @brief Move uma tarefa para outra coluna.
     * @param t Ponteiro para a tarefa a ser movida.
     * @param colunaDestino Ponteiro para a coluna de destino.
     */
    void moverTarefa(Tarefa* t, Coluna* colunaDestino) {}

    /**
     * @brief Imprime as tarefas da coluna nomeada.
     */
    void imprimir() {}

    /**
     * @brief Sobrecarga do operador de inserção para imprimir a coluna nomeada.
     * @param os O stream de saída.
     * @param coluna A coluna nomeada a ser impressa.
     * @return O stream de saída atualizado.
     */
    friend ostream& operator<<(ostream& os, const ColunaNomeada& coluna);
};

#endif  // __COLUNAS__
