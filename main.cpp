#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]){ 
	
	FILE *img;
	FILE *output_img;
    ofstream archivo_sal;
	
	char format[10] = {};
    int width = 0;
	int height = 0;
	int intensity = 0;
	int ignored_value = 0;
	int n = 0;
    img = fopen ( "vit_small.ppm" , "rb" );

	n = fscanf(img,"%s",format);     //help: http://www.cplusplus.com/forum/general/208835/
    n = fscanf(img, "%d %d", &width, &height);
	n = fscanf(img, "%d", &intensity);
	n = fscanf(img, "%d", &ignored_value);
	n++;
	
    printf("format: %s\n", format);
    printf("Width: %d\n", width);
    printf("Height: %d\n", height);
    printf("intensity: %d\n", intensity);
	printf("ignored value: %d\n", ignored_value);
	
	//int size = width*height;	
    unsigned char mat_Red[height][width] = {};
	unsigned char mat_Green[height][width] = {};	
	unsigned char mat_Blue[height][width] = {};

	unsigned char n_Red[height][width] = {};
	unsigned char n_Green[height][width] = {};
	unsigned char n_Blue[height][width] = {};


	for(int h=0; h<height; h++){   //Storing file values into 2D matrices
		for(int w=0; w<width; w++){
			mat_Red[h][w] = fgetc (img);
			mat_Green[h][w] = fgetc (img);
			mat_Blue[h][w] = fgetc (img);
		}
	}
	
	//------------------------- RED CHANNEL ----------------------------------------
	for(int y=0; y<height; y++){        //Copy the 2d Red matrix to new matrix (n_Red = mat_Red)
		for(int z=0; z<width; z++){
			n_Red[y][z] = mat_Red[y][z];
		}
	}
	for(int i=1; i<height-1; i++){  //Apply Convolution with the kernel to the Red channel image
		for(int j=1; j<width-1; j++){
			int sum = (-1*mat_Red[i-1][j]) + (-1*mat_Red[i][j-1]) + (5*mat_Red[i][j]) + (-1*mat_Red[i][j+1]) + (-1*mat_Red[i+1][j]);
			if(sum > 255) { n_Red[i][j] = 255; }
			else if(sum < 0) { n_Red[i][j] = 0; }
			else{ n_Red[i][j] = sum; }
		}
	}	
	
	//------------------------- GREEN CHANNEL ----------------------------------------
	for(int y=0; y<height; y++){        //Copy the 2d Green matrix to new matrix (n_Green = mat_Green)
		for(int z=0; z<width; z++){
			n_Green[y][z] = mat_Green[y][z];
		}
	}
	for(int i=1; i<height-1; i++){  //Apply Convolution with the kernel to the Green channel image
		for(int j=1; j<width-1; j++){
			int sum = (-1*mat_Green[i-1][j]) + (-1*mat_Green[i][j-1]) + (5*mat_Green[i][j]) + (-1*mat_Green[i][j+1]) + (-1*mat_Green[i+1][j]);
			if(sum > 255) { n_Green[i][j] = 255; }
			else if(sum < 0) { n_Green[i][j] = 0; }
			else{ n_Green[i][j] = sum; }
		}
	}	
	//------------------------- BLUE CHANNEL ----------------------------------------	
	for(int y=0; y<height; y++){        //Copy the 2d Blue matrix to new matrix (n_Blue = mat_Blue)
		for(int z=0; z<width; z++){
			n_Blue[y][z] = mat_Blue[y][z];
		}
	}
	for(int i=1; i<height-1; i++){  //Apply Convolution with the kernel to the Blue channel image
		for(int j=1; j<width-1; j++){
			int sum = (-1*mat_Blue[i-1][j]) + (-1*mat_Blue[i][j-1]) + (5*mat_Blue[i][j]) + (-1*mat_Blue[i][j+1]) + (-1*mat_Blue[i+1][j]);
			if(sum > 255) { n_Blue[i][j] = 255; }
			else if(sum < 0) { n_Blue[i][j] = 0; }
			else{ n_Blue[i][j] = sum; }
		}
	}		
	
	output_img = fopen ("output.ppm","w");
	fputc (80, output_img); //P 
	fputc (54, output_img); //6
	fputc (10, output_img); //newline
	fputc (51, output_img); //3
	fputc (48, output_img); //0
	fputc (48, output_img); //0
	fputc (10, output_img); //newline
	fputc (52, output_img); //4
	fputc (48, output_img); //0
	fputc (48, output_img); //0
	fputc (10, output_img); //newline
	fputc (50, output_img); //2
	fputc (53, output_img); //5
	fputc (53, output_img); //5
	fputc (10, output_img); //newline
	
	for (int h1 = 0; h1 < height; h1++){ 
	    for(int w1 = 0; w1 < width; w1++){
			fputc (n_Red[h1][w1], output_img);
			fputc (n_Green[h1][w1], output_img);
			fputc (n_Blue[h1][w1], output_img);
		}
	}
	
	int bin1=0;
	int bin2=0;
	int bin3=0;
	int bin4=0;
	int bin5=0;
	for (int h2 = 0; h2 < height; h2++){ 
	    for(int w2 = 0; w2 < width; w2++){
			int value = round((0.2126*n_Red[h2][w2]) + (0.7152*n_Green[h2][w2]) + (0.0722*n_Blue[h2][w2]));
			if(0 <= value && value <= 50){
				bin1++;
			} else if(51 <= value && value <= 101){
				bin2++;
			} else if(102 <= value && value <= 152){
				bin3++;
			} else if(153 <= value && value <= 203){
				bin4++;
			} else{
				bin5++;
			}
		}
	}
	
	archivo_sal.open("output.txt");
	archivo_sal << bin1 << " " << bin2 << " " << bin3 << " " << bin4 << " " << bin5;
    archivo_sal.close();	
	fclose(img);
	fclose(output_img);
	
	return 0;
}


	//unsigned char Red[size] = {};
	//unsigned char Green[size] = {};
	//unsigned char Blue[size] = {};

	//unsigned char* pixels = new unsigned char[size];
    
	//for (int ax = 0; ax < size; ax++){ //update every color array separatelly
	//	Red[ax] = fgetc (img);
	//	Green[ax] = fgetc (img);
	//	Blue[ax] = fgetc (img);
	//}
	







