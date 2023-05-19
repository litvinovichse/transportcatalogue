#pragma once
#include <istream>
#include "transport_catalogue.h"

namespace Input {

    void processInputRequest(BusCatalogue::TransportCatalogue& tc);
    void parseRequest(BusCatalogue::TransportCatalogue& tc);
    void parseBus(BusCatalogue::TransportCatalogue& tc, std::string BusData);
    void parseStop(BusCatalogue::TransportCatalogue& tc, std::string StopData);

}

