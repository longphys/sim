#include "TRandom3.h"
#include "TH1D.h"
#include "TCanvas.h"

void test()
{
	TRandom3* rnd = new TRandom3();
	rnd->SetSeed();
	TH1D* h = new TH1D("h", "histo", 200, -10.0, 10.0);
	int N = 10000;
	for (int i = 0; i < N; i++)
	{
		h->Fill(rnd->Gaus(0.0, 1.0));
	}
	TCanvas* c1 = new TCanvas("c1", "c1", 500, 500);
	c1->cd();
	h->Draw();
}
