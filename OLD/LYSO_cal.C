void LYSO_cal(TString Fname="LYSO_cal.dat"){
  TTree* tree = new TTree("tree","data from ascii file");
  tree->ReadFile(Form("%s",Fname.Data()),"ene/F:cal/F:ecal/F:syscal/F:sig/F:esig/F");

  tree->Draw("cal:ene:ecal+syscal:ene*0.001","","goff");
  TGraphErrors* gra = new TGraphErrors(tree->GetSelectedRows(),tree->GetV2(),tree->GetV1(),tree->GetV4(),tree->GetV3());
  TCanvas* c1 = new TCanvas();
  gra->Draw("ap");
  gra->SetMarkerStyle(8);
  gra->SetLineWidth(2);
  TF1* flin = new TF1("flin","pol1",0,1500);
  gra->Fit("flin");
  gra->GetXaxis()->SetTitle("Energy [keV]");
  gra->GetYaxis()->SetTitle("LYSO signal [Vxs]");

  double p1=flin->GetParameter(1);
  double p0=flin->GetParameter(0);
  TCanvas* c2 = new TCanvas();
  tree->SetAlias("sigmax","max(sig+esig,syscal)");
  tree->SetAlias("sigmin","sig-esig");
  tree->SetAlias("sigmd","0.5*(sigmax+sigmin)");
  tree->SetAlias("siged","0.5*(sigmax-sigmin)");
  
  tree->Draw(Form("sigmd*%e:ene:(siged)*%e:ene*0.001",1/p1,1/p1),"","goff");
  TGraphErrors* gra2 = new TGraphErrors(tree->GetSelectedRows(),tree->GetV2(),tree->GetV1(),tree->GetV4(),tree->GetV3());
  gra2->Draw("ap");
  gra2->SetMarkerStyle(8);
  gra2->SetLineWidth(2);
  TF1* fsig = new TF1("fsig","sqrt([1]*[1]*x+[0]*[0])",0,1500);
  fsig->SetParameter(0,15);
  fsig->SetParameter(1,1);
  
  gra2->Fit("fsig");
  gra2->GetXaxis()->SetTitle("Energy [keV]");
  gra2->GetYaxis()->SetTitle("#sigma [keV]");

  cout << "expected sigma@ 662 keV = " << fsig->Eval(662) << endl;
  cout << "expected sigma@ 59.5 keV = " << fsig->Eval(59.5) << endl;

  cout << "Alias ELYSO " << Form("(-A4+%e)*%e",-p0,1./p1) << endl;
  return;
}
