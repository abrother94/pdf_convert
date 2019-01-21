#!/bin/bash
SECTION="$1"
#echo SECTION[$SECTION]
ITEM="$2"
PARAM="$3"
PARAM1="$4"

LINE_TMP="chapter_line_me_tmp"
G988_TXT="g988.txt"


declare -A matrix_g988_chapter_line_me
matrix_all_g988_chapter_line_count=0

declare -A matrix_chapter_line_me
matrix_all_chapter_line_count=0

declare -A matrix_chapter_line_me_content
matrix_chapter_line_me_content_count=0

declare -A matrix_attributes_mode
matrix_attributes_mode_count=0

collect_g988_me_content_section_line_index()
{
    # 8,9 section refert to ME attribe
    G988_ME_TYPE_NAME=`cat g988.txt | grep "Index" -A200 | egrep '[9]\.[0-9]{1,2}\.[0-9]{1,2}'`

    while IFS=$'\n' read -r one_line ;do
	#echo "one_line[$one_line]"
	matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},"NAME"]=`echo $one_line | awk -F"[9].[0-9]{1,2}.[0-9]{1,2}" '{print $1}' | sed -e 's/ *$//g'| sed -e 's/ /_/g'`
	matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},"ID"]=`echo $one_line | awk -F"[9].[0-9]{1,2}.[0-9]{1,2}" '{print $2}' | sed -e 's/ //g'`
	#echo "[${matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},"NAME"]}][${matrix_g988_chapter_line_me[${matrix_all_g988_chapter_line_count},"ID"]}]"
	matrix_all_g988_chapter_line_count=$((matrix_all_g988_chapter_line_count+1))
    done <<< "$G988_ME_TYPE_NAME"
    #echo "matrix_all_g988_chapter_line_count[$matrix_all_g988_chapter_line_count]"
}


collect_all_content_section_line_index()
{
    while IFS=' ' read -r line_num section me_des;do
	matrix_chapter_line_me[${matrix_all_chapter_line_count},0]=$line_num
	matrix_chapter_line_me[${matrix_all_chapter_line_count},1]=$section
	matrix_chapter_line_me[${matrix_all_chapter_line_count},2]=`echo $me_des | sed -e 's/ /_/g'`
	matrix_all_chapter_line_count=$((matrix_all_chapter_line_count+1))
    done < $LINE_TMP
}

collect_me_content_section_line_index()
{
    # 8,9 section refert to ME attribe
    ME_TYPE_NAME=`cat $LINE_TMP | egrep "[9]{1,2}\.[0-9]{1,2}\.[0-9]{1,2}"`

    while IFS=' ' read -r line_num section me_des;do
	matrix_chapter_line_me_content[${matrix_chapter_line_me_content_count},0]=$line_num
	matrix_chapter_line_me_content[${matrix_chapter_line_me_content_count},1]=$section
	matrix_chapter_line_me_content[${matrix_chapter_line_me_content_count},2]=$me_des
	matrix_chapter_line_me_content_count=$((matrix_chapter_line_me_content_count+1))
    done <<< "$ME_TYPE_NAME"
}


dump_me_setciotn()
{
    local SECTION="$1"
    echo "dump name[$SECTION]"
    local c=0

    for (( c=0; c < "${matrix_all_chapter_line_count}"; c++ ))
    do
	SA="${matrix_chapter_line_me[$c,2]}"
	echo "SA[$SA]"
	DA="${SECTION}"
	if [ "${SA}" == "${DA}" ] ;then
	    echo "match[${matrix_chapter_line_me[$c,0]}]"
	    START=${matrix_chapter_line_me[$c,0]}
	    END=${matrix_chapter_line_me[$(($c+1)),0]}
	    END=$(($END-1))
	    break
	fi
    done

    ENDPAGE="$END"p
    echo [$START][$ENDPAGE]

    FSECTION="${SECTION//[ \/]/_}"
    RES=`cat "$G988_TXT"| sed -n $START,$ENDPAGE > "ME_NAME/$FSECTION"`
}

