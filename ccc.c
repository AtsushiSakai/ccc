#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#define BUFLEN 256


FILE *fp;//$B%G%P%C%/MQ%U%!%$%k(B

void error(char *fmt,...){
  va_list args;
  va_start(args,fmt);
  vfprintf(stderr,fmt,args);//$B2?8N$+%(%i!<(B
  fprintf(stderr,"\n");
  va_end(args);
  exit(1);
}

/**
 * @brief $B?tCMMQ$N%"%;%s%V%i$r=PNO$9$k4X?t(B
 *
 * @param n
 *
 */
void compile_number(int n){
  //$B0lHV=i$a$NCM$O(Bn$B$KF~$C$F$$$k(B
  int c;
  while ((c=getc(stdin))!=EOF){
    //$B%9%Z!<%9$N>l9g$OL5;k(B
    if(isspace(c))
      break;
    if(!isdigit(c))
      error("Invalid character in number:'%c'",c);

    fprintf(fp,"%d\n",c);
    fprintf(fp,"%d\n",n);

    n=n*10+(c-'0');//$B7e$r>e$2$FB-$7$F$$$/(B

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
  int c=getc(stdin);//$BI8=`F~NO$+$i$R$H$^$H$^$j$NJ#?tJ8;z$r<hF@(B

  if(isdigit(c)){
    return compile_number(c-'0');//$B%"%9%-!<%3!<%I$G?t;z$r<hF@(B
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

