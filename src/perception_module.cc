#include "light.pb.h"
#include <unistd.h>
#include <cstdint>
#include <ctime>
#include <time.h>
#include <string>
#include <iostream>

namespace zzy {
namespace car {
    float turn_kmh_2_ms(float speed) {
        return speed / 36.0; //x * 1000 / 3600;
    }
    void send(const Request& request) {
        std::time_t now = std::time(nullptr);
        std::cout << std::asctime(std::localtime(&now)) << " Send msg: " << request.vehicle_id()
            << request.perception().light_type() << std::endl;
    }

    void mock_request() {
        Request request;
        request.set_vehicle_id(123);
        std::time_t now = std::time(nullptr);
        request.set_timestamp(now); 
        Perception* percevied_msg = request.mutable_perception();
        percevied_msg->set_light_type(Perception::CAR_LIGHT);   
        percevied_msg->set_car_light_type(Perception::TURN_LEFT);
        percevied_msg->set_distance(200);    //200m ahead
        percevied_msg->set_object_speed(35); //35km/h
        send(request);
        sleep(1);
    }
    
}
}
    int main() {
        zzy::car::mock_request(); 
        return 0;
    }