dump_all_me_1()
{
    local c=0
    echo "dump_all_me count[$matrix_all_g988_chapter_line_count]"
    for (( c=0; c < "${matrix_all_g988_chapter_line_count}"; c++ ))
    do
	NAME=${matrix_g988_chapter_line_me["$c","NAME"]}
	echo "dump_all_me name[$NAME]"
        dump_me_setciotn "${NAME}"
    done
}

dump_all_me()
{
    local c=0
    echo "dump_all_me count[$matrix_chapter_line_me_content_count]"
    for (( c=0; c < "${matrix_chapter_line_me_content_count}"; c++ ))
    do
	NAME=${matrix_chapter_line_me_content["$c",2]}
	echo "dump_all_me name[$NAME]"
        dump_me_setciotn "${NAME}"
    done
}

find_me_class_id()
{
    local me_name="$1"
    #echo "dump name[$me_name]"
    local c=0

    for (( c=0; c < "${matrix_all_g988_chapter_line_count}"; c++ ))
    do
	SA="${matrix_g988_chapter_line_me[$c,"NAME"]}"
	DA="${me_name}"
	if [ "${SA}" == "${DA}" ] ;then
	    echo "${matrix_g988_chapter_line_me[$c,"ID"]}"
	    break
	fi
    done
}



get_attribute_name()
{
    local name="$1"
    local SS='Managed entity id:'
    local ES='Actions'
    # Legnecy method
    #start_line=`cat "$name" | egrep -n -m 1  'Managed entity id:' | awk -F":" '{print $1}'`
    #start_line=`echo  "$start_to_action_content" | egrep -n -m 1  'Managed entity id:' | awk -F":" '{print $1}'`
    # Get from content start to "Action" patten and quit and pipeline#
    # Print "Managed entity id:" line number
    # start_line=`sed '/Action/q' "$name" | egrep -n -m 1  'Managed entity id:' | awk -F":" '{print $1}'`
    #echo start_line[$start_line]
    # Get rid of content before "Managed entiry id: to file end" 
    # content=`tail -n +$start_line "$name"` 
    #echo content[$content]
    local L_PARAM="$2"
    #Latest method
    Attribute_Name=`sed -n "/$SS/,/$ES/p; /$ES/q" "$name" | sed -e 's/\//_/g' | awk -F"\\\\\ {2,5}" '{print $1}' | tr '\n' " " | awk -v L_PARAM="$L_PARAM" -F":" '{print $L_PARAM}' | sed -e 's/^ *//g ; s/ /_/g ; s/-/_/g' `
    echo "$Attribute_Name"
}

get_action()
{
    local name="$1"
    local SS='Actions'
    local ES='Notifications'
    #Action_mode=`sed -n "/$SS/,/$ES/p; /$ES/q" "$name" | sed -e "s/$SS//g" | sed -e "s/$ES//g"`
    Action_mode=`sed -n "/$SS/,/$ES/p; /$ES/q" "$name" | sed -e 's/\//_/g' | awk -F"\\\\\ {2,5}" '{print $1}' | tr '\n' " " | sed -e "s/$SS//g" | sed -e "s/$ES//g" `
    local action_type=`echo "$Action_mode" | tr '[:upper:]' '[:lower:]'`
    echo "$action_type" 
}

