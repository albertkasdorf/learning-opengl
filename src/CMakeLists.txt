
set(
    TARGET_NAME learn-opengl
)
add_executable(
    ${TARGET_NAME} main.cpp
)
set_target_properties(
    ${TARGET_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
target_compile_features(
    ${TARGET_NAME} PRIVATE cxx_std_17
)