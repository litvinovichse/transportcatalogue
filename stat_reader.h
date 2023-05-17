#pragma once
#include "transport_catalogue.h"
namespace output {
class Stat{
public:
    void parseRequest(TransportCatalogue& tc);
    void bus(TransportCatalogue& tc, std::string request);
    void stop(TransportCatalogue& tc, std::string name);
};
} //output
