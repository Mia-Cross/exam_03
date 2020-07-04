#!/bash

REF_DIR="my_micro_paint4"
TEST_DIR="my_micro_paint5"

cd $TEST_DIR
gcc -Wall -Wextra -Werror *.c *.h
echo "Preparing output file..."

echo "=== ./a.out ===" > out
./a.out
echo "RETURN = $?" >> out
./a.out | cat -e >> out
echo "1"

echo "=== ./a.out ../my_file ../operation ===" >> out
./a.out ../my_file ../operation_file.example
echo "RETURN = $?" >> out
./a.out ../my_file ../operation_file.example | cat -e >> out
echo "2"

echo "=== ./a.out hello ===" >> out
./a.out hello
echo "RETURN = $?" >> out
./a.out hello | cat -e >> out
echo "3"

echo "=== ./a.out ../my_file ===" >> out
./a.out ../my_file
echo "RETURN = $?" >> out
./a.out ../my_file | cat -e >> out
echo "4"

echo "=== ./a.out ../operation_file.example ===" >> out
./a.out ../operation_file.example
echo "RETURN = $?" >> out
./a.out ../operation_file.example | cat -e >> out
echo "5"

echo "=== ./a.out ../operation_file.example2 ===" >> out
./a.out ../operation_file.example2
echo "RETURN = $?" >> out
./a.out ../operation_file.example2 | cat -e >> out
echo "6"

echo "=== ./a.out ../crash_at_first ===" >> out
./a.out ../crash_at_first
echo "RETURN = $?" >> out
./a.out ../crash_at_first | cat -e >> out
echo "7"

echo "=== ./a.out ../crash_at_third ===" >> out
./a.out ../crash_at_third
echo "RETURN = $?" >> out
./a.out ../crash_at_third | cat -e >> out
echo "8"

echo "=== ./a.out ../impossible ===" >> out
./a.out ../impossible
echo "RETURN = $?" >> out
./a.out ../impossible | cat -e >> out

echo "Execution is over ! Now let's diff..."

diff out ../$REF_DIR/out

#Cleanup
#rm a.out *.gch

echo ""
echo "I told you everything I know ! BYE UwU"