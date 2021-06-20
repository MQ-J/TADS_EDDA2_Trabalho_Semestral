/* BIBLIOTECAS */
#include <stdio.h>  /*biblioteca padr�o*/
#include <stdlib.h> /*para usar funcao system*/
#include <locale.h> /*para usar funcao setlocale*/
#include <string.h> /*para usar fgets e afins*/

/* DEFINI��ES */
#define enti_max   116 /*o maior tem 116 caracteres*/
#define cnpj_max   14  /*CNPJ tem 14 numeros*/
#define email_max  42  /*o maior tem 42*/
#define telefo_max 11  /*11 caracteres*/
#define comuni_max 25  /*o maior tem 25*/
#define endere_max 93  /*o maior tem 93*/
#define tipo_max   17  /*o maior tinha 17*/
#define subpre_max 18  /*o maior tinha 18*/
#define cesta_max  4/*como j� tem numeros de 4 casas no .csv*/

/* ESTRUTURAS */
typedef struct
{
	char Entidade  [enti_max   + 1];
	char CNPJ      [cnpj_max   + 1];
	char Email     [email_max  + 1];
	char Telefone  [telefo_max + 1];
	char Comunidade[comuni_max + 1];
	char Endereco  [endere_max + 1];
	char Tipo      [tipo_max   + 1];
	char Subpre    [subpre_max + 1];
	int Quant_cesta;	
	
} secoes;

/* FUN��ES */
void decoracao()
{
	system   ("color 0b");
	setlocale(LC_ALL, "");	
}
