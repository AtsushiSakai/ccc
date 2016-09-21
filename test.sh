#!/bin/bash
echo "Tests start"

function compile(){
  echo "$1" | ./ccc > tmp.s

  #コンパイルチェック
  if [ $? -ne 0 ]; then
    echo "Failed to comile $1"
    exit
  fi

  #tmp.outという実行ファイルを作る driver.cとtmp.cを使って
  gcc -o tmp.out driver.c tmp.s || exit

  if [ $? -ne 0 ]; then
    echo "GCC failed"
    exit
  fi

}

function test(){
  expected="$1"
  result="$2"
  echo $result
  compile "$expected"

  rlt="`./tmp.out`" #実行ファイルを実行して、標準出力を取得

  if [ "$rlt" != "$expected" ]; then
    echo "Test failed $expected extected but got $rlt"
    exit
  fi

}

make -s ccc

#test
test 0 0
test 42 42 

test abs '"abc"'

rm -f tmp.out tmp.s
echo "All tests passed"
