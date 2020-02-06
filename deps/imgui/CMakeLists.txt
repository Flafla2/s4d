cmake_minimum_required(VERSION 3.14)

project(imgui LANGUAGES CXX OBJC)

set(SOURCES_IMGUI "imgui_compile.cpp")

add_library(imgui ${SOURCES_IMGUI})
