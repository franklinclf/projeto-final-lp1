#ifndef __PESSOA__
#define __PESSOA__

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::ostream;

class Pessoa {
    protected:
    string nome;
    string contato;

    public:
    Pessoa() {}
    Pessoa(string n, string c): nome(n), contato(c) {}
    ~Pessoa() {}

    void setNome(string n)
    {
        nome = n;
    }

    void setContato(string c)
    {
        contato = c;
    }

    string getNome()
    {
        return nome;
    }

    string getContato()
    {
        return contato;
    }

};

class Colaborador : public Pessoa{
    private:
    string funcao;
    int tarefasAtribuidas;

    public:
    Colaborador() {}
    Colaborador(string n, string c, string f): Pessoa(n, c), funcao(f) {}
    ~Colaborador() {}

    void setFuncao(string f)
    {
        funcao = f;
    }

    void setTarefasAtribuidas(int t)
    {
        tarefasAtribuidas = t;
    }

    string getFuncao()
    {
        return funcao;
    }

    int getTarefasAtribuidas()
    {
        return tarefasAtribuidas;
    }

    friend ostream& operator<<(std::ostream& out, Colaborador& colaborador)
    {
        out << "Nome: " << colaborador.nome << "\n";
        out << "Contato: " << colaborador.contato << "\n";
        out << "Função: " << colaborador.funcao << "\n";

        return out;
    }
};

#endif