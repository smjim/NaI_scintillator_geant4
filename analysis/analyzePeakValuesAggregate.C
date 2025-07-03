void analyzePeakValuesAggregate() {
    const int maxFiles = 10000;   // max files to try	// TODO if there are 1000000 then maybe do that if it doesnt crash
    const int nHist = 100;       // number of event histograms per file

    TH1D *hPeakValues = new TH1D("hPeakValues", "Histogram of Peak Values; Peak Bin Content; Events", 140, 0, 700);
    //TH1D *hPeakValues = new TH1D("hPeakValues", "Histogram of Peak Values; Peak Bin Content; Events", 50, 0, 1000);

    for (int f = 0; f < maxFiles; f++) {
        // Generate filename with leading zeros: 00, 001, ... 999
        TString fileName;
		fileName = TString::Format("../output/run_output_%06d.root", f);

        TFile *file = TFile::Open(fileName, "READ");
        if (!file || file->IsZombie()) {
            // If file not found or cannot open, assume no more files and break
            std::cout << "No more files found after " << f << ", stopping." << std::endl;
            break;
        }

        std::cout << "Processing file: " << fileName.Data() << std::endl;

        for (int i = 0; i < nHist; i++) {
            TString histName = TString::Format("arrivalTimes_evt%d", i);
            TH1D *h = (TH1D*)file->Get(histName);
            if (!h) {
                std::cerr << "Histogram " << histName << " not found in file " << fileName << std::endl;
                continue;
            }

            double maxContent = 0;
            int maxBin = 0;
            for (int bin = 1; bin <= h->GetNbinsX(); bin++) {
                double content = h->GetBinContent(bin);
                if (content > maxContent) {
                    maxContent = content;
                    maxBin = bin;
                }
            }

//            std::cout << "File " << fileName.Data() << " Event " << i << " max bin " << maxBin << " with content " << maxContent << std::endl;
            hPeakValues->Fill(maxContent);
        }

        file->Close();
        delete file;
    }

    TCanvas *c = new TCanvas("cPeakValues", "Peak Values Histogram", 800, 600);
    hPeakValues->SetLineColor(kRed);
    hPeakValues->Draw();
    c->Update();
}

