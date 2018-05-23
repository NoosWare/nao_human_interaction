# NAO Example application using NOOS

Example application using robot [NAO](https://www.softbankrobotics.com/emea/en/robots/nao) with [NOOS API](https://github.com/NoosWare/noos-api-cpp).
NAO will recognize the faces (previously trained in the NOOS Cloud) in the case that a face is detected.
NAO will move closer if the person is too far and then NAO will say the age, gender and expression of that person.
To end the program, touch the top part of head of NAO.

*WARNING:* There is no obstacle avoidance or cliff detection, so you will have to take care of the robot while the application is running.

## Dependencies

The following dependencies are required to build the application:

- gcc/g++ >= 5.4
- boost >= 1.58
- cmake >= 2.8
- libssl-dev >= 1.0.1

*WARNING*: `libssl` is required independently of the version included in the `Naoqi SDK`, because the included one is
too old for including TLS version 1_2, which is the protocol used for connecting with the NOOS platform.

On a Ubuntu/Debian machine you can install all dependencies using (you milage may vary depending on distro version)

```shell
sudo apt-get install cmake gcc g++ libboost-all-dev libssl-dev
```

### NOOS API

To install the Noos API, just follow the instructions of this [link](https://github.com/NoosWare/noos-api-cpp) and
use the `cmake` option `-DOPEN_NAO=ON`.
This will install the `static` version of the library.

### Naoqi SDK for C++
i
First, you will need to download the latest version of the library in the [aldebaran web page](http://doc.aldebaran.com/2-4/dev/community_software.html)
For this app the C++ SDK is required.
After uncompress your files, for running the app correctly you should write the correct path to your SDK:

```
cmake .. -DNAOQI_PATH=/your/path
```

`{HOME}/naoqi-sdk-2.1.4.13-linux32/` is the default path and version in the project. 
Otherwise, use the `-DNAOQI_PATH` option.
i
## Building

To build simply do:

```shell
mkdir build
cd build
cmake .. -DNAOQI_SDK=/your/path
make
```

*WARNING*: You should take care of the system that you use for compilation due to has to be compatible with NAO. This app
has been run and tested in Ubuntu 14.04 of 32-bit.

## Run

To run the application you should add 4 arguments:

- IP of the robot
- reset robot: `true` for reset posture and head of the robot; `false` for run the application
- user name for using the Noos platform
- password of the Noos platform

Example:

```shell
./NAO_app 127.0.0.1 false my_user my_pass
```

It can be run remotely in your computer, or directly in NAO using the local IP (127.0.0.1).
