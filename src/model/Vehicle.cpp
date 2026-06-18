#include "Vehicle.h"
#include "Road.h"
#include "Intersection.h"

Vehicle::Vehicle(int id, double speed, Intersection* start, Intersection* dest)
    : id(id),
      baseSpeed(speed),
      spawnPoint(start),
      destination(dest),
      currentRoad(nullptr),
      distanceTravelledOnRoad(0.0),
      currentRouteIndex(0) 
{
    // Xe vừa sinh ra chưa có lộ trình, đứng yên tại spawnPoint chờ Người 3 nạp route
}

void Vehicle::setRoute(const std::vector<Road*>& route) {
    currentRoute = route;
    currentRouteIndex = 0;
    distanceTravelledOnRoad = 0.0;
    
    if (!currentRoute.empty()) {
        currentRoad = currentRoute[0]; // Bắt đầu lăn bánh lên con đường đầu tiên
    } else {
        currentRoad = nullptr;
    }
}

bool Vehicle::hasReachedDestination() const {
    // Nếu không còn đường nào để đi và đã đi hết lộ trình -> tới đích
    return (currentRoad == nullptr && currentRouteIndex >= currentRoute.size());
}

double Vehicle::getProgressRatio() const {
    if (currentRoad == nullptr || currentRoad->getDistance() <= 0.0) {
        return 0.0;
    }
    return distanceTravelledOnRoad / currentRoad->getDistance();
}

void Vehicle::update(double dt) {
    // 1. Kiểm tra an toàn: Tới đích rồi hoặc chưa có đường thì đứng im
    if (hasReachedDestination() || currentRoad == nullptr) {
        return;
    }

    // 2. Lấy tốc độ thực tế từ hàm ĐA HÌNH (con nít Car hay cứu thương tự lo)
    double actualSpeed = calculateCurrentSpeed();

    // 3. Tính toán quãng đường đi được trong frame này (S = v * t)
    double distanceMoved = actualSpeed * dt;
    distanceTravelledOnRoad += distanceMoved;

    // 4. Kiểm tra xem xe có đi hết con đường hiện tại chưa
    // Dùng while để xử lý lố qua nhiều đường nhỏ liên tiếp
    while (currentRoad != nullptr && distanceTravelledOnRoad >= currentRoad->getDistance()) {
        
        // Lưu lịch sử đường vừa đi xong
        addTravelHistory(currentRoad);

        // Khấu trừ quãng đường vừa đi hết, giữ lại phần dư (chạy lố) sang đường tiếp theo
        distanceTravelledOnRoad -= currentRoad->getDistance();
        
        // Nhảy sang đường tiếp theo trong lộ trình
        currentRouteIndex++;

        if (currentRouteIndex < currentRoute.size()) {
            // Còn đường để đi
            currentRoad = currentRoute[currentRouteIndex];
        } else {
            // Đã đến đích (hết lộ trình)
            currentRoad = nullptr;
            distanceTravelledOnRoad = 0.0; // Reset thẳng về 0 để an toàn
            break;
        }
    }
}   