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
    void addStop(const std::string &name, const double &alt = 0, const double &longt = 0);
    void searchRoute();
    void serchStop();
    void getDetailedRoute(); //Bus X: R stops on route, U unique stops, L route length
private:
    std::unordered_map<std::string, std::vector<std::string *>> _route; // поменять потом на unordered_map && hash функцию
    std::deque<Stops> allStops;
    std::unordered_map<std::string, Stops *> stopname_to_stop;
};


/*
 * #include "geo.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <deque>
#include <vector>

/*transport_catalogue.h, transport_catalogue.cpp — класс транспортного справочника;*/

struct Bus{                                     /*ИНФОРМАЦИЯ ОБ АВТОБУСЕ*/
    std::string bus_name;                      //имя автобуса
    std::vector<std::string> stops;             //все имеющиеся остановки этого автобуса
    bool circular_route;                        //круговой маршрут yes or not.
};

struct Stop{                                    /*ИНФОРМАЦИЯ ОБ ОСТАНОВКЕ*/
    std::string stop_name;                      //имя остановки
    Coordinates coordinate_stop;                //координаты остановки
};

struct InfoRoute{                               /*ИНФОРМАЦИЯ О МАРШРУТЕ*/
    size_t stops_count;                         //количество остановок
    size_t stops_unique_count;                  //количество уникальных остановок
    double distance_route;                      //длина маршрута
};

class TransportCatalogue{
public:

    void AddStop(const std::string& s_name, Coordinates& coordinate);                                           //добавить остановку
    void AddBus(const std::string& route_name, const std::vector<std::string>&st_name, bool circular_route);    //добавить автобус
    const Stop* FindStop(std::string& stop_name) const;                                                         //найти остановку
    const Bus* FindBus(std::string& b_name) const;                                                              //найти автобус
    const InfoRoute GetBusInfo(std::string& route_name);                                                        //найти информацию о маршруте автобуса
    size_t StopsUniqueCount(std::string& unique_bus_name);                                                      //уникальное количество остановок автобуса


private:
    std::deque<Stop> all_bus_stop_;                                             //все остановки
    std::deque<Bus> all_bus_info_;                                              //информация о всех автобусах
    std::unordered_map<std::string_view, const Bus*>busname_to_bus_;            //поиск по нэйму автобуса информацию об автобусе
    std::unordered_map<std::string_view, const Stop*>stopname_to_stop_;         //поиск по нэйму остановки информацию об остановке
};
