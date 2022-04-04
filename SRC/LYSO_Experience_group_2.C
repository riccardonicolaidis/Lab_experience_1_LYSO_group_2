
void LYSO_Experience_group_2(){


TString Fname0="../DST/LYSO3.dst";
TString Fname1="../DST/LYSO4.dst";
TString Fname2="../DST/LYSO5.dst";
TString Fname3="../DST/LYSO6.dst";


// IMPORTAZIONE DEI DATI
TTree* tree = new TTree("tree","data from ascii file"); 
tree->ReadFile(Fname0.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");
tree->ReadFile(Fname1.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");
//tree->ReadFile(Fname2.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");
//tree->ReadFile(Fname3.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");
  
// Creo un nuovo istogramma e plotto le aree del sodio
// Istogrammi 2D per i tempi per puilire i dati

// MASCHERA 
//TString Mask = "T34!=0 && abs(-T32+4e-9)<3e-8 && abs(-T42+10e-9)<3e-8 && abs(-T12+40e-9)<3e-8 && T12!=0 && T42!=0 && -A3<13e-9 && -A4<13e-9 && -A3/PK3<0.3e-6 && -A4/PK4<0.3e-6 && -A2<5e-9";

TString Mask0 = "T34!=0 && T32!=0 && T42!=0 && T12!=0 &&";
TString Mask1 = "abs(-T32+5e-9)<0.3e-7 && abs(-T42+10e-9)<0.3e-7 &&";
TString Mask2 = "abs(-T12 +0.04e-6)<0.4e-7 &&";
TString Mask3 = "(-A4/PK4-0.22e-6)<0.07e-6 && (-A3/PK3-0.21e-6)<0.1e-6 &&";
TString Mask4 = "-A4<16e-9 & -A3<16e-9";
TString Mask = Mask0 + Mask1 + Mask2 + Mask3 + Mask4;



// ISTOGRAMMI TEMPI
// Pulisco i dati guardando i tempi
TCanvas* c1 = new TCanvas();
tree->Draw("-T32:-T42", Mask, "colz");

TCanvas* c2 = new TCanvas();
tree->Draw("-T32:-T12", Mask , "colz");
	
// ISTOGRAMMI AREE/PICCHI
// Pulisco i dati eliminando gli eventi di pile-up
TCanvas* c3 = new TCanvas();
tree->Draw("-A3/PK3:-A4/PK4", Mask , "colz");


// istogramma 2D delle aree NaI1 NaI2
TCanvas* a1 = new TCanvas();
tree->Draw("-A3:-A4", Mask ,"colz");                    // AREE
a1->SaveAs("../docs/assets/images/LYSO_A3_A4.png");
  


TCanvas* a2 = new TCanvas();
tree->Draw("PK3:PK4", Mask , "colz");                   // PICCHI
// Istogrammi con dati filtrati 
a2->SaveAs("../docs/assets/images/LYSO_PK3_PK4.png");


// ISTOGRAMMA UNIDIMENSIONALE DEI NaI

// ***********************************
//  NaI 1 
// ***********************************

TCanvas* a3 = new TCanvas();
a3->SetGrid();
TH1D* h1= new TH1D("h1","NaI1 LYSO spectrum",100,1e-11, 15e-9);
tree->Draw("-A3>>h1",Mask,"");
gPad->SetLogy();
a3->SaveAs("../docs/assets/images/NaI1_LYSO_Spectrum.png");

TCanvas* a4 = new TCanvas();
a4->SetGrid();
TH1D* h2= new TH1D("h2","NaI2 LYSO spectrum",100,1e-10, 12e-9);
tree->Draw("-A4>>h2",Mask,"");
gPad->SetLogy();
a4->SaveAs("../docs/assets/images/NaI2_LYSO_Spectrum.png");


// ******************************************
// CALIBRATION CO 60
// ******************************************
TString Fname4 = "../DST/Co2_1.dst";
TTree* tree1 = new TTree("tree1","data from ascii file"); 
tree1->ReadFile(Fname4.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");


TString Mask_Co_0 = "-A3/PK3<0.4e-6 && -A4/PK4<0.4e-6 && T34!=0 && -A3<0.08e-6 && -A4<0.08e-6";
TString Mask_Co_1 = "&& T34!=0 && abs(-T34 -4e-9)<11e-9";
TString Mask_Co = Mask_Co_0 + Mask_Co_1;

TCanvas* a5 = new TCanvas();
tree1->Draw("-A3:-A4", Mask_Co, "colz");


// Histogram Co_60
TCanvas* a6 = new TCanvas();
a6->SetGrid();
TH1D* h3= new TH1D("h3","",200,1e-11, 80e-9);
tree1->Draw("-A3>>h3",Mask_Co,"");
gPad->SetLogy();

TF1* f1 = new TF1("f1","gaus+gaus(3) + [6]*x + [7]",39e-9,50e-9);
f1->SetParameter(0,250);
f1->SetParameter(1,42e-9);
f1->SetParameter(2,0.5e-9);
f1->SetParameter(3,200);
f1->SetParameter(4,47e-9);
f1->SetParameter(5,0.5e-9);
f1->SetParameter(6,-1);
f1->SetParameter(7, 60);
h3->Fit("f1","L","", 39e-9, 50e-9);

a6 -> SaveAs("../docs/assets/images/NaI1_Co_calib.png");

TCanvas* a7 = new TCanvas();
a7->SetGrid();
TH1D* h4= new TH1D("h4","",250,1e-11, 80e-9);
tree1->Draw("-A4>>h4",Mask_Co,"");
gPad->SetLogy();

TF1* f2 = new TF1("f2","gaus+gaus(3) + [6]",30e-9,42e-9);
f2->SetParameter(0,200);
f2->SetParameter(1,35e-9);
f2->SetParameter(2,0.5e-9);
f2->SetParameter(3,200);
f2->SetParameter(4,39e-9);
f2->SetParameter(5,0.5e-9);
f2->SetParameter(6, 60);

h4->Fit("f2","L","", 30e-9, 42e-9);

a7 -> SaveAs("../docs/assets/images/NaI2_Co_calib.png");

TString Mask_Pedestal = "&& abs(-A1)<0.1e-9 && abs(-A2+0.2e-9)<0.3e-9";

TCanvas* a8 = new TCanvas();
tree1->Draw("-A2:-T34", Mask_Co+Mask_Pedestal, "colz");
a8 -> SaveAs("../docs/assets/images/LYSO_pedestal.png");




/*
TF1* f1 = new TF1("f1","gaus+gaus(3)+gaus(6)",1e-16,14e-9);
f1->SetParameter(0,100);
f1->SetParameter(1,5e-9);
f1->SetParameter(2,2e-9);
f1->SetParameter(3,60);
f1->SetParameter(4,7.6e-9);
f1->SetParameter(5,0.5e-9);
f1->SetParameter(6,40);
f1->SetParameter(7,12e-9);
f1->SetParameter(8,0.5e-9);
h1->Fit("f1","L","", 1e-16, 14e-9);

// ***********************************
//  NaI 2 
// ***********************************

TCanvas* a2 = new TCanvas();
a2->SetGrid();
TH1D* h2= new TH1D("h2","",120,1e-16,14e-9);
tree->Draw("-A4>>h2",Mask,"");
gPad->SetLogy();




TF1* f2 = new TF1("f2","gaus+gaus(3)+gaus(6)",1e-16,14e-9);
f2->SetParameter(0,100);
f2->SetParameter(1,5e-9);
f2->SetParameter(2,2e-9);
f2->SetParameter(3,60);
f2->SetParameter(4,7.6e-9);
f2->SetParameter(5,0.5e-9);
f2->SetParameter(6,40);
f2->SetParameter(7,12e-9);
f2->SetParameter(8,0.5e-9);
h2->Fit("f2","L","", 1e-16, 14e-9);




*/
return;
}