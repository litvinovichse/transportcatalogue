#include "request_handler.h"
#include "transport_catalogue.h"
#include "json_reader.h"
#include "domain.h"
#include "json_reader.h"
#include "json.h"

using namespace std;
using namespace BusCatalogue;
using namespace BusData;
using namespace geo;
using namespace json;


int main() {

    Request req;
    TransportCatalogue tc;
    Document document = json::Load(std::cin);
    json::Input::firstStep(tc,document,req);
    tc.fillDistance();

}
