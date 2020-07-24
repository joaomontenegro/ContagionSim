#ifndef _PARAM_FILE_H_
#define _PARAM_FILE_H_

#include "param.h"
#include "log.h"

#include <string>
#include <fstream>
#include <sstream>

bool LOG = false;

bool ReadParam(const std::string& filepath, Params* outParams)
{
	std::ifstream file(filepath);
	
	if (!file.is_open()) {
		Log::error("Could not open Param File: " + filepath);
		return false;
	}

	int lineNum = 0;
	std::string line;
	while (std::getline(file, line)) {
		lineNum++;

		if (line.empty() || line.front() == '#') {
			continue;
		}

		std::string type;
		std::string key;
		std::string value;
		std::stringstream ss(line);
		ss >> type >> key >> value;

		if (ss.fail()) {
			Log::error("Param File: " + filepath + " (line " + std::to_string(lineNum) + ")");
			//return false;
		}

		if (type == "int") {
			int intValue = std::stoi(value.c_str());
			outParams->set<int>(key, intValue);

			Log::debug("Param: i " + key + " : " + std::to_string(intValue));
		} else if (type == "float") {
			float floatValue = std::stof(value.c_str());
			outParams->set<float>(key, floatValue);
			Log::debug("Param: f " + key + " : " + std::to_string(floatValue));
		
		} else if (type == "double") {
			double doubleValue = std::stod(value.c_str());
			outParams->set<double>(key, doubleValue);
			Log::debug("Param: d " + key + " : " + std::to_string(doubleValue));
		
		} else if (type == "string") {
			if (!value.empty()) {
				if (value.front() == '"') {
					value.erase(0, 1);
				}

				if (value.back() == '"') {
					value.erase(value.size() - 1, 1);
				}
			}
			outParams->set<std::string>(key, value);

			Log::debug("Param: s " + key + " : " + value);
		}
	}
	
	file.close();
	return true;
}

#endif
