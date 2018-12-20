#!/bin/bash
# ------------------------------------------------------------------
# NAME
#   OMCI ME Template Generator Script
#
# DESCRIPTION
#   Shell script to automatically generate C files and H files for
#   Accton's OMCI ME template using text files _PREPARED_ from G984.4.
#
#   See bottom of this script for an example of a valid input file.
#
# EXAMPLE
#   ME_template_generator.sh  9.7.1_ME.txt  9.7.2_ME.txt .....
#
# OUTPUT
#   me_xyz1.[ch]
#   me_xyz2.[ch]
#   .....
#   omci_TMP_common.h
#   omci_TMP_me_declarations.h
#   omci_TMP_all_me_headers.h
#
# DESIGN
#   Aug 10, 2010, 13:34:56, Victor Lee
#   at Accton Office, Taichung, Taiwan, created.
# ------------------------------------------------------------------

# ---------------------------------
# User's options begin:
# ---------------------------------

My_Special_Name=""          ## <== You can use your favorite user's name.
My_Output_DIR=./"OUT_MEs"   ## <== You can change template output folder.
My_Debug_ON=0               ## <== You can enable debug messages [ 0 / 1 ].

# ---------------------------------
# User's options end...
# ---------------------------------

ME_DEFINITION_OUTFILE=omci_TMP_me_declarations.c
ME_CID_DEFINITION_OUTFILE=omci_TMP_common.h
ME_INCLUDE_DEFINITION_OUTFILE=omci_TMP_all_me_headers.h
[ -n "${My_Special_Name}" ] && USER_ID="${My_Special_Name}" || USER_ID=`whoami`
USER_NAME=`cat /etc/passwd | awk '{FS=":"}/'${USER_ID}'/{print $5}' 2>/dev/null`
[ -z "${USER_NAME}" ] && USER_NAME=${USER_ID}
[ -d ${My_Output_DIR} ] || mkdir -p ${My_Output_DIR}

alias echo='echo -e'
declare -i ME_ATTRS_COUNT=0
declare ME_TOP_COMMENT=""
declare ME_NAME=""
declare ME_NUM=""
declare ME_CID=""
declare ME_ID=""
declare ME_id=""

toupper()
{
	echo `echo "$1" | tr '[:lower:]' '[:upper:]'`
}

tolower()
{
	echo `echo "$1" | tr '[:upper:]' '[:lower:]'`
}

create_ME_top_comment_C()
{
	echo '/* -------------------------------------------------------------------'
	echo ' *'
	echo ' *  NAME'
	echo ' *    me_'${ME_id}'.c'
	echo ' *'
	echo ' *  DESCRIPTION'
	echo ' *    '${ME_NUM}' : "'${ME_NAME}'"'
	echo ' *'
	echo ' *    MECID_'${ME_ID}' = '${ME_CID}
	echo ' *'
	echo "${ME_TOP_COMMENT}"
	echo ' *'
	echo ' *  SEE ALSO'
	echo ' *'
	echo ' *  NOTES'
	echo ' *'
	echo ' *  BUGS'
	echo ' *'
	echo ' *  DESIGN'
	echo ' *    '`date +"%m / %d, %Y, %T,"` ${USER_NAME}', created with'
	echo ' *    OMCI ME Template Generator Script by Victor Lee '
	echo ' *    at Accton Office, Taichung, Taiwan'
	echo ' *'
	echo ' *  HISTORY'
	echo ' *    $Date$,' ${USER_NAME}
	echo ' *    at Accton Office, Taichung, Taiwan, modified.'
	echo ' *'
	echo ' *  REVISION'
	echo ' *    $Id$'
	echo ' *'
	echo ' *  Copyright(C) Accton Techonology Corporation, 2010'
	echo ' *'
	echo ' * -------------------------------------------------------------------'
	echo ' */'
	echo ''
	echo '#include <stdlib.h>'
	echo '#include <stdio.h>'
	echo '#include <string.h>'
	echo ''
	echo '#include "omci_common.h"'
	[ "${ME_PM}" == "1" ] && \
		echo '#include "omci_pm_common.h"'
	echo '#include "me_'${ME_id}'.h"'
	[ "${ME_PM}" == "1" ] && ( \
		echo ''
		echo 'typedef struct __attribute__ ((__packed__))'; \
		echo '{'; \
		echo '	// Must declare _ONLY_ address-pointers (*)'; \
		echo '	//'
		echo '	PM_sample_data_T *XYZ_data_ptr;'; \
		echo '} '${ME_ID}'_Priv_PM_data_T;' )
	echo ''
}

create_ME_top_comment_H()
{
	echo '/* -------------------------------------------------------------------'
	echo ' *'
	echo ' *  NAME'
	echo ' *    me_'${ME_id}'.h'
	echo ' *'
	echo ' *  DESCRIPTION'
	echo ' *'
	echo ' *  SEE ALSO'
	echo ' *'
	echo ' *  NOTES'
	echo ' *'
	echo ' *  BUGS'
	echo ' *'
	echo ' *  DESIGN'
	echo ' *    '`date +"%m / %d, %Y, %T,"` ${USER_NAME}', created with'
	echo ' *    OMCI ME Template Generator Script by Victor Lee '
	echo ' *    at Accton Office, Taichung, Taiwan'
	echo ' *'
	echo ' *  HISTORY'
	echo ' *    $Date$,' ${USER_NAME}
	echo ' *    at Accton Office, Taichung, Taiwan, modified.'
	echo ' *'
	echo ' *  REVISION'
	echo ' *    $Id$'
	echo ' *'
	echo ' *  Copyright(C) Accton Techonology Corporation, 2010'
	echo ' *'
	echo ' * -------------------------------------------------------------------'
	echo ' */'
	echo ''
	echo '#if !defined(ME_'${ME_ID}'_H_INCLUDED)'
	echo '#define ME_'${ME_ID}'_H_INCLUDED'
	echo ''
}

create_init_creator_handler_ONT()
{
	ME_ptr_NAME=$1
	ME_ID_COMMENT=$2
	echo ''
	echo 'UI8_T ME_'${ME_ptr_NAME}'_init(UI16_T ME_ID, UI8_T ME_Index)'
	echo '{'
	echo '	PRELUDE();'
	echo '	ME_T *ME_ptr = ME_'${ME_ptr_NAME}'_ptr;'
	echo '	ME_Instance_T *instance_ptr;'
	echo ''
	echo '	// Initialize ME instance attributes value'
	echo '	lock_ME_instances(ME_ptr);'
	echo '	// ME_ID :'
	echo "${ME_ID_COMMENT}"
	echo '	if (!(instance_ptr = ME_add_instance(ME_ptr,ME_ID,0)))'
	echo '	{'
	echo '		unlock_ME_instances(ME_ptr);'
	echo '		return error_out("Cannot add instance");'
	echo '	}'
	echo ''
	echo '	ME_instance_setup_all_attrs_value(instance_ptr);'
	echo ''
	echo '	unlock_ME_instances(ME_ptr);'
	echo ''
	echo '	return 0;'
	echo '}'
	echo ''
}

