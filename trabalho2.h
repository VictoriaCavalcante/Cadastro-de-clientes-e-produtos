#include<stdio.h>
#include<stdlib.h>

//Estruturas para pilha de produtos dos clientes
struct lista_produtos
{
    char info_produto[50];
    struct lista_produtos *prox;
};
typedef struct lista_produtos Lista_produtos;

struct pilha
{
    Lista_produtos *topo;
};
typedef struct pilha Pilha;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Estrutura que guarda e cria os clientes
struct lista_cliente
{
    int info_cod;
    char info_nome[50];
    char info_email[20];
    struct lista_cliente *prox;
    Pilha *p;//pilha de produtos recentemente adquiridos
};
typedef struct lista_cliente Lista;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCAO PARA CRIAR A LISTA (esta sera usada apenas uma vez)
Lista* cria_lista(Lista *l)
{
    return NULL;
}

//FUNCAO PARA ADICIONAR E CRIAR OS NOVOS CLIENTES NA LISTA: 1 - Cadastra cliente
Lista* add_cliente(Lista *l, int cod)
{
    Lista *aux = l;
    if(cod > 9999){
        printf("\nFALHOU: APENAS 4 DIGITOS PERMITIDAS"); //verificando se o codigo possui apenas 4 digitos
        return l;
    }

    while(aux != NULL)
    {
        if(aux->info_cod == cod) //verificando se o codigo fornecido para adicionar o cliente ja esta sendo usado por outro cliente
        {
       //o COD do cliente eh fornecido no main e o nome e email nesta funcao, dessa forma, assim que o usuario entrar com o codigo ha a
      //verificacao se o mesmo encontra-se utilizado. Em caso afirmativo o usuario eh informado antes de ter que escrever o nome e o email
            printf("\nFALHOU: ESTE COD JA ESTA SENDO USADO");
            return l;
        }
        aux = aux->prox;
    }

    //variaveis para insercao ordenada dos clientes mediante seus codigos
    aux = l;
    Lista *ant = NULL; //esta variavel eh utilizada para nao perdermos a lista
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    novo->info_cod = cod;

    while(aux != NULL && aux->info_cod < cod)//para adicionar em ordem crescente eh verificado se o codigo eh menor do que o codigo do cliente que ja esta na lista
    {
        ant = aux;
        aux = aux->prox;
        //se ele sair o while por conta da primeira sentenca, ele eh o maior da lista.
        //se ele sair por conta da segunda sentenca, ele sera adicionado na frente do elemento que ele eh maior
    }

    if(ant == NULL)//se o anterior for igual a NULL ele sera adicionado no inicio
    {
        novo->prox = l;
        l = novo;
    }
    else //se nao, adicionamos ele na posicao correspondente com cuidado para nao perder a lista
    {
        ant->prox = novo;
        novo->prox = aux;
    }

    //leitura dos dados do cliente
    printf("Nome: ");
    scanf("%s", novo->info_nome);
    printf("Email: ");
    scanf("%s", novo->info_email);

    //criacao da pilha de produtos do cliente
    novo->p = (Pilha*) malloc(sizeof(Pilha));
    novo->p->topo = NULL;

    printf("\nCLIENTE CADASTRADO");
    return l;
}

//FUNCAO PARA REMOVER CLIENTES: 2 - Remove cliente
Lista* remove_cliente(Lista *l, int cod)
{
    Lista *ant = NULL;
    Lista *aux = l;
    if(aux == NULL) //se nao houver clientes na lista emite-se essa mensagem
        printf("NAO HA CLIENTES");
    else
    {
        if(aux->info_cod == cod) //se o cliente a ser removido estiver na primeira posicao ha um tratamento diferente
        {
            l = aux->prox;  //o primeiro elemento aponta para o segundo para que a lista nao seja perdida
            printf("\nCLIENTE %d REMOVIDO (%s)", cod, aux->info_nome);
            free(aux);     // entao o primeiro eh liberado
        }
        else //se o cliente a ser removido nao for o primeiro executa-se as linhas abaixo
        {
            while(aux != NULL && aux->info_cod != cod)//while criado para percorrer a lista buscando o cliente atraves do COD fornecido
            {
                ant = aux;
                aux = aux->prox;
            }
            if(aux == NULL) //se esta sentenca for verdadeira quer dizer que ele percorreu toda a lista e nao encontrou o COD
                printf("\nCLIENTE %d NAO CADASTRADO", cod); //emite-se entao esta mensagem
            else
            {
                //se nao, quer dizer que o COD foi encontrado, entao o cliente eh removido

//A variavel ant passara a apontar para o elemento que esta sendo apontado pelo elemento que vai ser removido, ou seja, o posterior ao que sera removido.
                // Assim nao perdemos o restante da lista

                ant->prox = aux->prox;
                printf("\nCLIENTE %d REMOVIDO (%s)", cod, aux->info_nome);//feedback para o usuario
                free(aux); //o elemento entao, eh finalmente liberado
            }
        }
    }
    return l;
}

