add_executable(uniq_ptr unique_ptr.cpp)
add_executable(shared_ptr shared_ptr.cpp)
add_executable(weak_ptr weak_ptr.cpp)

add_custom_target(smart_pointers)
add_dependencies(smart_pointers uniq_ptr)
add_dependencies(smart_pointers shared_ptr)
add_dependencies(smart_pointers weak_ptr)