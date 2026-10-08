# c++sweeper

Minesweeper + c++ + sdl3

Based on google arcade minesweeper
https://www.google.com/fbx?fbx=minesweeper

`https://www.google.com/logos/fnbx/minesweeper/flag_icon.png >> assets/flag_icon.png`

`https://fonts.gstatic.com/s/googlesans/v29/4UaGrENHsxJlGDuGo1OIlL3Owp4.woff2 -> 4UaGrENHsxJlGDuGo1OIlL3Owp4.otf >> assets/google_sans.otf`

## Building
Prerequisites:

You will need depencencies from for SDL3, which you can find at https://wiki.libsdl.org/SDL3/READMEs for your device. You will also need `cmake`, and either `gcc >= 15` or `clang >= 19` to build

Clone with `git clone https://github.com/dumb12344/c--sweeper.git --depth 1 --recurse-submodules --shallow-submodules`

### Build steps:
use `make` or `make test` for dev test, use `make release` or `make dev` to build, outputs in `out/dev_or_release/c++sweeper`

use `make test-clang`, `make release-clang`, or `make dev-clang` to build with clang

### Web build:
You need to install `emsdk`, and you may need to change the Makefile for non-unix systems

use `make release-emscripten` to build web release, outputs in `out/emscripten/c++sweeper.[html, js, wasm]`