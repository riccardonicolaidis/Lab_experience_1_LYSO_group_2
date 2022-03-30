
void LYSO_bkg(){
  TFile* fbeta = (TFile*) TFile::Open("hbeta.root");
  TH1D* hbeta = (TH1D*) fbeta->Get("hbeta");
  TFile* fbeta1 = (TFile*) TFile::Open("hbeta1.root");
  TH1D* hbeta1 = (TH1D*) fbeta1->Get("hbeta1");
  TFile* fbeta2 = (TFile*) TFile::Open("hbeta2.root");
  TH1D* hbeta2 = (TH1D*) fbeta2->Get("hbeta2");
  TFile* fbeta3 = (TFile*) TFile::Open("hbeta3.root");
  TH1D* hbeta3 = (TH1D*) fbeta3->Get("hbeta3");
  TFile* fbeta4 = (TFile*) TFile::Open("hbeta4.root");
  TH1D* hbeta4 = (TH1D*) fbeta4->Get("hbeta4");
  TFile* fbeta5 = (TFile*) TFile::Open("hbeta5.root");
  TH1D* hbeta5 = (TH1D*) fbeta5->Get("hbeta5");
  TFile* fbeta6 = (TFile*) TFile::Open("hbeta6.root");
  TH1D* hbeta6 = (TH1D*) fbeta6->Get("hbeta6");
  TFile* fbeta7 = (TFile*) TFile::Open("hbeta7.root");
  TH1D* hbeta7 = (TH1D*) fbeta7->Get("hbeta7");

  TTree* tree1 = new TTree("tree1","data from ascii file");
  tree1->ReadFile("../DST/LYSO1.dst","evnum/I:A4/F:A3/F:A2/F:A1/F:T31/F:T32/F");
  tree1->SetAlias("ELYSO1","(-A4+3.360057e-10)*5.529926e+11");
  TCanvas* c1 = new TCanvas();
  tree1->Draw("-A4:-A3","-A1<0.1e-9 && -A2<-0.3e-9","colz");

  TCanvas* c2 = new TCanvas();
  tree1->Draw("-A4:-A3","-A1<0.1e-9 && -A2<-0.3e-9 && -A4>(-A3)*3.-2.e-9","colz");

  TCanvas* c3 = new TCanvas();
  tree1->Draw("-A4:-A3","-A1<0.1e-9 && -A2<-0.3e-9 && -A4<1.e-9 && -A3<0.8e-9","goff");
  TGraph* gra = new TGraph(tree1->GetSelectedRows(),tree1->GetV2(),tree1->GetV1());
  gra->Draw("ap");
  TF1* flin = new TF1("flin","[0]+[1]*x",-0.2e-9,0.5e-9);
  flin->FixParameter(1,1);
  gra->Fit("flin","","",-0.2e-9,0.4e-9);
  tree1->SetAlias("ELYSOLE1",Form("((-A3+%e)+3.360057e-10)*5.529926e+11",flin->GetParameter(0)));
  TCanvas* c4 = new TCanvas();
  TH1D* hbkg1 = new TH1D("hbkg1","",100,0,2000);
  TH1D* hbkgLE = new TH1D("hbkgLE","",200,0,1000);
  tree1->Draw("ELYSO1>>hbkg1","-A1<0.1e-9 && -A2<-0.3e-9 && -A4>(-A3)*3.-2.e-9 && -A3<1.3e-9","");
  tree1->Draw("ELYSOLE1>>hbkgLE","-A1<0.1e-9 && -A2<-0.3e-9 && -A4>(-A3)*3.-2.e-9 && -A3<1.3e-9","");

  TTree* tree2 = new TTree("tree2","data from ascii file");
  tree2->ReadFile("../DST/LYSO2.dst","evnum/I:A4/F:A3/F:A2/F:A1/F:T31/F:T32/F");
  tree2->SetAlias("ELYSO2","(-A4+3.360057e-10)*5.529926e+11");
  TH1D* hbkg2 = new TH1D("hbkg2","",100,0,2000);
  hbkg2->SetLineColor(2);
  tree2->Draw("ELYSO2>>hbkg2","-A1<0.1e-9 && -A2<-0.3e-9 && -A4>(-A3)*3.-2.e-9 && -A3<1.3e-9","same");
  TTree* tree3 = new TTree("tree3","data from ascii file");
  tree3->ReadFile("../DST/LYSO3.dst","evnum/I:A4/F:A3/F:A2/F:A1/F:T31/F:T32/F");
  tree3->SetAlias("ELYSO3","(-A4+3.360057e-10)*5.529926e+11");
  TH1D* hbkg3 = new TH1D("hbkg3","",100,0,2000);
  hbkg3->SetLineColor(3);
  tree3->Draw("ELYSO3>>hbkg3","-A1<0.1e-9 && -A2<-0.3e-9 && -A4>(-A3)*3.-2.e-9 && -A3<1.3e-9","same");

  TH1D* hbkg = (TH1D*) hbkg1->Clone("hbkg");
  hbkg->Add(hbkg2);
  hbkg->Add(hbkg3);

  TCanvas* cbkg = new TCanvas();
  hbkg->Draw("e");
  hbkg->GetXaxis()->SetTitle("Energy [keV]");
  hbkg1->Scale(hbkg->Integral()/hbkg1->Integral());
  hbkg2->Scale(hbkg->Integral()/hbkg2->Integral());
  hbkg3->Scale(hbkg->Integral()/hbkg3->Integral());
  hbkg1->Draw("histosame");
  hbkg2->Draw("histosame");
  hbkg3->Draw("histosame");
  gPad->SetLogy();

  TCanvas* cmod = new TCanvas();
  hbkg->Draw("e");
  gPad->SetLogy();
  hbeta->Scale(hbkg->Integral(0,5)/hbeta->Integral(0,5));
  hbeta->Draw("histosame");
  hbeta1->Scale(2*hbeta->Integral()/hbeta1->Integral());
  hbeta1->Draw("histosame");

  hbeta2->Scale(0.3*hbkg->Integral(14,17)/hbeta2->Integral(14,17));
  hbeta2->Draw("histosame");
  hbeta3->Scale(2*hbeta2->Integral()/hbeta3->Integral());
  hbeta3->Draw("histosame");
  
  hbeta4->Scale(1.5*hbeta2->Integral()/hbeta4->Integral());
  hbeta4->Draw("histosame");
  hbeta5->Scale(2*hbeta4->Integral()/hbeta5->Integral());
  hbeta5->Draw("histosame");
  
  hbeta7->Scale(0.6*hbkg->Integral(35,42)/hbeta7->Integral(35,42));
  hbeta7->Draw("histosame");
  hbeta6->Scale(hbeta7->Integral()/(1.5*hbeta6->Integral()));
  hbeta6->Draw("histosame");
  
  TH1D* hmod = (TH1D*) hbeta->Clone();
  hmod->Add(hbeta1);
  hmod->Add(hbeta2);
  hmod->Add(hbeta3);
  hmod->Add(hbeta4);
  hmod->Add(hbeta5);
  hmod->Add(hbeta6);
  hmod->Add(hbeta7);
  hmod->SetLineColor(2);
  hmod->Draw("histosame");
  
  TCanvas* csig = new TCanvas();
  TTree* tree4 = new TTree("tree4","data from ascii file");
  tree4->ReadFile("../DST/Cs_LYSO1.dst","evnum/I:A4/F:A3/F:A2/F:A1/F:T31/F:T32/F");
  tree4->SetAlias("ELYSO4","(-A4+3.360057e-10)*5.529926e+11");
  TH1D* hsig4 = new TH1D("hsig4","",100,0,2000);
  hsig4->SetLineColor(4);
  tree4->Draw("ELYSO4>>hsig4","-A1<0.1e-9 && -A2<-0.3e-9 && -A4>(-A3)*3.-2.e-9 && -A3<1.3e-9","same");

  TTree* tree5 = new TTree("tree5","data from ascii file");
  tree5->ReadFile("../DST/Cs_LYSO2.dst","evnum/I:A4/F:A3/F:A2/F:A1/F:T31/F:T32/F");
  tree5->SetAlias("ELYSO5","(-A4+3.360057e-10)*5.529926e+11");
  TH1D* hsig5 = new TH1D("hsig5","",100,0,2000);
  hsig5->SetLineColor(5);
  tree5->Draw("ELYSO5>>hsig5","-A1<0.1e-9 && -A2<-0.3e-9 && -A4>(-A3)*3.-2.e-9 && -A3<1.3e-9","same");


  TH1D* hsig = (TH1D*) hsig5->Clone("hsig");
  TH1D* hsub = (TH1D*) hbkg->Clone("hsub");
  //  hsig->Add(hsig4);
  hsig4->Scale(hsig->Integral(40,100)/hsig4->Integral(40,100));
  hsig5->Scale(hsig->Integral(40,100)/hsig5->Integral(40,100));
  hsub->Scale(hsig->Integral(40,100)/hsub->Integral(40,100));
  hsub->SetLineColor(1);
  hsig->SetMarkerColor(2);
  hsig->SetLineColor(2);

  hsig->Draw("e");
  hsig4->Draw("histosame");
  hsig5->Draw("histosame");
  hsub->Draw("histosame");
  gPad->SetLogy();

  TCanvas* cam = new TCanvas();

  TTree* tree6 = new TTree("tree6","data from ascii file");
  tree6->ReadFile("../DST/Am_LYSO1.dst","evnum/I:A4/F:A3/F:A2/F:A1/F:T31/F:T32/F");
  tree6->SetAlias("ELYSOLE6","(-A4+3.360057e-10)*5.529926e+11");
  tree6->SetAlias("ELYSOLE6",Form("((-A3+%e)+3.360057e-10)*5.529926e+11",flin->GetParameter(0)));
  TH1D* hsig6 = new TH1D("hsig6","",200,0,1000);
  hsig5->SetLineColor(6);
  tree6->Draw("ELYSOLE6>>hsig6","-A1<0.1e-9 && -A2<-0.3e-9 && -A4>(-A3)*3.-2.e-9 && -A3<1.3e-9","same");
  hbkgLE->Scale(hsig6->Integral(40,200)/hbkgLE->Integral(40,200));
  hsig6->Draw("e");
  hbkgLE->Draw("histosame");
  gPad->SetLogy();


  TCanvas* diff = new TCanvas();
  TH1D* hCs = (TH1D*) hsig->Clone("hCs");
  hCs->Add(hsub,-1);
  hCs->Draw();
  hCs->Fit("gaus","","",550,850);
  return;
    

  return;   

}
