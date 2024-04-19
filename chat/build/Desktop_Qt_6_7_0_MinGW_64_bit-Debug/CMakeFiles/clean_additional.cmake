# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\chat_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\chat_autogen.dir\\ParseCache.txt"
  "chat_autogen"
  )
endif()
