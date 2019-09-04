# Spirograph using the Fourier Series
Translates any SVG image into an approximation of it using the Fourier Series and renders it with a spirograph.
Inspired by 3Blue1Brown https://www.youtube.com/watch?v=r6sGWTCMz2k

## Getting started
*Dependencies:*
sfml, imgui, imgui-sfml, nanosvg, noc (file dialog)
Optional: cotire (speedup builds), jet-live (hot reload)

### Linux
```
sudo pacman -S sfml

git clone github.com/erikgoe/fourier-spirograph

mkdir dep && cd dep
git clone https://github.com/ocornut/imgui
git clone https://github.com/eliasdaler/imgui-sfml
git clone https://github.com/memononen/nanosvg
git clone https://github.com/guillaumechereau/noc
cat imgui-sfml/imconfig-SFML.h >> imgui/imconfig.h

# Optional
git clone https://github.com/sakra/cotire
git clone https://github.com/ddovod/jet-live

mkdir build && cd build
cmake ..
make
```

### Windows
Download sfml (https://www.sfml-dev.org/download.php) and extract it somewhere.
```
git clone github.com/erikgoe/fourier-spirograph

mkdir dep && cd dep
git clone https://github.com/ocornut/imgui
git clone https://github.com/eliasdaler/imgui-sfml
git clone https://github.com/memononen/nanosvg
git clone https://github.com/guillaumechereau/noc
copy imgui/imconfig.h imgui-sfml/imconfig-SFML.h imgui/imconfig.h

# Optional
git clone https://github.com/sakra/cotire
git clone https://github.com/ddovod/jet-live

mkdir build && cd build
cmake .. -DSFML_PATH=C:/src/sfml/SFML-2.5.1
msbuild ALL_BUILD.vcxproj
```
SFML_PATH should be the path to the directory where you extracted sfml into.

Alternatively you can build the .sln in Visual Studio.

## Examples
Approximating a simple rectangle
![rectangle](res/spirograph_rectangle.png)
Outline of Europe
![europe_outline](res/spirograph_europe.png)
A bit sharper
![europe_outline_sharp](res/spirograph_europe_sharp.png)
