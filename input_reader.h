#pragma once
#include <istream>
#include "transport_catalogue.h"

class Recorder{
public:
    void recordNewDataIntoBase(TransportCatalogue& tc);
    void newBus(TransportCatalogue& tc, std::string BusData);
    void newStop(TransportCatalogue& tc, std::string StopData);

private:
};

