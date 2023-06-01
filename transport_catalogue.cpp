// напишите решение с нуля
// код сохраните в свой git-репозиторий
#include "transport_catalogue.h"
#include <iostream>
#include <unordered_set>

void BusCatalogue::TransportCatalogue::addBusToBase(const std::string &busnum, const std::vector<std::string> &stops, bool circle)
{
    allBuses.push_back({busnum, stops, circle});
    finderBuses[allBuses.back().name] = &allBuses.back();
    for (const auto &a : allBuses.back().stop){
        bussesForStop[a].insert(busnum);
    }
}

void BusCatalogue::TransportCatalogue::addStop(const std::string &name, const double &lat, const double longt, std::map<std::string, int> &neighboringStops)
{
    allStops.push_back({name,{lat,longt}});
    finderStops[allStops.back().name] = &allStops.back();

    allNeighboringStops[name] = neighboringStops;

}

BusData::Info BusCatalogue::TransportCatalogue::getDetailedRoute(std::string busName)
{
    auto temp = finderBuses.find(busName);
    if (temp == finderBuses.end()) { return {0,0,0,0,false};}
    size_t stopsCount{ 0 };
    size_t uniqueStopsCount{ 0 };
    double length{ 0 };
    double curva{ 0.0 };

    if (searchBuses(busName)->is_Circle){
        stopsCount = temp->second->stop.size();
    } else {
        stopsCount = temp->second->stop.size() * 2 - 1;
    }

    std::unordered_set<std::string_view> unique_stops;
    for (const auto& stop : finderBuses.at(busName)->stop) {
        unique_stops.insert(stop);
    }
    uniqueStopsCount = unique_stops.size();


    for (size_t i {1}; i < temp->second->stop.size(); ++i){
        length+= ComputeDistance(finderStops.at(temp->second->stop[i-1])->coordinates,finderStops.at(temp->second->stop[i])->coordinates);
        if (!temp->second->is_Circle) {
            curva += GetDistance(finderStops.at(temp->second->stop[i-1]), finderStops.at(temp->second->stop[i])) +
                     GetDistance(finderStops.at(temp->second->stop[i]), finderStops.at(temp->second->stop[i-1]));
        } else {
            curva += GetDistance(finderStops.at(temp->second->stop[i-1]), finderStops.at(temp->second->stop[i]));
        }
    }
    if (!temp->second->is_Circle){
        length = length * 2;
    }



    return {stopsCount, uniqueStopsCount, length, curva, true};
}

std::set<std::string> BusCatalogue::TransportCatalogue::getStopsForBus(std::string busName)
{
    if (bussesForStop.count(busName)){
        return bussesForStop.at(busName);
    }
    return {};
}


const BusData::Buses *BusCatalogue::TransportCatalogue::searchBuses(std::string busName)
{
    if (finderBuses.find(busName) != finderBuses.end()){
        return finderBuses.find(busName)->second;
    }
    return nullptr;
}

const BusData::Stops *BusCatalogue::TransportCatalogue::searchStops(std::string stopName)
{
    if (finderStops.find(stopName) != finderStops.end()){
        return finderStops.find(stopName)->second;
    }
    return nullptr;
}

void BusCatalogue::TransportCatalogue::SetDistance(const BusData::Stops *from, const BusData::Stops *to, const int distance)
{
    stop_distances_[{from, to}] = distance;
}

int BusCatalogue::TransportCatalogue::GetDistance(const BusData::Stops *from, const BusData::Stops *to)
{
    if (stop_distances_.count({ from, to })) {
        return stop_distances_.at({ from, to });
    } else if (stop_distances_.count({ to, from })){
        return stop_distances_.at({ to, from });
    }
    return 0;
}

void BusCatalogue::TransportCatalogue::fillDistance()
{
    for (const auto &a : allNeighboringStops){
        for (const auto &b : a.second){
            SetDistance(finderStops.at(a.first), finderStops.at(b.first), b.second);
        }
    }
}

void BusCatalogue::TransportCatalogue::addRequestToList(BusData::Request req)
{
    requestList.push_back(req);
}


namespace BusCatalogue {
std::vector<BusData::Request> TransportCatalogue::getRequestList() const
{
    return requestList;
}

}
