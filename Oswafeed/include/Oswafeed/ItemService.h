#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <ios>


#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"

class Item;

class ItemService
{
	std::vector<std::unique_ptr<Item>> items;
	bool hasUpdate = false;
	bool isUpdating = false;
	std::string apiURl = "http://statsapi.mlb.com/api/v1/schedule/games/?hydrate=game%28content%28editorial%28recap%29%29%29,decisions&sportId=1&date=";
	std::string date = "2020-09-01";

	std::vector<std::unique_ptr<Item>> requestItems(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);
	std::unique_ptr<std::istream> requestImage(const std::string& url);
public:
	ItemService();
	std::vector<std::unique_ptr<Item>>& getItems();
	void update();
	bool isUpdated();
};