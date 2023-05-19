#include <iostream>
#include "input_reader.h"
#include "stat_reader.h"

using namespace std;

int main()
{
    BusCatalogue::TransportCatalogue tc;

    Input::processInputRequest(tc);
    Output::processInputRequest(std::cout, tc);
}

