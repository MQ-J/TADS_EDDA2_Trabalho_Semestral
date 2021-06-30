/* BIBLIOTECA */
#include "biblio_geral.h"

/* VARI�VEIS GLOBAIS */
secoes * ONG;/*ponteiro de estruturas*/
int        i;/*contador do for*/

/* FUNC�ES */
void consulta()
{	
	for (i=0; i<66; i++)                                                           /*como deixar um espa�o padronizado?*/
	{
		printf("\n%s" , ONG[i].Entidade);                                          /*como deixar a apar�ncia bonita?*/
		printf(" %s |", ONG[i].CNPJ);
		printf(" %s |", ONG[i].Email);
		printf(" %s |", ONG[i].Telefone);
		printf(" %s |", ONG[i].Comunidade);
		printf(" %s |", ONG[i].Endereco);
		printf(" %s |", ONG[i].Tipo);
		printf(" %s |", ONG[i].Subpre);
		printf(" %i |", ONG[i].Quant_cesta);
	}
}


/* CORPO DO PROGRAMA */
int main()
{
	//cor da tela e acentos
	decoracao();
	
	//vari�veis locais
	char email[email_max  + 1];
	char cnpj [cnpj_max   + 1];
	
	//malloc da estrutura
	FILE * dat = fopen("OSC.dat", "rb");/*abre .dat como bin�rio*/
	erro_fopen(dat);                    /*verifica erro do fopen*/
	fseek(dat, 0, SEEK_END);            /*para o ftell funcionar*/
	ONG = (secoes*) malloc(ftell(dat)); /*malloc da estrutura*/
	fclose(dat); erro_malloc(ONG);      /*verifica erro do malloc*/


	//preenche estrutura - ERRO: fread n�o v� nada pq fseek levou para o fim do arquivo!
	limpa_estrutura_malloc(ONG);        /*limpa estrutura*/
	fread(&ONG, sizeof(ONG), 1, dat);   /*copia valores do .dat pra a estrutura*/
	fclose(dat);                        /*fecha .dat*/
	
	//menu
	printf("A��O SOCIAL CIDADE SOLID�RIA\n");
	printf("----------------------------\n");
	printf("digite seu email: ");                fflush(stdin);  gets(email);
	printf("Digite o cnpj [somente n�meros]: "); fflush(stdin);  gets(cnpj);

	consulta(); /*chama a consulta*/
	
	free(ONG); /*libera o espa�o alocado*/
	
	return(0);
}
