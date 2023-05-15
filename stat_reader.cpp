#include "stat_reader.h"

void Stat::parseRequest(TransportCatalogue &tc, std::string request)
{
    request = request.substr(request.find_first_of(' ') + 1);
    output(tc, request);
}

void Stat::output(TransportCatalogue &tc, std::string request)
{

}
