add_executable(raftlog_tests
  log_tests.cpp
  raft_tests.cpp
)

target_link_libraries(raftlog_tests PRIVATE raftlog Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(raftlog_tests)
