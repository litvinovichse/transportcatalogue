#pragma once
#include "transport_catalogue.h"
namespace output {
class Stat{
public:
    void parseRequest(BusCatalogue::TransportCatalogue& tc);
    void bus(BusCatalogue::TransportCatalogue& tc, std::string request);
    void stop(BusCatalogue::TransportCatalogue& tc, std::string name);
};
} //output
