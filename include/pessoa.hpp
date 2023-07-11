#ifndef __PESSOA__
#define __PESSOA__

#include <iostream>
#include <string>

using std::cout;
using std::ostream;
using std::string;

class Pessoa
{
protected:
    string nome;
    string contato;

public:
    Pessoa() {}
    Pessoa(string n, string c) : nome(n), contato(c) {}
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

class Colaborador : public Pessoa
{
private:
    string funcao;
    int tarefasAtribuidas;
    int idUnico;
    static int contador;

public:
    Colaborador()
    {
        idUnico = ++contador;
    }
    Colaborador(string n, string c, string f) : Pessoa(n, c), funcao(f)
    {
        idUnico = ++contador;
    }
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

    int getID()
    {
        return idUnico;
    }

    friend ostream &operator<<(std::ostream &out, Colaborador *&colaborador)
    {
        out << "ID: " << colaborador->idUnico << "\n";
        out << "Nome: " << colaborador->nome << "\n";
        out << "Contato: " << colaborador->contato << "\n";
        out << "Funcaoo: " << colaborador->funcao << "\n";

        return out;
    }
};

#endif