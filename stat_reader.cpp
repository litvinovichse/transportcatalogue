#include "stat_reader.h"
#include <iostream>

void Stat::parseRequest(TransportCatalogue &tc)
{
    std::string line;
    std::getline(std::cin, line);
    line = line.substr(line.find_first_of(' ') + 1);
    output(tc, line);
}

void Stat::output(TransportCatalogue &tc, std::string request)
{
    auto detail = tc.getDetailedRoute(request);
    if (!detail.correct){
        std::cout << "Bus " << request << ": not found" << std::endl;
        return;
    }
    std::cout << "Bus " << request <<": " << detail.stopsCount << " stops on route, " << detail.uniqueStopsCount << " unique stops, " << detail.length <<" route length" << std::endl;;
}
