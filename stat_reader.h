#pragma once
#include "transport_catalogue.h"

class Stat{
public:
    void parseRequest(TransportCatalogue& tc);
    void output(TransportCatalogue& tc, std::string request);

};
