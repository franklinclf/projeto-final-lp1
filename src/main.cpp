#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>
#include "../include/quadro.hpp"

using namespace std;

void limparConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearBuffer()
{
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Colaborador::contador = 0;

Colaborador *buscaBinaria(const set<Colaborador *, comparador> &equipe, int id)
{
    auto inicio = equipe.begin();
    auto fim = equipe.end();

    while (inicio != fim)
    {
        if ((*inicio)->getID() == id)
        {
            return *inicio;
        }
        else if ((*inicio)->getID() < id)
        {
            ++inicio;
        }
        else
        {
            return nullptr;
        }
    }

    return nullptr;
}

Colaborador *cadastrarColaborador(Quadro *&KanBan)
{
    clearBuffer();
    string nome, contato, funcao;
    cout << "Digite o nome do colaborador: ";
    getline(cin, nome);
    cout << "Digite o contato do colaborador: ";
    getline(cin, contato);
    cout << "Digite a funcao do colaborador: ";
    getline(cin, funcao);

    Colaborador *colaborador = new Colaborador(nome, contato, funcao);
    KanBan->inserirColaborador(colaborador);

    return colaborador;
}

void criarQuadro(Quadro *&KanBan)
{
    clearBuffer();

    string nome, desc;

    cout << "Digite o nome do quadro: ";
    getline(cin, nome);

    cout << "Digite a descricao do quadro: ";
    getline(cin, desc);

    KanBan = new Quadro(nome, desc);
}

void criarColuna(Quadro *&KanBan)
{
    clearBuffer();
    string nome, desc;

    cout << "Digite o nome da coluna: ";
    getline(cin, nome);

    cout << "Digite a descricao da coluna: ";
    getline(cin, desc);

    Coluna *coluna = new ColunaNomeada(nome, desc);
    KanBan->adicionarColuna(coluna);

    cout << "Coluna adiconada com sucesso!" << endl;
}

void editarColuna(Quadro *&KanBan)
{
    
    if (KanBan->getNumeroColunas() == 0)
    {
        cout << "Crie uma coluna primeiro!" << endl;
        return;
    }

    KanBan->imprimir();

    int indice;

    cout << "Digite o indice da coluna: ";
    if (!(std::cin >> indice) || indice < 0 || indice >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    clearBuffer();

    string nome, desc;

    cout << "Novo nome da coluna (para manter, deixe vazio): ";
    std::getline(std::cin, nome);
    if (nome != "")
    {
        KanBan->obterColuna(indice)->setNome(nome);
    }

    cout << "Novo descricao da coluna (para manter, deixe vazio): ";
    std::getline(std::cin, desc);
    if (desc != "")
    {
        KanBan->obterColuna(indice)->setDescricao(desc);
    }

    cout << "Coluna editada com sucesso!" << endl;
}

void removerColuna(Quadro *&KanBan)
{
    clearBuffer();
    if (KanBan->getNumeroColunas() == 0)
    {
        cout << "Crie uma coluna primeiro!" << endl;
        return;
    }

    KanBan->imprimir();
    int indice;

    cout << "Digite o indice da coluna a ser removida: ";

    if (!(std::cin >> indice) || indice < 0 || indice >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    KanBan->removerColuna(indice);
    cout << "Coluna removida com sucesso!" << endl;
}

void adicionarTarefa(Quadro *&KanBan)
{
    if (KanBan->getNumeroColunas() == 0)
    {
        cout << "Crie uma coluna primeiro!" << endl;
        return;
    }

    clearBuffer();

    KanBan->imprimir();
    
    int indice;

    cout << "Digite o indice da coluna: ";
    if (!(std::cin >> indice) || indice < 0 || indice >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        clearBuffer();
        return;
    }

    clearBuffer();


    string titulo, descricao;
    int prioridade;

    cout << "Digite o titulo da tarefa: ";
    std::getline(std::cin, titulo);

    cout << "Digite a descricao da tarefa: ";
    std::getline(std::cin, descricao);

    cout << "Digite a prioridade da tarefa: ";
    if (!(std::cin >> prioridade) || prioridade < 0)
    {
        cout << "Prioridade invalida!" << endl;
        clearBuffer();
        return;
    }

    clearBuffer();

    Tarefa *tarefa = new Tarefa(titulo, descricao);
    tarefa->setPrioridade(prioridade);
    KanBan->obterColuna(indice)->inserirTarefa(tarefa);

    cout << "Tarefa adicionada com sucesso!" << endl;

    char decisao;
    cout << "Quer designar essa tarefa a algum colaborador? (S/N) ";

    if (!(std::cin >> decisao) || toupper(decisao) != 'S')
    {
        clearBuffer();
        return;
    }

    char decisao2;
    cout << "Criar novo colaborador? (S/N) ";

    if (!(std::cin >> decisao2))
    {
        cout << "Operacao invalida." << endl;
        clearBuffer();
        return;
    }
    else if (toupper(decisao2) == 'S')
    {
        tarefa->setResponsavel(cadastrarColaborador(KanBan));
        cout << "Colaborador designado com sucesso!" << endl;
    }
    else
    {
        int idColaborador;
        cout << "ID do colaborador: ";
        if (!(std::cin >> idColaborador))
        {
            cout << "Indice invalido!" << endl;
            clearBuffer();
            return;
        }

        if (buscaBinaria(KanBan->getEquipe(), idColaborador) != nullptr)
        {
            tarefa->setResponsavel(buscaBinaria(KanBan->getEquipe(), idColaborador));
            cout << "Colaborador designado com sucesso!" << endl;
        }
        else
        {
            cout << "Indice invalido!" << endl;
            clearBuffer();
            return;
        }
    }
    return;
}

void moverTarefas(Quadro *&KanBan)
{
    if (KanBan->getNumeroColunas() == 0)
    {
        cout << "Crie uma coluna primeiro!" << endl;
        return;
    }

    if (KanBan->getNumeroColunas() < 2)
    {
        cout << "Crie mais uma coluna primeiro." << endl;
        return;
    }

    clearBuffer();

    KanBan->imprimir();

    int indiceColuna;

    cout << "Digite o indice da coluna que contem essa tarefa: ";
    if (!(std::cin >> indiceColuna) || indiceColuna < 0 || indiceColuna >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        clearBuffer();
        return;
    }


    if(KanBan->obterColuna(indiceColuna)->getTamanho() == 0)
    {
        cout << "Coluna vazia!" << endl;
        clearBuffer();
        return;
    }

    clearBuffer();

    int indiceTarefa;

    cout << "Digite o indice da tarefa que deseja mover: ";
    if (!(std::cin >> indiceTarefa) || indiceTarefa < 0 || indiceTarefa >= KanBan->obterColuna(indiceColuna)->getTamanho())
    {
        cout << "Indice invalido!" << endl;
        clearBuffer();
        return;
    }

    Tarefa *tarefa = KanBan->obterColuna(indiceColuna)->obterTarefa(indiceTarefa);
    cout << tarefa;

    clearBuffer();

    char decisao;
    cout << "Quer mover essa tarefa para outra coluna? (S/N) ";
    if (!(std::cin >> decisao) || toupper(decisao) != 'S')
    {
        return;
    }

    cout << "Digite o indice da coluna para qual voce quer mover a tarefa: ";

    int indiceDestino;
    if (!(std::cin >> indiceDestino) || indiceDestino < 0 || indiceDestino >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        clearBuffer();
        return;
    }

    clearBuffer();

    KanBan->obterColuna(indiceColuna)->moverTarefa(indiceTarefa, KanBan->obterColuna(indiceDestino));
    return;
}

void editarTarefa(Quadro *&KanBan)
{
    if (KanBan->getNumeroColunas() == 0)
    {
        cout << "Crie uma coluna primeiro!" << endl;
        return;
    }

    clearBuffer();

    KanBan->imprimir();

    int indiceColuna;

    cout << "Digite o indice da coluna: ";
    if (!(std::cin >> indiceColuna) || indiceColuna < 0 || indiceColuna >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    int indiceTarefa;
    cout << "Digite o indice da tarefa: ";
    if (!(std::cin >> indiceTarefa) || indiceTarefa < 0 || indiceTarefa >= KanBan->obterColuna(indiceColuna)->getTamanho())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    string titulo;
    cout << "Novo titulo da Tarefa (deixe em branco para manter): ";
    std::getline(std::cin, titulo);
    if (titulo != "")
    {
        KanBan->obterColuna(indiceColuna)->obterTarefa(indiceTarefa)->setTitulo(titulo);
    }

    string desc;
    cout << "Novo descricao da Tarefa (deixe em branco para manter): ";
    std::getline(std::cin, desc);
    if (desc != "")
    {
        KanBan->obterColuna(indiceColuna)->obterTarefa(indiceTarefa)->setDescricao(desc);
    }

    int prioridade;
    cout << "Novo prioridade da Tarefa (deixe em branco para manter): ";
    if (!(std::cin >> prioridade) || prioridade < 0)
    {
        cout << "Prioridade invalida!" << endl;
        clearBuffer();
        return;
    }
    if (std::cin.peek() == '\n')
    {
        return;
    }
    else
    {
        KanBan->obterColuna(indiceColuna)->obterTarefa(indiceTarefa)->setPrioridade(prioridade);
    }

    cout << "Tarefa editada com sucesso!" << endl;
    return;
}

void removerTarefa(Quadro *&KanBan)
{
    if (KanBan->getNumeroColunas() == 0)
    {
        cout << "Crie uma coluna primeiro!" << endl;
        return;
    }

    clearBuffer();

    KanBan->imprimir();

    int indiceColuna, indiceTarefa;

    cout << "Digite o indice da coluna: ";
    if (!(std::cin >> indiceColuna) || indiceColuna < 0 || indiceColuna >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    cout << "Digite o indice da tarefa: ";
    if (!(std::cin >> indiceTarefa) || indiceTarefa < 0 || indiceTarefa >= KanBan->obterColuna(indiceColuna)->getTamanho())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    KanBan->obterColuna(indiceColuna)->removerTarefa(indiceTarefa);

    cout << "Tarefa removida com sucesso!" << endl;
}

void adicionarColunaArquivo(Quadro *&KanBan)
{
    clearBuffer();
    cout << "Colunas do tipo \"arquivo\" são utilizadas para armazenar tarefas finalizadas e/ou obsoletas." << endl;

    string nome, desc;
    cout << "Digite o nome da coluna: ";
    getline(cin, nome);
    cout << "Digite a descricao da coluna: ";
    getline(cin, desc);

    Coluna *colunaArquivo = new ColunaArquivo(nome, desc);
    KanBan->adicionarColuna(colunaArquivo);
}

void moverColuna(Quadro *&KanBan)
{
    if (KanBan->getNumeroColunas() == 0)
    {
        cout << "Crie uma coluna primeiro!" << endl;
        return;
    }

    if (KanBan->getNumeroColunas() < 2)
    {
        cout << "Crie mais uma coluna primeiro." << endl;
        return;
    }

    clearBuffer();

    KanBan->imprimir();

    int indice, indiceDestino;
    cout << "Digite o indice da coluna: ";
    if (!(std::cin >> indice) || indice < 0 || indice >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    cout << "Digite o indice da coluna destino: ";
    if (!(std::cin >> indiceDestino) || indiceDestino < 0 || indiceDestino >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    KanBan->moverColuna(indice, indiceDestino);

    cout << "Coluna movida com sucesso!" << endl;
}

void ordenarColuna(Quadro *&KanBan)
{
    if (KanBan->getNumeroColunas() == 0)
    {
        cout << "Crie uma coluna primeiro." << endl;
        return;
    }
    
    clearBuffer();

    KanBan->imprimir();

    int indice;
    cout << "Digite o indice da coluna: ";
    if (!(std::cin >> indice) || indice < 0 || indice >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    KanBan->obterColuna(indice)->ordenar();

    cout << "Coluna ordenada com sucesso!" << endl;
}

void exibirColaboradores(Quadro *&KanBan)
{
    if (KanBan->getEquipe().size() == 0)
    {
        cout << "Nenhum colaborador adicionado." << endl;
        return;
    }

    KanBan->exibirColaboradores();
}

void buscarColaborador(Quadro *&KanBan)
{
    if (KanBan->getEquipe().size() == 0)
    {
        cout << "Nenhum colaborador adicionado." << endl;
        return;
    }

    int id;
    cout << "Digite o ID do colaborador: ";
    if (!(std::cin >> id) || id < 1)
    {
        cout << "ID invalido!" << endl;
        return;
    }

    Colaborador *colaborador = buscaBinaria(KanBan->getEquipe(), id);
    if (colaborador != nullptr)
    {
        cout << "Colaborador encontrado!" << endl;
        cout << colaborador;
    }
    else
    {
        cout << "Colaborador nao encontrado!" << endl;
    }
}

int main()
{
    limparConsole();

    Quadro *KanBan = nullptr;
    bool quadroCriadoOuCarregado = false;
    int opcao = -1;

    while (opcao != 0)
    {
        
        if (!quadroCriadoOuCarregado)
        {
            cout << "\n\n========== MENU INICIAL ==========" << endl;
            cout << "1. Criar quadro" << endl;
            cout << "2. Carregar quadro" << endl;
            cout << "0. Sair" << endl;
            cout << "===================================" << endl;

            cout << "Digite a opcao desejada: ";
            while (!(std::cin >> opcao) || opcao < 0 || opcao > 2)
            {
                cout << "Entrada invalida. Tente novamente." << endl;
                clearBuffer();
                cout << "Digite a opcao desejada: ";
            }

            if (opcao == 1)
            {
                limparConsole();
                criarQuadro(KanBan);
                quadroCriadoOuCarregado = true;
            }
            else if (opcao == 2)
            {
                limparConsole();
                break;
            }
            else if (opcao == 0)
            {
                limparConsole();
                break;
            }
            else
            {
                limparConsole();
                cout << "Opcao invalida. Tente novamente." << endl;
                clearBuffer();
                continue;
            }
        }

        else
        {
            cout << "\n\n========== MENU ==========" << endl;
            cout << "1. Adicionar coluna" << endl;
            cout << "2. Editar coluna" << endl;
            cout << "3. Remover coluna" << endl;
            cout << "4. Adicionar tarefa" << endl;
            cout << "5. Mover tarefas" << endl;
            cout << "6. Editar tarefa" << endl;
            cout << "7. Remover tarefa" << endl;
            cout << "8. Adicionar coluna de Arquivo" << endl;
            cout << "9. Mover coluna" << endl;
            cout << "10. Ordenar coluna" << endl;
            cout << "11. Cadastrar colaborador" << endl;
            cout << "12. Exibir lista de colaboradores" << endl;
            cout << "13. Buscar colaborador" << endl;
            cout << "14. Imprimir quadro" << endl;
            cout << "15. Salvar quadro" << endl;
            cout << "0. Sair" << endl;
            cout << "==========================" << endl;

            cout << "Digite a opcao desejada: ";
            while (!(std::cin >> opcao) || opcao < 0 || opcao > 15)
            {
                cout << "Entrada invalida. Tente novamente." << endl;
                clearBuffer();
                cout << "Digite a opcao desejada: ";
            }

            if (opcao == 1)
            {
                limparConsole();
                criarColuna(KanBan);
                KanBan->imprimir();
            }
            else if (opcao == 2)
            {
                limparConsole();
                editarColuna(KanBan);
                KanBan->imprimir();
            }
            else if (opcao == 3)
            {
                limparConsole();
                removerColuna(KanBan);
                KanBan->imprimir();
            }
            else if (opcao == 4)
            {
                limparConsole();
                adicionarTarefa(KanBan);
                KanBan->imprimir();
            }
            else if (opcao == 5)
            {
                limparConsole();
                moverTarefas(KanBan);
                KanBan->imprimir();
            }
            else if (opcao == 6)
            {
                limparConsole();
                editarTarefa(KanBan);
                KanBan->imprimir();
            }
            else if (opcao == 7)
            {
                limparConsole();
                removerTarefa(KanBan);
                KanBan->imprimir();
            }
            else if (opcao == 8)
            {
                limparConsole();
                adicionarColunaArquivo(KanBan);
                KanBan->imprimir();
            }
            else if (opcao == 9)
            {
                limparConsole();
                moverColuna(KanBan);
                KanBan->imprimir();
            }
            else if (opcao == 10)
            {
                limparConsole();
                ordenarColuna(KanBan);
                KanBan->imprimir();
            }
            else if (opcao == 11)
            {
                limparConsole();
                cadastrarColaborador(KanBan);
                KanBan->exibirColaboradores();
            }
            else if (opcao == 12)
            {
                limparConsole();
                exibirColaboradores(KanBan);
            }
            else if (opcao == 13)
            {
                limparConsole();
                buscarColaborador(KanBan);
            }
            else if (opcao == 14)
            {
                limparConsole();
                KanBan->imprimir();
            }
            else if (opcao == 15)
            {
                limparConsole();
                break;
            }
            else if (opcao == 0)
            {
                limparConsole();
                break;
            }
            else
            {
                limparConsole();
                cout << "Opcao invalida. Tente novamente." << endl;
                continue;
            }
        }
    }

    return 0;
}