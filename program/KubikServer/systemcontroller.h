#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H


enum BatteryChargeStatus
{
    High = 1,                   //the battery capacity is at more than 66 percent
    Low = 2,                    //the battery capacity is at less than 33 percent
    Critica = 4,                //the battery capacity is at less than five percent
    Charging = 8,               //
    NoSystemBattery = 128,    //
    UnknownStatus = 255        //unable to read the battery flag information
};

class SystemController
{
public:
    BatteryChargeStatus batteryStatus();
    void changeDesktopPath() = delete;
    bool hasInternetConnection();
};

#endif // SYSTEMCONTROLLER_H
