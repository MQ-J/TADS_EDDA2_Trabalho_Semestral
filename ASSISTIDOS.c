/* BIBLIOTECA */
#include "biblio_geral.h"

/* FUNÇÕES */
void consulta_assistido(void); /*operação de consulta*/
void limpa_assistido   (void); /*previnir lixo de memória*/
void preenche_assistido(void); /*cadastro - preenche estrutura local*/
void confirma_assistido(void); /*cadastro - salva no arquivo .dat*/

/* VARIÁVEL DA ESTRUTURA */
secoesAssis Pessoa;

/* CORPO DO PROGRAMA */
int main()
{
	/*cor da tela e acentos*/
	decoracao();
	
	/*variáveis locais*/
	char op;
	
	/*menu*/
	do
	{
		system("cls");
		printf("------------------------------\n");
		printf("          ASSISTIDOS          \n");
		printf("------------------------------\n");
		printf("1 - Consulta\n");
		printf("2 - Cadastro\n");
		printf("3 - Reseta lista de assistidos\n");
		printf("0 - Voltar ao menu\n");
		fflush(stdin); scanf("%c", &op);
		switch(op)
		{
			case '1': consulta_assistido(); break;
			case '2': limpa_assistido(); preenche_assistido(); confirma_assistido(); break;
			case '3': system("converte_csvAssistido.exe"); getch(); break;
			case '0': return(0);
		}
	}
	while(op != 0);
}

void consulta_assistido()
{
	/*variáveis locais*/
	secoesAssis * Pessoa_consulta;
	int quant;
	char CPF [cpf_max   + 1];
	int i;
	
	/*malloc da estrutura*/
	FILE * dat = fopen("ASSISTIDOS.dat", "rb"); erro_fopen(dat);                             /*abre .dat como binário*/
	fseek(dat, 0, SEEK_END);                                                                 /*para o ftell funcionar*/
	Pessoa_consulta = (secoesAssis*) malloc(ftell(dat)); erro_malloc_assis(Pessoa_consulta); /*malloc da estrutura*/
	
	/*define numero de estruturas*/
	quant = ftell(dat) / sizeof(secoesAssis);
	
	/*limpa estrutura*/
	memset(Pessoa_consulta->NomeCompleto, '\0', sizeof(Pessoa_consulta->NomeCompleto));
	memset(Pessoa_consulta->DataNasc,     '\0', sizeof(Pessoa_consulta->DataNasc));
	memset(Pessoa_consulta->CPF,          '\0', sizeof(Pessoa_consulta->CPF));
	memset(Pessoa_consulta->Municipio,    '\0', sizeof(Pessoa_consulta->Municipio));
	memset(Pessoa_consulta->Logradouro,   '\0', sizeof(Pessoa_consulta->Logradouro));
	memset(Pessoa_consulta->Numero,       '\0', sizeof(Pessoa_consulta->Numero));
	memset(Pessoa_consulta->Complemento,  '\0', sizeof(Pessoa_consulta->Complemento));
	memset(Pessoa_consulta->Bairro,       '\0', sizeof(Pessoa_consulta->Bairro));
	memset(Pessoa_consulta->TelefoneCel,  '\0', sizeof(Pessoa_consulta->TelefoneCel));
	Pessoa_consulta->PossuiPet = '\0';
	
	/*preenche estrutura*/
	fseek(dat, 0, SEEK_SET);                                 /*para o fread funcionar*/
	fread(Pessoa_consulta, sizeof(secoesAssis), quant, dat); /*copia valores do .dat pra a estrutura*/
	fclose(dat);                                             /*fecha .dat*/
	
	/*ordena estrutura*/
	ordena_assis(Pessoa_consulta, 0, quant-1);
	
	/*pesquisa cpf*/
	printf("Qual cpf vc quer procurar?\n");
	fflush(stdin); gets(CPF);
	if (strcmp(CPF, "todos") == 0)
	{
		for(i=0; i<quant; i++)
		{
			printf("\n%s | %s | %s | %s | %s | %s | %s | %s | %s | %c |\n\n", Pessoa_consulta[i].NomeCompleto, Pessoa_consulta[i].DataNasc, Pessoa_consulta[i].CPF, Pessoa_consulta[i].Municipio, Pessoa_consulta[i].Logradouro, Pessoa_consulta[i].Numero, Pessoa_consulta[i].Complemento, Pessoa_consulta[i].Bairro, Pessoa_consulta[i].TelefoneCel, Pessoa_consulta[i].PossuiPet);
		}
	}
	else
	{
		for(i=0; i<quant; i++)
		{
			if (strcmp(CPF, Pessoa_consulta[i].CPF) == 0)
			{
				printf("\n%s | %s | %s | %s | %s | %s | %s | %s | %s | %c |", Pessoa_consulta[i].NomeCompleto, Pessoa_consulta[i].DataNasc, Pessoa_consulta[i].CPF, Pessoa_consulta[i].Municipio, Pessoa_consulta[i].Logradouro, Pessoa_consulta[i].Numero, Pessoa_consulta[i].Complemento, Pessoa_consulta[i].Bairro, Pessoa_consulta[i].TelefoneCel, Pessoa_consulta[i].PossuiPet);
				break;
			}
			if (strcmp(CPF, Pessoa_consulta[i].CPF) != 0 && i == quant-1)
			printf("Cnpj não encontrado!");
		}
	}
	
	/*pausa na tela*/
	printf("\n\nDigite qualquer tecla para voltar");
	getche();
	
	/*libera o espaço alocado*/
	free(Pessoa_consulta);
}

