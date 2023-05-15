#include "transport_catalogue.h"

class Stat{
public:
    void parseRequest(TransportCatalogue& tc, std::string request);
    void output(TransportCatalogue& tc, std::string request);

};
