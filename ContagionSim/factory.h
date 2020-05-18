#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <string>
#include <map>

template <class T>
class Factory
{
public:
	typedef T* (*Generator)();

	static Factory<T>& get();

	void registerClass(const std::string& name,
				       const Generator& generator);

	T* create(std::string name);

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
			[]() { return static_cast<T*>(new TChild()); });
	}
};

template <class T> T* CreateEntity(const std::string& name)
{
	auto& f = Factory<T>::get();
	return f.create(name);
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
Factory<T>::create(std::string name)
{
	auto it = _registry.find(name);
	if (it != _registry.end()) {
		Generator& generator = it->second;
		return generator();
	}

	return nullptr;
}



#endif // _FACTORY_H_
