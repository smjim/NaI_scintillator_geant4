void plotArrivalTimes() {
    TFile *file = TFile::Open("1e6_per_MeV.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    const int nHist = 10; // number of histograms you showed
    for (int i = 0; i < nHist; i++) {
        TString histName = TString::Format("arrivalTimes_evt%d", i);
        TH1D* h = (TH1D*)file->Get(histName);
        if (!h) {
            std::cerr << "Histogram " << histName << " not found!" << std::endl;
            continue;
        }

        TCanvas *c = new TCanvas(histName, histName, 800, 600);
        h->SetLineColor(kBlue);
        h->SetTitle(Form("Photon Arrival Times Event %d; Time (ns); Counts", i));
        h->Draw();
        c->Update();
    }
}

