
void CoPedestalLYSO(TString Fname="../DST/CoPedestalLYSO.dst"){
  TTree* tree = new TTree("tree","data from ascii file");
  tree->ReadFile(Form("%s",Fname.Data()),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T14/F");
  TCanvas* c1 = new TCanvas();
  tree->Draw("-A1:-A2", "-A2<0.07e-6 && -A1<0.07e-6 && -A4<0.1e-9 && abs(T12-0.05e-6)<0.05e-6", "colz");
  TCanvas* c2 = new TCanvas();
  tree->Draw("-A4:T12", "-A2<0.07e-6 && -A1<0.07e-6", "colz");
  
  TCanvas* c3 = new TCanvas();
  TH1D* h1 = new TH1D("h1","",300,10e-9,70e-9);
    tree->Draw("-A1>>h1","-A2<41.5e-9 && -A2>36e-9 && -A1<0.07e-6 && -A4<0.1e-9 && abs(T12-0.05e-6)<0.05e-6", "");
    TF1* f1 = new TF1("f1","[0]+gaus(1)",10e-9,70e-9);
  f1->SetParameter(0,0);
  f1->SetParameter(1,18);
  f1->SetParameter(2,55e-9);
  f1->SetParameter(3,3e-9);
  h1->Fit("f1","L", "", 45e-9,65e-9);
  h1->GetXaxis()->SetTitle("NaI1 (Vxs)");
  double p1 = f1->GetParameter(2);
  double ep1 = f1->GetParError(2);
  double s1 = f1->GetParameter(3);
  double e1 = f1->GetParError(3);
  
  cout << "NaI1 1332 keV" << endl;
  cout << p1 << "+/-" << ep1 << endl;
  cout << s1 << "+/-" << e1 << endl;
  
  TCanvas* c4 = new TCanvas();
  TH1D* h2 = new TH1D("h2","",300,10e-9,70e-9);
    tree->Draw("-A1>>h2","-A2<47e-9 && -A2>42.5e-9 && -A1<0.7e-6 && -A4<0.1e-9 && abs(T12-0.05e-6)<0.05e-6", "");
    TF1* f2 = new TF1("f2","[0]+gaus(1)",10e-9,70e-9);
  f2->SetParameter(0,0);
  f2->SetParameter(1,18);
  f2->SetParameter(2, 50e-9);
  f2->SetParameter(3,3e-9);
  h2->Fit("f2","L", "", 45e-9,65e-9);
  h2->GetXaxis()->SetTitle("NaI (Vxs)");
  double p2 = f2->GetParameter(2);
  double ep2 = f2->GetParError(2);
  double s2 = f2->GetParameter(3);
  double e2 = f2->GetParError(3);
  
  cout << "NaI1 1173 keV" << endl;
  cout << p2 << "+/-" << ep2 << endl;
  cout << s2 << "+/-" << e2 << endl;
  
  
  TCanvas* c5 = new TCanvas();
  TH1D* h11 = new TH1D("h11","",300,10e-9,70e-9);
    tree->Draw("-A2>>h11","-A1<52.5e-9 && -A1>47.5e-9 && -A2<0.07e-6 && -A4<0.1e-9 && abs(T12-0.05e-6)<0.05e-6", "");
    TF1* f11 = new TF1("f11","[0]+gaus(1)",10e-9,70e-9);
  f11->SetParameter(0,0);
  f11->SetParameter(1,18);
  f11->SetParameter(2,55e-9);
  f11->SetParameter(3,3e-9);
  h11->Fit("f11","L", "", 37e-9,50e-9);
  h11->GetXaxis()->SetTitle("NaI2 (Vxs)");
  double p11 = f11->GetParameter(2);
  double ep11 = f11->GetParError(2);
  double s11 = f11->GetParameter(3);
  double e11 = f11->GetParError(3);
  
  cout << "NaI2 1332 keV" << endl;
  cout << p11 << "+/-" << ep11 << endl;
  cout << s11 << "+/-" << e11 << endl;
  
  TCanvas* c6 = new TCanvas();
  TH1D* h22 = new TH1D("h22","",300,10e-9,70e-9);
    tree->Draw("-A2>>h22","-A1<59e-9 && -A1>52.5e-9 && -A2<0.7e-6 && -A4<0.1e-9 && abs(T12-0.05e-6)<0.05e-6", "");
    TF1* f22 = new TF1("f22","[0]+gaus(1)",10e-9,70e-9);
  f22->SetParameter(0,0);
  f22->SetParameter(1,18);
  f22->SetParameter(2, 50e-9);
  f22->SetParameter(3,3e-9);
  h22->Fit("f22","L", "", 35e-9,45e-9);
  h22->GetXaxis()->SetTitle("NaI2 (Vxs)");
  double p22 = f22->GetParameter(2);
  double ep22 = f22->GetParError(2);
  double s22 = f22->GetParameter(3);
  double e22 = f22->GetParError(3);
  
  cout << "NaI2 1173 keV" << endl;
  cout << p22 << "+/-" << ep22 << endl;
  cout << s22 << "+/-" << e22 << endl;
  return;
	
/* tree->SetAlias("E1","201.8+(-A1-7.500416e-09)*(306.8-201.8)/(1.111327e-08-7.500416e-09)");
  tree->SetAlias("E2","201.8+(-A2-8.962911e-09)*(306.8-201.8)/(1.337650e-08-8.962911e-09)");

  
  TH2D* hh = new TH2D("hh","",15,300,700,15,300,700);
  tree->Draw("E2:E1>>hh","T31>0.05e-6 && T31<0.4e-6 && T32>0.05e-6 && E2<700 && E1<700 && -A4>0.5e-9 && -A4<2.5e-9","colz"); 
  hh->Smooth();
  
  
  TH1D* h1 = new TH1D("h1","",30,0.5e-9,3e-9);
  tree->Draw("-A4>>h1","T32+T31<0.35e-6 && T31>0.05e-6 && T31<0.4e-6 && T32>0.05e-6 && E2<1300 && E1<1300 && E2>470 && E2<620 && E1>480 && E1<620 && -A3<1.3e-9","");
  /*TF1* f1 = new TF1("f1","[0]+gaus(1)",0.5e-9,2.5e-9);
  f1->SetParameter(0,0);
  f1->SetParameter(1,1);
  f1->SetParameter(2,2.e-9);
  f1->SetParameter(3,0.5e-9);
  h1->Fit("f1","L");
  h1->GetXaxis()->SetTitle("LYSO (Vxs)");
  double p1 = f1->GetParameter(2);
  double ep1 = f1->GetParError(2);
  double s1 = f1->GetParameter(3);
  double e1 = f1->GetParError(3);

  
  TH2D* hh2 = new TH2D("hh2","",15,0,800,15,0,1.5e-9);
  tree->Draw("-A4:E2>>hh2","T31>0.05e-6 && T31<0.4e-6 && T32>0.05e-6 && -A3<1.3e-9 && E1>800","colz");
  hh2->Smooth();
  hh2->GetXaxis()->SetTitle("NaI2 [keV]");
  hh2->GetYaxis()->SetTitle("LYSO signal [Vxs]");
    
  TCanvas* c4 = new TCanvas();
  TH1D* h2 = new TH1D("h2","",30,0,1.1e-9);
  tree->Draw("-A4>>h2","T31>0.05e-6 && T31<0.4e-6 && T32>0.05e-6 && E2>470 && E2<620 && E1>950 && E1<1620 && -A3<1.3e-9","");
  TF1* f2 = new TF1("f2","[0]+gaus(1)",0.,1.1e-9);
  f2->SetParameter(0,0);
  f2->SetParameter(1,1);
  f2->SetParameter(2,0.7e-9);
  f2->SetParameter(3,0.5e-9);
  h2->Fit("f2","L");
  h2->GetXaxis()->SetTitle("LYSO (Vxs)");
  double p2 = f2->GetParameter(2);
  double ep2 = f2->GetParError(2);
  double s2 = f2->GetParameter(3);
  double e2 = f2->GetParError(3);

  cout << "511 keV@ " << p2 << "+-" << ep2 << endl;
  cout << "1275 keV@ " << p1 << "+-" << ep1 << endl;

  cout << "sig @ 511 keV " << s2 << "+-" << e2 << endl;
  cout << "sig @ 1275 keV " << s1 << "+-" << e1 << endl;

  //hh1->Smooth();
  return;
*/

}
