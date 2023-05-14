// напишите решение с нуля
// код сохраните в свой git-репозиторий
#include "transport_catalogue.h"

void TransportCatalogue::addBusToBase(std::string& busnum, std::vector<std::string> route)
{
    for(const auto &tmp : route){
        _route[busnum].push_back(&stopname_to_stop[tmp]->name);
    }
}

void TransportCatalogue::addStop(const std::string &name, const double &alt, const double &longt)
{
    allStops.push_back({name,alt,longt});
    stopname_to_stop[name] = &allStops.back();
}

