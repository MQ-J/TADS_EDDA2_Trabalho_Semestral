/* BIBLIOTECA */
#include "biblio_geral.h"

/* FUNÇÕES */
void consulta_entidade(void);  /*operação de consulta*/
void limpa_entidade   (void);  /*previnir lixo de memória*/
void preenche_entidade(void);  /*cadastro - preenche estrutura local*/
void valida_tipo      (char*); /*cadastro - lista de tipos permitidos*/
void valida_subpre    (char*); /*cadastro - lista de subprefeituras permitidas*/
void confirma_entidade(void);  /*cadastro - salva no arquivo .dat*/

/* VARIÁVEIS GLOBAIS */
secoesEnti ONG; /*variável das estruturas*/
int erro;       /*valida dados digitados*/

/* CORPO DO PROGRAMA */
int main()
{
	/*cor da tela e acentos*/
	decoracao();
	
	/*variáveis*/
	char op;
	
	/*menu*/
	do
	{
		system("mode 35, 20");
		system("cls");
		printf("-----------------------------------\n");
		printf("             ENTIDADES             \n");
		printf("-----------------------------------\n");
		printf("1 - Consulta\n");
		printf("2 - Cadastro\n");
		printf("3 - Reseta lista de entidades\n");
		printf("0 - Voltar ao menu\n");
		fflush(stdin); scanf("%c", &op);
		switch(op)
		{
			case '1': consulta_entidade(); break;
			case '2': limpa_entidade(); preenche_entidade(); confirma_entidade(); break;
			case '3': system("mode 50, 465"); system("converte_csvEntidade.exe"); getch(); break;
			case '0': return(0);
		}
	}
	while(op != 0);
}

void consulta_entidade()
{	
	/*variáveis*/
	secoesEnti * ONG_consulta;  /*variável do malloc da estrutura*/
	char CNPJ [cnpj_max   + 1]; /*cnpj que será pesquisado*/
	int quant, i;
	
	/*malloc da estrutura*/
	FILE * dat = fopen("OSC.dat", "rb"); erro_fopen(dat);                            /*abre .dat como binário*/
	fseek(dat, 0, SEEK_END);                                                         /*para o ftell funcionar*/
	ONG_consulta = (secoesEnti*) malloc(ftell(dat)); erro_malloc_enti(ONG_consulta); /*malloc da estrutura*/
	
	/*define numero de estruturas*/
	quant = ftell(dat) / sizeof(secoesEnti);
	
	/*limpa estrutura com malloc*/
	memset(ONG_consulta->Entidade,   '\0', sizeof(ONG_consulta->Entidade));
	memset(ONG_consulta->CNPJ,       '\0', sizeof(ONG_consulta->CNPJ));
	memset(ONG_consulta->Email,      '\0', sizeof(ONG_consulta->Email));
	memset(ONG_consulta->Telefone,   '\0', sizeof(ONG_consulta->Telefone));
	memset(ONG_consulta->Comunidade, '\0', sizeof(ONG_consulta->Comunidade));
	memset(ONG_consulta->Endereco,   '\0', sizeof(ONG_consulta->Endereco));
	memset(ONG_consulta->Tipo,       '\0', sizeof(ONG_consulta->Tipo));
	memset(ONG_consulta->Subpre,     '\0', sizeof(ONG_consulta->Subpre));
	ONG_consulta->Quant_cesta = 0;

	/*preenche estrutura*/
	fseek(dat, 0, SEEK_SET);                             /*para o fread funcionar*/
	fread(ONG_consulta, sizeof(secoesEnti), quant, dat); /*copia valores do .dat pra a estrutura*/
	fclose(dat);                                         /*fecha .dat*/
	
	/*ordena estrutura*/
	ordena_enti(ONG_consulta, 0, quant-1);
	
	/*pesquisa cnpj*/
	printf("Qual cnpj vc quer procurar?\n");
	fflush(stdin); gets(CNPJ);
	if (strcmp(CNPJ, "todos") == 0)
	{
		system("mode 50, 500");
		for(i=0; i<quant; i++)
		{
			printf("\n%s | %s | %s | %s | %s | %s | %s | %s | %i |\n\n", ONG_consulta[i].Entidade, ONG_consulta[i].CNPJ, ONG_consulta[i].Email, ONG_consulta[i].Telefone, ONG_consulta[i].Comunidade, ONG_consulta[i].Endereco, ONG_consulta[i].Tipo, ONG_consulta[i].Subpre, ONG_consulta[i].Quant_cesta);
		}
	}
	else
	{
		for(i=0; i<quant; i++)
		{
			if (strcmp(CNPJ, ONG_consulta[i].CNPJ) == 0)
			{
				printf("\n%s | %s | %s | %s | %s | %s | %s | %s | %i |", ONG_consulta[i].Entidade, ONG_consulta[i].CNPJ, ONG_consulta[i].Email, ONG_consulta[i].Telefone, ONG_consulta[i].Comunidade, ONG_consulta[i].Endereco, ONG_consulta[i].Tipo, ONG_consulta[i].Subpre, ONG_consulta[i].Quant_cesta);
				break;
			}
			if (strcmp(CNPJ, ONG_consulta[i].CNPJ) != 0 && i == quant-1)
			printf("Cnpj não encontrado!");
		}
	}
	
	/*pausa na tela*/
	printf("\n\nDigite qualquer tecla para voltar");
	getche();
	
	/*libera o espaço alocado*/
	free(ONG_consulta);
}

