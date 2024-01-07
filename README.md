# PPM Viewer

An Open Source PPM-File Viewer written in `C` and `SDL`.

## Features

- Supports PBM-Files (P1) and PPM-Files (P3)

## How to build

```bash
cmake --build . --config Release
```

## Submodules

```bash
git submodule add https://github.com/libsdl-org/SDL.git vendors/sdl
```

## References

- [ASCII Chart](https://en.cppreference.com/w/cpp/language/ascii)
- [PPM Format Specification](https://netpbm.sourceforge.net/doc/ppm.html)
- [PBM, PGM, and PPM files The simple image file formats](http://utk.claranguyen.me/guide.php?id=ppm)
- [PPM / PGM / PBM image files by Paul Bourke](https://paulbourke.net/dataformats/ppm)
