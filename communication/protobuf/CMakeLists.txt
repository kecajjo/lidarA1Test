# generate files from proto
find_package(Protobuf REQUIRED)

set(PROTO_FILES LaserScan TestMsg)
set(PROTO_INPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(PROTO_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
foreach(proto IN LISTS PROTO_FILES)
  execute_process(
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} -I${CMAKE_CURRENT_SOURCE_DIR}
            --cpp_out=${PROTO_OUTPUT_PATH} "${PROTO_INPUT_PATH}/${proto}.proto")
endforeach(proto)

set(LIB_PROTO_FILES ${PROTO_FILES})

list(TRANSFORM LIB_PROTO_FILES APPEND ".pb.cc")

add_library(protoMessages ${LIB_PROTO_FILES})

target_include_directories(protoMessages PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(protoMessages PUBLIC ${Protobuf_LIBRARIES})