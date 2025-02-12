# libspacepacket
Header-only C library for encoding and decoding CCSDS SpacePacket headers

# Usage
Include in your CMake target like this:
```
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/libspacepacket/)
target_link_libraries(exampletarget
    libspacepacket
)
```
See [coconut-fsw](https://github.com/ASU-SDSL/coconut-fsw) for a real-world usage example 

# Credit
Decoder inspired by https://github.com/altillimity/libccsds/blob/master/src/ccsds.cpp, encoder is custom.

If this repo helped you, please ⭐ it!