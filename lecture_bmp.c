#include <stdio.h>
#include <stdlib.h>

/*Lecture a partir d'un flux donné de deux bytes consécutifs
 * Attention : prevoir de ne pas etre a la fin du fichier
 */
void readInt2Bytes(int * intOuput, FILE * fichierALire)
{
	int premierByte = 0;
	int deuxiemeByte = 0 ;

	premierByte = fgetc(fichierALire);
	deuxiemeByte = fgetc(fichierALire);

	*intOuput = premierByte + 256 * deuxiemeByte;
	
	return;
}	



int main(){
	
	FILE* fichierBMP = NULL;
	
	fichierBMP = fopen("./lena512.bmp", "rb");
	
	if(fichierBMP == NULL)
	{
		printf("\nerreur a l ouverture du fichier");
		return 0;
	}

	/*DEBUT LECTURE ENTÊTE*/

	/* 00-02 UNKNOWN */
	int character = 0;
	int a = 0;
	for(a=0; a<2; a++)
	{
		character = fgetc(fichierBMP);
		printf("\n%d_______UNKNOWN",character, SEEK_CUR); 
	}

	/*readInt2Bytes(&character, fichierBMP);
	printf("\n%d", character);*/

	/* 02-06 taille fichier BMP*/
	int tailleFichier = 0;
	fread(&tailleFichier, sizeof(int), 1, fichierBMP);
	printf("\n%d___taille fichier bmp", tailleFichier);
	
	/* 06-0A id appli x2*/
	int idAppli = 0;
	for(a=0;a<2;a++)
	{
		readInt2Bytes(&idAppli, fichierBMP);
		printf("\n%d___id application", idAppli);
	}
	
	/* 0A-0E offset adresse de debut fichier bmp */
	int offsetDebutBMP = 0;
	fread(&offsetDebutBMP, sizeof(int), 1, fichierBMP);
	printf("\n%d___offset debut BMP", offsetDebutBMP);

	/* 0E-12 information zone bitmap */
	int infoZoneBitmap = 0;
	fread(&infoZoneBitmap, sizeof(int), 1, fichierBMP);
	printf("\n%d___information zone bitmap",infoZoneBitmap); 
	
	/* 12-16 largeur image*/
	int largeurBMP = 0;
	fread(&largeurBMP, sizeof(int), 1, fichierBMP);
	printf("\n%d___largeur image BMP",largeurBMP);
	
	/* 16-1A hauteur image*/
	int hauteurBMP = 0;
	fread(&hauteurBMP, sizeof(int), 1, fichierBMP);
	printf("\n%d___hauteur image BMP", hauteurBMP);
	
	/* 1A-1C nombre de plan */
	int nombrePlan = 0;
	readInt2Bytes(&nombrePlan, fichierBMP);
	printf("\n%d___nombre de plan", nombrePlan);

	/* 1C-1E bit par pixel */
	int bitParPixel = 0;
	readInt2Bytes(&bitParPixel, fichierBMP);
	printf("\n%d___bit par pixel", bitParPixel);

	/* 1E-22 format de compression */
	int formatCompression = 0;
	fread(&formatCompression, sizeof(int), 1, fichierBMP);
	printf("\n%d___format de compression", formatCompression);

	/* 22-26 taille de l'image */
	int tailleImage = 0;
	fread(&tailleImage, sizeof(int), 1, fichierBMP);
	printf("\n%d___taille de l'image", tailleImage);

	/* 26-2A resolution horizontale de l'image */
	int resolutionHorizontale = 0;
	fread(&resolutionHorizontale, sizeof(int), 1, fichierBMP);
	printf("\n%d___resolution horizontale", resolutionHorizontale);

	/* 2A-2E resolution verticale de l'image */
	int resolutionVerticale = 0;
	fread(&resolutionVerticale, sizeof(int), 1, fichierBMP);
	printf("\n%d___resolution verticale", resolutionVerticale);
	
	/* 2E-32 nombre couleur utilisé (0=max) */
	int nombreCouleurUtilise = 0;
	fread(&nombreCouleurUtilise, sizeof(int), 1, fichierBMP);
	printf("\n%d___nombre de couleur utilise", nombreCouleurUtilise);

	/* 32-36 nombre d'index de couleur */
	int nombreIndexCouleur = 0;
	fread(&nombreIndexCouleur, sizeof(int), 1, fichierBMP);
	printf("\n%d___nombre d'index de couleur imptte (0= tte imptte)", nombreIndexCouleur);

	/*FIN ENTÊTE*/
	
	fseek(fichierBMP, 1024, SEEK_CUR);
	/*fseek(fichierBMP, 262140, SEEK_CUR);
	*/
	
	printf("\ntaille h : %d ; taille l : %d", hauteurBMP, largeurBMP);

	int b = 0;

	int ** ligne = NULL;
	ligne = malloc(sizeof(int*)*hauteurBMP);
	
	for(a=0;a<hauteurBMP;a++)
	{
		ligne[a] = malloc(sizeof(int)*largeurBMP);
	}

	for(a=hauteurBMP-1;a>=0;a--)
	{
		for(b=0;b<largeurBMP;b++)
		{
			(ligne[a])[b] = fgetc(fichierBMP);
			if((ligne[a])[b] == -1)
			{
				printf("erreur lecture fichier image");
				return 0;
			}
		}
	}
	
	/*printf("\n\n%d_%d_%d", ligne[511][0], ligne[511][1], ligne[511][2]);
	*/

	/*for(a=0;a<5;a++)
	*/
	/*do
	{
		character = fgetc(fichierBMP);
		printf("\n_________%d", character);
	
	}
	while(character!=-1);
	*/

	
	FILE* fichierOut = NULL;

	ficherOut = fopen("outputTest.bmp","wb");

	


	


	printf("\n");
	fclose(fichierBMP);	
}
