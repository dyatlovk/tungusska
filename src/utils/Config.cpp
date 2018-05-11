#include "Config.h"

Config::Config(){};

Config::~Config(){};

void Config::load(const char* filename)
{
	boost::property_tree::ini_parser::read_ini(filename, tree);
}

void Config::find(std::string node)
{
	tree.get<std::string>(node);
}