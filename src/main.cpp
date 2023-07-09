#include <iostream>
#include <cstdlib>
#include <string>
#include "../include/quadro.hpp"

using std::cout;
using std::endl;

string input(string pergunta)
{
    string resposta;
    std::cout << pergunta;
    std::cin >> resposta;
    return resposta;
}

void limparConsole()
{
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

}

void criarQuadro(Quadro *&KanBan)
{
    string nome = input("Nome do Quadro: ");
    string desc = input("Descricao do Quadro: ");
    KanBan = new Quadro(nome, desc);
}

void criarColuna(Quadro *&KanBan)
{
    string nome = input("Nome da Coluna: ");
    string desc = input("Descricao da Coluna: ");
    Coluna *coluna = new ColunaNomeada(nome, desc);
    KanBan->adicionarColuna(coluna);
    cout << "Coluna adiconada com sucesso!" << endl;
    KanBan->imprimir();
}

void editarColuna(Quadro *&KanBan)
{
    int indice = stoi(input("Indice da Coluna: "));

    if (indice < 0 || indice >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    string nome = input("Novo nome da Coluna: ");
    string desc = input("Nova descricao da Coluna: ");
    KanBan->obterColuna(indice)->setNome(nome);
    KanBan->obterColuna(indice)->setDescricao(desc);
    cout << "Coluna editada com sucesso!" << endl;
}

void removerColuna(Quadro *&KanBan)
{
    int indice = stoi(input("Indice da Coluna: "));
    if (indice < 0 || indice >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }
    KanBan->removerColuna(indice);
    cout << "Coluna removida com sucesso!" << endl;
}

void adicionarTarefa(Quadro *&KanBan)
{
    int indice = stoi(input("Indice da Coluna: "));
    if (indice < 0 || indice >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }
    string titulo = input("Titulo da Tarefa: ");
    string descricao = input("Descricao da Tarefa: ");
    string prioridade = input("Prioridade da Tarefa: ");
    int numeroPrioridade;
    try
    {
        numeroPrioridade = stoi(prioridade);
    }
    catch (...)
    {
        cout << "Prioridade invalida!" << endl;
        return;
    }

    Tarefa *tarefa = new Tarefa(titulo, descricao);
    tarefa->setPrioridade(numeroPrioridade);
    KanBan->obterColuna(indice)->inserirTarefa(tarefa);

    cout << "Tarefa adicionada com sucesso!" << endl;

    string decisao = input("Quer designar essa tarefa a algum colaborador do quadro? (S/N)");
    if (decisao == "S")
    {
        string nomeColaborador = input("Nome do colaborador: ");
        string contatoColaborador = input("Contato do colaborador: ");
        string funcaoColaborador = input("Funcao do colaborador: ");
        Colaborador *colaborador = new Colaborador(nomeColaborador, contatoColaborador, funcaoColaborador);
        KanBan->obterColuna(indice)->obterTarefa(indice)->setResponsavel(colaborador);
        cout << "Colaborador designado com sucesso!" << endl;
    }

    return;
}

void moverTarefas(Quadro *&KanBan)
{
    int indice = stoi(input("Indice da Coluna: "));
    if (indice < 0 || indice >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    int indiceTarefa = stoi(input("Indice da Tarefa: "));
    if (indiceTarefa < 0 || indiceTarefa >= KanBan->obterColuna(indice)->getTamanho())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    Tarefa *tarefa = KanBan->obterColuna(indice)->obterTarefa(indiceTarefa);
    cout << tarefa;
    string decisao = input("Quer mover essa tarefa para outra coluna? (S/N) ");
    if (decisao == "S")
    {
        int indiceDestino = stoi(input("Indice da Coluna: "));
        if (indiceDestino < 0 || indiceDestino >= KanBan->getNumeroColunas())
        {
            cout << "Indice invalido!" << endl;
            return;
        }

        KanBan->obterColuna(indice)->moverTarefa(indiceTarefa, KanBan->obterColuna(indiceDestino));
        cout << "Tarefa movida com sucesso!" << endl;
    }

    return;
}

void editarTarefa(Quadro *&KanBan)
{
    int indiceColuna = stoi(input("Indice da Coluna: "));
    if (indiceColuna < 0 || indiceColuna >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    int indiceTarefa = stoi(input("Indice da Tarefa: "));
    if (indiceTarefa < 0 || indiceTarefa >= KanBan->obterColuna(indiceColuna)->getTamanho())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    string titulo = input("Novo titulo da Tarefa (deixe em branco para manter)): ");
    if (titulo != "")
    {
        KanBan->obterColuna(indiceColuna)->obterTarefa(indiceTarefa)->setTitulo(titulo);
    }

    string descricao = input("Nova descricao da Tarefa (deixe em branco para manter): ");
    if (descricao != "")
    {
        KanBan->obterColuna(indiceColuna)->obterTarefa(indiceTarefa)->setDescricao(descricao);
    }

    string prioridade = input("Nova prioridade da Tarefa (deixe em branco para manter): ");
    if (prioridade != "")
    {
        string prioridade = input("Prioridade da Tarefa: ");
        int numeroPrioridade;
        try
        {
            numeroPrioridade = stoi(prioridade);
        }
        catch (...)
        {
            cout << "Prioridade invalida!" << endl;
            return;
        }
        KanBan->obterColuna(indiceColuna)->obterTarefa(indiceTarefa)->setPrioridade(numeroPrioridade);
    }

    cout << "Tarefa editada com sucesso!" << endl;
    return;
}

void removerTarefa(Quadro *&KanBan)
{
    int indiceColuna = stoi(input("Indice da Coluna: "));
    if (indiceColuna < 0 || indiceColuna >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    int indiceTarefa = stoi(input("Indice da Tarefa: "));
    if (indiceTarefa < 0 || indiceTarefa >= KanBan->obterColuna(indiceColuna)->getTamanho())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    KanBan->obterColuna(indiceColuna)->removerTarefa(indiceTarefa);
    cout << "Tarefa removida com sucesso!" << endl;
}

void adicionarColunaArquivo(Quadro *&KanBan)
{
    cout << "Colunas do tipo \"arquivo\" são utilizadas para armazenar tarefas finalizadas e/ou obsoletas." << endl;
    string nome = input("Nome da Coluna: ");
    string desc = input("Descricao da Coluna: ");
    Coluna *colunaArquivo = new ColunaArquivo(nome, desc);
    KanBan->adicionarColuna(colunaArquivo);
}

void moverColunas(Quadro *&KanBan)
{
    int indice = stoi(input("Indice da coluna a ser movida: "));
    if (indice < 0 || indice >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    int indiceDestino = stoi(input("Indice da coluna destino: "));
    if (indiceDestino < 0 || indiceDestino >= KanBan->getNumeroColunas())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    if (indice == indiceDestino)
    {
        cout << "Indices iguais." << endl;
        return;
    }

    KanBan->moverColuna(indice, indiceDestino);
    cout << "Coluna movida com sucesso!" << endl;
}

int main()
{
    Quadro *KanBan = nullptr;
    bool quadroCriadoOuCarregado = false;
    int opcao = -1;

    while (opcao != 0)
    {
        if (!quadroCriadoOuCarregado)
        {
            std::cout << "========== MENU INICIAL ==========" << std::endl;
            std::cout << "1. Criar quadro" << std::endl;
            std::cout << "2. Carregar quadro" << std::endl;
            std::cout << "0. Sair" << std::endl;
            std::cout << "===================================" << std::endl;
            std::cout << "Digite o numero da opcao desejada: ";
            std::cin >> opcao;

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
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
                continue;
            }
        }

        else
        {
            std::cout << "========== MENU ==========" << std::endl;
            std::cout << "1. Adicionar Coluna" << std::endl;
            std::cout << "2. Editar Coluna" << std::endl;
            std::cout << "3. Remover Coluna" << std::endl;
            std::cout << "4. Adicionar Tarefa" << std::endl;
            std::cout << "5. Mover Tarefas" << std::endl;
            std::cout << "6. Editar Tarefa" << std::endl;
            std::cout << "7. Remover Tarefa" << std::endl;
            std::cout << "8. Adicionar Coluna de Arquivo" << std::endl;
            std::cout << "9. Mover Colunas" << std::endl;
            std::cout << "10. Imprimir Quadro" << std::endl;
            std::cout << "11. Salvar Quadro" << std::endl;
            std::cout << "0. Sair" << std::endl;
            std::cout << "==========================" << std::endl;
            std::cout << "Digite o numero da opcao desejada: ";
            std::cin >> opcao;

            if (opcao == 1)
            {
                limparConsole();
                criarColuna(KanBan);
            }
            else if (opcao == 2)
            {
                limparConsole();
                editarColuna(KanBan);
            }
            else if (opcao == 3)
            {
                limparConsole();
                removerColuna(KanBan);
            }
            else if (opcao == 4)
            {
                limparConsole();
                adicionarTarefa(KanBan);
            }
            else if (opcao == 5)
            {
                limparConsole();
                moverTarefas(KanBan);
            }
            else if (opcao == 6)
            {
                limparConsole();
                editarTarefa(KanBan);
            }
            else if (opcao == 7)
            {
                limparConsole();
                removerTarefa(KanBan);
            }
            else if (opcao == 8)
            {
                limparConsole();
                adicionarColunaArquivo(KanBan);
            }
            else if (opcao == 9)
            {
                limparConsole();
                moverColunas(KanBan);
            }
            else if (opcao == 10)
            {
                limparConsole();
                KanBan->imprimir();
            }
            else if (opcao == 11)
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