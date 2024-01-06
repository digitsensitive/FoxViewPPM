# PPM Viewer

An Open Source PPM-File Viewer written in `C` and `SDL`.

## Roadmap

The goal is to write a clean and short code. No overhead!

1. Basic SDL Setup with CMake to create window
2. Study PPM File Format
3. Study how to open ppm Format with specific program (drag-and-drop?)
4. Add read_ppm_file() function
5. Add display_ppm_file() function

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
