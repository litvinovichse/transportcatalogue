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

class TransportCatalogue{
public:
    struct Buses{
        std::string name;
        std::vector<std::string> stop;

        bool circle;
    };

    struct Stops {
        std::string name{""};
        Coordinates coordinates;
        std::map<std::string, int> nbs;
    };

    size_t uniqueStopsFill(std::string_view bus) const;

    struct Info {
        size_t stopsCount{ 0 };
        size_t uniqueStopsCount{ 0 };
        double length{ 0 };
        double curvature{ 0 };
        bool correct{ false };
    };

    struct StopDistancesHasher {
        size_t operator()(const std::pair<const Stops*, const Stops*>& points) const {
            size_t hash_first = std::hash<const void*>{}(points.first);
            size_t hash_second = std::hash<const void*>{}(points.second);
            return hash_first + hash_second * 37;
        }
    };

    void addBusToBase(std::string &busnum, std::vector<std::string> stops, bool circle);
    void addStop(const std::string &name, const double &lat, const double &longt, std::map<std::string, int> nb);
    size_t UniqueStopsCount(std::string_view bus_number) const;
    Info getDetailedRoute(std::string requestVal);
    std::set<std::string> getStopsForBus(std::string busName);
    const Buses* searchBuses(std::string value);
    const Stops* searchStops(std::string value);
    void SetDistance(const Stops* from, const Stops* to, const int distance);
    int GetDistance(const Stops* from, const Stops* to);
private:


    std::deque<Stops> allStops;
    std::deque<Buses> allBuses;

    std::unordered_map<std::string_view, const Stops*> finderStops;
    std::unordered_map<std::string_view, const Buses*> finderBuses;


    std::unordered_map<std::string, std::set<std::string>> bussesForStop;


    std::unordered_map<std::pair<const Stops*, const Stops*>, int, StopDistancesHasher> stop_distances_;
};



