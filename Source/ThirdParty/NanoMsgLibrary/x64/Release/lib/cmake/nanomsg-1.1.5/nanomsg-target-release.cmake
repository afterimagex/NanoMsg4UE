#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "nanomsg" for configuration "Release"
set_property(TARGET nanomsg APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(nanomsg PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/nanomsg.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/nanomsg.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS nanomsg )
list(APPEND _IMPORT_CHECK_FILES_FOR_nanomsg "${_IMPORT_PREFIX}/lib/nanomsg.lib" "${_IMPORT_PREFIX}/bin/nanomsg.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
