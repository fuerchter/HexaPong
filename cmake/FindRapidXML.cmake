find_path(RAPIDXML_INCLUDE_DIR NAMES rapidxml.hpp)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(RAPIDXML DEFAULT_MSG RAPIDXML_INCLUDE_DIR)

if(RAPIDXML_FOUND)
	set(RAPIDXML_INCLUDE_DIRS ${RAPIDXML_INCLUDE_DIR})
endif()

mark_as_advanced(RAPIDXML_INCLUDE_DIR)