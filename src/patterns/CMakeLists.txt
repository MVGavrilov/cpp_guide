add_executable(factory_method factory_method.cpp)
add_executable(abstract_factory abstract_factory.cpp)
add_executable(prototype prototype.cpp)

add_custom_target(patterns)
add_dependencies(patterns factory_method)
add_dependencies(patterns abstract_factory)
add_dependencies(patterns prototype)