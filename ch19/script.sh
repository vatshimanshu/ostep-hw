#! /bin/bash
gcc tlb.c -o tlb -std=c99
i=1
while [[ $i -le 2048 ]] ; do
   ./tlb $i 5000000
  (( i *= 2 ))
done
