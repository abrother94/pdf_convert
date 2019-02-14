#/bin/bash

F_OUT_File="OMCI_SEQ_DIAG.out"
ONT_File="ONT_OMCI_SEQ_DIAG.out"
OLT_File="OLT_OMCI_SEQ_DIAG.out"
ARROW_File="ARROW_OMCI_SEQ_DIAG.out"

F_OUT_START()
{
echo "
digraph omci_sequnce {
    rankdir="LR"; 
    node[shape="point"]; 
    edge[arrowhead="none"] 
" >> ${F_OUT_File}
}

F_OUT_END()
{
echo "
}
" >> ${F_OUT_File}
}

ONT_OUT_START()
{
echo "
    ONT{
        rank="same"; 
        ONT[shape="plaintext"] 
	ONT
" >> ${ONT_File}
}

ONT_OUT_END()
{
echo "
    }
" >> ${ONT_File}
}

OLT_OUT_START()
{
echo "
    OLT{
        rank="same"; 
        OLT[shape="plaintext"] 
	OLT
" >> ${OLT_File}
}

OLT_OUT_END()
{
echo "
    }
" >> ${OLT_File}
}


set_ont_info()
{
echo "        ->
        ONT_"${stime}"
" >> ${ONT_File}
}

set_olt_info()
{
echo "        ->
        OLT_"${stime}"
" >> ${OLT_File}
}

set_content_info()
{
    echo "dir[$dir]"
    if [ "$dir" = "R" ];then
	echo "
	OLT_${stime}->ONT_${stime} [label=\"${Message}\" arrowhead=\"normal\"];
	" >> ${ARROW_File}
    elif [ "$dir" = "A" ] ;then
	echo "
	ONT_"${stime}"->OLT_"${stime}" [label=\"${Message}\" arrowhead=\"normal\" color=lightblue];
	" >> ${ARROW_File}
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

	"omci_seq_start")
        `rm ${F_OUT_File}`
        `rm ${ONT_File}`
        `rm ${OLT_File}`
        `rm ${ARROW_File}`
        F_OUT_START	
	;;
	"omci_seq_end")
        F_OUT_END
        `rm ${ONT_File}`
        `rm ${OLT_File}`
        `rm ${ARROW_File}`
	;;
	"omci_ont_start")
        ONT_OUT_START	
	;;
	"omci_ont_end")
        ONT_OUT_END
	;;
	"omci_olt_start")
        OLT_OUT_START	
	;;
	"omci_olt_end")
        OLT_OUT_END
	;;

	"omci_info")
	stime="${3}"
        set_ont_info 
        set_olt_info 
	dir="${4}"  #L means from OLT to ONT, N means from ONT to OLT
	Message="${5}"
	set_content_info
	;;

#	"omci_olt_info")
#	stime="${3}"
#        set_olt_info 
#	;;

	"omci_append_all")
	`cat ${ONT_File} >>  ${F_OUT_File}`
	`cat ${OLT_File} >>  ${F_OUT_File}`
	`cat ${ARROW_File} >>  ${F_OUT_File}`
	;;

	"me_info")

	;;

	esac
	;;
"help")  
   	show_help 
	;;
esac
