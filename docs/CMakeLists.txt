# check if Doxygen is installed
find_package(Doxygen 1.9)
if (DOXYGEN_FOUND)

    # Populates the doxygen-awesome-css_SOURCE_DIR variable.
    FetchContent_GetProperties(doxygen-awesome-css)

    #
    # Configuration
    # https://www.doxygen.nl/manual/config.html
    #
    set(DOXYGEN_PROJECT_NAME "Learning OpenGL")
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_WARN_NO_PARAMDOC YES)
    set(DOXYGEN_WARN_AS_ERROR YES)

    #
    # Base Theme
    #
    set(DOXYGEN_GENERATE_TREEVIEW YES) # optional. Also works without treeview
    set(DOXYGEN_DISABLE_INDEX NO)
    set(DOXYGEN_FULL_SIDEBAR NO)
    set(DOXYGEN_HTML_EXTRA_STYLESHEET ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome.css)
    set(DOXYGEN_HTML_COLORSTYLE LIGHT) # required with Doxygen >= 1.9.5

    #
    # Sidebar-Only Theme
    #
    # set(DOXYGEN_GENERATE_TREEVIEW     YES) # required!
    # set(DOXYGEN_DISABLE_INDEX         NO)
    # set(DOXYGEN_FULL_SIDEBAR          NO)
    # set(
    #     DOXYGEN_HTML_EXTRA_STYLESHEET
    #     ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome.css
    #     ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome-sidebar-only.css
    # )
    # set(DOXYGEN_HTML_COLORSTYLE       LIGHT) # required with Doxygen >= 1.9.5

    doxygen_add_docs(
        doxygen
        #
        # If ALL is set, the target will be added to the default build target.
        # ALL
        #
        # Include all source files.
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
        #
        # Include the readme of the project.
        ${CMAKE_CURRENT_SOURCE_DIR}/../README.md
        #
        # Include all markdown files in the docs folder.
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

else (DOXYGEN_FOUND)

    message(
        SEND_ERROR
        "Doxygen need to be installed to generate the doxygen documentation."
    )

endif (DOXYGEN_FOUND)
