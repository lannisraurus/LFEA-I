#include "data_colector.cpp"

int main(){
    
    data_colector alfa("alfa_3_data.txt");
    vector<double> x = alfa.get_a_certain_col(2);
    //vector<double> FWHM = alfa.get_a_certain_col(2);
    //vector<double> N = alfa.get_a_certain_col(3);
    vector<double> ex;
    vector<double> y = alfa.get_a_certain_col(1);
    vector<double> ey;
    Int_t points_numb = x.size();
    double peak_energy_MeV = 5.3044;
    double chn = 372.45;
    double echn = 11.15 / 2.355 / sqrt(1861);
    double e_peak_p_units_MeV = 5.14235;

    /*for (int i = 0; i < x.size(); i++){
        
        ex.push_back(FWHM[i] / 2.355 / sqrt(N[i]));
    }*/
    
    for (int i = 0; i < x.size(); i++){
        
        y.push_back(y[i] * peak_energy_MeV / e_peak_p_units_MeV);

    }

    double* x_ptr = &x[0];
    //double* ex_ptr = &ex[0];
    double* y_ptr = &y[0];
    //double* ey_ptr = &ey[0];

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraph* g = new TGraph(points_numb, x_ptr, y_ptr);
    TF1* f = new TF1("f", "[0] * x + [1]");
    TPaveText* pt = new TPaveText(225, 5, 325, 6, "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    g->SetMarkerStyle(8);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("Channels");
    g->GetXaxis()->SetLimits(200, 750);
    g->GetXaxis()->SetNdivisions(-210);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Real energy (MeV)");
    g->GetYaxis()->SetRangeUser(4, 7);
    g->GetYaxis()->SetNdivisions(-508);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");
    pt->AddText(Form("y = ax + b"));
    pt->AddText(Form("a = %.10f %c %.10f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.10f %c %.10f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.10f", f->GetChisquare()));
    pt->Draw();

    C->Update();
    C->SaveAs("alfa_fit.png");
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete A;

    return 0;
}