get_attribute_mode()
{
    local name="$1"
    local ATTRI1="$2"
    local TYPE="$3"
    local SS='Managed entity id:'
    local ES='Actions'
    local RWP='(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, Set-by-create\)|\(R, W, Set-by-create\)) *(\(mandatory\)|\(optional\)) *(\([0-9]{1,2}(|N) (byte(|s))(|, where N is the number of entries in the table)\))'
    local RWPATTERN='(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, Set-by-create\)|\(R, W, Set-by-create\))'
    local MANPATTERN='(\(mandatory\)|\(optional\))'
    local BYTEPATTERN='(\([0-9]{1,2}(|N) (byte(|s))(|, where N is the number of entries in the table)\))'
    Attribute_Name=`sed -n "/$SS/,/$ES/p; /$ES/q" "$name" | egrep "((^ {1,30})|(^[A-Za-z].*(\ {3}[^A-Za-z0-9\(\)])))"  | sed -e 's/^[A-Za-z].* [^A-Za-z\(\)]//g' |sed -e 's/^ \{1,24\}//g' | tr '\n' " " |  egrep -o "$RWP" `

    #while IFS=' ' read -r RW SET_GET SIZE;do
    while read -r ALL;do
	matrix_attributes_mode_count=$((matrix_attributes_mode_count+1))
	#echo "[$RW] [$SET_GET] [$SIZE]"
	matrix_attributes_mode[$matrix_attributes_mode_count,"RW"]=`echo $ALL |  egrep -o "$RWPATTERN"` 
	matrix_attributes_mode[$matrix_attributes_mode_count,"SET_GET"]=`echo $ALL | egrep -o "$MANPATTERN"`
	matrix_attributes_mode[$matrix_attributes_mode_count,"SIZE"]=`echo $ALL | egrep -o "$BYTEPATTERN"`
	#echo [$matrix_attributes_mode_count]
    done <<< "$Attribute_Name"

    case "${TYPE}" in
	"RW")  
	    #echo "${matrix_attributes_mode[$ATTRI1,"RW"]}"
	    CT="${matrix_attributes_mode[$ATTRI1,"RW"]}"
	    if [ "$CT" == "(R)" ];then
		echo "ATTR_ACCESS_R"
	    elif [ "$CT" == "(W)" ];then
		echo "ATTR_ACCESS_W"
	    elif [ "$CT" == "(R, W)" ];then
		echo "ATTR_ACCESS_RW"
	    elif [ "$CT" == "(W, Set-by-create)" ];then
		echo "ATTR_ACCESS_W_SC"
	    elif [ "$CT" == "(R, Set-by-create)" ];then
		echo "ATTR_ACCESS_R_SC"
	    elif [ "$CT" == "(R, W, Set-by-create)" ];then
		echo "ATTR_ACCESS_RW_SC"
	    fi

	    ;;
	"SET_GET")  
	    echo "${matrix_attributes_mode[$ATTRI1,"SET_GET"]}" | awk -F"[()]" '{print $2}' 
	    ;;
	"SIZE")  
	    echo "${matrix_attributes_mode[$ATTRI1,"SIZE"]}" | awk -F"[()]" '{print $2}' | sed -e 's/ byte[s]*//g'
	    ;;
    esac
}


get_me_attributes_num()
{
    local name="$1"
    local SS='Managed entity id:'
    local ES='Actions'
    local RWP='(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, Set-by-create\)|\(R, W, Set-by-create\)) *(\(mandatory\)|\(optional\)) *(\([0-9]{1,2}(|N) (byte(|s))(|, where N is the number of entries in the table)\))'
    local RWPATTERN='(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, Set-by-create\)|\(R, W, Set-by-create\))'
    local MANPATTERN='(\(mandatory\)|\(optional\))'
    local BYTEPATTERN='(\([0-9]{1,2}(|N) (byte(|s))(|, where N is the number of entries in the table)\))'
    local count=`sed -n "/$SS/,/$ES/p; /$ES/q" "$name" | egrep "((^ {1,30})|(^[A-Za-z].*(\ {3}[^A-Za-z0-9\(\)])))"  | sed -e 's/^[A-Za-z].* [^A-Za-z\(\)]//g' |sed -e 's/^ \{1,24\}//g' | tr '\n' " " |  egrep -o "$RWP" | wc -l`

    echo "$count"
}


#sed -n "/Managed entity id:/,/Action/p; /Action/q" ME_NAME/GEM_ITP | egrep "((^ {1,30})|(^[A-Za-z].*(\ {10}[^A-Za-z\(\)])))"  | sed -e 's/^[A-Za-z].* [^A-Za-z\(\)]//g'


#collect_g988_me_content_section_line_index
#collect_all_content_section_line_index
#collect_me_content_section_line_index
#dump_all_me_1
#get_me_attributes_num "$SECTION"
#get_attribute_name "$SECTION" "$2"
#exit

