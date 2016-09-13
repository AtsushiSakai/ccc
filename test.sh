#!/bin/bash
echo "Tests start"

function test(){
  expected="$1"
  result="$2"
  echo "$result" | ./ccc > tmp.s #アセンブラのコード cccはアセンブラのコードをはく

  #コンパイルチェック
  if [ ! $? ];then
    echo "Failed to comile $result"
    exit
  fi

  #tmp.outという実行ファイルを作る driver.cとtmp.cを使って
  gcc -o tmp.out driver.c tmp.s || exit
  rlt="`./tmp.out`" #実行ファイルを実行

  if [ "$rlt" != "$expected" ]; then
    echo "Test failed $expected extected but got $rlt"
    exit
  fi

}

make -s ccc

#test
test 0 0
test 42 42 

# rm -f tmp.out tmp.s
echo "All tests passed"
