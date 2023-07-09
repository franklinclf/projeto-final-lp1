#ifndef __LISTASE__
#define __LISTASE__
#include <iostream>
#include "colunas.hpp"

class NoSimples {
public:
    Coluna* coluna;
    NoSimples* proximo;

    NoSimples(Coluna* c) : coluna(c), proximo(nullptr) {}
};

class Lista {
private:
    NoSimples* inicio;
    int tamanho;

public:
    Lista() : inicio(nullptr), tamanho(0) {}

    ~Lista() {
        limpar();
    }

    bool vazia() const {
        return tamanho == 0;
    }

    int getTamanho() const {
        return tamanho;
    }

    void inserirInicio(Coluna* coluna) {
        NoSimples* novoNo = new NoSimples(coluna);
        novoNo->proximo = inicio;
        inicio = novoNo;
        tamanho++;
    }

    void removerInicio() {
        if (vazia()) {
            throw std::out_of_range("Lista vazia");
        }

        NoSimples* noRemovido = inicio;
        inicio = inicio->proximo;
        delete noRemovido->coluna;
        delete noRemovido;
        tamanho--;
    }

    void limpar() {
        while (!vazia()) {
            removerInicio();
        }
    }

    Coluna* obterPorIndice(int indice) const {
        if (indice < 0 || indice >= tamanho) {
            throw std::out_of_range("Índice inválido");
        }

        NoSimples* atual = inicio;
        for (int i = 0; i < indice; i++) {
            atual = atual->proximo;
        }

        return atual->coluna;
    }

    void moverColuna(int indiceAntigo, int indiceNovo) {

        NoSimples* noA = inicio;
        NoSimples* noB = inicio;
        for (int i = 0; i < indiceAntigo; i++) {
            noA = noA->proximo;
        }
        for (int i = 0; i < indiceNovo; i++) {
            noB = noB->proximo;
        }

        Coluna* temp = noA->coluna;
        noA->coluna = noB->coluna;
        noB->coluna = temp;
    }
};

#endif