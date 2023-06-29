#!/bin/sh

touch file1 file2

test_made=0
test_OK=0

check()
{
    test_made=$(($test_made+1))
    echo "#################"
    echo Test: "$@"

    find "$@" > file1
    return_find=$?

    ./myfind "$@" > file2
    return_myfind=$?

    echo
    if [ "$return_find" -eq "$return_myfind" ]; then
	    echo OK for return value
        test_OK=$(($test_OK+1))
    else
	    echo KO for return value, "$return_myfind" for myfind and "$return_find" for find
    fi

    diff file1 file2
    return_diff=$?
    if [ "$return_diff" -eq 0 ]; then
	    echo OK for comparaison
        test_OK=$(($test_OK+1))
    else
	    echo KO for comparaison
    fi
    echo
}

#without action
check
check src
check ast_evaluation src tests
check foo foobar src tests
check ast_evaluation src src src src src src
check src src foo bar acu tests ast_evaluation simple_ls
check ../tests/
check ./src/

#name action
check tests -name bar
check tests -name "test.sh"
check src -name bar
check src -name parser.c
check tests -name baz
check src ast_evaluation tests -name main.c
check src ast-evaluation tests simple_ls -name parser.c
check tests src -name tests
check src -name parser.c
check src tests -name *.c
check src -name par*.c
check -name simple*.c

#'or' and 'and'
check src -name main.c -name parser.c
check src -name parser.c -o parser.c
check -name action.h -name expression.h -o -name action.c
check src ast-evaluation ast_evaluation -name parser.c -o -name action.c -print
check -name parser.c -o -name action.h -o -name expression.h -print

#type action

check src tests -type d
check src testssdggrg -type g
check src tests ast_evaluation -type s
check src ast-evaluation tests -type d
check src tests -ast-evaluation -name parser.c -o -type d -print



echo Test passed: $test_OK/$(($test_made*2))

rm file1 file2
