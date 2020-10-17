#!/bin/bash
end=$((SECONDS+100))
a=0
while [ $SECONDS -lt $end ]; do
openssl enc -aes-256-ecb -in encrypt.txt -out encrypt.txt.enc -K 6162636465666768696a6b6c6d6e6f70 
let "a=1+a"
done
echo $a
