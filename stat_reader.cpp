#include "stat_reader.h"
#include <iostream>

void output::Stat::parseRequest(TransportCatalogue &tc)
{
    std::string line;
    std::getline(std::cin, line);
    if (line.substr(0, line.find_first_of(' ')) == "Bus"){
        line = line.substr(line.find_first_of(' ') + 1);
        bus(tc, line);
    } else if(line.substr(0, line.find_first_of(' ')) == "Stop") {
        line = line.substr(line.find_first_of(' ') + 1);
        stop(tc, line);
    }
}

void output::Stat::bus(TransportCatalogue &tc, std::string request)
{
    auto detail = tc.getDetailedRoute(request);
    if (!detail.correct){
        std::cout << "Bus " << request << ": not found" << std::endl;
        return;
    }
    std::cout << "Bus " << request <<": " << detail.stopsCount << " stops on route, " << detail.uniqueStopsCount << " unique stops, "
              << detail.curvature <<" route length, " << detail.curvature/detail.length << " curvature" << std::endl;;
}

void output::Stat::stop(TransportCatalogue &tc, std::string name)
{
    if (tc.searchStops(name) == nullptr){
        std::cout << "Stop " << name << ": not found" << std::endl;
    } else {
        auto a = tc.getStopsForBus(name);
        if (a.empty()){
            std::cout << "Stop " << name << ": no buses" << std::endl;
        } else {
            std::cout << "Stop " << name << ": buses ";
            for(const auto &bus : a){
                std::cout << bus << " ";
            }
            std::cout << std::endl;
        }
    }
/*Stop X: buses bus1 bus2 ... busN
bus1 bus2 ... busN — список автобусов, проходящих через остановку. Дубли не допускаются, названия должны быть отсортированы в алфавитном порядке.
Если остановка X не найдена, выведите Stop X: not found.
Если остановка X существует в базе, но через неё не проходят автобусы, выведите Stop X: no buses.*/
}
