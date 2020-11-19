#include "Oswafeed/ItemService.h"
#include "Oswafeed/Item.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/ConsoleCertificateHandler.h"

ItemService::ItemService()
{
	//Poco::Net::SSLManager::instance().defaultClientContext();
	Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pCert = new Poco::Net::ConsoleCertificateHandler(false);
	Poco::Net::Context::Ptr pContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "rootcert.pem");

	Poco::Net::SSLManager::instance().initializeClient(0, pCert, pContext);
}

std::vector<std::unique_ptr<Item>> ItemService::requestItems(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response)
{
	session.sendRequest(request);
	std::istream& rs = session.receiveResponse(response);
	Parser parser;
	auto data = parser.parse(rs);
	Object::Ptr json = data.extract<Object::Ptr>();
	std::vector<std::unique_ptr<Item>> newItems;
	if (!json->has("dates"))
	{
		std::cout << "Missing dates\n";
		return std::move(newItems);
	}
	auto dates = json->getArray("dates");
	if (dates->size() <= 0)
	{
		std::cout << "No dates\n";
		return std::move(newItems);
	}
	auto date = dates->getObject(0);
	
	if (!date->has("games"))
	{
		std::cout << "Missing games\n";
		return std::move(newItems);
	}
	auto games = date->getArray("games");
	for (int i = 0; i < games->size(); i++)
	{
		auto game = games->getObject(i);
		auto home = game->getObject("teams")->getObject("home")->getObject("team")->get("name");
		auto away = game->getObject("teams")->getObject("away")->getObject("team")->get("name");
		auto title = home.toString() + " vs " + away.toString();
		if (!game->has("content"))
		{
			std::cout << "No content\n";
			continue;
		}
		auto content = game->getObject("content");
		if (!content->has("editorial"))
		{
			std::cout << "No editorial\n";
			continue;
		}
		auto editorial = content->getObject("editorial");

		if (!editorial->has("recap"))
		{
			std::cout << "No recap\n";
			continue;
		}
		auto recap = editorial->getObject("recap");
		
		if (!recap->has("mlb"))
		{
			std::cout << "No mlb\n";
			continue;
		}
		auto mlb = recap->getObject("mlb");
		if(!mlb->has("headline") || !mlb->has("seoTitle"))
		{
			std::cout << "No headline or seoTitle\n";
			continue;
		}
		auto description = mlb->get("headline").toString();

		if (!mlb->has("image"))
		{
			std::cout << "No images\n";
			continue;
		}
		auto image = mlb->getObject("image");
		if (!image->has("cuts"))
		{
			std::cout << "No cuts\n";
		}

		auto cuts = image->getArray("cuts");
		if (cuts->size() < 4)
		{
			std::cout << "Incorrect cut size\n";
		}
		auto cut = cuts->getObject(3);

		if (!cut->has("src"))
		{
			std::cout << "Missing source\n";
		}
		auto imageSrc = cut->get("src").toString();
		auto requestedImage = requestImage(imageSrc);
		if (!requestedImage)
		{
			return std::move(newItems);
		}
		std::vector<unsigned char> data(std::istreambuf_iterator<char>(*requestedImage), {});
		newItems.push_back(std::make_unique<Item>(title, description, data));
	}

	return std::move(newItems);
}

std::unique_ptr<std::istream> ItemService::requestImage(const std::string& url)
{
	try
	{
		URI uri(url);
		HTTPSStreamFactory factory;
		auto stream = std::unique_ptr<std::istream>(factory.open(uri));
		return std::move(stream);
	}
	catch (Exception& exc)
	{
		std::cout << "Exception: " << exc.displayText() << std::endl;
	}
	
	return nullptr;
}

void ItemService::update()
{
	if (isUpdating)
	{
		return;
	}

	isUpdating = true;
	try
	{
		URI uri(apiURl + date);
		std::string path(uri.getPathAndQuery());

		HTTPClientSession session(uri.getHost(), uri.getPort());
		HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		HTTPResponse response;
		items = requestItems(session, request, response);
	}
	catch (Exception& exc)
	{
		std::cout << "Exception: " << exc.displayText() << std::endl;
	}

	// Run the logic to get JSON
	hasUpdate = true;
}

bool ItemService::isUpdated()
{
	return hasUpdate;
}

std::vector<std::unique_ptr<Item>>& ItemService::getItems()
{
	return items;
}

