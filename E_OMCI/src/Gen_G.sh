#/bin/bash

Config_File="ME_DIAG.out"
J_B_START()
{
echo "
digraph ME_DIAG {
node [fontname="Arial"];
" >> ${Config_File}
}
J_B_END()
{
echo "
}
" >> ${Config_File}
}

set_me_info()
{
    if [ "$dir" = "R" -a "$CT" = "L" ];then
	echo " 
	ME_$ME_CID [
	shape=Mrecord
	label=
	\"{ME_CID="${ME_CID}"|
	    "${ME_NAME}"|
	    <f0>Inst_ID="${INSTANT_ID}"
	}\"]; " >> ${Config_File}
    elif [ "$CT" = "N" ] ;then
	echo " 
	ME_$ME_CID [
	shape=record
	style=filled
	fillcolor=lightgray	
	label=
	\"{ME_CID="${ME_CID}"|
	    "${ME_NAME}"|
	    <f0>Inst_ID="${INSTANT_ID}"
	}\"]; " >> ${Config_File}

    fi
}

case "${1}" in
"get")  
	case "${2}" in
	"xx")
	get_xx
	esac
	;;
"set")  
	case "${2}" in

	"me_info_start")
        `rm ${Config_File}`
	J_B_START
	;;

	"me_info")

        ME_CID="${3}"
	ME_NAME="${4}"
	INSTANT_ID="${5}"
	dir="${6}"
	CT="${7}"
        set_me_info	
	;;

	"me_info_end")
	    J_B_END
	esac
	;;
"help")  
   	show_help 
	;;
esac
