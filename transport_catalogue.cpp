// напишите решение с нуля
// код сохраните в свой git-репозиторий
#include "transport_catalogue.h"
#include <iostream>

void TransportCatalogue::addBusToBase(std::string& busnum, std::vector<std::string> stops, bool circle)
{
    allBuses.push_back({busnum, stops, circle});
    finderBuses.insert(std::make_pair(allBuses.back().name, &allBuses.back()));
    for (const auto& s : stops){
            uniqueStops[s].insert(busnum);
    }

}

void TransportCatalogue::addStop(const std::string &name, const double &alt, const double &longt)
{
    allStops.push_back({name,{alt,longt}});
    finderStops.insert(std::make_pair(allStops.back().name, &allStops.back()));
}

std::string TransportCatalogue::getDetailedRoute(std::string requestVal)
{
    if (searchBuses(requestVal) != nullptr){
    std::string aaa = "Bus " + requestVal + ": " + std::to_string(searchBuses(requestVal)->stop.size());
    return aaa;
    }
    else {
    return "empty";
    }
}

const TransportCatalogue::Buses *TransportCatalogue::searchBuses(std::string value)
{
    if (finderBuses.find(value) != finderBuses.end()){
            return finderBuses.find(value)->second;
    }
    return nullptr;
}

const TransportCatalogue::Stops *TransportCatalogue::searchStops(std::string value)
{
    if (finderStops.find(value) != finderStops.end()){
            return finderStops.find(value)->second;
    }
    return nullptr;
}

