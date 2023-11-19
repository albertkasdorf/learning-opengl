FetchContent_Declare(
    hdf5
    GIT_REPOSITORY https://github.com/HDFGroup/hdf5.git
    GIT_TAG        8b5cac6bc498546efa5639f99bb7dbbc1a2d5d90 # Tag hdf5-1_14_3
)

# project (HDF5 C)
# target_link_libraries (${example} PRIVATE ${HDF5_LIB_TARGET})