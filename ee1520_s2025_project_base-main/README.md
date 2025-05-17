# EE1520 Homework 2 – Traceable People 

這次作業設計方向追蹤人物在特定時間與地點的移動路徑（GPS trace），並記錄每筆位置資料的標籤與人物當下狀態（例如在車上、已到達等）。

---

## 📁 專案檔案結構

- `main.cpp`: 主要執行程式，負責建立人物物件、記錄追蹤資料並輸出 JSON 結果
- `Traceable_Person.h / .cpp`: 負責描述可追蹤人物，支援記錄位置、狀態、標籤，並能輸出為 JSON
- `Timed_Location.h / .cpp`: 表示包含時間與 GPS 的資料點
- `GPS.h`: 處理 "latitude","longitude"
- `JvTime.h`: 處理 ISO 8601 格式的時間（e.g., `2025-04-14T14:30:00+0000`）


---

## 新增部分

### Traceable_Person.h
```c++
void addTrace(const Timed_Location &tl, const std::string &label, const std::string &status);
```


### Traceable_Person.cpp 

1. 對人物新增物件，增加職業
```c++
Traceable_Person::Traceable_Person(std::string name, std::string occupation)
    : Person("", name) 
{
  this->class_name = "Traceable_Person";
  this->occupation = occupation;
  this->home = nullptr; 
}
```

2. 對人物新增地點跟時間，並加上狀態，ex: Bus77 or get off the bus 
```c++
void Traceable_Person::addTrace(const Timed_Location &tl, const std::string &label, const std::string &status)
{
  this->GPS_trace.traces.push_back(tl);
  this->trace_labels.push_back(label);
  this->trace_statuses.push_back(status);
}

```


---

## 🔧 編譯方式

```bash

make 
./main

```

## 🔧 編譯結果

```
{
  "1.name" : "Felix Wu",
  "2.occupation" : "instructor",
  "GPS trace" :
  [
    {
      "label" : "NCKU EE 4th floor",
      "location" :
      {
        "latitude" : 22.996776000000001,
        "longitude" : 120.222415
      },
      "status" : "ended class",
      "time" :
      {
        "time" : "2025-04-14T14:00:00+"
      }
    },
    {
      "label" : "Chang-Rong Bus Stop",
      "location" :
      {
        "latitude" : 22.9971,
        "longitude" : 120.2222
      },
      "status" : "on Bus77",
      "time" :
      {
        "time" : "2025-04-14T14:30:00+"
      }
    }
  ]
}
{
  "1.name" : "John",
  "2.occupation" : "student",
  "GPS trace" :
  [
    {
      "label" : "Chang-Rong Bus Stop",
      "location" :
      {
        "latitude" : 22.9971,
        "longitude" : 120.2222
      },
      "status" : "on Bus77",
      "time" :
      {
        "time" : "2025-04-14T14:30:00+"
      }
    },
    {
      "label" : "NCKU Hospital",
      "location" :
      {
        "latitude" : 22.998079000000001,
        "longitude" : 120.222168
      },
      "status" : "get off the Bus 77",
      "time" :
      {
        "time" : "2025-04-14T14:45:00+"
      }
    }
  ]
}

```