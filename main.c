#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_output.h"



int main()
{
	ptrImage pImage = NULL;
	pImage = malloc(sizeof(strImage));

	openImage("./lena512.bmp", pImage);
	
	/*
	openImage("./output_lena512.bmp", pImage);
	*/	
	int a=0;
	int b=0;
	
	for(a=0;a<pImage->int32_hauteurImage/2;a++){
		for(b=0;b<pImage->int32_largeurImage/2;b++){
			pImage->ptrData[a][b] = 0;
		}
	}

	for(a=pImage->int32_hauteurImage/2-1;a<pImage->int32_hauteurImage;a++){
		for(b=pImage->int32_largeurImage/2-1;b<pImage->int32_largeurImage;b++){
			pImage->ptrData[a][b] = 255-pImage->ptrData[a][b];
		}
	}

	/*printf("%s pese : %d Bytes", pImage->nom, pImage->int32_tailleFichier);
	*/
	
	
	saveImage("output_lena512.bmp", pImage);
	
	
	
	closeImage(pImage);


	return 1;
}
