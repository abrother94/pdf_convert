#!/bin/bash

get_me_attributes_num()
{
    local name=$1
    count=`cat "$name" | sed -n '/^/,/Actions/p; /Actions/q' | egrep '(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, W, Set-by-create\))' | wc -l`
    echo $count
}



PARAM="$1"
`ls ME_NAME > filelist.txt`

while read filename;
do  
    echo "get form $filename"
    ACT=`sed -i "/.*\([A-Za-z]: [A-Za-z]\).*/,/Actions/ s/: /:  /g" ME_NAME/$filename` 
    #REST=`cat ME_NAME/$filename | sed -e "s/$RELPACE/$RES/g "`
    #RESE=`sed -i  "s/$RELPACE/$RES/g " ME_NAME/$filename`
    param_num=$(get_me_attributes_num "ME_NAME/$filename")
    echo "$param_num"
    #break
    #if ( $PARAM > $param_num ) ;then
#	echo "only have $param_num but ask $PARAM"
#	break
 #   fi
  #  STR=`./get_section.sh "ME_NAME/$filename" "$PARAM"`
   # STR_LEN=${#STR}
   # if (( $STR_LEN > 70 ));then
   # 	echo "[ME_NAME/$filename] STR[$STR] LEN[$STR_LEN]"
   # exit
   # fi
done < filelist.txt
