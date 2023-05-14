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

    void addBusToBase(std::string& busnum, std::vector<std::string> stops, bool& circle);
    void addStop(const std::string &name, const double &alt = 0, const double &longt = 0);
    void searchRoute();
    void serchStop();
    void getDetailedRoute();
private:
    //должны быть :
    /* 1. набор маршрутов - контейнер структур.*/
    std::deque<Buses> allBusses;
    /* 2. маршрут(автобус) - структура. состоит из имени автобуса + контейнер структур остановок (тут ссылки должны быть).*/
    /* 3. структура остановки, состоящая из имени + структуры координат, которая находится в файле geo.
    */







    ////для автобусов
    //весь перечень

    //поиск
    std::unordered_map<std::string, std::vector<std::string *>> rote_of_buses;

    ////для остановок
    //весь перечень
    std::deque<Stops> allStops;
    //поиск
    std::unordered_map<std::string_view, Stops *> stopname_to_stop;
};



