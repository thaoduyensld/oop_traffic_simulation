#ifndef EMERGENCY_VEHICLE_H
#define EMERGENCY_VEHICLE_H

#include "Vehicle.h"
#include "Road.h"

class EmergencyVehicle : public Vehicle {
public:
    // Gọi constructor của lớp cha
    EmergencyVehicle(int id, double speed, Intersection* start, Intersection* dest) 
        : Vehicle(id, speed, start, dest) {}

    // [BẮT BUỘC] Override lại hàm ảo để thể hiện Đa hình
    double calculateCurrentSpeed() const override {
        if (currentRoad == nullptr) return 0.0;
        
        // Đặc quyền xe ưu tiên: Hú còi dẹp đường!
        // Phớt lờ mọi giới hạn tốc độ (speedLimit) và bất chấp kẹt xe (congestionLevel).
        // Luôn chạy đúng với tốc độ gốc tối đa.
        return baseSpeed; 
    }
};

#endif