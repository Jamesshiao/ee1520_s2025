#include "Traceable_Bus.h"

Traceable_Bus::Traceable_Bus() : bus_name("unknown") {}

Traceable_Bus::Traceable_Bus(const std::string &name) : bus_name(name) {}

Traceable_Bus::~Traceable_Bus() {}

void Traceable_Bus::addPassenger(Traceable_Person *person)
{
    passengers.push_back(person);
}

std::string Traceable_Bus::get_name() const
{
    return bus_name;
}

Json::Value *Traceable_Bus::dump2JSON()
{
    Json::Value *result_ptr = new Json::Value(Json::objectValue);
    (*result_ptr)["bus_name"] = this->bus_name;

    Json::Value passenger_array(Json::arrayValue);
    for (size_t i = 0; i < passengers.size(); ++i)
    {
        Json::Value *person_json = passengers[i]->dump2JSON();
        if (person_json != nullptr)
        {
            passenger_array.append(*person_json);
            delete person_json;
        }
    }
    (*result_ptr)["passengers"] = passenger_array;

    return result_ptr;
}
