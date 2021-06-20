/* BIBLIOTECA */
#include "biblio_geral.h"

/* CORPO DO PROGRAMA */
int main()
{
	decoracao();  /*habilita acento e cor do programa*/
	
	secoes ONG;    /*vetor de 66 estruturas dessas*/
	int i;         /*contador para o vetor das estruturas*/
	char item;     /*pega os caracteres do .csv para a estrutura*/
	char quant[5]; /*m�ximo de 1000 cestas*/
	
	
	FILE * csv = fopen("OSC.csv", "r"); /*abre para ler*/
	FILE * dat = fopen("OSC.dat", "wb");/*abre como bin�rio*/
	fseek(csv, 112, SEEK_SET);          /*pula o cabe�alho do .csv*/
	
	while(!feof(csv)) /*looping para ler o .csv e copiar para a estrutura*/
	{
		//limpa a estrutura
		memset(ONG.Entidade,   '\0', sizeof(ONG.Entidade));
		memset(ONG.CNPJ,       '\0', sizeof(ONG.CNPJ));
		memset(ONG.Email,      '\0', sizeof(ONG.Email));
		memset(ONG.Telefone,   '\0', sizeof(ONG.Telefone));
		memset(ONG.Comunidade, '\0', sizeof(ONG.Comunidade));
		memset(ONG.Endereco,   '\0', sizeof(ONG.Endereco));
		memset(ONG.Tipo,       '\0', sizeof(ONG.Tipo));
		memset(ONG.Subpre,     '\0', sizeof(ONG.Subpre));
		ONG.Quant_cesta = 0;
		
		//entidade
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') ONG.Entidade[i] = item;
			i++;
		}
		while(item != ';');
		ONG.Entidade[i] = '\0';
		printf("%s ", ONG.Entidade);
		
		//cnpj
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') ONG.CNPJ[i] = item;
			i++;
		}
		while(item != ';');
		ONG.CNPJ[i] = '\0';
		printf("%s ", ONG.CNPJ);
		
		//email
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') ONG.Email[i] = item;
			i++;
		}
		while(item != ';');
		ONG.Email[i] = '\0';
		printf("%s ", ONG.Email);
		
		//telefone
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') ONG.Telefone[i] = item;
			i++;
		}
		while(item != ';');
		ONG.Telefone[i] = '\0';
		printf("%s ", ONG.Telefone);

		//comunidade
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') ONG.Comunidade[i] = item;
			i++;
		}
		while(item != ';');
		ONG.Comunidade[i] = '\0';
		printf("%s ", ONG.Comunidade);
		
		//endere�o
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') ONG.Endereco[i] = item;
			i++;
		}
		while(item != ';');
		ONG.Endereco[i] = '\0';
		printf("%s ", ONG.Endereco);
		
		//tipo
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') ONG.Tipo[i] = item;
			i++;
		}
		while(item != ';');
		ONG.Tipo[i] = '\0';
		printf("%s ", ONG.Tipo);
		
		//subprefeitura
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') ONG.Subpre[i] = item;
			i++;
		}
		while(item != ';');
		ONG.Subpre[i] = '\0';
		printf("%s ", ONG.Subpre);
		
		//cestas
		for(i=0; i<=cesta_max; i++)
		{
			item = fgetc(csv);
			if (item != ';' && item != '\n' && item != EOF && item != '\0') quant[i] = item;
		}
		quant[i] = '\0';
		ONG.Quant_cesta = atoi(quant);
		printf("%i\n\n", ONG.Quant_cesta);
		
		//copia os dados da estrutura no .dat
		fwrite(&ONG, sizeof(ONG), 1, dat);
	}
	
	fclose(csv); /*fecha o .csv*/
	fclose(dat); /*fecha o .dat*/
	
	
	return(0);
}