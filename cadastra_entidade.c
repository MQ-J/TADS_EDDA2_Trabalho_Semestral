/* BIBLIOTECA */
#include "biblio_geral.h"

/* FUNÇÕES */
void limpa_entidade(void);
void preenche_entidade(void);
void confirma_entidade(void);

/* VARIÁVEL DAS ESTRUTURAS */
secoes ONG;

/* CORPO DO PROGRAMA */
int main()
{
	//cor da tela e acentos
	decoracao();
	
	//variáveis
	char cadastra;
	
	//menu
	do
	{
		system("cls");
		printf("----------------------------\n");
		printf("           CADASTRO         \n");
		printf("----------------------------\n");
		limpa_entidade();
		preenche_entidade();
		confirma_entidade();
		printf("Cadastrar outra entidade? [s = sim] [n = não]\n");
		fflush(stdin); cadastra = getchar();
	}
	while (cadastra == 's' || cadastra == 'S');
	
	return(0);
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
