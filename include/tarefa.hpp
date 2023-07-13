/**
 * @file tarefa.hpp
 * @brief Definição da classe Tarefa
 * @author Franklin Oliveira
 */

#ifndef __TAREFA__
#define __TAREFA__

#include <string>
#include <iostream>
#include "pessoa.hpp"

using std::cout;
using std::ostream;
using std::string;

/**
 * @brief Classe que representa uma Tarefa.
 */
class Tarefa
{
private:
    string titulo;                 /**< Título da tarefa */
    string descricao;              /**< Descrição da tarefa */
    int prioridade;                /**< Prioridade da tarefa */
    Colaborador* responsavel;      /**< Responsável pela tarefa */

    /**
     * @brief Alinha um texto ao centro de uma largura específica.
     * @param texto Texto a ser alinhado.
     * @param width Largura do alinhamento.
     * @return Texto alinhado.
     */
    static string alinhamento(const string &texto, int width)
    {
        int espacos = width - texto.length();
        if (espacos > 0)
        {
            int espacosEsquerda = espacos / 2;
            int espacosDireita = espacos - espacosEsquerda;
            return std::string(espacosEsquerda, ' ') + texto + std::string(espacosDireita, ' ');
        }
        return texto;
    }

    /**
     * @brief Quebra o texto em várias linhas com base em uma largura específica.
     * @param texto Texto a ser quebrado.
     * @param width Largura máxima de cada linha.
     * @return Texto quebrado em várias linhas.
     */
    static string quebrarLinha(const string &texto, int width)
    {
        string resultado;
        int posicao = 0;
        while (posicao < (int)texto.length())
        {
            string linha = texto.substr(posicao, width - 4);
            if (linha.back() == ' ')
            {
                resultado += "| " + linha + std::string(width - 4 - linha.length(), ' ') + " |\n";
            }
            else
            {
                int posEspaco = linha.find_last_of(' ');
                if (posEspaco != (int)string::npos)
                {
                    linha[posEspaco] = ' ';
                    resultado += "| " + linha + std::string(width - 4 - linha.length(), ' ') + " |\n";
                }
                else
                {
                    resultado += "| " + linha + std::string(width - 4 - linha.length(), ' ') + " |\n";
                }
            }
            posicao += width - 4;
        }
        return resultado;
    }

public:
    /**
     * @brief Construtor padrão da classe Tarefa.
     */
    Tarefa() {}

    /**
     * @brief Construtor da classe Tarefa.
     * @param t Título da tarefa.
     * @param d Descrição da tarefa.
     */
    Tarefa(string t, string d) : titulo(t), descricao(d), prioridade(0) {
        responsavel = nullptr;
    }

    /**
     * @brief Construtor da classe Tarefa.
     * @param t Título da tarefa.
     * @param d Descrição da tarefa.
     * @param p Prioridade da tarefa.
     * @param r Responsável pela tarefa.
     */
    Tarefa(string t, string d, int p, Colaborador* r) : titulo(t), descricao(d), prioridade(p), responsavel(r) {}

    /**
     * @brief Destrutor da classe Tarefa.
     */
    ~Tarefa() {}

    /**
     * @brief Define o título da tarefa.
     * @param t Título da tarefa.
     */
    void setTitulo(string t)
    {
        titulo = t;
    }

    /**
     * @brief Define a descrição da tarefa.
     * @param d Descrição da tarefa.
     */
    void setDescricao(string d)
    {
        descricao = d;
    }

    /**
     * @brief Define a prioridade da tarefa.
     * @param p Prioridade da tarefa.
     */
    void setPrioridade(int p)
    {
        prioridade = p;
    }

    /**
     * @brief Define o responsável pela tarefa.
     * @param r Responsável pela tarefa.
     */
    void setResponsavel(Colaborador* r)
    {
        responsavel = r;
        ++r;
    }

    /**
     * @brief Obtém o título da tarefa.
     * @return Título da tarefa.
     */
    string getTitulo()
    {
        return titulo;
    }

    /**
     * @brief Obtém a descrição da tarefa.
     * @return Descrição da tarefa.
     */
    string getDescricao()
    {
        return descricao;
    }

    /**
     * @brief Obtém a prioridade da tarefa.
     * @return Prioridade da tarefa.
     */
    int getPrioridade()
    {
        return prioridade;
    }

    /**
     * @brief Obtém o responsável pela tarefa.
     * @return Responsável pela tarefa.
     */
    Colaborador* getResponsavel()
    {
        return responsavel;
    }

    /**
     * @brief Sobrecarga do operador de saída (<<) para imprimir as informações da tarefa.
     * @param os Fluxo de saída.
     * @param tarefa Ponteiro para a tarefa a ser impressa.
     * @return Fluxo de saída atualizado.
     */
    friend std::ostream &operator<<(std::ostream &os, Tarefa* &tarefa)
    {
        const int quadroWidth = 40;

        os << "+" << std::string(quadroWidth, '-') << "+\n";
        os << "| " << alinhamento(tarefa->titulo, quadroWidth - 3) << " |\n";
        os << "+" << std::string(quadroWidth, '-') << "+\n";
        os << "| Descricao: " << std::string(quadroWidth - 14, ' ') << " |\n";
        os << quebrarLinha(tarefa->descricao, quadroWidth + 1);
        os << "+" << std::string(quadroWidth, '-') << "+\n";
        os << "| Prioridade: " << alinhamento(std::to_string(tarefa->prioridade), quadroWidth - 15) << " |\n";
        if(tarefa->responsavel != nullptr)
        {
            os << "| Responsavel: " << alinhamento(tarefa->responsavel->getNome(), quadroWidth - 16) << " |\n";
        }
        else
        {
            os << "| Responsavel: " << alinhamento("Nao designado.", quadroWidth - 16) << " |\n";
        }
        os << "+" << std::string(quadroWidth, '-') << "+\n";

        return os;
    }
};

#endif
