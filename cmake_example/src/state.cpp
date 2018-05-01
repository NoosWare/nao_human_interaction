#include "state.hpp"

void state::reset()
{
    face_found = false;
    close_face = false;
    head_data.movement_time = 0.0f;
    state_time = boost::chrono::system_clock::now();
    age.clear();
    expression.clear(); 
}

nao_state::nao_state()
: detecting_faces_(std::bind(&nao_state::face_callback, this, std::placeholders::_1)),
  f_extras_(std::bind(&nao_state::expression_callback, this, std::placeholders::_1),
            std::bind(&nao_state::age_callback, this, std::placeholders::_1))
{}

state nao_state::new_state()
{
    state_.reset();
    auto now = boost::chrono::system_clock::now();
    
    get_image()(robot_ip::ip, image_);

    printf("get_image: %lld \n", boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::system_clock::now() - now).count());
    if (!image_.empty()) {
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
        bigger_face()(faces, i, max_size);
        face_location()(faces.at(i).top_left_x + max_size/2,
                        state_.head_data.angle_head,
                        state_.head_data.movement_time);
        state_.face_found = true;
        printf("size of face: %d \n",max_size); 
        //if (max_size > 90) {
            //state_.close_face = true;
            f_extras_.batch_send(image_, faces.at(i));  
        //}
    }
    state_.state_time = boost::chrono::system_clock::now();
}

void nao_state::age_callback(std::vector<std::pair<std::string,float>> ages)
{
    if (ages.size() != 0) {
        float max_prob = 0;
        int pos = 0;
        for (auto i = 0; i < ages.size(); i++) {
            if (ages[i].second > max_prob) {
               max_prob = ages[i].second;
               pos = i;
            }
        }
        state_.age = ages[pos].first;
    }
}

void nao_state::expression_callback(std::vector<std::pair<std::string,float>> expressions)
{
    if (expressions.size() != 0) {
        float max_prob = 0;
        int pos = 0;
        for (auto i = 0; i < expressions.size(); i++) {
            if (expressions[i].second > max_prob) {
               max_prob = expressions[i].second;
               pos = i;
            }
        }
        state_.expression = expressions[pos].first;
        printf("EMOTIONNNNNNNNNNNNNNNNNNNNNNN : %s  %.2f \n", expressions[pos].first.c_str(), expressions[pos].second);
    }
}
