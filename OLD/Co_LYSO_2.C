
void Co_LYSO_2(TString Fname="../DST/Co2_1.dst"){
  // Default file coem argomento della funzione
  // TTree : classe di root per gestire variabili
  // Il metodo fondamentale 'e il costruttore
  // Stringa con nome e titolo
  // Per info vai su root TTree::TTree(e tab
  TTree* tree = new TTree("tree","data from ascii file");
  tree->ReadFile(Fname.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");
  // Stringa costruita con la descrizione del contenuto delle colonne. I : sono i separatori delle variabili
  //  tree->Draw("-A4-A3:T34", "-A3<6e-8 && -A4<6e-8 && abs(T34+5e-9)<7e-9 && abs(T32)<2e-8 && T34!=0 ", "colz");
  //  tree->Draw("-A4:-A3", "-A3<6e-8 && -A4<6e-8 && abs(T34+5e-9)<7e-9 && abs(T32)<2e-8 && T34!=0", "colz");
  //  tree->Draw("T34:T32", "abs(T34+5e-9)<7e-9 && abs(T32)<2e-8", "colz");
  
  tree->Draw("-A4:-A3", "-A3<0.6e-7 && -A4<0.6e-7", "colz");
  TH2D* h2D = new TH2D("h2D",";NaI1[V s];NaI2 [V s]",200,0,60e-9,200,0,60e-9);
  tree->Draw("T34:-A3/PK3", "-A3<0.6e-7 && -A4<0.6e-7 && abs(T34+5e-9)<2e-8 && T34!=0", "colz");
  tree->Draw("-A4:-A3>>h2D", "-A3<0.6e-7 && -A4<0.6e-7 && abs(T34+5e-9)<2e-8 && T34!=0", "colz");
  
     
TCanvas* c2 = new TCanvas();
  TH1D* h1 = new TH1D("h1",";NaI1[V s];Events",200,0,60e-9);
  tree->Draw("-A3>>h1", "-A3<0.6e-7 && -A4<42e-9 && -A4>37e-9 && abs(T34+5e-9)<2e-8 && T34!=0", "");
  h1->SetLineColor(kRed+2);
  
  
  TF1* f1 = new TF1("f1","[0]+gaus(1)",0,50e-9);
  TF1* f2 = new TF1("f2","[0]+gaus(1)+[4]*x",0,50e-9);
  f1->SetParameter(0,0); 
  f1->SetParameter(1,30);
  f1->SetParameter(2,40.e-9);           //centro gaussiana
  f1->SetParameter(3,1e-9);             //sigma gaussiana
  h1->Fit("f1","L", "", 35e-9, 50e-9); //L:likelyhood 
  f1->SetLineColor(kGreen-3);
  f2->SetParameter(0,0);
  f2->SetParameter(1,30);
  f2->SetParameter(2,40.e-9);           //centro gaussiana                                                                    
  f2->SetParameter(3,1e-9);             //sigma gaussiana                                                                     
  h1->Fit("f2","L", "", 35e-9, 50e-9); //L:likelyhood
 

  f1->Draw("same");
  //h1->GetXaxis()->SetTitle("NaI2 (Vxs)");
  double p1 = f1->GetParameter(2); //centro gaussiana
  double ep1 = f1->GetParError(2); //suo errore
  double s1 = f1->GetParameter(3); //sigma gaussiana
  double e1 = f1->GetParError(3);  //suo errore
 cout << "NaI1" <<endl;
 cout << "1100 keV@ " << p1 << "+-" << ep1 << endl;
 cout << "sig @ 1100 keV " << s1 << "+-" << e1 << endl;
 return;
  
TCanvas* c3 = new TCanvas();
  TH1D* h12 = new TH1D("h12","",50,0,12e-9);
  tree->Draw("-A2>>h12", "abs(-A3-A4-38e-9)<1e-9 &&    abs(-A3-20e-9)<5e-9 &&   abs(-A4-18e-9)<5e-9 && abs(T34+5e-9)<7e-9 && abs(T32)<2e-8 && T34!=0", "colz");
  

  
  TF1* f12 = new TF1("f12","[0]*exp(-x/[4]) + gaus(1)",0,50e-9);
  f12->SetParameter(0,1);
  f12->SetParameter(1,10);
  f12->SetParameter(2,6e-9); //centro gaussiana
  f12->SetParameter(3,2e-9); //sigma gaussiana
  f12->SetParameter(4,2e-9);
  h12->Fit("f12","L", " ", 3e-9, 9e-9); //L:likelyhood 
  h12->GetXaxis()->SetTitle("LYSO (Vxs)");
  double p12 = f12->GetParameter(2); //centro gaussiana
  double ep12 = f12->GetParError(2); //suo errore
  double s12 = f12->GetParameter(3); //sigma gaussiana
  double e12 = f12->GetParError(3);  //suo errore
  return;
  
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