ITEM="$2"
PARAM="$3"
PARAM1="$4"

show_help()
{
    echo "./get_section.sh ME_NAME attribute_mode [1-16] [RW,SET_GET,SIZE]"
    echo "./get_section.sh ME_NAME attribute_name [1-16]"
    echo "./get_section.sh ME_NAME me_class"
    echo "./get_section.sh ME_NAME me_name"
    echo "./get_section.sh ME_NAME action"
    echo "./get_section.sh ME_NAME attribute_num"
}

if (( $# == 0 ));then 
    show_help 
    exit
fi

case "${ITEM}" in
    "attribute_mode")  
	#RE=`echo $(get_attribute_mode "$SECTION" "$PARAM" "$PARAM1") | awk -F"[()]" '{print $2}'`
	RE=`echo $(get_attribute_mode "$SECTION" "$PARAM" "$PARAM1")`
	echo "$RE"
	;;
    "attribute_name")  
	echo $(get_attribute_name  "$SECTION" "$PARAM")
	;;
    "me_class")  
	collect_g988_me_content_section_line_index
	ME_NAME=`cat $SECTION | egrep "^[9].[0-9]{1,2}.[0-9]{1,2}" | awk -F"^[9].[0-9]{1,2}.[0-9]{1,2}" '{print $2}'| sed -e "s/^ *//g ; s/ /_/g;"`
	echo $(find_me_class_id  "$ME_NAME")
	;;
    "me_name")  
	ME_NAME=`cat $SECTION | egrep "^[9].[0-9]{1,2}.[0-9]{1,2}" | awk -F"^[9].[0-9]{1,2}.[0-9]{1,2}" '{print $2}'| sed -e "s/^ *//g ; s/ /_/g ; s/-/_/g; s/\./_/g"`
	RE=`echo $ME_NAME | sed -e "s/^[0-9A-Za-z]/ME_&/g"`
	echo "$RE"
	;;
    "action")  		
	echo $(get_action "$SECTION")
	;;
    "attribute_num")  		
	echo $(get_me_attributes_num "$SECTION")
	;;
esac


exit

file_line=`wc -l < $LINE_TMP`
file_linep="$file_line"p
org_final_page=`wc -l < "$G988_TXT"`
org_final_pagep="$org_final_page"p
final_line_1st=`sed -n $file_linep $LINE_TMP | awk -e '{print $1}'`

if [ "$START" = "$final_line_1st" ];then
    echo "Final chapter!!"
    echo "[$org_final_pagep]"
fi

START=`cat $LINE_TMP | grep "$SECTION" | awk -e '{print $1}'`
END_tmp=`cat $LINE_TMP | grep -n "$START" | awk -F: '{print $1}'`
ENDNUM=$(($END_tmp + 1))
PAGE_END="$ENDNUM"p
END=`cat $LINE_TMP | sed -n $PAGE_END  | awk '{print $1}' `
END=$(($END-1))
ENDPAGE="$END"p
echo [$START][$ENDPAGE]
`cat "$G988_TXT" | sed -n $START,$ENDPAGE > $SECTION`



#//GET ATTRIBUTE
#sed -n '/Managed entity id/,/Notifications/p' FILENAME


#//Find how many attributes
#cat ONT-G | egrep '(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, W, Set-by-create\))' | wc -l
#//GET Read/Write type
#(\(R\)|\(W\)|\(R, W\)|\(W, Set-by-create\)|\(R, W, Set-by-create\))
#(R)
#(W)
#(R, W)
#(W, Set-by-create) 
#(R, W, Set-by-create)
# echo "(R) (mandatory) (2 bytes)" | egrep -o "(\([1-9nN]{1,2} (byte|bytes)\)|\([A-Za-z]*\))"
#sed -n '/Managed entity id/,/Notifications/p' FI


#\([0-9]{1,100} (byte|bytes)\)

#(1 byte) (8 bytes) (22 bytes)



