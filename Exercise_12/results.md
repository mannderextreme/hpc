# 12.1 Triad parallel

# 12.1.2. Results for different array sizes

1024: Overhead for parallelization probably quite big --> worse performance than triad_simple <br>
1024*1024: Overhead is worth it because of big amount of calculations --> much better performance than triad_simple<br>
512*1024*1024: amount of data is now too big again, performance gets worse (amaunt of parallelization is fixed --> finite performance boost + overhead) --> still better performance than simple though<br>
512*1024*1024*1024: data is too big for memory --> bad_alloc / I took the wrong value first, tried it with 2*1024*1024*1024, same result<br>

        [hgf_rlx5119@ftp-x86n6 Exercise_11]$ OMP_NUM_THREADS=32 ./build/auto_vec 1024 100
        working with:
        N_VALUES: 1024; this means 0.00390625 MiB per array
        N_REPEATS: 100
        benchmarking triad_simple
        performance:
            duration: 1.572e-05 seconds
            GFLOPS: 13.028
            GiB/s: 72.7996
        benchmarking triad_parallel
        number of values: 1024
        performance:
            duration: 0.000542105 seconds
            GFLOPS: 0.377787
            GiB/s: 2.11105
        benchmarking triad_parallel
        number of values: 1024^2
        performance:
            duration: 0.00123006 seconds
            GFLOPS: 170.492
            GiB/s: 952.699
        benchmarking triad_with_parallel
        number of values: 512*1024^2
        performance:
            duration: 5.65642 seconds
            GFLOPS: 18.9827
            GiB/s: 106.074
        benchmarking triad_parallel
        number of values: 512*1024^3
        terminate called after throwing an instance of 'std::bad_alloc'
        what():  std::bad_alloc
        Aborted (core dumped)

# 12.1.3.1 Twice the amount of threads using OMP_NUM_THREADS
OMP_NUM_THREADS allows us to set the amount of threads the maschine should use. 

        [hgf_rlx5119@ftp-x86n6 Exercise_11]$ OMP_NUM_THREADS=64 ./build/auto_vec 1024 10000
        working with:
        N_VALUES: 1024; this means 0.00390625 MiB per array
        N_REPEATS: 10000
        benchmarking triad_simple
        performance:
            duration: 0.00096786 seconds
            GFLOPS: 21.1601
            GiB/s: 118.241
        benchmarking triad_parallel
        number of values: 1024
        performance:
            duration: 0.0487348 seconds
            GFLOPS: 0.420233
            GiB/s: 2.34824
        benchmarking triad_parallel
        number of values: 1024^2
        performance:
            duration: 0.0960207 seconds
            GFLOPS: 218.406
            GiB/s: 1220.44
        benchmarking triad_with_parallel
        number of values: 512*1024^2
        performance:
            duration: 275.462 seconds
            GFLOPS: 38.9797
            GiB/s: 217.816
        benchmarking triad_parallel
        number of values: 512*1024^3
        terminate called after throwing an instance of 'std::bad_alloc'
        what():  std::bad_alloc
        Aborted (core dumped)

# 12.1.3.2 Setting parallelization to specific cores (- threads possible as well)