create_init_creator_handler_OLT()
{
	ME_ptr_NAME=$1
	ME_ID_COMMENT=$2
	echo ''
	echo 'UI8_T ME_'${ME_ptr_NAME}'_create_init(UI16_T ME_ID, UI8_T ME_Index)'
	echo '{'
	echo '	PRELUDE();'
	echo '	ME_T *ME_ptr = ME_'${ME_ptr_NAME}'_ptr;'
	echo '	ME_Instance_T *instance_ptr;'
	echo ''
	echo '	// Initialize ME instance attributes value'
	echo '	lock_ME_instances(ME_ptr);'
	echo '	// ME_ID :'
	echo "${ME_ID_COMMENT}"
	[ "${ME_PM}" == "1" ] && ( \
		echo '	// ----------------------------------------------------------------------'; \
		echo '	// For each PM ME "ME_instance_ptr" found by ME_ID of this PM instance,'; \
		echo '	// (1) History_Bin        : [ ME_instance_ptr ]'; \
		echo '	//     Attributes read by : < MSGTYPE_GET >'; \
		echo '	//     Attr value of History_Bin is calculated ONLY at LAST PM_interval.'; \
		echo '	// (2) Currnet_Bin        : [ ME_instance_ptr -> next ]'; \
		echo '	//     Attributes read by : < MSGTYPE_GET_CURRENT_DATA >'; \
		echo '	//     Attr value of Current_Bin is calculated at ANY current moment.'; \
		echo '	// ----------------------------------------------------------------------'; \
		echo '	// Private_Storage of PM ME Instance stores "ACCUMULATED" BL PM counters.'; \
		echo '	// (1) History_PM_Storage : [ ME_instance_ptr -> Private_Storage]'; \
		echo '	//     Stores ACCUMULATED counters of BL Command FROZEN at LAST PM_interval.'; \
		echo '	// (2) Currnet_PM_Storage : [ ME_instance_ptr -> next -> Private_Storage ]'; \
		echo '	//     Stores ACCUMULATED counters of BL Command read at ANY current moment.'; \
		echo '	// ----------------------------------------------------------------------' )
	echo '	if (!(instance_ptr = ME_add_instance(ME_ptr,ME_ID,ME_Index)))'
	echo '	{'
	echo '		unlock_ME_instances(ME_ptr);'
	echo '		return error_out("Cannot add instance");'
	echo '	}'
	echo ''
	echo '	ME_instance_setup_all_attrs_value(instance_ptr);'
	echo ''
	echo '	if (instance_ptr->Private_Storage == 0)'; \
	echo '	{'; \
	echo '		'${ME_ID}'_Priv_PM_data_T *priv_ptr = calloc(1, sizeof('${ME_ID}'_Priv_PM_data_T));'; \
	echo '		priv_ptr->XYZ_data_ptr = calloc(1, sizeof(PM_sample_data_T));'; \
	echo '		instance_ptr->Private_Storage = (UI8_T*)priv_ptr;'; \
	echo '	}'; \
	echo ''
	echo '	unlock_ME_instances(ME_ptr);'
	echo ''
	echo '	return 0;'
	echo '}'
	echo ''
}

create_ingress_handler_ONT()
{
	ME_ptr_NAME=$1
	echo
	echo 'UI8_T ME_'${ME_ptr_NAME}'_ingress_handler(UI8_T Action, ME_Instance_T *Parser_instance_ptr)'
	echo '{'
	echo '	PRELUDE();'
	echo '	ME_T *ME_ptr = ME_'${ME_ptr_NAME}'_ptr;'
	echo ''
	echo '	debug_out(4,"Hello! This is \"%s\" ingress handler.",ME_ptr->Name);'
	echo '	debug_out(4,"Received: Message_Type [%d]", Action);'
	echo ''
	echo '	switch (Action)'
	echo '	{'
	echo '	case MSGTYPE_SET:'
	echo '	case MSGTYPE_GET:'
	echo '		return ME_get_set_action_generic_handler(ME_ptr,Action,Parser_instance_ptr,0);'
	echo '		break;'
	echo '	default:'
	echo '		return set_instance_OMCI_msg_contents_status'
	echo '			(Parser_instance_ptr,ME_ATTR_RESULT_CMD_UNSUP);'
	echo '		break;'
	echo '	}'
	echo '	return ME_ATTR_RESULT_SUCCESS;'
	echo '}'
	echo
}

create_ingress_handler_OLT()
{
	ME_ptr_NAME=$1
	echo
	echo 'UI8_T ME_'${ME_ptr_NAME}'_ingress_handler(UI8_T Action, ME_Instance_T *Parser_instance_ptr)'
	echo '{'
	echo '	PRELUDE();'
	echo '	ME_T *ME_ptr = ME_'${ME_ptr_NAME}'_ptr;'
	echo ''
	echo '	debug_out(4,"Hello! This is \"%s\" ingress handler.",ME_ptr->Name);'
	echo '	debug_out(4,"Received: Message_Type [%d]", Action);'
	echo ''
	echo '	switch (Action)'
	echo '	{'
	echo '	case MSGTYPE_CREATE:'
	echo '		if (ME_'${ME_ptr_NAME}'_create_init(Parser_instance_ptr->ME_ID,0))'
	echo '			return set_instance_OMCI_msg_contents_status'
	echo '				(Parser_instance_ptr,ME_ATTR_RESULT_INST_EXIST);'
	echo '		Action = MSGTYPE_SET;'
	echo '	case MSGTYPE_SET:'
	echo '	case MSGTYPE_GET:'
	echo '		return ME_get_set_action_generic_handler(ME_ptr,Action,Parser_instance_ptr,0);'
	echo '		break;'
	echo '	case MSGTYPE_DELETE:'
	echo '		return ((ME_delete_instance(ME_ptr, Parser_instance_ptr->ME_ID) == 0) ?'
	echo '				set_instance_OMCI_msg_contents_status(Parser_instance_ptr,ME_ATTR_RESULT_SUCCESS) :'
	echo '				set_instance_OMCI_msg_contents_status(Parser_instance_ptr,ME_ATTR_RESULT_INST_NA));'
	echo '	default:'
	echo '		return set_instance_OMCI_msg_contents_status'
	echo '			(Parser_instance_ptr,ME_ATTR_RESULT_CMD_UNSUP);'
	echo '		break;'
	echo '	}'
	echo '	return ME_ATTR_RESULT_SUCCESS;'
	echo '}'
	echo
}

