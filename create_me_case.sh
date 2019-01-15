#!/bin/bash

get_me_attributes_section()
{
    local name=$1
    count=`sed '/Actions/q' "$name"`
    echo $count
}

FILELIST="./E_OMCI/src/S_ME/"
`ls $FILELIST > case.txt`

while read filename;
do  
    echo "$filename"
done < case.txt
