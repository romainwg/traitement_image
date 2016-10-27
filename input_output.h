#ifndef INPUT_OUPUT
#define INPUT_OUTPUT

typedef struct image {

	char nom[256];
	int int8_unknow1;
	int int8_unknow2; /*init*/
	int int32_tailleFichier;
	int int16_idAppli1; /*init*/
	int int16_idAppli2; /*init*/
	int int32_offsetDebutBMP; /*1078 si palette(1024) sinon 54*/
	int int32_infoZoneBitmap;
	int int32_largeurImage;
	int int32_hauteurImage;
	int int16_nombrePlan;
	int int16_bitParPixel;
	int int32_formatCompression; /*init*/
	int int32_tailleImage;
	int int32_resHorizontale; /*init _ utile pour impression*/
	int int32_resVerticale; /*init _ utile pour impression*/
	int int32_nombreCouleurUtil;
	int int32_nombreIndexCouleur;
	int int8096_palette[1024]; /*palette si gray*/
	int ** ptrData; /*contenu de l'image*/
	
} * ptrImage;

typedef struct image strImage;

void readInt2Bytes(int * intOuput, FILE * fichierALire);

void writeInt2Bytes(int intInput, FILE * fichierAEcrire);

void writePalette(FILE * fichierAEcrire);

int openImage(char * name, ptrImage pImage);

int closeImage(ptrImage pImage);

int saveImage(char * name, ptrImage pImage);

#endif

