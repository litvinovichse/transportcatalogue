#pragma once
#include "transport_catalogue.h"
namespace Output {

    void processInputRequest(std::ostream &os, BusCatalogue::TransportCatalogue& tc);
    void parseRequest(std::ostream &os, BusCatalogue::TransportCatalogue& tc);
    void printBus(std::ostream &os, BusCatalogue::TransportCatalogue& tc, std::string request);
    void printStop(std::ostream &os, BusCatalogue::TransportCatalogue& tc, std::string name);

} //output
