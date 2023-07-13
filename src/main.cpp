/**
 * @file main.cpp
 * @brief Sistema de Gerenciamento de Tarefas
 *
 * Este programa implementa um sistema de quadro KanBan que permite a criação
 * de quadros, colunas, tarefas, colaboradores, e a realização de diversas operações
 * como adicionar, editar e remover colunas e tarefas, mover tarefas entre colunas,
 * designar colaboradores para tarefas, entre outras.
 *
 * @author Franklin Oliveira
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "../include/quadro.hpp"
#include "../include/listaDuplamenteEncadeada.hpp"
#include "../include/listaSimplesmenteEncadeada.hpp"

using namespace std;

/**
 * @brief Limpa a tela do console.
 */
void limparConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Limpa o buffer do console.
 */
void clearBuffer()
{
    cin.clear();
    cin.ignore(100, '\n');
}

int Colaborador::contador = 0;

/**
 * @brief Realiza uma busca binária em uma equipe de colaboradores pelo ID.
 *
 * @param equipe O conjunto de colaboradores a ser pesquisado.
 * @param id O ID do colaborador a ser encontrado.
 * @return Um ponteiro para o colaborador encontrado ou nullptr se não for encontrado.
 */
Colaborador *buscaBinaria(const set<Colaborador *, comparador> &equipe, int id)
{
    auto inicio = equipe.begin();
    auto fim = equipe.end();

    while (inicio != fim)
    {
        auto meio = std::next(inicio, std::distance(inicio, fim) / 2);

        if ((*meio)->getID() == id)
        {
            return *meio;
        }
        else if ((*meio)->getID() < id)
        {
            inicio = std::next(meio);
        }
        else
        {
            fim = meio;
        }
    }

    return nullptr;
}

/**
 * @brief Cria e cadastra um novo colaborador no quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 * @return O ponteiro para o novo colaborador cadastrado.
 */
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

/**
 * @brief Cria um novo quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan a ser criado.
 */
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

/**
 * @brief Cria e adiciona uma nova coluna ao quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
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

/**
 * @brief Edita uma coluna existente no quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
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

/**
 * @brief Remove uma coluna do quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
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

/**
 * @brief Adiciona uma nova tarefa a uma coluna no quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
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

/**
 * @brief Move uma tarefa de uma coluna para outra no quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
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

    if (KanBan->obterColuna(indiceColuna)->getTamanho() == 0)
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

/**
 * @brief Edita uma tarefa existente no quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
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
        clearBuffer();
        return;
    }

    clearBuffer();

    int indiceTarefa;
    cout << "Digite o indice da tarefa: ";
    if (!(std::cin >> indiceTarefa) || indiceTarefa < 0 || indiceTarefa >= KanBan->obterColuna(indiceColuna)->getTamanho())
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    clearBuffer();

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

    string input;
    int prioridade;

    cout << "Novo prioridade da Tarefa (deixe em branco para manter): ";
    std::getline(std::cin, input);

    if (!(input.empty()))
    {
        try
        {
            prioridade = stoi(input);
            KanBan->obterColuna(indiceColuna)->obterTarefa(indiceTarefa)->setPrioridade(prioridade);
        }
        catch (...)
        {
            cout << "Prioridade invalida!" << endl;
            clearBuffer();
            return;
        }
    }

    string input2;
    int ID;

    cout << "ID do novo responsavel (deixe em branco para manter): ";
    std::getline(std::cin, input2);

    if (!(input2.empty()))
    {
        try
        {
            ID = stoi(input2);
        }
        catch (...)
        {
            cout << "ID invalido!" << endl;
            clearBuffer();
            return;
        }
    }

    if (buscaBinaria(KanBan->getEquipe(), ID) == nullptr)
    {
        cout << "Colaborador nao cadastrado." << endl;
        return;
    }

    KanBan->obterColuna(indiceColuna)->obterTarefa(indiceTarefa)->setResponsavel(buscaBinaria(KanBan->getEquipe(), ID));

    cout << "Tarefa editada com sucesso!" << endl;
    return;
}

/**
 * @brief Remove uma tarefa de uma coluna no quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
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

/**
 * @brief Adiciona uma nova coluna do tipo "arquivo" ao quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
void adicionarColunaArquivo(Quadro *&KanBan)
{
    clearBuffer();
    cout << "Colunas do tipo \"arquivo\" sao utilizadas para armazenar tarefas finalizadas e/ou obsoletas." << endl;

    string nome, desc;
    cout << "Digite o nome da coluna: ";
    getline(cin, nome);
    cout << "Digite a descricao da coluna: ";
    getline(cin, desc);

    Coluna *colunaArquivo = new ColunaArquivo(nome, desc);
    KanBan->adicionarColuna(colunaArquivo);
}

/**
 * @brief Move uma coluna de uma posição para outra no quadro KanBan.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
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

/**
 * @brief Ordena as tarefas em uma coluna do quadro KanBan com base na prioridade.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
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

/**
 * @brief Busca um colaborador pelo ID no quadro KanBan e exibe suas informações.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 */
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

/**
 * @brief Salva o quadro KanBan em um arquivo.
 *
 * @param KanBan O ponteiro para o quadro KanBan.
 * @param fileName O nome do arquivo de saída.
 */
