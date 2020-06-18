#include "TH1.h"
#include "TFile.h"
#include "TROOT.h"

//#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
  // The command line is empty, the user need help
  if (argc == 1) {
    std::cout << "Usage: "
              << argv[0]
              << " path/name_source_file"
              << std::endl;
    return EXIT_SUCCESS;
  }

  // The command line contain more than 1 argument
  if (argc != 2) {
    std::cerr << "Incorrect number of arguments." << std::endl;
    return EXIT_FAILURE;
  }

  // Recreate the file
  TFile *file = new TFile(argv[1], "RECREATE");

  TH1F *histogram_inital_ke = new TH1F("initial_ke", "Initial Kinetic Energy Distribution", 100, 1e-11, 350e-9);
  TH1F *histogram_final_ke = new TH1F("final_ke", "Final Kinetic Energy Distribution", 100, 1e-11, 150e-9);

  histogram_inital_ke->Write();
  histogram_final_ke->Write();

  file->Close();

  std::cout << "The file " << argv[1] << " have been successfully created." << std::endl;

  return(EXIT_SUCCESS);
}
