#include "transport_catalogue.h"
#include "json_reader.h"
#include "domain.h"
#include "map_renderer.h"
#include "request_handler.h"
#include "json_reader.h"
#include "json.h"

using namespace std;
using namespace BusCatalogue;
using namespace BusData;
using namespace geo;
using namespace json;


int main() {

    std::vector<StatRequest> stat_request;
    map_renderer::RenderSettings render_settings;
    TransportCatalogue catalogue;
    Document doc_in;

    doc_in = json::Load(std::cin);
    json::parse(doc_in, catalogue, stat_request, render_settings);

    map_renderer::MapRenderer map_render(render_settings);

    request_handler::RequestHandler request_handler(catalogue, map_render);
    request_handler.render_map(std::cout);
}
