#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "includes.ihh"

/**
 * @brief Contains the ip of the robot
 * @struct robot_ip
 * @date 17.04.2018
 */
struct robot_ip
{
    ///@brief  robot ip
    static std::string ip;

protected:
    static void set_ip(std::string new_ip);

};

/**
 * @brief Contains the platform data
 * @struct noos_platform
 * @date 18.04.2018
 */
struct noos_platform
{
    ///@brief  robot ip
    static noos::cloud::platform noos;

protected:
    static void set_platform(std::string ip_plat,
                             std::string user,
                             std::string pass);

};


/**
 * @brief configuration of the main parameters
 * @class configuration
 * @date 20.04.2018
 */
class configuration
: public noos_platform,
  public robot_ip
{
public:
   ///@brief set ip
   void set_ip_nao(std::string ip);

   ///@brief set noos platform
   void set_noos(std::string ip_plat,
                 std::string user,
                 std::string pass); 
};

#endif
