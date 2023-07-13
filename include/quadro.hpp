/**
 * @file quadro.hpp
 * @brief Define a classe Quadro para representar um quadro de tarefas.
 * @author Franklin Oliveira
 */

#ifndef __QUADRO__
#define __QUADRO__

#include <iostream>
#include <string>
#include <set>
#include "colunas.hpp"
#include "listaSimplesmenteEncadeada.hpp"

/**
 * @struct comparador
 * @brief Estrutura de comparação para ordenar os colaboradores por ID.
 */
struct comparador
{
    /**
     * @brief Operador de comparação para ordenar os colaboradores por ID.
     * @param c1 Primeiro colaborador a ser comparado.
     * @param c2 Segundo colaborador a ser comparado.
     * @return true se o ID do primeiro colaborador é menor que o do segundo, false caso contrário.
     */
    bool operator()(Colaborador *c1, Colaborador *c2) const
    {
        return c1->getID() < c2->getID();
    }
};

/**
 * @class Quadro
 * @brief Classe que representa um quadro de tarefas.
 */
class Quadro
{
private:
    std::string nome;                 ///< Nome do quadro.
    std::string descricao;            ///< Descrição do quadro.
    Lista listaColunas;               ///< Lista de colunas do quadro.
    std::set<Colaborador *, comparador> equipe;   ///< Equipe de colaboradores do quadro.

public:
    /**
     * @brief Construtor padrão da classe Quadro.
     */
    Quadro() {}

    /**
     * @brief Construtor da classe Quadro.
     * @param n Nome do quadro.
     * @param d Descrição do quadro.
     */
    Quadro(const std::string &n, const std::string &d) : nome(n), descricao(d) {}

    /**
     * @brief Destrutor da classe Quadro.
     */
    ~Quadro()
    {
        listaColunas.limpar();
    }

    /**
     * @brief Adiciona uma coluna ao quadro.
     * @param coluna Ponteiro para a coluna a ser adicionada.
     */
    void adicionarColuna(Coluna *coluna)
    {
        listaColunas.inserirInicio(coluna);
    }

    /**
     * @brief Remove uma coluna do quadro.
     * @param indice Índice da coluna a ser removida.
     */
    void removerColuna(int indice)
    {
        listaColunas.removerPorIndice(indice);
    }

    /**
     * @brief Obtém uma coluna do quadro pelo índice.
     * @param indice Índice da coluna.
     * @return Ponteiro para a coluna encontrada.
     */
    Coluna *obterColuna(int indice) const
    {
        return listaColunas.obterPorIndice(indice);
    }

    /**
     * @brief Obtém o número de colunas do quadro.
     * @return Número de colunas do quadro.
     */
    int getNumeroColunas() const
    {
        return listaColunas.getTamanho();
    }

    /**
     * @brief Obtém o nome do quadro.
     * @return Nome do quadro.
     */
    std::string getNome() const
    {
        return nome;
    }

    /**
     * @brief Obtém a descrição do quadro.
     * @return Descrição do quadro.
     */
    std::string getDescricao() const
    {
        return descricao;
    }

    /**
     * @brief Define o nome do quadro.
     * @param n Novo nome do quadro.
     */
    void setNome(std::string n)
    {
        nome = n;
    }

    /**
     * @brief Define a descrição do quadro.
     * @param d Nova descrição do quadro.
     */
    void setDescricao(std::string d)
    {
        descricao = d;
    }

    /**
     * @brief Obtém a equipe de colaboradores do quadro.
     * @return Equipe de colaboradores do quadro.
     */
    std::set<Colaborador *, comparador> getEquipe()
    {
        return equipe;
    }

    /**
     * @brief Imprime as informações do quadro.
     */
    void imprimir() const
    {
        std::cout << "\nNome do Quadro: " << nome << std::endl;
        std::cout << "Descricao do Quadro: " << descricao << std::endl;

        for (int i = 0; i < getNumeroColunas(); i++)
        {
            Coluna *coluna = obterColuna(i);
            std::cout << "|=========== " << coluna->getNome() << " ===========| " << std::endl;
            std::cout << "Indice da Coluna: " << i << std::endl;
            coluna->imprimir();
            std::cout << std::endl;
        }
    }

    /**
     * @brief Insere um colaborador na equipe do quadro.
     * @param colaborador Ponteiro para o colaborador a ser inserido.
     */
    void inserirColaborador(Colaborador *colaborador)
    {
        equipe.insert(colaborador);
    }

    /**
     * @brief Exibe os colaboradores da equipe do quadro.
     */
    void exibirColaboradores()
    {
        for (Colaborador *colaborador : equipe)
        {
            std::cout << "ID " << colaborador->getID() << ": ";
            std::cout << colaborador->getNome() << std::endl;
        }
    }

    /**
     * @brief Move uma coluna do quadro para uma nova posição.
     * @param indiceAntigo Índice atual da coluna.
     * @param indiceNovo Novo índice para a coluna.
     */
    void moverColuna(int indiceAntigo, int indiceNovo)
    {
        listaColunas.moverColuna(indiceAntigo, indiceNovo);
    }
};

#endif
