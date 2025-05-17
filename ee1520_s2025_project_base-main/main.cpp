#include "Traceable_Person.h"
#include "Timed_Location.h"
#include "JvTime.h"
#include "GPS.h"
#include <iostream>
#include <vector>

int main()
{
  std::vector<Traceable_Person> people;

  // === 第一筆人物：Felix Wu ===
  Traceable_Person tp1("Felix Wu", "instructor");

  tp1.addTrace(
      Timed_Location(GPS_DD(22.996776, 120.222415), JvTime("2025-04-14T14:00:00+0000")),
      "NCKU EE 4th floor", "ended class");

  tp1.addTrace(
      Timed_Location(GPS_DD(22.997100, 120.222200), JvTime("2025-04-14T14:30:00+0000")),
      "Chang-Rong Bus Stop", "on Bus77");

  people.push_back(tp1);

  // === 第二筆人物：John ===
  Traceable_Person tp2("John", "student");

  tp2.addTrace(
      Timed_Location(GPS_DD(22.997100, 120.222200), JvTime("2025-04-14T14:30:00+0000")),
      "Chang-Rong Bus Stop", "on Bus77");

  tp2.addTrace(
      Timed_Location(GPS_DD(22.998079, 120.222168), JvTime("2025-04-14T14:45:00+0000")),
      "NCKU Hospital", "get off the Bus 77");

  people.push_back(tp2);

  // === 輸出每一筆資料 ===
  for (auto &person : people)
  {
    Json::Value *raw = person.dump2JSON();
    if (!raw)
      continue;

    Json::Value formatted(Json::objectValue);
    formatted["1.name"] = (*raw)["name"];
    formatted["2.occupation"] = (*raw)["occupation"];
    if ((*raw).isMember("status"))
      formatted["3.status"] = (*raw)["status"];
    if ((*raw).isMember("location"))
      formatted["location"] = (*raw)["location"];
    if ((*raw).isMember("GPS trace"))
      formatted["GPS trace"] = (*raw)["GPS trace"];

    delete raw;

    Json::StreamWriterBuilder builder;
    builder["indentation"] = "  ";
    std::cout << Json::writeString(builder, formatted) << std::endl;
  }

  return 0;
}

/*
int main()
{
  std::vector<Traceable_Person> people;

  // === 第一筆人物：Felix Wu ===
  Traceable_Person tp1("Felix Wu", "instructor");

  tp1.addTraceWithLabel(
      Timed_Location(GPS_DD(22.996776, 120.222415), JvTime("2025-04-14T14:00:00+0000")),
      "NCKU EE 4th floor");
  tp1.setCurrentStatus("on bus");
  tp1.addTraceWithLabel(
      Timed_Location(GPS_DD(22.997100, 120.222200), JvTime("2025-04-14T14:30:00+0000")),
      "Chang-Rong Bus Stop");
  tp1.setCurrentStatus("on bus");

  people.push_back(tp1);

  // === 第二筆人物：John ===
  Traceable_Person tp2("John", "student");

  tp2.addTraceWithLabel(
      Timed_Location(GPS_DD(22.997100, 120.222200), JvTime("2025-04-14T14:30:00+0000")),
      "Chang-Rong Bus Stop");
  tp2.setCurrentStatus("on bus");
  tp2.addTraceWithLabel(
      Timed_Location(GPS_DD(22.998079, 120.222168), JvTime("2025-04-14T14:45:00+0000")),
      "NCKU Hospital");
  tp2.setCurrentStatus("arrived");

  people.push_back(tp2);

  // === 輸出每一筆資料 ===
  for (auto &person : people)
  {
    Json::Value *raw = person.dump2JSON();
    if (!raw)
      continue;

    Json::Value formatted(Json::objectValue);
    formatted["1.name"] = (*raw)["name"];
    formatted["2.occupation"] = (*raw)["occupation"];
    if ((*raw).isMember("status"))
      formatted["3.status"] = (*raw)["status"];
    if ((*raw).isMember("location"))
      formatted["location"] = (*raw)["location"];
    if ((*raw).isMember("GPS trace"))
      formatted["GPS trace"] = (*raw)["GPS trace"];

    delete raw;

    Json::StreamWriterBuilder builder;
    builder["indentation"] = "  ";
    std::cout << Json::writeString(builder, formatted) << std::endl;
  }

  return 0;
}
*/