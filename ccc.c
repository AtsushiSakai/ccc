#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#define BUFLEN 256


FILE *fp;//デバック用ファイル

void error(char *fmt,...){
  va_list args;
  va_start(args,fmt);
  vfprintf(stderr,fmt,args);//何故かエラー
  fprintf(stderr,"\n");
  va_end(args);
  exit(1);
}

/**
 * @brief 数値用のアセンブラを出力する関数
 *
 * @param n
 *
 */
void compile_number(int n){
  //一番初めの値はnに入っている
  int c;
  while ((c=getc(stdin))!=EOF){
    //スペースの場合は無視
    if(isspace(c))
      break;
    if(!isdigit(c))
      error("Invalid character in number:'%c'",c);

    fprintf(fp,"%d\n",c);
    fprintf(fp,"%d\n",n);

    n=n*10+(c-'0');//桁を上げて足していく

    fprintf(fp,"%d\n",n);
  }

  printf("\t.text\n\t"
      ".global intfn\n"
      "intfn:\n\t"
      "mov $%d, %%rax\n\t"
      "ret\n",n);
}

void compile_string(int c){
  char buf[BUFLEN];
  int i=0;
  buf[i++]=c;

  for(;;){
    int c=getc(stdin);
    if (c==EOF){
      /* error("Unterminated string"); */
      break;
    }
    else if(c=='\n'){
      continue;
    }

    buf[i++]=c;
    if(i==BUFLEN-1) error("String too long");
  }

  buf[i]='\0';
  printf("\t.data\n"
      ".mydata:\n\t"
      ".string \"%s\"\n\t"
      ".text\n\t"
      ".global stringfn\n"
      "stringfn:\n\t"
      "lea .mydata(%%rip), %%rax\n\t"
      "ret\n",buf);

}

void Compile(void){
  int c=getc(stdin);//標準入力からひとまとまりの複数文字を取得

  if(isdigit(c)){
    return compile_number(c-'0');//アスキーコードで数字を取得
  }
  else{
    return compile_string(c);
  }


  error("Don't know how to handle '%c'",c);
}

int main(int argc, char **argv){
  fp = fopen( "debug.txt", "w" );
  Compile();
  fclose(fp);
  return 0;
}

