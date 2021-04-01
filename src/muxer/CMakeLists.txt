set (SourceFiles
     muxer.cpp
)

set(HeaderFiles
    muxer.h
)

add_library (vStream.Muxer OBJECT
             ${SourceFiles} ${HeaderFiles}
)

include_directories(${VSTREAM_SOURCE_DIR})

target_include_directories (
    vStream.Muxer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${VSTREAM_SOURCE_DIR}
)