//FUNCAO PARA MOSTRAR O NOME E O EMAIL DO CLIENTE, DADO O CODIGO: 3 - Buscar cliente
void busca_cliente(Lista *l, int cod)
{
    Lista *aux = l;
    if(aux == NULL) //Lista de clientes vazia
        printf("NAO HA CLIENTES CADASTRADOS");
    else
    {
        while(aux != NULL)//while para percorrer a lista
        {
            if(aux->info_cod == cod) //se o codigo fornecido for encontrado emitimos o nome e o email do cliente
            {
                printf("Nome: %s\nE-mail: %s\n\n", aux->info_nome, aux->info_email);
                printf("CLIENTE ENCONTRADO");
                break;
            }
            aux = aux->prox;
        }
        if(aux == NULL) //se o aux for igual a NULL, quer dizer que ele percorreu toda a lista e nao encontrou
            printf("CLIENTE NAO CADASTRADO");  //portanto, sera emitida esta mensagem.
    }
}

//esta funcao eh semelhante a funcao de busca, porem, recebe um endereco (ponteiro de ponteiro) pois ela sera utilizada dentro de funcoes
//o motivo de nao utilizarmos a funcao busca para isso (transformando ela em uma funcao com retorno) eh por conta das mensagens que ela emite
Lista* get_cliente(Lista **l, int cod)
{
    //mesmo principio da funcao "busca_cliente", agora retornando o cliente
    Lista *aux = *l;
    if(aux == NULL)
    {
        printf("NAO HA CLIENTES CADASTRADOS");
        return NULL;
    }
    else
    {
        while(aux != NULL)
        {
            if(aux->info_cod == cod)
                return aux;

            aux = aux->prox;
        }
        if(aux == NULL)
        {
            printf("CLIENTE NAO CADASTRADO");
            return NULL;
        }
    }
}

//FUNCAO PARA IMPRIMIR OS DADOS DOS CLIENTES (RELATORIO): 7 - Relatorio clientes
void imprime(Lista *l)
{
    Lista *aux = l;
    if(aux == NULL) //se estiver vazia emite-se esta mensagem, nao executa o while abaixo
        printf("NENHUM CLIENTE CADASTRADO");

    while(aux != NULL)//while para percorrer a lista imprimindo os dados dos clientes
    {
        printf("\nCod: %d\nNome: %s\nE-mail: %s\n-------------------------", aux->info_cod, aux->info_nome, aux->info_email);
        aux = aux->prox;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//FUNCAO PARA ADICIONAR UM PRODUTO A PILHA DE PRODUTOS DO CLIENTE (push): 4 - Adicionar produto
void add_produto(Lista *l, int cod)
{
    Lista *cliente = get_cliente(&l, cod); //funcao para obter o cliente detentor do codigo indicado, caso exista
    if(cliente != NULL)
    {
        Lista_produtos *lp = (Lista_produtos*)malloc(sizeof(Lista_produtos));
        lp->prox = cliente->p->topo; //o produto criado agora aponta para o primeiro da lista dos produtos
        cliente->p->topo = lp;//e o topo (que indica o inicio da lista) passa a pontar para ele, transformando-o em primeiro da lista
        printf("Produto: ");
        scanf("%s", lp->info_produto);
        printf("\nPRODUTO ADICIONADO");
    }
}

//FUNCAO PARA IMPRIMIR A PILHA DE PRODUTOS DE UM CLIENTE, DADO O CODIGO: 6 - Imprimir produtos
void imprime_pilha(Lista *l, int cod)
{
    Lista *cliente = get_cliente(&l, cod);
    //caso o usuario entre com um cod que nao esta cadastrado ou caso nao haja clientes cadastrados a funcao busca chamada acima trata isso emitindo estas mensagens para o usuario
    if(cliente != NULL)
    {
        Lista_produtos *aux = cliente->p->topo;
        //se o topo for igual a NULL ha produtos (lembrando que temos acesso a pilha dos clientes por conta da funcao "get_cliente")
        if(aux == NULL)
            printf("\nNAO HA PRODUTO");
        else
        {
            //se o aux (topo) for diferente de NULL os produtos serao impressos.
            printf("\nPRODUTOS CLIENTE %d: (%s)\n", cod, cliente->info_nome);
            while(aux != NULL)
            {
                printf("-> %s\n", aux->info_produto);
                aux = aux->prox;
            }
        }
    }
}

//FUNCAO PARA REMOVER O ULTIMO PRODUTO ADICIONADO NA PILHA DE UM CLIENTE, DADO O CODIGO: 5 - Remover produto
int remove_produto(Lista *l, int cod)
{
    Lista *cliente = get_cliente(&l, cod); //buscamos o cliente para termos acesso a sua pilha
    if(cliente != NULL)
    {
        if(cliente->p->topo == NULL) //se seu topo estiver vazio quer dizer que nao ha produtos
            return 0;
        else //se nao, o produto do topo eh removido.
        {
            Lista_produtos* prod = cliente->p->topo;
            cliente->p->topo = cliente->p->topo->prox;
            free(prod);
            return 1;
        }
    }
}
