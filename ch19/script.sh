#! /bin/bash
gcc tlb.c -o tlb
i=1
while [[ $i -le 2048 ]] ; do
   ./tlb $i 500000000
  (( i *= 2 ))
done