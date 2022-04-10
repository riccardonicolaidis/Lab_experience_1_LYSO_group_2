void LYSO_Experience_group_2(){


// Stringhe contenenti gli indirizzi dei file 

/*
TString Fname0="../DST/LYSO3.dst";
TString Fname1="../DST/LYSO4.dst";
TString Fname2="../DST/LYSO5.dst";
TString Fname3="../DST/LYSO6.dst";
TString Fname4 = "../DST/Co2_1.dst";
TString Fname5 = "../DST/Co2_2.dst";
TString Fname6 = "../DST/Na2_1.dst";
TString Fname7 = "../DST/Na2_2.dst";

*/

TString Fname0 = "DST/group2/LYSO3.dst";
TString Fname1 = "DST/group2/LYSO4.dst";
TString Fname2 = "DST/group2/LYSO5.dst";
TString Fname3 = "DST/group2/LYSO6.dst";
TString Fname4 = "DST/group2/Co2_1.dst";
TString Fname5 = "DST/group2/Co2_2.dst";
TString Fname6 = "DST/group2/Na2_1.dst";
TString Fname7 = "DST/group2/Na2_2.dst";

// Record for calibration
ofstream calfile;
calfile.open ("docs/group2/Calibration.txt",ios::app);
char risp;


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

	   
    cout <<"Vuoi salvare i risultati del fit? (y/n)"<<endl;
    cin>>risp;
    
	if (risp == 'y'){
    	calfile << "Calibrazione degli scintillatori NaI con sorgente Co 60"<<endl;
    	calfile << "NaI 1\n";
      calfile << "1173\t" << Co_NaI1_1 << "\t" << dCo_NaI1_1 << "\t" << Res_Co_NaI1_1 << "\t" << dRes_Co_NaI1_1 << "\t\n";
      calfile << "1332\t" << Co_NaI1_2 << "\t" << dCo_NaI1_2 << "\t" << Res_Co_NaI1_2 << "\t" << dRes_Co_NaI1_2 << "\t\n";


      calfile << "NaI 2\n";
      calfile << "1173\t" << Co_NaI2_1 << "\t" << dCo_NaI2_1 << "\t" << Res_Co_NaI2_1 << "\t" << dRes_Co_NaI2_1 << "\t\n";
      calfile << "1332\t" << Co_NaI2_2 << "\t" << dCo_NaI2_2 << "\t" << Res_Co_NaI2_2 << "\t" << dRes_Co_NaI2_2 << "\t\n";

      calfile << "LYSO Pedestal\n";
      calfile << "0\t" << pedestal_centre << "\t" << dpedestal_centre << "\t" << pedestal_res << "\t" << dpedestal_res << "\t\n";
    	calfile << "*********************************************************************************" << endl;
    }
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

	cout <<"Vuoi salvare i risultati del fit? (y/n)"<<endl;
   
   cin>>risp;
    
	if (risp == 'y'){
		calfile << "Calibrazione del cristallo di LYSO con sorgente C0 60"<<endl;
    	calfile << "Cobalto LYSO\n";
    	calfile << "1173\t" << (f13->GetParameter(1)) << "\t" <<(f13->GetParError(1)) << "\t" <<(f13->GetParameter(2))/(f13->GetParameter(1)) << "\t" << (f13->GetParError(2))/(f13->GetParameter(1)) << "\n";
    	calfile << "1332\t" << (f12->GetParameter(1)) << "\t" <<(f12->GetParError(1)) << "\t" <<(f12->GetParameter(2))/(f12->GetParameter(1)) << "\t" << (f12->GetParError(2))/(f12->GetParameter(1)) << "\n";
    	calfile << "*********************************************************************************" << endl;
    }
};

