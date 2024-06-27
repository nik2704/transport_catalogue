#include <iostream>
#include <string>
#include <string_view>
#include "stat_reader.h"


void ParseAndPrintStat(const TransportCatalogue& tansport_catalogue, std::string_view request,
                       std::ostream& output) {
    // Реализуйте самостоятельно
    std::string_view bus_prefix = "Bus ";
    if (request.substr(0, bus_prefix.size()) != bus_prefix) {
        output << "Invalid request" << std::endl;
        return;
    }

    std::string bus_name = std::string(request.substr(bus_prefix.size()));

    BusInfo bus_info = tansport_catalogue.GetRouteInfo(bus_name);

    if (bus_info.bus_name_.empty()) {
        output << "Bus " << bus_name << ": not found" << std::endl;
        return;
    }

    output << "Bus " << bus_info.bus_name_ << ": "
           << bus_info.stops_count_ << " stops on route, "
           << bus_info.unique_stops_ << " unique stops, "
           << bus_info.meters_route_length_ << " route length" << std::endl;    
}