void limpa_assistido(void)
{
	/*limpa estrutura*/
	memset(Pessoa.NomeCompleto, '\0', sizeof(Pessoa.NomeCompleto));
	memset(Pessoa.DataNasc,     '\0', sizeof(Pessoa.DataNasc));
	memset(Pessoa.CPF,          '\0', sizeof(Pessoa.CPF));
	memset(Pessoa.Municipio,    '\0', sizeof(Pessoa.Municipio));
	memset(Pessoa.Logradouro,   '\0', sizeof(Pessoa.Logradouro));
	memset(Pessoa.Numero,       '\0', sizeof(Pessoa.Numero));
	memset(Pessoa.Complemento,  '\0', sizeof(Pessoa.Complemento));
	memset(Pessoa.Bairro,       '\0', sizeof(Pessoa.Bairro));
	memset(Pessoa.TelefoneCel,  '\0', sizeof(Pessoa.TelefoneCel));
	Pessoa.PossuiPet = '\0';
}

void preenche_assistido(void)
{
	/*variáveis locais*/
	int i;
	
	/*pede dados do novo assistido*/
	printf("Nome completo:          "); fflush(stdin); gets(Pessoa.NomeCompleto);
	printf("Data de nascimento:     "); for(i=0; i<data_max; i++)                Pessoa.DataNasc[i] = getche(); Pessoa.DataNasc[i] = '\0';
	printf("\nCPF:                  "); printf("  ");  for(i=0; i<cpf_max; i++)  Pessoa.CPF[i] = getche();      Pessoa.CPF[i] = '\0';
	printf("\nMunicípio:            "); printf("  ");  fflush(stdin); gets(Pessoa.Municipio);
	printf("Logradouro:             "); fflush(stdin); gets(Pessoa.Logradouro);
	printf("Número:                 "); fflush(stdin); gets(Pessoa.Numero);
	printf("Complemento:            "); fflush(stdin); gets(Pessoa.Complemento);
	printf("Bairro:                 "); fflush(stdin); gets(Pessoa.Bairro);
	printf("Telefone celular:       "); for(i=0; i<telecel_max; i++) Pessoa.TelefoneCel[i] = getche(); Pessoa.TelefoneCel[i] = '\0';
	printf("\nPossui pet? [S ou N]: "); printf("  ");  fflush(stdin); scanf("%c", &Pessoa.PossuiPet);
	printf("----------------------------\n");
}

void confirma_assistido(void)
{
	/*variáveis locais e abertura do arquivo*/
	char confirma;
	FILE * dat = fopen("ASSISTIDOS.dat", "ab"); erro_fopen(dat);
	
	/*salva assistido no arquivo ou não*/
	printf("Salvar assistido? [s = sim] [n = não]\n");
	fflush(stdin); confirma = getchar();
	switch(confirma)
	{
		case 'n': case 'N': break;
		case 's': case 'S': fwrite(&Pessoa, sizeof(Pessoa), 1, dat);  break;
		default: printf("opção inválida!\n"); getch(); confirma_assistido();
	}
	
	/*fecha arquivo*/
	fclose(dat);
}
