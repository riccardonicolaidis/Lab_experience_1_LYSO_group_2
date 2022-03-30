
void Na_LYSO_NaI1_NaI2(TString Fname="../DST/Na1_LYSO_NaI1_NaI2.dst"){
  TTree* tree = new TTree("tree","data from ascii file");
  tree->ReadFile(Form("%s",Fname.Data()),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T24/F");

  tree->Draw("-A4:-A2", "-A2<0.05e-6  && -A4<4e-9 && abs(T12)<0.1e-6  && -A1<15e-9 && -A1>4e-9 && abs(T24+0.3e-6)<0.1e-6","colz");

TCanvas* c2 = new TCanvas();
  TH1D* h1 = new TH1D("h1",";NaI2[V s];Events",200,0,50e-9);
  tree->Draw("-A2>>h1", "-A4<0.75e-9 && -A4>0.25e-9 && abs(T12)<0.1e-6  && -A1<15e-9 && -A1>4e-9 && abs(T24+0.3e-6)<0.1e-6", "");
  TF1* f1 = new TF1("f1","[0]+gaus(1)",0,50e-9);
  f1->SetParameter(0,0);
  f1->SetParameter(1,10);
  f1->SetParameter(2,40.e-9); //centro gaussiana
  f1->SetParameter(3,3e-9); //sigma gaussiana
  h1->Fit("f1","L", " ", 37e-9, 47e-9); //L:likelyhood 
  //h1->GetXaxis()->SetTitle("NaI2 (Vxs)");
  double p1 = f1->GetParameter(2); //centro gaussiana
  double ep1 = f1->GetParError(2); //suo errore
  double s1 = f1->GetParameter(3); //sigma gaussiana
  double e1 = f1->GetParError(3);  //suo errore
 cout << "NaI2" <<endl;
 cout << "1275 keV@ " << p1 << "+-" << ep1 << endl;
 cout << "sig @ 1275 keV " << s1 << "+-" << e1 << endl;

TCanvas* c3 = new TCanvas();
  TH1D* h12 = new TH1D("h12","",200,0,50e-9);
  tree->Draw("-A2>>h12", "-A4<2.5e-9 && -A4>1e-9 && abs(T12)<0.1e-6  && -A1<15e-9 && -A1>4e-9 && abs(T24+0.3e-6)<0.1e-6", "");
  TF1* f12 = new TF1("f12","[0]+ [4]*x + gaus(1)",0,50e-9);
  f12->SetParameter(0,0);
  f12->SetParameter(1,10);
  f12->SetParameter(2,18.e-9); //centro gaussiana
  f12->SetParameter(3,2e-9); //sigma gaussiana
  f12->SetParameter(4,0);
  h12->Fit("f12","L", " ", 16e-9, 21e-9); //L:likelyhood 
  h12->GetXaxis()->SetTitle("NaI2 (Vxs)");
  double p12 = f12->GetParameter(2); //centro gaussiana
  double ep12 = f12->GetParError(2); //suo errore
  double s12 = f12->GetParameter(3); //sigma gaussiana
  double e12 = f12->GetParError(3);  //suo errore

  cout << "NaI2" <<endl;
 cout << "511 keV@ " << p12 << "+-" << ep12 << endl;
 cout << "sig @ 511 keV " << s12 << "+-" << e12 << endl;


 TCanvas* c4 = new TCanvas();
  TH1D* h22 = new TH1D("h22","",200,0,50e-9);
  tree->Draw("-A1>>h22", "-A2<45e-9  && -A2>37e-9&& -A4<1e-9 && -A4>0.25e-9 && abs(T12)<0.1e-6  && abs(T24+0.3e-6)<0.1e-6", "");
  TF1* f22 = new TF1("f22","[0]+ [4]*x + gaus(1)",0,50e-9);
  f22->SetParameter(0,0);
  f22->SetParameter(1,10);
  f22->SetParameter(2,18.e-9); //centro gaussiana
  f22->SetParameter(3,2e-9); //sigma gaussiana
  f22->SetParameter(4,0);
  h22->Fit("f22","L", " ", 7e-9, 20e-9); //L:likelyhood 
  h22->GetXaxis()->SetTitle("NaI1 (Vxs)");
  double p22 = f22->GetParameter(2); //centro gaussiana
  double ep22 = f22->GetParError(2); //suo errore
  double s22 = f22->GetParameter(3); //sigma gaussiana
  double e22 = f22->GetParError(3);  //suo errore
 
 cout << "NaI1" <<endl;
 cout << "511 keV@ " << p22 << "+-" << ep22 << endl;
 cout << "sig @ 511 keV " << s22 << "+-" << e22 << endl;

TCanvas* c5 = new TCanvas();
  TH1D* h31 = new TH1D("h31","",200,0,5e-9);
  tree->Draw("-A4>>h31", "-A2<20e-9  && -A2>15e-9&& -A1<15e-9 && -A1>4e-9 && abs(T12)<0.1e-6  && abs(T24+0.3e-6)<0.1e-6", "");
  TF1* f31 = new TF1("f31","[0]+ [4]*x + gaus(1)",0,50e-9);
  f31->SetParameter(0,0);
  f31->SetParameter(1,10);
  f31->SetParameter(2,2.e-9); //centro gaussiana
  f31->SetParameter(3,0.2e-9); //sigma gaussiana
  f31->SetParameter(4,0);
  h31->Fit("f31","L", " ", 1.5e-9, 2.5e-9); //L:likelyhood 
  h31->GetXaxis()->SetTitle("LYSO (Vxs)");
  double p31 = f31->GetParameter(2); //centro gaussiana
  double ep31 = f31->GetParError(2); //suo errore
  double s31 = f31->GetParameter(3); //sigma gaussiana
  double e31 = f31->GetParError(3);  //suo errore
 
 cout << "LYSO" <<endl;
 cout << "1275 keV@ " << p31 << "+-" << ep31 << endl;
 cout << "sig @ 1275 keV " << s31 << "+-" << e31 << endl;

TCanvas* c6 = new TCanvas();
  TH1D* h32 = new TH1D("h32","",200,0,5e-9);
  tree->Draw("-A4>>h32", "-A2<45e-9 && -A2>40e-9&& -A1<15e-9 && -A1>4e-9 && abs(T12)<0.1e-6 && abs(T24+0.3e-6)<0.1e-6", "");
  TF1* f32 = new TF1("f32","[0]+ [4]*x + gaus(1)",0,50e-9);
  f32->SetParameter(0,0);
  f32->SetParameter(1,10);
  f32->SetParameter(2,2.e-9); //centro gaussiana
  f32->SetParameter(3,0.2e-9); //sigma gaussiana
  f32->SetParameter(4,0);
  h32->Fit("f32","L", " ", 0.1e-9, 1e-9); //L:likelyhood 
  h32->GetXaxis()->SetTitle("LYSO (Vxs)");
  double p32 = f32->GetParameter(2); //centro gaussiana
  double ep32 = f32->GetParError(2); //suo errore
  double s32 = f32->GetParameter(3); //sigma gaussiana
  double e32 = f32->GetParError(3);  //suo errore
 
 cout << "LYSO" <<endl;
 cout << "511 keV@ " << p32 << "+-" << ep32 << endl;
 cout << "sig @ 511 keV " << s32 << "+-" << e32 << endl;

  // suggestion how to proceed:
  // evnum>2550e3 select run with strong source between NaI1 and LYSO
  // -A1<15e-9 should select 511keV in NaI1 (the rest is compton)
  // 0.5e-9<-A4<1.e-9 should be 511keV in LYSO then the 1275keV is shown in NaI2
  // -A4 similar to 1.8e-9 should be 1275keV in LYSO and 15e-9<-A2<20e-9 sould be 511keV in NaI2
  return;
  tree->SetAlias("E1","201.8+(-A1-7.500416e-09)*(306.8-201.8)/(1.111327e-08-7.500416e-09)");
  tree->SetAlias("E2","201.8+(-A2-8.962911e-09)*(306.8-201.8)/(1.337650e-08-8.962911e-09)");
}
