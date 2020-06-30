#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "param.h"

#include <string>
#include <map>

template <class T>
class Factory
{
public:
	typedef T* (*Generator)(const Params&);

	static Factory<T>& get();

	void registerClass(const std::string& name,
				       const Generator& generator);

	T* create(const std::string name, const Params& params);

private:
	Factory() = default;
	~Factory() = default;

	std::map<std::string, Generator> _registry;
};

template <class T, class TChild>
class RegisterEntity
{
public:
	RegisterEntity(const std::string& name)
	{
		auto& f = Factory<T>::get();
		f.registerClass(
			name,
			[](const Params& params) { return static_cast<T*>(new TChild(params)); });
	}
};

template <class T> T* CreateEntity(const std::string& name, const Params& params)
{
	auto& f = Factory<T>::get();
	return f.create(name, params);
}

template <class T>
Factory<T>&
Factory<T>::get()
{
	static Factory instance;
	return instance;
}

template <class T>
void
Factory<T>::registerClass(const std::string& name,
						  const Generator& generator)
{
	_registry[name] = generator;
}

template <class T>
T*
Factory<T>::create(const std::string name, const Params& params)
{
	auto it = _registry.find(name);
	if (it != _registry.end()) {
		Generator& generator = it->second;
		return generator(params);
	}

	return nullptr;
}



#endif // _FACTORY_H_
