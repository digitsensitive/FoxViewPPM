# FoxViewPPM

FoxViewPPM is an Open Source image viewer for PPM, PBM and PGM files, written
in `C` and `SDL2`. The program parses the image data (header and body) and
displays the content using the SDL2 library.

<img src="./readme_image.png" alt="PPM Viewer Image" style="width: 100%;"/>

## Features

- Supports PBM, PGM and PPM files (ASCII and Binary, P1-P6)

## How to build

Initialize or update submodules:

```bash
git submodule update --init --recursive
```

```bash
cd build
cmake --build . --config Release
```

## References

- [ASCII Chart](https://en.cppreference.com/w/cpp/language/ascii)
- [PBM, PGM, and PPM files The simple image file formats](http://utk.claranguyen.me/guide.php?id=ppm)
- [PPM Format Specification](https://netpbm.sourceforge.net/doc/ppm.html)
- [PPM / PGM / PBM image files by Paul Bourke](https://paulbourke.net/dataformats/ppm)
