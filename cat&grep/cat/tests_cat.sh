#!/ bin / bash
SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""
TEST_FILE=(
    "tests/test1.txt"
    "tests/test2.txt"
    "tests/test3.txt"
    "tests/test4.txt"
)

s21_cat="./s21_cat"
cat="cat"

flags=(
    "-b"
    "-e"
    "-n"
    "-s"
    "-t"
    "-v"
)

printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "1 PARAMETER"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${TEST_FILE[@]}"
    do
        (( COUNTER++ ))
        TEST1="$var1 $var2"
        
        $s21_cat $TEST1 > test_result_s21_cat.txt
        $cat $TEST1 > test_result_cat.txt
        DIFF_RES="$(diff -s test_result_s21_cat.txt test_result_cat.txt)"
        if [ "$DIFF_RES" == "Files test_result_s21_cat.txt and test_result_cat.txt are identical" ]
            then
                (( SUCCESS++ ))
                echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
            else
                echo "$TEST1" >> log.txt
                (( FAIL++ ))
                echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
        fi
        rm test_result_s21_cat.txt test_result_cat.txt
        
    done
done

printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "1 PARAMETER"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${TEST_FILE[@]}"
    do
       
           
                (( COUNTER++ ))
                TEST1="$var1 $var2"
        
                $s21_cat $TEST1 > test_result_s21_cat.txt
                $cat $TEST1 > test_result_cat.txt
                DIFF_RES="$(diff -s test_result_s21_cat.txt test_result_cat.txt)"
                if [ "$DIFF_RES" == "Files test_result_s21_cat.txt and test_result_cat.txt are identical" ]
                    then
                        (( SUCCESS++ ))
                        echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
                else
                        echo "$TEST1" >> log.txt
                        (( FAIL++ ))
                        echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
                fi
                rm test_result_s21_cat.txt test_result_cat.txt
           
  
     done
done

printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"
##############################

printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"
##############################