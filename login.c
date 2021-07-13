/* BIBLIOTECA */
#include "biblio_geral.h"

/* FUNCÕES */
int login(secoes* ONG, int quant, char email[email_max  + 1], char cnpj [cnpj_max   + 1])
{
	int i;          /*para o loop do for*/
	int libera = 0; /*contador que libera acesso*/
	
	for(i=0; i<quant; i++)
	{	
		if(strcmp(email, ONG[i].Email) == 0) /*vê se emails são iguais*/
		{
			libera++;
			break;
		}
	}
	for(i=0; i<quant; i++)
	{
		if (strcmp(cnpj, ONG[i].CNPJ) == 0) /*vê se cnpj's são iguais*/
		{
			libera++;
			break;
		}
	}
	return(libera);
}

void consulta(secoes* ONG, int quant)
{
	int i; /*para o loop do for*/
	
	for (i=0; i<quant; i++) /*mostra as seções de cada entidade*/
	{
		printf("\n\n%s |" , ONG[i].Entidade);
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
	
	//variáveis locais
	secoes * ONG;               /*ponteiro de estruturas*/
	int quant;                  /*quantidade de organizações no .dat*/
	char email[email_max  + 1]; /*para login no sistema*/
	char cnpj [cnpj_max   + 1]; /*para login no sistema*/
	
	//malloc da estrutura
	FILE * dat = fopen("OSC.dat", "rb"); erro_fopen(dat); /*abre .dat como binário*/
	fseek(dat, 0, SEEK_END);                              /*para o ftell funcionar*/
	ONG = (secoes*) malloc(ftell(dat)); erro_malloc(ONG); /*malloc da estrutura*/
	
	//define numero de estruturas
	quant = ftell(dat) / sizeof(secoes);   /*debug printf("numero de orgs: %i\n\n", quant);*/
	
	//limpa estrutura
	memset(ONG->Entidade,   '\0', sizeof(ONG->Entidade));
	memset(ONG->CNPJ,       '\0', sizeof(ONG->CNPJ));
	memset(ONG->Email,      '\0', sizeof(ONG->Email));
	memset(ONG->Telefone,   '\0', sizeof(ONG->Telefone));
	memset(ONG->Comunidade, '\0', sizeof(ONG->Comunidade));
	memset(ONG->Endereco,   '\0', sizeof(ONG->Endereco));
	memset(ONG->Tipo,       '\0', sizeof(ONG->Tipo));
	memset(ONG->Subpre,     '\0', sizeof(ONG->Subpre));
	ONG->Quant_cesta = 0;

	//preenche estrutura
	fseek(dat, 0, SEEK_SET);                /*para o fread funcionar*/
	fread(ONG, sizeof(secoes), quant, dat); /*copia valores do .dat pra a estrutura*/
	fclose(dat);                            /*fecha .dat*/
	
	//menu de login
	do
	{
		system("cls");
		printf("AÇÃO SOCIAL CIDADE SOLIDÁRIA\n");
		printf("----------------------------\n");
		printf("digite seu email: ");                fflush(stdin);  gets(email);
		printf("Digite o cnpj [somente números]: "); fflush(stdin);  gets(cnpj);	
	}
	while(login(ONG, quant, email, cnpj) != 2);

	consulta(ONG, quant); /*chama a consulta*/
	
	free(ONG); /*libera o espaço alocado*/
	
	return(0);
}
