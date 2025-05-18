#include <iostream>
#include "Traceable_Person.h"
#include "Traceable_Bus.h"
#include "Timed_Location.h"
#include "JvTime.h"

int main()
{
    // === 創建人物 ===
    Traceable_Person FelixWu("Felix Wu", "instructor");
    Traceable_Person John("John", "student");

    // === 建立 GPS + 時間（正確格式）===
    Timed_Location t1(GPS_DD(22.996776, 120.222415), JvTime("2025-04-14T14:00:00+0000")); // NCKU EE
    Timed_Location t2(GPS_DD(22.997100, 120.222200), JvTime("2025-04-14T14:30:00+0000")); // 昌榮站
    Timed_Location t3(GPS_DD(22.998079, 120.222168), JvTime("2025-04-14T14:45:00+0000")); // 醫院站
    Timed_Location t4(GPS_DD(22.990000, 120.215000), JvTime("2025-04-14T15:15:00+0000")); // Moore & Pollock

    // === 添加 GPS trace ===
    FelixWu.addTrace(t1, "NCKU EE 4th floor", "ended class");
    FelixWu.addTrace(t2, "Chang-Rong Bus Stop", "on Bus77");
    FelixWu.addTrace(t4, "Moore and Pollock", "got off Bus77");

    John.addTrace(t2, "Chang-Rong Bus Stop", "on Bus77");
    John.addTrace(t3, "NCKU Hospital", "get off the Bus 77");

    // === 建立 Bus 並加入乘客 ===
    Traceable_Bus bus77("Bus 77");
    bus77.addPassenger(&FelixWu);
    bus77.addPassenger(&John);

    // === 輸出 JSON ===
    Json::Value *bus_json = bus77.dump2JSON();
    std::cout << *bus_json << std::endl;
    delete bus_json;

    return 0;
}