create_ingress_handler_PM_OLT()
{
	ME_ptr_NAME=$1
	echo
	echo 'UI8_T ME_'${ME_ptr_NAME}'_ingress_handler(UI8_T Action, ME_Instance_T *Parser_instance_ptr)'
	echo '{'
	echo '	PRELUDE();'
	echo '	ME_T *ME_ptr = ME_'${ME_ptr_NAME}'_ptr;'
	echo '	UI8_T ret;'
	echo '	UI16_T ME_ID;'
	echo '	UI32_T Priv_PM_data_size;'
	echo '	ME_Instance_T *instance_ptr;'
	echo ''
	echo '	debug_out(4,"Hello! This is \"%s\" ingress handler.",ME_ptr->Name);'
	echo '	debug_out(4,"Received: Message_Type [%d]", Action);'
	echo ''
	echo '	switch (Action)'
	echo '	{'
	echo '	case MSGTYPE_CREATE:'
	echo '		// Invoking special PM creator function, to create 2 instances with same ME_ID'
	echo '		if ((ret = PM_ME_create_instance(ME_ptr, Parser_instance_ptr->ME_ID)))'
	echo '			return set_instance_OMCI_msg_contents_status(Parser_instance_ptr,ret);'
	echo '		Action = MSGTYPE_SET;'
	echo '	case MSGTYPE_SET:'
	echo '		// Setting the 1st PM instance (accessed by ME_ID)'
	echo '		ME_get_set_action_generic_handler(ME_ptr,Action,Parser_instance_ptr,0);'
	echo '		// Setting the 2nd PM instance (accessed by ME_ID instance->next)'
	echo '		return ME_get_set_action_generic_handler(ME_ptr,Action,Parser_instance_ptr,1);'
	echo '	case MSGTYPE_GET:'
	echo '	case MSGTYPE_GET_CURRENT_DATA:'
	echo '		return ME_get_set_action_generic_handler(ME_ptr,Action,Parser_instance_ptr,0);'
	echo '		break;'
	echo '	case MSGTYPE_DELETE:'
	echo '		ME_ID = Parser_instance_ptr->ME_ID;'
	echo '		// Free-up all Priv_PM_data malloc space by this ME_ID'
	echo '		Priv_PM_data_size = sizeof('${ME_ID}'_Priv_PM_data_T);'
	echo '		if ((instance_ptr = ME_find_instance(ME_ptr, ME_ID)))'
	echo '		{'
	echo '			free_up_Memory_inside_Priv_PM_data'
	echo '				(instance_ptr->Private_Storage, Priv_PM_data_size);'
	echo '			if ((instance_ptr->next != 0) &&'
	echo '				(instance_ptr->next->ME_ID == ME_ID))'
	echo '				free_up_Memory_inside_Priv_PM_data'
	echo '					(instance_ptr->next->Private_Storage, Priv_PM_data_size);'
	echo '		}'
	echo '		// Deleting 1st PM instance with this ME_ID'
	echo '		if (ME_delete_instance(ME_ptr, ME_ID) == 0)'
	echo '		{	// Deleting 2nd PM instance with this ME_ID'
	echo '			return ((ME_delete_instance(ME_ptr, ME_ID) == 0) ?'
	echo '					set_instance_OMCI_msg_contents_status(Parser_instance_ptr,ME_ATTR_RESULT_SUCCESS) :'
	echo '					set_instance_OMCI_msg_contents_status(Parser_instance_ptr,ME_ATTR_RESULT_INST_NA));'
	echo '		}'
	echo '		else'
	echo '			return set_instance_OMCI_msg_contents_status(Parser_instance_ptr,ME_ATTR_RESULT_INST_NA);'
	echo '	default:'
	echo '		return set_instance_OMCI_msg_contents_status'
	echo '			(Parser_instance_ptr,ME_ATTR_RESULT_CMD_UNSUP);'
	echo '		break;'
	echo '	}'
	echo '	return ME_ATTR_RESULT_SUCCESS;'
	echo '}'
	echo ''
	echo ''
	echo 'UI8_T ME_'${ME_ptr_NAME}'_PMs_updater(BOOL_T update_2nd_bin)'
	echo '{'
	echo '	PRELUDE();'
	echo '	ME_T *ME_ptr = ME_'${ME_ptr_NAME}'_ptr;'
	echo '	ME_Instance_T *instance_ptr_old;'
	echo '	ME_Instance_T *instance_ptr_now;'
	echo '	// Declare PM data-structure pointer for : [ priv_old / priv_now ]'
	echo '	'${ME_ID}'_Priv_PM_data_T *priv_old;'
	echo '	'${ME_ID}'_Priv_PM_data_T *priv_now;'
	echo ''
	echo '	lock_ME_instances(ME_ptr);'
	echo '	if (!(instance_ptr_old = ME_ptr->Instances))'
	echo '	{'
	echo '		unlock_ME_instances(ME_ptr);'
	echo '		// warn_out("ME %s does not have instance",ME_ptr->Name);'
	echo '		return 0;'
	echo '	}'
	echo ''
	echo '	while (instance_ptr_old)'
	echo '	{'
	echo '		if (!(instance_ptr_now = instance_ptr_old->next))'
	echo '		{'
	echo '			error_out("ME %s (PM) does have next instance (current-bin)",ME_ptr->Name);'
	echo '			break;'
	echo '		}'
	echo '		'
	echo '		if (instance_ptr_old->Attrs_value['${ME_ptr_NAME}'_ATTR_1_Interval_end_time].uint32 != get_PM_interval_counter())'
	echo '		{'
	echo '			// Store new interval value for later check'
	echo '			instance_ptr_old->Attrs_value['${ME_ptr_NAME}'_ATTR_1_Interval_end_time].uint32 = get_PM_interval_counter();'
	echo ''
	echo '			// Setup PM data-structure pointer for : [ priv_old / priv_now ]:'
	echo '			priv_old = ('${ME_ID}'_Priv_PM_data_T*)instance_ptr_old->Private_Storage;'
	echo '			priv_now = ('${ME_ID}'_Priv_PM_data_T*)instance_ptr_now->Private_Storage;'
	echo ''
	echo '			// First, copy [ Currnet_Bin ] to [ History_Bin ]'
	echo '			update_CurrentBin_to_HistoryBin(ME_ptr, instance_ptr_old);'
	echo ''
	echo '			// Last, copy [ Currnet_PM_Storage ] to [ History_PM_Storage ]'
	echo '			*(priv_old->XYZ_data_ptr) = *(priv_now->XYZ_data_ptr);'
	echo '		}'
	echo '		instance_ptr_old=instance_ptr_now->next;'
	echo '	}'
	echo '	unlock_ME_instances(ME_ptr);'
	echo '	return 0;'
	echo '}'
	echo ''
	echo ''
	echo 'UI8_T ME_'${ME_ptr_NAME}'_Alarms_checker(void)'
	echo '{'
	echo '	PRELUDE();'
	echo '	ME_T *ME_ptr = ME_'${ME_ptr_NAME}'_ptr;'
	echo '	ME_Instance_T *instance_ptr_old;'
	echo '	ME_Instance_T *instance_ptr_now;'
	echo '	ME_Instance_T *Threshold_instance_ptr;'
	echo '	UI32_T         TCA_index = 0;'
	echo '	UI32_T         Attr_id = 0;'
	echo '	UI32_T         Attr_value_now;'
	echo '	BOOL_T Alarm_now_Status = 0;'
	echo '	UI8_T Alarms_Triggered = 0;'
	echo ''
	echo '	lock_ME_instances(ME_ptr);'
	echo '	if (!(instance_ptr_old = ME_ptr->Instances))'
	echo '	{'
	echo '		unlock_ME_instances(ME_ptr);'
	echo '		// warn_out("ME %s does not have instance",ME_ptr->Name);'
	echo '		return 0;'
	echo '	}'
	echo ''
	echo '	while (instance_ptr_old)'
	echo '	{'
	echo '		UI16_T Threshold_ME_ID;'
	echo '		if (!(instance_ptr_now = instance_ptr_old->next))'
	echo '		{'
	echo '			error_out("ME %s (PM) does have next instance (current-bin)",ME_ptr->Name);'
	echo '			break;'
	echo '		}'
	echo '		Threshold_ME_ID = instance_ptr_old->Attrs_value['${ME_ID}'_ATTR_2_'${ATTRS_NAME[2]}'].uint32;'
	echo '		if (Threshold_ME_ID)'
	echo '		{'
	echo '			if (!(instance_ptr_old->Alarms_TCAs_bitmap) &&'
	echo '				!(ME_instance_add_alarm_tca_table(instance_ptr_old)))'
	echo '			{'
	echo '				error_out("Cannot add instance alarms table");'
	echo '				instance_ptr_old = (instance_ptr_now ? instance_ptr_now->next : 0);'
	echo '				continue;'
	echo '			}'
	echo ''
	echo '			Threshold_instance_ptr = ME_find_instance(ME_THREDATA1_ptr, Threshold_ME_ID); // For TCA:[0-6]'
	echo '			if (Threshold_instance_ptr)'
	echo '			{'
	echo '				// ----------------------------------------------------------------------'
	echo '				// Notifications - Threshold crossing alert'
	echo '				//   Check individual PM TCA Attribute data'
	echo '				// ----------------------------------------------------------------------'
	echo ''
	echo '				// Attr_id   = ME_XXX_PM_ATTR_YYY;                     /* example only */'
	echo '				// TCA_index = THREDATA1_ATTR_ZZZ_Threshold_value_ZZZ; /* example only */'
	echo '				Alarms_Triggered += get_PM_attr_alarm(instance_ptr_old,Attr_id,Threshold_instance_ptr,TCA_index);'
	echo ''
	echo '			}'
	echo ''
	echo '			if (Alarms_Triggered)'
	echo '				send_an_alarms_TCAs_notification(MSGTYPE_ALARM,instance_ptr_old);'
	echo '		}'
	echo '		instance_ptr_old=instance_ptr_now->next;'
	echo '	}'
	echo '	unlock_ME_instances(ME_ptr);'
	echo '	return Alarms_Triggered;'
	echo '}'
	echo
}

create_attr_info()
{
	ME_ptr_NAME=$1
	ME_ATTR_ID=$2
	ME_ATTR_NAME=$3
	ME_ATTR_DESC=$4
	ME_ATTR_RW=$5
	ME_ATTR_SIZE=$6
	ME_ATTR_TYPE=$7
	ME_ATTR_SUPPORT=$8
	[ "${ME_ATTR_SUPPORT}" == "N" ] \
		&& COMMENT="// optional" \
		|| COMMENT="// mandatory"
	echo '	{ '${ME_ptr_NAME}'_ATTR_'${ME_ATTR_ID}'_'${ME_ATTR_NAME}','
	echo '	  "'${ME_ATTR_DESC}'",'
	echo '	  '${ME_ATTR_SIZE}','
	echo '	  ATTR_ACCESS_'${ME_ATTR_RW}','
	echo '	  ATTR_FORMAT_'${ME_ATTR_TYPE}','
	( `echo ${ME_ATTR_RW} | grep -q "_SC"` ) \
		&& echo '	  (void*)0, // Value is set by Create' \
		|| echo '	  (void*)0, // ONT default to 0 (??)'
	echo '	  ATTR_SUPPORT_'${ME_ATTR_SUPPORT}',' ${COMMENT}
	echo '	  '${ME_ptr_NAME}'_ATTR_'${ME_ATTR_ID}'_'${ME_ATTR_NAME}'_handler,'
	echo '	},'
}

