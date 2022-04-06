void compareHist(){
	//This will work only if you have the same setup as the one we had in the lecture!!!
	TFile *file1 = TFile::Open("Hdiff1.root");
	TH1D* hdiff1 = (TH1D*)file1->Get("hdiff");
	hdiff1->Draw();
	TFile *file2 = TFile::Open("Hdiff2.root");
	TH1D* hdiff2 = (TH1D*)file2->Get("hdiff2");
	hdiff2->Draw("Same");
	hdiff2->SetLineColor(3);
}
