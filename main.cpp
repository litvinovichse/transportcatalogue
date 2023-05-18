#include <iostream>
#include "input_reader.h"
#include "stat_reader.h"

using namespace std;

int main()
{
    BusCatalogue::TransportCatalogue tc;
    Recorder rec;
    output::Stat st;
    string counter{ "" };
    std::getline(std::cin, counter);
        for (int i {1}; i <= stoi(counter); ++i){
        rec.recordNewDataIntoBase(tc);
    }
        tc.fillDistance();
    std::getline(std::cin, counter);
    for (int i {1}; i <= stoi(counter); ++i){
        st.parseRequest(tc);
    }
}

