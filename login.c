/* BIBLIOTECA */
#include "biblio_geral.h"

/* VARI�VEIS GLOBAIS */
secoes ONG[66];                                                             /*vetor de estruturas, mas tenho que usar MALLOC!*/
int i;         /*contador do for*/

/* FUNC�ES */
void consulta()
{
	for(i=0; i<66; i++)                                                           /*como deixar um espa�o padronizado?*/
	{
		printf("\n%s", ONG[i].Entidade);                                          /*como deixar a apar�ncia bonita?*/
		printf(" %s |", ONG[i].CNPJ);
		printf(" %s |", ONG[i].Email);
		printf(" %s |", ONG[i].Telefone);
		printf(" %s |", ONG[i].Comunidade);
		printf(" %s |", ONG[i].Endereco);
		printf(" %s |", ONG[i].Tipo);
		printf(" %s |", ONG[i].Subpre);
		printf(" %i |", ONG[i].Quant_cesta);
	}
}


void ordena_enti() /*ordena entidades usando insertion short*/
{
	FILE * dat = fopen("OSC.dat", "rb");    /*abre .dat como bin�rio*/
	fread(&ONG, sizeof(ONG), 1, dat);       /*copia valores do .dat pra a estrutura*/
	
	//insertion short
	secoes escolhido;
    int   anterior;
    for (i = 1; i <66; i++) 
    {
		escolhido = ONG[i]; 
		anterior  = i - 1;
		while ( ONG[anterior].CNPJ > ONG[i].CNPJ ) 
		{
	    	ONG[i] = ONG[anterior];                                                            /*por que n�o funciona?*/
	    	ONG[anterior] = escolhido;
		}
    }
    
    fclose(dat); /*fecha .dat*/
    
}

/* CORPO DO PROGRAMA */
int main()
{
	decoracao(); /*habilita acento e cor do programa*/
	
	char email[email_max  + 1];
	char cnpj [cnpj_max   + 1];
	
	//menu
	printf("A��O SOCIAL CIDADE SOLID�RIA\n");
	printf("----------------------------\n");
	printf("digite seu email: ");                fflush(stdin);  gets(email);
	printf("Digite o cnpj [somente n�meros]: "); fflush(stdin);  gets(cnpj);
	ordena_enti();
	
	consulta();
	
	return(0);
}
