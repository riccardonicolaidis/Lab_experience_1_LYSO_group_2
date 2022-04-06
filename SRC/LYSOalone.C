
void LYSOalone(){
	//import data
  TTree* treeLYSO = new TTree("treeLYSO","data from ascii file");
  TTree* treeCS = new TTree("treeCS","data from ascii file");
  //data for LYSO
  treeLYSO->ReadFile("../DST/LYSO6.dst","evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");
  //data for CS
  treeCS->ReadFile("../DST/CS2.dst","evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");
  
  //Selection rules string
  TString rules = "-A3<-1e-9 && -A4<-0.4e-9 && abs(-A2/PK2-0.09e-6)<0.03e-6";
  if(1){
  //plot for filtering the data
  //This part is needed to check if there is already a C1 and if there is delete it
  TCanvas *C1 = (TCanvas*) gROOT->FindObject("C1");
  if (C1) delete C1;
  C1 = new TCanvas("C1","canvas",2096,640);
	//divide the canvas in 2
	C1->Divide(2,1);
	
	//just drawing the tree should be faster than using histograms as it auto selects the range
	//select which canvas to use
	C1->cd(1);
  //TH2D *h2Darea = new TH2D("h2Darea",";NaI1[V s];NaI2 [V s]",200,0e-9,90e-9,200,0e-9,90e-9);
  treeLYSO->Draw("-A2/PK2:A1/PK1", rules.Data(), "colz");
  
  C1->cd(2);
  //TH2D *h2Ddelay = new TH2D("h2Ddelay",";A3/PK3[V s];T32 [s]",200,0e-9,30e-9,200,0e-9,30e-9);
  treeLYSO->Draw("-A4:-A3", rules.Data(), "colz");
  }

	if(1){
	//fit the data
	//this rules can be useful to select sub ranges
	TString rules_extra = "";//&& -A2>0e-9 && -A2<8e-9 ";
	
	TCanvas *C2 = (TCanvas*) gROOT->FindObject("C2");
  if (C2) delete C2;
  C2 = new TCanvas("C2","canvas",1048,1280);
  C2->Divide(1,2);
  C2->cd(1);
	TH1D* h1 = new TH1D("h1",";NaI2[V s];Events",200,0,20e-9);
  treeLYSO->Draw("-A2>>h1", rules.Append(rules_extra.Data()).Data(), "");
  
//create new histograms
  TH1D* hLYSO = new TH1D("hLYSO",";EnergyLYSO[MeV];Events",80,0,2.5);
  TH1D* hCS = (TH1D*)hLYSO->Clone("hCS");
  hCS->SetLineColor(2);
  
  //calibration
  double pl1 = 7e-9/1.7;
  double pl0 = 0;
  
	//create new variables in the two trees 
  treeLYSO->SetAlias("ELYSO",Form("((-A2-%g)/%g)",pl0,pl1));
  treeCS->SetAlias("ELYSO",Form("((-A2-%g)/%g)",pl0,pl1));
  treeLYSO->Draw("ELYSO>>hCS", rules.Append(rules_extra.Data()).Data(), "");
  treeCS->Draw("ELYSO>>hLYSO", rules.Append(rules_extra.Data()).Data(), "same");
  gPad->SetLogy();
  
  //integrate the tails
  double intCS = hCS->Integral(hCS->FindBin(1.3),hCS->GetNbinsX());
  double intLYSO = hLYSO->Integral(hLYSO->FindBin(1.3),hLYSO->GetNbinsX()); 
  
  hLYSO->Scale(intCS/intLYSO);
  
  C2->cd(2);
  TH1D* hdiff = (TH1D*)hCS->Clone("hdiff2");
  hdiff->Add(hLYSO,-1);
  hdiff->Draw("Same");
  gPad->SetGridy();
  hdiff->SaveAs("Hdiff2.root");
  C2->SaveAs("Hdiff2.png");  
  }
}
