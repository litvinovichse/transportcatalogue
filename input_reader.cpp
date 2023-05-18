// напишите решение с нуля
// код сохраните в свой git-репозиторий

#include "input_reader.h"
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
    busData = busData.substr(busData.find(':') + 2);
    if(busData.find('>') != std::string::npos){
        std::vector<std::string> stopsLocal;
        std::size_t pos = busData.find('>');
        while (pos != std::string::npos) {
            stopsLocal.push_back(busData.substr(0, pos - 1));
            busData = busData.substr(pos + 2);
            pos = busData.find('>');
        }
        stopsLocal.push_back(busData);

        tc.addBusToBase(number, stopsLocal, true);

    } else if (busData.find('-') != std::string::npos){
        std::vector<std::string> stopsLocal;
        std::size_t pos = busData.find('-');
        while (pos != std::string::npos) {
            stopsLocal.push_back(busData.substr(0, pos - 1));
            busData = busData.substr(pos + 2);
            pos = busData.find('-');
        }
        stopsLocal.push_back(busData);
        tc.addBusToBase(number, stopsLocal, false);
    }
}

void Recorder::newStop(TransportCatalogue &tc, std::string stopData)
{
    std::string test;
    std::map<std::string, int> ret;
    std::string stopName = stopData.substr(0,stopData.find(':'));
    stopData = stopData.substr(stopData.find(':') + 2);
    double alt = std::stod(stopData.substr(0, stopData.find(',')));
    stopData = stopData.substr(stopData.find(',') + 2);
    double longt = 0.0;
    if (stopData.find(',') == std::string::npos){
        longt = std::stod(stopData);
        tc.addStop(stopName,alt,longt,ret);
        return;
    } else {
        longt = std::stod(stopData.substr(0, stopData.find(',')));
        stopData = stopData.substr(stopData.find(',') + 2);
    }
    int dist{0};
    std::string nbName;
    while(stopData.find(',') != std::string::npos){
        dist = std::stoi(stopData.substr(stopData.find_first_not_of(' '), stopData.find('m')));
        stopData = stopData.substr(stopData.find('m') + 5);
        nbName = stopData.substr(0, stopData.find(','));
        stopData = stopData.substr(stopData.find(',') + 1);
        ret[nbName] = dist;
    }
    dist = std::stoi(stopData.substr(0, stopData.find('m')));
    stopData = stopData.substr(stopData.find('m') + 5);
    nbName = stopData;
    ret[nbName] = dist;

    tc.addStop(stopName,alt,longt, ret);
}
