# WeeChat
Wee /wi:/ - adjective - little

WeeChat is a lightweight Desktop WeChat browser. It's designed in C++ and GTK in order to be as fast as possible.

## Requirements
#### G++
`sudo dnf install gcc-c++`

#### gtkmm 3.0
`sudo dnf install gtkmm30`

#### Boost
`sudo dnf install boost boost-system boost-filesystem`

#### Autotools
`sudo dnf install automake autoconf`

## Compilation
This software uses Autotools for compilations. In order to compile this software
```bash
autoreconf -vfi
./configure
make
./src/WeeChat
```