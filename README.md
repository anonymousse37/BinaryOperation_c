# BinaryOperation_c
Provides a library of functiuns to handle binary operations

- The project has been developped using CodeBlocks/Windows x64
- A doxygen documentation is supplied ( around 30MB unzipped ) with graphviz so you have dependency graphs 
- There is several .c/.h files but the files that matter are bin.c/bin.h.
  - You will find there the functions
  - There is a sample function 'binw_example' 
  - You can call it in the main function so you can have a fast overview of what you can do with it
- The code has been tested with Dr Memory, there is some memory leaks but at this point i'm not able to say if there are false positives.
- The library is made to work with 8 bytes words 
  - It handle signed words
  - It handles carry overflow until 8 byte ( long long int )
  - What you can do with this library is :
    - Addition 
    - Substraction 
    - Multiplication 
    - AND/OR/XOR and more 
    - Decimal-binary and binary-decimal conversion 
    - String-binary and binary-string conversion
- A log file is generated at the execution ( logger.txt ). It will logs errors, for example when a carry overflow occurs.

- To run the project, you need to open BIN.cbp and compile it.
- main.c already calls binw_example with the logging enabled
- That's all you need to do. A prompt will appear with the results of the samples ( check sample.png )
- You might have warnings due to the %lld format in printf. Depends of your gcc options but it is 'irrelevant' and will not be a problem.

- I'm really open to suggestions in order to improve the code
- I'm really open to your feedbacks ( what you think, did it help, ... )
- Thank you for reading this !


For example, this is how to realize and OR operation between two binary words

```
binw_set_sz(); // The first function to call. It sets the size of the binary words. Default is the size of long long int i.e 64 bits
t_binw *b3 = NULL;
t_binw *b4 = NULL;
t_binw *b5 = NULL;
long long int d3 = 0;
long long int d4 = 0;
long long int d5 = 0;
if ( (b3 = binw_create_random()) )
{
   binw_display(b3, "b3"); 
   printf(" = %lld", binw_to_dec(b3));
   if ( (b4 = binw_create_random()) )
   {
      binw_display(b4, "b4"); printf(" = %lld",binw_to_dec(b4));
      if ( (b5 = binw_or(b3,b4)) )
      {
         d5=binw_to_dec(b5);
         binw_display(b5, "b5=b2 OR b3"), printf(" = %lld", d5);
         binw_destroy(b5);
      }
      else printf("\nb5 is NULL");
      binw_destroy(b4);
    }
    binw_destroy(b3);
}
```
