create_test_sourcelist( TESTS
	tests.cpp
    testfile.cpp
    )

add_executable( tests ${TESTS} )

remove( TESTS tests.cpp )

foreach( test ${TESTS} )
    get_filename_component( TName ${test} NAME_WE )
    add_test( ${TName} tests ${TName} )
endforeach( test )