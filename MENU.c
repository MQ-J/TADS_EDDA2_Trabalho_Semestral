/* BIBLIOTECA */
#include "biblio_geral.h"

/* VARIÁVEIS GLOBAIS */
secoesEnti * ONG; /*ponteiro de estruturas*/
int quant;    /*quantidade de organizações no .dat*/

/* FUNCÕES */
void organiza_entidade(void);
int login(int quant, char email[email_max  + 1], char cnpj [cnpj_max   + 1]);

/* CORPO DO PROGRAMA */
int main()
{
	//cor da tela e acentos
	decoracao();
	
	//variáveis locais
	char email[email_max  + 1]; /*para login no sistema*/
	char cnpj [cnpj_max   + 1]; /*para login no sistema*/
	char op; int loop;          /*controlam opções do sistema*/
	
	//faz malloc e organiza entidades
	organiza_entidade();
	
	//menu de login
	do
	{
		system("cls");
		printf("AÇÃO SOCIAL CIDADE SOLIDÁRIA\n");
		printf("----------------------------\n");
		printf("Digite seu email: ");                fflush(stdin);  gets(email);
		printf("Digite o cnpj [somente números]: "); fflush(stdin);  gets(cnpj);
	}
	while(login(quant, email, cnpj) != 1);
	
	//menu de opções
	do
	{
		system("cls");
		printf("----------------------------\n");
		printf("AÇÃO SOCIAL CIDADE SOLIDÁRIA\n");
		printf("----------------------------\n");
		printf(" 1 - ENTIDADES\n");
		printf(" 2 - ASSISTIDOS\n");
		printf(" 3 - DONATIVOS\n");
		printf("\n");
		printf(" 9 - ATENDIMENTO\n");
		printf(" 0 - ENCERRAR\n");
		printf("----------------------------\n");
		printf("Digite a opção escolhida: ");
		fflush(stdin); scanf("%c", &op);
		switch(op)
		{
			case '1': system("ENTIDADES.exe"); break;
			case '2': system("ASSISTIDOS.exe"); break;
			case '3': break;
			case '9': break;
			case '0': loop = 1; break;
		}
	}
	while(loop != 1);
	
	return(0);
}

void organiza_entidade()
{
	//malloc da estrutura
	FILE * dat = fopen("OSC.dat", "rb"); erro_fopen(dat); /*abre .dat como binário*/
	fseek(dat, 0, SEEK_END);                              /*para o ftell funcionar*/
	ONG = (secoesEnti*) malloc(ftell(dat)); erro_malloc_enti(ONG); /*malloc da estrutura*/
	
	//define numero de estruturas
	quant = ftell(dat) / sizeof(secoesEnti);   //printf("numero de orgs: %i\n\n", quant); getch();
	
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
	fread(ONG, sizeof(secoesEnti), quant, dat); /*copia valores do .dat pra a estrutura*/
	fclose(dat);                            /*fecha .dat*/
	
	//ordena estrutura
	ordena_enti(ONG, 0, quant-1);
	
	//libera o espaço alocado
	free(ONG);
}

int login(int quant, char email[email_max  + 1], char cnpj [cnpj_max   + 1])
{
	int metade = quant/2; /*para ler o meio da estrutura*/
	int libera;           /*variável que controla o acesso*/
	
	printf("vendo %s e %s\n", cnpj, ONG[metade].CNPJ); /*debug*/
	
	if (strcmp(cnpj, ONG[metade].CNPJ) == 0) /*caso o cnpj esteja no meio*/
	{
		if (strcmp(email, ONG[metade].Email) == 0)
		{
			printf("Achei!"); getch(); /*debug*/
			libera = 1;                /*libera acesso*/
		}
		else
		{
		printf("Senha errada!"); getch(); /*debug*/
		libera = 0;                /*não libera acesso*/
		}
	}

	if (strcmp(cnpj, ONG[metade].CNPJ) < 0) /*caso cnpj seja menor*/
	{
		libera = login(metade-1, email, cnpj);
	}
	if (strcmp(cnpj, ONG[metade].CNPJ) > 0) /*caso cnpj seja maior*/
	{
		libera = login(quant+3, email, cnpj);
	}
	
	return(libera);
}
