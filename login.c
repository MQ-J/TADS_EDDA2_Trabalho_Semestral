/* BIBLIOTECA */
#include "biblio_geral.h"

/* FUNCÕES */
int login(secoes* ONG, int quant, char email[email_max  + 1], char cnpj [cnpj_max   + 1])
{
	int i;
	
	for (i=0; i<quant; i++)
	{
		printf("Comparando CNPJ: %s com %s\n", ONG[i].CNPJ, cnpj);
		printf("Comparando EMAIL: %s com %s\n\n", ONG[i].Email, email);
		
		if((ONG[i].CNPJ == cnpj) && (ONG[i].Email == email)) /*verifica senhas*/
		return(0);                                           /*autoriza acesso*/
	}
	return(1); /*não autoriza acesso*/
}

void consulta(secoes* ONG, int quant)
{
	int i;
	
	for (i=0; i<quant; i++)
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

	//preenche estrutura
	limpa_estrutura_malloc(ONG);            /*limpa estrutura*/
	fseek(dat, 0, SEEK_SET);                /*para o fread funcionar*/
	fread(ONG, sizeof(secoes), quant, dat); /*copia valores do .dat pra a estrutura*/
	fclose(dat);                            /*fecha .dat*/
	
	//menu
	do
	{
		system("cls");
		printf("AÇÃO SOCIAL CIDADE SOLIDÁRIA\n");
		printf("----------------------------\n");
		printf("digite seu email: ");                fflush(stdin);  gets(email);
		printf("Digite o cnpj [somente números]: "); fflush(stdin);  gets(cnpj);	
	}
	while(login(ONG, quant, email, cnpj) != 0);

	consulta(ONG, quant); /*chama a consulta*/
	
	free(ONG); /*libera o espaço alocado*/
	
	return(0);
}
