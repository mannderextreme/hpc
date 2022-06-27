# clean plots
rm -r plots
mkdir plots

echo "#threads GFLOPS" > plots/scaling_cores.csv

for nthreads in 1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 159 160
do
  peak_asimd_fmadd_sp=$(awk 'NR==5' data/scaling_cores_${nthreads}.txt | awk '{print $2}')
  echo ${nthreads} ${peak_asimd_fmadd_sp} >> plots/scaling_cores_peak_asimd_fmadd_sp.csv

  peak_asimd_fmadd_dp=$(awk 'NR==8' data/scaling_cores_${nthreads}.txt | awk '{print $2}')
  echo ${nthreads} ${peak_asimd_fmadd_dp} >> plots/scaling_cores_peak_asimd_fmadd_dp.csv

  peak_asimd_fmla_sp=$(awk 'NR==11' data/scaling_cores_${nthreads}.txt | awk '{print $2}')
  echo ${nthreads} ${peak_asimd_fmla_sp} >> plots/scaling_cores_peak_asimd_fmla_sp.csv

  peak_asimd_fmla_dp=$(awk 'NR==14' data/scaling_cores_${nthreads}.txt | awk '{print $2}')
  echo ${nthreads} ${peak_asimd_fmla_dp} >> plots/scaling_cores_peak_asimd_fmla_dp.csv
done

for bench in scaling_cores_peak_asimd_fmadd_sp scaling_cores_peak_asimd_fmadd_dp scaling_cores_peak_asimd_fmla_sp scaling_cores_peak_asimd_fmla_dp
do
  for type in pdf txt
  do
    if [[ ${type} == "pdf" ]]
    then
      terminal=pdf
    else
      terminal=dumb
    fi

  #awk '{print $2}' plots/${bench}.csv | \
  cat   plots/${bench}.csv | gnuplot -p -e "set terminal ${terminal} noenhanced; set xlabel '#cores'; plot '<cat' with lp title 'GFLOPS (${bench})'" > plots/${bench}_scaling_cores.${type}
  done
done
