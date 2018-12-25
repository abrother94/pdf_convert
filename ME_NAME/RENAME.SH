#!/bin/bash

toupper()
{
	echo `echo "$1" | tr '[:lower:]' '[:upper:]'`
}

tolower()
{
	echo `echo "$1" | tr '[:upper:]' '[:lower:]'`
}

RENAME_S=("performance_monitoring" "pm" 
          "station_management" "STA_MGMT" 
	  "Physical_path_termination_point" "PPTP"
	  "configuration" "CFG"
	  "bridge" "BRG"
	  "interworking_termination_point" "ITP"
	  "INVENTORY_AND_STATUS_DATA" "INNT_STATUS"
	  "SUBCARRIER_MASKING" "subc_mask"
	  "SUBCARRIER_MASKING" "subc_mask"
	  "SERVICE" "srv"
	  "DOWNSTREAM" "DS"
	  "UPSTREAM" "US"
	  "PROFILE" "prof"
	  "OPERATION" "opt"
	  "CHANNEL" "ch"
	  "EXTENDED" "ext"
	  "ETHERNET" "ETH"
	  "SUBSCRIBER" "SUBSC"
	  "CONFIG" "CFG"
	  "TERMINATION_POINT" "TP"
	  "NETWORK" "NET"
	  "INTERFACE" "INF"
	  "HISTORY_DATA" "HIS_DATA"
	  "EXTENSION" "EXT"
	  )

rename_all()
{
    N=${#RENAME_S[@]}
    N=$(($N/2))

    for (( c=0; c < "${N}"; c++ ))
    do
	echo "c[$c]"
	for name in *; do
	    J=$(($c*2))
	    K=$(($J+1))
	    Rename "$name" "${RENAME_S[$J]}" "${RENAME_S[$K]}"
	done
    done
}

Rename()
{
    local NNAME="$1"
    local O_S=`toupper "$2"`
    local N_S=`toupper "$3"`
    #echo "NNAME[$NNAME] O_S[$O_S] N_S[$N_S]"
    mv "$NNAME" "`echo $NNAME | sed "s/$O_S/$N_S/"`"
}

for f in *  
do 
    mv -- "$f" "$(tr [:lower:] [:upper:] <<< "$f")" 
done

rename_all


