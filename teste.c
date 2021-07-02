#include "biblio_geral.h"
#include <windows.h>

secoes * ONG;
int i, j;
char item;
char quant[5];


void preenche_Quant_cesta(FILE * dat)
{
	for(j=0; j<cesta_max; j++)
	{
		item = fgetc(dat);
		if (item != ';' && item != '\n' && item != EOF && item != '\0') quant[i] = item;
	}
	quant[i] = '\0';
	ONG[i].Quant_cesta = atoi(quant);
	printf("%i\n\n", ONG[i].Quant_cesta);
	
}

void preenche_Subpre(FILE * dat)
{
	for(j=0; j<subpre_max; j++)
	{
		item = fgetc(dat);
		if (item == ';') preenche_Quant_cesta(dat);
		ONG[i].Subpre[j] = item;
		printf("%c", ONG[i].Subpre[j]);
	}
}

void preenche_Tipo(FILE * dat)
{
	for(j=0; j<tipo_max; j++)
	{
		item = fgetc(dat);
		if (item == ';') preenche_Subpre(dat);
		ONG[i].Tipo[j] = item;
		printf("%c", ONG[i].Tipo[j]);
	}
}

void preenche_Endereco(FILE * dat)
{
	for(j=0; j<endere_max; j++)
	{
		item = fgetc(dat);
		if (item == ';') preenche_Tipo(dat);
		ONG[i].Endereco[j] = item;
		printf("%c", ONG[i].Endereco[j]);
	}
}

void preenche_Comunidade(FILE * dat)
{
	for(j=0; j<comuni_max; j++)
	{
		item = fgetc(dat);
		if (item == ';') preenche_Endereco(dat);
		ONG[i].Comunidade[j] = item;
		printf("%c", ONG[i].Comunidade[j]);
	}
}

void preenche_Telefone(FILE * dat)
{
	for(j=0; j<telefo_max; j++)
	{
		item = fgetc(dat);
		if (item == ';') preenche_Comunidade(dat);
		ONG[i].Telefone[j] = item;
		printf("%c", ONG[i].Telefone[j]);
	}
}

void preenche_Email(FILE * dat)
{
	for(j=0; j<email_max; j++)
	{
		item = fgetc(dat);
		if (item == ';') preenche_Telefone(dat);
		ONG[i].Email[j] = item;
		printf("%c", ONG[i].Email[j]);
	}
}

void preenche_CNPJ(FILE * dat)
{
	for(j=0; j<cnpj_max; j++)
	{
		item = fgetc(dat);
		if (item == ';') preenche_Email(dat);
		ONG[i].CNPJ[j] = item;
		printf("%c", ONG[i].CNPJ[j]);
	}
}

void preenche_Entidade(FILE * dat)
{
	for(j=0; j<enti_max; j++)
	{
		item = fgetc(dat);
		if (item == ';') preenche_CNPJ(dat);
		ONG[i].Entidade[j] = item;
		printf("%c", ONG[i].Entidade[j]);
	}
}

int main()
{	
	decoracao();

	//malloc da estrutura
	FILE * dat = fopen("OSC.csv", "rb"); erro_fopen(dat); /*abre .dat como binário*/
	fseek(dat, 0, SEEK_END);                              /*para o ftell funcionar*/
	ONG = (secoes*) malloc(ftell(dat)); erro_malloc(ONG); /*malloc da estrutura*/
	
	//preenche estrutura
	limpa_estrutura_malloc(ONG);        /*limpa estrutura*/
	fseek(dat, -ftell(dat), SEEK_END);  /*para o fread funcionar*/
	while(!feof(dat))                   /*loop que preenche estrutura*/
	{	
		for (i=0; i<66; i++) 
		preenche_Entidade(dat);
	}
	
	
	fclose(dat);                        /*fecha .dat*/
	
	for (i=0; i<66; i++)
	{
		printf("\n\n");
		for(j=0; j<  enti_max; j++) printf("%c" , ONG[i].Entidade[j]);
		printf("\n");
		for(j=0; j<  cnpj_max; j++) printf("%c", ONG[i].CNPJ[j]);
		printf("\n");
		for(j=0; j< email_max; j++) printf("%c", ONG[i].Email[j]);
		printf("\n");
		for(j=0; j<telefo_max; j++) printf("%c", ONG[i].Telefone[j]);
		printf("\n");
		for(j=0; j<comuni_max; j++) printf("%c", ONG[i].Comunidade[j]);
		printf("\n");
		for(j=0; j<endere_max; j++) printf("%c", ONG[i].Endereco[j]);
		printf("\n");
		for(j=0; j<  tipo_max; j++) printf("%c", ONG[i].Tipo[j]);
		printf("\n");
		for(j=0; j<subpre_max; j++) printf("%c", ONG[i].Subpre[j]);
		printf("\n");
		printf("%i", ONG[i].Quant_cesta);
	}
	
	return (0);
}
