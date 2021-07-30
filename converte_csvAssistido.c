/* BIBLIOTECA */
#include "biblio_geral.h"


/* CORPO DO PROGRAMA */
int main()
{
	decoracao();  /*habilita acento e cor do programa*/
	
	secoesAssis Pessoa; /*variável das estruturas*/
	int i;              /*contador para as estruturas*/
	char item;          /*pega os caracteres do .csv para a estrutura*/
	
	FILE * csv = fopen("ASSISTIDOS.csv", "r");  erro_fopen(csv); /*abre .csv para ler*/
	FILE * dat = fopen("ASSISTIDOS.dat", "wb"); erro_fopen(dat); /*cria .dat novo*/
	fseek(csv, 103, SEEK_SET);                                   /*pula o cabeçalho do .csv*/
	
	while(!feof(csv)) /*looping para ler o .csv e copiar para a estrutura*/
	{
		//limpa a estrutura
		memset(Pessoa.NomeCompleto,   '\0', sizeof(Pessoa.NomeCompleto));
		memset(Pessoa.DataNasc,       '\0', sizeof(Pessoa.DataNasc));
		memset(Pessoa.CPF,            '\0', sizeof(Pessoa.CPF));
		memset(Pessoa.Municipio,      '\0', sizeof(Pessoa.Municipio));
		memset(Pessoa.Logradouro,     '\0', sizeof(Pessoa.Logradouro));
		memset(Pessoa.Numero,         '\0', sizeof(Pessoa.Numero));
		memset(Pessoa.Complemento,    '\0', sizeof(Pessoa.Complemento));
		memset(Pessoa.Bairro,         '\0', sizeof(Pessoa.Bairro));
		memset(Pessoa.TelefoneCel,    '\0', sizeof(Pessoa.TelefoneCel));
		Pessoa.PossuiPet = '\0';
		
		//nome completo
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item == EOF) break; /*impede loop infinito do fim do EOF*/
			if (item != ';') Pessoa.NomeCompleto[i] = item;
			i++;
		}
		while(item != ';');
		if (item == EOF) break; /*impede loop infinito do fim do EOF*/
		Pessoa.NomeCompleto[i] = '\0';
		printf("%s ", Pessoa.NomeCompleto);
		
		//data de nascimento
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') Pessoa.DataNasc[i] = item;
			i++;
		}
		while(item != ';');
		Pessoa.DataNasc[i] = '\0';
		printf("%s ", Pessoa.DataNasc);
		
		//cpf
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') Pessoa.CPF[i] = item;
			i++;
		}
		while(item != ';');
		Pessoa.CPF[i] = '\0';
		printf("%s ", Pessoa.CPF);
		
		//município
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') Pessoa.Municipio[i] = item;
			i++;
		}
		while(item != ';');
		Pessoa.Municipio[i] = '\0';
		printf("%s ", Pessoa.Municipio);
		
		//logradouro
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') Pessoa.Logradouro[i] = item;
			i++;
		}
		while(item != ';');
		Pessoa.Logradouro[i] = '\0';
		printf("%s ", Pessoa.Logradouro);
		
		//número
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') Pessoa.Numero[i] = item;
			i++;
		}
		while(item != ';');
		Pessoa.Numero[i] = '\0';
		printf("%s ", Pessoa.Numero);
		
		//complemento
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') Pessoa.Complemento[i] = item;
			i++;
		}
		while(item != ';');
		Pessoa.Complemento[i] = '\0';
		printf("%s ", Pessoa.Complemento);
		
		//bairro
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') Pessoa.Bairro[i] = item;
			i++;
		}
		while(item != ';');
		Pessoa.Bairro[i] = '\0';
		printf("%s ", Pessoa.Bairro);
		
		//telefone celular
		i = 0;
		do
		{
			item = fgetc(csv);
			if (item != ';') Pessoa.TelefoneCel[i] = item;
			i++;
		}
		while(item != ';');
		Pessoa.TelefoneCel[i] = '\0';
		printf("%s ", Pessoa.TelefoneCel);
		
		//possui pet
		Pessoa.PossuiPet = fgetc(csv);
		printf("%c\n\n", Pessoa.PossuiPet);
		item = fgetc(csv); /*lê a quebra de linha e descarta*/
		
		//copia os dados da estrutura no .dat
		fwrite(&Pessoa, sizeof(Pessoa), 1, dat);
	}
	
	fclose(csv); /*fecha o .csv*/
	fclose(dat); /*fecha o .dat*/
	
	
	return(0);
}
