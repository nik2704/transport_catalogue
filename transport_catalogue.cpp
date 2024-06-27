#include "geo.h"
#include "transport_catalogue.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>

TransportCatalogue::TransportCatalogue() {}

void TransportCatalogue::AddRoute(std::string_view bus_name, std::vector<const Stop *> stops, bool is_circle) {
    Bus bus = { std::string(bus_name), stops, is_circle };

    all_buses_.push_back(bus);
    busename_to_bus_[all_buses_.back().bus_name] = &all_buses_.back();
}

void TransportCatalogue::AddStop(std::string_view stop_name, Coordinates coordinates) {
    Stop stop = { std::string(stop_name), coordinates };

    all_stops_.push_back(std::move(stop));
    stopname_to_stop_[all_stops_.back().name] = &all_stops_.back();
}

const Bus* TransportCatalogue::GetRoute(std::string_view bus_name) {
    return busename_to_bus_.count(bus_name) == 0 ? nullptr : busename_to_bus_.at(bus_name);
}

const Stop* TransportCatalogue::GetStop(std::string_view stop_name) {
    return busename_to_bus_.count(stop_name) == 0 ? nullptr : stopname_to_stop_.at(stop_name);
}

BusInfo TransportCatalogue::GetRouteInfo(const std::string_view bus_name) const {
    BusInfo bus_info;

    if (busename_to_bus_.count(bus_name)) {
        auto& bus = busename_to_bus_.at(bus_name);

        bus_info.bus_name_ = bus->bus_name;
        bus_info.stops_count_ = static_cast<int>(bus->stops.size());

        std::set<std::string> uniqueNames;

        for (const auto& stop : bus->stops) {
            std::cout << (*stop).name << "  ";
            // uniqueNames.insert(stop->name);
        }

        // The number of unique names
        
        bus_info.unique_stops_ = 0;
        bus_info.meters_route_length_ = 0.0;

        if (bus_info.stops_count_ > 1) {
            for (int i = 0; i < bus_info.stops_count_ - 1; ++i) {
                // bus_info.meters_route_length_ += ComputeDistance(bus->stops[i]->coordinates, bus->stops[i + 1]->coordinates); 
            }
        }

        return bus_info;
    }
    
    return bus_info;
}
