#include "Letadlo.h"
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>


Letadlo::Letadlo(TerrainMap& m, std::string name_in, Point start_in, Point finish_in) : Path(m, name_in, start_in, finish_in){
}

Letadlo::~Letadlo(){
}

bool Letadlo::find() {

	cout << "Letadlo  --  Letadlo  -- Letadlo" << endl;
	deque<Point> Body;
	deque<Point> Cesta;
	Body.push_back(start);
	double hodnota = 500;
	Matrix<double> vzdalenosti(map.nx, map.ny);
	for (int i = 1; i < 255; i++) {
		for (int j = 1; j < 255; j++) {
			vzdalenosti(i, j) = hodnota;
			vzdalenosti(start.x, start.y) = 0;
		}
	}
	//Matrix<Point> predchozi_pole(map.nx, map.ny);

	int k;
	int l;
	int k_i;
	int l_j;
	bool B = true;

	while (B==true) {
		Point aktualni_bod = Body[0];
		if (!Body.empty()) {
			Body.pop_front();
		}

		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				//std::cout << "i" << i << "  " << "j" << j << endl;
				k = aktualni_bod.x;
				l = aktualni_bod.y;
				k_i = aktualni_bod.x + i;
				l_j = aktualni_bod.y + j;
				//cout << "aktu1 " << aktualni_bod.x << aktualni_bod.y << endl;
				
				while (k < 3 || k >(map.nx-3) || l < 3 || l >(map.ny - 3)) {
					Body.pop_front();
			
					Point aktualni_bod = Body[0];
					//cout << "aktu2 " << aktualni_bod.x << aktualni_bod.y << endl;

					k = aktualni_bod.x;
					l = aktualni_bod.y;
					k_i = k + i;
					l_j = l + j;
				}

				if (k_i != start.x && l_j != start.y) {
					double wew = (vzdalenosti(k, l) + sqrt(2));
					if (vzdalenosti(k_i, l_j) > wew ) {	// diagonalni prvky


						if (i != 0 && j != 0) {

							vzdalenosti(k_i, l_j) = vzdalenosti(k, l) + sqrt(2);
							Point bodN(k_i, l_j);
							Body.push_back(bodN);
							std::cout << k_i << "  " << l_j << "  " << vzdalenosti(k_i, l_j) << endl;
						}
					}
					double ww = (vzdalenosti(k, l) + 1);
					if (vzdalenosti(k_i, l_j) > ww ) {		// nediagonalni prvky
						if (i == 0 && j != 0 || j == 0 && i != 0) {
							//std::cout << "899999999999999999999******************" << endl;
							vzdalenosti(k_i, l_j) = vzdalenosti(k, l) + 1;
							Point bodN1(k_i, l_j);
							std::cout << k_i << "  " << l_j << "  " << vzdalenosti(k_i, l_j) << endl;
							std::cout << "Delka fronty: " << Body.size() << std::endl;

							Body.push_back(bodN1);
							//std::cout << 30 << "  " << 28 << "  " << vzdalenosti(100, 58) << endl;
						}
					}
				}

			}
			
		}
		int ki;
		int lj;

		Point bod_na_ceste;
		double val;
		if (k_i==9 && l_j == 2) {


			for (Point element : Body) {
				std::cout <<"x" << element.x << " " << "y" << element.x << " ";
			}
			std::cout << "-------------------------------------------------------------------------" << endl;
			string filename = "C:\\Users\\josef\\Desktop\\MAPA.dat";
			// Otevøení souboru pro zápis
			ofstream File(filename.c_str());
			for (int i = 0; i < 255;i++) {
				for (int j = 0; j < 255; j++) {
					File << vzdalenosti(i,j) << " ";
					
				}
				File << std::endl;
			}
			// Závìr souboru
			File.close();

			cout << "Soubor " << filename << " byl vytvoøen." << endl;
			Cesta.push_front(finish);
			Point aktualni_bod2 = finish;
			while (true) {
				aktualni_bod2 = Cesta[0];
				std::cout << "x " << aktualni_bod2.x << " y " << aktualni_bod2.y << endl;
				val = vzdalenosti(aktualni_bod2.x, aktualni_bod2.y);
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						std::cout << "i " << i << " j " << j << endl;

						k_i = aktualni_bod2.x + i;
						l_j = aktualni_bod2.y + j;
						std::cout << vzdalenosti(k_i, l_j) << " " << val << endl;
						if (vzdalenosti(k_i, l_j) < val) {
							val = vzdalenosti(k_i, l_j);
							std::cout << "****" << endl;
							std::cout << "Delka fronty: " << Body.size() << std::endl;
							ki = k_i;
							lj = l_j;

						}
					}
				}
				Point bod_na_ceste(ki, lj);
				std::cout << "xx " << bod_na_ceste.x << " yy " << bod_na_ceste.y << endl;
				Cesta.push_front(bod_na_ceste);
				//aktualni_bod2 = bod_na_ceste;
			if (aktualni_bod2 == start) {

				string filename = "C:\\Users\\josef\\Desktop\\Letadlo.dat";
				// Otevøení souboru pro zápis
				ofstream File(filename.c_str());
				for (Point u : Cesta) {
					File << u.x << " " << u.y << std::endl;
				}
				// Závìr souboru
				File.close();

				cout << "Soubor " << filename << " byl vytvoøen." << endl;
				B = false;
				break;
				//std::exit(6);
			}
			}
		}
	}
	
	return false;
	}



