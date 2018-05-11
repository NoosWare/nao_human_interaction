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
            std::bind(&nao_state::age_callback, this, std::placeholders::_1)),
  op_image_(nao_broker::get_broker(), "opi")
{}

state nao_state::new_state()
{
    state_.reset();
    auto now = boost::chrono::system_clock::now();
    
    //get_image()(robot_ip::ip, image_);
    //im_module_->optimizedImageProcessing();
    //image_ = im_module_.get_image();
    image_ = op_image_.optimizedImageProcessing();

    printf("get_image: %lld \n", boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::system_clock::now() - now).count());
    //if (!image_.empty()) {
    //    detecting_faces_.send(image_);
    //}
    //tactile_sensor touched_sensor;
    //state_.head_touched = touched_sensor.touched; 
    printf("sensor touched: %x \n", state_.head_touched);
    return state_;
}

void nao_state::face_callback(std::vector<noos::object::person> faces)
{
    if (faces.size() != 0) { 
        int i = 0;
        int max_size = 0;
        bigger_face()(faces, i, max_size);
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
        printf("EMOTIONNNNNNNNNNNNNNNNNNNNNNN : %s  %.2f \n", expressions[pos].first.c_str(), expressions[pos].second);
    }
}
