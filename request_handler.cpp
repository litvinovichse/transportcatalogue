#include "request_handler.h"
#include <iostream>

void processReply(std::ostream &os, BusCatalogue::TransportCatalogue &tc)
{
    bool firstReq = true;
    std::cout << "[" ;
    for (const auto &req : tc.getRequestList()){
        if (!firstReq){
            os << ",\n";
        }
        if(req.type == "Bus"){
            busProcess(tc, req, os);
        }
        if (req.type == "Stop"){
            stopProcess(tc,req, os);
        }
        firstReq = false;
    }
    std::cout << "]";
}

void busProcess(BusCatalogue::TransportCatalogue &tc, const BusData::Request& req, std::ostream &os)
{
    auto data = tc.getDetailedRoute(req.name);
    if (data.correct){
        os << "{\n\"curvature\": " << data.curvature / data.length << ",\n"
           << "\"request_id\": " << req.id << ",\n"
           << "\"route_length\": " << data.curvature << ",\n"
           << "\"stop_count\": " << data.stopsCount << ",\n"
           << "\"unique_stop_count\": " << data.uniqueStopsCount << "\n  }\n";
    } else {
        std::cout << "{\n \"request_id\": " << req.id << ",\n" << "\"error_message\": \"not found\" \n}\n";
    }
}

void stopProcess(BusCatalogue::TransportCatalogue &tc, const BusData::Request& req,std::ostream &os )
{
    auto bussesOnStop = tc.getStopsForBus(req.name);
    if (bussesOnStop.empty() && tc.searchStops(req.name) == nullptr){
        os << "  \n{\n";
        os << "    \"request_id\": " << req.id << ",\n"
           <<"    \"error_message\": \"not found\" \n  }";
    } else {
        os << "  {\n    \"buses\": [\n";
        bool firstLine = true;
        for(const auto &bus : bussesOnStop){
            if (firstLine){
                os << "      \"" << bus << "\"\n";
                firstLine = false;
            } else {
                os << ",\n";
                os << "      \"" << bus << "\"\n";
            }
        }
        os <<  "    ],\n    \"request_id\": " << std::to_string(req.id) << "\n  } \n";
    }
}
