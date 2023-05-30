#include "request_handler.h"
#include <iostream>


/*
 * Здесь можно было бы разместить код обработчика запросов к базе, содержащего логику, которую не
 * хотелось бы помещать ни в transport_catalogue, ни в json reader.
 *
 * Если вы затрудняетесь выбрать, что можно было бы поместить в этот файл,
 * можете оставить его пустым.
 */


void processReply(BusCatalogue::TransportCatalogue &tc, Request& req)
{
    if(req.type == "Bus"){
        std::cout << "[{\"busses\"[\"" << req.name<< "\"],\"request_id\"" << std::to_string(req.id) << "}] ";
    }
    if (req.type == "Stop"){

    }
}
