#include "stdafx.h"
#include "PDI.h"
#include <vector>
#include <iostream>


Mat PDI::escalaCinza(Mat imagemColorida) {
	Mat aux = imagemColorida.clone();

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			Vec3b pixel = aux.at<Vec3b>(x, y);
			int cinza = pixel[2] * 0.21 + pixel[1] * 0.72 + pixel[0] * 0.07;

			pixel[2] = cinza;
			pixel[1] = cinza;
			pixel[0] = cinza;

			aux.at<Vec3b>(x, y) = pixel;
		}
	}

	return aux;
}

Mat PDI::juntarImagens(Mat imagemRed, Mat imagemGreen, Mat imagemBlue) {
	Mat aux = imagemRed.clone();

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			Vec3b pixelR = imagemRed.at<Vec3b>(x, y);
			Vec3b pixelG = imagemGreen.at<Vec3b>(x, y);
			Vec3b pixelB = imagemBlue.at<Vec3b>(x, y);

			int pixR = pixelR[2];
			int pixG = pixelG[2];
			int pixB = pixelB[2];

			pixelR[2] = pixR;
			pixelR[1] = pixG;
			pixelR[0] = pixB;

			aux.at<Vec3b>(x, y) = pixelR;
		}
	}

	return aux;
}

Mat PDI::escalaAzul(Mat imagemColorida) {
	Mat aux = imagemColorida.clone();

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			Vec3b pixel = aux.at<Vec3b>(x, y);
			int cinza = pixel[2] * 0.21 + pixel[1] * 0.72 + pixel[0] * 0.07;

			pixel[2] = cinza;
			pixel[1] = cinza;
			//pixel[0] = cinza;

			aux.at<Vec3b>(x, y) = pixel;
		}
	}

	return aux;
}

Mat PDI::negativoLinear(Mat imagemBase) {
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

Mat PDI::canal(Mat imagemColorida, int canal) {
	Mat aux = imagemColorida.clone();

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			Vec3b pixel = aux.at<Vec3b>(x, y);
			int cinza = pixel[canal];

			pixel[2] = cinza;
			pixel[1] = cinza;
			pixel[0] = cinza;

			aux.at<Vec3b>(x, y) = pixel;
		}
	}

	return aux;
}

