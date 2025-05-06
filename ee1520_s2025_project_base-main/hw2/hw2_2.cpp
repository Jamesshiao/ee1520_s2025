#include <iostream>
#include <string>
#include <vector>
#include "../Traceable_Person.h"
#include "../Locatable_Thing.h"
#include "../Labeled_GPS.h"
#include "../Timed_Location.h"
#include "../JvTime.h"

int main() {
  // Create locations
  Labeled_GPS ee_building(1.0, -1.0, "NCKU EE 4th floor");
  Labeled_GPS chang_rong(1.0, -1.0, "Chang-Rong Bus Stop");
  Labeled_GPS hospital(1.0, -1.0, "NCKU Hospital");
  Labeled_GPS moore_pollock(1.0, -1.0, "Moore and Pollock bus stop");

  // Create timestamps
  JvTime t1("2025-04-14T14:00:00+0000");
  JvTime t2("2025-04-14T14:30:00+0000");
  JvTime t3("2025-04-14T14:45:00+0000");
  JvTime t4("2025-04-14T15:15:00+0000");

  // Create people
  Traceable_Person instructor("I001", "Felix Wu");
  Traceable_Person student("S001", "John");

  // Add GPS traces directly to GPS_trace vector
  instructor.GPS_trace.traces.push_back(Timed_Location(ee_building, t1));
  instructor.GPS_trace.traces.push_back(Timed_Location(chang_rong, t2));
  instructor.GPS_trace.traces.push_back(Timed_Location(hospital, t3));
  instructor.GPS_trace.traces.push_back(Timed_Location(moore_pollock, t4));

  student.GPS_trace.traces.push_back(Timed_Location(ee_building, t1));
  student.GPS_trace.traces.push_back(Timed_Location(chang_rong, t2));
  student.GPS_trace.traces.push_back(Timed_Location(hospital, t3));

  // Devices (只給定位點，不支援 owner，因此只用 GPS_DD)
  Locatable_Thing computer(hospital);
  Locatable_Thing phone(moore_pollock);

  // JSON 輸出
  Json::Value* jv_instructor = instructor.GPS_trace.dump2JSON();
  Json::Value* jv_student = student.GPS_trace.dump2JSON();
  Json::Value* jv_phone = phone.dump2JSON();

  if (jv_instructor != NULL) {
    std::cout << "INSTRUCTOR:\n" << jv_instructor->toStyledString() << std::endl;
    delete jv_instructor;
  }

  if (jv_student != NULL) {
    std::cout << "STUDENT:\n" << jv_student->toStyledString() << std::endl;
    delete jv_student;
  }

  if (jv_phone != NULL) {
    std::cout << "PHONE:\n" << jv_phone->toStyledString() << std::endl;
    delete jv_phone;
  }

  return 0;
}
