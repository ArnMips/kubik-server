#include "systemcontroller.h"

#include <WinBase.h>
#include <WinInet.h>
#include <Windows.h>

BatteryChargeStatus SystemController::batteryStatus()
{
    SYSTEM_POWER_STATUS sps;
    GetSystemPowerStatus(&sps);
    return static_cast<BatteryChargeStatus>(sps.BatteryFlag);
}

bool SystemController::hasInternetConnection()
{
//    if (InternetCheckConnection(
//                L"http://www.google.com",FLAG_ICC_FORCE_CONNECTION,0)
//            ) {
//        return true;
//    }
    return false;
}
