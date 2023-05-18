#pragma once
#include <istream>
#include "transport_catalogue.h"

class Recorder{
public:
    void recordNewDataIntoBase(BusCatalogue::TransportCatalogue& tc);
    void newBus(BusCatalogue::TransportCatalogue& tc, std::string BusData);
    void newStop(BusCatalogue::TransportCatalogue& tc, std::string StopData);

private:
};

