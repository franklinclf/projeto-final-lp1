#ifndef __QUADRO__
#define __QUADRO__
#include <iostream>
#include <string>
#include <set>
#include "colunas.hpp"
#include "listaSimplesmenteEncadeada.hpp"

struct comparador
{
    bool operator()(Colaborador* c1, Colaborador* c2) const
    {
        return c1->getID() < c2->getID();
    }
};

class Quadro {
private:
    std::string nome;
    std::string descricao;
    Lista listaColunas;
    std::set<Colaborador*, comparador> equipe;

public:
    Quadro() {}
    Quadro(const std::string& n, const std::string& d) : nome(n), descricao(d) {}
    ~Quadro() {
        listaColunas.limpar();
    }

    void adicionarColuna(Coluna* coluna) {
        listaColunas.inserirInicio(coluna);
    }

    void removerColuna(int indice) {
        listaColunas.removerPorIndice(indice);
    }

    Coluna* obterColuna(int indice) const {
        return listaColunas.obterPorIndice(indice);
    }

    int getNumeroColunas() const {
        return listaColunas.getTamanho();
    }

    std::string getNome() const {
        return nome;
    }

    std::string getDescricao() const {
        return descricao;
    }

    std::set<Colaborador*, comparador> getEquipe() {
        return equipe;
    }

    void imprimir() const {
        std::cout << "\nNome do Quadro: " << nome << std::endl;
        std::cout << "Descricao do Quadro: " << descricao << std::endl;

        for (int i = 0; i < getNumeroColunas(); i++) {
            Coluna* coluna = obterColuna(i);
            std::cout << "+------------ " << coluna->getNome() << " ------------+ " << std::endl;
            std::cout << "Indice da Coluna: " << i << std::endl;
            coluna->imprimir();
            std::cout << std::endl;
        }
    }
    
    void inserirColaborador(Colaborador* colaborador) {
        equipe.insert(colaborador);
    }

    void exibirColaboradores() {
        for (Colaborador* colaborador : equipe) {
            std::cout << "ID " << colaborador->getID() << ": ";
            std::cout << colaborador->getNome() << std::endl;
        }
    }

    void moverColuna(int indiceAntigo, int indiceNovo)
    {
        listaColunas.moverColuna(indiceAntigo, indiceNovo);
    }
};

#endif