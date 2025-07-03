void analyzePeakValues() {
    TFile *file = TFile::Open("output.root", "READ");
    //TFile *file = TFile::Open("1e6_per_MeV.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    const int nHist = 10; // Number of event histograms
    TH1D *hPeakValues = new TH1D("hPeakValues", "Histogram of Peak Values; Peak Bin Content; Events", 50, 0, 10000);

    for (int i = 0; i < nHist; i++) {
        TString histName = TString::Format("arrivalTimes_evt%d", i);
        TH1D *h = (TH1D*)file->Get(histName);
        if (!h) {
            std::cerr << "Histogram " << histName << " not found!" << std::endl;
            continue;
        }

        // Find max bin content
        double maxContent = 0;
        int maxBin = 0;
        for (int bin = 1; bin <= h->GetNbinsX(); bin++) {
            double content = h->GetBinContent(bin);
            if (content > maxContent) {
                maxContent = content;
                maxBin = bin;
            }
        }

        std::cout << "Event " << i << " max bin " << maxBin << " with content " << maxContent << std::endl;
        hPeakValues->Fill(maxContent);
    }

    TCanvas *c = new TCanvas("cPeakValues", "Peak Values Histogram", 800, 600);
    hPeakValues->SetLineColor(kRed);
    hPeakValues->Draw();
    c->Update();
}

