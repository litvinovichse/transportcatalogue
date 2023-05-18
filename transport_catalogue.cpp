// напишите решение с нуля
// код сохраните в свой git-репозиторий
#include "transport_catalogue.h"
#include <iostream>
#include <unordered_set>

void TransportCatalogue::addBusToBase(std::string& busnum, std::vector<std::string> stops, bool circle)
{
    allBuses.push_back({busnum, stops, circle});
    finderBuses[allBuses.back().name] = &allBuses.back();
    for (const auto &a : allBuses.back().stop){
        bussesForStop[a].insert(busnum);
    }
}

void TransportCatalogue::addStop(const std::string &name, const double &lat, const double &longt, std::map<std::string, int> nb)
{
    allStops.push_back({name,{lat,longt}});
    finderStops[allStops.back().name] = &allStops.back();

    nbs[name] = nb;
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
    if (temp == finderBuses.end()) { return {0,0,0,0,false};}
    size_t stopsCount{ 0 };
    size_t uniqueStopsCount{ 0 };
    double length{ 0 };
    double curva{ 0.0 };

    if (searchBuses(requestVal)->circle){
        stopsCount = temp->second->stop.size();
    } else {
        stopsCount = temp->second->stop.size() * 2 - 1;
    }

    for (const auto &a : nbs){
        for (const auto &b : nbs.at(requestVal)){
            SetDistance(finderStops.at(a.first), finderStops.at(b.first), b.second);
        }
    }

    uniqueStopsCount = UniqueStopsCount(requestVal);


    for (size_t i {1}; i < temp->second->stop.size(); ++i){
        length+= ComputeDistance(finderStops.at(temp->second->stop[i-1])->coordinates,finderStops.at(temp->second->stop[i])->coordinates);
        if (!temp->second->circle) {
            curva += GetDistance(finderStops.at(temp->second->stop[i-1]), finderStops.at(temp->second->stop[i])) +
                GetDistance(finderStops.at(temp->second->stop[i]), finderStops.at(temp->second->stop[i-1]));
        } else {
            curva += GetDistance(finderStops.at(temp->second->stop[i-1]), finderStops.at(temp->second->stop[i]));
        }
    }
    if (!temp->second->circle){
        length = length * 2;
    }



    return {stopsCount, uniqueStopsCount, length, curva, true};
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

void TransportCatalogue::SetDistance(const Stops *from, const Stops *to, const int distance)
{
    stop_distances_[{from, to}] = distance;
}

int TransportCatalogue::GetDistance(const Stops *from, const Stops *to)
{
    if (stop_distances_.count({ from, to })) {
        return stop_distances_.at({ from, to });
    } else if (stop_distances_.count({ to, from })){
        return stop_distances_.at({ to, from });
    }
    return 0;
}

