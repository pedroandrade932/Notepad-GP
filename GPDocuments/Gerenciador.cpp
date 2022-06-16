// Dominio-negocio do projeto: papelaria e loja.
// Funcionalidades: Serve para armazenar o preço, o nome e a quatidade no estoque.

//---- Bibliotecas ----//
#include <iostream>//---- Daqui é pego o "cout" e o "cin". ----//
#include <unistd.h>//---- Usada para o "usleep" (o ".h" é obrigatório). ----//
#include <fstream>
#include <string>
#include <sstream>
#include "uteis.h"//---- Biblioteca personalizada. ----//
using namespace std;

struct Loja//--- Aqui ficam os dados da loja ---//
{
    string his;//--- Aqui fica o "hitórico" da loja. ---//
    float capt;//--- Aqui é armazenado o capital da loja ---//
    float preco;//--- Aqui é guardado o preço de todos os produtos. ---//
    int quant;//--- Aqui é armazenado a quantidade de itens de cada produto. ---//
    string nome;//--- Aqui é colocado o nome de todos os produtos. ---//
};


//---- Variaveis globais (Pelo menos até onde eu sei).----//
Loja shop[150];//--- Vetor que possui Todos os dados da loja. ---//
bool en = false;//--- Essa é só uma variável para a def "search" (necessaria para que a pesquisa termine). ---//
int at = 0;//--- A quantidade de itens que a loja possue. ---//
int his = 0;//--- Aqui ajuda os dados do histórico. ---//
float capital;//--- Aqui fica o capital ATUAL. ---//


//---- Definição de funções (Defs) ----//
void sleep(int s)//---- Pausa o programa (Uma conversão para segundos). ----//
{
    usleep( s * 1000000);
}


int search()//---- Pesquisa determinado produto pelo nome. ----//
{
    //---- AI rudimentar que pesquisa o produto no estoque, se encontra-lo, devolve seu indice. ----//
    //---- Se não encontrar, avisa que o produto não existe. ----//
    
    string icad;//--- O nome do produto pedido vem aqui dentro. ---//
    en = false;//--- Define "en" para falso sempre que começa uma nova pesquisa. ---//
    int dad = 0;//--- Aqui ficará a id do produto. ---//
    cout << "Nome do produto pedido: ";
    cin >> icad;
    for (int i = 0; i < 150; i++)
    {
        if(shop[i].nome == icad)
        {
            dad = i;
            en = true;
        }
        if(i == 149 and en == false)
        {
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-" << "\n";
            cout << "\033[31mProduto '" << icad << "' não encontrado.\033[m\n";
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-" << "\n";
            sleep(2);
            system("clear");
        }
    }
    return dad;//--- Após encontrar o item envia seu id. ---//
}


void read(){
    ifstream arquivo;
    arquivo.open("exemplo.txt");
    
    if(arquivo.is_open()){
        for (int i = 0; i < 150; i++)
        {
            getline(arquivo, shop[i].nome);
            getline(arquivo, shop[i].his);
        }
        ostringstream str1;
        str1 << his;
        string hist = str1.str();
        ostringstream str2;
        str2 << at;
        string atv = str2.str();
        getline(arquivo, hist);
        getline(arquivo, atv);
        arquivo.close();
    }

}


void save(){
    ofstream arquivo;
    arquivo.open("__saves__/conf.txt");
    
    if(arquivo.is_open()){
        for (int i = 0; i < 150; i++)
        {
            arquivo << shop[i].nome << "\n";
        }
        
        for (int i = 0; i < 150; i++)
        {
            arquivo << shop[i].his << "\n";
        }
        for (int i = 0; i < 150; i++)
        {
            arquivo << shop[i].capt << "\n";
        }
        
        for (int i = 0; i < 150; i++)
        {
            arquivo << shop[i].preco << "\n";
        }
        
        for (int i = 0; i < 150; i++)
        {
            arquivo << shop[i].quant << "\n";
        }
        
        arquivo << at << "\n";
        arquivo << his << "\n";
        arquivo << capital << "\n";
        arquivo.close();
    }
}


