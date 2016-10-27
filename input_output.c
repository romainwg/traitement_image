#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_output.h"

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

void writeInt2Bytes(int intInput, FILE * fichierAEcrire)
{
	if(intInput > (256*256+256)-1)
	{
		printf("depassement ecriture int2byte");
		return;	
	}
	
	int modulo = intInput%256;

	fputc(modulo, fichierAEcrire);

	fputc((intInput-modulo)/256, fichierAEcrire);

	
	

	return;

}

void writeInt1Bytes(int intInput, FILE * fichierAEcrire)
{
	if(intInput > (256)-1)
	{
		printf("depassement ecriture int1byte");
		return;	
	}
	
	fputc(intInput, fichierAEcrire);

	return;

}

void writePalette(FILE * fichierAEcrire)
{
	int a = 0;
	int b = 0;
	for(a=0;a<256;a++){
		for(b=0;b<3;b++){
			fputc(a, fichierAEcrire);
		}
		fputc(0, fichierAEcrire);	
	}
	return;
}

int saveImage(char * name, ptrImage pImage)
{	
	if(name == NULL || pImage == NULL)
	{
		printf("erreur saveImage : nom ou pImage non defini");
		return 0;
	}
	
	pImage->int32_offsetDebutBMP = 1078;
	pImage->int32_infoZoneBitmap = 40;
	pImage->int32_tailleFichier = 54 + 1024 + pImage->int32_tailleImage; 
	pImage->int16_nombrePlan = 1; /*init*/
	pImage->int16_bitParPixel = 8;
	pImage->int32_formatCompression = 0; /*init*/
	pImage->int32_resHorizontale = 0; /*init _ utile pour impression*/
	pImage->int32_resVerticale = 0; /*init _ utile pour impression*/
	pImage->int32_nombreCouleurUtil = 0;
	pImage->int32_nombreIndexCouleur = 0;

	FILE* fichierOutput = NULL;

	

	fichierOutput = fopen(name, "wb");
	
	if(fichierOutput == NULL){
		printf("\nerreur a l ouverture du fichier");
		return 0;
	}

	
	
	writeInt1Bytes(pImage->int8_unknow1, fichierOutput);
	writeInt1Bytes(pImage->int8_unknow2, fichierOutput);
	fwrite(&(pImage->int32_tailleFichier), sizeof(int), 1, fichierOutput);
	writeInt2Bytes(pImage->int16_idAppli1, fichierOutput);
	writeInt2Bytes(pImage->int16_idAppli2, fichierOutput);
	fwrite(&(pImage->int32_offsetDebutBMP), sizeof(int), 1, fichierOutput);
	fwrite(&(pImage->int32_infoZoneBitmap), sizeof(int), 1, fichierOutput);
	fwrite(&(pImage->int32_largeurImage), sizeof(int), 1, fichierOutput);
	fwrite(&(pImage->int32_hauteurImage), sizeof(int), 1, fichierOutput);
	writeInt2Bytes(pImage->int16_nombrePlan, fichierOutput);
	writeInt2Bytes(pImage->int16_bitParPixel, fichierOutput);
	fwrite(&(pImage->int32_formatCompression), sizeof(int), 1, fichierOutput);
	fwrite(&(pImage->int32_tailleImage), sizeof(int), 1, fichierOutput);
	fwrite(&(pImage->int32_resHorizontale), sizeof(int), 1, fichierOutput);
	fwrite(&(pImage->int32_resVerticale), sizeof(int), 1, fichierOutput);
	fwrite(&(pImage->int32_nombreCouleurUtil), sizeof(int), 1, fichierOutput);
	fwrite(&(pImage->int32_nombreIndexCouleur), sizeof(int), 1, fichierOutput);

	writePalette(fichierOutput);
	/*fwrite(pImage->ptrData, sizeof(int), 1, fichierOutput);*/
	int a=0;
	int b=0;

	if(pImage->int32_largeurImage % 2 == 0){
		for(a=pImage->int32_hauteurImage-1;a>=0;a--){
			for(b=0;b<pImage->int32_largeurImage;b++){
				fputc((pImage->ptrData)[a][b], fichierOutput);
			}
		}
	}else{
		for(a=pImage->int32_hauteurImage-1;a>=0;a--){
			for(b=0;b<(pImage->int32_largeurImage+1);b++){
				if(b != pImage->int32_largeurImage){
					fputc((pImage->ptrData)[a][b], fichierOutput);
				}else{
					fputc(0, fichierOutput);
				}
			}
		}
	}

	fclose(fichierOutput);

	return 1;
}

