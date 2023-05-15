// напишите решение с нуля
// код сохраните в свой git-репозиторий
#include "transport_catalogue.h"

void TransportCatalogue::addBusToBase(std::string& busnum, std::vector<std::string> stops, bool circle)
{
    allBuses.push_back({busnum, stops, circle});
    finderBuses.insert(std::make_pair(allBuses.back().name, &allBuses.back()));
}

void TransportCatalogue::addStop(const std::string &name, const double &alt, const double &longt)
{
    allStops.push_back({name,{alt,longt}});
    finderStops.insert(std::make_pair(allStops.back().name, &allStops.back()));
}

const TransportCatalogue::Buses *TransportCatalogue::searchBuses(std::string& busName)
{
    if(finderBuses.count(busName)){
        return finderBuses.at(busName);
    }
}

const TransportCatalogue::Stops *TransportCatalogue::serchStop(std::string& stopName)
{
    return finderStops.at(stopName);
}

void TransportCatalogue::getDetailedRoute(std::string &requestVal)
{

}

