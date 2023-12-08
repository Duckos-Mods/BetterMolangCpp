#pragma once
#include "../Tokens/Token.h"
#include <map>
#include <vector>
#include "../Error/Errors.h"
#include <typeinfo>

#define GET_TYPE_NAME(type) typeid(type).name()


template <typename RegisteryType>
class ObjectRegistery
{
private:
	std::map<std::string, RegisteryType> m_Objects;
public:
	ObjectRegistery() {};

	inline void RegisterObject(const std::string& name, const RegisteryType& reg)
	{
		if (ObjectExists(name)) {
			Errors::Error("Object %s already exists!", name.c_str());
		}
		Errors::Info("Registering object %s, Of Type %s", name.c_str(), GET_TYPE_NAME(reg));
		m_Objects[name] = reg;
	}
	inline bool ObjectExists(const std::string& name)
	{
		return m_Objects.find(name) != m_Objects.end();
	}
	inline RegisteryType& GetObject(const std::string& name)
	{
		if (!ObjectExists(name)) {
			Errors::Error("Object %s does not exist!", name.c_str());
		}
		return m_Objects[name];
	}
};

