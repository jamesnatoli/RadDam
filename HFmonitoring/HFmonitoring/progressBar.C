// progress bar for loops :)
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

void progressBar( Long64_t ientry, Long64_t nentries, std::chrono::time_point<std::chrono::high_resolution_clock> start) {
  Int_t barWidth = 100;
  if (((ientry % ((int)(nentries / barWidth))) == 0) && (nentries > 0)) {
    std::cout << "[";
    float progress = (float)ientry / nentries;
    int pos = barWidth * progress;
    for (int b = 0; b < barWidth; ++b) {
      if (b < pos) std::cout << "=";
      else if (b == pos) std::cout << ">";
      else std::cout << " ";
    }
    std::cout << "] "; 
    if (progress != 0) {
      auto checkpoint = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::seconds>(checkpoint - start);
      std::cout << std::setw(5) << (100 * round(progress * 100) / 100) << "%" << ", ETA: " 
		<< std::setw(15) << round((std::chrono::duration<float>(duration).count() / (progress)) - (std::chrono::duration<float>(duration).count()))
		<< " seconds";
    } else
      std::cout << "Getting time estimate...";
    std::cout << "\r";
    std::cout.flush();
  }
  return;
}

