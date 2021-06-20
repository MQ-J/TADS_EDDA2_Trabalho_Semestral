/* BIBLIOTECA */
#include "biblio_geral.h"

/* CORPO DO PROGRAMA */
int main()
{
	decoracao(); /*habilita acento e cor do programa*/
	
	secoes ONG[66]; /*vetor de 66 estruturas, mas tenho que usar MALLOC!*/
	int i;          /*contador do for*/
	
	FILE * dat = fopen("OSC.dat", "rb"); /*abre como binário*/
	fread(&ONG, sizeof(ONG), 1, dat);    /*copia valores do .dat pra a estrutura*/
	
	for(i=0; i<66; i++)      /*usar FTELL com SIZEOF para definir o MALLOC do vetor de estruturas*/
	{
		printf("\n%s", ONG[i].Entidade); /*como usar o #DEFINE da biblioteca_geral aqui, para deixar um espaço padronizado?*/
		printf(" %s |", ONG[i].CNPJ);
		printf(" %s |", ONG[i].Email);
		printf(" %s |", ONG[i].Telefone);
		printf(" %s |", ONG[i].Comunidade);
		printf(" %s |", ONG[i].Endereco);
		printf(" %s |", ONG[i].Tipo);
		printf(" %s |", ONG[i].Subpre);
		printf(" %i |", ONG[i].Quant_cesta);
	}
	
	fclose(dat);
	
	
	return(0);
}
