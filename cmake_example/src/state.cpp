#include "state.hpp"

nao_state::nao_state(noos::cloud::platform plat)
: detecting_faces__(plat,
                    std::bind(&nao_state::face_callback, this, std::placeholders::_1)
{}

void nao_state::new_state()
{
    
}

void nao_state::face_callback(std::vector<noos::object::face> faces)
{

}