Mat PDI::logaritmo(Mat imagemBase) {
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

Mat PDI::potencia(Mat imagemBase, float gama) {
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

int PDI::intensidadeMaxima(Mat imagemBase) {
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

Mat PDI::alargamento(Mat imagemBase) {
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

int PDI::intensidadeMinima(Mat imagemBase) {
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

Mat PDI::limiarizacao(Mat imagemBase, int limiar) {
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

Mat PDI::janelamento(Mat imagemBase, int li, int ls) {
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

int** PDI::kernel(int tamanho) {
	int **kernelt = new int*[tamanho];
	kernelt[0] = new int[tamanho * tamanho];
	for (int i = 1; i < tamanho; i++) {
		kernelt[i] = kernelt[i - 1] + tamanho;
	}

	for (int i = 0; i < tamanho; i++) {
		for (int j = 0; j < tamanho; j++) {
			kernelt[i][j] = 1;
		}
	}

	return kernelt;
}

int** PDI::kernelPonderado() {
	//soma 256
	int tamanho = 5;
	int **kernelt = new int*[tamanho];
	kernelt[0] = new int[tamanho * tamanho];
	for (int i = 1; i < tamanho; i++) {
		kernelt[i] = kernelt[i - 1] + tamanho;
	}

	kernelt[0][0] = 1;
	kernelt[0][1] = 4;
	kernelt[0][2] = 6;
	kernelt[0][3] = 4;
	kernelt[0][4] = 1;

	kernelt[1][0] = 4;
	kernelt[1][1] = 16;
	kernelt[1][2] = 24;
	kernelt[1][3] = 16;
	kernelt[1][4] = 4;

	kernelt[2][0] = 6;
	kernelt[2][1] = 24;
	kernelt[2][2] = 36;
	kernelt[2][3] = 24;
	kernelt[2][4] = 6;

	kernelt[3][0] = 4;
	kernelt[3][1] = 16;
	kernelt[3][2] = 24;
	kernelt[3][3] = 16;
	kernelt[3][4] = 4;

	kernelt[4][0] = 1;
	kernelt[4][1] = 4;
	kernelt[4][2] = 6;
	kernelt[4][3] = 4;
	kernelt[4][4] = 1;

	return kernelt;
}

Mat PDI::suavizacaoMedia(Mat imagemBase, int** kernel, int tamanhoKernel, int somaKernel) {
	Mat aux = imagemBase.clone();
	int desl = tamanhoKernel / 2;
	for (int x = desl; x < aux.rows - desl; x++) {
		for (int y = desl; y < aux.cols - desl; y++) {
			float soma = 0;
			for (int i = x - desl; i <= x + desl; i++) {
				for (int j = y - desl; j <= y + desl; j++) {
					Vec3b pixel = imagemBase.at<Vec3b>(i, j);
					soma += pixel[2] * kernel[i - x + desl][j - y + desl];
				}
			}
			soma = soma / somaKernel;
			Vec3b pixel = imagemBase.at<Vec3b>(x, y);
			pixel[2] = soma;
			pixel[1] = soma;
			pixel[0] = soma;
			aux.at<Vec3b>(x, y) = pixel;
		}
	}
	return aux;
}

Mat PDI::suavizacaoMediana(Mat imagemBase, int tamanhoKernel) {
	Mat aux = imagemBase.clone();
	int desl = tamanhoKernel / 2;
	for (int x = desl; x < aux.rows - desl; x++) {
		for (int y = desl; y < aux.cols - desl; y++) {
			int *vet = new int[tamanhoKernel * tamanhoKernel];
			for (int i = x - desl; i <= x + desl; i++) {
				for (int j = y - desl; j <= y + desl; j++) {
					Vec3b pixel = imagemBase.at<Vec3b>(i, j);
					vet[(i - x + desl) * tamanhoKernel + (j - y + desl)] = pixel[2];
				}
			}

			qsort(vet, tamanhoKernel * tamanhoKernel, sizeof(int), compare);
			int mediana = vet[(tamanhoKernel * tamanhoKernel) / 2];
			Vec3b pixel = imagemBase.at<Vec3b>(x, y);
			pixel[2] = mediana;
			pixel[1] = mediana;
			pixel[0] = mediana;
			aux.at<Vec3b>(x, y) = pixel;
		}
	}
	return aux;
}

int PDI::compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

Mat PDI::agucamento(Mat imagemBase) {
	Mat aux = imagemBase;
	Vec3b pixel;

	//Filtro A do Slide
	/*int filtro[3][3] = { { 0,1,0 },
	{ 1,-4,1 },
	{ 0,1,0 } };*/

	//Filtro B do Slide
	/*int filtro[3][3] = { { 1,1,1 },
	{ 1,-8, 1 },
	{ 1,1,1 } };*/

	//Filtro C do Slide
	/*int filtro[3][3] = { { 0,-1,0 },
	{ -1,4,-1 },
	{ 0,-1,0 } };*/

	//Filtro D do Slide
	int filtro[3][3] = { { -1,-1,-1 },
	{ -1,8,-1 },
	{ -1,-1,-1 } };

	int somaR;
	int somaG;
	int somaB;
	int somaK;


	for (int x = 0; x < aux.cols; x++) {
		for (int y = 0; y < aux.rows; y++) {
			for (int linha = -1; linha <= 1; linha++) {
				for (int coluna = -1; coluna <= 1; coluna++) {
					if ((x + linha) >= 0 && (x + linha) < aux.cols) {
						if ((y + coluna) >= 0 && (y + coluna) < aux.rows) {
							pixel = aux.at<Vec3b>(x + linha, y + coluna);

							somaR += filtro[linha + 1][coluna + 1] * pixel[2]; //Multiplica Vermelho
							somaG += filtro[linha + 1][coluna + 1] * pixel[1]; //Multiplica Verde
							somaB += filtro[linha + 1][coluna + 1] * pixel[0]; //Multiplica azul
							somaK += filtro[linha + 1][coluna + 1];
						}
					}
				}
			}

			//Para evitar divisão por zero

			if (somaK == 0) {
				pixel[2] = somaR;
				pixel[1] = somaG;
				pixel[0] = somaB;
			}
			else {
				if (somaR / somaK > 255)
					pixel[2] = 255;
				else if (somaR / somaK < 0)
					pixel[2] = 0;
				else
					pixel[2] = somaR / somaK;

				if (somaG / somaK > 255)
					pixel[1] = 255;
				else if (somaG / somaK < 0)
					pixel[1] = 0;
				else
					pixel[1] = somaG / somaK;
				if (somaB / somaK > 255)
					pixel[0] = 255;
				else if (somaB / somaK < 0)
					pixel[0] = 0;
				else
					pixel[0] = somaB / somaK;
			}

			//Reseta os valores após isso

			somaR = 0;
			somaG = 0;
			somaB = 0;
			somaK = 0;
			aux.at<Vec3b>(x, y) = pixel;

		}
	}
	return aux;
}

int** PDI::kernelCentroPositivo() {
	//soma 256
	int tamanho = 3;
	int **kernelt = new int*[tamanho];
	kernelt[0] = new int[tamanho * tamanho];
	for (int i = 1; i < tamanho; i++) {
		kernelt[i] = kernelt[i - 1] + tamanho;
	}

	kernelt[0][0] = 0;
	kernelt[0][1] = 1;
	kernelt[0][2] = 0;

	kernelt[1][0] = 1;
	kernelt[1][1] = 1;
	kernelt[1][2] = 1;

	kernelt[2][0] = 0;
	kernelt[2][1] = 1;
	kernelt[2][2] = 0;

	return kernelt;
}

int RetornaPontoCentral(int atual, int TamKernel) {
	int retorno = (atual + (TamKernel / 2));
	return retorno;
}

Mat PDI::Erosao(Mat imagemBase) {

	Mat aux = imagemBase.clone();

	int TamKernel = 5;
	int PosicaoInicial = TamKernel / 2;
	int PosicaoFinalX = aux.rows - TamKernel;
	int PosicaoFinalY = aux.cols - TamKernel;
	int PosicaoFinalI = TamKernel - 1;
	int PosicaoFinalJ = TamKernel - 1;
		
	Vec3b pixelReferencia;
	Vec3b pixelCor;

	Vec3b Branco;
	Branco[0] = 255;
	Branco[1] = 255;
	Branco[2] = 255;
	
	Vec3b Preto;
	Preto[0] = 0;
	Preto[1] = 0;
	Preto[2] = 0;

	int  ElementoEstruturante[5][5]{
		255,255,255,255,255,
		255,255,255,255,255,
		255,255,0,0,0,
		255,255,0,0,0,
		255,255,0,0,0,
	};
	
	for (int x = PosicaoInicial; x < PosicaoFinalX; x++) {
		for (int y = PosicaoInicial; y < PosicaoFinalY; y++) {
			
			for (int i = 0; i < PosicaoFinalI; i++) {
				for (int j = 0; j < PosicaoFinalJ; j++) {
					
					pixelReferencia = imagemBase.at<Vec3b>( (x + i), (y + j) );

					if (pixelReferencia[0] != ElementoEstruturante[i][j])
					{
						pixelCor = Preto;
						break;
					}
					else
					{
						pixelCor = Branco;
					}
				}
			}

			aux.at<Vec3b>((RetornaPontoCentral(x, TamKernel)), (RetornaPontoCentral(y, TamKernel))) = pixelCor;
		}
	}
	
	return aux;
}





Mat PDI::Dilatacao(Mat imagemBase) {

	int** kernel = kernelCentroPositivo();
	Mat aux = imagemBase.clone();
	//float soma = 0;
	//int tamanhoKernel = 3;
	//int desl = tamanhoKernel;

	int  ElementoExtruturante[5][5]{
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,1,1,1,
		0,0,1,1,1,
	};


	for (int x = 1; x < aux.rows - 1; x++) {
		for (int y = 1; y < aux.cols - 1; y++) {
			for (int i = x; i <= x; i++) {
				for (int j = y; j <= y; j++) {

					Vec3b pixelCentral = imagemBase.at<Vec3b>(i, j);
					Vec3b pixelCima = imagemBase.at<Vec3b>(i - 1, j);
					Vec3b pixelEsquerda = imagemBase.at<Vec3b>(i, j - 1);
					Vec3b pixelDireita = imagemBase.at<Vec3b>(i, j + 1);
					Vec3b pixelBaixo = imagemBase.at<Vec3b>(i + 1, j);



					int vetor[5];
					vetor[0] = pixelCentral[0];
					vetor[1] = pixelCima[0];
					vetor[2] = pixelEsquerda[0];
					vetor[3] = pixelDireita[0];
					vetor[4] = pixelBaixo[0];

					if (ValidaElementoDilatacao(vetor)) {
						pixelCentral[0] = 255;
						pixelCentral[1] = 255;
						pixelCentral[2] = 255;
					}
					else
					{
						pixelCentral[0] = 0;
						pixelCentral[1] = 0;
						pixelCentral[2] = 0;
					}

					aux.at<Vec3b>(x, y) = pixelCentral;
				}
			}
		}
	}

	return aux;
}



bool PDI::ValidaElementoDilatacao(int vetor[5]) {
	for (int i = 0; i < 5; i++)
	{
		if (vetor[i] ==255)
			return true;
	}

	return false;

}

bool PDI::ValidaElementoErosao(int vetor[5]) {
	for (int i = 0; i < 5; i++)
	{
		if (vetor[i] == 0)
			return true;
	}

	return false;

}

Vec3b PDI::Cor(int cor) {

	Vec3b corRetorno;

	if (cor == 255 || cor == 1)
	{
		corRetorno[0] = 255;
		corRetorno[1] = 255;
		corRetorno[2] = 255;

		return corRetorno;
	}
	else if(cor == 0)
	{
		corRetorno[0] = 0;
		corRetorno[1] = 0;
		corRetorno[2] = 0;

		return corRetorno;
	}
}