void initStrImage(ptrImage pImage)
{
	pImage->int8_unknow1 = 66;
	pImage->int8_unknow2 = 77; /*init*/
	pImage->int32_tailleFichier = 0;
	pImage->int16_idAppli1 = 0; /*init*/
	pImage->int16_idAppli2 = 0; /*init*/
	pImage->int32_offsetDebutBMP = 0; /*1078 si palette(1024) sinon 54*/
	pImage->int32_infoZoneBitmap = 0;
	pImage->int32_largeurImage = 0;
	pImage->int32_hauteurImage = 0;
	pImage->int16_nombrePlan = 1; /*init*/
	pImage->int16_bitParPixel = 8;
	pImage->int32_formatCompression = 0; /*init*/
	pImage->int32_tailleImage = 0;
	pImage->int32_resHorizontale = 0; /*init _ utile pour impression*/
	pImage->int32_resVerticale = 0; /*init _ utile pour impression*/
	pImage->int32_nombreCouleurUtil = 0;
	pImage->int32_nombreIndexCouleur = 0;
	pImage->ptrData = NULL;

	return;
}

int openImage(char * name, ptrImage pImage)
{
	int vDebug = 0;

	FILE* fichierBMP = NULL;
	fichierBMP = fopen(name, "rb");
	
	if(fichierBMP == NULL){
		printf("\nerreur a l ouverture du fichier");
		return 0;
	}

	
	initStrImage(pImage);
	
	strcpy(pImage->nom, name);
	
	/*DEBUT LECTURE ENTÊTE*/

	/* 00-02 UNKNOWN */
	int character = 0;
	int a = 0;

		character = fgetc(fichierBMP);
		pImage->int8_unknow1 = character;
		if(vDebug){
			printf("\n%d_______UNKNOWN1",character, SEEK_CUR); 
		}
		character = fgetc(fichierBMP);
		pImage->int8_unknow2 = character;
		if(vDebug){
			printf("\n%d_______UNKNOWN2",character, SEEK_CUR); 
		}

	/*readInt2Bytes(&character, fichierBMP);
	printf("\n%d", character);*/

	/* 02-06 taille fichier BMP*/
	int tailleFichier = 0;
	fread(&tailleFichier, sizeof(int), 1, fichierBMP);
	pImage->int32_tailleFichier = tailleFichier;
	if(vDebug){
	printf("\n%d___taille fichier bmp", tailleFichier);
	}	

	/* 06-0A id appli x2*/
	int idAppli = 0;
	readInt2Bytes(&idAppli, fichierBMP);
	pImage->int16_idAppli1;
	if(vDebug){
	printf("\n%d___id application", idAppli);
	}
	readInt2Bytes(&idAppli, fichierBMP);
	pImage->int16_idAppli2;
	if(vDebug){
	printf("\n%d___id application", idAppli);
	}
	
	/* 0A-0E offset adresse de debut fichier bmp */
	int offsetDebutBMP = 0;
	fread(&offsetDebutBMP, sizeof(int), 1, fichierBMP);
	pImage->int32_offsetDebutBMP = offsetDebutBMP;
	if(vDebug){
	printf("\n%d___offset debut BMP", offsetDebutBMP);
	}

	/* 0E-12 information zone bitmap */
	int infoZoneBitmap = 0;
	fread(&infoZoneBitmap, sizeof(int), 1, fichierBMP);
	pImage->int32_infoZoneBitmap = infoZoneBitmap;
	if(vDebug){
	printf("\n%d___information zone bitmap",infoZoneBitmap); 
	}

	/* 12-16 largeur image*/
	int largeurBMP = 0;
	fread(&largeurBMP, sizeof(int), 1, fichierBMP);
	pImage->int32_largeurImage = largeurBMP;
	if(vDebug){
	printf("\n%d___largeur image BMP",largeurBMP);
	}
	
	/* 16-1A hauteur image*/
	int hauteurBMP = 0;
	fread(&hauteurBMP, sizeof(int), 1, fichierBMP);
	pImage->int32_hauteurImage = hauteurBMP;
	if(vDebug){
	printf("\n%d___hauteur image BMP", hauteurBMP);
	}
	
	/* 1A-1C nombre de plan */
	int nombrePlan = 0;
	readInt2Bytes(&nombrePlan, fichierBMP);
	pImage->int16_nombrePlan = nombrePlan;
	if(vDebug){
	printf("\n%d___nombre de plan", nombrePlan);
	}

	/* 1C-1E bit par pixel */
	int bitParPixel = 0;
	readInt2Bytes(&bitParPixel, fichierBMP);
	pImage->int16_bitParPixel = bitParPixel;
	if(vDebug){
	printf("\n%d___bit par pixel", bitParPixel);
	}

	/* 1E-22 format de compression */
	int formatCompression = 0;
	fread(&formatCompression, sizeof(int), 1, fichierBMP);
	pImage->int32_formatCompression = formatCompression;
	if(vDebug){
	printf("\n%d___format de compression", formatCompression);
	}

	/* 22-26 taille de l'image */
	int tailleImage = 0;
	fread(&tailleImage, sizeof(int), 1, fichierBMP);
	pImage->int32_tailleImage = tailleImage;
	if(vDebug){
	printf("\n%d___taille de l'image", tailleImage);
	}

	/* 26-2A resolution horizontale de l'image */
	int resolutionHorizontale = 0;
	fread(&resolutionHorizontale, sizeof(int), 1, fichierBMP);
	pImage->int32_resHorizontale = resolutionHorizontale;
	if(vDebug){
	printf("\n%d___resolution horizontale", resolutionHorizontale);
	}

	/* 2A-2E resolution verticale de l'image */
	int resolutionVerticale = 0;
	fread(&resolutionVerticale, sizeof(int), 1, fichierBMP);
	pImage->int32_resVerticale = resolutionVerticale;
	if(vDebug){
	printf("\n%d___resolution verticale", resolutionVerticale);
	}

	/* 2E-32 nombre couleur utilisé (0=max) */
	int nombreCouleurUtilise = 0;
	fread(&nombreCouleurUtilise, sizeof(int), 1, fichierBMP);
	pImage->int32_nombreCouleurUtil = nombreCouleurUtilise;
	if(vDebug){
	printf("\n%d___nombre de couleur utilise", nombreCouleurUtilise);
	}

	/* 32-36 nombre d'index de couleur */
	int nombreIndexCouleur = 0;
	fread(&nombreIndexCouleur, sizeof(int), 1, fichierBMP);
	pImage->int32_nombreIndexCouleur = nombreIndexCouleur;
	if(vDebug){
	printf("\n%d___nombre d'index de couleur imptte (0= tte imptte)", nombreIndexCouleur);
	}
	/*FIN ENTÊTE*/
	
	if(offsetDebutBMP==0){
		printf("erreur lecture offset");
		return 0;
	}
	fseek(fichierBMP, offsetDebutBMP-54, SEEK_CUR);
	
	/*fseek(fichierBMP, 262140, SEEK_CUR);
	*/
	
	/*printf("\ntaille h : %d ; taille l : %d", hauteurBMP, largeurBMP);
	*/

	int b = 0;

	int ** ligne = NULL;
	ligne = malloc(sizeof(int*)*hauteurBMP);
	
	for(a=0;a<hauteurBMP;a++)
	{
		ligne[a] = malloc(sizeof(int)*largeurBMP);
	}
	if(largeurBMP%2 == 0){ /*largeur paire*/
		for(a=hauteurBMP-1;a>=0;a--)
		{
			for(b=0;b<largeurBMP;b++)
			{
				(ligne[a])[b] = fgetc(fichierBMP);
				/*printf("%d", (ligne[a])[b]);*/
				if((ligne[a])[b] == -1)
				{
					printf("erreur lecture fichier image");
					return 0;
				}
			}
		}
	}else{
		for(a=hauteurBMP-1;a>=0;a--)
		{
			for(b=0;b<largeurBMP;b++)
			{
				(ligne[a])[b] = fgetc(fichierBMP);
				/*printf("\n_%d_%d", (ligne[a])[b], test);*/
				if((ligne[a])[b] == -1)
				{
					printf("erreur lecture fichier image");
					return 0;
				}
			}
			fgetc(fichierBMP); /*lecture dans le vide dernier car*/
		}
	}
	
	pImage->ptrData = ligne;

	/*printf("\n\n%d_%d_%d", ligne[511][0], ligne[511][1], ligne[511][2]);
	*/

	fclose(fichierBMP);
	/*free(ligne);
	*/

	return 1;
}


int closeImage(ptrImage pImage){
	free(pImage);
}
