#include "state.hpp"

void state::reset()
{
    face_found = false;
    movement_time = 0.0f;
    state_time = boost::chrono::system_clock::now();
}

nao_state::nao_state()
: detecting_faces_(noos_platform::noos,
                    std::bind(&nao_state::face_callback, this, std::placeholders::_1))
{}

state nao_state::new_state()
{
    state_.reset();
    auto now = boost::chrono::system_clock::now();
    
    get_image()(robot_ip::ip, image_);

    printf("get_image: %lld \n", boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::system_clock::now() - now).count());
    if (!pic.empty()) {
        detecting_faces_.send(image_);
    }
    return state_;
}

void nao_state::face_callback(std::vector<noos::object::face> faces)
{
    std::cout << "Found: " << faces.size() << " faces" << std::endl; 
    if (faces.size() != 0) { 
        int i = 0;
        int max_size = 0;
        bigger_face(faces, i, max_size);
        state_.center_face_x = faces.at(i).top_left_x + max_size/2;
        face_location()(state_.center_face_x,
                        state_.angle_head,
                        state_.movement_time);
        state_.face_found = true;
    }
    state_.state_time = boost::chrono::system_clock::now();
    printf("angle after callback: %.2f \n", state_.angle_head); 
}