if(n_sezione == 0 || n_sezione == 4){
   TTree* tree4 = new TTree("tree4","data from ascii file");
   tree4->ReadFile(Fname6.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");

   TString Mask_Na1_0 = "abs(T42-1e-7)<4e-7 && abs(T32-1e-7)<3e-7 && T32!=0";
   TString Mask_Na1_1 = "&& abs(T34-5e-8)<3e-7 && T34!=0 && -A3/PK3<35e-8 && -A3/PK3>10e-8 && -A4/PK4<35e-8 && -A4/PK4>10e-8 && -A3<33e-9 && -A4<27e-9 && -A2<8e-9 && PK4<0.09 && PK3<0.11";
   TString Mask_Na1 = Mask_Na1_0 + Mask_Na1_1;

   // ISTOGRAMMI TEMPI
	TCanvas* c41 = new TCanvas();
	c41->SetGrid();
	c41->SetTitle("Na_T32_T42");
	tree4->Draw("T32:T42", Mask_Na1, "colz");
	c41->SaveAs("docs/group2/images/Na_T32_T42_1.png");
//	 c41->SaveAs("../docs/assets/images/Na_T32_T42_1.png");

	TCanvas* c42 = new TCanvas();
 	c42->SetTitle("Na_T34_T32");
	tree4->Draw("T34:T32", Mask_Na1, "colz");  // because in 0 there is a noisy spot 
	c42->SaveAs("docs/group2/images/Na_T34_T32_1.png");
//	 c42->SaveAs("../docs/assets/images/Na_T34_T32_1.png");

	// ISTOGRAMMI AREE/PICCHI
	TCanvas* c43 = new TCanvas();
	c43->SetTitle("Areas/peaks");
	tree4->Draw("-A3/PK3:-A4/PK4", Mask_Na1 , "colz");
	c43->SaveAs("docs/group2/images/Na_A3PK3_A4PK4_1.png");
//	 c43->SaveAs("../docs/assets/images/Na_A3PK3_A4PK4_1.png");

	// istogramma 2D delle aree NaI1 NaI2
	TCanvas* c44 = new TCanvas();
	c44->SetTitle("NaI1 vs NaI2");
	tree4->Draw("-A3:-A4", Mask_Na1 ,"colz");                    // AREE
	c44->SaveAs("docs/group2/images/Na_A3_A4_1.png");
//	 c44->SaveAs("../docs/assets/images/Na_A3_A4_1.png");
 
	TCanvas* c442 = new TCanvas();
	c442->SetTitle("Lyso vs NaI1");
	tree4->Draw("-A2:-A3", Mask_Na1, "colz");
 
	TCanvas* c45 = new TCanvas();
	c45->SetTitle("Peak-to-peak ch 3 and 4");
	tree4->Draw("PK3:PK4", Mask_Na1, "colz");                   // PICCHI
	// Istogrammi con dati filtrati 
	c45->SaveAs("docs/group2/images/Na_PK3_PK4_1.png");
//	 c44->SaveAs("../docs/assets/images/Na_PK3_PK4_1.png");

	TCanvas* c46 = new TCanvas();
	TH1D* h41 = new TH1D("h41","Peak @ 511 keV;NaI1 [V s];Events",200,0,4e-8);
	tree4->Draw("-A3>>h41", Mask_Na1, "colz");
	gPad->SetLogy();
	  
	TF1* f41 = new TF1("f41","[0]+gaus(1)",0,4e-8);
	f41->SetParameter(0,0);
	f41->SetParameter(1,70);
	f41->SetParameter(2,25.e-9); //centro gaussiana
	f41->SetParameter(3,1e-9); //sigma gaussiana
	h41->Fit("f41","L", " ", 20.5e-9, 30e-9); //L:likelyhood 
	c46->SaveAs("docs/group2/images/NaI1_511_1.png");
//	 c44->SaveAs("../docs/assets/images/NaI1_511_1.png");

   double p41  = f41->GetParameter(2); //centro gaussiana
   double ep41 = f41->GetParError(2); //suo errore
   double s41  = f41->GetParameter(3); //sigma gaussiana
   double e41  = f41->GetParError(3);  //suo errore

	TCanvas* c47 = new TCanvas();
	TH1D* h42 = new TH1D("h42","Peak @ 511 keV;NaI2 [V s];Events",200,0,3e-8);
	tree4->Draw("-A4>>h42", Mask_Na1, "colz");
	gPad->SetLogy();
	  
	TF1* f42 = new TF1("f42","[0]+gaus(1)",0,7e-8);
	f42->SetParameter(0,0);
	f42->SetParameter(1,70);	// altezza
	f42->SetParameter(2,17.e-9); //centro gaussiana
	f42->SetParameter(3,1e-9); //sigma gaussiana
	h42->Fit("f42","L", " ", 16e-9, 22e-9); //L:likelyhood 
	c47->SaveAs("docs/group2/images/NaI2_511_1.png");
//	 c47->SaveAs("../docs/assets/images/NaI2_511_1.png");

   double p42  = f42->GetParameter(2); //centro gaussiana
   double ep42 = f42->GetParError(2); //suo errore
   double s42  = f42->GetParameter(3); //sigma gaussiana
   double e42  = f42->GetParError(3);  //suo errore

	TCanvas* c48 = new TCanvas();
   TH1D* h43 = new TH1D("h43",";LYSO [V s];Events",200,0,8.1e-9);
   tree4->Draw("-A2>>h43", Mask_Na1, "colz");
   gPad->SetLogy();
  
   TF1* f43 = new TF1("f43","[0] + [4]*x +gaus(1) + gaus(5)",0,4e-8);
   f43->SetParameter(0,0);
   f43->SetParameter(1,100);	// altezza
   f43->SetParameter(2,3e-9); //centro gaussiana
   f43->SetParameter(3,2e-9); //sigma gaussiana
   f43->SetParameter(4,0);
   f43->SetParameter(5,100);	// altezza
   f43->SetParameter(6,6e-9); //centro gaussiana
   f43->SetParameter(7,2e-9); //sigma gaussiana
 
   h43->Fit("f43","L", " ", 2e-9, 7e-9); //L:likelyhood 
	c48->SaveAs("docs/group2/images/LYSO_1275_1.png");
//	 c48->SaveAs("../docs/assets/images/LYSO_1275_1.png");
 
   double p43   = f43->GetParameter(2); //centro gaussiana
   double ep43  = f43->GetParError(2); //suo errore
   double s43   = f43->GetParameter(3); //sigma gaussiana
   double e43   = f43->GetParError(3);  //suo errore
   double p432  = f43->GetParameter(6); //centro gaussiana
   double ep432 = f43->GetParError(6); //suo errore
   double s432  = f43->GetParameter(7); //sigma gaussiana
	double e432  = f43->GetParError(7);  //suo errore

	cout <<"Vuoi salvare i risultati del fit? (y/n)"<<endl;
   cin>>risp;
    
   if (risp == 'y'){
   	calfile << "Calibrazione con sorgente Na 22: 511 keV in NaI1 e NaI2" << endl;
   	calfile << "NaI1" <<endl;
		calfile << "511 keV @ " << p41 << "+-" << ep41 << endl;
		calfile << "sig @ 511 keV " << s41 << "+-" << e41 << endl;
		calfile << "NaI2" <<endl;
		calfile << "511 keV @ " << p42 << "+-" << ep42 << endl;
		calfile << "sig @ 511 keV " << s42 << "+-" << e42 << endl;
		calfile << "LYSO" <<endl;
		calfile << "511 keV @ " << p43 << "+-" << ep43 << endl;
		calfile << "sig @ 511 keV " << s43 << "+-" << e43 << endl;
		calfile << "LYSO" <<endl;
		calfile << "1275 keV @ " << p432 << "+-" << ep432 << endl;
		calfile << "sig @ 1275 keV " << s432 << "+-" << e432 << endl;

    	calfile << "*********************************************************************************" << endl;  
	}
};    

if(n_sezione == 0 || n_sezione == 5){
	TTree* tree5 = new TTree("tree5","data from ascii file");
   tree5->ReadFile(Fname7.Data(),"evnum/I:A1/F:A2/F:A3/F:A4/F:T12/F:T32/F:T42/F:T34/F:PK1/F:PK2/F:PK3/F:PK4/F");

   TString Mask_Na2_0 = "abs(T42-10e-9)<9e-9 && abs(T32-7e-9)<1e-8 && T32!=0";
   TString Mask_Na2_1 = "&& abs(T34+4e-9)<1e-8 && T34!=0 && -A3/PK3<30e-8 && -A3/PK3>5e-8 && -A4/PK4<30e-8 && -A4/PK4>15e-8 && PK4<0.09 && PK3<0.23 && -A3<6e-8 && -A4<30e-9 && -A2<8e-9";
   TString Mask_Na2 = Mask_Na2_0 + Mask_Na2_1;
   
   TCanvas* c51 = new TCanvas();
	c51->SetTitle("Na_T32_T42");
	tree5->Draw("T32:T42", Mask_Na2, "colz");
	c51->SaveAs("docs/group2/images/Na_T32_T42_2.png");

	TCanvas* c512 = new TCanvas();
	c512->SetTitle("Na_T34_T32");
	tree5->Draw("T34:T32", Mask_Na2, "colz");  // because in 0 there is a noisy spot 
	c512->SaveAs("docs/group2/images/Na_T34_T32_2.png");

	// ISTOGRAMMI AREE/PICCHI
	// Pulisco i dati eliminando gli eventi di pile-up
	TCanvas* c53 = new TCanvas();
	c53->SetTitle("Areas/peaks");
	tree5->Draw("-A3/PK3:-A4/PK4", Mask_Na2 , "colz");

	// istogramma 2D delle aree NaI1 NaI2
	TCanvas* c54 = new TCanvas();
	c54->SetTitle("NaI1 and NaI2 Areas");
	tree5->Draw("-A3:-A4", Mask_Na2 ,"colz");                    // AREE
	c54->SaveAs("docs/group2/images/Na_A3_A4_2.png");
	  
	TCanvas* c542 = new TCanvas();
	c542->SetTitle("Lyso vs NaI2 Areas");
	tree5->Draw("-A2:-A3", Mask_Na2, "colz");
	 
	TCanvas* c55 = new TCanvas();
	c55->SetTitle("Peak-to-peak ch 3 and 4");
	tree5->Draw("PK3:PK4", Mask_Na2, "colz");                   // PICCHI
	// Istogrammi con dati filtrati 
	c55->SaveAs("docs/group2/images/Na_PK3_PK4_2.png");

	TCanvas* c56 = new TCanvas();
	TH1D* h51 = new TH1D("h51","Peak @ 1275 keV;NaI1 [V s];Events",200,0,7e-8);
	tree5->Draw("-A3>>h51", Mask_Na2, "colz");
	gPad->SetLogy();
	  
	TF1* f51 = new TF1("f51","[0]+gaus(1)",0,7e-8);
	f51->SetParameter(0,0);
	f51->SetParameter(1,70);
	f51->SetParameter(2,56.e-9); //centro gaussiana
	f51->SetParameter(3,1e-9); //sigma gaussiana
	h51->Fit("f51","L", " ", 47e-9, 58e-9); //L:likelyhood 
	c56->SaveAs("docs/group2/images/NaI1_1275_2.png");

	double p51  = f51->GetParameter(2); //centro gaussiana
	double ep51 = f51->GetParError(2); //suo errore
	double s51  = f51->GetParameter(3); //sigma gaussiana
	double e51  = f51->GetParError(3);  //suo errore
	cout << "NaI1" <<endl;
	cout << "1275 keV@ " << p51 << "+-" << ep51 << endl;
	cout << "sig @ 1275 keV " << s51 << "+-" << e51 << endl;

	TCanvas* c57 = new TCanvas();
	TH1D* h52 = new TH1D("h52","Peak @ 511 keV;NaI2 [V s];Events",200,0,3e-8);
	tree5->Draw("-A4>>h52", Mask_Na2, "colz");
	gPad->SetLogy();
	  
	TF1* f52 = new TF1("f52","[0]+gaus(1)",0,7e-8);
	f52->SetParameter(0,0);
	f52->SetParameter(1,70);	// altezza
	f52->SetParameter(2,17.e-9); //centro gaussiana
	f52->SetParameter(3,1e-9); //sigma gaussiana
	h52->Fit("f52","L", " ", 14e-9, 21e-9); //L:likelyhood 
	c57->SaveAs("docs/group2/images/NaI2_511_2.png");

	double p52  = f52->GetParameter(2); //centro gaussiana
	double ep52 = f52->GetParError(2); //suo errore
	double s52  = f52->GetParameter(3); //sigma gaussiana
	double e52  = f52->GetParError(3);  //suo errore

	TCanvas* c58 = new TCanvas();
	TH1D* h53 = new TH1D("h53","Peak @ 511 keV;LYSO [V s];Events",200,0,8.1e-9);
	tree5->Draw("-A2>>h53", Mask_Na2, "colz");
	gPad->SetLogy();
	  
	TF1* f53 = new TF1("f53","[0]+gaus(1)",0,7e-8);
	f53->SetParameter(0,0);
	f53->SetParameter(1,100);	// altezza
	f53->SetParameter(2,2.2e-9); //centro gaussiana
	f53->SetParameter(3,1e-9); //sigma gaussiana
	h53->Fit("f53","L", " ", 1.6e-9, 3e-9); //L:likelyhood 
	c58->SaveAs("docs/group2/images/LYSO_511_2.png");

	double p53  = f53->GetParameter(2); //centro gaussiana
	double ep53 = f53->GetParError(2); //suo errore
	double s53  = f53->GetParameter(3); //sigma gaussiana
	double e53  = f53->GetParError(3);  //suo errore

	cout <<"Vuoi salvare i risultati del fit? (y/n)"<<endl;
   cin>>risp;
    
	if (risp == 'y'){
    	calfile << "Calibrazione con sorgente Na 22: 511 keV in NaI2 e LYSO" << endl;
		calfile << "NaI1" <<endl;
		calfile << "1275 keV @ " << p51 << "+-" << ep51 << endl;
		calfile << "sig @ 1275 keV " << s51 << "+-" << e51 << endl;
		calfile << "NaI2" <<endl;
		calfile << "511 keV @ " << p52 << "+-" << ep52 << endl;
		calfile << "sig @ 511 keV " << s52 << "+-" << e52 << endl;
		calfile << "LYSO" <<endl;
		calfile << "511 keV @ " << p53 << "+-" << ep53 << endl;
		calfile << "sig @ 511 keV " << s53 << "+-" << e53 << endl;

		calfile<<"*********************************************************************************" << endl; 	   
	}
}; 
calfile.close();
}
