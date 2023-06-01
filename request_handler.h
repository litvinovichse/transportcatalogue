#pragma once

#include "transport_catalogue.h"
#include <string>

struct Request{
    int id{0};
    std::string type;
    std::string name;
};

void processReply(std::ostream &os, BusCatalogue::TransportCatalogue& tc);

