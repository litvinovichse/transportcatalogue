// напишите решение с нуля
// код сохраните в свой git-репозиторий

#include "stat_reader.h"
#include <iostream>

void Recorder::recordNewDataIntoBase(TransportCatalogue &tc)
{
    std::string line;
    std::getline(std::cin, line);
    std::string command = line.substr(0, line.find(' '));
    if (command == "Bus"){
        newBus(tc, line.substr(line.find(' ') + 1));
    } else if (command == "Stop"){
        newStop(tc, line.substr(line.find(' ') + 1));
    } else {
        return;
    }

}

void Recorder::newBus(TransportCatalogue& tc, std::string busData)
{
    std::string number = busData.substr(0, busData.find(':'));
    std::cout << number;
    busData = busData.substr(busData.find(':') + 2);
    if(busData.find('>') != std::string::npos){
        // std::vector<Stops> route
    } else {

    }

}

void Recorder::newStop(TransportCatalogue &tc, std::string stopData)
{
    std::string stopName = stopData.substr(0,stopData.find(':'));
    stopData = stopData.substr(stopData.find(':') + 2);
    double alt = std::stod(stopData.substr(0, stopData.find(',')));
    stopData = stopData.substr(stopData.find(',') + 2);
    if (stopData.find(' ') != std::string::npos){
        stopData.substr(0, stopData.find(' '));
    }
    double longt = std::stod(stopData);
    std::cout << "name:" << stopName << "alt:" << alt << "long:" << longt << "!" << std::endl;
    tc.addStop(stopName, alt, longt);
}
