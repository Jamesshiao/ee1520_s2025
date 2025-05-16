
#include "Traceable_Person.h"

Traceable_Person::Traceable_Person(std::string name, std::string occupation)
  : Person("", name)  // 給空的 vsID，或你要的預設值
{
  this->class_name = "Traceable_Person";
  this->occupation = occupation;
  this->home = nullptr;  // 若需要可事後用 setHome 設定
}


Traceable_Person::Traceable_Person(std::string name, std::string occupation, GPS_DD *home_ptr)
  : Person("", name, home_ptr)
{
  this->class_name = "Traceable_Person";
  this->occupation = occupation;
}


Traceable_Person::~Traceable_Person() {} 


void Traceable_Person::addTraceWithLabel(const Timed_Location & tl, const std::string& label) {
  this->GPS_trace.traces.push_back(tl);
  this->trace_labels.push_back(label);
}


Json::Value * Traceable_Person::dump2JSON() {
  
  Json::Value *result_ptr = new Json::Value(Json::objectValue);
  
  if (this->home != nullptr) {
    Json::Value *home_json = this->home->dump2JSON();
    if (home_json != nullptr) {
      (*result_ptr)["location"] = *home_json;
      delete home_json;
    }
  }

  if (!this->GPS_trace.traces.empty()) {
    Json::Value trace_array(Json::arrayValue);
    for (size_t i = 0; i < this->GPS_trace.traces.size(); ++i) {
      Json::Value *jv = this->GPS_trace.traces[i].dump2JSON();
      if (jv != nullptr) {
        if (i < this->trace_labels.size()) {
          (*jv)["label"] = this->trace_labels[i];
        }
        trace_array.append(*jv);
        delete jv;
      }
    }
    (*result_ptr)["GPS trace"] = trace_array;
  }


  (*result_ptr)["name"] = this->name;
  (*result_ptr)["occupation"] = this->occupation;


  return result_ptr;
}
 











