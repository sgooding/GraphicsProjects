project(BOOST_THREAD)

#
#
add_executable(BoostThread BoostThread.cpp)

find_package(Boost COMPONENTS thread REQUIRED)
target_link_libraries(BoostThread ${Boost_LIBRARIES})

