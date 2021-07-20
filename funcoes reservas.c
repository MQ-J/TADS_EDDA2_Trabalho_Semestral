//primeira vers�o - busca bin�ria
int login(secoes* ONG, int quant, char email[email_max  + 1], char cnpj [cnpj_max   + 1])
{
	int i;          /*para o loop do for*/
	int metade;     /*divide vetor em dois*/
	
	metade = quant/2;
	
	if (strcmp(cnpj, ONG[metade].CNPJ) == 0)
	{
		if (strcmp(email, ONG[metade].Email) == 0) return(2);
		return(1);
	}
	
	if (strcmp(cnpj, ONG[metade].CNPJ) < 0)
	login(secoes* ONG, metade-1, email, cnpj);
	if (strcmp(cnpj, ONG[metade].CNPJ) > 0)
	login(secoes* ONG, metade+1, email, cnpj);
}


//original - sem busca bin�ria
int login(secoes* ONG, int quant, char email[email_max  + 1], char cnpj [cnpj_max   + 1])
{
	int i;          /*para o loop do for*/
	int libera = 0; /*contador que libera acesso*/
	
	for(i=0; i<quant; i++)
	{	
		if(strcmp(email, ONG[i].Email) == 0) /*v� se emails s�o iguais*/
		{
			libera++;
			break;
		}
	}
	for(i=0; i<quant; i++)
	{
		if (strcmp(cnpj, ONG[i].CNPJ) == 0) /*v� se cnpj's s�o iguais*/
		{
			libera++;
			break;
		}
	}
	return(libera);
}


//vers�o com gambiarra matem�tica - busca bin�ria
int login(secoes* ONG, int quant, char email[email_max  + 1], char cnpj [cnpj_max   + 1])
{
	int i;                /*para o loop do for*/
	int metade = quant/2; /*para ler o meio da estrutura*/
	int libera;           /*vari�vel que controla o acesso*/
	
	printf("vendo %s e %s\n", cnpj, ONG[metade].CNPJ);
	
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
		libera = 0;                /*n�o libera acesso*/
		}
	}

	if (strcmp(cnpj, ONG[metade].CNPJ) < 0) /*caso cnpj seja menor*/
	{
		libera = login(ONG, metade-1, email, cnpj);
	}
	if (strcmp(cnpj, ONG[metade].CNPJ) > 0) /*caso cnpj seja maior*/
	{
		libera = login(ONG, quant+3, email, cnpj);
	}
	
	return(libera);
}


//erro 3221225725 - n�o achei cnpj
