# c++sweeper

Minesweeper + c++ + sdl3

Based on google arcade minesweeper
https://www.google.com/fbx?fbx=minesweeper

`https://www.google.com/logos/fnbx/minesweeper/flag_icon.png >> assets/flag_icon.png`

`https://fonts.gstatic.com/s/googlesans/v29/4UaGrENHsxJlGDuGo1OIlL3Owp4.woff2 -> 4UaGrENHsxJlGDuGo1OIlL3Owp4.otf >> assets/google_sans.otf`

## Building
Prerequisites:

You will need `libc++`, `sdl3`, `sdl3_image`, `sdl3_ttf`, `cmake`, and either `gcc` or `clang` to build 

Build steps:
use `make` or `make test` for dev test, use `make release` or `make dev` to build, outputs in `out/build/dev_or_release/c++sweeper`

use `make test-clang`, `make release-clang`, or `make dev-clang` to build with clang