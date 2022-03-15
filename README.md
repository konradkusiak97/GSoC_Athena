# GSoC_Athena
Results for the warm up excersize for Google Summer of code 2022 application

## Exercise 1
Setting up the DPC++ compiler, compiling and running the vector addition and matrix multiplication examples.

Vector Addition:

```
[konradd-Flow@fedora vector-add]$ source /opt/software/intel/oneapi/setvars.sh 
 
:: initializing oneAPI environment ...
   bash: BASH_VERSION = 5.1.8(1)-release
   args: Using "$@" for setvars.sh arguments: 
:: advisor -- latest
:: ccl -- latest
:: compiler -- latest
:: debugger -- latest
:: dev-utilities -- latest
:: dpcpp-ct -- latest
:: dpl -- latest
:: ipp -- latest
:: ippcp -- latest
:: ipp -- latest
:: mkl -- latest
:: mpi -- latest
:: tbb -- latest
:: vpl -- latest
:: vtune -- latest
:: oneAPI environment initialized ::
 
[konradd-Flow@fedora vector-add]$ make all
dpcpp -O2 -g -std=c++17 -o vector-add-buffers src/vector-add-buffers.cpp
[konradd-Flow@fedora vector-add]$ ls
License.txt    Makefile.win.fpga  third-party-programs.txt    vector-add-usm.vcxproj
Makefile       README.md          vector-add-buffers
Makefile.fpga  sample.json        vector-add-buffers.vcxproj
Makefile.win   src                vector-add.sln
[konradd-Flow@fedora vector-add]$ ./vector-add-buffers 
Running on device: AMD Ryzen 7 5800HS with Radeon Graphics         
Vector size: 10000
[0]: 0 + 0 = 0
[1]: 1 + 1 = 2
[2]: 2 + 2 = 4
...
[9999]: 9999 + 9999 = 19998
Vector add successfully completed on device.
```

Matrix multiplication:

```
[konradd-Flow@fedora matrix_mul]$ make all
dpcpp -std=c++17 -g -o matrix_mul_dpc src/matrix_mul_dpcpp.cpp 
[konradd-Flow@fedora matrix_mul]$ ls
License.txt  Makefile.win    matrix_mul_dpcpp.vcxproj  README.md    src
Makefile     matrix_mul_dpc  matrix_mul.sln            sample.json  third-party-programs.txt
[konradd-Flow@fedora matrix_mul]$ ./matrix_mul_dpc 
Device: AMD Ryzen 7 5800HS with Radeon Graphics         
Problem size: c(150,600) = a(150,300) * b(300,600)
Result of matrix multiplication using DPC++: Success - The results are correct!
[konradd-Flow@fedora matrix_mul]$
```