/**
 * @file pessoa.hpp
 * @brief Definição das classes Pessoa e Colaborador
 * @author Franklin Oliveira
 */

#ifndef __PESSOA__
#define __PESSOA__

#include <iostream>
#include <string>

using std::cout;
using std::ostream;
using std::string;

/**
 * @brief Classe base que representa uma Pessoa.
 */
class Pessoa
{
protected:
    string nome;    /**< Nome da pessoa */
    string contato; /**< Informações de contato da pessoa */

public:
    /**
     * @brief Construtor padrão da classe Pessoa.
     */
    Pessoa() {}

    /**
     * @brief Construtor da classe Pessoa.
     * @param n Nome da pessoa.
     * @param c Informações de contato da pessoa.
     */
    Pessoa(string n, string c) : nome(n), contato(c) {}

    /**
     * @brief Destrutor da classe Pessoa.
     */
    ~Pessoa() {}

    /**
     * @brief Define o nome da pessoa.
     * @param n Nome da pessoa.
     */
    void setNome(string n)
    {
        nome = n;
    }

    /**
     * @brief Define as informações de contato da pessoa.
     * @param c Informações de contato da pessoa.
     */
    void setContato(string c)
    {
        contato = c;
    }

    /**
     * @brief Obtém o nome da pessoa.
     * @return Nome da pessoa.
     */
    string getNome()
    {
        return nome;
    }

    /**
     * @brief Obtém as informações de contato da pessoa.
     * @return Informações de contato da pessoa.
     */
    string getContato()
    {
        return contato;
    }
};

/**
 * @brief Classe que representa um Colaborador, derivada da classe Pessoa.
 */
class Colaborador : public Pessoa
{
private:
    string funcao;             /**< Função do colaborador */
    int tarefasAtribuidas;     /**< Número de tarefas atribuídas ao colaborador */
    int idUnico;               /**< ID único do colaborador */
    static int contador;       /**< Contador para atribuição de ID único */

public:
    /**
     * @brief Construtor padrão da classe Colaborador.
     */
    Colaborador()
    {
        idUnico = ++contador;
    }

    /**
     * @brief Construtor da classe Colaborador.
     * @param n Nome do colaborador.
     * @param c Informações de contato do colaborador.
     * @param f Função do colaborador.
     */
    Colaborador(string n, string c, string f) : Pessoa(n, c), funcao(f)
    {
        idUnico = ++contador;
    }

    /**
     * @brief Destrutor da classe Colaborador.
     */
    ~Colaborador() {}

    /**
     * @brief Define a função do colaborador.
     * @param f Função do colaborador.
     */
    void setFuncao(string f)
    {
        funcao = f;
    }

    /**
     * @brief Define o número de tarefas atribuídas ao colaborador.
     * @param t Número de tarefas atribuídas ao colaborador.
     */
    void setTarefasAtribuidas(int t)
    {
        tarefasAtribuidas = t;
    }

    /**
     * @brief Obtém a função do colaborador.
     * @return Função do colaborador.
     */
    string getFuncao()
    {
        return funcao;
    }

    /**
     * @brief Obtém o número de tarefas atribuídas ao colaborador.
     * @return Número de tarefas atribuídas ao colaborador.
     */
    int getTarefasAtribuidas()
    {
        return tarefasAtribuidas;
    }

    /**
     * @brief Obtém o ID único do colaborador.
     * @return ID único do colaborador.
     */
    int getID()
    {
        return idUnico;
    }

    /**
     * @brief Sobrecarga do operador de pré-incremento (++colaborador).
     * Incrementa o número de tarefas atribuídas ao colaborador em 1.
     * @param colaborador Referência para o colaborador a ser incrementado.
     * @return Referência para o colaborador após o incremento.
     */
    friend Colaborador &operator++(Colaborador &colaborador)
    {
        colaborador.tarefasAtribuidas++;
        return colaborador;
    }

    /**
     * @brief Sobrecarga do operador de saída (<<) para imprimir as informações do colaborador.
     * @param out Fluxo de saída.
     * @param colaborador Ponteiro para o colaborador a ser impresso.
     * @return Fluxo de saída atualizado.
     */
    friend ostream &operator<<(std::ostream &out, Colaborador *&colaborador)
    {
        out << "ID: " << colaborador->idUnico << "\n";
        out << "Nome: " << colaborador->nome << "\n";
        out << "Contato: " << colaborador->contato << "\n";
        out << "Funcao: " << colaborador->funcao << "\n";
        out << "Tarefas atribuidas: " << colaborador->tarefasAtribuidas << "\n";

        return out;
    }
};

#endif