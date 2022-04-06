
void LYSO_Experience_group_2(){


// Stringhe contenenti gli indirizzi dei file 

TString Fname0="../DST/LYSO3.dst";
TString Fname1="../DST/LYSO4.dst";
TString Fname2="../DST/LYSO5.dst";
TString Fname3="../DST/LYSO6.dst";
TString Fname4 = "../DST/Co2_1.dst";
TString Fname5 = "../DST/Co2_2.dst";
TString Fname6 = "../DST/Na2_1.dst";
TString Fname7 = "../DST/Na2_2.dst";



cout << "Scegli al sezione da runnare:\nScegli 0 per runnarle tutte\n\n";
int n_sezione;
cin >> n_sezione;

if(n_sezione == 0 || n_sezione == 1){
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
};


// ******************************************
// CALIBRATION CO 60
// ******************************************

if(n_sezione == 0 || n_sezione == 2){
        TTree* tree1 = new TTree("tree1","data from ascii file"); 
        tree1->ReadFile(Fname4.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");

        TString Mask_Co_0 = "-A3/PK3<0.4e-6 && -A4/PK4<0.4e-6 && T34!=0 && -A3<0.08e-6 && -A4<0.08e-6";
        TString Mask_Co_1 = "&& T34!=0 && abs(-T34 -4e-9)<11e-9";
        TString Mask_Co = Mask_Co_0 + Mask_Co_1;

        TCanvas* a5 = new TCanvas();
        TH2D* h2d= new TH2D("h2d",";NaI1[V s];NaI2 [V s]",70,0,60e-9,70,0,60e-9);
        tree1->Draw("-A3:-A4>>h2d",Mask_Co,"colz");
        a5 -> SaveAs("../docs/assets/images/Co_spectrum_NaI1_NaI2.png");

        // Histogram Co_60
        TCanvas* a6 = new TCanvas();
        a6->SetGrid();
        TH1D* h3= new TH1D("h3","",100,39e-9, 50e-9);
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

        double Co_NaI1_1      = f1->GetParameter(1);
        double dCo_NaI1_1     = f1->GetParError(1);
        double Res_Co_NaI1_1  = f1->GetParameter(2)/Co_NaI1_1;
        double dRes_Co_NaI1_1 = f1->GetParError(2)/Co_NaI1_1;
        double Co_NaI1_2      = f1->GetParameter(4);
        double dCo_NaI1_2     = f1->GetParError(4);
        double Res_Co_NaI1_2  = f1->GetParameter(5)/Co_NaI1_2;
        double dRes_Co_NaI1_2 = f1->GetParError(5)/Co_NaI1_2;

        
        a6 -> SaveAs("../docs/assets/images/NaI1_Co_calib.png");

        TCanvas* a7 = new TCanvas();
        a7->SetGrid();
        TH1D* h4= new TH1D("h4","",100,30e-9, 44e-9);
        tree1->Draw("-A4>>h4",Mask_Co,"");
        gPad->SetLogy();

        TF1* f2 = new TF1("f2","gaus+gaus(3) + [6] + [7] * TMath::Exp(-x/[8])",30e-9,42e-9);
        f2->SetParameter(0,80);
        f2->SetParameter(1,35e-9);
        f2->SetParameter(2,1e-9);
        f2->SetParameter(3,80);
        f2->SetParameter(4,39e-9);
        f2->SetParameter(5,1e-9);
        f2->SetParameter(6, 30);
        f2->SetParameter(7, 30);
        f2->SetParameter(8, 10e-9);

        h4->Fit("f2","L","", 30e-9, 42e-9);

        double Co_NaI2_1      = f2->GetParameter(1);
        double dCo_NaI2_1     = f2->GetParError(1);
        double Res_Co_NaI2_1  = f2->GetParameter(2)/Co_NaI1_1;
        double dRes_Co_NaI2_1 = f2->GetParError(2)/Co_NaI1_1;
        double Co_NaI2_2      = f2->GetParameter(4);
        double dCo_NaI2_2     = f2->GetParError(4);
        double Res_Co_NaI2_2  = f2->GetParameter(5)/Co_NaI1_2;
        double dRes_Co_NaI2_2 = f2->GetParError(5)/Co_NaI1_2;

        // *********************
        // Fit pedestal
        TCanvas* a70 = new TCanvas();
        a70->SetGrid();
        TH1D* h40= new TH1D("h40","",250,-0.4e-9, 0e-9);
        tree1->Draw("-A2>>h40",Mask_Co,"");
        gPad->SetLogy();

        TF1* f20 = new TF1("f20","gaus+ [3]",-0.4e-9,0e-9);
        f20->SetParameter(0,100);
        f20->SetParameter(1,-0.2e-9);
        f20->SetParameter(2,0.1e-9);
        f20->SetParameter(3,10);
        h40->Fit("f20","L","", -0.4e-9, 0e-9);

        a70 -> SaveAs("LYSO_pedestal_hist_fit.png");

        double pedestal_centre      = f20->GetParameter(1);
        double dpedestal_centre     = f20->GetParError(1);
        double pedestal_res  = f20->GetParameter(2)/pedestal_centre;
        double dpedestal_res = f20->GetParError(2)/pedestal_centre;

        
        a7 -> SaveAs("../docs/assets/images/NaI2_Co_calib.png");

        TString Mask_Pedestal = "&& abs(-A1)<0.1e-9 && abs(-A2+0.2e-9)<0.3e-9";

        TCanvas* a8 = new TCanvas();
        tree1->Draw("-A2:-T34", Mask_Co+Mask_Pedestal, "colz");
        a8 -> SaveAs("../docs/assets/images/LYSO_pedestal.png");

        cout << "NaI 1\n";
        cout << "1173\t" << Co_NaI1_1 << "\t" << dCo_NaI1_1 << "\t" << Res_Co_NaI1_1 << "\t" << dRes_Co_NaI1_1 << "\t\n";
        cout << "1332\t" << Co_NaI1_2 << "\t" << dCo_NaI1_2 << "\t" << Res_Co_NaI1_2 << "\t" << dRes_Co_NaI1_2 << "\t\n";


        cout << "NaI 2\n";
        cout << "1173\t" << Co_NaI2_1 << "\t" << dCo_NaI2_1 << "\t" << Res_Co_NaI2_1 << "\t" << dRes_Co_NaI2_1 << "\t\n";
        cout << "1332\t" << Co_NaI2_2 << "\t" << dCo_NaI2_2 << "\t" << Res_Co_NaI2_2 << "\t" << dRes_Co_NaI2_2 << "\t\n";

        cout << "LYSO Pedestal\n";
        cout << "0\t" << pedestal_centre << "\t" << dpedestal_centre << "\t" << pedestal_res << "\t" << dpedestal_res << "\t\n";

};

// Calibration LYSO second file
// The NaI1 is vetoed 

// Devo estrarre i picchi del cobalto dagli istogrammi

if(n_sezione == 0 || n_sezione == 3){
    TTree* tree2 = new TTree("tree2","data from ascii file"); 
    tree2->ReadFile(Fname5.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");


    TString Mask_Co2_0 = "T12!=0 && T42!=0 && abs(-T12+0.04e-6)<0.2e-7 && abs(-T42+0.01e-6)<0.7e-7";
    TString Mask_Co2_1 ="&& abs(-A2/PK2 -0.09e-6)<0.03e-6 && abs(-A4/PK4-0.28e-6)<0.1e-6";
    TString Mask_Co2_2 = "&& -A4>0.03e-6 && -A4<0.05e-6 && -A2>2e-9 && -A2<9e-9";
    TString Mask_Co_peak1 = "&& -A4>32e-9 && -A4<37e-9";
    TString Mask_Co_peak2 = "&& -A4>38e-9 && -A4<41e-9";
    TString Mask_Co2 = Mask_Co2_0 + Mask_Co2_1 + Mask_Co2_2;

    // Pulisco i dati guardando i tempi

    TCanvas* a9 = new TCanvas();
    // Elimino i Pile up
    tree2->Draw("-A4/PK4:-A2/PK2",Mask_Co2, "colz");

    TCanvas* a50 = new TCanvas();
    TH2D* h2d0= new TH2D("h2d0",";LYSO[V s]; NaI2[V s]",70,1e-9,9e-9,70,8e-9,50e-9);
    tree2->Draw("-A4:-A2>>h2d0",Mask_Co2_0 + Mask_Co2_1,"colz");
    a50 -> SaveAs("../docs/assets/images/Co_spectrum_NaI2_LYSO.png");

    
    TCanvas* a10 = new TCanvas();
    tree2->Draw("-A4:-A2",Mask_Co2+"", "colz");
    a10 -> SaveAs("../docs/assets/images/Co_spectrum_zoom_peaks.png");
    

    TCanvas* a11 = new TCanvas();
    a11->SetGrid();
    TH1D* h5= new TH1D("h5","",40,32e-9,37e-9);
    tree2->Draw("-A4>>h5",Mask_Co2+Mask_Co_peak1,"");
    gPad->SetLogy();
    

    TCanvas* a12 = new TCanvas();
    a11->SetGrid();
    TH1D* h6= new TH1D("h6","",60,4e-9,8e-9);
    tree2->Draw("-A2>>h6",Mask_Co2+Mask_Co_peak1,"");
    gPad->SetLogy();

    TF1* f12 = new TF1("f12","gaus+ [3]*x",5e-9,8e-9);
    f12->SetParameter(0,30);
    f12->SetParameter(1,6.2e-9);
    f12->SetParameter(2,1e-9);
    f12->SetParameter(3,0);
    h6->Fit("f12","L","", 5e-9, 8e-9);
    a12->SaveAs("../docs/assets/images/Co_LYSO_peak_1332.png");

    TCanvas* a14 = new TCanvas();
    a11->SetGrid();
    TH1D* h8= new TH1D("h8","",100,38e-9,41e-9);
    tree2->Draw("-A4>>h8",Mask_Co2+Mask_Co_peak2,"");
    gPad->SetLogy();
    

    TCanvas* a13 = new TCanvas();
    a11->SetGrid();
    TH1D* h7= new TH1D("h7","",100,1e-9,12e-9);
    tree2->Draw("-A2>>h7",Mask_Co2+Mask_Co_peak2,"");
    gPad->SetLogy();

    TF1* f13 = new TF1("f13","gaus+ [3] + [4]* TMath::Exp(-x/[5])",2e-9,9e-9);
    f13->SetParameter(0,60);
    f13->SetParameter(1,5.9e-9);
    f13->SetParameter(2,1e-9);
    f13->SetParameter(3,5);
    f13->SetParameter(4,10);
    f13->SetParameter(5,1e-9);
    h7->Fit("f13","L","", 2e-9, 8e-9);
    a13->SaveAs("../docs/assets/images/Co_LYSO_peak_1173.png");

    cout << "Cobalto LYSO\n";
    cout << "1173\t" << (f13->GetParameter(1)) << "\t" <<(f13->GetParError(1)) << "\t" <<(f13->GetParameter(2))/(f13->GetParameter(1)) << "\t" << (f13->GetParError(2))/(f13->GetParameter(1)) << "\n";
    cout << "1332\t" << (f12->GetParameter(1)) << "\t" <<(f12->GetParError(1)) << "\t" <<(f12->GetParameter(2))/(f12->GetParameter(1)) << "\t" << (f12->GetParError(2))/(f12->GetParameter(1)) << "\n";

};

if(n_sezione == 0 || n_sezione == 4){
    TTree* tree3 = new TTree("tree3","data from ascii file");
    tree3->ReadFile(Fname6.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");

    TString Mask_Na1_0 = "T12!=0 && T32!=0 && T42!=0 && T34!=0 && abs(-T32)<0.5e-6 && abs(-T12+40e-9)<10e-9";
    TString Mask_Na1_1 = "&& -A3<0.03e-6 && -A4<0.03e-6";
    TString Mask_Na1 = Mask_Na1_0 + Mask_Na1_1;

    TCanvas* a13 = new TCanvas();
    a13->SetGrid();
    tree3->Draw("-A3:-A4",Mask_Na1 + "", "colz");
    

}

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