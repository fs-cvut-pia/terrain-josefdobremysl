#include "Letadlo.h"
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>


Letadlo::Letadlo(TerrainMap& m, std::string name_in, Point start_in, Point finish_in) : Path(m, name_in, start_in, finish_in) {
}

Letadlo::~Letadlo() {
}

bool Letadlo::find() {
	deque<Point> Body;
	deque<Point> Cesta;
	Body.push_back(start);
	int hodnota = 500;

	Matrix<double> vzdalenosti(map.nx, map.ny);
	for (int i = 1; i < 255; i++) {
		for (int j = 1; j < 255; j++) {
			vzdalenosti(i, j) = hodnota;
			vzdalenosti(start.x, start.y) = 0;
		}
	}

	int k;
	int l;
	int k_i;
	int l_j;
	int n = 0;
	cout << "letadlo" << endl;

	while (Body.size() > 1 || n < 10) {
		n++;
		std::cout << "Delka fronty: " << Body.size() << std::endl;
		Point aktualni_bod = Body[0];				// První prvek z kontejneru je aktuální bod
		Body.pop_front();
		k = aktualni_bod.x;					// Souřadnice aktuálního bodu 
		l = aktualni_bod.y;
		if (k < 3 || k >(map.nx - 3) || l < 3 || l >(map.ny - 3)) {			// Pokud je bod na kraji oblasti  
			
			Point aktualni_bod = Body[0];										// jako aktuální bod se vezme další bod z fronty 
			Body.pop_front();
		}
		for (int i = -1; i < 2; i++) {				// Cyklus přes všechny sousedy aktuálního bodu 
			for (int j = -1; j < 2; j++) {
				k = aktualni_bod.x;					// Souřadnice aktuálního bodu 
				l = aktualni_bod.y;
				k_i = aktualni_bod.x + i;			// Souřadnice sousedního bodu
				l_j = aktualni_bod.y + j;
				//cout << "777" << endl;
				if (k_i != start.x || l_j != start.y) {
					double wew = (vzdalenosti(k, l) + sqrt(2));
					if (vzdalenosti(k_i, l_j) > wew) {									// diagonalni prvky
						if (i != 0 && j != 0) {
							vzdalenosti(k_i, l_j) = vzdalenosti(k, l) + sqrt(2);
							Point bodN(k_i, l_j);
							Body.push_back(bodN);
							std::cout << k_i << "  " << l_j << "  " << vzdalenosti(k_i, l_j) << endl;
						}
					}
				
					double ww = (vzdalenosti(k, l) + 1);
					if (vzdalenosti(k_i, l_j) > ww) {									// nediagonalni prvky
						if (i == 0 && j != 0 || j == 0 && i != 0) {
			
							vzdalenosti(k_i, l_j) = vzdalenosti(k, l) + 1;
							Point bodN1(k_i, l_j);
							Body.push_back(bodN1);
						}
					}
				
				}				
			}
		}
	}
	cout << "Cesta nalezena" << endl;
		
	// Následuje zápis cesty do souboru

	int ki;
	int lj;

	Point bod_na_ceste;
	double val;

		string filename = "C:\\Users\\josef\\Desktop\\MAPA.dat";   // Otevření souboru pro zápis
		ofstream File(filename.c_str());						   // Matice vzdáleností
		for (int i = 0; i < 255; i++) {
			for (int j = 0; j < 255; j++) {
				File << vzdalenosti(i, j) << " ";
			}
			File << std::endl;
		}
		// Zavření souboru
		File.close();

		cout << "Soubor " << filename << " byl vytvo�en." << endl;
		Cesta.push_front(finish);
		Point aktualni_bod2 = finish;
		while (true) {
			aktualni_bod2 = Cesta[0];
			val = vzdalenosti(aktualni_bod2.x, aktualni_bod2.y);
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {

					k_i = aktualni_bod2.x + i;
					l_j = aktualni_bod2.y + j;

					if (vzdalenosti(k_i, l_j) < val) {
						val = vzdalenosti(k_i, l_j);

							ki = k_i;
							lj = l_j;
						}
					}
				}
				Point bod_na_ceste(ki, lj);
				Cesta.push_front(bod_na_ceste);			
				if (aktualni_bod2 == start) {
					string filename = "C:\\Users\\josef\\Desktop\\Letadlo.dat";
					ofstream File(filename.c_str());
					for (Point u : Cesta) {
						File << u.x << " " << u.y << std::endl;
					}
					File.close();						// Z�v�r souboru
					cout << "Soubor " << filename << " byl vytvořen." << endl;
					
					std::exit(6);
				}
			}
	return false;	
}

