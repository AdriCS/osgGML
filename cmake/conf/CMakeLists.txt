####
# Configuration files.
####

set(CMAKE_DEST_DIR "share/cmake")
set(PROJECT_ROOT_DIR "../../..")

configure_file("${PROJECT_NAME}-config.cmake.in"
               ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake @ONLY
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
              DESTINATION "${CMAKE_DEST_DIR}"
)
install(EXPORT ${EXPORT_NAME} FILE "${PROJECT_NAME}-${EXPORT_NAME}.cmake"
        DESTINATION "${CMAKE_DEST_DIR}"
)