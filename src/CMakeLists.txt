add_library(raftlog
  log/segment.cpp
  log/index.cpp
  log/log.cpp
  raft/raft_node.cpp
  broker/server.cpp
  broker/client.cpp
)

target_include_directories(raftlog PUBLIC
  ${CMAKE_SOURCE_DIR}/include
)

find_package(ZLIB REQUIRED)
target_link_libraries(raftlog PRIVATE ZLIB::ZLIB)
