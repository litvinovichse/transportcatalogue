#pragma once
#include <deque>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <set>

#include "geo.h"
namespace BusData {

struct Buses{
    std::string name;
    std::vector<std::string> stop;
    bool circle;
};

struct Stops {
    std::string name{""};
    Coordinates coordinates;
};


struct Info {
    size_t stopsCount{ 0 };
    size_t uniqueStopsCount{ 0 };
    double length{ 0 };
    double curvature{ 0 };
    bool correct{ false };
};

}//BusData

namespace Hashers {

struct StopDistancesHasher {
    size_t operator()(const std::pair<const BusData::Stops*, const BusData::Stops*>& points) const {
        size_t hash_first = std::hash<const void*>{}(points.first);
        size_t hash_second = std::hash<const void*>{}(points.second);
        return hash_first + hash_second * 37;
    }
};
}//Hashers

namespace BusCatalogue {

class TransportCatalogue{
public:

    size_t uniqueStopsFill(std::string_view bus) const;
    void addBusToBase(std::string &busnum, std::vector<std::string> stops, bool circle);
    void addStop(const std::string &name, const double &lat, const double &longt, std::map<std::string, int> nb);
    size_t UniqueStopsCount(std::string_view bus_number) const;
    BusData::Info getDetailedRoute(std::string requestVal);
    std::set<std::string> getStopsForBus(std::string busName);
    const BusData::Buses* searchBuses(std::string value);
    const BusData::Stops* searchStops(std::string value);
    void SetDistance(const BusData::Stops* from, const BusData::Stops* to, const int distance);
    int GetDistance(const BusData::Stops* from, const BusData::Stops* to);
    void fillDistance();
private:


    std::deque<BusData::Stops> allStops;
    std::deque<BusData::Buses> allBuses;

    std::unordered_map<std::string_view, const BusData::Stops*> finderStops;
    std::unordered_map<std::string_view, const BusData::Buses*> finderBuses;


    std::unordered_map<std::string, std::set<std::string>> bussesForStop;


    std::unordered_map<std::pair<const BusData::Stops*, const BusData::Stops*>, int, Hashers::StopDistancesHasher> stop_distances_;
    std::unordered_map<std::string, std::map<std::string, int>> nbs; // <stop name,<neighbourName, dist>>
};
}//BusCatalogue



