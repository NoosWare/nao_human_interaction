#include "configuration.hpp"

std::string robot_ip::ip = "127.0.0.1";
noos::cloud::platform noos_platform::noos = {"85.10.206.221", "9001", "test_token", "test"};

void robot_ip::set_ip(std::string new_ip)
{
    ip = new_ip;
}

void noos_platform::set_platform(std::string user,
                                 std::string pass)
{
    noos.user = user;
    noos.token = pass;
}

void configuration::set_ip_nao(std::string ip)
{
    robot_ip::set_ip(ip);
}

void configuration::set_noos(std::string user,
                             std::string pass)
{
    noos_platform::set_platform(user, pass); 
}
