# Spirograph using the Fourier Transformation
Translates any SVG into a spirograph and renders it.
Inspired by https://www.youtube.com/watch?v=r6sGWTCMz2k

## Dependencies
sfml, imgui, imgui-sfml, nanosvg, noc (file dialog)
Optional: cotire (speedup builds), jet-live (hot reload)

### Linux
```
sudo pacman -S sfml
mkdir dep && cd dep
git clone https://github.com/ocornut/imgui
git clone https://github.com/eliasdaler/imgui-sfml
git clone https://github.com/memononen/nanosvg
git clone https://github.com/guillaumechereau/noc

# Optional
git clone https://github.com/sakra/cotire
git clone https://github.com/ddovod/jet-live
```
follow the instructions at "Ingerating into your project manually" in imgui-sfml/README.md

## Building
### Linux
```
mkdir build && cd build
cmake ..
make
```

## Tests
