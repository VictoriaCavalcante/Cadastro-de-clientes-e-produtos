#include "trabalho2.h"

int main()
{
    printf("                     TRABALHO PRATICO 2 - ESTRUTURA DE DADOS\n\n\n");
    printf("Discentes: Andre Cacau e Victoria Cavalcante\n\n\n");
    printf("                                           Elaboracao do programa proposto pelo\n");
    printf("                                           professor  Raoni  para  obtencao  de\n");
    printf("                                           parte  da  nota  referente  a  N2 da\n");
    printf("                                           disciplina de Estrutura de  Dados do\n");
    printf("                                           curso de Bacharelado em  Sistemas de\n");
    printf("                                           Informacao da UFAC. Data: 15/09/2019\n");
    printf("\n________________________________________________________________________________");


    Lista *l; l = cria_lista(l);
    int cod, aux, r;
    printf("\n                   SISTEMA DE CADASTRO DE CLIENTES E PRODUTOS\n");
    while(1)
    {
        printf("\n\nO que desejas fazer?\n");
        //cabecalho de instrucoes para utilizacao do programa
        printf("1 - Cadastrar cliente \n2 - Remover cliente \n3 - Buscar cliente \n4 - Adicionar produto \n5 - Remover produto \n6 - Imprimir produtos \n7 - Relatorio clientes \n8 - Remove todos produtos \n9 - Sair\n");
        printf("Escolha uma das opcoes listadas: ");
        scanf("%d", &aux);

        if(aux == 1)
        {
            printf("\nCADASTRANDO CLIENTE\n\n");
            printf("Cod: ");
            scanf("%d", &cod);
            l = add_cliente(l, cod);
        }
        else if(aux == 2)
        {
            printf("\nREMOVENDO CLIENTE\n\n");
            printf("Insira o COD do cliente: ");
            scanf("%d", &cod);

            if(get_cliente(&l, cod) == NULL) //sempre deve haver a verificacao de se o usuario entrou com um COD cadastrado, pois se nao ele tentaria remover algo que nao existe, gerando assim um erro durante a utilizacao
                printf(" ");//como a funcao acima ja emite o feedbak para o usuario, nao precisamos imprimir nenhuma mensagem aqui
            else
            {
                //caso o codigo fornecido seja valido, o cliente correspondente a ele sera removido juntamente com sua pilha de produtos.
                while(get_cliente(&l, cod)->p->topo != NULL) //removendo a pilha
                    remove_produto(get_cliente(&l, cod), cod); //funcao busca eh utilizada para que a lista dos clientes nao seja perdida
                free(get_cliente(&l, cod)->p); //depois de limpar toda a pilha, a estrutura pilha do cliente eh removida
                l = remove_cliente(l, cod); //por fim, o cliente eh removido
            }
        }
        else if(aux == 3)
        {
            printf("\nBUSCANDO CLIENTE\n\n");
            printf("Insira o COD do cliente: ");
            scanf("%d", &cod);
            busca_cliente(l, cod);
        }
        else if(aux == 4)
        {
            printf("\nADICIONANDO PRODUTO\n\n");
            printf("Insira o COD do cliente: ");
            scanf("%d", &cod);
            add_produto(l, cod);
        }
        else if(aux == 5)
        {
            printf("\nDESFAZENDO ULTIMA AQUISICAO\n\n");
            printf("Insira o COD do cliente: ");
            scanf("%d", &cod);

            //como a funcao "remove_produto" sera usada para remover a pilha de produto dos clientes, ela nao podera emitir mensagens durante a execucao quando for chamada
            r = remove_produto(l, cod);

            //os feedbaks portanto foram adicionados no main, para aparecerem soh quando necessario
            if(r == 1)
                printf("\nAQUISICAO DESFEITA");
            else
                printf("\nNAO HA PRODUTO");
        }
        else if(aux == 6)
        {
            printf("\nIMPRIMINDO PRODUTOS\n\n");
            printf("Insira o COD do cliente: ");
            scanf("%d", &cod);
            imprime_pilha(l, cod);
        }
        else if(aux == 7)
        {
            printf("\nRELATORIO CLIENTES\n");
            imprime(l);
        }
        else if(aux == 8)
        {
            printf("\nREMOVENDO PRODUTOS\n\n"); //esta opcao nao foi feita como funcao pois teriamos que mudar a funcao "remove_produto" para que retorna-se um endereco (ponteiro de ponteiro) para poder ser utilizada dentro de uma funcao
            printf("Insira o COD do cliente: ");
            scanf("%d", &cod);

            if(get_cliente(&l, cod) == NULL) //esta funcao retorna o cliente dado o codigo, utilizamos ela para ter acesso a pilha
                printf(" ");// caso seja verdade a sentenca acima, ela emite a mensagem de que nao ha clientes cadastrados ou de que o cod fornecido nao esta cadatrado, por isso nao imprimimos nada aqui
            else if(remove_produto(get_cliente(&l, cod), cod) == 0)//passamos o cliente como parametro na funcao remove, e caso a funcao retorne 0 quer dizer que nao ha produtos para serem removidos
                printf("\nNAO HA PRODUTO");
            else //se nao, quer dizer que a funcao retornou algo diferente de zero, no caso 1.
            {
                //a funcao busca que criamos eh essencial para termos acesso a pilha de produtos dos clientes
                while(get_cliente(&l, cod)->p->topo != NULL) //enquanto o ponteiro de clientes for diferente de NULL ele removera os produtos atraves da funcao "remove_produto"
                    remove_produto(get_cliente(&l, cod), cod);
                printf("\nPRODUTOS REMOVIDOS");
            }
        }
        else if(aux == 9) //o break sai do while e apos isso o programa eh finalizado (opcao 9 - Sair)
            break;
        else
            printf("\nOPCAO INVALIDA"); //caso o usuario nao entre com nenhuma das opcoes listadas emiti-se esta mensagem
    }

    printf("\n\nOBRIGADO POR UTILIZAR O PROGRAMA");
    return 0;
}
