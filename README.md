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

# Credit
Decoder inspired by https://github.com/altillimity/libccsds/blob/master/src/ccsds.cpp, encoder is custom.

If this repo helped you, please ⭐ it!