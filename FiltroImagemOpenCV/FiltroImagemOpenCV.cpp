#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "PDI.h"
#include <math.h>
#include <vector>
#include <stdio.h>
#include <iostream>
using namespace cv;
using namespace std;

//

Mat escalaCinza(Mat imagemColorida);
Mat negativoLinear(Mat imagemBase);
Mat logaritmo(Mat imagemBase);
int intensidadeMaxima(Mat imagemBase);
Mat potencia(Mat imagemBase, float gama);
int intensidadeMinima(Mat imagemBase);
Mat alargamento(Mat imagemBase);
Mat limiarizacao(Mat imagemBase, int limiar);
Mat janelamento(Mat imagemBase, int li, int ls);
Mat suavizacao(Mat imagemBase, int kernel[3][3], float somaKernel);


int main()
{
	Mat original = imread("C:/Users/dougl/Desktop/Aula 4/Erosao.png");
	
	//Mat suavizada = PDI::suavizacaoMediana(original, 5);


	Mat suavizada = PDI::Erosao(original);

	for (int i = 0; i < 40; i++)
	{
		suavizada = PDI::Erosao(suavizada);
	}

	imshow("Erosão", suavizada);
	suavizada = PDI::Dilatacao(suavizada);

	for (int i = 0; i < 30; i++)
	{
		suavizada = PDI::Dilatacao(suavizada);
	}

	/*Mat borda = original + suavizada;
	Mat agucada = original + borda;*/

	imshow("Original", original);
	imshow("Final", suavizada);
	
	waitKey(0);
	return 0;
}

Mat escalaCinza(Mat imagemColorida) {
	Mat aux = imagemColorida.clone();

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			Vec3b pixel = aux.at<Vec3b>(x, y);
			int cinza = pixel[2] * 0.21 + pixel[1] * 0.72 + pixel[0] * 0.07;

			pixel[2] = cinza;//R
			pixel[1] = cinza;//G
			pixel[0] = cinza;//B

			aux.at<Vec3b>(x, y) = pixel;
		}
	}

	return aux;
}

Mat negativoLinear(Mat imagemBase) {
	Mat aux = imagemBase.clone();

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			Vec3b pixel = aux.at<Vec3b>(x, y);
			int negativo = 255 - pixel[2];

			pixel[2] = negativo;
			pixel[1] = negativo;
			pixel[0] = negativo;

			aux.at<Vec3b>(x, y) = pixel;
		}
	}

	return aux;
}

Mat logaritmo(Mat imagemBase) {
	Mat aux = imagemBase.clone();

	float c = 255 / (log(intensidadeMaxima(imagemBase)));

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			Vec3b pixel = aux.at<Vec3b>(x, y);
			int pLog = c * log(1 + pixel[2]);

			pixel[2] = pLog;
			pixel[1] = pLog;
			pixel[0] = pLog;

			aux.at<Vec3b>(x, y) = pixel;
		}
	}

	return aux;
}

Mat potencia(Mat imagemBase, float gama) {
	Mat aux = imagemBase.clone();

	float c = 255 / pow(intensidadeMaxima(imagemBase), gama);

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			Vec3b pixel = aux.at<Vec3b>(x, y);
			int pExp = c * pow(pixel[2], gama);

			pixel[2] = pExp;
			pixel[1] = pExp;
			pixel[0] = pExp;

			aux.at<Vec3b>(x, y) = pixel;
		}
	}

	return aux;
}

int intensidadeMaxima(Mat imagemBase) {
	int maximo = 0;
	for (int x = 0; x < imagemBase.rows; x++) {
		for (int y = 0; y < imagemBase.cols; y++) {
			Vec3b pixel = imagemBase.at<Vec3b>(x, y);
			if (pixel[2] > maximo) {
				maximo = pixel[2];
			}
		}
	}

	return maximo;
}

Mat alargamento(Mat imagemBase) {
	Mat aux = imagemBase.clone();

	int minI = intensidadeMinima(imagemBase);
	int maxI = intensidadeMaxima(imagemBase);
	float escala = maxI - minI;

	for (int x = 0; x < imagemBase.rows; x++) {
		for (int y = 0; y < imagemBase.cols; y++) {
			Vec3b pixel = imagemBase.at<Vec3b>(x, y);
			int novoPixel = (pixel[2] - minI) * (255 / escala);

			pixel[2] = novoPixel;
			pixel[1] = novoPixel;
			pixel[0] = novoPixel;

			aux.at<Vec3b>(x, y) = pixel;
		}
	}

	return aux;
}

int intensidadeMinima(Mat imagemBase) {
	int minimo = 255;
	for (int x = 0; x < imagemBase.rows; x++) {
		for (int y = 0; y < imagemBase.cols; y++) {
			Vec3b pixel = imagemBase.at<Vec3b>(x, y);
			if (pixel[2] < minimo) {
				minimo = pixel[2];
			}
		}
	}

	return minimo;
}

Mat limiarizacao(Mat imagemBase, int limiar) {
	Mat aux = imagemBase.clone();

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			Vec3b pixel = aux.at<Vec3b>(x, y);
			int cPixel;

			if (pixel[2] <= limiar)
				cPixel = 0;
			else
				cPixel = 255;

			pixel[2] = cPixel;
			pixel[1] = cPixel;
			pixel[0] = cPixel;

			aux.at<Vec3b>(x, y) = pixel;
		}
	}

	return aux;
}

Mat janelamento(Mat imagemBase, int li, int ls) {
	Mat aux = imagemBase.clone();

	float escala = ls - li;

	for (int x = 0; x < imagemBase.rows; x++) {
		for (int y = 0; y < imagemBase.cols; y++) {
			Vec3b pixel = imagemBase.at<Vec3b>(x, y);
			int novoPixel = pixel[2];

			if (pixel[2] <= li)
				novoPixel = 0;
			else if (pixel[2] >= ls)
				novoPixel = 255;
			else
				novoPixel = (pixel[2] - li) * (255 / escala);

			pixel[2] = novoPixel;
			pixel[1] = novoPixel;
			pixel[0] = novoPixel;

			aux.at<Vec3b>(x, y) = pixel;
		}
	}

	return aux;
}


Mat suavizacao(Mat imagemBase, int kernel[3][3], float somaKernel) {
	Mat aux = imagemBase.clone();

	for (int x = 1; x < aux.rows - 1; x++) 
	{
		for (int y = 1; y < aux.cols - 1; y++) 
		{
			int somaR = 0;
			int somaG = 0;
			int somaB = 0;

			for (int xk = x - 1; xk <= x + 1; xk++)
			{
				for (int yk = y - 1; yk <= y + 1; yk++)
				{
					Vec3b pixel = aux.at<Vec3b>(xk, yk);

					somaR += pixel[2] * kernel[xk - x + 1][yk - y + 1];
					somaG += pixel[1] * kernel[xk - x + 1][yk - y + 1];
					somaB += pixel[0] * kernel[xk - x + 1][yk - y + 1];
				}
			}

			somaR = somaR / somaKernel;
			somaG = somaG / somaKernel;
			somaB = somaB / somaKernel;

			Vec3b pixel = aux.at<Vec3b>(x, y);

			pixel[2] = somaR;
			pixel[1] = somaG;
			pixel[0] = somaB;
		}
	}

	return aux;
}