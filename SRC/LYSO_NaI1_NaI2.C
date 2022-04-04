
void LYSO_NaI1_NaI2(TString Fname="../DST/LYSO3.dst"){

  //TTree* tree = new TTree("tree","data from ascii file");
  //tree->ReadFile(Form("%s",Fname.Data()),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T14/F");
  TTree* tree = new TTree("tree","data from ascii file"); 
  tree->ReadFile(Fname.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");
  
  // Creo un nuovo istogramma e plotto le aree del sodio
  // Istogrammi 2D per i tempi per puilire i dati

  TString Mask = "T34!=0 && abs(-T32+4e-9)<3e-8 && abs(-T42+10e-9)<3e-8 && abs(-T12+40e-9)<3e-8 && T12!=0 && T42!=0 && -A3<13e-9 && -A4<13e-9 && -A3/PK3<0.3e-6 && -A4/PK4<0.3e-6 && -A2<5e-9";


	TCanvas* c1 = new TCanvas();
	tree->Draw("-T32:-T42", Mask, "colz");
  TCanvas* c2 = new TCanvas();
	tree->Draw("-T32:-T12", Mask , "colz");

	
  // istogramma 2D delle aree NaI1 NaI2
  TCanvas* c3 = new TCanvas();
  tree->Draw("-A3:-A4", Mask ,"colz");
  c3->SaveAs("../docs/assets/images/LYSO_A3_A4.png");
  
  TCanvas* b1 = new TCanvas();
  tree->Draw("PK3:PK4", Mask , "colz");
  // Istogrammi con dati filtrati 
    b1->SaveAs("../docs/assets/images/LYSO_PK3_PK4.png");
  // Istogramma per identificare eventi di pile up
  TCanvas* b2 = new TCanvas();
  tree->Draw("-A3/PK3:-A4/PK4", Mask , "colz");
  // Non ci sono eccessi di eventi di pile up
  
  TCanvas* b3 = new TCanvas();
  tree->Draw("-A2:(-A3-A4)", Mask ,"colz");

  return;

  TCanvas* a1 = new TCanvas();
  TH1D* h2= new TH1D("h2","",100,1e-9,18e-9);
  tree->Draw("-A3>>h2",Mask,"");
  gPad->SetLogy();
  return;
  TF1* f2 = new TF1("f2","gaus+gaus(3)+gaus(6)",9e-9,18e-9);
  f2->SetParameter(0,31);
  f2->SetParameter(1,14.1e-9);
  f2->SetParameter(2,0.6e-9);
  f2->SetParameter(3,6);
  f2->SetParameter(4,10e-9);
  f2->SetParameter(5,0.6e-9);
  f2->SetParameter(6,6);
  f2->SetParameter(7,11.5e-9);
  f2->SetParameter(8,2e-9);
  h2->Fit("f2","L");

  //TCanvas* c3 = new TCanvas();
  TH1D* h3= new TH1D("h3","",200,4e-9,16e-9);
   tree->Draw("-A2>>h3","-A1>9e-9 && -A1<13.e-9 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  gPad->SetLogy();
  TF1* f3 = (TF1*) f2->Clone("f3");
  h3->Fit("f3","L");

  double p2=abs(f2->GetParameter(1)); //map to 307keV
  double s2=f2->GetParameter(2)/p2; //map to 307keV
  double e2=f2->GetParError(2)/p2; //map to 307keV
  double p3=f3->GetParameter(4); //map to 202keV
  double s3=f3->GetParameter(5)/p3; //map to 202keV
  double e3=f3->GetParError(5)/p3; //map to 202keV
  
  tree->SetAlias("E2",Form("201.8+(-A2-%e)*(306.8-201.8)/(%e-%e)",p3,p2,p3));
  TCanvas* c4 = new TCanvas();
  TH1D* h4= new TH1D("h4","",200,5.e-9,14e-9);
  tree->Draw("-A1>>h4","-A2>8e-9 && -A2<11.e-9 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  gPad->SetLogy();
  TF1* f4 = (TF1*) f3->Clone("f4");
  f4->SetParameter(1,11e-9);
  f4->SetParameter(4,7.5e-9);
  f4->SetParameter(5,3.e-10);
  f4->SetParameter(7,1e-9);
  f4->SetParameter(8,7e-9);
  h4->Fit("f4","L");

  TCanvas* c5 = new TCanvas();
  TH1D* h5= new TH1D("h5","",200,1e-9,9e-9);
  tree->Draw("-A1>>h5","-A2>12e-9 && -A2<16.e-9 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  gPad->SetLogy();
  TF1* f5 = (TF1*) f4->Clone("f5");
  f5->SetParameter(1,5.2e-9);
  f5->SetParameter(2,1.5e-9);
  f5->SetParameter(4,7.5e-9);
  f5->SetParameter(5,3.9e-10);
  f5->SetParameter(7,2.1e-9);
  f5->SetParameter(8,5.4e-10);
  h5->Fit("f5","L");

  double p4=f4->GetParameter(1); //map to 307keV
  double s4=f4->GetParameter(2)/p4; //map to 307keV
  double e4=f4->GetParError(2)/p4; //map to 307keV
  double p5=f5->GetParameter(4); //map to 202keV
  double s5=f5->GetParameter(5)/p5; //map to 202keV
  double e5=f5->GetParError(5)/p5; //map to 202keV
  
  tree->SetAlias("E1",Form("201.8+(-A1-%e)*(306.8-201.8)/(%e-%e)",p5,p4,p5));


  TCanvas* c6 = new TCanvas();
  tree->Draw("E1+E2","E1<500 && E2<500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","colz");

  TCanvas* c7 = new TCanvas();
  TH2D* hhh = new TH2D("hhh","",100,0,400,100,0,400);
  tree->Draw("E1:E2>>hhh","E1<500 && E2<500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","colz");
  gPad->SetGrid();

  cout << "Alias E2 =" << Form("201.8+(-A2-%e)*(306.8-201.8)/(%e-%e)",p3,p2,p3) << endl;
  cout << "Alias E1 =" << Form("201.8+(-A1-%e)*(306.8-201.8)/(%e-%e)",p5,p4,p5) << endl;
 
  cout << "res NaI2 = " << s3 << "+-" << e3 << " @202 keV " << s2 << "+-" <<e2 <<" @307 keV" << endl;
  cout << "res NaI1 = " << s5 << "+-" << e5 << " @202 keV " << s4 << "+-" <<e4 <<" @307 keV" << endl;

  TCanvas* c8 = new TCanvas();
  TH2D* hhh3 = new TH2D("hhh3","",150,0,1200,150,0,700);
  tree->Draw("E1+E2:ELYSO>>hhh3","E1<500 && E2<500 && E1+E2<750 && ELYSO<1500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","colz");
  hhh3->Smooth();

  TCanvas* c9 = new TCanvas();
  TH1D* hbeta = new TH1D("hbeta","",100,0,2000);
  tree->Draw("ELYSO-88>>hbeta","E1<500 && E2<500 && E1+E2<550 && E1+E2>450 && ELYSO<1500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  hbeta->SaveAs("hbeta.root");
  TH1D* hbeta1 = new TH1D("hbeta1","",100,0,2000);
  tree->Draw("ELYSO>>hbeta1","E1<500 && E2<500 && E1+E2<550 && E1+E2>450 && ELYSO<1500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  hbeta1->SaveAs("hbeta1.root");
  
  TH1D* hbeta2 = new TH1D("hbeta2","",100,0,2000);
  tree->Draw("202+ELYSO-88>>hbeta2","E1<500 && E2<500 && E1+E2<550 && E1+E2>450 && ELYSO<1500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  hbeta2->SaveAs("hbeta2.root");
  TH1D* hbeta3 = new TH1D("hbeta3","",100,0,2000);
  tree->Draw("202+ELYSO>>hbeta3","E1<500 && E2<500 && E1+E2<550 && E1+E2>450 && ELYSO<1500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  hbeta3->SaveAs("hbeta3.root");

  TH1D* hbeta4 = new TH1D("hbeta4","",100,0,2000);
  tree->Draw("307+ELYSO-88>>hbeta4","E1<500 && E2<500 && E1+E2<550 && E1+E2>450 && ELYSO<1500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  hbeta4->SaveAs("hbeta4.root");
  TH1D* hbeta5 = new TH1D("hbeta5","",100,0,2000);
  tree->Draw("307+ELYSO>>hbeta5","E1<500 && E2<500 && E1+E2<550 && E1+E2>450 && ELYSO<1500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  hbeta5->SaveAs("hbeta5.root");

  TH1D* hbeta6 = new TH1D("hbeta6","",100,0,2000);
  tree->Draw("307+202+ELYSO-88>>hbeta6","E1<500 && E2<500 && E1+E2<550 && E1+E2>450 && ELYSO<1500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  hbeta6->SaveAs("hbeta6.root");
  TH1D* hbeta7 = new TH1D("hbeta7","",100,0,2000);
  tree->Draw("307+202+ELYSO>>hbeta7","E1<500 && E2<500 && E1+E2<550 && E1+E2>450 && ELYSO<1500 && abs(T31-0.19e-6)<0.1e-6 && abs(T32-0.19e-6)<0.1e-6","");
  hbeta7->SaveAs("hbeta7.root");
  

  return;
   

}
