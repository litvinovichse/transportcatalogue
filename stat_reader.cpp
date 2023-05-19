#include "stat_reader.h"
#include <iostream>

void Output::parseRequest(std::ostream &os, BusCatalogue::TransportCatalogue &tc)
{
    std::string line;
    std::getline(std::cin, line);
    if (line.substr(0, line.find_first_of(' ')) == "Bus"){
        line = line.substr(line.find_first_of(' ') + 1);
        printBus(os, tc, line);
    } else if(line.substr(0, line.find_first_of(' ')) == "Stop") {
        line = line.substr(line.find_first_of(' ') + 1);
        printStop(os, tc, line);
    }
}

void Output::printBus(std::ostream &os, BusCatalogue::TransportCatalogue& tc, std::string request)
{
    auto detail = tc.getDetailedRoute(request);
    if (!detail.correct){
        os << "Bus " << request << ": not found" << std::endl;
        return;
    }
    os << "Bus " << request <<": " << detail.stopsCount << " stops on route, " << detail.uniqueStopsCount << " unique stops, "
              << detail.curvature <<" route length, " << detail.curvature/detail.length << " curvature" << std::endl;;
}

void Output::printStop(std::ostream &os, BusCatalogue::TransportCatalogue& tc, std::string name)
{
    if (tc.searchStops(name) == nullptr){
        os << "Stop " << name << ": not found" << std::endl;
    } else {
        auto a = tc.getStopsForBus(name);
        if (a.empty()){
            os << "Stop " << name << ": no buses" << std::endl;
        } else {
            os << "Stop " << name << ": buses ";
            for(const auto &bus : a){
                os << bus << " ";
            }
            os << std::endl;
        }
    }
/*Stop X: buses bus1 bus2 ... busN
bus1 bus2 ... busN — список автобусов, проходящих через остановку. Дубли не допускаются, названия должны быть отсортированы в алфавитном порядке.
Если остановка X не найдена, выведите Stop X: not found.
Если остановка X существует в базе, но через неё не проходят автобусы, выведите Stop X: no buses.*/
}

void Output::processInputRequest(std::ostream &os, BusCatalogue::TransportCatalogue& tc)
{
    std::string counter;
    std::getline(std::cin, counter);
    for (int i {1}; i <= stoi(counter); ++i){
        Output::parseRequest(os, tc);
    }
}
