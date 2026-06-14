printf("This is a backslash: \\, single quote: \', double quote: \" and "
       "question mark: \?, with null character at the end\n"
       "\0(this part will be ignored)");
putchar('\''); /* putchar('''); -> error */
printf("??!\n" /* you need to use backslash in C90 to avoid trigraph */
       "\?\?!\n");
