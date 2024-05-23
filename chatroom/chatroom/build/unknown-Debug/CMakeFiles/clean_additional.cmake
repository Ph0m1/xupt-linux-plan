# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/chatroom_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/chatroom_autogen.dir/ParseCache.txt"
  "chatroom_autogen"
  )
endif()
