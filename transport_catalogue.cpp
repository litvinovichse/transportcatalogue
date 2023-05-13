// напишите решение с нуля
// код сохраните в свой git-репозиторий
#include "transport_catalogue.h"

void TransportCatalogue::addBusToBase(std::string &busnum)
{
    if (!route.count(busnum)){
        route[busnum]={};
    }
}

void TransportCatalogue::addStop(std::string &name, double &alt, double &longt)
{
    allStops.push_back({name,alt,longt});
    stopname_to_stop[name] = &allStops.back();
}

