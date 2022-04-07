// LYSO (ch.2) should see the 1200 keV while NaI1 and NaI2 should see the two photons at 511 keV
void Na_LYSO_NaI1_between_NaI2(TString Fname="DST/group2/Na2_1.dst"){

TTree* tree = new TTree("tree","data from ascii file");
tree->ReadFile(Fname.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");

//* Record for calibration
ofstream calfile;
calfile.open ("docs/group2/Calibration.txt",ios::app);

calfile<<"LYSO (ch.2) should see the 1200 keV while NaI1 and NaI2 should see the two photons at 511 keV" <<endl;
//*/
TString Mask0 = "abs(T42-1e-7)<4e-7 && abs(T32-1e-7)<3e-7 && T32!=0";
TString Mask1 = "&& abs(T34-5e-8)<3e-7 && T34!=0";
TString Mask2 = "&& -A3/PK3<35e-8 && -A3/PK3>10e-8 && -A4/PK4<35e-8 && -A4/PK4>10e-8";
TString Mask3 = "&& -A3<33e-9 && -A4<27e-9 && -A2<8e-9";
TString Mask4 = "&& PK4<0.09 && PK3<0.11";
TString Mask = Mask0 + Mask1 + Mask2 + Mask3 + Mask4;

// ISTOGRAMMI TEMPI
TCanvas* c1 = new TCanvas();
c1->SetTitle("Na_T32_T42");
tree->Draw("T32:T42", Mask, "colz");
c1->SaveAs("docs/group2/images/Na_T32_T42_1.png");

TCanvas* c12 = new TCanvas();
c12->SetTitle("Na_T34_T32");
tree->Draw("T34:T32", Mask, "colz");  // because in 0 there is a noisy spot 
c12->SaveAs("docs/group2/images/Na_T34_T32_1.png");

// ISTOGRAMMI AREE/PICCHI
// Pulisco i dati eliminando gli eventi di pile-up
TCanvas* c3 = new TCanvas();
c3->SetTitle("Areas/peaks");
tree->Draw("-A3/PK3:-A4/PK4", Mask , "colz");
c3->SaveAs("docs/group2/images/Na_A3PK3_A4PK4_1.png");

// istogramma 2D delle aree NaI1 NaI2
TCanvas* c4 = new TCanvas();
c4->SetTitle("NaI1 vs NaI2");
tree->Draw("-A3:-A4", Mask ,"colz");                    // AREE
c4->SaveAs("docs/group2/images/Na_A3_A4_1.png");
 
TCanvas* c42 = new TCanvas();
c42->SetTitle("Lyso vs NaI1");
tree->Draw("-A2:-A3", Mask, "colz");
 
TCanvas* c5 = new TCanvas();
c5->SetTitle("Peak-to-peak ch 3 and 4");
tree->Draw("PK3:PK4", Mask, "colz");                   // PICCHI
// Istogrammi con dati filtrati 
c5->SaveAs("docs/group2/images/Na_PK3_PK4_1.png");

TCanvas* c6 = new TCanvas();
  TH1D* h1 = new TH1D("h1","Peak @ 511 keV;NaI1 [V s];Events",200,0,4e-8);
  tree->Draw("-A3>>h1", Mask, "colz");
  gPad->SetLogy();
  h1->SetLineColor(kRed+2);
  
  TF1* f1 = new TF1("f1","[0]+gaus(1)",0,4e-8);
  f1->SetParameter(0,0);
  f1->SetParameter(1,70);
  f1->SetParameter(2,25.e-9); //centro gaussiana
  f1->SetParameter(3,1e-9); //sigma gaussiana
  h1->Fit("f1","L", " ", 20.5e-9, 30e-9); //L:likelyhood 
c6->SaveAs("docs/group2/images/NaI1_511_1.png");

  double p1 = f1->GetParameter(2); //centro gaussiana
  double ep1 = f1->GetParError(2); //suo errore
  double s1 = f1->GetParameter(3); //sigma gaussiana
  double e1 = f1->GetParError(3);  //suo errore

TCanvas* c7 = new TCanvas();
  TH1D* h2 = new TH1D("h2","Peak @ 511 keV;NaI2 [V s];Events",200,0,3e-8);
  tree->Draw("-A4>>h2", Mask, "colz");
  gPad->SetLogy();
  h2->SetLineColor(kRed+2);
  
  TF1* f2 = new TF1("f2","[0]+gaus(1)",0,7e-8);
  f2->SetParameter(0,0);
  f2->SetParameter(1,70);	// altezza
  f2->SetParameter(2,17.e-9); //centro gaussiana
  f2->SetParameter(3,1e-9); //sigma gaussiana
  h2->Fit("f2","L", " ", 16e-9, 22e-9); //L:likelyhood 
c7->SaveAs("docs/group2/images/NaI2_511_1.png");

  double p2 = f2->GetParameter(2); //centro gaussiana
  double ep2 = f2->GetParError(2); //suo errore
  double s2 = f2->GetParameter(3); //sigma gaussiana
  double e2 = f2->GetParError(3);  //suo errore

TCanvas* c8 = new TCanvas();
  TH1D* h3 = new TH1D("h3",";LYSO [V s];Events",200,0,8.1e-9);
  tree->Draw("-A2>>h3", Mask, "colz");
  gPad->SetLogy();
  h3->SetLineColor(kRed+2);
  
  TF1* f3 = new TF1("f3","[0] + [4]*x +gaus(1) + gaus(5)",0,4e-8);
  f3->SetParameter(0,0);
  f3->SetParameter(1,100);	// altezza
  f3->SetParameter(2,3e-9); //centro gaussiana
  f3->SetParameter(3,2e-9); //sigma gaussiana
  f3->SetParameter(4,0);
  f3->SetParameter(5,100);	// altezza
  f3->SetParameter(6,6e-9); //centro gaussiana
  f3->SetParameter(7,2e-9); //sigma gaussiana
 
  h3->Fit("f3","L", " ", 2e-9, 7e-9); //L:likelyhood 
c8->SaveAs("docs/group2/images/LYSO_1275_1.png");
 
  double p3 = f3->GetParameter(2); //centro gaussiana
  double ep3 = f3->GetParError(2); //suo errore
  double s3 = f3->GetParameter(3); //sigma gaussiana
  double e3 = f3->GetParError(3);  //suo errore
  double p32 = f3->GetParameter(6); //centro gaussiana
  double ep32 = f3->GetParError(6); //suo errore
  double s32 = f3->GetParameter(7); //sigma gaussiana
  double e32 = f3->GetParError(7);  //suo errore

calfile << "NaI1" <<endl;
calfile << "511 keV@ " << p1 << "+-" << ep1 << endl;
calfile << "sig @ 511 keV " << s1 << "+-" << e1 << endl;
calfile << "NaI2" <<endl;
calfile << "511 keV@ " << p2 << "+-" << ep2 << endl;
calfile << "sig @ 511 keV " << s2 << "+-" << e2 << endl;
calfile << "LYSO" <<endl;
calfile << "511 keV@ " << p3 << "+-" << ep3 << endl;
calfile << "sig @ 511 keV " << s3 << "+-" << e3 << endl;
calfile << "1275 keV@ " << p32 << "+-" << ep32 << endl;
calfile << "sig @ 1275 keV " << s32 << "+-" << e32 << endl;

  // suggestion how to proceed:
  // evnum>2550e3 select run with strong source between NaI1 and LYSO
  // -A1<15e-9 should select 511keV in NaI1 (the rest is compton)
  // 0.5e-9<-A4<1.e-9 should be 511keV in LYSO then the 1275keV is shown in NaI2
  // -A4 similar to 1.8e-9 should be 1275keV in LYSO and 15e-9<-A2<20e-9 sould be 511keV in NaI2

calfile << "-------------------------------------------------------------------------" << endl;  
calfile.close();  
  return;
  tree->SetAlias("E1","201.8+(-A1-7.500416e-09)*(306.8-201.8)/(1.111327e-08-7.500416e-09)");
  tree->SetAlias("E2","201.8+(-A2-8.962911e-09)*(306.8-201.8)/(1.337650e-08-8.962911e-09)");
}
