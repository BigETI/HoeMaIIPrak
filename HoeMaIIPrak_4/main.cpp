#include <iostream>
#include <fstream>
#include <vector>
#include "Fourier.h"

using namespace std;

vector<CKomplex>  werte_einlesen(char *dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	ifstream fp;
	fp.open(dateiname);
	if (fp.is_open())
	{
		fp >> N;
		werte.resize(N);
		CKomplex null(0, 0);
		for (i = 0; i < N; i++)
			werte[i] = null;
		while (!fp.eof())
		{
			fp >> idx >> re >> im;
			CKomplex a(re, im);
			werte[idx] = a;
		}
		fp.close();
	}
	return werte;
}

void werte_ausgeben(char *dateiname, vector<CKomplex> & werte, double epsilon = -1.0)
{
	int i;
	int N = werte.size();
	ofstream fp;
	fp.open(dateiname);
	if (fp.is_open())
	{
		fp << N << endl;
		for (i = 0; i < N; i++)
			if (werte[i].abs() > epsilon)
				fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
		fp.close();
	}
}

vector<CKomplex> abweichung(vector<CKomplex> & a, vector<CKomplex> & b)
{
	vector<CKomplex> ret;
	if (a.size() == b.size())
	{
		for (size_t i(0U), sz(a.size()); i != sz; i++)
			ret.push_back(b[i] - a[i]);
	}
	return ret;
}

double abs_max_complex_vec(vector<CKomplex> & cs)
{
	double ret(0.0), t;
	bool first(true);
	for (vector<CKomplex>::iterator it(cs.begin()), end(cs.end()); it != end; ++it)
	{
		t = (abs(it->re()) > abs(it->im())) ? it->re() : it->im();
		if (first)
		{
			first = false;
			ret = t;
		}
		else
		{
			if (abs(ret) < abs(t))
				ret = t;
		}
	}
	return ret;
}

int main(int argc, char *argv[])
{
	vector<CKomplex> werte(werte_einlesen("Daten_original.txt"));
	vector<CKomplex> transformiert(Fourier::hin(werte));
	vector<CKomplex> n_werte;
	vector<CKomplex> delta;
	werte_ausgeben("Daten_transformiert_default.txt", transformiert);
	werte_ausgeben("Daten_transformiert_0_1.txt", transformiert, 0.1);
	werte_ausgeben("Daten_transformiert_1.txt", transformiert, 1.0);

	transformiert = werte_einlesen("Daten_transformiert_default.txt");
	n_werte = Fourier::zurueck(transformiert);
	werte_ausgeben("Daten_neu_default.txt", n_werte);
	delta = abweichung(werte, n_werte);
	werte_ausgeben("Daten_abweichungen_default.txt", delta);
	cout << "Maximale Abweichung bei Standard-Epsilon: " << abs_max_complex_vec(delta) << endl;

	transformiert = werte_einlesen("Daten_transformiert_0_1.txt");
	n_werte = Fourier::zurueck(transformiert);
	werte_ausgeben("Daten_neu_0_1.txt", n_werte);
	delta = abweichung(werte, n_werte);
	werte_ausgeben("Daten_abweichungen_0_1.txt", delta);
	cout << "Maximale Abweichung bei epsilon=0.1: " << abs_max_complex_vec(delta) << endl;

	transformiert = werte_einlesen("Daten_transformiert_1.txt");
	n_werte = Fourier::zurueck(transformiert);
	werte_ausgeben("Daten_neu_1.txt", n_werte);
	delta = abweichung(werte, n_werte);
	werte_ausgeben("Daten_abweichungen_1.txt", delta);
	cout << "Maximale Abweichung bei epsilon=1.0: " << abs_max_complex_vec(delta) << endl;
	
	getchar();
	
	return 0;
}