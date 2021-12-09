#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]){ 
	
	FILE *img;

	char format[10];
    int width = 0;
	int height = 0;
	int intensity = 0;
	int ignored_value = 0;
	int i, j = 0;
    img = fopen ( "vit_small.ppm" , "rb" );

	fscanf(img,"%s",format);     //help: http://www.cplusplus.com/forum/general/208835/
    fscanf(img, "%d %d", &width, &height);
	fscanf(img, "%d", &intensity);
	fscanf(img, "%d", &ignored_value);

    printf("format: %s\n", format);
    printf("Width: %d\n", width);
    printf("Height: %d\n", height);
    printf("intensity: %d\n", intensity);
	printf("ignored value: %d\n", ignored_value);
	
	int size = width*height;
	unsigned char Red[size] = {};
	unsigned char Green[size] = {};
	unsigned char Blue[size] = {};
	unsigned char temp[size*3] = {};
	
	unsigned char n_Red[size] = {};
	//unsigned char* pixels = new unsigned char[size];
    
	while (i < size*3){
	  temp[i] = fgetc (img);
	  i++;
	}
	
	for (int ax = 0; ax < size*3; ax += 3){ //update every color array
		Red[j] = temp[ax];
		Green[j] = temp[ax+1];
		Blue[j] = temp[ax+2];
		j++;
	}

	n_Red = Red;
	for(int i=1; i<width-1; i++){
		for(int j=1; j<height-1; j++){
			n_Red[i][j] = -1*Red[i-1][j] - 1*Red[i][j-1] + 5*Red[i][j] - 1*Red[i][j+1] - 1*Red[i+1][j]
		}
	}

	
//	for(int q=0; q < size; q++){ //loop throuh all the pixels
//		int sum = 0;
//		for(int h=0; h<2; h++){ //loop through kernel height
//		    int row = q/width;
//			for(int w=0; w<2; w++){  //loop through kernel width
//			    int col = q%width;
//				sum+= kernel[w][h] + Red[(row*width)+col];
//			}
//		}
//		
//		//aqui escribir el resultado en el cuadro de enmiedio de la nueva matriz
//	}
//	if(row = 0 or col = 0 or row = heigth or col = width){
//		n_Red[q] = Red[q];
//	}
//	else {
//		n_Red[q] = sum; // aqui cambiar esto porque las orillas se deben de quedar igual
//	}
	

	

	
	//while (fread(pixels, 1, height*4, img)) {} 
	 
	//for(i=0;i<sizeof(Red);i++){
	//	cout << int(Green[i]) << endl;
	//}

	fclose(img);
	return 0;
}












