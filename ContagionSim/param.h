#ifndef _PARAM_H_
#define _PARAM_H_

#include "log.h"

#include <map>
#include <vector>
#include <string>


class Params {
public:

	Params() {}

	~Params()
	{
		// Delete all Param objects in the map
		for (auto i : _paramMap) {
			delete i.second;
		}
	}

	template<class T>
	void set(const std::string& key, T value) {}

	template<class T>
	T get(const std::string& key, T defaultValue) const { return defaultValue; }

	bool hasKey(const std::string& key)
	{
		return _paramMap.count(key) > 0;
	}

	void getKeys(std::vector<std::string>& keys)
	{
		keys.clear();
		keys.reserve(_paramMap.size());
		
		for (auto i : _paramMap) {
			keys.push_back(i.first);
		}
	}

private:

	class Param {
	public:
		Param() = default;
		virtual ~Param() = default;
	};

	//TODO: use shared_ptr<Param> instead of Param*
	typedef std::map<std::string, Param*> ParamMap;
	ParamMap _paramMap;

	class ParamInt : public Param
	{
	public:
		ParamInt(int v) : Param(), value(v) {}
		virtual ~ParamInt() = default;
		
		int value;
	};

	class ParamFloat : public Param
	{
	public:
		ParamFloat(float v) : Param(), value(v) {}
		virtual ~ParamFloat() = default;
		
		float value;
	};

	class ParamDouble : public Param
	{
	public:
		ParamDouble(double v) : Param(), value(v) {}
		virtual ~ParamDouble() = default;
		
		double value;
	};

	class ParamString : public Param
	{
	public:
		ParamString(std::string v) : Param(), value(v) {}
		virtual ~ParamString() = default;

		std::string value;
	};

};

//*** Param Setters ***//
template<>
inline void Params::set<int>(const std::string& key, int value)
{
	_paramMap[key] = new ParamInt(value);
}

template<>
inline void Params::set<float>(const std::string& key, float value)
{
	_paramMap[key] = new ParamFloat(value);
}

template<>
inline void Params::set<double>(const std::string& key, double value)
{
	_paramMap[key] = new ParamDouble(value);
}

template<>
inline void Params::set<std::string>(const std::string& key, std::string value)
{
	_paramMap[key] = new ParamString(value);
}

//*** Param Getters ***//
template<>
inline int Params::get<int>(const std::string& key, int defaultValue) const
{
	ParamMap::const_iterator it = _paramMap.find(key);
	if (it == _paramMap.end()) {
		warn("ParamInt not found: '" + key + "', using default: " + std::to_string(defaultValue));
		return defaultValue;
	}

	Param* param = it->second;
	ParamInt* paramInt = dynamic_cast<ParamInt*>(param);
	if (paramInt == nullptr) {
		warn("Param is not a ParamInt: '" + key + "', using default: " + std::to_string(defaultValue));
		return defaultValue;
	}

	return paramInt->value;
}

template<>
inline float Params::get<float>(const std::string& key, float defaultValue) const
{
	ParamMap::const_iterator it = _paramMap.find(key);
	if (it == _paramMap.end()) {
		warn("ParamFloat not found: '" + key + "', using default: " + std::to_string(defaultValue));
		return defaultValue;
	}

	Param* param = it->second;
	ParamFloat* paramFloat = dynamic_cast<ParamFloat*>(param);
	if (paramFloat == nullptr) {
		warn("Param is not a ParamFloat: '" + key + "', using default: " + std::to_string(defaultValue));
		return defaultValue;
	}

	return paramFloat->value;
}

template<>
inline double Params::get<double>(const std::string& key, double defaultValue) const
{
	ParamMap::const_iterator it = _paramMap.find(key);
	if (it == _paramMap.end()) {
		warn("ParamDouble not found: '" + key + "', using default: " + std::to_string(defaultValue));
		return defaultValue;
	}

	Param* param = it->second;
	ParamDouble* paramDouble = dynamic_cast<ParamDouble*>(param);
	if (paramDouble == nullptr) {
		warn("Param is not a ParamDouble: '" + key + "', using default: " + std::to_string(defaultValue));
		return defaultValue;
	}

	return paramDouble->value;
}

template<>
inline std::string Params::get<std::string>(const std::string& key, std::string defaultValue) const
{
	ParamMap::const_iterator it = _paramMap.find(key);
	if (it == _paramMap.end()) {
		warn("ParamString not found: '" + key + "', using default: " + defaultValue);
		return defaultValue;
	}

	Param* param = it->second;
	ParamString* paramString = dynamic_cast<ParamString*>(param);
	if (paramString == nullptr) {
		warn("Param is not a ParamString: '" + key + "', using default: " + defaultValue);
		return defaultValue;
	}

	return paramString->value;
}

#endif // _PARAM_H_

