#include "AppSub.hpp"

map<string, FUNCTION> _collector;

int register_algorithm(string name, FUNCTION func) {

	_collector.insert (make_pair(name, func));

	return (int)_collector.size();
}

FUNCTION get_algorithm(string name) {

	map<string, FUNCTION>::iterator it;
	it = _collector.find(name);

	if (it != _collector.end())
		return it->second;
	else
		return NULL;
}