create_attr_handler_R()
{
	ME_ptr_NAME=$1
	ME_ATTR_ID=$2
	ME_ATTR_NAME=$3
	ME_ATTR_TYPE=$4
	ME_ATTR_COMMENT=$5
	echo
	echo 'UI8_T '${ME_ptr_NAME}'_ATTR_'${ME_ATTR_ID}'_'${ME_ATTR_NAME}'_handler(UI8_T Action, ME_Instance_T *ME_instance_ptr, UI32_T *Value_ptr, void *arg)'
	echo '{'
	echo '	PRELUDE();'
	echo '	UI8_T Attr_ID = (UI32_T)arg;'
	echo "${ME_ATTR_COMMENT}"
	echo '	if (Action == MSGTYPE_GET)'
	echo '	{'
	[ "${ME_ATTR_TYPE}" == "UINT" ] \
		&& echo '		*Value_ptr = ME_instance_ptr->Attrs_value[Attr_ID].uint32;' \
		|| echo '		*Value_ptr = (UI32_T)ME_instance_ptr->Attrs_value[Attr_ID].pointer;'
	echo '	}'
	# -------------------------------------------------------------------------------
	# (Action == MSGTYPE_GET_CURRENT_DATA) only exists in PM Read-Only Attr: [3..16]
	# -------------------------------------------------------------------------------
	[ "${ME_PM}" == "1" ] && [ "${ME_ATTR_ID}" != "1" ] && ( \
		echo '	else if (Action == MSGTYPE_GET_CURRENT_DATA)'; \
		echo '	{'; \
		echo '		ME_Instance_T *instance_ptr_now = ME_instance_ptr->next;'; \
		echo '		// Now update CURRENT data of this Attr in : [ priv_now->.. ]'; \
		echo '		'${ME_ID}'_Priv_PM_data_T *priv_old = ('${ME_ID}'_Priv_PM_data_T*)ME_instance_ptr->Private_Storage;'; \
		echo '		'${ME_ID}'_Priv_PM_data_T *priv_now = ('${ME_ID}'_Priv_PM_data_T*)instance_ptr_now->Private_Storage;'; \
		echo '		// get_XYZ_from_blcmd (uni_index, priv_now->XYZ_data_ptr); /* for example */'; \
		echo '		instance_ptr_now->Attrs_value[Attr_ID].uint32'; \
		echo '			= (priv_now->XYZ_data_ptr->ABC_counter - /* example only */'; \
		echo '			   priv_old->XYZ_data_ptr->ABC_counter); /* example only */'; \
		echo '		*Value_ptr = instance_ptr_now->Attrs_value[Attr_ID].uint32;'; \
		echo '	}' )
	echo '	else'
	echo '		return ME_ATTR_RESULT_ATTR_FAIL;'
	echo '	return ME_ATTR_RESULT_SUCCESS;'
	echo '}'
	echo
}

create_attr_handler_RW_uint32()
{
	ME_ptr_NAME=$1
	ME_ATTR_ID=$2
	ME_ATTR_NAME=$3
	ME_ATTR_TYPE=$4
	ME_ATTR_COMMENT=$5
	echo
	echo 'UI8_T '${ME_ptr_NAME}'_ATTR_'${ME_ATTR_ID}'_'${ME_ATTR_NAME}'_handler(UI8_T Action, ME_Instance_T *ME_instance_ptr, UI32_T *Value_ptr, void *arg)'
	echo '{'
	echo '	PRELUDE();'
	echo '	UI8_T Attr_ID = (UI32_T)arg;'
	echo "${ME_ATTR_COMMENT}"
	echo '	if (Action == MSGTYPE_GET)'
	echo '	{'
	echo '		*Value_ptr = ME_instance_ptr->Attrs_value[Attr_ID].uint32;'
	echo '	}'
	echo '	else if (Action == MSGTYPE_SET)'
	echo '	{'
	echo '		ME_instance_ptr->Attrs_value[Attr_ID].uint32 = *Value_ptr;'
	echo '	}'
	echo '	else'
	echo '		return ME_ATTR_RESULT_ATTR_FAIL;'
	echo '	return ME_ATTR_RESULT_SUCCESS;'
	echo '}'
	echo
}

create_attr_handler_RW_block()
{
	ME_ptr_NAME=$1
	ME_ATTR_ID=$2
	ME_ATTR_NAME=$3
	ME_ATTR_TYPE=$4
	ME_ATTR_COMMENT=$5
	echo
	echo 'UI8_T '${ME_ptr_NAME}'_ATTR_'${ME_ATTR_ID}'_'${ME_ATTR_NAME}'_handler(UI8_T Action, ME_Instance_T *ME_instance_ptr, UI32_T *Value_ptr, void *arg)'
	echo '{'
	echo '	PRELUDE();'
	echo '	UI8_T Attr_ID = (UI32_T)arg;'
	echo "${ME_ATTR_COMMENT}"
	echo '	if (Action == MSGTYPE_GET)'
	echo '	{'
	echo '		*Value_ptr = (UI32_T)ME_instance_ptr->Attrs_value[Attr_ID].pointer;'
	echo '	}'
	echo '	else if (Action == MSGTYPE_SET)'
	echo '	{'
	[ "${ME_ATTR_TYPE}" == "TABLE" ] && ( \
		echo '		// ------------------------------------------------------------------'; \
		echo '		// WARNING !! Each table attribute SETTING needs special handling codes '; \
		echo '		// ------------------------------------------------------------------' )
	echo '		set_Attr_pointer_value(ME_instance_ptr, Attr_ID, (UI8_T*)*Value_ptr,0);'
	echo '	}'
	echo '	else'
	echo '		return ME_ATTR_RESULT_ATTR_FAIL;'
	echo '	return ME_ATTR_RESULT_SUCCESS;'
	echo '}'
	echo
}

open_input_file()
{
	INPUT_FILE="$1"
	exec 6<&0
	exec 6>&1
	exec < ${INPUT_FILE}
	echo "Reading file:" ${INPUT_FILE} >&6
}

open_output_file()
{
	OUTPUT_FILE=${My_Output_DIR}/"$1"
	exec 6<&0
	exec 6>&1
	exec > ${OUTPUT_FILE}
	echo "  generating:" ${OUTPUT_FILE} >&6
}

open_append_file()
{
	APPEND_FILE=${My_Output_DIR}/"$1"
	exec 6<&0
	exec 6>&1
	exec >> ${APPEND_FILE}
	echo "  appending: " ${APPEND_FILE} >&6
}

close_IO_files()
{
	exec 0<&-
	exec 1>&-
	exec 0<&6
	exec 1>&6
}

