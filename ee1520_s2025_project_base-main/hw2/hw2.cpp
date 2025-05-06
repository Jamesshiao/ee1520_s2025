#include <iostream>
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>



// 時間與地點
class Time_Location {
public:
    std::string time;
    double latitude;
    double longitude;
    std::string label;

    Time_Location(std::string t, double lat, double lon, std::string lab)
        : time(t), latitude(lat), longitude(lon), label(lab) {}

    Json::Value dump2JSON() const {
        Json::Value result;
        result["time"] = time;
        result["location"]["latitude"] = latitude;
        result["location"]["longitude"] = longitude;
        result["location"]["label"] = label;
        return result;
    }
};

// 人物
class Person {
protected:
    std::string name;
    std::string occupation;
    std::vector<Time_Location> gps_trace;

public:
    Person(std::string n, std::string o = "unknown") : name(n), occupation(o) {}

    void addLocation(const Time_Location& loc) {
        gps_trace.push_back(loc);
    }

    std::string getName() const { return name; }

    virtual Json::Value dump2JSON() const {
        Json::Value result;
        result["name"] = name;
        result["occupation"] = occupation;
        for (const auto& loc : gps_trace) {
            result["GPS trace"].append(loc.dump2JSON());
        }
        return result;
    }

    virtual ~Person() {}
};

// 裝置
class Device {
    std::string model;
    std::string id;
    Time_Location location;
    Person* owner;

public:
    Device(std::string m, std::string i, Time_Location loc, Person* p)
        : model(m), id(i), location(loc), owner(p) {}

    Json::Value dump2JSON() const {
        Json::Value result;
        result["model"] = model;
        result["ID"] = id;
        result["location"] = location.dump2JSON();
        result["owner"] = owner->getName();
        return result;
    }
};

// 公車
class Bus {
    std::string name;
    Person* driver;
    std::string date;
    std::vector<Time_Location> gps_trace;
    std::vector<std::pair<Person*, std::pair<std::string, std::string>>> passenger_log; // Person, (上車時間, 下車時間)

public:
    Bus(std::string n, Person* d, std::string dt)
        : name(n), driver(d), date(dt) {}

    void addStop(const Time_Location& loc) {
        gps_trace.push_back(loc);
    }

    void addPassenger(Person* p, std::string time_on, std::string time_off) {
        passenger_log.push_back({p, {time_on, time_off}});
    }

    Json::Value dump2JSON() const {
        Json::Value result;
        result["name"] = name;
        result["date"] = date;
        result["driver"] = driver->getName();

        for (const auto& loc : gps_trace) {
            result["GPS trace"].append(loc.dump2JSON());
        }

        for (const auto& entry : passenger_log) {
            Json::Value passenger;
            passenger["name"] = entry.first->getName();
            passenger["board_time"] = entry.second.first;
            passenger["leave_time"] = entry.second.second;
            result["passengers"].append(passenger);
        }

        return result;
    }
};


int main() {
    // 創建人物
    Person* felix = new Person("Felix Wu", "instructor");
    Person* john = new Person("John", "student");
    Person* tiffany = new Person("Tiffany", "Psychology student");

    // 加入 GPS trace
    felix->addLocation(Time_Location("2025-04-14T14:00:00+0000", 1.0, -1.0, "NCKU EE 4th floor"));
    felix->addLocation(Time_Location("2025-04-14T14:30:00+0000", 1.0, -1.0, "Chang-Rong Bus Stop"));
    felix->addLocation(Time_Location("2025-04-14T14:45:00+0000", 1.0, -1.0, "NCKU Hospital"));
    felix->addLocation(Time_Location("2025-04-14T15:15:00+0000", 1.0, -1.0, "Moore and Pollock"));

    // 建立手機
    Device felix_phone("Android phone", "001", Time_Location("2025-04-14T15:15:00+0000", 1.0, -1.0, "Moore and Pollock"), felix);

    // 建立公車
    Bus bus77("Bus 77", tiffany, "2025-04-14");
    bus77.addStop(Time_Location("2025-04-14T14:30:00+0000", 1.0, -1.0, "Chang-Rong Bus Stop"));
    bus77.addStop(Time_Location("2025-04-14T14:45:00+0000", 1.0, -1.0, "NCKU Hospital"));
    bus77.addStop(Time_Location("2025-04-14T15:15:00+0000", 1.0, -1.0, "Moore and Pollock"));

    // 上下車記錄
    bus77.addPassenger(felix, "2025-04-14T14:30:00+0000", "2025-04-14T15:15:00+0000");
    bus77.addPassenger(john, "2025-04-14T14:30:00+0000", "2025-04-14T14:45:00+0000");

    // 輸出 JSON
    Json::StreamWriterBuilder writer;
    std::cout << "Felix:" << std::endl;
    std::cout << Json::writeString(writer, felix->dump2JSON()) << std::endl;

    std::cout << "\nFelix's Phone:" << std::endl;
    std::cout << Json::writeString(writer, felix_phone.dump2JSON()) << std::endl;

    std::cout << "\nBus 77:" << std::endl;
    std::cout << Json::writeString(writer, bus77.dump2JSON()) << std::endl;

    // 清除資源
    delete felix;
    delete john;
    delete tiffany;

    return 0;
}
