/* BIBLIOTECA */
#include "biblio_geral.h"

/* VARIÁVEIS GLOBAIS */
secoes * ONG;/*ponteiro de estruturas*/

/* FUNCÕES */
void consulta()
{
	int i, j;
	
	for (i=0; i<66; i++)
	{
		for(j=0; j<  enti_max; j++) printf("\n\n%c " , ONG[i].Entidade[j]);
		for(j=0; j<  cnpj_max; j++) printf(" %c |", ONG[i].CNPJ[j]);
		for(j=0; j< email_max; j++) printf(" %c |", ONG[i].Email[j]);
		for(j=0; j<telefo_max; j++) printf(" %c |", ONG[i].Telefone[j]);
		for(j=0; j<comuni_max; j++) printf(" %c |", ONG[i].Comunidade[j]);
		for(j=0; j<endere_max; j++) printf(" %c |", ONG[i].Endereco[j]);
		for(j=0; j<  tipo_max; j++) printf(" %c |", ONG[i].Tipo[j]);
		for(j=0; j<subpre_max; j++) printf(" %c |", ONG[i].Subpre[j]);
		printf(" %i |", ONG[i].Quant_cesta);
	}
}


/* CORPO DO PROGRAMA */
int main()
{
	//cor da tela e acentos
	decoracao();
	
	//variáveis locais
	char email[email_max  + 1];
	char cnpj [cnpj_max   + 1];
	
	//malloc da estrutura
	FILE * dat = fopen("OSC.dat", "rb"); erro_fopen(dat); /*abre .dat como binário*/
	fseek(dat, 0, SEEK_END);                              /*para o ftell funcionar*/
	ONG = (secoes*) malloc(ftell(dat)); erro_malloc(ONG); /*malloc da estrutura*/

	//preenche estrutura
	limpa_estrutura_malloc(ONG);        /*limpa estrutura*/
	fseek(dat, -ftell(dat), SEEK_END);  /*para o fread funcionar*/
	fread(&ONG, sizeof(ONG), 1, dat);   /*copia valores do .dat pra a estrutura*/
	fclose(dat);                        /*fecha .dat*/
	
	//menu
	printf("AÇÃO SOCIAL CIDADE SOLIDÁRIA\n");
	printf("----------------------------\n");
	printf("digite seu email: ");                fflush(stdin);  gets(email);
	printf("Digite o cnpj [somente números]: "); fflush(stdin);  gets(cnpj);

	consulta(); /*chama a consulta*/
	
	free(ONG); /*libera o espaço alocado*/
	
	return(0);
}
