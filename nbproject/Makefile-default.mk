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
${OBJECTDIR}/_ext/1970182031/dpm_adc.o: ../UFM\ Library/DPM/src/dpm_adc.c  .generated_files/flags/default/fa9fc5e94364ba0eda74ebd9d6e1d292b3c93bb0 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_adc.o "../UFM Library/DPM/src/dpm_adc.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_bsp.o: ../UFM\ Library/DPM/src/dpm_bsp.c  .generated_files/flags/default/63710eecb746f61d4963adae5241ddba8ec459c5 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o "../UFM Library/DPM/src/dpm_bsp.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_cal.o: ../UFM\ Library/DPM/src/dpm_cal.c  .generated_files/flags/default/679abb6772d15c14973f0b92891723271f9dcce .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_cal.o "../UFM Library/DPM/src/dpm_cal.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o: ../UFM\ Library/DPM/src/dpm_eeprom.c  .generated_files/flags/default/cb329d57664d80f7093302a6f5ff9677cc0078dd .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o "../UFM Library/DPM/src/dpm_eeprom.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_flow.o: ../UFM\ Library/DPM/src/dpm_flow.c  .generated_files/flags/default/94b82ee716babcb4fcb5ba7be191c910dafff4d5 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_flow.o "../UFM Library/DPM/src/dpm_flow.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o: ../UFM\ Library/DPM/src/dpm_interrupt.c  .generated_files/flags/default/2d7a9416981424004d06b4a5491d294df076601b .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o "../UFM Library/DPM/src/dpm_interrupt.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_lcd.o: ../UFM\ Library/DPM/src/dpm_lcd.c  .generated_files/flags/default/9a432f7bf8f7f6feb1e8d08562bc055f1da889f8 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o "../UFM Library/DPM/src/dpm_lcd.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_menu.o: ../UFM\ Library/DPM/src/dpm_menu.c  .generated_files/flags/default/2d1ac5f03adf2a38dc0d7f563a9a71dfd213b36c .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_menu.o "../UFM Library/DPM/src/dpm_menu.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_protocol.o: ../UFM\ Library/DPM/src/dpm_protocol.c  .generated_files/flags/default/1cd13bd8253a0e37312d6a779974f4922f317f3f .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o "../UFM Library/DPM/src/dpm_protocol.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o: ../UFM\ Library/DPM/src/dpm_datalogger.c  .generated_files/flags/default/ca85f8c3329fbe4f9b818d01ecaae5e69a5d156d .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o "../UFM Library/DPM/src/dpm_datalogger.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_config_read.o: ../UFM\ Library/DPM/src/dpm_config_read.c  .generated_files/flags/default/24ebe1091bcab2f23a677d39c5bec863288ec667 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o "../UFM Library/DPM/src/dpm_config_read.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1219524773/FSIO.o: ../UFM\ Library/DPM/usb\ lib/MDD_File_System/FSIO.c  .generated_files/flags/default/2983dc5940b6abda99f5c2fe6fdba1f156ecf74 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1219524773" 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1219524773/FSIO.o.d" -o ${OBJECTDIR}/_ext/1219524773/FSIO.o "../UFM Library/DPM/usb lib/MDD_File_System/FSIO.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_config.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_config.c  .generated_files/flags/default/20306243ac8353a6fb237bf69dad471e4b4d88e3 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_config.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_config.o "../UFM Library/DPM/usb lib/USB/usb_config.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host.c  .generated_files/flags/default/fa81d7c2392d44cddb5ea7b1c628dc90b3c4980 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host.o "../UFM Library/DPM/usb lib/USB/usb_host.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd.c  .generated_files/flags/default/fb056ba6c06174754a08004936303b5282f0fa61 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd.o "../UFM Library/DPM/usb lib/USB/usb_host_msd.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd_scsi.c  .generated_files/flags/default/390752415a81e3a450f0098b38c2d04426ff2b98 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o "../UFM Library/DPM/usb lib/USB/usb_host_msd_scsi.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pic32/plat.o: pic32/plat.c  .generated_files/flags/default/8c639e7c931c61236a6aee9257f985d0bdae7168 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/pic32" 
	@${RM} ${OBJECTDIR}/pic32/plat.o.d 
	@${RM} ${OBJECTDIR}/pic32/plat.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/pic32/plat.o.d" -o ${OBJECTDIR}/pic32/plat.o pic32/plat.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o: rpc/wrapper/dd/goal_dd_rpc_ac.c  .generated_files/flags/default/f23b0556eb8f84d5daa9e401b911cf1e001b4c3a .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/dd" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o rpc/wrapper/dd/goal_dd_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o: rpc/goal_mctc/goal_mctc.c  .generated_files/flags/default/6c277ae7b8ca732764cf05f07b7a1b8bdf1f84e9 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_mctc" 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o.d" -o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o rpc/goal_mctc/goal_mctc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o: rpc/goal_mctc/goal_mctc_rb.c  .generated_files/flags/default/eeed6a05ec3dc64a1092d572c4fcd162c03301 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_mctc" 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o.d" -o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o rpc/goal_mctc/goal_mctc_rb.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o: rpc/goal_media/goal_ma_chan_tcp.c  .generated_files/flags/default/9680a3c82fe86bc9f24f36ce85c1bc35c9e44ad2 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o rpc/goal_media/goal_ma_chan_tcp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o: rpc/goal_media/goal_ma_chan_udp.c  .generated_files/flags/default/511afa92fd8f56c0d11db6e95b7bb63abc9da40 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o rpc/goal_media/goal_ma_chan_udp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_net.o: rpc/goal_media/goal_ma_net.c  .generated_files/flags/default/6d76687df301d5a38a28fb9fb402bebc831d7ec5 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_net.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o rpc/goal_media/goal_ma_net.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o: rpc/goal_media/goal_ma_net_minimal.c  .generated_files/flags/default/4ced146ec918fe5c27e0a5cb5477d7cf198e4c37 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o rpc/goal_media/goal_ma_net_minimal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o: rpc/goal_media/goal_mi_dm.c  .generated_files/flags/default/30cdd754c335b0d6e06b8c280c0a94b406996258 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o rpc/goal_media/goal_mi_dm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o: rpc/goal_media/goal_mi_mctc.c  .generated_files/flags/default/5a8f306f2295fc4d0fa586bd4930a2201d955c74 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o rpc/goal_media/goal_mi_mctc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o: rpc/wrapper/ccm/ccm_rpc_ac.c  .generated_files/flags/default/f731f131d1f65c7b1f8c515f1390cf4ce8e80eff .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/ccm" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o rpc/wrapper/ccm/ccm_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o: rpc/wrapper/http/goal_http_ac.c  .generated_files/flags/default/1952b195d9b68d3998eb89e9b0ddbe4b2478200b .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/http" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o rpc/wrapper/http/goal_http_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o: rpc/wrapper/net/ctc_net_ac.c  .generated_files/flags/default/14450c2f2016fd3d3ee39db8c3dd62a487cac491 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/net" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o rpc/wrapper/net/ctc_net_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o: rpc/wrapper/net/ctc_net_list.c  .generated_files/flags/default/e35c5283dff3f002d34943cc05da7f4699187888 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/net" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o.d" -o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o rpc/wrapper/net/ctc_net_list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o: rpc/wrapper/pnio/goal_pnio_rpc_ac.c  .generated_files/flags/default/76b6488c42f0ccb2067d3f7433ae3ae4fb940c90 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/pnio" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o rpc/wrapper/pnio/goal_pnio_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o: rpc/wrapper/pnio/goal_snmp_ac.c  .generated_files/flags/default/4b48eaef4726c5e35dd4e1f0d0f32b20576db32d .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/pnio" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o rpc/wrapper/pnio/goal_snmp_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sapi/sapi.o: sapi/sapi.c  .generated_files/flags/default/c4ac4b8badfee38567245040c93c7d9c9a508d8c .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sapi" 
	@${RM} ${OBJECTDIR}/sapi/sapi.o.d 
	@${RM} ${OBJECTDIR}/sapi/sapi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/sapi/sapi.o.d" -o ${OBJECTDIR}/sapi/sapi.o sapi/sapi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/goal_inst.o: ugoal/goal_inst.c  .generated_files/flags/default/5a30be9e259928ef00bb4425a891abb644975196 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/goal_inst.o.d 
	@${RM} ${OBJECTDIR}/ugoal/goal_inst.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/goal_inst.o.d" -o ${OBJECTDIR}/ugoal/goal_inst.o ugoal/goal_inst.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/ugoal.o: ugoal/ugoal.c  .generated_files/flags/default/403c11ad4b6add5caf46045f8b6ee630f35dcd12 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/ugoal.o.d 
	@${RM} ${OBJECTDIR}/ugoal/ugoal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/ugoal.o.d" -o ${OBJECTDIR}/ugoal/ugoal.o ugoal/ugoal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/ugoal_buffer.o: ugoal/ugoal_buffer.c  .generated_files/flags/default/19b15b0e924b29bcc288f169cdb31249bbf448c0 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/ugoal_buffer.o.d 
	@${RM} ${OBJECTDIR}/ugoal/ugoal_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/ugoal_buffer.o.d" -o ${OBJECTDIR}/ugoal/ugoal_buffer.o ugoal/ugoal_buffer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/c71a6ab54f3eaad0a5d787c62eb65d0fd8672f13 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pnet_app.o: pnet_app.c  .generated_files/flags/default/d3d2ffb690de2ef634608597e0ef680eea5a44f2 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pnet_app.o.d 
	@${RM} ${OBJECTDIR}/pnet_app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/pnet_app.o.d" -o ${OBJECTDIR}/pnet_app.o pnet_app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/goal_appl.o: goal_appl.c  .generated_files/flags/default/72285d902b75d15b0d3d6576797ccacec6683af0 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/goal_appl.o.d 
	@${RM} ${OBJECTDIR}/goal_appl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/goal_appl.o.d" -o ${OBJECTDIR}/goal_appl.o goal_appl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/_ext/1970182031/dpm_adc.o: ../UFM\ Library/DPM/src/dpm_adc.c  .generated_files/flags/default/d380f0a79adf17f13ddedcb9635d2ec69459b57b .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_adc.o "../UFM Library/DPM/src/dpm_adc.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_bsp.o: ../UFM\ Library/DPM/src/dpm_bsp.c  .generated_files/flags/default/9072e8f1634ccc561d83fb80f6a886fc13140275 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o "../UFM Library/DPM/src/dpm_bsp.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_cal.o: ../UFM\ Library/DPM/src/dpm_cal.c  .generated_files/flags/default/410357e3aaba7c9877fc20c4764a7d60e32eee73 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_cal.o "../UFM Library/DPM/src/dpm_cal.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o: ../UFM\ Library/DPM/src/dpm_eeprom.c  .generated_files/flags/default/246d5df458f508007bb0a83935b4badf38396c0d .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o "../UFM Library/DPM/src/dpm_eeprom.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_flow.o: ../UFM\ Library/DPM/src/dpm_flow.c  .generated_files/flags/default/27a1be1732dc18f350f21cde2a98983c0cbb492c .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_flow.o "../UFM Library/DPM/src/dpm_flow.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o: ../UFM\ Library/DPM/src/dpm_interrupt.c  .generated_files/flags/default/6637ec5c7d02759221f7bb43288f2448d85c98ee .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o "../UFM Library/DPM/src/dpm_interrupt.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_lcd.o: ../UFM\ Library/DPM/src/dpm_lcd.c  .generated_files/flags/default/730bed50a4fc19af57c2540bbc1dcb8f6c06ee .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o "../UFM Library/DPM/src/dpm_lcd.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_menu.o: ../UFM\ Library/DPM/src/dpm_menu.c  .generated_files/flags/default/ac3828b75ab1c064fcd42dfab79d831b32fa1a28 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_menu.o "../UFM Library/DPM/src/dpm_menu.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_protocol.o: ../UFM\ Library/DPM/src/dpm_protocol.c  .generated_files/flags/default/c84086bc4c291b02f5749a397416951dee055654 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o "../UFM Library/DPM/src/dpm_protocol.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o: ../UFM\ Library/DPM/src/dpm_datalogger.c  .generated_files/flags/default/efb3add8b7b6089c3b6b6398873e0b9dae1da019 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o "../UFM Library/DPM/src/dpm_datalogger.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_config_read.o: ../UFM\ Library/DPM/src/dpm_config_read.c  .generated_files/flags/default/286a9838dfed62a0b7bbfc070c386fc8f0670a98 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o "../UFM Library/DPM/src/dpm_config_read.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1219524773/FSIO.o: ../UFM\ Library/DPM/usb\ lib/MDD_File_System/FSIO.c  .generated_files/flags/default/2b37b0d66aeb87390d6ed1c68e67c911f892440f .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1219524773" 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/1219524773/FSIO.o.d" -o ${OBJECTDIR}/_ext/1219524773/FSIO.o "../UFM Library/DPM/usb lib/MDD_File_System/FSIO.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_config.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_config.c  .generated_files/flags/default/cba14be514a730d6aa104769430e0e1a46b542b4 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_config.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_config.o "../UFM Library/DPM/usb lib/USB/usb_config.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host.c  .generated_files/flags/default/54500f4f90799a42462d8abeaefa40593c4bc9c0 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host.o "../UFM Library/DPM/usb lib/USB/usb_host.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd.c  .generated_files/flags/default/13193c9f4294abd606c3a856f88325d02d12211 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd.o "../UFM Library/DPM/usb lib/USB/usb_host_msd.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd_scsi.c  .generated_files/flags/default/dae1b4917f6e420558cf610870147a74dce8bb76 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o "../UFM Library/DPM/usb lib/USB/usb_host_msd_scsi.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pic32/plat.o: pic32/plat.c  .generated_files/flags/default/8f68d6de08dbb777e81b88be2a6de4d1b032941d .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/pic32" 
	@${RM} ${OBJECTDIR}/pic32/plat.o.d 
	@${RM} ${OBJECTDIR}/pic32/plat.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/pic32/plat.o.d" -o ${OBJECTDIR}/pic32/plat.o pic32/plat.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o: rpc/wrapper/dd/goal_dd_rpc_ac.c  .generated_files/flags/default/93987507c69fc6598f8c579c91c7f9d609aa57e2 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/dd" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/dd/goal_dd_rpc_ac.o rpc/wrapper/dd/goal_dd_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o: rpc/goal_mctc/goal_mctc.c  .generated_files/flags/default/1d8c683e2608e6da67928b651ce38807ec45edb6 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_mctc" 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o.d" -o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc.o rpc/goal_mctc/goal_mctc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o: rpc/goal_mctc/goal_mctc_rb.c  .generated_files/flags/default/5eb85e342cf9b41ce25c15c7611ccdaa01fed41e .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_mctc" 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o.d" -o ${OBJECTDIR}/rpc/goal_mctc/goal_mctc_rb.o rpc/goal_mctc/goal_mctc_rb.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o: rpc/goal_media/goal_ma_chan_tcp.c  .generated_files/flags/default/eabac301aaeed9ced2424033799abb274b2e6d3 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_tcp.o rpc/goal_media/goal_ma_chan_tcp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o: rpc/goal_media/goal_ma_chan_udp.c  .generated_files/flags/default/7eb925d3c64f93e289b7fdd92e92a45fd317f997 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_chan_udp.o rpc/goal_media/goal_ma_chan_udp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_net.o: rpc/goal_media/goal_ma_net.c  .generated_files/flags/default/5cc2beed433260338c6c0e140322cf80edc97d50 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_net.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_net.o rpc/goal_media/goal_ma_net.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o: rpc/goal_media/goal_ma_net_minimal.c  .generated_files/flags/default/421e4b942819b8b28485a8b48424b4a2a5e64a01 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_ma_net_minimal.o rpc/goal_media/goal_ma_net_minimal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o: rpc/goal_media/goal_mi_dm.c  .generated_files/flags/default/8089cd357c46fe6d6f2a6f258f0553725a7f37b9 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_mi_dm.o rpc/goal_media/goal_mi_dm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o: rpc/goal_media/goal_mi_mctc.c  .generated_files/flags/default/dee23edfc45fdc9700587487344e38e68e936e42 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/goal_media" 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o.d 
	@${RM} ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o.d" -o ${OBJECTDIR}/rpc/goal_media/goal_mi_mctc.o rpc/goal_media/goal_mi_mctc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o: rpc/wrapper/ccm/ccm_rpc_ac.c  .generated_files/flags/default/78f9bd38c519b3a241ae3072be9fba4a52806f96 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/ccm" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/ccm/ccm_rpc_ac.o rpc/wrapper/ccm/ccm_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o: rpc/wrapper/http/goal_http_ac.c  .generated_files/flags/default/bdbabb116f26cd4230911c0ff60d553df6bef66f .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/http" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/http/goal_http_ac.o rpc/wrapper/http/goal_http_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o: rpc/wrapper/net/ctc_net_ac.c  .generated_files/flags/default/219d307a47c25afe1833b4bcd645fb423276a93 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/net" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_ac.o rpc/wrapper/net/ctc_net_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o: rpc/wrapper/net/ctc_net_list.c  .generated_files/flags/default/9e5dc27fbeea657634977f3312b06d811046760e .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/net" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o.d" -o ${OBJECTDIR}/rpc/wrapper/net/ctc_net_list.o rpc/wrapper/net/ctc_net_list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o: rpc/wrapper/pnio/goal_pnio_rpc_ac.c  .generated_files/flags/default/70254c5b0e8c58bbb2ebdbca173146a1726b9d61 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/pnio" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/pnio/goal_pnio_rpc_ac.o rpc/wrapper/pnio/goal_pnio_rpc_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o: rpc/wrapper/pnio/goal_snmp_ac.c  .generated_files/flags/default/af059d8d6e3d638ea200e02b18f8c667e2f0157c .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/rpc/wrapper/pnio" 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o.d 
	@${RM} ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o.d" -o ${OBJECTDIR}/rpc/wrapper/pnio/goal_snmp_ac.o rpc/wrapper/pnio/goal_snmp_ac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sapi/sapi.o: sapi/sapi.c  .generated_files/flags/default/963b09f2c57bddc371b8daa79e8a0f8fa44038f5 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sapi" 
	@${RM} ${OBJECTDIR}/sapi/sapi.o.d 
	@${RM} ${OBJECTDIR}/sapi/sapi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/sapi/sapi.o.d" -o ${OBJECTDIR}/sapi/sapi.o sapi/sapi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/goal_inst.o: ugoal/goal_inst.c  .generated_files/flags/default/a50274c29fe4e8bed370fc853de39311ab585bef .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/goal_inst.o.d 
	@${RM} ${OBJECTDIR}/ugoal/goal_inst.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/goal_inst.o.d" -o ${OBJECTDIR}/ugoal/goal_inst.o ugoal/goal_inst.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/ugoal.o: ugoal/ugoal.c  .generated_files/flags/default/7c11474d4b7faa01b2796498c769ac9dff275d7 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/ugoal.o.d 
	@${RM} ${OBJECTDIR}/ugoal/ugoal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/ugoal.o.d" -o ${OBJECTDIR}/ugoal/ugoal.o ugoal/ugoal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ugoal/ugoal_buffer.o: ugoal/ugoal_buffer.c  .generated_files/flags/default/3f226d37a87ca52fb25f542c2892dc31aaebf47b .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/ugoal" 
	@${RM} ${OBJECTDIR}/ugoal/ugoal_buffer.o.d 
	@${RM} ${OBJECTDIR}/ugoal/ugoal_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/ugoal/ugoal_buffer.o.d" -o ${OBJECTDIR}/ugoal/ugoal_buffer.o ugoal/ugoal_buffer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/67bf03e2609cafa95a2d612b33b50a018e9a2d0f .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pnet_app.o: pnet_app.c  .generated_files/flags/default/2d361a0963520da5526362f63e1161a346041ad0 .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pnet_app.o.d 
	@${RM} ${OBJECTDIR}/pnet_app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/pnet_app.o.d" -o ${OBJECTDIR}/pnet_app.o pnet_app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/goal_appl.o: goal_appl.c  .generated_files/flags/default/b79df291f337a08ca65f3f3771bbf5b098fa49ad .generated_files/flags/default/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/goal_appl.o.d 
	@${RM} ${OBJECTDIR}/goal_appl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -I"ugoal" -I"sapi" -I"rpc/goal_mctc" -I"rpc/goal_media" -I"rpc/wrapper/pnio" -I"rpc/wrapper/http" -I"rpc/wrapper/ccm" -I"pic32" -I"rpc" -I"rpc/wrapper/net" -I"rpc/wrapper/dd/protos/dd/rpc" -I"rpc/wrapper/dd" -MP -MMD -MF "${OBJECTDIR}/goal_appl.o.d" -o ${OBJECTDIR}/goal_appl.o goal_appl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
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
