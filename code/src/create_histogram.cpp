#include "TH1.h"
#include "TFile.h"
#include "TROOT.h"

//#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  /* Function that create a file with two histograms. This is to recover the
  initial and final energy of each track
  ex: "initial_ke", "Initial Kinetic Energy Distribution", 100 1e-11, 350e-9
  or: "final_ke", "Final Kinetic Energy Distribution", 100, 1e-11, 150e-9
  */

  // The command line is empty, the user need help
  if (argc == 1) {
    cout << "Usage: "
         << argv[0]
         << " path/name_source_file number_of_histograms"
         << endl;
    return EXIT_SUCCESS;
  }

  // The command line contain more than 1 argument
  if (argc != 2) {
    cerr << "Incorrect number of arguments." << endl;
    return EXIT_FAILURE;
  }

  // Update the file to add new histogram
  TFile *file = new TFile(argv[1], "UPDATE");

  // The variables that define the histogram
  Double_t upper_value;
  Double_t lower_value;
  Int_t n_bin;
  char* histogram_title = new char[50];
  char* histogram_id = new char[15];
  int n_histograms;

  cout << "Number of histograms: ";
  cin >> n_histograms;

  for (int i=0; i<n_histograms; i++) {
    // The user input
    cout << "The name of the histogram " << i+1 << " (no spaces allowed): ";
    cin >> histogram_title;
    cout << "The id of the histogram: ";
    cin >> histogram_id;
    cout << "Number of bin: ";
    cin >> n_bin;
    cout << "Lower value: ";
    cin >> lower_value;
    cout << "Upper value: ";
    cin >> upper_value;

    TH1F *histogram = new TH1F(histogram_id, histogram_title, n_bin, lower_value, upper_value);

    histogram->Write();

    cout << "The histogram " << i+1 << " have been created with "
         << histogram_id << ", "
         << histogram_title << ", "
         << n_bin << ", "
         << lower_value << ", "
         << upper_value << endl;
  }

  file->Close();

  cout << "The file " << argv[1] << " have been successfully created." << endl;

  return(EXIT_SUCCESS);
}
