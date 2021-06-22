/* BIBLIOTECA */
#include "biblio_geral.h"

/* VARIÁVEIS GLOBAIS */
secoes ONG[66];                                                             /*vetor de estruturas, mas tenho que usar MALLOC!*/
int i;         /*contador do for*/

/* FUNCÕES */
void consulta()
{
	for(i=0; i<66; i++)                                                           /*como deixar um espaço padronizado?*/
	{
		printf("\n%s", ONG[i].Entidade);                                          /*como deixar a aparência bonita?*/
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
	FILE * dat = fopen("OSC.dat", "rb");    /*abre .dat como binário*/
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
	    	ONG[i] = ONG[anterior];                                                            /*por que não funciona?*/
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
	printf("AÇÃO SOCIAL CIDADE SOLIDÁRIA\n");
	printf("----------------------------\n");
	printf("digite seu email: ");                fflush(stdin);  gets(email);
	printf("Digite o cnpj [somente números]: "); fflush(stdin);  gets(cnpj);
	ordena_enti();
	
	consulta();
	
	return(0);
}
