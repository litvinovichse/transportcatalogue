// напишите решение с нуля
// код сохраните в свой git-репозиторий


#include <deque>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
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



    void addBusToBase(std::string &busnum, std::vector<std::string> stops,
                      bool circle);
    void addStop(const std::string &name, const double &alt = 0, const double &longt = 0);
//    auto searchBuses(std::string& busName);
//    const Stops *serchStop(std::string& stopName);
    std::string getDetailedRoute(std::string requestVal);
private:

    const Buses* searchBuses(std::string value);
    const Stops* searchStops(std::string value);

    std::deque<Stops> allStops;
    std::deque<Buses> allBuses;

    std::unordered_map<std::string_view, const Stops*> finderStops;
    std::unordered_map<std::string_view, const Buses*> finderBuses;

    std::unordered_map<std::string, std::set<std::string>> uniqueStops; //остановка - автобусы, в которых она присутствует
};



