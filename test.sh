#!/bin/bash
echo "Tests start"

function test(){
  expected="$1"
  result="$2"
  echo "$result" | ./ccc > tmp.s

  #コンパイルチェック
  if [ ! $? ];then
    echo "Failed to comile $result"
    exit
  fi

  gcc -o tmp.out driver.c tmp.s || exit
}


make -s ccc

test 0 0

rm -f tmp.out tmp.s
echo "All tests passed"
