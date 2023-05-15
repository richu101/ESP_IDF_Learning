# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Espressif/frameworks/esp-idf-v4.4.4/components/bootloader/subproject"
  "E:/ESP_Work_Space/hello_world/build/bootloader"
  "E:/ESP_Work_Space/hello_world/build/bootloader-prefix"
  "E:/ESP_Work_Space/hello_world/build/bootloader-prefix/tmp"
  "E:/ESP_Work_Space/hello_world/build/bootloader-prefix/src/bootloader-stamp"
  "E:/ESP_Work_Space/hello_world/build/bootloader-prefix/src"
  "E:/ESP_Work_Space/hello_world/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/ESP_Work_Space/hello_world/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