OMP_PLACES enables the user to bind parallelization to physical cores or physical threads. Even allowing to define which cores/threads to the machine uses. Default option apparently is cores. 
        [hgf_rlx5119@ftp-x86n6 Exercise_11]$ KMP_AFFINITY=FALSE OMP_PLACES=threads OMP_DISPLAY_ENV=TRUE ./build/auto_vec 1024 100
        working with:
        N_VALUES: 1024; this means 0.00390625 MiB per array
        N_REPEATS: 100
        benchmarking triad_simple
        OMP: Warning #58: KMP_AFFINITY: parameter invalid, ignoring "FALSE".

        OPENMP DISPLAY ENVIRONMENT BEGIN
        _OPENMP='201611'
        [host] OMP_AFFINITY_FORMAT='OMP: pid %P tid %i thread %n bound to OS proc set {%A}'
        [host] OMP_ALLOCATOR='omp_default_mem_alloc'
        [host] OMP_CANCELLATION='FALSE'
        [host] OMP_DEBUG='disabled'
        [host] OMP_DEFAULT_DEVICE='0'
        [host] OMP_DISPLAY_AFFINITY='FALSE'
        [host] OMP_DISPLAY_ENV='TRUE'
        [host] OMP_DYNAMIC='FALSE'
        [host] OMP_MAX_ACTIVE_LEVELS='1'
        [host] OMP_MAX_TASK_PRIORITY='0'
        [host] OMP_NESTED: deprecated; max-active-levels-var=1
        [host] OMP_NUM_TEAMS='0'
        [host] OMP_NUM_THREADS='1'
        [host] OMP_PLACES='threads'
        [host] OMP_PROC_BIND='spread'
        [host] OMP_SCHEDULE='static'
        [host] OMP_STACKSIZE='4M'
        [host] OMP_TARGET_OFFLOAD=DEFAULT
        [host] OMP_TEAMS_THREAD_LIMIT='0'
        [host] OMP_THREAD_LIMIT='2147483647'
        [host] OMP_TOOL='enabled'
        [host] OMP_TOOL_LIBRARIES: value is not defined
        [host] OMP_WAIT_POLICY='PASSIVE'
        OPENMP DISPLAY ENVIRONMENT END


        performance:
            duration: 2.394e-05 seconds
            GFLOPS: 8.55472
            GiB/s: 47.8032
        benchmarking triad_parallel
        number of values: 1024
        performance:
            duration: 5.7479e-05 seconds
            GFLOPS: 3.56304
            GiB/s: 19.91
        benchmarking triad_parallel
        number of values: 1024^2
        performance:
            duration: 0.0142478 seconds
            GFLOPS: 14.7191
            GiB/s: 82.2495
        benchmarking triad_with_parallel
        number of values: 512*1024^2
        performance:
            duration: 17.5735 seconds
            GFLOPS: 6.11001
            GiB/s: 34.1423
        benchmarking triad_parallel
        number of values: 512*1024^3
        terminate called after throwing an instance of 'std::bad_alloc'
        what():  std::bad_alloc
        Aborted (core dumped)

# 12.1.3.3 Displaying OMP environment
OMP_ENV lets us see information about OMP environment variables. For example how many threads are in use or if debugging is enabled. 

        OPENMP DISPLAY ENVIRONMENT BEGIN
        _OPENMP='201611'
        [host] OMP_AFFINITY_FORMAT='OMP: pid %P tid %i thread %n bound to OS proc set {%A}'
        [host] OMP_ALLOCATOR='omp_default_mem_alloc'
        [host] OMP_CANCELLATION='FALSE'
        [host] OMP_DEBUG='disabled'
        [host] OMP_DEFAULT_DEVICE='0'
        [host] OMP_DISPLAY_AFFINITY='FALSE'
        [host] OMP_DISPLAY_ENV='TRUE'
        [host] OMP_DYNAMIC='FALSE'
        [host] OMP_MAX_ACTIVE_LEVELS='1'
        [host] OMP_MAX_TASK_PRIORITY='0'
        [host] OMP_NESTED: deprecated; max-active-levels-var=1
        [host] OMP_NUM_TEAMS='0'
        [host] OMP_NUM_THREADS='64'
        [host] OMP_PLACES='cores'
        [host] OMP_PROC_BIND='intel'
        [host] OMP_SCHEDULE='static'
        [host] OMP_STACKSIZE='4M'
        [host] OMP_TARGET_OFFLOAD=DEFAULT
        [host] OMP_TEAMS_THREAD_LIMIT='0'
        [host] OMP_THREAD_LIMIT='2147483647'
        [host] OMP_TOOL='enabled'
        [host] OMP_TOOL_LIBRARIES: value is not defined
        [host] OMP_WAIT_POLICY='PASSIVE'
        OPENMP DISPLAY ENVIRONMENT END