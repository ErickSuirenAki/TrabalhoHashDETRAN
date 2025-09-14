#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TF 30
struct registro{
    char status;
	char placa[9];
	int dia,mes,ano;
	int infracao;
};
void Criar(struct registro p[TF]){
	 int i;
    for (i=0; i<TF; i++){
        p[i].status= 'L';
        strcpy(p[i].placa,"");
        p[i].dia=0;
        p[i].mes=0;
        p[i].ano=0;
        p[i].infracao=0;
    }
    printf("\nTabela Hash enderecamento aberto (tentativa quadratica) criada\n");
}

void Exibir(struct registro p[TF])
{
    int i;

    for(i=0;i<TF;i++){
        printf("\n Posicao %d\tPlaca %s\tData: %d/%d/%d\tInfracao %d\tStatus %c",i, p[i].placa, p[i].dia,p[i].mes,p[i].ano,p[i].infracao, p[i].status);
    }
}


int Hash(char chave[15]){
    int i, soma =0;
    for(i=0; chave[i]!='\0';i++){
        if(chave[i]>='0' && chave[i]<='9')
            soma = soma + chave[i] - '0';
        else
            soma = soma + (int)chave[i];
    }
    return soma%TF;
    

}

void Inserir(struct registro p[TF]){
    int ender,k=1, dia, mes, ano, infracao;
    char chave[9];

    printf("\nDigite a placa do carro a ser adicionada a infracao ");
    fflush(stdin);
    gets(chave);
    printf("\nDigite o dia do registro da infracao(DD) ");
    scanf("%d", &dia);
    printf("\nDigite o mes do registro da infracao(MM) ");
    scanf("%d", &mes);
    printf("\nDigite o ano do registro da infracao(AAAA) ");
    scanf("%d", &ano);
    printf("\nDigite o codigo da infracao ");
    scanf("%d", &infracao);

    ender = Hash(chave);

    if(p[ender].status == 'L' || p[ender].status == 'R'){
        strcpy(p[ender].placa,chave);
        p[ender].ano =  ano;
        p[ender].dia = dia;
        p[ender].infracao = infracao;
        p[ender].mes = mes;
        p[ender].status = 'O';
    }
    else{
        while(k<TF && p[ender].status!='L' && p[ender].status!='R'){
            ender = (ender+k)%TF;
            k++;
        }
        if(k<TF){
            strcpy(p[ender].placa,chave);
            p[ender].ano =  ano;
            p[ender].dia = dia;
            p[ender].infracao = infracao;
            p[ender].mes = mes;
            p[ender].status = 'O';

        }
        else{
            printf("\nNao inseriu - Loop ou lotado");    
    }
}

}


int Buscar(struct registro p[TF], char chave[9]){
    int k = 1;
    int ender = Hash(chave);

    while(k<TF && p[ender%TF].status !='L'){
        if(p[ender%TF].status == 'O' && strcmp(p[ender%TF].placa,chave)==0){
            return ender;
        }
        ender = (ender+k)%TF;
        k++;
    }
    return TF;
    
}

void ConsultarPlaca (struct registro p[TF]){
    int ender,i;
    char chave[9];
    printf("\nDigite a placa do carro: ");
    fflush(stdin);
    gets(chave);

    ender = Buscar(p,chave);
    if(ender == TF){
        printf("Placa nao encontrada");
    }
    else{
        for(i=0; i<TF;i++){
            if(strcmp(p[i].placa, chave) == 0 && p[i].status == 'O'){
                 printf("\nPlaca %s Infracao %d Data %d/%d/%d", p[i].placa, p[i].infracao, p[i].dia, p[i].mes, p[i].ano);

            }
        }
}
}

void RemoverInfracao (struct registro p[TF]){
    int ender,infracao,i;
    char chave[9];

    printf("\nDigite a placa do carro: ");
    fflush(stdin);
    gets(chave);

    ender = Buscar(p,chave);
    if(ender == TF){
        printf("\nPlaca nao encontrada");
    }
    else{
        for(i=0; i<TF;i++){
            if(strcmp(p[i].placa, chave) == 0 && p[i].status == 'O'){
                 printf("\nPlaca %s Infracao %d Data %d/%d/%d", p[i].placa, p[i].infracao, p[i].dia, p[i].mes, p[i].ano);

            }
        }
        printf("\n\nQual das infracoes deseja remover?(codigo da infracao)\n");
        scanf("%d", &infracao);

        for(i=0; i<TF;i++){
            if(p[i].infracao == infracao && strcmp(p[i].placa, chave)==0 && p[i].status == 'O'){
                p[i].status = 'R';
                printf("Infracao %d removida da placa %s", infracao, chave);
                break;
            }
        }
        if(i==TF){
            printf("\nCodigo de infracao nao encontrado");

        }    
    }
}


int main (){

    struct registro p[TF];
    int op =-1;

    Criar(&p);

    while(op!=5){

        printf("\n\n1- Inserir infracao veicular - placa(3 letras e 4 numeros), data e codigo infracao ");
        printf("\n2- Consultar uma infracao pela placa do carro ");
        printf("\n3-Remover infracao");
        printf("\n4- Exibir tudo ");
        printf("\n5- sair ");
        printf("\nopcao?\n");
        scanf("%d", &op);

        switch(op){

            case 1:
                Inserir(p);
                break;
            case 2:
                ConsultarPlaca(p);
                break;
            case 3:
                RemoverInfracao(p);
                break;
            case 4:
                Exibir(p);
                break;
                
        }//switch

    }//while

    return 0;

}//main