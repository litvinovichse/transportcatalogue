#include "request_handler.h"
#include <iostream>


/*
 * Здесь можно было бы разместить код обработчика запросов к базе, содержащего логику, которую не
 * хотелось бы помещать ни в transport_catalogue, ни в json reader.
 *
 * Если вы затрудняетесь выбрать, что можно было бы поместить в этот файл,
 * можете оставить его пустым.
 */


void processReply(std::ostream &os, BusCatalogue::TransportCatalogue &tc)
{
    std::cout << "[" ;
    for (const auto &req : tc.getRequestList()){
        if(req.type == "Bus"){
            auto data = tc.getDetailedRoute(req.name);
            if (data.correct){
                os << "{\n\"curvature\": " << data.curvature / data.length << ",\n"
                   << "\"request_id\": " << req.id << ",\n"
                   << "\"route_length\": " << data.curvature << ",\n"
                   << "\"stop_count\": " << data.stopsCount << ",\n"
                   << "\"unique_stop_count\": " << data.uniqueStopsCount << "\n  }\n";
            }

        }
        if (req.type == "Stop"){
            auto bussesOnStop = tc.getStopsForBus(req.name);
            if (bussesOnStop.empty()){
                os << "  \n{\n";
                os << "    \"request_id\": " << req.id << "\n"
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
                os <<  "    ],\n    \"request_id\": " << std::to_string(req.id) << "\n  }, \n";
            }
    }
    }
    std::cout << "]";
}
