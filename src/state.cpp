#include "state.hpp"
#include "event.hpp"

void face_data::reset()
{
    face_found = false;
    close_face = false;
    label.clear();
    age.clear();
    expression.clear(); 
    name.clear();

}
void state::reset()
{
    head_data.movement_time = 0.0f;
    state_time = boost::chrono::system_clock::now();
    head_touched = false;
    face.reset();
}

nao_state::nao_state()
: detecting_faces_(std::bind(&nao_state::face_callback, this, std::placeholders::_1)),
  f_extras_(std::bind(&nao_state::expression_callback, this, std::placeholders::_1),
            std::bind(&nao_state::age_callback, this, std::placeholders::_1),
            std::bind(&nao_state::gender_callback, this, std::placeholders::_1))
{}

state nao_state::new_state()
{
    state_.reset();
    get_image()(robot_ip::ip, image_);
    if (!image_.empty()) {
        detecting_faces_.send(image_);
    }
    tactile_sensor touched_sensor;
    state_.head_touched = touched_sensor.touched; 
    return state_;
}

void nao_state::face_callback(std::vector<noos::object::person> faces)
{
    if (faces.size() != 0) { 
        int i = 0;
        int max_size = 0;
        bigger_face()(faces, i, max_size);
        if (max_size > 20) { 
            face_location()(faces.at(i).face_rect.top_left_x + max_size/2,
                            state_.head_data.angle_head,
                            state_.head_data.movement_time);
            state_.face.face_found = true;
            state_.face.label = faces.at(i).label;
            state_.face.name = faces.at(i).name;
            if (max_size > 70) {
                state_.face.close_face = true;
                f_extras_.batch_send(image_, faces.at(i).face_rect);  
            }
        }
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
        state_.face.age = ages[pos].first;
        auto dash = state_.face.age.find('-');
        state_.face.age.replace(dash, 1, " to "); 
    }
}

void nao_state::gender_callback(std::vector<std::pair<std::string,float>> gender)
{
    if (gender.size() != 0) {
        float max_prob = 0;
        int pos = 0;
        for (auto i = 0; i < gender.size(); i++) {
            if (gender[i].second > max_prob) {
               max_prob = gender[i].second;
               pos = i;
            }
        }
        state_.face.gender = gender[pos].first;
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
        state_.face.expression = expressions[pos].first;
    }
}
