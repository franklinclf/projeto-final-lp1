/**
 * @file quadro.hpp
 * @brief Definição da classe Quadro para um Gerenciador de Tarefas com Método Kanban utilizando colunas nomeadas em um deque.
 * @autor Franklin Oliveira
 */

#ifndef __QUADRO__
#define __QUADRO__

#include <iostream>
#include <string>
#include "colunas.hpp"
#include "deque.hpp"

/**
 * @class Quadro
 * @brief Classe que representa um quadro para um Gerenciador de Tarefas com Método Kanban utilizando colunas nomeadas em um deque.
 * @autor Franklin Oliveira
 */
class Quadro {
private:
    string titulo; /**< Título do quadro. */
    Deque<ColunaNomeada*> quadro; /**< Deque de colunas nomeadas. */

public:
    /**
     * @brief Construtor da classe Quadro.
     * @param titulo O título do quadro.
     */
    Quadro(const string& titulo) : titulo(titulo) {}

    /**
     * @brief Destrutor da classe Quadro.
     */
    ~Quadro() {}

    /**
     * @brief Define o título do quadro.
     * @param titulo O título do quadro.
     */
    void setTitulo(const string& titulo) {}

    /**
     * @brief Obtém o título do quadro.
     * @return O título do quadro.
     */
    string getTitulo() {}

    /**
     * @brief Adiciona uma coluna ao quadro.
     * @param coluna A coluna nomeada a ser adicionada.
     */
    void adicionarColuna(const ColunaNomeada& coluna) {}

    /**
     * @brief Remove uma coluna do quadro.
     * @param nome O nome da coluna a ser removida.
     */
    void removerColuna(const string& nome) {}

    /**
     * @brief Imprime o quadro, mostrando todas as colunas e suas tarefas.
     */
    void imprimirQuadro() {}

    /**
     * @brief Sobrecarga do operador de inserção para imprimir o quadro.
     * @param os O stream de saída.
     * @param quadro O quadro a ser impresso.
     * @return O stream de saída atualizado.
     */
    friend ostream& operator<<(ostream& os, const Quadro& quadro);
};

#endif  // __QUADRO__