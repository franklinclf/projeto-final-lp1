/**
 * @file tarefa.hpp
 * @brief Este arquivo contém as definições das classes Data e Tarefa.
 *        A classe Data representa uma data com dia, mês e ano.
 *        A classe Tarefa representa uma tarefa com título, descrição, prioridade e prazo.
 *        O código define métodos para configurar e obter informações relacionadas às tarefas.
 * @author Franklin Oliveira
 */

#ifndef __TASK__
#define __TASK__

#include <string>
using std::string;
using std::ostream;

/**
 * @brief Classe para representar uma data com dia, mês e ano.
 */
class Data
{
private:
    int dia; /**< O dia da data. */
    int mes; /**< O mês da data. */
    int ano; /**< O ano da data. */

public:
    /**
     * @brief Construtor da classe Data.
     *
     * @param d O dia da data.
     * @param m O mês da data.
     * @param a O ano da data.
     */
    Data(int d, int m, int a) : dia(d), mes(m), ano(a) {}

    /**
     * @brief Destrutor da classe Data.
     */
    ~Data(){}

    /**
     * @brief Define o dia da data.
     *
     * @param d O novo valor para o dia.
     */
    void setDia(int d) {}

    /**
     * @brief Define o mês da data.
     *
     * @param m O novo valor para o mês.
     */
    void setMes(int m) {}

    /**
     * @brief Define o ano da data.
     *
     * @param a O novo valor para o ano.
     */
    void setAno(int a) {}

    /**
     * @brief Obtém o dia da data.
     *
     * @return O dia da data.
     */
    int getDia() {}

    /**
     * @brief Obtém o mês da data.
     *
     * @return O mês da data.
     */
    int getMes() {}

    /**
     * @brief Obtém o ano da data.
     *
     * @return O ano da data.
     */
    int getAno() {}

    /**
     * @brief Obtém a representação da data como uma string.
     *
     * @return A data formatada como string.
     */
    string getData() {}
};

/**
 * @brief Classe para representar uma tarefa com título, descrição, prioridade e prazo.
 */
class Tarefa
{
protected:
    string titulo;      /**< O título da tarefa. */
    string descricao;   /**< A descrição da tarefa. */
    int prioridade;     /**< A prioridade da tarefa. */
    Data *prazo;        /**< O prazo da tarefa. */

public:
    /**
     * @brief Construtor da classe Tarefa.
     *
     * @param t O título da tarefa.
     * @param d A descrição da tarefa.
     * @param p A prioridade da tarefa.
     * @param dia O dia do prazo da tarefa.
     * @param mes O mês do prazo da tarefa.
     * @param ano O ano do prazo da tarefa.
     */
    Tarefa(string t, string d, int p, int dia, int mes, int ano) : titulo(t), descricao(d), prioridade(p), prazo(new Data(dia, mes, ano)) {}

    /**
     * @brief Destrutor da classe Tarefa.
     */
    ~Tarefa() {}

    /**
     * @brief Define o título da tarefa.
     *
     * @param t O novo valor para o título.
     */
    void setTitulo(string t) {}

    /**
     * @brief Define a descrição da tarefa.
     *
     * @param d O novo valor para a descrição.
     */
    void setDescricao(string d) {}

    /**
     * @brief Define a prioridade da tarefa.
     *
     * @param p O novo valor para a prioridade.
     */
    void setPrioridade(int p) {}

    /**
     * @brief Define o prazo da tarefa.
     *
     * @param d O novo dia do prazo.
     * @param m O novo mês do prazo.
     * @param a O novo ano do prazo.
     */
    void setPrazo(int d, int m, int a) {}

    /**
     * @brief Obtém o título da tarefa.
     *
     * @return O título da tarefa.
     */
    string getTitulo() {}

    /**
     * @brief Obtém a descrição da tarefa.
     *
     * @return A descrição da tarefa.
     */
    string getDescricao() {}

    /**
     * @brief Obtém a prioridade da tarefa.
     *
     * @return A prioridade da tarefa.
     */
    int getPrioridade() {}

    /**
     * @brief Obtém o prazo da tarefa como uma string formatada.
     *
     * @return O prazo da tarefa como uma string.
     */
    string getData() {}

    /**
     * @brief Imprime as informações da tarefa.
     */
    void imprimir() {}

    /**
     * @brief Faz a sobrecarga do operador "<<" para imprimir uma tarefa;
     */
    friend ostream& operator<<(ostream& os, const Tarefa& tarefa) {}
};

#endif