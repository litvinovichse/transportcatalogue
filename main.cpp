#include <iostream>
#include "json.h"
#include "json_reader.h"
#include "transport_catalogue.h"

using namespace std;

int main()
{

    auto document = json::Load(std::cin);
    BusCatalogue::TransportCatalogue tc;
    json::Input::firstStep(tc, document);
    tc.fillDistance();
    processReply(std::cout,tc);

}

