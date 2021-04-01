set (SourceFiles
     encoder.cpp
     audioEncoder.cpp
     videoEncoder.cpp
)

set(HeaderFiles
    encoder.h
    audioEncoder.h
    videoEncoder.h
)

add_library (vStream.Encoder OBJECT
             ${SourceFiles} ${HeaderFiles}
)

include_directories(${VSTREAM_SOURCE_DIR})

target_include_directories (
    vStream.Encoder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${VSTREAM_SOURCE_DIR}
)