# clean data
rm -r data
mkdir data

# generate data
for nthreads in 1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 159 160
do
  echo "$(date) running asimd microbenchmarks on ${nthreads} cores"
  OMP_NUM_THREADS=${nthreads} OMP_PLACES={0}:${nthreads}:1 ./build/micro_asimd 2>&1 >> "data/scaling_cores_asimd_${nthreads}.txt"
  OMP_NUM_THREADS=${nthreads} OMP_PLACES={0}:${nthreads}:1 ./build/micro_sve 2>&1 >> "data/scaling_cores_sve_${nthreads}.txt"

  echo "$(date) asimd running micro-benchmark on one core with ${nthreads} threads (pinned version)"
  OMP_NUM_THREADS=${nthreads} OMP_PLACES={0} ./build/micro_asimd 2>&1 >> "data/scaling_pinned_threads_${nthreads}.txt"
done
