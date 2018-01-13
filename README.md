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

- I'm really open to suggestions to improve the code
- I'm really open to your feeds ( what you think, did it help, ... )
- Thank you for reading this
