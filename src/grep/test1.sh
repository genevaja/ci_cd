#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0

echo > log.txt

TEST1='TEST1'
./s21_grep -e "[a-z]" Makefile text3.txt > test21_grep_e.txt
grep -e "[a-z]" Makefile text3.txt > test_grep_e.txt

DIFF_RES="$(diff test21_grep_e.txt test_grep_e.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1 FAILED:
        ./s21_grep -e '[a-z]' Makefile text3.txt > test21_grep_e.txt
        grep -e '[a-z]' Makefile text3.txt > test_grep_e.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST2='TEST2'
./s21_grep -i "[a-z]" Makefile text3.txt > test21_grep_i.txt
grep -i "[a-z]" Makefile text3.txt > test_grep_i.txt

DIFF_RES="$(diff test21_grep_i.txt test_grep_i.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST2 FAILED: 
        ./s21_grep -i '[a-z]' Makefile text3.txt > test21_grep_i.txt
        grep -i '[a-z]' Makefile text3.txt > test_grep_i.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST3='TEST3'
./s21_grep -vn "[a-z]" Makefile text3.txt > test21_grep_vn.txt
grep -vn "[a-z]" Makefile text3.txt > test_grep_vn.txt

DIFF_RES="$(diff test21_grep_vn.txt test_grep_vn.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST3 FAILED:
        ./s21_grep -vn '[a-z]' Makefile text3.txt > test21_grep_vn.txt
        grep -vn '[a-z]' Makefile text3.txt > test_grep_vn.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST4='TEST4'
./s21_grep -c "[a-z]" Makefile text3.txt > test21_grep_c.txt
grep -c "[a-z]" Makefile text3.txt > test_grep_c.txt

DIFF_RES="$(diff test21_grep_c.txt test_grep_c.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST4 FAILED:
        ./s21_grep -c '[a-z]' Makefile text3.txt > test21_grep_c.txt
        grep -c '[a-z]' Makefile text3.txt > test_grep_c.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST5='TEST5'
./s21_grep -l "[a-z]" Makefile text3.txt > test21_grep_l.txt
grep -l "[a-z]" Makefile text3.txt > test_grep_l.txt

DIFF_RES="$(diff test21_grep_l.txt test_grep_l.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST5 FAILED:
        ./s21_grep -l '[a-z]' Makefile text3.txt > test21_grep_l.txt
        grep -l '[a-z]' Makefile text3.txt > test_grep_l.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST6='TEST6'
./s21_grep -n "[a-z]" Makefile text3.txt > test21_grep_n.txt
grep -n "[a-z]" Makefile text3.txt > test_grep_n.txt

DIFF_RES="$(diff test21_grep_n.txt test_grep_n.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST6 FAILED:
        ./s21_grep -n '[a-z]' Makefile text3.txt > test21_grep_n.txt
        grep -n '[a-z]' Makefile text3.txt > test_grep_n.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST7='TEST7'
./s21_grep -h "[a-z]" Makefile text3.txt > test21_grep_h.txt
grep -h "[a-z]" Makefile text3.txt > test_grep_h.txt

DIFF_RES="$(diff test21_grep_h.txt test_grep_h.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST7 FAILED:
        ./s21_grep -h '[a-z]' Makefile text3.txt > test21_grep_h.txt
        grep -h '[a-z]' Makefile text3.txt > test_grep_h.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST8='TEST8'
./s21_grep -s "[a-z]" Makefile text3.txt text10.txt > test21_grep_s.txt
grep -s "[a-z]" Makefile text3.txt text10.txt > test_grep_s.txt

DIFF_RES="$(diff test21_grep_s.txt test_grep_s.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST8 FAILED:
        ./s21_grep -s '[a-z]' Makefile text3.txt > test21_grep_s.txt
        grep -s '[a-z]' Makefile text3.txt > test_grep_s.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST9='TEST9'
./s21_grep -f text4.txt Makefile text3.txt text10.txt > test21_grep_f.txt
grep -f text4.txt Makefile text3.txt text10.txt > test_grep_f.txt

DIFF_RES="$(diff test21_grep_f.txt test_grep_f.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST9 FAILED:
        ./s21_grep -f text4.txt Makefile text3.txt text10.txt > test21_grep_f.txt
        grep -f text4.txt Makefile text3.txt text10.txt > test_grep_f.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST10='TEST10'
./s21_grep -o '[a-z]' Makefile text3.txt > test21_grep_o.txt
grep -o '[a-z]' Makefile text3.txt > test_grep_o.txt

DIFF_RES="$(diff test21_grep_o.txt test_grep_o.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST10 FAILED:
        ./s21_grep -o '[a-z]' Makefile text3.txt > test21_grep_o.txt
        grep -o '[a-z]' Makefile text3.txt > test_grep_o.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST11='TEST11'
./s21_grep -iv '[a-z]' Makefile text3.txt > test21_grep_iv.txt
grep -iv '[a-z]' Makefile text3.txt > test_grep_iv.txt

DIFF_RES="$(diff test21_grep_iv.txt test_grep_iv.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST11 FAILED:
        ./s21_grep -iv '[a-z]' Makefile text3.txt > test21_grep_iv.txt
        grep -iv '[a-z]' Makefile text3.txt > test_grep_iv.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST12='TEST12'
./s21_grep -ic '[a-z]' Makefile text3.txt > test21_grep_ic.txt
grep -ic '[a-z]' Makefile text3.txt > test_grep_ic.txt

DIFF_RES="$(diff test21_grep_ic.txt test_grep_ic.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST14 FAILED:
        ./s21_grep -ic '[a-z]' Makefile text3.txt > test21_grep_ic.txt
        grep -ic '[a-z]' Makefile text3.txt > test_grep_ic.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST13='TEST13'
./s21_grep -in '[a-z]' Makefile text3.txt > test21_grep_in.txt
grep -in '[a-z]' Makefile text3.txt > test_grep_in.txt

DIFF_RES="$(diff test21_grep_in.txt test_grep_in.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST13 FAILED:
        ./s21_grep -in '[a-z]' Makefile text3.txt > test21_grep_in.txt
        grep -in '[a-z]' Makefile text3.txt > test_grep_in.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST14='TEST14'
./s21_grep -no "[a-z]" Makefile text3.txt > test21_grep_no.txt
grep -no "[a-z]" Makefile text3.txt > test_grep_no.txt

DIFF_RES="$(diff test21_grep_no.txt test_grep_no.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "
        $TEST14 FAILED: 
        ./s21_grep -no '[a-z]' Makefile text3.txt > test21_grep_no.txt
        grep -no '[a-z]' Makefile text3.txt > test_grep_no.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

TEST15='TEST15'
# Multi flags
./s21_grep -insh "[a-z]" Makefile text3.txt text10.txt > test21_grep_insh.txt
grep -insh "[a-z]" Makefile text3.txt text10.txt > test_grep_insh.txt

DIFF_RES="$(diff test21_grep_insh.txt test_grep_insh.txt)"
if [ "$DIFF_RES" == "" ]
then
    (( COUNTER_SUCCESS++ ))
else
    echo "
        $TEST15 FAILED: 
        ./s21_grep -insh '[a-z]' Makefile text3.txt text10.txt > test21_grep_insh.txt
        grep -insh '[a-z]' Makefile text3.txt text10.txt > test_grep_insh.txt" >> log.txt
        echo "1"
        (( COUNTER_FAIL++ ))
fi

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
