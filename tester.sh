#!/bash

REF_DIR="my_micro_paint4"
TEST_DIR="my_micro_paint6"

cd $TEST_DIR
gcc -Wall -Wextra -Werror *.c *.h
echo "Preparing output file..."

echo "=== ./a.out ===" > out
./a.out
echo "RETURN = $?" >> out
./a.out | cat -e >> out
echo "1, expected Error: argument"

echo "=== ./a.out ../my_file ../operation ===" >> out
./a.out ../my_file ../operation_file.example
echo "RETURN = $?" >> out
./a.out ../my_file ../operation_file.example | cat -e >> out
echo "2, expected Error: argument$"

echo "=== ./a.out hello ===" >> out
./a.out hello
echo "RETURN = $?" >> out
./a.out hello | cat -e >> out
echo "3, expect Error: Operation file corrupted"

echo "=== ./a.out ../my_file ===" >> out
./a.out ../my_file
echo "RETURN = $?" >> out
./a.out ../my_file | cat -e >> out
echo "4, expected to work"

echo "=== ./a.out ../operation_file.example ===" >> out
./a.out ../operation_file.example
echo "RETURN = $?" >> out
./a.out ../operation_file.example | cat -e >> out
echo "5, expected to work"

echo "=== ./a.out ../operation_file.example2 ===" >> out
./a.out ../operation_file.example2
echo "RETURN = $?" >> out
./a.out ../operation_file.example2 | cat -e >> out
echo "6, expected to work"

echo "=== ./a.out ../crash_at_first ===" >> out
./a.out ../crash_at_first
echo "RETURN = $?" >> out
./a.out ../crash_at_first | cat -e >> out
echo "7, expect Error: Operation file corrupted"

echo "=== ./a.out ../crash_at_third ===" >> out
./a.out ../crash_at_third
echo "RETURN = $?" >> out
./a.out ../crash_at_third | cat -e >> out
echo "8, expect Error: Operation file corrupted"

echo "=== ./a.out ../impossible ===" >> out
./a.out ../impossible
echo "RETURN = $?" >> out
./a.out ../impossible | cat -e >> out
echo "9, expect Error: Operation file corrupted"
echo ""

echo "Execution is over ! Now let's diff..."
echo ""
diff out ../$REF_DIR/out

#Cleanup
#rm a.out *.gch

echo ""
echo "I told you everything I know ! BYE UwU"