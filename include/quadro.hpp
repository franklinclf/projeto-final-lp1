#ifndef __QUADRO__
#define __QUADRO__
#include <iostream>
#include <string>
#include "colunas.hpp"
#include "listaSimplesmenteEncadeada.hpp"

class Quadro {
private:
    std::string nome;
    std::string descricao;
    Lista listaColunas;

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
        listaColunas.removerInicio();
    }

    void limparColunas() {
        listaColunas.limpar();
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

    void moverColuna(int indiceAntigo, int indiceNovo)
    {
        listaColunas.moverColuna(indiceAntigo, indiceNovo);
    }
};

#endif