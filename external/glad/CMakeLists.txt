set(
    TARGET_NAME glad
)
add_library(
    ${TARGET_NAME} STATIC
)
add_library(
    ${TARGET_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME}
)
target_sources(
    ${TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
)
target_include_directories(
    ${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
