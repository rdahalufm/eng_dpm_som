#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="../UFM Library/DPM/src/dpm_adc.c" "../UFM Library/DPM/src/dpm_bsp.c" "../UFM Library/DPM/src/dpm_cal.c" "../UFM Library/DPM/src/dpm_eeprom.c" "../UFM Library/DPM/src/dpm_flow.c" "../UFM Library/DPM/src/dpm_interrupt.c" "../UFM Library/DPM/src/dpm_lcd.c" "../UFM Library/DPM/src/dpm_menu.c" "../UFM Library/DPM/src/dpm_protocol.c" "../UFM Library/DPM/src/dpm_datalogger.c" "../UFM Library/DPM/src/dpm_config_read.c" "../UFM Library/DPM/usb lib/MDD_File_System/FSIO.c" "../UFM Library/DPM/usb lib/USB/usb_config.c" "../UFM Library/DPM/usb lib/USB/usb_host.c" "../UFM Library/DPM/usb lib/USB/usb_host_msd.c" "../UFM Library/DPM/usb lib/USB/usb_host_msd_scsi.c" pic32/plat.c rpc/wrapper/dd/goal_dd_rpc_ac.c rpc/goal_mctc/goal_mctc.c rpc/goal_mctc/goal_mctc_rb.c rpc/goal_media/goal_ma_chan_tcp.c rpc/goal_media/goal_ma_chan_udp.c rpc/goal_media/goal_ma_net.c rpc/goal_media/goal_ma_net_minimal.c rpc/goal_media/goal_mi_dm.c rpc/goal_media/goal_mi_mctc.c rpc/wrapper/ccm/ccm_rpc_ac.c rpc/wrapper/http/goal_http_ac.c rpc/wrapper/net/ctc_net_ac.c rpc/wrapper/net/ctc_net_list.c rpc/wrapper/pnio/goal_pnio_rpc_ac.c rpc/wrapper/pnio/goal_snmp_ac.c sapi/sapi.c ugoal/goal_inst.c ugoal/ugoal.c ugoal/ugoal_buffer.c main.c pnet_app.c goal_appl.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1970182031/dpm_adc.o ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o ${OBJECTDIR}/_ext/1970182031/dpm_cal.o ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o ${OBJECTDIR}/_ext/1970182031/dpm_flow.o ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o ${OBJECTDIR}/_ext/1970182031/dpm_menu.o ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o ${OBJECTDIR}/_ext/1219524773/FSIO.o ${OBJECTDIR}/_ext/421586199/usb_config.o ${OBJECTDIR}/_ext/421586199/usb_host.o ${OBJECTDIR}/_ext/421586199/usb_host_msd.o ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o ${OBJECTDIR}/pic32/plat.o ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o ${OBJECTDIR}/sapi/sapi.o ${OBJECTDIR}/ugoal/goal_inst.o ${OBJECTDIR}/ugoal/ugoal.o ${OBJECTDIR}/ugoal/ugoal_buffer.o ${OBJECTDIR}/main.o ${OBJECTDIR}/pnet_app.o ${OBJECTDIR}/goal_appl.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d ${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d ${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d ${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d ${OBJECTDIR}/_ext/1219524773/FSIO.o.d ${OBJECTDIR}/_ext/421586199/usb_config.o.d ${OBJECTDIR}/_ext/421586199/usb_host.o.d ${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d ${OBJECTDIR}/pic32/plat.o.d ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o.d ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o.d ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o.d ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o.d ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o.d ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o.d ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o.d ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o.d ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o.d ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o.d ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o.d ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o.d ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o.d ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o.d ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o.d ${OBJECTDIR}/sapi/sapi.o.d ${OBJECTDIR}/ugoal/goal_inst.o.d ${OBJECTDIR}/ugoal/ugoal.o.d ${OBJECTDIR}/ugoal/ugoal_buffer.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/pnet_app.o.d ${OBJECTDIR}/goal_appl.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1970182031/dpm_adc.o ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o ${OBJECTDIR}/_ext/1970182031/dpm_cal.o ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o ${OBJECTDIR}/_ext/1970182031/dpm_flow.o ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o ${OBJECTDIR}/_ext/1970182031/dpm_menu.o ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o ${OBJECTDIR}/_ext/1219524773/FSIO.o ${OBJECTDIR}/_ext/421586199/usb_config.o ${OBJECTDIR}/_ext/421586199/usb_host.o ${OBJECTDIR}/_ext/421586199/usb_host_msd.o ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o ${OBJECTDIR}/pic32/plat.o ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o ${OBJECTDIR}/sapi/sapi.o ${OBJECTDIR}/ugoal/goal_inst.o ${OBJECTDIR}/ugoal/ugoal.o ${OBJECTDIR}/ugoal/ugoal_buffer.o ${OBJECTDIR}/main.o ${OBJECTDIR}/pnet_app.o ${OBJECTDIR}/goal_appl.o

