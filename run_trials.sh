# This script runs every schedule on all 10 datafiles and puts the result into a file within ./results

cd results
rm -f output

QUANTUM="100"

for SCHEDULE in fifo sjf rr
do 
  echo $SCHEDULE
  rm -f ${SCHEDULE}_results
  touch ${SCHEDULE}_results
  for VARIABLE in 0 1 2 3 4 5 6 7 8 9
  do
    if [ $SCHEDULE != "rr" ]
    then
      ../${SCHEDULE} ../data_$VARIABLE > output
      # echo "../${SCHEDULE} ../data_$VARIABLE > output"
    else
      ../${SCHEDULE} $QUANTUM ../data_$VARIABLE > output
      # echo "../${SCHEDULE} $QUANTUM ../data_$VARIABLE > output"
    fi
    cp ${SCHEDULE}_results tmp
    cat output tmp > ${SCHEDULE}_results
  done
done
rm -f tmp
rm -f output