void salvarQuadro(Quadro *&KanBan, string fileName)
{
    if (KanBan->getNumeroColunas() == 0)
    {
        cout << "Crie uma coluna primeiro!" << endl;
        return;
    }

    ofstream file(fileName);

    if (!file)
    {
        cout << "Erro ao abrir arquivo." << endl;
        return;
    }

    // quadro
    file << KanBan->getNome();
    file << "\n";
    file << KanBan->getDescricao();
    file << "\n";

    // equipe
    set<Colaborador *, comparador> equipe = KanBan->getEquipe();
    int tamanhoEquipe = equipe.size();
    file << tamanhoEquipe;
    file << "\n";
    for (Colaborador *colaborador : equipe)
    {
        file << colaborador->getNome();
        file << "\t";
        file << colaborador->getContato();
        file << "\t";
        file << colaborador->getFuncao();
        file << "\t";
        file << colaborador->getID();
        file << "\n";
    }

    // colunas

    int numeroColunas = KanBan->getNumeroColunas();
    file << numeroColunas;
    file << "\n";
    for (int i = 0; i < numeroColunas; i++)
    {
        file << KanBan->obterColuna(i)->getNome();
        file << "\t";
        file << KanBan->obterColuna(i)->getDescricao();
        file << "\t";
        string tipoColuna = "nomeada";
        if (dynamic_cast<ColunaArquivo *>(KanBan->obterColuna(i)) != nullptr)
        {
            tipoColuna = "arquivo";
        }
        file << tipoColuna;
        file << "\t";
        // tarefas
        int numeroTarefas = KanBan->obterColuna(i)->getTamanho();
        file << numeroTarefas;
        file << "\n";
        for (int j = 0; j < numeroTarefas; j++)
        {
            Tarefa *tarefa = KanBan->obterColuna(i)->obterTarefa(j);
            file << tarefa->getTitulo();
            file << "\t";
            file << tarefa->getDescricao();
            file << "\t";
            file << tarefa->getPrioridade();
            file << "\t";
            if (tarefa->getResponsavel() == nullptr)
            {
                file << "nullptr";
            }
            else
            {
                file << tarefa->getResponsavel()->getID();
            }
            file << "\n";
        }
    }

    cout << "Quadro salvo com sucesso!" << endl;

    file.close();
}

/**
 * @brief Carrega um quadro KanBan a partir de um arquivo.
 *
 * @param fileName O nome do arquivo a ser carregado.
 * @return O ponteiro para o quadro KanBan carregado.
 */
Quadro *carregarQuadro(string fileName)
{
    ifstream file(fileName);

    if (!file)
    {
        cout << "Erro ao abrir arquivo." << endl;
        return nullptr;
    }

    string nomeQuadro, descricaoQuadro;
    getline(file, nomeQuadro);
    getline(file, descricaoQuadro);

    Quadro *quadro = new Quadro(nomeQuadro, descricaoQuadro);

    int tamanhoEquipe;
    file >> tamanhoEquipe;
    file.ignore(100, '\n');

    for (int i = 0; i < tamanhoEquipe; i++)
    {
        string nome, contato, funcao;
        int id;
        getline(file, nome, '\t');
        getline(file, contato, '\t');
        getline(file, funcao, '\t');
        file >> id;
        file.ignore(100, '\n');
        quadro->inserirColaborador(new Colaborador(nome, contato, funcao));
    }

    int numeroColunas;
    file >> numeroColunas;
    file.ignore(100, '\n');

    for (int i = 0; i < numeroColunas; i++)
    {
        string nomeColuna, descricaoColuna, tipoColuna;
        getline(file, nomeColuna, '\t');
        getline(file, descricaoColuna, '\t');
        getline(file, tipoColuna, '\t');

        Coluna *coluna;
        if (tipoColuna == "arquivo")
        {
            coluna = new ColunaArquivo(nomeColuna, descricaoColuna);
        }
        else
        {
            coluna = new ColunaNomeada(nomeColuna, descricaoColuna);
        }

        int numeroTarefas;
        file >> numeroTarefas;
        file.ignore(100, '\n');

        for (int j = 0; j < numeroTarefas; j++)
        {
            Tarefa *tarefa;
            string titulo, descricao, responsavelString;
            int prioridade, responsavelID;
            getline(file, titulo, '\t');
            getline(file, descricao, '\t');
            file >> prioridade;
            file.ignore(100, '\t');
            getline(file, responsavelString, '\n');
            if (responsavelString == "nullptr")
            {
                tarefa = new Tarefa(titulo, descricao, prioridade, nullptr);
            }
            else
            {
                responsavelID = stoi(responsavelString);
                tarefa = new Tarefa(titulo, descricao, prioridade, buscaBinaria(quadro->getEquipe(), responsavelID));
            }

            coluna->inserirTarefa(tarefa);
        }

        quadro->adicionarColuna(coluna);
    }

    file.close();

    cout << "Quadro carregado com sucesso!" << endl;

    return quadro;
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
                string fileName;
                cout << "Digite o nome do arquivo (com extensao): ";
                cin >> fileName;
                KanBan = carregarQuadro(fileName);
                if (KanBan != nullptr)
                {
                    quadroCriadoOuCarregado = true;
                }
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
            }
        }

        else
        {
            cout << "\n========== MENU ==========" << endl;
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
                salvarQuadro(KanBan, "save.txt");
            }
            else if (opcao == 0)
            {
                limparConsole();
                salvarQuadro(KanBan, "save.txt");
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