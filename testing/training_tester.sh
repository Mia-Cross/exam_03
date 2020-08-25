#!/bin/bash

# WARNING !!
# This tester's only purpose is to make your life easier when comparing
# your output with the original executable.
# It DOES NOT check for leaks or if the file stream is not closed at the end.

# path to the directory to test (all .c and .h files must be at the root of the directory)
TEST_DIR="my_micro_paint7"

cd ../$TEST_DIR
echo -n "Compiling your program..."
gcc -Wall -Wextra -Werror *.c *.h
echo "OK, done !"
cd ..
mv $TEST_DIR/a.out testing/
cd testing/

echo ""
echo 'TEST 1 : "./a.out"'
echo ""
echo "EXPECTED OUTPUT ="
./our_micro_paint | cat -e | tee expect
echo "EXPECTED RETURN = $?"
echo "YOUR OUTPUT ="
./a.out | cat -e | tee yours
echo "YOUR RETURN = $?"
echo -n ">> DIFF BETWEEN FILES = "
if [[ `diff expect yours` ]]
then
    echo ""
    diff expect yours
else
    echo " No difference, nice !"
fi
echo ""

echo ""
echo 'TEST 2 : "./a.out hello"'
echo ""
echo "EXPECTED OUTPUT ="
./our_micro_paint hello | cat -e | tee expect
echo "EXPECTED RETURN = $?"
echo "YOUR OUTPUT ="
./a.out hello | cat -e | tee yours
echo "YOUR RETURN = $?"
echo -n ">> DIFF BETWEEN FILES = "
if [[ `diff expect yours` ]]
then
    echo ""
    diff expect yours
else
    echo " No difference, nice !"
fi
echo ""

echo ""
echo 'TEST 3 : "./a.out my_file operation_file.example"'
echo ""
echo "EXPECTED OUTPUT ="
./our_micro_paint operation_files/my_file operation_files/operation_file.example | cat -e | tee expect
echo "EXPECTED RETURN = $?"
echo "YOUR OUTPUT ="
./a.out operation_files/my_file operation_files/operation_file.example | cat -e | tee yours
echo "YOUR RETURN = $?"
echo -n ">> DIFF BETWEEN FILES = "
if [[ `diff expect yours` ]]
then
    echo ""
    diff expect yours
else
    echo " No difference, nice !"
fi
echo ""

echo ""
echo 'TEST 4 : "./a.out my_file"'
echo ""
echo "EXPECTED OUTPUT ="
./our_micro_paint operation_files/my_file | cat -e | tee expect
echo "EXPECTED RETURN = $?"
echo "YOUR OUTPUT ="
./a.out operation_files/my_file | cat -e | tee yours
echo "YOUR RETURN = $?"
echo -n ">> DIFF BETWEEN FILES = "
if [[ `diff expect yours` ]]
then
    echo ""
    diff expect yours
else
    echo " No difference, nice !"
fi
echo ""

echo ""
echo 'TEST 5 : "./a.out operation_file.example"'
echo ""
echo "EXPECTED OUTPUT ="
./our_micro_paint operation_files/operation_file.example | cat -e | tee expect
echo "EXPECTED RETURN = $?"
echo "YOUR OUTPUT ="
./a.out operation_files/operation_file.example | cat -e | tee yours
echo "YOUR RETURN = $?"
echo -n ">> DIFF BETWEEN FILES = "
if [[ `diff expect yours` ]]
then
    echo ""
    diff expect yours
else
    echo " No difference, nice !"
fi
echo ""

echo ""
echo 'TEST 6 : "./a.out operation_file.example2"'
echo ""
echo "EXPECTED OUTPUT ="
./our_micro_paint operation_files/operation_file.example2 | cat -e | tee expect
echo "EXPECTED RETURN = $?"
echo "YOUR OUTPUT ="
./a.out operation_files/operation_file.example2 | cat -e | tee yours
echo "YOUR RETURN = $?"
echo -n ">> DIFF BETWEEN FILES = "
if [[ `diff expect yours` ]]
then
    echo ""
    diff expect yours
else
    echo " No difference, nice !"
fi
echo ""

echo ""
echo 'TEST 7 : "./a.out crash_at_first"'
echo ""
echo "EXPECTED OUTPUT ="
./our_micro_paint operation_files/crash_at_first | cat -e | tee expect
echo "EXPECTED RETURN = $?"
echo "YOUR OUTPUT ="
./a.out operation_files/crash_at_first | cat -e | tee yours
echo "YOUR RETURN = $?"
echo -n ">> DIFF BETWEEN FILES = "
if [[ `diff expect yours` ]]
then
    echo ""
    diff expect yours
else
    echo " No difference, nice !"
fi
echo ""

echo ""
echo 'TEST 8 : "./a.out crash_at_third"'
echo ""
echo "EXPECTED OUTPUT ="
./our_micro_paint operation_files/crash_at_third | cat -e | tee expect
echo "EXPECTED RETURN = $?"
echo "YOUR OUTPUT ="
./a.out operation_files/crash_at_third | cat -e | tee yours
echo "YOUR RETURN = $?"
echo -n ">> DIFF BETWEEN FILES = "
if [[ `diff expect yours` ]]
then
    echo ""
    diff expect yours
else
    echo " No difference, nice !"
fi
echo ""

echo ""
echo 'TEST 9 : "./a.out impossible"'
echo ""
echo "EXPECTED OUTPUT ="
./our_micro_paint operation_files/impossible | cat -e | tee expect
echo "EXPECTED RETURN = $?"
echo "YOUR OUTPUT ="
./a.out operation_files/impossible | cat -e | tee yours
echo "YOUR RETURN = $?"
echo -n ">> DIFF BETWEEN FILES = "
if [[ `diff expect yours` ]]
then
    echo ""
    diff expect yours
else
    echo " No difference, nice !"
fi
echo ""

echo ""
echo 'Execution is over ! Hope it went well for you ;)'