cmake_minimum_required(VERSION 3.14)

project(glad LANGUAGES CXX OBJC)

set(SOURCES_GLAD "glad.cpp")

add_library(glad ${SOURCES_GLAD})
