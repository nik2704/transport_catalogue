#pragma once

#include <deque>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>

#include "geo.h"

struct Stop {
public:
	std::string name;
	Coordinates coordinates;
	std::set<std::string> buses_;
};

struct Bus {
	std::string bus_name;
	std::vector<const Stop*> stops;
	bool is_circle;
};

struct BusInfo {
	std::string bus_name_;
	int stops_count_;
	int unique_stops_;
	double meters_route_length_;
};

class TransportCatalogue {
public:
    TransportCatalogue();

	// добавление маршрута в базу,
	void AddRoute(std::string_view bus_name, std::vector<const Stop *> stops, bool is_circle);

	// добавление остановки в базу,
	void AddStop(std::string_view stop_name, Coordinates coordinates);

	// поиск маршрута по имени,
    const Bus* GetRoute(std::string_view bus_name);

	// поиск остановки по имени,
	const Stop* GetStop(std::string_view stop_name);
	
	// получение информации о маршруте.
	BusInfo GetRouteInfo(const std::string_view name) const;

private:
	std::deque<Stop> all_stops_;
	std::unordered_map<std::string_view, const Stop*> stopname_to_stop_;
	std::deque<Bus> all_buses_;
	std::unordered_map<std::string_view, const Bus*> busename_to_bus_;
};
