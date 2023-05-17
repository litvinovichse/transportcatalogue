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
    };

    size_t uniqueStopsFill(std::string_view bus) const;

    struct Info {
        size_t stopsCount{ 0 };
        size_t uniqueStopsCount{ 0 };
        double length{ 0 };
        bool correct{ false };
    };

    void addBusToBase(std::string &busnum, std::vector<std::string> stops, bool circle);
    void addStop(const std::string &name, const double &lat = 0, const double &longt = 0);
    size_t UniqueStopsCount(std::string_view bus_number) const;
    Info getDetailedRoute(std::string requestVal);
    std::set<std::string> getStopsForBus(std::string busName);
    const Buses* searchBuses(std::string value);
    const Stops* searchStops(std::string value);

private:


    std::deque<Stops> allStops;
    std::deque<Buses> allBuses;

    std::unordered_map<std::string_view, const Stops*> finderStops;
    std::unordered_map<std::string_view, const Buses*> finderBuses;

    std::unordered_map<std::string, std::set<std::string>> bussesForStop;


    //std::unordered_map<std::pair<const Stops*, const Stops*>, int> stop_distances_;
};



