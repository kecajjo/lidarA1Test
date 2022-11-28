# finding ZeroMq 
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

#################################################
add_executable(laptop
 src/subscriber.cpp )
## add the include directory to our compile directives
target_include_directories(laptop PUBLIC inc/ ${ZeroMQ_INCLUDE_DIR})
## at the 0mq library to our link directive
target_link_libraries(laptop PUBLIC protoMessages ${ZeroMQ_LIBRARY} ${Protobuf_LIBRARIES})
