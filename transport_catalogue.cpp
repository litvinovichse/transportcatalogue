// напишите решение с нуля
// код сохраните в свой git-репозиторий
#include "transport_catalogue.h"

void TransportCatalogue::addBusToBase(std::string& busnum, std::vector<std::string> stops, bool &circle)
{
    for(const auto &tmp : stops){
        rote_of_buses[busnum].push_back(&stopname_to_stop[tmp]->name);
    }
}

void TransportCatalogue::addStop(const std::string &name, const double &alt, const double &longt)
{
    allStops.push_back({name,{alt,longt}});
    stopname_to_stop[name] = &allStops.back();
}

