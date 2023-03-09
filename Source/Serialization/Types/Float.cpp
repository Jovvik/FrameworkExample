#include "../Serializer.hpp"

#include <algorithm>

#include "xorstr.hpp"

void Serialization::Serializer::Serialize(const char* name, float& type, Direction direction)
{
	switch (direction) {
	case SERIALIZE:
		GetValue(name) = std::to_string(type);
		break;
	case DESERIALIZE:
		std::string string = GetValue(name);
		if (!string.empty())
			type = std::stof(string);
		break;
	}
}