# R-Type #

## Prerequies ##
*you will have to install dependencies:*

**DISTRIBUTION LINUX**

you can use this list:
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

example for window:
```
    ???
```

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
Here is the developer team :

- Tibo PENDINO - tibo.pendino@epitech.eu
- Zacharie LAWSON - zacharie.lawson@epitech.eu
- Valentin DURIEUX - valentin.durieux@epitech.eu
- Perry CHOUTEAU - perry.chouteau@epitech.eu
- Erwan CARIOU - erwan1.cariou@epitech.eu