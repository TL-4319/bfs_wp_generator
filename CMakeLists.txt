cmake_minimum_required(VERSION 3.14)
# Project information
project(WP-generator
  VERSION 1.0.0
  DESCRIPTION "Software to convert mission item to waypoint.txt file for persistent storage"
  LANGUAGES CXX
)

# Add the executable
add_executable(gen_wp 
  gen_wp/gen_wp.cc
)

