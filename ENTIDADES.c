/* BIBLIOTECA */
#include "biblio_geral.h"

/* FUNÇÕES */
void consulta_entidade(void); //operação de consulta
void limpa_entidade   (void); //previnir lixo de memória
void preenche_entidade(void); //operação de cadastro
void confirma_entidade(void); //operação de cadastro

/* VARIÁVEL DAS ESTRUTURAS */
secoes ONG;

/* CORPO DO PROGRAMA */
int main()
{
	//cor da tela e acentos
	decoracao();
	
	//variáveis
	char op;
	
	//menu
	do
	{
		system("cls");
		printf("------------------------------\n");
		printf("          ENTIDADES           \n");
		printf("------------------------------\n");
		printf("1 - Consulta\n");
		printf("2 - Cadastro\n");
		printf("3 - Reseta lista de entidades\n");
		printf("0 - Voltar ao menu\n");
		fflush(stdin); scanf("%c", &op);
		switch(op)
		{
			case '1': consulta_entidade(); break;
			case '2': limpa_entidade(); preenche_entidade(); confirma_entidade(); break;
			case '3': system("converte_csvEntidade.exe"); getch(); break;
			case '0': return(0);
		}
	}
	while(op != 0);
}

void consulta_entidade()
{	
	//variáveis
	secoes * ONG_consulta;
	int quant;
	char CNPJ [cnpj_max   + 1];
	int i;
	
	//malloc da estrutura
	FILE * dat = fopen("OSC.dat", "rb"); erro_fopen(dat); /*abre .dat como binário*/
	fseek(dat, 0, SEEK_END);                              /*para o ftell funcionar*/
	ONG_consulta = (secoes*) malloc(ftell(dat)); erro_malloc(ONG_consulta); /*malloc da estrutura*/
	
	//define numero de estruturas
	quant = ftell(dat) / sizeof(secoes);   //printf("numero de orgs: %i\n\n", quant); getch();
	
	//limpa estrutura
	memset(ONG_consulta->Entidade,   '\0', sizeof(ONG_consulta->Entidade));
	memset(ONG_consulta->CNPJ,       '\0', sizeof(ONG_consulta->CNPJ));
	memset(ONG_consulta->Email,      '\0', sizeof(ONG_consulta->Email));
	memset(ONG_consulta->Telefone,   '\0', sizeof(ONG_consulta->Telefone));
	memset(ONG_consulta->Comunidade, '\0', sizeof(ONG_consulta->Comunidade));
	memset(ONG_consulta->Endereco,   '\0', sizeof(ONG_consulta->Endereco));
	memset(ONG_consulta->Tipo,       '\0', sizeof(ONG_consulta->Tipo));
	memset(ONG_consulta->Subpre,     '\0', sizeof(ONG_consulta->Subpre));
	ONG_consulta->Quant_cesta = 0;

	//preenche estrutura
	fseek(dat, 0, SEEK_SET);                /*para o fread funcionar*/
	fread(ONG_consulta, sizeof(secoes), quant, dat); /*copia valores do .dat pra a estrutura*/
	fclose(dat);                            /*fecha .dat*/
	
	//ordena estrutura
	ordena_enti(ONG_consulta, 0, quant-1);
	
	//pesquisa cnpj
	printf("Qual cnpj vc quer procurar?\n");
	fflush(stdin); gets(CNPJ);
	if (strcmp(CNPJ, "todos") == 0)
	{
		for(i=0; i<=quant; i++)
		{
			printf("\n%s | %s | %s | %s | %s | %s | %s | %s | %i |\n\n", ONG_consulta[i].Entidade, ONG_consulta[i].CNPJ, ONG_consulta[i].Email, ONG_consulta[i].Telefone, ONG_consulta[i].Comunidade, ONG_consulta[i].Endereco, ONG_consulta[i].Tipo, ONG_consulta[i].Subpre, ONG_consulta[i].Quant_cesta);
		}
	}
	else
	{
		for(i=0; i<=quant; i++)
		{
			if (strcmp(CNPJ, ONG_consulta[i].CNPJ) == 0)
			{
				printf("\n%s | %s | %s | %s | %s | %s | %s | %s | %i |", ONG_consulta[i].Entidade, ONG_consulta[i].CNPJ, ONG_consulta[i].Email, ONG_consulta[i].Telefone, ONG_consulta[i].Comunidade, ONG_consulta[i].Endereco, ONG_consulta[i].Tipo, ONG_consulta[i].Subpre, ONG_consulta[i].Quant_cesta);
				break;
			}
			if (strcmp(CNPJ, ONG_consulta[i].CNPJ) != 0 && i == quant)
			printf("Cnpj não encontrado!");
		}
	}
	
	//pausa na tela
	printf("\n\nDigite qualquer tecla para voltar");
	getche();
	
	//libera o espaço alocado
	free(ONG_consulta);
}

void limpa_entidade(void)
{
	memset(ONG.Entidade,   '\0', sizeof(ONG.Entidade));
	memset(ONG.CNPJ,       '\0', sizeof(ONG.CNPJ));
	memset(ONG.Email,      '\0', sizeof(ONG.Email));
	memset(ONG.Telefone,   '\0', sizeof(ONG.Telefone));
	memset(ONG.Comunidade, '\0', sizeof(ONG.Comunidade));
	memset(ONG.Endereco,   '\0', sizeof(ONG.Endereco));
	memset(ONG.Tipo,       '\0', sizeof(ONG.Tipo));
	memset(ONG.Subpre,     '\0', sizeof(ONG.Subpre));
	ONG.Quant_cesta = 0;
}

void preenche_entidade(void)
{
	int i;
	
	printf("Digite o nome da Entidade: ");           fflush(stdin); gets(ONG.Entidade);
	printf("Digite o CNPJ da Entidade: ");           for(i=0; i<cnpj_max; i++)   ONG.CNPJ[i] = getche();     ONG.CNPJ[i] = '\0';
	printf("\nDigite o email da Entidade: ");        fflush(stdin); gets(ONG.Email);
	printf("Digite o telefone da Entidade: ");       for(i=0; i<telefo_max; i++) ONG.Telefone[i] = getche(); ONG.Telefone[i] = '\0';
	printf("\nDigite a comunidade da Entidade: ");   fflush(stdin); gets(ONG.Comunidade);
	printf("Digite o endereço da Entidade: ");       fflush(stdin); gets(ONG.Endereco);
	printf("Digite o tipo da Entidade: ");           fflush(stdin); gets(ONG.Tipo);
	printf("Digite a sub-prefeitura da Entidade: "); fflush(stdin); gets(ONG.Subpre);
	printf("----------------------------\n");
}

void confirma_entidade(void)
{
	char confirma;
	FILE * dat = fopen("OSC.dat", "ab"); erro_fopen(dat);
	
	printf("Salvar entidade? [s = sim] [n = não]\n");
	fflush(stdin); confirma = getchar();
	switch(confirma)
	{
		case 'n': case 'N': break;
		case 's': case 'S': fwrite(&ONG, sizeof(ONG), 1, dat);  break;
		default: printf("opção inválida!\n"); getch(); confirma_entidade();
	}
	fclose(dat);
}
