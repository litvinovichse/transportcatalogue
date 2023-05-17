// напишите решение с нуля
// код сохраните в свой git-репозиторий
#include "transport_catalogue.h"
#include <iostream>
#include <unordered_set>

void TransportCatalogue::addBusToBase(std::string& busnum, std::vector<std::string> stops, bool circle)
{
    allBuses.push_back({busnum, stops, circle});
    std::string_view a = allBuses.back().name;
    finderBuses[a] = &allBuses.back();
    for (const auto &a : allBuses.back().stop){
        bussesForStop[a].insert(busnum);
    }
}

void TransportCatalogue::addStop(const std::string &name, const double &lat, const double &longt)
{
    allStops.push_back({name,{lat,longt}});
    std::string_view a = allStops.back().name;
    finderStops[a] = &allStops.back();
}

size_t TransportCatalogue::UniqueStopsCount(std::string_view bus_number) const
{
    std::unordered_set<std::string_view> unique_stops;
    for (const auto& stop : finderBuses.at(bus_number)->stop) {
        unique_stops.insert(stop);
    }
    return unique_stops.size();
}

TransportCatalogue::Info TransportCatalogue::getDetailedRoute(std::string requestVal)
{
    auto temp = finderBuses.find(requestVal);
    if (temp == finderBuses.end()) { return {0,0,0,false};}
    size_t stopsCount{ 0 };
    size_t uniqueStopsCount{ 0 };
    double length{ 0 };
    if (searchBuses(requestVal)->circle){
        stopsCount = temp->second->stop.size();
    } else {
        stopsCount = temp->second->stop.size() * 2 - 1;
    }

    uniqueStopsCount = UniqueStopsCount(requestVal);


    for (size_t i {1}; i < temp->second->stop.size(); ++i){
        length+= ComputeDistance(finderStops.at(temp->second->stop[i-1])->coordinates,finderStops.at(temp->second->stop[i])->coordinates);
    }
    if (!temp->second->circle){
        length = length * 2;
    }
    return {stopsCount, uniqueStopsCount, length, true};
}

std::set<std::string> TransportCatalogue::getStopsForBus(std::string busName)
{
    if (bussesForStop.count(busName)){
        return bussesForStop.at(busName);
    }
    return {};
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

