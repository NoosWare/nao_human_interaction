# NAO Example aplication using NOOS

Example application using robot [NAO](https://www.softbankrobotics.com/emea/en/robots/nao) with [NOOS API](https://github.com/NoosWare/noos-api-cpp).
NAO will recognize the faces (previously trained in the NOOS Cloud) in the case that a face is detected.
NAO will move closer if the person is too far and then if this person is happy or neutral, NAO will guess the age of that person.

WARNING: There is no obstacle avoidance or cliff detection, so you will have to take care of the robot while the application is running.

