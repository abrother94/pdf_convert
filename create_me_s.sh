#!/bin/bash
SECTION="$1"
OUTPUT_PATH="E_OMCI/src/S_ME"
CID=`./get_section.sh "$SECTION" me_class`
ME_NAME=`./get_section.sh "$SECTION" me_name`
ATT_MODE_T_AC=`./get_section.sh "$SECTION" action` 
ATTRIB_NUM=`./get_section.sh "$SECTION" attribute_num`


OUTPUT_FILE_NAME="$CID"_"$ME_NAME"
OUTPUT_FILE="$OUTPUT_PATH/$OUTPUT_FILE_NAME"

echo "CID[$CID]"
echo "ME_NAME[$ME_NAME]"
echo "ATTRIB_NUM[$ATTRIB_NUM]"
echo "OUTPUT_FILE[$OUTPUT_FILE]"

J_B_START()
{
    echo "{" >> ${OUTPUT_FILE}
}
J_B_END()
{
    echo "}" >> ${OUTPUT_FILE}
}

J_COMMA()
{
    echo "," >> ${OUTPUT_FILE}
}

J_A_START()
{
    echo "\"Attrs_info\":[" >> ${OUTPUT_FILE}
}

J_A_END()
{
    echo "]" >> ${OUTPUT_FILE}
}

BASIC_SET()
{
    local CLASS=$1
    local ME_NAME="$2"
    local ACTION="$3"
    echo "    \"Class\"       : $CLASS ,
    \"Id\"          : 0 ,
    \"Name\"        : \"$ME_NAME\" ,
    \"Action\"      : \"$ACTION\", 
    \"Created_by\"  : \"OLT\" ,
    \"Create_Time\" : 0 
    " >> ${OUTPUT_FILE}
}

ATTRIB_SET()
{
    local ID=$1
    local ATT_NAME="$2"
    local SIZE="$3"
    local ACCESS="$4"
    local MAND="$5"
    J_B_START
    echo "
    \"Id\"       : $ID ,
    \"Name\"     : \"$ATT_NAME\" ,
    \"Size\"     : \"$SIZE\" ,
    \"Access\"   : \"$ACCESS\",
    \"Value\"    : 0,
    \"Mandtary\" : \"$MAND\"
    " >> ${OUTPUT_FILE}
    J_B_END
}

#Create file from here#
if [ -f ${OUTPUT_FILE} ];then
    `rm ${OUTPUT_FILE}`
fi

J_B_START

BASIC_SET "$CID" "$ME_NAME" "$ATT_MODE_T_AC"
J_COMMA

J_A_START

for (( c=1; c <= "${ATTRIB_NUM}"; c++ ))
do 
    ATT_NAME_T=`./get_section.sh "$SECTION" attribute_name "$c"` 
    ATT_MODE_T_SIZE=`./get_section.sh "$SECTION" attribute_mode "$c" "SIZE"`
    ATT_MODE_T_RW=`./get_section.sh "$SECTION" attribute_mode "$c" "RW"`
    ATT_MODE_T_MAND=`./get_section.sh "$SECTION" attribute_mode "$c" "SET_GET"`
    ATTRIB_SET "$c" "$ATT_NAME_T" "$ATT_MODE_T_SIZE" "$ATT_MODE_T_RW" "$ATT_MODE_T_MAND" 
    if (( $c != "$(($ATTRIB_NUM))" ));then
	#echo "[$c] [$(($ATTRIB_NUM))]"
	J_COMMA
    fi
done

J_A_END
J_B_END