void limpa_entidade(void)
{
	/*limpa estrutura*/
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
	/*variáveis*/
	int i;
	erro = 0;
	
	/*pede dados da nova entidade*/
	system("mode 100, 12");
	printf("Nome da Entidade: "); fflush(stdin); gets(ONG.Entidade);
	printf("CNPJ:             "); for(i=0; i<cnpj_max; i++)   ONG.CNPJ[i] = getche();     ONG.CNPJ[i] = '\0';
	printf("\nEmail:          "); printf("  ");  fflush(stdin); gets(ONG.Email);
	printf("Telefone:     	  "); for(i=0; i<telefo_max; i++) ONG.Telefone[i] = getche(); ONG.Telefone[i] = '\0';
	printf("\nComunidade:     "); printf("  ");  fflush(stdin); gets(ONG.Comunidade);
	printf("Endereço:         "); fflush(stdin); gets(ONG.Endereco);
	printf("Tipo:             "); fflush(stdin); valida_tipo(gets(ONG.Tipo));
	printf("Sub-prefeitura:   "); fflush(stdin); valida_subpre(gets(ONG.Subpre));
	printf("----------------------------\n");
	
	/*caso dados inválidos sejam deletados*/
	switch(erro)
	{
		case 1: printf("tipo inválido\n\n");                  getch(); preenche_entidade(); break;
		case 2: printf("subprefeitura inválida\n\n");         getch(); preenche_entidade(); break;
		case 3: printf("tipo e subprefeitura inválidos\n\n"); getch(); preenche_entidade(); break;
	}
}

void valida_tipo(char * tipo)
{
	/*variáveis*/
	int i, soma = 0;
	
	/*soma os caracteres digitados...*/
	for(i=0; i<=tipo_max; i++)
	soma = soma + tipo[i];
	
	/*...e verifica se é igual às somas cadastradas*/
	switch(soma)
	{
		case 625:  /*Idosos*/
		case 591:  /*Favela*/	                  case 370:  /*LGBTI*/
		case 503:  /*Cortiço*/                    case 652:  /*Outros*/
		case 1048: /*Loteamento*/                 case 436:  /*Ocupação*/
		case 1659: /*Grupo de mulheres*/          case 1680: /*Comunidade indígena*/
		case 1793: /*Criança e adolescente*/      case 2020: /*Pessoas com deficiência*/
		case 2083: /*Pessoas em situação de rua*/ case 2155: /*Imigrantes/refugiados*/
		case 2058: /*Minorias étnico-raciais*/    case 2885: /*Egressos do sistema prisional*/
		break;
		default: erro = erro + 1;
	}
}

void valida_subpre(char * subpre)
{
	/*variáveis*/
	int i, soma = 0;
	
	/*soma os caracteres digitados...*/
	for(i=0; i<=subpre_max; i++)
	soma = soma + subpre[i];
	
	/*...e verifica se é igual às somas cadastradas*/
	switch(soma)
	{
		case 1022: /*Aricanduva*/        case 564:  /*Butantã*/
		case 1041: /*Campo Limpo*/       case 1600: /*Capela do Socorro*/
		case 910:  /*Casa Verde*/        case 1188: /*Cidade Ademar*/
		case 1645: /*Cidade Tiradentes*/ case 1812: /*Ermelino Matarazzo*/
		case 1166: /*Freguesia do Ó*/    case 1025: /*Guaianases*/
		case 811:  /*Ipiranga*/          case 1367: /*Itaim Paulista*/
		case 828:  /*Itaquera*/          case 904:  /*Jabaquara*/
		case 836:  /*Jaçanã/Tremembé*/   case 382:  /*Lapa*/
		case 940:  /*M'Boi Mirim*/       case 495:  /*Mooca*/
		case 1150: /*Parelheiros*/       case 492:  /*Penha*/
		case 527:  /*Perus*/             case 945:  /*Pinheiros*/
		case 1385: /*Pirituba/Jaraguá*/  case 1628: /*Santana/Tucuruvi*/
		case 1045: /*Santo Amaro*/       case 791:  /*São Mateus*/
		case 779:  /*São Miguel*/        case 920:  /*Sapopemba*/
		case -43:  /*Sé*/                case 2323: /*Vila Maria/Vila Guilherme*/
		case 1125: /*Vila Mariana*/      case 1267: /*Vila Prudente*/
		break;
		default: erro = erro + 2;
	}
}

void confirma_entidade(void)
{
	/*variáveis e abertura de arquivo*/
	char confirma;
	FILE * dat = fopen("OSC.dat", "ab"); erro_fopen(dat);
	
	/*salva entidade no  arquivo ou não*/
	printf("Salvar entidade? [s = sim] [n = não]\n");
	fflush(stdin); confirma = getchar();
	switch(confirma)
	{
		case 'n': case 'N': break;
		case 's': case 'S': fwrite(&ONG, sizeof(ONG), 1, dat);  break;
		default: printf("opção inválida!\n"); getch(); confirma_entidade();
	}
	
	/*fecha arquivo*/
	fclose(dat);
}
