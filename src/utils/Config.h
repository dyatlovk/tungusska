#ifndef TUNGUSSKA_CONFIG_H
#define TUNGUSSKA_CONFIG_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

// Global config
#define CFG_LOAD( filename )

class Config
{
public:
	Config();
	~Config();

	// load config file
	void load(const char* filename);

	// find node
	void find(std::string node);

private:
	boost::property_tree::ptree tree;
};

#endif