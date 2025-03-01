# CMake generated Testfile for 
# Source directory: C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager
# Build directory: C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(FlagFieldTests "C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/build/Debug/flagfield_tests.exe")
  set_tests_properties(FlagFieldTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/CMakeLists.txt;47;add_test;C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(FlagFieldTests "C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/build/Release/flagfield_tests.exe")
  set_tests_properties(FlagFieldTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/CMakeLists.txt;47;add_test;C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(FlagFieldTests "C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/build/MinSizeRel/flagfield_tests.exe")
  set_tests_properties(FlagFieldTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/CMakeLists.txt;47;add_test;C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(FlagFieldTests "C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/build/RelWithDebInfo/flagfield_tests.exe")
  set_tests_properties(FlagFieldTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/CMakeLists.txt;47;add_test;C:/Users/RayRi/Documents/Ray's C++ Libraries/Flag Manager/CMakeLists.txt;0;")
else()
  add_test(FlagFieldTests NOT_AVAILABLE)
endif()
subdirs("googletest-build")
