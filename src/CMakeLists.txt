project(${CMAKE_PROJECT_NAME})

add_library (${PROJECT_NAME} STATIC
  vStreamStatic.cpp
  pch.h
  $<TARGET_OBJECTS:vStream.Encoder>
  $<TARGET_OBJECTS:vStream.Muxer>
)

# vStream Src dir
set(VSTREAM_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#external includes
target_include_directories(${PROJECT_NAME} PRIVATE
                            ${AVCODEC_INCLUDE_DIR}
                            ${AVFORMAT_INCLUDE_DIR}
                            ${AVUTIL_INCLUDE_DIR}
                            ${AVDEVICE_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  # Add include_directories here
  encoder
)
target_link_libraries(${PROJECT_NAME} PRIVATE
                      ${AVCODEC_LIBRARY}
                      ${AVFORMAT_LIBRARY}
                      ${AVUTIL_LIBRARY}
                      ${AVDEVICE_LIBRARY})

add_subdirectory(main)
add_subdirectory(encoder)
add_subdirectory(muxer)
