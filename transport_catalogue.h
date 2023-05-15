// напишите решение с нуля
// код сохраните в свой git-репозиторий


#include <deque>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>

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

    void addBusToBase(std::string& busnum, std::vector<std::string> stops, bool circle);
    void addStop(const std::string &name, const double &alt = 0, const double &longt = 0);
    const Buses *searchBuses(std::string& busName);
    const Stops *serchStop(std::string& stopName);
    void getDetailedRoute(std::string& requestVal);
private:

    std::deque<Stops> allStops;
    std::deque<Buses> allBuses;

    std::unordered_map<std::string_view, const Buses*> finderBuses;
    std::unordered_map<std::string_view, const Stops*> finderStops;

    size_t countUnique;
};



