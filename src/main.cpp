#include <iostream>
#include <string>
#include "../include/Tarefa.hpp"
#include "../include/Colunas.hpp"
using std::endl;

int main()
{
    Colaborador franks("Franklin Oliveira", "franklin-oliveira@outlook.com.br", "Scrum Master");
    Colaborador dennis("Dennis Gabriel", "franklin-oliveira@outlook.com.br", "Scrum Master");
    Tarefa t1("Linguagem de Programacao 1", "Aliqua enim officia magna nisi fugiat laborum duis labore nisi commodo. Cillum cupidatat est non pariatur sit laborum officia deserunt. Officia cupidatat incididunt cillum do nulla cillum nisi.");
    Tarefa t2("Linguagem de Programacao 2", "Cillum cupidatat est non pariatur sit laborum officia deserunt. Officia cupidatat incididunt cillum do nulla cillum nisi.");
    t1.setPrioridade(1);
    t1.setResponsavel(franks);
    t2.setPrioridade(3);
    t2.setResponsavel(dennis);

    ColunaNomeada c1("Coluna teste", "Isso aqui eh soh um teste, em?");
    c1.inserirTarefa(t1);
    c1.imprimir();

    c1.inserirTarefa(t2);
    c1.imprimir();

    t2.setResponsavel(franks);

    c1.ordenar();
    c1.imprimir();


    return 0;
}

