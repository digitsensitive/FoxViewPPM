# FoxViewPPM

![GitHub repo size](https://img.shields.io/github/repo-size/digitsensitive/FoxViewPPM)
![GitHub Release](https://img.shields.io/github/v/release/digitsensitive/FoxViewPPM)

FoxViewPPM is a lightweight image viewer written in `C` and `SDL2`, specifically
designed for PPM, PBM, and PGM file formats. It aims to provide a simple and
efficient tool for viewing images with a focus on ease of use.

This project was created for educational purposes.

<img src="./readme_image.png" alt="PPM Viewer Image" style="width: 100%;"/>

## Features

1. **Cross-Platform Compatibility**: FoxViewPPM is designed to work seamlessly
   across various platforms, including Windows, macOS, and Linux (coming).
2. **Support for PPM, PBM, and PGM Formats**: The viewer is capable of parsing and
   displaying images in the widely used PPM (Portable Pixel Map),
   PBM (Portable Bitmap), and PGM (Portable Graymap) formats.
3. **Efficient Image Parsing**: FoxViewPPM efficiently parses both the header and
   body of image files, ensuring quick and accurate rendering of images.
4. **Command Line Support**: Run FoxViewPPM from the command line, making it
   convenient for integration into scripts or other workflows.
5. **Lightweight and Fast**: With a minimalistic design, FoxViewPPM prioritizes
   speed and efficiency, providing a fast and responsive image viewing experience.
6. **Open Source**: FoxViewPPM is an open-source project, encouraging collaboration
   and contributions from the community. Feel free to fork the repository,
   report issues, or submit pull requests.

## How to build

Initialize submodules:

```bash
git submodule update --init --recursive
```

Build Release:

```bash
cd build
cmake --build . --config Release
```

## References

- [ASCII Chart](https://en.cppreference.com/w/cpp/language/ascii)
- [PBM, PGM, and PPM files The simple image file formats](http://utk.claranguyen.me/guide.php?id=ppm)
- [PPM Format Specification](https://netpbm.sourceforge.net/doc/ppm.html)
- [PPM / PGM / PBM image files by Paul Bourke](https://paulbourke.net/dataformats/ppm)

## License

This project is licensed under the GPL-3.0 license.
