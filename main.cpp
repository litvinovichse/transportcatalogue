// напишите решение с нуля
// код сохраните в свой git-репозиторий
#include <iostream>
#include "stat_reader.h"


using namespace std;

int main()
{
    TransportCatalogue tc;
    Recorder rec;
    string counter{ " " };
    std::getline(std::cin, counter);

        for (int i {1}; i <= stoi(counter); ++i){
        rec.recordNewDataIntoBase(tc);

    }
}
