#ifndef _PARAM_H_
#define _PARAM_H_

#include <map>
#include <string>

#include <iostream>

class Param {
public:
	Param() = default;
	virtual ~Param() = default;
};

// TODO: use shared_ptr - otherwise the user needs to delete the Param*
typedef std::map<std::string, Param*> Params;

template<class T>
T ParamGet(const Params& params, const std::string& name, T defaultValue) { return defaultValue;  }

/* Int Param */
class ParamInt : public Param
{
public:
	ParamInt(int value) : Param(), _value(value) {}
	virtual ~ParamInt() = default;

	int get() const { return _value; }

private:
	int _value;
};

template<>
inline int ParamGet<int>(const Params& params, const std::string& name, int defaultValue)
{
	Params::const_iterator it = params.find(name);
	if (it == params.end()) {
		//TODO Warning ?
		return defaultValue;
	}

	const ParamInt* p = dynamic_cast<const ParamInt*>(it->second);
	if (p != nullptr) {
		return p->get();
	}
	else {
		//TODO Warning ?
		return defaultValue;
	}
}


/* Float Param */
class ParamFloat : public Param
{
public:
	ParamFloat(float value) : Param(), _value(value) {}
	virtual ~ParamFloat() = default;

	float get() const { return _value; }

private:
	float _value;
};

template<>
inline float ParamGet<float>(const Params& params, const std::string& name, float defaultValue)
{
	Params::const_iterator it = params.find(name);
	if (it == params.end()) {
		//TODO Warning ?
		std::cout << " Naaaa 1" << std::endl;
		return defaultValue;
	}
	else {
		std::cout << " Found " << name << std::endl;
	}

	const ParamFloat* p = dynamic_cast<const ParamFloat*>(it->second);
	if (p != nullptr) {
		return p->get();
	}
	else {
		//TODO Warning ?
		std::cout << " Naaaa 2" << std::endl;
		return defaultValue;
	}
}

/* Double Param */
class ParamDouble : public Param
{
public:
	ParamDouble(double value) : Param(), _value(value) {}
	virtual ~ParamDouble() = default;

	double get() const { return _value; }

private:
	double _value;
};

template<>
inline double ParamGet<double>(const Params& params, const std::string& name, double defaultValue)
{
	Params::const_iterator it = params.find(name);
	if (it == params.end()) {
		//TODO Warning ?
		return defaultValue;
	}

	const ParamDouble* p = dynamic_cast<const ParamDouble*>(it->second);
	if (p != nullptr) {
		return p->get();
	}
	else {
		//TODO Warning ?
		return defaultValue;
	}
}

#endif // _PARAM_H_

