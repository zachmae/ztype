# Z-Type #

R-Type is an Epitech third year project that consist of the recreation of the famous eponym arcade game from 1987.
The overall project consist of two axis, a multithreaded server and a graphical client for the game
The game is working with an ECS(Entity Component System) of our own design.

The whole project as been made in C++ using  the Asio library for the network and SFML for the display

## Prerequies ##
*you will have to install dependencies:*

**DISTRIBUTION LINUX**

Dependencies are as this list:
- SFML(-devel)
- libX11(-devel, -xcb)
- libXrandr(-devel)
- libgl1-mesa(-devel)
- libgudev
- glx-utils

example for ubuntu:
```
    sudo apt install SFML
```
example for fedora:
```
    sudo dnf install SFML
```

**DISTRIBUTION WINDOWS**

Dependencies are as this list:
- CMake
- Visual Studio
- OpenGL

**Release**

For both Windows and Linux, you can check the release page of our repository to download the latest version of the game

## Installation and Usage ##

Execute CMake
```
    cd build
    cmake ..
    cmake --build .
```

Server
```
    ./rtype [port]
```

Client
```
    ./rtype [ip] [port]
```

## Documentation ##

Use convensional commit to add upgrades

We use Doxygen to document this project, you can generate it by write those commands
```
    doxygen ./documentation/doxygen/rtype_doxygen.conf
```

## Contributors ##

This game has been done in the context of an Epitech project.</br>
Here is the developer team (you can join us by mail):

- Tibo PENDINO - tibo.pendino@epitech.eu
- Zacharie LAWSON - zacharie.lawson@epitech.eu
- Valentin DURIEUX - valentin.durieux@epitech.eu
- Perry CHOUTEAU - perry.chouteau@epitech.eu
- Erwan CARIOU - erwan1.cariou@epitech.eu

## License ##

Our Z-Type source code is distributed under the MIT license. See [License.md](https://github.com/EpitechPromo2025/B-CPP-500-PAR-5-1-rtype-zacharie.lawson/blob/main/License.md) for more details