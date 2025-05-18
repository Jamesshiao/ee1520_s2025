#ifndef _TRACEABLE_BUS_H_
#define _TRACEABLE_BUS_H_

#include "Traceable_Person.h"
#include <vector>
#include <string>


class Traceable_Bus
{
private:
    std::string bus_name;
    std::vector<Traceable_Person *> passengers;

public:
    Traceable_Bus();
    Traceable_Bus(const std::string &name);
    ~Traceable_Bus();

    void addPassenger(Traceable_Person *person);

    std::string get_name() const;

    // 輸出：只列出 bus 名與乘客清單（完整細節仍在 person 那邊）
    virtual Json::Value *dump2JSON(void);
};

#endif /* _TRACEABLE_BUS_H_ */
