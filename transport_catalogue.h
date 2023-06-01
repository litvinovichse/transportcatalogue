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

struct Request{
    int id{0};
    std::string type;
    std::string name;
};

struct Buses{
    std::string name;
    std::vector<std::string> stop;
    bool is_Circle;
};

struct Stops {
    std::string name{""};
    geo::Coordinates coordinates;
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
    void addBusToBase(const std::string &busnum, const std::vector<std::string>& stops, bool circle);
    void addStop(const std::string &name, const double &lat, const double longt, std::map<std::string, int>& neighboringStops);
    BusData::Info getDetailedRoute(std::string busName);
    std::set<std::string> getStopsForBus(std::string busName);
    const BusData::Buses* searchBuses(std::string busName);
    const BusData::Stops* searchStops(std::string stopName);
    void SetDistance(const BusData::Stops* from, const BusData::Stops* to, const int distance);
    int GetDistance(const BusData::Stops* from, const BusData::Stops* to);
    void fillDistance();
    void addRequestToList(BusData::Request req);

    /*
     * Здравствуйте, Марина!
    не совсем понял, что нужно в итоге сделать с этим методом (fillDistance).
    Если перенести его в input_reader, то он будет заполняться с nullptr'ами,
    а в таком случае, программа, разумеется, падает :(.
    Остальное, вроде бы, все подправил, тесты тренажера проходит.
    Спасибо Вам за Вашу помощь!
    */

    std::vector<BusData::Request> getRequestList() const;

private:


    std::deque<BusData::Stops> allStops;
    std::deque<BusData::Buses> allBuses;

    std::unordered_map<std::string_view, const BusData::Stops*> finderStops;
    std::unordered_map<std::string_view, const BusData::Buses*> finderBuses;


    std::unordered_map<std::string, std::set<std::string>> bussesForStop;


    std::unordered_map<std::pair<const BusData::Stops*, const BusData::Stops*>, int, Hashers::StopDistancesHasher> stop_distances_;
    std::unordered_map<std::string, std::map<std::string, int>> allNeighboringStops; // <stop name,<neighbourName, dist>>
    std::vector<BusData::Request> requestList;
};
}//BusCatalogue


