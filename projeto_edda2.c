/*BIBLIOTECAS*/
#include <stdio.h>     //default
#include <stdlib.h>    //para usar função system
#include <locale.h>    //para poder usar acentos
#include "decoracao.h" //bibloteca pessoal para decoração do código

/*VARIÁVEIS GLOBAIS*/
char op;

/*INICIO*/
int main()
{
	system("mode 56, 30");
	cabecalho();
	setlocale(LC_ALL,"");
	
	printf("\n\n                       BOM DIA!");
	printf("\n  ESCOLHA SUAS OPÇÕES:");
	printf("\n* lista de médicos.......[digite 1]");
	printf("\n* lista de vacinas.......[digite 2]");
	printf("\n* encerrar seção.........[digite 3]");
	printf("\n");  scanf("%c", &op);  fflush(stdin);
	
	switch (op)
	{
		case '1': break;
		case '2': break;
		case '3': break;
		default: main();
	}
	
	return (0);
}