read_a_text_line()
{
	while read TEXT_LINE ; do
		TXT_LN=`echo ${TEXT_LINE} | tr -d [:blank:]`
		[ ${#TXT_LN} -eq 0 ] && continue || break
	done
	echo "${TEXT_LINE}"
}

input_ME_definition()
{
	# ------------------------------------------------------------------
	# Read ME_NUM, ME_NAME, ME_ID, ME_CID definition:
	# ------------------------------------------------------------------
	LINE="`read_a_text_line`"
	ME_NUM=${LINE%% *}
	echo ME_NUM[$ME_NUM]
	ME_NAME=${LINE#* }
	echo ME_NAME[$ME_NAME]

	LINE="`read_a_text_line`"
	ME_ID=${LINE}
	echo ME_ID[$ME_ID]
	ME_id=`tolower "${LINE}"`

	LINE="`read_a_text_line`"
	ME_CID=${LINE}
	echo ME_CID[$ME_CID]

	( `echo ${ME_NAME} | grep -q -i "performance monitor"` ) \
		&& ME_PM="1" \
		|| ME_PM="0"
}

input_ME_comment()
{
	# ------------------------------------------------------------------
	# Read this ME's general spec description (comment block):
	# ------------------------------------------------------------------
	ME_TOP_COMMENT=" `read_a_text_line`"
	ME_TOP_COMMENT=${ME_TOP_COMMENT/\*/\*   }
	while read LINE ; do
		LN=`echo ${LINE} | tr -d [:blank:]`
		[ ${#LN} -eq 0 ] && break
		LINE=${LINE/\*/\*   }
		ME_TOP_COMMENT="${ME_TOP_COMMENT}
 ${LINE}"
	done
	# Skip the line: "Attributes"
	JUNK=`read_a_text_line`
}

input_ME_attrs_details()
{
	# ------------------------------------------------------------------
	# Read all G984.4 attrs definition into arrays:
	# ------------------------------------------------------------------
	declare -i COUNT
	declare -i SIZE
	COUNT=0
	ME_TABLE=""
	while : ; do
		LINE="`read_a_text_line`"

		echo LINE[$LINE]
		exit
		[ "${LINE}" == "Actions" ] && break;
		# ---------------------------------
		# Attr's Table-Attr checking:
		# ---------------------------------
		( `echo ${LINE} | grep -q -i " Table:"` ) \
			&& TABLE_ATTR="1" \
			|| TABLE_ATTR="0"
		# ---------------------------------
		# Attr's Description name:
		# ---------------------------------
		LINE=${LINE%:}
		ATTRS_DESC[$COUNT]="${LINE}"
		# ---------------------------------
		# Attr's identifing Name:
		# ---------------------------------
		LINE=${LINE//(/}
		LINE=${LINE//)/}
		LINE=${LINE//./}
		LINE=${LINE//\// over }
		LINE=${LINE//  / }
		LINE=${LINE// - /_}
		LINE=${LINE//-/_}
		LINE=${LINE// /_}
		ATTRS_NAME[$COUNT]="${LINE}"
		# ---------------------------------
		# Attr's Comment (func spec):
		# ---------------------------------
		BLOCK="`read_a_text_line`"
		BLOCK=${BLOCK/\/\//	\/\/}
		while : ; do
			LINE="`read_a_text_line`"
			if [ "${LINE:0:2}" == "//" ]; then
				LINE=${LINE/\/\//	\/\/}
				BLOCK="${BLOCK}
${LINE}"
			else
				break
			fi
		done
		ATTRS_COMMENT[$COUNT]="${BLOCK}"
		# ---------------------------------
		# Attr's Size (XX bytes):
		# ---------------------------------
		SIZE=`echo ${LINE} | awk 'BEGIN{FS="("}{print $4}' | cut -d ' ' -f1 | tr -d [:alpha:]`
		ATTRS_SIZE[$COUNT]=${SIZE}
		# ---------------------------------
		# Attr's Type:
		# ---------------------------------
		[ ${SIZE} -le 4 ] \
			&& ATTRS_TYPE[$COUNT]="UINT" \
			|| ATTRS_TYPE[$COUNT]="BLOCK"
		# ---------------------------------
		# NOTE: No way to know ATTRS_TYPE="STRING"
		# ---------------------------------
		if [ "${TABLE_ATTR}" == "1" ]; then
			ME_TABLE="1"
			ATTRS_TYPE[$COUNT]="TABLE"
		fi
		# ---------------------------------
		# Attr's Support: (mandatory) (optional)
		# ---------------------------------
		if   echo ${LINE} | grep -q "mandatory" ; then
			ATTRS_SUPPORT[$COUNT]="Y"
		elif echo ${LINE} | grep -q "optional" ; then
			ATTRS_SUPPORT[$COUNT]="N"
		else
			echo "****** ERROR ******" >&6
			echo "Unknown (mandatory/optional) property:" \"${LINE}\" >&6
		fi
		# ---------------------------------
		# Attr's RW: (R) (W) (R, W)
		#            (R, Set-by-create)
		#            (W, Set-by-create)
		#            (R, W, Set-by-create)
		# ---------------------------------
		if   echo ${LINE} | grep -q "(R)" ; then
			ATTRS_RW[$COUNT]="R"
		elif echo ${LINE} | grep -q "(W)" ||
			 echo ${LINE} | grep -q "(R, W)" ; then
			ATTRS_RW[$COUNT]="RW"
		elif echo ${LINE} | grep -q "(R, Set-by-create)" ; then
			ATTRS_RW[$COUNT]="R_SC"
		elif echo ${LINE} | grep -q "(W, Set-by-create)" ||
			 echo ${LINE} | grep -q "(R, W, Set-by-create)" ; then
			ATTRS_RW[$COUNT]="RW_SC"
		else
			echo "****** ERROR ******" >&6
			echo "Unknown (R/W) property:" \"${LINE}\" >&6
		fi
		COUNT=COUNT+1
	done
	ME_ATTRS_COUNT=COUNT-1
}

input_ME_action_list()
{
	# ------------------------------------------------------------------
	# Read ME's Actions list
	# ------------------------------------------------------------------
	LINE="`read_a_text_line`"
	ME_ACTIONS=${LINE}
	( `echo "${ME_ACTIONS}" | grep -q "Create"` ) \
		&& ME_CREATOR="OLT" \
		|| ME_CREATOR="ONT"
}

output_ME_C_file()
{
	open_output_file me_${ME_id}.c

	# ------------------------------------------------------------------
	# (1) generate ME's top comment block
	# ------------------------------------------------------------------
	create_ME_top_comment_C

	# ------------------------------------------------------------------
	# (2) generate ME's all attrs' info
	# ------------------------------------------------------------------
	echo 'ME_Attr_Info_T '${ME_ID}'_Attrs_Info[]='
	echo '{'
	echo '	// Note: Attributes Information can be declared in any order.'
	echo '	//'
	for ((I=1; I <= ME_ATTRS_COUNT ; I++)) ; do
		create_attr_info ${ME_ID} $I ${ATTRS_NAME[$I]} "${ATTRS_DESC[$I]}" \
			${ATTRS_RW[$I]} ${ATTRS_SIZE[$I]} ${ATTRS_TYPE[$I]} ${ATTRS_SUPPORT[$I]}
	done
	echo '	{ 0 } // Must have '{ 0 }' at the end of array.'
	echo '};'
	echo ''

	# ------------------------------------------------------------------
	# (3) generate ME's create init handler
	# ------------------------------------------------------------------
	ATTRS_COMMENT[0]=${ATTRS_COMMENT[0]//\/\//\/\/  }

	[ "${ME_CREATOR}" == "ONT" ] \
		&& create_init_creator_handler_ONT ${ME_ID} "${ATTRS_COMMENT[0]}" \
		|| create_init_creator_handler_OLT ${ME_ID} "${ATTRS_COMMENT[0]}"

	# ------------------------------------------------------------------
	# (4) generate ME's ingress handler
	# ------------------------------------------------------------------
	if [ "${ME_CREATOR}" == "ONT" ] ; then
		create_ingress_handler_ONT ${ME_ID}
	elif [ "${ME_PM}" == "1" ] ; then
		create_ingress_handler_PM_OLT ${ME_ID}
	else
		create_ingress_handler_OLT ${ME_ID}
	fi

	# ------------------------------------------------------------------
	# (5) generate ME's individual attr's handler
	# ------------------------------------------------------------------
	for ((I=1; I <= ME_ATTRS_COUNT ; I++)) ; do
		if [ "${ATTRS_RW[$I]}" == "R" -o "${ATTRS_RW[$I]}" == "R_SC" ] ; then
			create_attr_handler_R ${ME_ID} $I ${ATTRS_NAME[$I]} \
				${ATTRS_TYPE[$I]} "${ATTRS_COMMENT[$I]}"
		elif [ "${ATTRS_RW[$I]}" == "RW" -o "${ATTRS_RW[$I]}" == "RW_SC" ] ; then
			if [ ${ATTRS_SIZE[$I]} -le 4 -a "${ATTRS_TYPE[$I]}" != "TABLE" ] ; then
				create_attr_handler_RW_uint32 ${ME_ID} $I ${ATTRS_NAME[$I]} \
					${ATTRS_TYPE[$I]} "${ATTRS_COMMENT[$I]}"
			else
				create_attr_handler_RW_block ${ME_ID} $I ${ATTRS_NAME[$I]} \
					${ATTRS_TYPE[$I]} "${ATTRS_COMMENT[$I]}"
			fi
		fi
	done

	close_IO_files
}

output_ME_H_file()
{
	open_output_file me_${ME_id}.h

	# ------------------------------------------------------------------
	# (1) generate ME's top comment block
	# ------------------------------------------------------------------
	create_ME_top_comment_H

	# ------------------------------------------------------------------
	# (2) generate ME's all attrs' enumerator
	# ------------------------------------------------------------------
	echo ''
	echo 'enum'
	echo '{'
	for ((I=1; I <= ME_ATTRS_COUNT ; I++)) ; do
		echo '	'${ME_ID}'_ATTR_'$I'_'${ATTRS_NAME[$I]} '=' $I','
	done
	echo '};'
	echo ''

	# ------------------------------------------------------------------
	# (3) generate ME's all attrs' handler declaration
	# ------------------------------------------------------------------
	echo ''
	[ "${ME_CREATOR}" == "ONT" ] \
		&& echo 'UI8_T ME_'${ME_ID}'_init(UI16_T ME_ID, UI8_T ME_Index);' \
		|| echo 'UI8_T ME_'${ME_ID}'_create_init(UI16_T ME_ID, UI8_T ME_Index);'
	echo ''
	echo 'UI8_T ME_'${ME_ID}'_ingress_handler(UI8_T Message_type, ME_Instance_T *Parser_instance_ptr);'
	echo ''
	if [ "${ME_PM}" == "1" ] ; then
		echo 'UI8_T ME_'${ME_ID}'_PMs_updater(BOOL_T update_2nd_bin);'
		echo ''
		echo 'UI8_T ME_'${ME_ID}'_Alarms_checker(void);'
	fi
	echo ''
	echo ''
	for ((I=1; I <= ME_ATTRS_COUNT ; I++)) ; do
		echo 'UI8_T '${ME_ID}'_ATTR_'$I'_'${ATTRS_NAME[$I]}'_handler(UI8_T Action, ME_Instance_T *ME_instance_ptr, UI32_T *Value_ptr, void *arg);'
		echo ''
	done
	echo ''
	echo 'extern ME_Attr_Info_T '${ME_ID}'_Attrs_Info[];'
	echo ''
	echo 'extern ME_T *ME_'${ME_ID}'_ptr;'
	echo ''
	echo ''
	echo '#endif /* ME_'${ME_ID}'_H_INCLUDED */'

	close_IO_files
}

output_ME_definition()
{
	open_append_file ${ME_DEFINITION_OUTFILE}

	echo '	{ MECID_'${ME_ID}','
	echo '	  "'${ME_NAME}'",'
	echo '	  &ME_'${ME_ID}'_ptr,'
	echo '	  0,'
	echo '	  { '${ME_ID}'_Attrs_Info },'
	echo '	  { 0 }, // Alarms/TCAs: N/A'
	echo '	  0, // AVCs attr: N/A'
	[ "${ME_PM}" == "1" ] && EXTRA=' | ACT_GET_CURRENT_DATA' || EXTRA=''
	[ "${ME_TABLE}" == "1" ] && EXTRA=${EXTRA}' | ACT_GET_NEXT,' || EXTRA=${EXTRA}','
	[ "${ME_CREATOR}" == "ONT" ] \
		&& ( echo '	  ACT_GET | ACT_SET' ${EXTRA}; echo '	  ME_ONT_CREATED,' ) \
		|| ( echo '	  ACT_CREATE | ACT_DELETE | ACT_GET | ACT_SET' ${EXTRA}; echo '	  ME_OLT_CREATED,' )
	echo '	  ME_SUPPORTED,'
	[ "${ME_PM}" == "1" ] \
		&& echo '	  MIB_UPLOAD_EXCLUDED,' \
		|| echo '	  MIB_UPLOAD_INCLUDED,'
	[ "${ME_CREATOR}" == "ONT" ] \
		&& echo '	  ME_'${ME_ID}'_init,' \
		|| echo '	  ME_'${ME_ID}'_create_init,'
	echo '	  ME_'${ME_ID}'_ingress_handler,'
	[ "${ME_PM}" == "1" ] \
		&& ( echo '	  ME_'${ME_ID}'_PMs_updater,'; echo '	  ME_'${ME_ID}'_Alarms_checker,'; echo '	  0,' ) \
		|| ( echo '	  0, 0, 0,' )
	echo '	  PTHREAD_MUTEX_INITIALIZER'
	echo '	},'
	echo ''
	echo 'ME_T *ME_'${ME_ID}'_ptr = 0;'
	echo

	close_IO_files
}

output_ME_CID_definition()
{
	open_append_file ${ME_CID_DEFINITION_OUTFILE}

	echo '	MECID_'${ME_ID}'					= '${ME_CID}', // '${ME_NUM}

	close_IO_files
}

output_ME_include_definition()
{
	open_append_file ${ME_INCLUDE_DEFINITION_OUTFILE}

	echo '#include "me_'${ME_id}'.h"'

	close_IO_files
}

display_debug_info()
{
	echo "------------------------------------------------------------------"
	echo "ME_NUM:   [${ME_NUM}]"
	echo "ME_NAME:  [${ME_NAME}]"
	echo "ME_ID:    [${ME_ID}]"
	echo "ME_id:    [${ME_id}]"
	echo "ME_CID:   [${ME_CID}]"
	echo "ME_ATTRS_COUNT: [ 0 .. ${ME_ATTRS_COUNT} ]"
	echo "ME's COMMENT:"
	echo "/*"
	echo "${ME_TOP_COMMENT}"
	echo "*/"
	for ((I=0; I <= ME_ATTRS_COUNT; I++)) ; do
		echo "------------------------------------------------------------------"
		echo "[ Attr: $I]"
		echo "DESC:    ${ATTRS_DESC[$I]}"
		echo "NAME:    ${ATTRS_NAME[$I]}"
		echo "SIZE:    ${ATTRS_SIZE[$I]}"
		echo "SUPPORT: ${ATTRS_SUPPORT[$I]}"
		echo "RW:      ${ATTRS_RW[$I]}"
		echo "COMMENT:"
		echo "${ATTRS_COMMENT[$I]}"
	done
	echo "------------------------------------------------------------------"
}

display_warning_info()
{
	BLINK_TXT="\033[01;06;40m"
	GRN_COLOR="\033[01;32;40m"
	RED_COLOR="\033[01;04;31;40m"
	NO_COLOR="\033[m"
	alias echo='echo -e'
	echo ""
	echo ${BLINK_TXT}"IMPORTANT..!!"${NO_COLOR}
	echo ""
	echo "  You also need to "${GRN_COLOR}"manually"${NO_COLOR}" add your above MEs init to following functions:"
	echo ""
	echo "  (1) "${RED_COLOR}"startup_all_ONT_created_MEs()"${NO_COLOR}"  (in omci_common.c)"
	echo "      or,"
	echo "  (2) "${RED_COLOR}"startup_all_OLT_created_MEs()"${NO_COLOR}"  (in omci_common.c)"
	echo ""
}

[ -z "$1" ] && echo "Need at least one G984.4 ME text filename" && exit 1

rm -f ${My_Output_DIR}/${ME_DEFINITION_OUTFILE}
rm -f ${My_Output_DIR}/${ME_CID_DEFINITION_OUTFILE}
rm -f ${My_Output_DIR}/${ME_INCLUDE_DEFINITION_OUTFILE}

while (( $# > 0 )) ; do
	[ ! -f "$1" ] && shift 1 && continue

	dos2unix -k $1 &>/dev/null

	# ------------------------------------------------------------------
	# Input ME's G984.4 definition from this text file
	# ------------------------------------------------------------------

	open_input_file $1
	input_ME_definition
	input_ME_comment
	input_ME_attrs_details
	input_ME_action_list
	close_IO_files

	# ------------------------------------------------------------------
	# Output ME's C source codes file
	# Output ME's H source codes file
	# Output ME's data-structure definition (for: omci_me_declarations.c)
	# Output ME's Class ID declaration (for: omci_common.h)
	# Output ME's header include line (for: omci_all_me_headers.h)
	# ------------------------------------------------------------------

	echo "  [" ${ME_NUM} "]"
	output_ME_C_file
	output_ME_H_file
	output_ME_definition
	output_ME_CID_definition
	output_ME_include_definition

	# ------------------------------------------------------------------
	# Optional debugging messages
	# ------------------------------------------------------------------

	[ "${My_Debug_ON}" == "1" ] && display_debug_info

	shift 1
done

display_warning_info

echo "Byebye.."

exit 0

### ===================================================================== ###
###																		  ###
### Example of an acceptable valid ME text file copied from: G984.4 Spec. ###
###																		  ###
### ===================================================================== ###

9.7.6 VDSL2 line configuration extensions

VDSL2_LINE_CFG_EXTENSIONS

165

* This managed entity extends the xDSL line configuration MEs with attributes
* that are unique to [ITU-T G.993.2] VDSL2. The attributes of this ME are
* further defined in [ITU-T G.997.1]. An instance of this managed entity is
* created and deleted by the OLT.
*
* Relationships
*
* An instance of this managed entity may be associated with zero or more
* instances of the physical path termination point xDSL UNI part 1.
*
* The overall xDSL line configuration profile is modelled in several parts,
* all of which are associated together through a common managed entity id
* (the client physical path termination point xDSL UNI part 1 has a single
* pointer, which refers to the entire set of line configuration parts).

Attributes

Managed entity id:
// This attribute uniquely identifies each instance of this managed entity.
// All xDSL and VDSL2 line configuration profiles that pertain to a given
// physical path termination point xDSL must share a common managed
// entity id.
(R, Set-by-create) (mandatory) (2 bytes)

VDSL2 profiles enabling:
// This attribute (PROFILES) contains the G.993.2 profiles to be allowed
// by the xTU-C. It is coded in a bit map representation (0 if not allowed, 1
// if allowed) with the following definition:
// Bit     Meaning
// 1 (LSB) G.993.2 profile 8a.
// 2       G.993.2 profile 8b.
// 3       G.993.2 profile 8c.
// 4       G.993.2 profile 8d.
// 5       G.993.2 profile 12a.
// 6       G.993.2 profile 12b.
// 7       G.993.2 profile 17a.
// 8       G.993.2 profile 30a.
(R, W, Set-by-create) (mandatory) (1 byte)

VDSL2 PSD mask class selection (CLASSMASK):
// To reduce the number of configuration possibilities, the limit PSD masks
// are grouped in the following PSD mask classes:
// . Class 998 Annex A: D-32, D-48, D-64, D-128.
// . Class 997-M1c Annex B: 997-M1c-A-7.
// . Class 997-M1x Annex B: 997-M1x-M-8, 997-M1x-M.
// . Class 997-M2x Annex B: 997-M2x-M-8, 997-M2x-A, 997-M2x-M,
//     997E17-M2x-NUS0, 997E30-M2x-NUS0.
// . Class 998-M1x Annex B: 998-M1x-A, 998-M1x-B,
//     998-M1x-NUS0.
// . Class 998-M2x Annex B: 998-M2x-A, 998-M2x-M, 998-M2x-B,
//     998-M2x-NUS0, 998E17-M2x-NUS0, 998E17-M2x-NUS0-M,
//     998E30-M2x-NUS0, 998E30-M2x-NUS0-M.
// . Class 998ADE-M2x Annex B: 998-M2x-A, 998-M2x-M,
//     998-M2x-B, 998-M2x-NUS0, 998ADE17-M2x-A,
//     998ADE17-M2x-B, 998ADE17-M2x-NUS0-M,
//     998ADE30-M2x-NUS0-A, 998ADE30-M2x-NUS0-M.
// . Class 998-B Annex C: POTS-138b, POTS-276b (clause C.2.1.1 of
//     [ITU-T G.993.2]), TCM-ISDN (clause C.2.1.2 of [ITU-T G.993.2]).
// . Class 998-CO Annex C: POTS-138co, POTS-276co (clause C.2.1.1
//     of [ITU-T G.993.2]).
// . Class HPE-M1 Annex B: HPE17-M1-NUS0, HPE30-M1-NUS0.
// Each class is designed such that the PSD levels of each limit PSD mask
// of a specific class are equal in their respective passbands above 552 kHz.
// The CLASSMASK attribute is defined per annex enabled in the xTSE
// table (see Table 9.7.12-1). It selects a single PSD mask class per annex to
// be activated at the VTU-O. The coding is as follows:
//  Attribute value  G.993.2 Annex A  G.993.2 Annex B  G.993.2 Annex C
//  1                998              997-M1c          998-B
//  2                                 997-M1x          998-CO
//  3                                 997-M2x
//  4                                 998-M1x
//  5                                 998-M2x
//  6                                 998ADE-M2x
//  7                                 HPE
// NOTE 1 - A single PSD mask class may be selected per [ITU-T G.993.2]
//   annex.
(R, W, Set-by-create) (mandatory) (1 byte)

VDSL2 limit PSD masks:
// The LIMITMASK attribute contains the G.993.2 limit PSD masks of the
// selected PSD mask class, enabled by the near-end xTU for each class of
// profiles. One LIMITMASK parameter is defined per annex enabled in
// the xTSE (see Table 9.7.12-1).
// The profiles are grouped in the following profile classes:
// - Class 8: Profiles 8a, 8b, 8c, 8d.
// - Class 12: Profiles 12a, 12b.
// - Class 17: Profile 17a.
// - Class 30: Profile 30a.
// For each profile class, several limit PSD masks of the selected PSD mask
// class (CLASSMASK) may be enabled. The enabling attribute is coded in
// a bit map representation (0 if the associated mask is not allowed, 1 if it is
// allowed). The bit mask is defined in Table 9.7.6-1.
(R, W, Set-by-create) (mandatory) (8 bytes)

VDSL2 US0 disabling:
// The US0DISABLE attribute specifies whether channel US0 is disabled
// for each limit PSD mask enabled in the LIMITMASK attribute.
// For each limit PSD mask enabled in the LIMITMASK attribute, one bit
// indicates if US0 is disabled. The disabling attribute is a bit map where
// the value 1 specifies that US0 is disabled for the associated limit mask.
// The bit map has the same structure as the LIMITMASK attribute.
(R, W, Set-by-create) (mandatory) (8 bytes)

VDSL2 US0 PSD masks:
// The US0MASK attribute contains the US0 PSD masks to be allowed by
// the xTU-C. This attribute is only defined for Annex A of
// [ITU-T G.993.2]. It is represented as a bit map (0 if not allowed, 1 if
// allowed) with the definitions of Table 9.7.6-2.
(R, W, Set-by-create) (mandatory) (4 bytes)

VDSL2-CARMASK table:
// This attribute specifies restrictions, additional to the band plan, that
// determine the set of subcarriers allowed for transmission in both
// upstream and downstream directions.
// The VDSL2-CARMASK attribute describes the not-masked subcarriers
// in terms of one or more frequency bands. Each band is represented by
// start and stop subcarrier indices with a subcarrier spacing of 4.3125 kHz.
// The valid range of subcarrier indices is from 0 to at least the index of the
// highest allowed subcarrier in both transmission directions among all
// profiles enabled by the VDSL2 profiles enabling (PROFILES) attribute.
// Up to 32 bands may be specified. Other subcarriers are masked.
// For profiles using 8.625 kHz tone spacing, the odd subcarrier indices
// i4.3125 in VDSL2-CARMASK can be transformed into actual subcarrier
// indices i8.625 using the following rule:
// - For the start frequency of each band: i8.625 = (i4.3125 + 1)/2.
// - For the stop frequency of each band: i8.625 = (i4.3125 - 1)/2.
// The VDSL2-CARMASK attribute is a table where each entry comprises:
// - An entry number field (1 byte, first entry numbered 1).
// - Band start subcarrier index (2 bytes).
// - Band stop subcarrier index (2 bytes).
// By default, the table is empty. Entries are added or modified using the set
// action, which permits from one to as many as six breakpoints to be
// // addressed in a single set message (Note 2). Setting a table entry with
// non-zero subcarrier references implies insertion into the table. Setting an
// entrys subcarrier references to zero implies deletion from the table, if
// present.
// NOTE 2 - OMCI does not provide robust exception handling when more than
//   one entry is included in a set command, and multiple values per set operation
//   are not recommended.
// The maximum number of breakpoints is 32, so the maximum size of the
// table is 160 bytes.
(R, W) (mandatory) (5N bytes, where N is the number of bands)

CARMASK valid:
// This attribute controls and reports the status of the VDSL2-CARMASK
// table. If CARMASK valid = 1, then the VDSL2-CARMASK has been
// effectuated on the xDSL equipment. If CARMASK valid = 0 (default),
// then the VDSL2-CARMASK table is under construction and has not
// been effectuated on the xDSL equipment.
// This attribute behaves as follows:
// . If the OLT changes any of the VDSL2-CARMASK table entries
//   or sets CARMASK valid = 0, then CARMASK valid = 0.
// . If CARMASK valid = 0 and the OLT sets CARMASK valid = 1,
//   then the ONT updates the xDSL equipment with the content of
//   the table.
(R, W) (mandatory) (1 byte)

UPBOSHAPED:
// Upstream power back-off (UPBO) is specified in [ITU-T G.993.2] to
// provide spectral compatibility between loops of different lengths
// deployed in the same cable binder. The upstream transmit PSD mask,
// UPBOMASKus is defined in clause 7.2.1.3.2 of [ITU-T G.993.2] using
// the formula:
//
// UPBOMASK(kl0,f) = UPBOPSD(f) + LOSS(kl0,f) + 3.5[dBm/Hz]
// LOSS(kl0,f) = kl0?šf [dB]
//
// where UPBOPSD(f) = -a-b?šf.
// The UPBO configuration attributes a and b are set by the OLT via this
// attribute. The value of kl0 may be determined during initialization by the
// VTUs or also set by the OLT. Further detail appears in [ITU-T G.997.1].
// This attribute includes two parameters for each band. The parameters are
// a and b, in that order. Parameter a lies in the range 4000 (40.00 dBm/Hz)
// to 8095 (80.95 dBm/Hz). Parameter b lies in the range 0 (0.00 dBm/Hz)
// to 4095 (40.95 dBm/Hz). The special values a = b = 0 disable UPBO in
// the respective upstream band.
// The upstream electrical length parameter UPBOKL defines the electrical
// length expressed in dB at 1 MHz, kl0, which may also be configured by
// the OLT. Its value ranges from 0 (0.0 dB) to 1280 (128.0 dB).
// If the force electrical length parameter UPBOKLF is 1, the VTU-R is
// forced to use the electrical length from this attribute (UPBOKL) to
// compute UPBO. Otherwise, the VTUs determine the electrical length
// themselves.
//   Upstream band 1 a 2 bytes
//                   b 2 bytes
//   Upstream band 2 a 2 bytes
//                   b 2 bytes
//   Upstream band 3 a 2 bytes
//                   b 2 bytes
//   Upstream band 4 a 2 bytes
//                   b 2 bytes
//   Upstream band 5 a 2 bytes
//                   b 2 bytes
//   UPBOKL            2 bytes
//   UPBOKLF           1 byte
(R, W) (mandatory) (23 bytes)

Cyclic extension:
// The CEFLAG attribute enables (1) the optional cyclic extension values.
// If set to 0, the cyclic extension is forced to the mandatory length 5N/32.
(R, W) (mandatory) (1 byte)

Downstream SNR mode:
// The SNRMODEds attribute controls transmitter referred virtual noise in
// the downstream direction. If set to 1, virtual noise is disabled. If set to 2,
// virtual noise is enabled.
(R, W) (mandatory) (1 byte)

Upstream SNR mode:
// The SNRMODEus attribute controls transmitter referred virtual noise in
// the upstream direction. If set to 1, virtual noise is disabled. If set to 2,
// virtual noise is enabled.
(R, W) (mandatory) (1 byte)

Transmitter referred virtual noise downstream table:
// The TXREFVNds table defines the downstream transmitter referred
// virtual noise. TXREFVNds is specified through a set of breakpoints.
// Each breakpoint comprises a subcarrier index t, with a subcarrier spacing
// of 4.3125 kHz, and a noise PSD level at that subcarrier. The set of
// breakpoints can then be represented as [(t1, PSD1), (t2, PSD2), ... ,
// (tN, PSDN)]. The subcarrier index t is an unsigned two-byte integer. The
// noise level is one byte whose value ranges from 0 (-40 dBm/Hz) to 200
// (-140 dBm/Hz), in steps of 0.5 dB. Values between 201 and 254 indicate
// a noise PSD level of 0 W/Hz. The maximum number of breakpoints
// is 32.
// Table entries for this attribute have default value 254 for the noise PSD
// level. Entries are added or modified using the set action. Setting an entry
// to a noise PSD level less than or equal to 254 implies insertion into the
// table. Setting an entrys noise PSD level to 255 implies deletion from the
// table, if present.
// NOTE 3 - OMCI does not provide robust exception handling when more than
//   one entry is included in a set command, and multiple values per set operation
//   are not recommended.
(R, W) (optional) (3N bytes, where N is the number of breakpoints)

Transmitter referred virtual noise upstream table:
// The TXREFVNus attribute defines the upstream transmitter referred
// virtual noise. TXREFVNus is specified through a set of breakpoints.
// Each breakpoint comprises a subcarrier index t, with a subcarrier spacing
// of 4.3125 kHz, and a noise PSD level at that subcarrier. The set of
// breakpoints can then be represented as [(t1, PSD1), (t2, PSD2), ... ,
// (tN, PSDN)]. The subcarrier index t is an unsigned two-byte integer. The
// noise level is one byte whose value ranges from 0 (-40 dBm/Hz) to 200
// (-140 dBm/Hz), in steps of 0.5 dB. Values between 201 and 254 indicate
// a noise PSD level of 0 W/Hz. The maximum number of breakpoints
// is 16.
// Table entries for this attribute have default value 254 for the noise PSD
// level. Entries are added or modified using the set action. Setting an entry
// to a noise PSD level less than or equal to 254 implies insertion into the
// table. Setting an entrys noise PSD level to 255 implies deletion from the
// table, if present.
// NOTE 4 - OMCI does not provide robust exception handling when more than
//   one entry is included in a set command, and multiple values per set
//   operation are not recommended.
(R, W) (optional) (3N bytes, where N is the number of breakpoints)

DPBOSHAPED:
// Downstream power back-off - shaped as described in [ITU-T G.997.1]
// as a vector of parameters that modifies the downstream PSD mask.
//
// DPBOEPSD - Assumed exchange PSD mask. This component points to
//   an xDSL downstream PSD mask profile managed entity. It should
//   contain not more than 16 break points. (2 bytes)
// DPBOESEL - E-side electrical length. This component is the assumed
//   loss at some reference frequency of the electrical cable from the xDSL
//   equipment to a possible flexibility point. It ranges from 0 (0.0 dB) to 511
//   (255.5 dB) in steps of 0.5 dB. The value 0 has the special meaning that it
//   disables the DPBOSHAPED feature. (2 bytes)
//
// The following three parameters describe the cable model. Further detail
// appears in [ITU-T G.997.1]. Each is a scalar that represents the range -1
// (coded as 0) to +1.5 (coded as 640) in steps of 1/256.
//
// DPBOESCMA - (2 bytes)
// DPBOESCMB - (2 bytes)
// DPBOESCMC - (2 bytes)
//
// DPBOMUS - Assumed minimum usable receive PSD mask. This
//   component ranges from 0 (0.0 dBm/Hz) to 255 (-127.5 dBm/Hz) in steps
//   of 0.5 dB. (1 byte)
// DPBOFMIN - The lower frequency bound above which DPBO is
//   applied. This component ranges from 0 (0.00 kHz) to 2048
//   (8832.00 kHz) in steps of 4.3125 kHz. (2 bytes)
// DPBOFMAX - The upper frequency bound below which DPBO is
//   applied. This component ranges from 32 (138.00 kHz) to 6956
//   (29997.75 kHz) in steps of 4.3125 kHz. (2 bytes)
(R, W) (optional) (15 bytes)

Actions
Create, delete, get, get next, set
