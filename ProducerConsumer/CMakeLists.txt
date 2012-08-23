project(PRODUCER_CONSUMER)

#
#
add_executable(ProducerConsumer ProducerConsumer.cpp)

find_package(Boost COMPONENTS thread date_time REQUIRED)
target_link_libraries(ProducerConsumer ${Boost_LIBRARIES})

