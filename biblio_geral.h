/* BIBLIOTECAS */
#include <stdio.h>  /*biblioteca padrão*/
#include <stdlib.h> /*para usar funcao system*/
#include <locale.h> /*para usar funcao setlocale*/
#include <string.h> /*para usar fgets e afins*/
#include <conio.h>  /*para usar gets e afins*/

/* DEFINIÇÕES */
#define enti_max   116 /*o maior tem 116 caracteres*/
#define cnpj_max   14  /*CNPJ tem 14 numeros*/
#define email_max  100 /*o maior tem 42*/
#define telefo_max 11  /*11 caracteres*/
#define comuni_max 25  /*o maior tem 25*/
#define endere_max 93  /*o maior tem 93*/
#define tipo_max   17  /*o maior tinha 17*/
#define subpre_max 18  /*o maior tinha 18*/
#define cesta_max  4   /*como já tem numeros de 4 casas no .csv*/

/* ESTRUTURAS */
typedef struct
{
	char Entidade  [enti_max   + 1];
	char CNPJ      [cnpj_max   + 1];
	char Email     [email_max  + 1];
	char Telefone  [telefo_max + 1];
	char Comunidade[comuni_max + 1];
	char Endereco  [endere_max + 1];
	char Tipo      [tipo_max   + 1];
	char Subpre    [subpre_max + 1];
	int Quant_cesta;	
	
} secoes;

/* FUNÇÕES */
void decoracao()  /*muda a cor da tela e habilita acentos*/
{
	system   ("color 0b");
	setlocale(LC_ALL, "");	
}

void erro_malloc(secoes * doc)  /*verifica se malloc deu certo*/
{
	if (doc == NULL)
	{
		printf("Erro na alocação da estrutura");
		exit(0);
	}
}

void erro_fopen(FILE * doc)  /*verifica se fopen deu certo*/
{
	if (doc == NULL)
	{
		printf("Erro ao abrir arquivo");
		exit(0);
	}
}

void ordena_enti(secoes * ONG, int ini, int fim)  /*ordena .dat de entidades com quick_sort*/
{
	//variáveis locais
	int pivo, i, j;
	secoes aux;
	
	//caso o vetor só tenha um numero a função não roda
	if(ini < fim)
	{
		//definição das variáveis
		pivo = fim;
		i    = ini;
		j    = fim;
		
		while(i<j)
		{
			//analisa os numeros do vetor, guardando o que tem que trocar
			while((strcmp(ONG[i].CNPJ, ONG[pivo].CNPJ) <= 0) && i < fim)
			i++;
			while(strcmp(ONG[j].CNPJ, ONG[pivo].CNPJ) > 0)
			j--;
			
			//troca o que tem q trocar
			if(i<j)
			{
				aux    = ONG[i];
				ONG[i] = ONG[j];
				ONG[j] =  aux  ;
			}
		}
		//quando acaba as trocas, muda o pivo
		aux       = ONG[pivo];
		ONG[pivo] =   ONG[i] ;
		ONG[i]    =    aux   ;
		
		//refaz a função nos dois lados do vetor
		ordena_enti(ONG, ini, i-1);
		ordena_enti(ONG, i+1, fim);
	}
}