//---- Programa principal ----//
int main()//---- Aqui o programa é organizado e as "Defs" utilizadas. ----//
{
    read();
    int res;//--- Aqui ficará a escolha do menu. ---//
    while (true)//--- Laço de repetição principal no qual o programa todo roda. ---//
    {
        cout << "\033[30mAtualizações da v2.0.0: Correção de erros,\najuda, cores, melhoramento na aparência e\nSalvamento de dados.\033[m\n";
        cout << "\033[33m-----------------------------------------\033[m" << "\n";
        cout << "\033[1;34m Gerenciador de estoque e compras v1.1.0\033[m" << "\n";
        cout << "\033[33m-----------------------------------------\033[m" << "\n";
        cout << "\033[30mPara acessar as opções, digite o número correspondente ao lado da opção.\033[m\n";
        if(shop[0].capt == 0)//--- Caso seja a primeira vez que entra no sistema. ---//
        {
            cout << "\033[34mAntes de começar, informe seu capital inicial: R$\033[m";
            cin >> capital;
            shop[his].capt = capital;
            shop[his].his = "Capital inicial: \033[32m+R$";
            his++;
            save();
        }
        res = menu("[ \033[32m1\033[m ] Adicionar item\n[ \033[32m2\033[m ] Vender item\n[ \033[32m3\033[m ] Ver/reabastecer estoque\n[ \033[33m4\033[m ] Entradas e saidas\n[ \033[31m5\033[m ] Desligar\033[m");
        system("clear");
        if(res == 1 and at <= 149)//---- Isso acontece somente se AINDA tiver espaço no estoque. ----//
        {
            int i;//--- Aqui colocará a quantidade do produto atual. ---//
            float s;//--- Aqui colocará o preço do produto atual. ---//
            float cptr;//--- Valor da compra. ---//
            string r = "s";//--- Comfirmar compra arriscada. ---//
            cout << "\033[33m------------------------------------\033[m" << "\n";
            cout << "\033[1;34m Adicionar novo produto na loja\033[m" << "\n";
            cout << "\033[33m------------------------------------\033[m" << "\n";
            cout << "\033[33mDigite o nome do Produto:\033[m ";
            cin >> shop[at].nome;
            i = input("\033[34mDigite a quantidade de unidades:\033[m ");
            shop[at].quant = i;
            cout << "\033[32mDigite o preço pago pelas unidades(o que você gastou no total): R$\033[m ";
            cin >> cptr;
            if(cptr > capital)
            {
                cout << "\033[31mAtenção, a compra excedeu o saldo do capital, sua loja estará falida.\033[m\n";
                cout << "Deseja continuar mesmo assim [s/n]? ";
                cin >> r;
            }
            if(r == "s")//--- Caso sim. ---//
            {
                shop[his].capt = cptr;
                shop[his].his = "Compra: \033[31m-R$";
                capital -= cptr;
                his++;
                cout << "\033[32mDigite o preço por unidade:\033[m ";
                cin >> s;
                shop[at].preco = s;
                at += 1;
                cout << "Adicionado com sucesso.\n";
                sleep(2);
            }
            else
            {
                cout << "Cancelado com sucesso.\n";
                sleep(2);
            }
            system("clear");
        }
        else if(res == 1 and at > 149)//---- Isso acontece somente se NÃO tiver espaço no estoque. ----//
        {
            cout << "------------------------------" << "\n";
            cout << "\033[31mNão há mais vagas no estoque.\033[m" << "\n";
            cout << "------------------------------" << "\n";
            sleep(2);
            system("clear");
        }
        else if(res == 2)//---- Acontece se a opção escolhida for 2. ----//
        {
            int num;//--- número de itens a serem retirados. ---//
            cout << "\033[33m------------------------------------\033[m" << "\n";
            cout << "\033[1;34m Vender um produto da loja\033[m" << "\n";
            cout << "\033[33m------------------------------------\033[m" << "\n";
            int id = search();//--- Variável que indica qual o produto será vendido. ---//
            string conf;//--- Variavel que confirma a compra. ---//
            if(en == true)//---- Caso o resultado da pesquisa seja positivo. ----//
            {
                if (shop[id].quant == 0)//---- Avisa que o produto está esgotado. ----//
                {
                    cout << "\033[31mItem esgotado. Vá em 'Ver/reabastecer estoque' e coloque mais.\033[m\n";
                    sleep(4);
                    system("clear");
                }
                else//---- Caso ainda tenha itens. ----//
                {
                    num = input("\033[33mQuantos itens?\033[m ");
                    system("clear");
                }
                if(num <= shop[id].quant)//---- Acontece se a quantidade de itens for maior ou iqual ao pedido. ----//
                {
                    float val = num * shop[id].preco;//--- calcula o valor total da compra. ---//
                    cout << "O preço final será de: \033[32mR$" << val << "\033[m\n";
                    while(true)
                    {
                        cout << "Realizar compra? ('s' para sim ou 'n' para não) ";
                        cin >> conf;
                        if(conf == "s")//---- Caso a compra seja confirmada. ----//
                        {
                            cout << "\033[32mVenda realizada com sucesso, volte sempre!!!\033[m\n";
                            shop[id].quant -= num;
                            shop[his].capt = val;
                            shop[his].his = "Venda: \033[32m+R$";
                            capital += val;
                            his++;
                            sleep(2);
                            system("clear");
                            break;
                        }
                    
                        else if(conf == "n")//---- Caso seja cancelada. ----//
                        {
                            cout << "\033[31mCompra cancelada com sucesso.\033[m\n";
                            sleep(2);
                            system("clear");
                            break;
                        }
                        else//---- Caso não seja nem sim nem não. ----//
                        {
                            cout << "\033[33mOps... Tente novamente.\033[m\n";
                            sleep(2);
                            system("clear");
                        }
                    }
                }
                else if(shop[id].quant > 0)//---- Caso seja pedido mais produtos que o estoque possui. ----//
                {
                    cout << "\033[31mNão há produtos o suficiente. Vá em 'Ver/reabastecer estoque'.\033[m\n";
                    sleep(4);
                    system("clear");
                }
            }
        }
        else if(res == 3)//---- Caso o usuario queira ver o estoque completo. ----//
        {
            while(true)
            {
                cout << "\033[33m---------------------------------\033[m" << "\n";
                cout << "\033[1;34m Estoque completo da loja\033[m" << "\n";
                cout << "\033[33m---------------------------------\033[m" << "\n";
                if(at <= 0)//--- Caso não tenha produtos no estoque. ---//
                {
                    cout << "\033[3;31mSem produtos no estoque.\033[m\n";
                }
                else//--- Caso tenha produtos no estoque. ---//
                {
                    for (int i = 1; i <= at; i++)
                    {
                        cout << "[ " << i << " ] \033[33m" << shop[i - 1].nome << "\033[34m Q:" << shop[i - 1].quant << " \033[m";
                        cout << "\033[32mR$:" << shop[i - 1].preco << "\033[m\n";
                    }
                }
                int it = input("Escolha um item (999 para sair): ");//--- Aqui ficará a posição do item que o usuario vai mexer. ---//
                system("clear");
                if (it == 999)//---- testa se foi digitado 999. ----//
                {
                    break;
                }
                else if(it <= at)//---- Caso exista um item na loja com esse id. ----//
                {
                    cout << "\033[33m---------------------------------\033[m" << "\n";
                    cout << "\033[1;34m Alteração de produto da loja\033[m" << "\n";
                    cout << "\033[33m---------------------------------\033[m" << "\n";
                    cout << "O que você vai fazer?\n";
                    res = menu("\033[33m[ 1 ] Colocar mais no estoque\n[ 2 ] excluir\n[ 3 ] Mudar o preço\033[m");
                    if(res == 1)//---- Se a resposta for 1. ----//
                    {
                        float cptr;
                        int qt = input("Quantos itens? ");//--- Quantidade a ser somada. ---//
                        shop[it - 1].quant += qt;
                        cout << "\033[32mDigite o preço pago pelas unidades(o que você gastou no total): R$\033[m ";
                        cin >> cptr;
                        shop[his].capt = cptr;
                        shop[his].his = "Compra: \033[31m-R$";
                        capital -= cptr;
                        his++;
                        cout << "\033[32mAdicionado com sucesso.\033[m\n";
                        sleep(2);
                        system("clear");
                    }
                    else if(res == 2)//---- Se a resposta for 2. ----//
                    {
                        for (int i = it - 1; i < 149; i++)
                        {
                            shop[i].nome = shop[i + 1].nome;
                            shop[i].preco = shop[i + 1].preco;
                            shop[i].quant = shop[i + 1].quant;
                        }
                        at -= 1;
                        cout << "\033[31mExcluido com sucesso.\033[m\n";
                        sleep(2);
                        system("clear");
                    }
                    else if(res == 3)//---- Se a resposta for 3. ----//
                    {
                        float pr;//--- Aqui colocará o novo preço. ---//
                        cout << "Qual o novo preço? ";
                        cin >> pr;
                        shop[it - 1].preco = pr;
                        cout << "\033[32mPreço atualizado com sucesso.\033[m\n";
                        sleep(2);
                        system("clear");
                    }
                }
                else//--- Caso o id do produto não exista. ---//
                {
                    cout << "\033[31mErro, tente novamente.\033[m\n";
                    sleep(2);
                    system("clear");
                }
            }
        }
        else if(res == 4)//--- Se a opção for 4. ---//
        {
            int e;
            cout << "\033[33m============================================\033[m\n";
            cout << "   \033[1;34mHISTÓRICO DE ENTRADAS E SAÍDAS DA LOJA\033[m\n";
            cout << "\033[33m============================================\033[m\n";
            for (int i = 0; i < his; i++)
            {
                cout << shop[i].his << shop[i].capt << "\033[m\n";
            }
            cout << "--------------------------------------------\n";
            if(capital >= 0)
                cout << "\033[33mSaldo atual: \033[32m" << capital << "\033[m\n";
            else
            {
                cout << "\033[33mSaldo atual: \033[31m" << capital << "\033[m\n";
            }
            cout << "--------------------------------------------\n";
            cout << "Aperte qualquer número para sair: ";
            cin >> e;
            system("clear");
        }
        else if(res == 5)//--- Se a opção for 5 (Desligar). ---//
        {
            cout << "\033[1;34mDesligando o sistema...\033[m\n";
            save();
            sleep(2);
            cout << "\033[1;33m>>> Volte sempre!!! <<<\033[m\n";
            sleep(1);
            break;
        }
        else//--- Caso o número digitado não seja uma opção. ---//
        {
            cout << "\033[33m---------------------------------\033[m" << "\n";
            cout << "\033[1;31m ERRO: Essa opção não existe.\033[m" << "\n";
            cout << "\033[33m---------------------------------\033[m" << "\n";
            sleep(2);
            system("clear");
        }
    }
    return 0;
}
//---- O programa acaba aqui. ----//
