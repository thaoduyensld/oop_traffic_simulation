#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include "Road.h"
#include <algorithm> // Để dùng std::min

class Car : public Vehicle {
public:
    // Gọi constructor của lớp cha
    Car(int id, double speed, Intersection* start, Intersection* dest) 
        : Vehicle(id, speed, start, dest) {}

    // [BẮT BUỘC] Override lại hàm ảo để thể hiện Đa hình
    double calculateCurrentSpeed() const override {
        if (currentRoad == nullptr) return 0.0;
        
        // 1. Tốc độ không được vượt quá giới hạn của con đường
        double maxAllowedSpeed = std::min(baseSpeed, currentRoad->getSpeedLimit());
        
        // 2. Bị ảnh hưởng bởi kẹt xe (Ví dụ: mức độ kẹt = 2.0 thì tốc độ giảm một nửa)
        return maxAllowedSpeed / currentRoad->getCongestionLevel();
    }
};

#endif