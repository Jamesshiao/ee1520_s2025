#include "Traceable_Person.h"
#include "Timed_Location.h"
#include "JvTime.h"
#include "GPS.h"
#include <iostream>
#include <vector>



int main() {
  std::vector<Traceable_Person> people;

  // === 第一筆人物：Felix Wu ===
  Traceable_Person tp1("Felix Wu", "instructor");

  // 1. EE lecture 結束地點
  tp1.addTraceWithLabel(
    Timed_Location(GPS_DD(22.996776, 120.222415), JvTime("2025-04-14T14:00:00+0000")),
    "NCKU EE 4th floor"
  );

  // 2. 上車地點：Chang-Rong Station
  tp1.addTraceWithLabel(
    Timed_Location(GPS_DD(22.997100, 120.222200), JvTime("2025-04-14T14:30:00+0000")),
    "Chang-Rong Bus Stop"
  );

  people.push_back(tp1);

  // === 第二筆人物：John ===
  Traceable_Person tp2("John", "student");

  // 1. 上車地點與 Felix 一樣（不重複寫）
  tp2.addTraceWithLabel(
    Timed_Location(GPS_DD(22.997100, 120.222200), JvTime("2025-04-14T14:30:00+0000")),
    "Chang-Rong Bus Stop"
  );

  // 2. 下車地點：NCKU Hospital
  tp2.addTraceWithLabel(
    Timed_Location(GPS_DD(22.998079, 120.222168), JvTime("2025-04-14T14:45:00+0000")),
    "NCKU Hospital"
  );

  people.push_back(tp2);

  // === 輸出每一筆資料 ===
  for (auto& person : people) {
    Json::Value* raw = person.dump2JSON();
    if (!raw) continue;

    Json::Value formatted(Json::objectValue);
    formatted["1.name"] = (*raw)["name"];
    formatted["2.occupation"] = (*raw)["occupation"];
    if ((*raw).isMember("location")) formatted["location"] = (*raw)["location"];
    if ((*raw).isMember("GPS trace")) formatted["GPS trace"] = (*raw)["GPS trace"];
    delete raw;

    Json::StreamWriterBuilder builder;
    builder["indentation"] = "  ";
    std::cout << Json::writeString(builder, formatted) << std::endl;
  }

  return 0;
}




/*
int main() {
  std::vector<Traceable_Person> people;

  // === 第一筆人物 ===
  Traceable_Person tp1("Felix Wu", "instructor");
  tp1.addTraceWithLabel(
    Timed_Location(GPS_DD(22.996776, 120.222415), JvTime("2025-04-14T14:00:00+0000")),"NCKU EE 4th floor");
  people.push_back(tp1);

  // === 第二筆人物 ===
  Traceable_Person tp2("John", "student");
  tp2.addTraceWithLabel(
    Timed_Location(GPS_DD(22.998079, 120.222168), JvTime("2025-04-14T14:45:00+0000")),"NCKU Hospital");
  people.push_back(tp2);

  // === 輸出每一筆資料 ===
  for (auto& person : people) {
    Json::Value* raw = person.dump2JSON();
    if (!raw) continue;

    Json::Value formatted(Json::objectValue);
    formatted["1.name"] = (*raw)["name"];
    formatted["2.occupation"] = (*raw)["occupation"];
    if ((*raw).isMember("location")) formatted["location"] = (*raw)["location"];
    if ((*raw).isMember("GPS trace")) formatted["GPS trace"] = (*raw)["GPS trace"];
    delete raw;

    Json::StreamWriterBuilder builder;
    builder["indentation"] = "  ";
    std::cout << Json::writeString(builder, formatted) << std::endl;
  }

  return 0;
}


*/

/*

int main() {
  // 建立人物 Felix Wu，職業 instructor
  Traceable_Person tp("Felix Wu", "instructor");

  // 加入一筆 GPS trace 與對應的 label
  tp.addTraceWithLabel(
    Timed_Location(GPS_DD(22.996776239105127, 120.2224149947794), JvTime("2025-04-14T14:00:00+0000")),
    "NCKU EE 4th floor"
  );

  // 輸出 JSON
  Json::Value* jv = tp.dump2JSON();
  if (jv != nullptr) {
    std::cout << *jv << std::endl;
    delete jv;
  }

  return 0;
}
*/