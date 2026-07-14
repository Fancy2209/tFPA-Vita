# The Fancy Pants Adventures 1.23 Vita Port

#### NOTE: Sound is currently broken due to issues with the PSVita version of OpenSLES, once these are fixed a new build will be made.  

## Prerequisites
For Playing:  
- The target game's `.so` 
- Data files from version 1.23 extracted from its APK.

For Building:  
- [VitaSDK-softfp](https://github.com/vitasdk-softfp#how-to-install) installed and `VITASDK` env var pointing to it.
- [kubridge](https://github.com/bythos14/kubridge) - kernel plugin required for RWX memory; must be installed on the target Vita.
- A modified version of [OpenSLES](https://github.com/Fancy2209/opensles/tree/tfpa) - modified version 

If you're new to Vita homebrew development in general, start with [Getting Started with PSVita Homebrew Development](https://web.archive.org/web/20250216192850/https://gl33ntwine.com/posts/develop-for-vita/) first.

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

This produces `build/VpkNameYouChose.vpk`. Install it on the Vita like any other homebrew, then copy the game data to `DATA_PATH`.

## Credits

- [TheFloW](https://github.com/TheOfficialFloW) - original so-loader, gtasa_vita
- [Rinnegatamante](https://github.com/Rinnegatamante) - VitaGL, numerous ports and contributions, trophy code
- [withLogic](https://github.com/withLogic) - VitaTRPBuilder and help with the TRP File
- [fgsfds](https://github.com/fgsfds) - various contributions

## License

This software may be modified and distributed under the terms of the MIT license. See the [LICENSE](LICENSE) file for details.
