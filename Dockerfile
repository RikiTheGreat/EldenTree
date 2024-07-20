# Use Ubuntu latest as base image
FROM ubuntu:latest
LABEL authors="mahdi"


RUN apt-get update &&  apt-get install -y pkg-config   g++ git cmake make ninja-build doxygen curl zip unzip tar 

COPY . /usr/src/EldenTree/
WORKDIR /usr/src/EldenTree/

RUN git clone https://github.com/microsoft/vcpkg.git vcpkg
RUN vcpkg/bootstrap-vcpkg.sh -disableMetrics
RUN vcpkg/vcpkg install
RUN  rm -rf linRelease-ninja-build
RUN apt-get install clang-format clang-tidy -y
RUN cmake --preset Linux-Release-Ninja -DCMAKE_TOOLCHAIN_FILE="vcpkg/scripts/buildsystems/vcpkg.cmake"


WORKDIR linRelease-ninja-build
RUN ninja
