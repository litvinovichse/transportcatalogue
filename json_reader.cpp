#include "json_reader.h"
#include "json.h"
namespace json {
namespace Input {



void firstStep(BusCatalogue::TransportCatalogue &tc, json::Document& requestArray)
{
    auto nDocument = requestArray.GetRoot(); // map
    if (nDocument.AsMap().count("base_requests")){
        auto a = nDocument.AsMap().at("base_requests"); //arr
        for (const auto& b : a.AsArray()){
            if (b.IsMap()){
                if (b.AsMap().at("type").AsString() == "Bus"){
                    std::vector<std::string> stopsLocal;
                    std::string number = b.AsMap().at("name").AsString();
                    for (const auto &c : b.AsMap().at("stops").AsArray()) {
                        stopsLocal.push_back(c.AsString());
                    }
                    bool circle = b.AsMap().at("is_roundtrip").AsBool();
                    tc.addBusToBase(number, stopsLocal, circle);
                } else if (b.AsMap().at("type").AsString() == "Stop"){
                    std::map<std::string, int> ret;
                    std::string stopName = b.AsMap().at("name").AsString();
                    double alt = b.AsMap().at("latitude").AsDouble();
                    double longt = b.AsMap().at("longitude").AsDouble();
                    for (const auto &c : b.AsMap().at("road_distances").AsMap()) {
                        ret[c.first] = c.second.AsInt();
                    }
                    tc.addStop(stopName,alt,longt,ret);
                }
            }
        }
    }


    if (nDocument.AsMap().count("stat_requests")){
        BusData::Request req;
        auto a = nDocument.AsMap().at("stat_requests");
        for (const auto& b : a.AsArray()){
            if (b.IsMap()){
                req.id = b.AsMap().at("id").AsInt();
                req.type = b.AsMap().at("type").AsString();
                req.name = b.AsMap().at("name").AsString();
                tc.addRequestToList({req.id, req.type, req.name});
                // std::cout << b.AsMap().at("id").AsInt() << "\n" << b.AsMap().at("type").AsString();
            }
        }
    }





}
}//namespace Input
}//namespace json







