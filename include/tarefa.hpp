#ifndef __TAREFA__
#define __TAREFA__

#include <string>
#include <iostream>
#include "pessoa.hpp"

using std::cout;
using std::ostream;
using std::string;

class Tarefa
{
private:
    string titulo;
    string descricao;
    int prioridade;
    Colaborador* responsavel;

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
    Tarefa() {}

    Tarefa(string t, string d) : titulo(t), descricao(d), prioridade(0) {}

    ~Tarefa() {}

    void setTitulo(string t)
    {
        titulo = t;
    }

    void setDescricao(string d)
    {
        descricao = d;
    }

    void setPrioridade(int p)
    {
        prioridade = p;
    }

    void setResponsavel(Colaborador* r)
    {
        responsavel = r;
    }

    string getTitulo()
    {
        return titulo;
    }

    string getDescricao()
    {
        return descricao;
    }

    int getPrioridade()
    {
        return prioridade;
    }

    Colaborador* getResponsavel()
    {
        return responsavel;
    }

    friend std::ostream &operator<<(std::ostream &os, Tarefa &tarefa)
    {
        const int quadroWidth = 40;

        os << "+" << std::string(quadroWidth, '-') << "+\n";
        os << "| " << alinhamento(tarefa.titulo, quadroWidth - 3) << " |\n";
        os << "+" << std::string(quadroWidth, '-') << "+\n";
        os << "| Descricao: " << std::string(quadroWidth - 14, ' ') << " |\n";
        os << quebrarLinha(tarefa.descricao, quadroWidth + 1);
        os << "+" << std::string(quadroWidth, '-') << "+\n";
        os << "| Prioridade: " << alinhamento(std::to_string(tarefa.prioridade), quadroWidth - 15) << " |\n";
        os << "| Responsavel: " << alinhamento(tarefa.responsavel->getNome(), quadroWidth - 16) << " |\n";
        os << "+" << std::string(quadroWidth, '-') << "+\n";

        return os;
    }

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
        os << "| Responsavel: " << alinhamento(tarefa->responsavel->getNome(), quadroWidth - 16) << " |\n";
        os << "+" << std::string(quadroWidth, '-') << "+\n";

        return os;
    }
};

#endif