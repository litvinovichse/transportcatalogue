#include "geo.h"
#include <string>
#include <vector>
namespace BusData {

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
}
