# Task 5.2:
Anzahl der FLOPs pro Matrix = 2*m*n*k

Matrix Size: 4
Avg. calc time: 1.36835e-06
Sustained GFLOPS: 93543.4

running reference GEMM benchmarks

Matrix Size: 8
Avg. calc time: 1.01166e-05
Sustained GFLOPS: 101220

running reference GEMM benchmarks

Matrix Size: 12
Avg. calc time: 3.31051e-05
Sustained GFLOPS: 104395

running reference GEMM benchmarks

Matrix Size: 16
Avg. calc time: 8.10567e-05
Sustained GFLOPS: 101065

running reference GEMM benchmarks

Matrix Size: 24
Avg. calc time: 0.00026779
Sustained GFLOPS: 103245

running reference GEMM benchmarks

Matrix Size: 32
Avg. calc time: 0.00062697
Sustained GFLOPS: 104528

running reference GEMM benchmarks

Matrix Size: 48
Avg. calc time: 0.00209438
Sustained GFLOPS: 105609

running reference GEMM benchmarks

Matrix Size: 64
Avg. calc time: 0.00499349
Sustained GFLOPS: 104994

# Task 5.3:

## Without optimization flags:

benchmarking fixed matrix size kernels
Calculating reference kernel: 
dur: 3.09594
Avg. calc time: 0.000619188
Sustained GFLOPS: 105842

Calculating fixed mnk kernel: 
dur: 3.08867
Avg. calc time: 0.000617735
Sustained GFLOPS: 106091

Calculating fixed nkm kernel: 
dur: 2.41392
Avg. calc time: 0.000482783
Sustained GFLOPS: 135746

## with O2:

benchmarking fixed matrix size kernels
Calculating reference kernel: 
dur: 3.20062
Avg. calc time: 0.000640125
Sustained GFLOPS: 102380

Calculating fixed mnk kernel: 
dur: 2.84518
Avg. calc time: 0.000569037
Sustained GFLOPS: 115170

Calculating fixed nkm kernel: 
dur: 2.43316
Avg. calc time: 0.000486632
Sustained GFLOPS: 134673

## with 03:

benchmarking fixed matrix size kernels
Calculating reference kernel: 
dur: 3.08229
Avg. calc time: 0.000616457
Sustained GFLOPS: 106311

Calculating fixed mnk kernel: 
dur: 3.049
Avg. calc time: 0.0006098
Sustained GFLOPS: 107471

Calculating fixed nkm kernel: 
dur: 2.42188
Avg. calc time: 0.000484376
Sustained GFLOPS: 135300

# Task 5.4