# Source Files
SOURCEFILES=../UFM Library/DPM/src/dpm_adc.c ../UFM Library/DPM/src/dpm_bsp.c ../UFM Library/DPM/src/dpm_cal.c ../UFM Library/DPM/src/dpm_eeprom.c ../UFM Library/DPM/src/dpm_flow.c ../UFM Library/DPM/src/dpm_interrupt.c ../UFM Library/DPM/src/dpm_lcd.c ../UFM Library/DPM/src/dpm_menu.c ../UFM Library/DPM/src/dpm_protocol.c ../UFM Library/DPM/src/dpm_datalogger.c ../UFM Library/DPM/src/dpm_config_read.c ../UFM Library/DPM/usb lib/MDD_File_System/FSIO.c ../UFM Library/DPM/usb lib/USB/usb_config.c ../UFM Library/DPM/usb lib/USB/usb_host.c ../UFM Library/DPM/usb lib/USB/usb_host_msd.c ../UFM Library/DPM/usb lib/USB/usb_host_msd_scsi.c pic32/plat.c rpc/wrapper/dd/goal_dd_rpc_ac.c rpc/goal_mctc/goal_mctc.c rpc/goal_mctc/goal_mctc_rb.c rpc/goal_media/goal_ma_chan_tcp.c rpc/goal_media/goal_ma_chan_udp.c rpc/goal_media/goal_ma_net.c rpc/goal_media/goal_ma_net_minimal.c rpc/goal_media/goal_mi_dm.c rpc/goal_media/goal_mi_mctc.c rpc/wrapper/ccm/ccm_rpc_ac.c rpc/wrapper/http/goal_http_ac.c rpc/wrapper/net/ctc_net_ac.c rpc/wrapper/net/ctc_net_list.c rpc/wrapper/pnio/goal_pnio_rpc_ac.c rpc/wrapper/pnio/goal_snmp_ac.c sapi/sapi.c ugoal/goal_inst.c ugoal/ugoal.c ugoal/ugoal_buffer.c main.c pnet_app.c goal_appl.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX440F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1970182031/dpm_adc.o: ../UFM\ Library/DPM/src/dpm_adc.c  .generated_files/flags/default/4c2fe1da596c7e7560099f7dd1718989afca240b .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_adc.o "../UFM Library/DPM/src/dpm_adc.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_bsp.o: ../UFM\ Library/DPM/src/dpm_bsp.c  .generated_files/flags/default/33089438f7b657b949cda6962a6aa7b5207338c3 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o "../UFM Library/DPM/src/dpm_bsp.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_cal.o: ../UFM\ Library/DPM/src/dpm_cal.c  .generated_files/flags/default/293f8eec52817e99be48e74db3607be9f99e6bc5 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_cal.o "../UFM Library/DPM/src/dpm_cal.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o: ../UFM\ Library/DPM/src/dpm_eeprom.c  .generated_files/flags/default/dc3192b47c76b70866122bd5c741420a7add273 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o "../UFM Library/DPM/src/dpm_eeprom.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_flow.o: ../UFM\ Library/DPM/src/dpm_flow.c  .generated_files/flags/default/d46d25ae9a7987c2b73fceb5fae1e315bc82afb1 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_flow.o "../UFM Library/DPM/src/dpm_flow.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o: ../UFM\ Library/DPM/src/dpm_interrupt.c  .generated_files/flags/default/e9872f440c2d48f26a48815494a32813b77d636d .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o "../UFM Library/DPM/src/dpm_interrupt.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_lcd.o: ../UFM\ Library/DPM/src/dpm_lcd.c  .generated_files/flags/default/8766b7741c2206bb8062ebe0f68135799df50b34 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o "../UFM Library/DPM/src/dpm_lcd.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_menu.o: ../UFM\ Library/DPM/src/dpm_menu.c  .generated_files/flags/default/e4dcc75d3d40019b4ef55ed71da11d72afe92350 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_menu.o "../UFM Library/DPM/src/dpm_menu.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_protocol.o: ../UFM\ Library/DPM/src/dpm_protocol.c  .generated_files/flags/default/20f744c41a85b62960e5bc63ff6ec5e7fd25e015 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o "../UFM Library/DPM/src/dpm_protocol.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o: ../UFM\ Library/DPM/src/dpm_datalogger.c  .generated_files/flags/default/d6f3cf4308b774c42a9180e8029c3f18bbbc7624 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o "../UFM Library/DPM/src/dpm_datalogger.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_config_read.o: ../UFM\ Library/DPM/src/dpm_config_read.c  .generated_files/flags/default/7f7cd0faadb3357cccdeede3c1bbb14eaa90462f .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o "../UFM Library/DPM/src/dpm_config_read.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1219524773/FSIO.o: ../UFM\ Library/DPM/usb\ lib/MDD_File_System/FSIO.c  .generated_files/flags/default/6009c82827c7aee320cb31e8e9142904a6563149 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1219524773" 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1219524773/FSIO.o.d" -o ${OBJECTDIR}/_ext/1219524773/FSIO.o "../UFM Library/DPM/usb lib/MDD_File_System/FSIO.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_config.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_config.c  .generated_files/flags/default/7cdc2ac620df2c85444331a0bdf44f77ebfc99b6 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_config.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_config.o "../UFM Library/DPM/usb lib/USB/usb_config.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host.c  .generated_files/flags/default/76fd233a228e5d022cde79b90e143d95425ee730 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host.o "../UFM Library/DPM/usb lib/USB/usb_host.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd.c  .generated_files/flags/default/6826387c6fc5cc70bbd4ffeb9e6d19586b0cff06 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd.o "../UFM Library/DPM/usb lib/USB/usb_host_msd.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd_scsi.c  .generated_files/flags/default/89e99ef7f35cd4810d493f9dcf2af7057974e96b .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o "../UFM Library/DPM/usb lib/USB/usb_host_msd_scsi.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pic32/plat.o: pic32/plat.c  .generated_files/flags/default/86634b3d3156ec0ecd794a0bf933fb2021a779d0 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/pic32" 
	@${RM} ${OBJECTDIR}/pic32/plat.o.d 
	@${RM} ${OBJECTDIR}/pic32/plat.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/pic32/plat.o.d" -o ${OBJECTDIR}/pic32/plat.o pic32/plat.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o: rpc/wrapper/dd/goal_dd_rpc_ac.c  .generated_files/flags/default/2c0e3fa7590bb88f351bd474577fb6af9442b1ef .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/dd" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o rpc/wrapper/dd/goal_dd_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o: rpc/goal_mctc/goal_mctc.c  .generated_files/flags/default/71bcb37fe5597bb9e52ec193cf9f965035189630 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_mctc" 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o.d" -o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o rpc/goal_mctc/goal_mctc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o: rpc/goal_mctc/goal_mctc_rb.c  .generated_files/flags/default/ae85934d33acea218c5d7a87a61f265c71847a1e .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_mctc" 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o.d" -o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o rpc/goal_mctc/goal_mctc_rb.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o: rpc/goal_media/goal_ma_chan_tcp.c  .generated_files/flags/default/a7011b5192106dd862718d0e24c0670d40598150 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o rpc/goal_media/goal_ma_chan_tcp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o: rpc/goal_media/goal_ma_chan_udp.c  .generated_files/flags/default/d43effb01e3c96c68881fdb42a2eba2545ff88df .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o rpc/goal_media/goal_ma_chan_udp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_net.o: rpc/goal_media/goal_ma_net.c  .generated_files/flags/default/cb509de969720c14ed1c05c759a436d5c6f4206c .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_net.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o rpc/goal_media/goal_ma_net.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o: rpc/goal_media/goal_ma_net_minimal.c  .generated_files/flags/default/b5acd0eef22eb4606efa168eedb6d8d0f56a3df .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o rpc/goal_media/goal_ma_net_minimal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o: rpc/goal_media/goal_mi_dm.c  .generated_files/flags/default/db08c20198de94675d9aeb7820150eff6a33d3d1 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o rpc/goal_media/goal_mi_dm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o: rpc/goal_media/goal_mi_mctc.c  .generated_files/flags/default/eddf6accd8f72d8df66fbe6feb899a463b75c9d1 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o rpc/goal_media/goal_mi_mctc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o: rpc/wrapper/ccm/ccm_rpc_ac.c  .generated_files/flags/default/a0243ff2941c5ed33c449b5c093732af6604293d .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/ccm" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o rpc/wrapper/ccm/ccm_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o: rpc/wrapper/http/goal_http_ac.c  .generated_files/flags/default/8bc7a54059cd67b2fb504ddd51a60f0f0a321fce .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/http" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o rpc/wrapper/http/goal_http_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o: rpc/wrapper/net/ctc_net_ac.c  .generated_files/flags/default/6eecd09c2bb6b40c3116d6620c5ba5423e2d8f1 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/net" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o rpc/wrapper/net/ctc_net_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o: rpc/wrapper/net/ctc_net_list.c  .generated_files/flags/default/2d4bf01006756b237cb3938f7f606deb145741a2 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/net" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o.d" -o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o rpc/wrapper/net/ctc_net_list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o: rpc/wrapper/pnio/goal_pnio_rpc_ac.c  .generated_files/flags/default/23017eb6bebafb5b2dce784318ceda38b6b1aeeb .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/pnio" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o rpc/wrapper/pnio/goal_pnio_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o: rpc/wrapper/pnio/goal_snmp_ac.c  .generated_files/flags/default/3f5e37c7d7c8159805b7bbc372c238b76ab566b9 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/pnio" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o rpc/wrapper/pnio/goal_snmp_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sapi/sapi.o: sapi/sapi.c  .generated_files/flags/default/18c3454ad47e876c216ea638a216da588b79d062 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sapi" 
	@${RM} ${OBJECTDIR}/sapi/sapi.o.d 
	@${RM} ${OBJECTDIR}/sapi/sapi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/sapi/sapi.o.d" -o ${OBJECTDIR}/sapi/sapi.o sapi/sapi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/goal_inst.o: ugoal/goal_inst.c  .generated_files/flags/default/1e2e950de978ac353d833302573427e303ef810a .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/goal_inst.o.d 
	@${RM} ${OBJECTDIR}/ugoal/goal_inst.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/goal_inst.o.d" -o ${OBJECTDIR}/ugoal/goal_inst.o ugoal/goal_inst.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/ugoal.o: ugoal/ugoal.c  .generated_files/flags/default/7884711ca923f18596363882f97dfeaf4d9aaf03 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/ugoal.o.d 
	@${RM} ${OBJECTDIR}/ugoal/ugoal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/ugoal.o.d" -o ${OBJECTDIR}/ugoal/ugoal.o ugoal/ugoal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/ugoal_buffer.o: ugoal/ugoal_buffer.c  .generated_files/flags/default/ef0cf89b79ef4a129e70c62a56b1cfcbfe55f20e .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/ugoal_buffer.o.d 
	@${RM} ${OBJECTDIR}/ugoal/ugoal_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/ugoal_buffer.o.d" -o ${OBJECTDIR}/ugoal/ugoal_buffer.o ugoal/ugoal_buffer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/4fcc9a53f1481d7745a357d6e7f034009a168a1f .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pnet_app.o: pnet_app.c  .generated_files/flags/default/c31f4c5c7da822050a7269c4cc5608b00ec3b42d .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pnet_app.o.d 
	@${RM} ${OBJECTDIR}/pnet_app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/pnet_app.o.d" -o ${OBJECTDIR}/pnet_app.o pnet_app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/goal_appl.o: goal_appl.c  .generated_files/flags/default/37c037888f3a79e5e853e2640c0d06197db7d770 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/goal_appl.o.d 
	@${RM} ${OBJECTDIR}/goal_appl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/goal_appl.o.d" -o ${OBJECTDIR}/goal_appl.o goal_appl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/_ext/1970182031/dpm_adc.o: ../UFM\ Library/DPM/src/dpm_adc.c  .generated_files/flags/default/bf11c2f2b032986f90eeadd7115d5ecf3512f859 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_adc.o "../UFM Library/DPM/src/dpm_adc.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_bsp.o: ../UFM\ Library/DPM/src/dpm_bsp.c  .generated_files/flags/default/1738ac576a54733d4b061d282e3b98a2ff6ff99c .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o "../UFM Library/DPM/src/dpm_bsp.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_cal.o: ../UFM\ Library/DPM/src/dpm_cal.c  .generated_files/flags/default/f03cdd3223b3e82cf3175760f2a4d45577dd22f2 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_cal.o "../UFM Library/DPM/src/dpm_cal.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o: ../UFM\ Library/DPM/src/dpm_eeprom.c  .generated_files/flags/default/79cf5061dd080be72a4a04d62765e2507e1c4587 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o "../UFM Library/DPM/src/dpm_eeprom.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_flow.o: ../UFM\ Library/DPM/src/dpm_flow.c  .generated_files/flags/default/d9d22316f8d8a8ee5386d4a18f729eef30d79502 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_flow.o "../UFM Library/DPM/src/dpm_flow.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o: ../UFM\ Library/DPM/src/dpm_interrupt.c  .generated_files/flags/default/72254a5c35dee9c5a86b38a780b20097a081640d .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o "../UFM Library/DPM/src/dpm_interrupt.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_lcd.o: ../UFM\ Library/DPM/src/dpm_lcd.c  .generated_files/flags/default/f14dabd1a7958984bf0115bb5d552f58dda11783 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o "../UFM Library/DPM/src/dpm_lcd.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_menu.o: ../UFM\ Library/DPM/src/dpm_menu.c  .generated_files/flags/default/dc38fa941bad4adb643d236cb1d4cc6ae4b50792 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_menu.o "../UFM Library/DPM/src/dpm_menu.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_protocol.o: ../UFM\ Library/DPM/src/dpm_protocol.c  .generated_files/flags/default/ef8bffb3d665fc9c9a2d62ff73bc343ecf923400 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o "../UFM Library/DPM/src/dpm_protocol.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o: ../UFM\ Library/DPM/src/dpm_datalogger.c  .generated_files/flags/default/266df75eaa2b7838a53cd1a5be0f10c0cc1b512 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o "../UFM Library/DPM/src/dpm_datalogger.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_config_read.o: ../UFM\ Library/DPM/src/dpm_config_read.c  .generated_files/flags/default/ca087861b3cf4a9df83a5ce5022419ae72896c90 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o "../UFM Library/DPM/src/dpm_config_read.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1219524773/FSIO.o: ../UFM\ Library/DPM/usb\ lib/MDD_File_System/FSIO.c  .generated_files/flags/default/9431dbf67c3ecec232165eccad30d935a63ee7e .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1219524773" 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1219524773/FSIO.o.d" -o ${OBJECTDIR}/_ext/1219524773/FSIO.o "../UFM Library/DPM/usb lib/MDD_File_System/FSIO.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_config.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_config.c  .generated_files/flags/default/ade3b472a1c1d7882d62ba36d1284a02c360ce09 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_config.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_config.o "../UFM Library/DPM/usb lib/USB/usb_config.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host.c  .generated_files/flags/default/d0df2a0619faa5b06356f3eb20f370ac4bf34764 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host.o "../UFM Library/DPM/usb lib/USB/usb_host.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd.c  .generated_files/flags/default/3a09c6f91417132300a3b3d698dbae35a14c97a6 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd.o "../UFM Library/DPM/usb lib/USB/usb_host_msd.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd_scsi.c  .generated_files/flags/default/65ca3a0ce83edcc7403c0eb10d021f75b1e33711 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o "../UFM Library/DPM/usb lib/USB/usb_host_msd_scsi.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pic32/plat.o: pic32/plat.c  .generated_files/flags/default/f01ebc08c9294d266eba1b7794f48c167f62ff95 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/pic32" 
	@${RM} ${OBJECTDIR}/pic32/plat.o.d 
	@${RM} ${OBJECTDIR}/pic32/plat.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/pic32/plat.o.d" -o ${OBJECTDIR}/pic32/plat.o pic32/plat.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o: rpc/wrapper/dd/goal_dd_rpc_ac.c  .generated_files/flags/default/5fda9ffa8eddfc182b7d7041c57d508f41544338 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/dd" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o rpc/wrapper/dd/goal_dd_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o: rpc/goal_mctc/goal_mctc.c  .generated_files/flags/default/914e2d2411674389633e6b595be3875f38b6fd7d .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_mctc" 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o.d" -o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o rpc/goal_mctc/goal_mctc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o: rpc/goal_mctc/goal_mctc_rb.c  .generated_files/flags/default/ca86a49cb1fdeca69e7565e57b93777422c0834 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_mctc" 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o.d" -o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o rpc/goal_mctc/goal_mctc_rb.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o: rpc/goal_media/goal_ma_chan_tcp.c  .generated_files/flags/default/3079fd00b4d9b0bc649e00660ea29337c38bd153 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o rpc/goal_media/goal_ma_chan_tcp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o: rpc/goal_media/goal_ma_chan_udp.c  .generated_files/flags/default/6c43ae1db64373d04569282b0cb757b845e648f4 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o rpc/goal_media/goal_ma_chan_udp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_net.o: rpc/goal_media/goal_ma_net.c  .generated_files/flags/default/e26a4cf3961b3eec24146f520e342945e6c07920 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_net.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o rpc/goal_media/goal_ma_net.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o: rpc/goal_media/goal_ma_net_minimal.c  .generated_files/flags/default/2cb50b420ae5ccebc71b127c2ef8c6c3a8b8bad5 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o rpc/goal_media/goal_ma_net_minimal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o: rpc/goal_media/goal_mi_dm.c  .generated_files/flags/default/e1af99258cd78d27beb379ee8f0f52d3d3813d12 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o rpc/goal_media/goal_mi_dm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o: rpc/goal_media/goal_mi_mctc.c  .generated_files/flags/default/97416994ab6b1010e8cc69a59e5d618bb6eaa327 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o rpc/goal_media/goal_mi_mctc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o: rpc/wrapper/ccm/ccm_rpc_ac.c  .generated_files/flags/default/ffd9d75a675e2c7e00a8276066e2510db9ca1351 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/ccm" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o rpc/wrapper/ccm/ccm_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o: rpc/wrapper/http/goal_http_ac.c  .generated_files/flags/default/53dfdafd9c61ea13e269b819ba35e8a3b4c8e7df .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/http" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o rpc/wrapper/http/goal_http_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o: rpc/wrapper/net/ctc_net_ac.c  .generated_files/flags/default/f104d8d91ed9e0f5f1f1dbfb72b3cc0a6bc1d10e .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/net" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o rpc/wrapper/net/ctc_net_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o: rpc/wrapper/net/ctc_net_list.c  .generated_files/flags/default/c697eca0b1722c1d6595ce60b7f06c16ad1dd18a .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/net" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o.d" -o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o rpc/wrapper/net/ctc_net_list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o: rpc/wrapper/pnio/goal_pnio_rpc_ac.c  .generated_files/flags/default/57e029f8387702a72a444192b002c8afc1cb7c3a .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/pnio" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o rpc/wrapper/pnio/goal_pnio_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o: rpc/wrapper/pnio/goal_snmp_ac.c  .generated_files/flags/default/d19c15c5d79fd9cf04cdae9ffb9e5389e0f020d3 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/pnio" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o rpc/wrapper/pnio/goal_snmp_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sapi/sapi.o: sapi/sapi.c  .generated_files/flags/default/d1ec0e97d2dd2d0e4242aad616622080b4c3ffa5 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sapi" 
	@${RM} ${OBJECTDIR}/sapi/sapi.o.d 
	@${RM} ${OBJECTDIR}/sapi/sapi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/sapi/sapi.o.d" -o ${OBJECTDIR}/sapi/sapi.o sapi/sapi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/goal_inst.o: ugoal/goal_inst.c  .generated_files/flags/default/dcd2de51693be96fabcbdc1fdf9a03a95103a2d3 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/goal_inst.o.d 
	@${RM} ${OBJECTDIR}/ugoal/goal_inst.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/goal_inst.o.d" -o ${OBJECTDIR}/ugoal/goal_inst.o ugoal/goal_inst.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/ugoal.o: ugoal/ugoal.c  .generated_files/flags/default/7a294771d1873fb4a4722cf062e3e98df58c53e3 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/ugoal.o.d 
	@${RM} ${OBJECTDIR}/ugoal/ugoal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/ugoal.o.d" -o ${OBJECTDIR}/ugoal/ugoal.o ugoal/ugoal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/ugoal_buffer.o: ugoal/ugoal_buffer.c  .generated_files/flags/default/f228b81310a28c95f379ec115dd8f0893176d425 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/ugoal_buffer.o.d 
	@${RM} ${OBJECTDIR}/ugoal/ugoal_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/ugoal_buffer.o.d" -o ${OBJECTDIR}/ugoal/ugoal_buffer.o ugoal/ugoal_buffer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/9f4d8de0479789b41ef9c3c4f8c6530655859111 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pnet_app.o: pnet_app.c  .generated_files/flags/default/f74d10ea47e9544ba95484a1e3f5371e99a6eea .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pnet_app.o.d 
	@${RM} ${OBJECTDIR}/pnet_app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/pnet_app.o.d" -o ${OBJECTDIR}/pnet_app.o pnet_app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/goal_appl.o: goal_appl.c  .generated_files/flags/default/959308a8b36049a63c72bafe4d1d28ce6b3a712d .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/goal_appl.o.d 
	@${RM} ${OBJECTDIR}/goal_appl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/goal_appl.o.d" -o ${OBJECTDIR}/goal_appl.o goal_appl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,--defsym=_min_heap_size=2000,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2000,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem 
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
