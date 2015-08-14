#/bin/bash
for i in {0..9}
do
  in="baj"
  in+=$i
  in+=".in" 
  time cat $in | ./../a.out > tmp
  echo $i
  out="baj"
  out+=$i
  out+=".out"
  diff tmp $out 
done
