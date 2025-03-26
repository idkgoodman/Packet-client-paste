# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/solstice-master-main/build/_deps/spdlog-src")
  file(MAKE_DIRECTORY "D:/solstice-master-main/build/_deps/spdlog-src")
endif()
file(MAKE_DIRECTORY
  "D:/solstice-master-main/build/_deps/spdlog-build"
  "D:/solstice-master-main/build/_deps/spdlog-subbuild/spdlog-populate-prefix"
  "D:/solstice-master-main/build/_deps/spdlog-subbuild/spdlog-populate-prefix/tmp"
  "D:/solstice-master-main/build/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp"
  "D:/solstice-master-main/build/_deps/spdlog-subbuild/spdlog-populate-prefix/src"
  "D:/solstice-master-main/build/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/solstice-master-main/build/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/solstice-master-main/build/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
