# PPM Viewer

An Open Source PPM-File Viewer written in `C` and `SDL`.

## Features

- Supports P1-P3 Files

| Magic Number | File Type             | Extension | Type    |
| ------------ | --------------------- | --------- | ------- |
| P1           | Portable BitMap       | PBM       | ASCII   |
| P2           | Portable GrayMap      | PGM       | ASCII   |
| P3           | Portable PixMap       | PPM       | ASCII   |
| P4           | Portable BitMap       | PBM       | Binary  |
| P5           | Portable GrayMap      | PGM       | Binary  |
| P6           | Portable PixMap       | PPM       | Binary  |
| P7           | Portable ArbitraryMap | PAM       | Unknown |

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
