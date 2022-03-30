void Co_LYSO_NaI12(TString Fname = "../DST/Co1_LYSO_NaI1_NaI2.dst")
{
	TTree *tree = new TTree("tree", "data from ascii file");
	tree->ReadFile(Form("%s", Fname.Data()),
		       "evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T/F");

	tree->SetAlias("E1", "201.8+(-A1-7.500416e-09)*(306.8-201.8)/"
			     "(1.111327e-08-7.500416e-09)");
	tree->SetAlias("E2", "201.8+(-A2-8.962911e-09)*(306.8-201.8)/"
			     "(1.337650e-08-8.962911e-09)");

	TCanvas *c1 = new TCanvas();
	// TH2D* hh1 = new TH2D("hh1","",50,1000,1400,80,0,2.5e-9);
	tree->Draw("-A4:-A1", "-A1<60e-9 && -A4<5e-9", "colz");

	TCanvas *c2 = new TCanvas();
	// TH2D* hh1 = new TH2D("hh1","",50,1000,1400,80,0,2.5e-9);
	tree->Draw("-A4:-A2", "", "colz");

	TCanvas *c3 = new TCanvas();
	tree->Draw("-A2", "-A2 < -1.4e-9", "");
	TH1D *h1 = new TH1D("h1", "", 200, -2e-9, -1.4e-9);
	tree->Draw("-A2 >> h1", "-A2 < -1.4e-9", "");
	TF1 *f1 = new TF1("f1", "gaus(0)", -2e-9, -1.4e-9);
	f1->SetParameter(0, 800);
	f1->SetParameter(1, -1.7e-9);
	f1->SetParameter(2, 1e-11);		  // centro gaussiana
	h1->Fit("f1", "L", " ", -2e-9, -1.4e-9); // L:likelyhood
	h1->GetXaxis()->SetTitle("NaI2 (Vxs)");
	double p1 = f1->GetParameter(1); // centro gaussiana
	double ep1 = f1->GetParError(1); // suo errore
	double s1 = f1->GetParameter(2); // sigma gaussiana
	double e1 = f1->GetParError(2);	 // suo errore  return;

	cout << "Pedestal" << endl;
	cout << "0 keV@ " << p1 << "+-" << ep1 << endl;
	cout << "sig @ 0 keV " << s1 << "+-" << e1 << endl;

	/*
  comment: for co1 one has A1 and A4 for alibration. in the other case one has
  co2 for A2 and A4 for calibration.

  hh1->Smooth();

  hh1->GetXaxis()->SetRangeUser(1160,1240);
  TH1D* h11 = hh1->ProjectionY("h11");
  hh1->GetXaxis()->SetRangeUser(1300,1360);
  TH1D* h21 = hh1->ProjectionY("h21");
  hh1->GetXaxis()->SetRangeUser(1000,1400);
  TCanvas* c2 = new TCanvas();
  TH2D* hh2 = new TH2D("hh2","",50,800,1050,80,0,2.5e-9);
  tree->Draw("-A4:E2>>hh2","-A3<1.2e-9 && E2<1000 && T32>0.2e-6 && -A4<2.5e-9 &&
  E2>800 && evnum<6600000","colz");
  //hh2->Smooth();
  hh2->GetXaxis()->SetRangeUser(890,910);
  TH1D* h12 = hh2->ProjectionY("h12");
  hh2->GetXaxis()->SetRangeUser(940,960);
  TH1D* h22 = hh2->ProjectionY("h22");
  hh2->GetXaxis()->SetRangeUser(800,1050);

  TCanvas* c3 = new TCanvas();
  h11->Add(h12);
  h11->Draw();
  h12->Draw("same");
  h12->SetLineColor(4);
  TF1* f1 = new TF1("f1","pol1+gaus(2)+gaus(5)+gaus(8)",1.7e-9,2.5e-9);
  f1->SetParameter(0,23);
  f1->SetParameter(1,-9.e9);
  f1->SetParameter(3,1.93e-9);
  f1->SetParameter(4,0.06e-9);
  f1->SetParameter(6,2.12e-9);
  f1->SetParameter(7,0.048e-9);
  f1->SetParameter(9,2.35e-9);
  f1->SetParameter(10,0.08e-9);
  h11->Fit("f1","","",1.75e-9,2.5e-9);
  h11->Fit("f1","L","",1.75e-9,2.5e-9);
  double p1 = f1->GetParameter(6);
  double ep1 = f1->GetParError(6);
  double es1 = 0.5*(p1-f1->GetParameter(3));
  double s1 = f1->GetParameter(7);
  double e1 = f1->GetParError(7);

  TCanvas* c4 = new TCanvas();
  h21->Add(h22);
  h21->Draw();
  h22->Draw("same");
  h22->SetLineColor(4);
  TF1* f2 = new TF1("f2","pol1+gaus(2)+gaus(5)+gaus(8)",1.5e-9,2.5e-9);
  f2->SetParameter(0,10);
  f2->SetParameter(1,-4.e9);
  f2->SetParameter(3,1.65e-9);
  f2->SetParameter(4,0.08e-9);
  f2->SetParameter(6,1.86e-9);
  f2->SetParameter(7,0.09e-9);
  f2->SetParameter(9,2.2e-9);
  f2->SetParameter(10,0.047e-9);
  h21->Fit("f2","","",1.5e-9,2.5e-9);
  h21->Fit("f2","L","",1.5e-9,2.5e-9);
  double p2 = f2->GetParameter(6);
  double ep2 = f2->GetParError(6);
  double es2 = 0.5*(p2-f2->GetParameter(3));
  double s2 = f2->GetParameter(7);
  double e2 = f2->GetParError(7);

  cout << "1170 keV@ " << p2 << "+-" << ep2 << "+-" << es2 << endl;
  cout << "1330 keV@ " << p1 << "+-" << ep1 << "+-" << es1 << endl;

  cout << "sigma @ 1170 keV " << s2 << "+-" << e2 << endl;
  cout << "sigma @ 1330 keV " << s1 << "+-" << e1 << endl;
  return;
  */
}
