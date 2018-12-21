#!/bin/bash
`ls ME_NAME > filelist.txt`

while read filename;
do  
    echo "$filename"
    ./get_section.sh "ME_NAME/$filename"; 
done < filelist.txt
