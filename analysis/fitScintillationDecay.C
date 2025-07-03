void fitScintillationDecay(int eventNumber=0) {
    TFile *file = TFile::Open("1e6_per_MeV.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    TString histName = TString::Format("arrivalTimes_evt%d", eventNumber);
    TH1D *h = (TH1D*)file->Get(histName);
    if (!h) {
        std::cerr << "Histogram " << histName << " not found!" << std::endl;
        return;
    }

    // Define function: f(x) = A * exp(-x/tau) for x > 0
    TF1 *fitFunc = new TF1("fitFunc", "[0]*exp(-x/[1])*(x>0)", 0, h->GetXaxis()->GetXmax());
    fitFunc->SetParameters(h->GetMaximum(), 250.0); // Amplitude, decay constant
    fitFunc->SetParLimits(0, 0, 1e7);  // amplitude
    fitFunc->SetParLimits(1, 1, 1000); // tau

    TCanvas *c = new TCanvas("cFit", "Scintillation Decay Fit", 800, 600);
    h->SetTitle(Form("Photon Arrival Times Event %d;Time (ns);Counts", eventNumber));
    h->Draw();
    h->Fit(fitFunc, "R");

    c->Update();

    double tau = fitFunc->GetParameter(1);
    double tauErr = fitFunc->GetParError(1);
    std::cout << "Decay time constant τ = " << tau << " ± " << tauErr << " ns" << std::endl;
}

