// напишите решение с нуля
// код сохраните в свой git-репозиторий


#include <deque>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>

class TransportCatalogue{
public:
    struct Stops {
        std::string name{""};
        double latitude{0};
        double longitude{0};
    };
    void addBusToBase(std::string& busnum, std::vector<std::string> route);
    void addStop(std::string &name, double &alt, double &longt);
    void searchRoute();
    void serchStop();
    void getDetailedRoute(); //Bus X: R stops on route, U unique stops, L route length
private:
    std::map<std::string, std::vector<std::string *>> _route; // поменять потом на unordered_map && hash функцию
    std::deque<Stops> allStops;
    std::unordered_map<std::string, Stops *> stopname_to_stop;
};
