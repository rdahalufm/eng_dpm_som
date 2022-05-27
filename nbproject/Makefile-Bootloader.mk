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
ifeq "$(wildcard nbproject/Makefile-local-Bootloader.mk)" "nbproject/Makefile-local-Bootloader.mk"
include nbproject/Makefile-local-Bootloader.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Bootloader
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
SOURCEFILES_QUOTED_IF_SPACED="../UFM Library/DPM/src/dpm_adc.c" "../UFM Library/DPM/src/dpm_bsp.c" "../UFM Library/DPM/src/dpm_cal.c" "../UFM Library/DPM/src/dpm_eeprom.c" "../UFM Library/DPM/src/dpm_flow.c" "../UFM Library/DPM/src/dpm_interrupt.c" "../UFM Library/DPM/src/dpm_lcd.c" "../UFM Library/DPM/src/dpm_menu.c" "../UFM Library/DPM/src/dpm_protocol.c" "../UFM Library/DPM/src/dpm_datalogger.c" "../UFM Library/DPM/src/dpm_config_read.c" "../UFM Library/DPM/usb lib/MDD_File_System/FSIO.c" "../UFM Library/DPM/usb lib/USB/usb_config.c" "../UFM Library/DPM/usb lib/USB/usb_host.c" "../UFM Library/DPM/usb lib/USB/usb_host_msd.c" "../UFM Library/DPM/usb lib/USB/usb_host_msd_scsi.c" sldrv2/ad_obj.c sldrv2/anybus.c sldrv2/app_obj.c sldrv2/etn_obj.c sldrv2/pnet_obj.c main.c pnet_app.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1970182031/dpm_adc.o ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o ${OBJECTDIR}/_ext/1970182031/dpm_cal.o ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o ${OBJECTDIR}/_ext/1970182031/dpm_flow.o ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o ${OBJECTDIR}/_ext/1970182031/dpm_menu.o ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o ${OBJECTDIR}/_ext/1219524773/FSIO.o ${OBJECTDIR}/_ext/421586199/usb_config.o ${OBJECTDIR}/_ext/421586199/usb_host.o ${OBJECTDIR}/_ext/421586199/usb_host_msd.o ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o ${OBJECTDIR}/sldrv2/ad_obj.o ${OBJECTDIR}/sldrv2/anybus.o ${OBJECTDIR}/sldrv2/app_obj.o ${OBJECTDIR}/sldrv2/etn_obj.o ${OBJECTDIR}/sldrv2/pnet_obj.o ${OBJECTDIR}/main.o ${OBJECTDIR}/pnet_app.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d ${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d ${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d ${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d ${OBJECTDIR}/_ext/1219524773/FSIO.o.d ${OBJECTDIR}/_ext/421586199/usb_config.o.d ${OBJECTDIR}/_ext/421586199/usb_host.o.d ${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d ${OBJECTDIR}/sldrv2/ad_obj.o.d ${OBJECTDIR}/sldrv2/anybus.o.d ${OBJECTDIR}/sldrv2/app_obj.o.d ${OBJECTDIR}/sldrv2/etn_obj.o.d ${OBJECTDIR}/sldrv2/pnet_obj.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/pnet_app.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1970182031/dpm_adc.o ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o ${OBJECTDIR}/_ext/1970182031/dpm_cal.o ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o ${OBJECTDIR}/_ext/1970182031/dpm_flow.o ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o ${OBJECTDIR}/_ext/1970182031/dpm_menu.o ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o ${OBJECTDIR}/_ext/1219524773/FSIO.o ${OBJECTDIR}/_ext/421586199/usb_config.o ${OBJECTDIR}/_ext/421586199/usb_host.o ${OBJECTDIR}/_ext/421586199/usb_host_msd.o ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o ${OBJECTDIR}/sldrv2/ad_obj.o ${OBJECTDIR}/sldrv2/anybus.o ${OBJECTDIR}/sldrv2/app_obj.o ${OBJECTDIR}/sldrv2/etn_obj.o ${OBJECTDIR}/sldrv2/pnet_obj.o ${OBJECTDIR}/main.o ${OBJECTDIR}/pnet_app.o

# Source Files
SOURCEFILES=../UFM Library/DPM/src/dpm_adc.c ../UFM Library/DPM/src/dpm_bsp.c ../UFM Library/DPM/src/dpm_cal.c ../UFM Library/DPM/src/dpm_eeprom.c ../UFM Library/DPM/src/dpm_flow.c ../UFM Library/DPM/src/dpm_interrupt.c ../UFM Library/DPM/src/dpm_lcd.c ../UFM Library/DPM/src/dpm_menu.c ../UFM Library/DPM/src/dpm_protocol.c ../UFM Library/DPM/src/dpm_datalogger.c ../UFM Library/DPM/src/dpm_config_read.c ../UFM Library/DPM/usb lib/MDD_File_System/FSIO.c ../UFM Library/DPM/usb lib/USB/usb_config.c ../UFM Library/DPM/usb lib/USB/usb_host.c ../UFM Library/DPM/usb lib/USB/usb_host_msd.c ../UFM Library/DPM/usb lib/USB/usb_host_msd_scsi.c sldrv2/ad_obj.c sldrv2/anybus.c sldrv2/app_obj.c sldrv2/etn_obj.c sldrv2/pnet_obj.c main.c pnet_app.c



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
	${MAKE}  -f nbproject/Makefile-Bootloader.mk dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX440F512H
MP_LINKER_FILE_OPTION=,--script="..\UFM Library\DPM\bootloader\app_32MX440F256H-bootloader.ld"
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
${OBJECTDIR}/_ext/1970182031/dpm_adc.o: ../UFM\ Library/DPM/src/dpm_adc.c  .generated_files/flags/Bootloader/1390f627b06b29205d4e3fb40a5a3b7507388708 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_adc.o "../UFM Library/DPM/src/dpm_adc.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_bsp.o: ../UFM\ Library/DPM/src/dpm_bsp.c  .generated_files/flags/Bootloader/4d519cb93aa65d37b7c840dfb43296d5141a9133 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o "../UFM Library/DPM/src/dpm_bsp.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_cal.o: ../UFM\ Library/DPM/src/dpm_cal.c  .generated_files/flags/Bootloader/74fe6d98f92a2f7096be99b4b5ea52092b14860e .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_cal.o "../UFM Library/DPM/src/dpm_cal.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o: ../UFM\ Library/DPM/src/dpm_eeprom.c  .generated_files/flags/Bootloader/24fa3d511f6d14074b0ecf2da7f7c95959a82156 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o "../UFM Library/DPM/src/dpm_eeprom.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_flow.o: ../UFM\ Library/DPM/src/dpm_flow.c  .generated_files/flags/Bootloader/8579b63bc31a4e6b8fd26a0d19313a891d47e79e .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_flow.o "../UFM Library/DPM/src/dpm_flow.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o: ../UFM\ Library/DPM/src/dpm_interrupt.c  .generated_files/flags/Bootloader/e433ed51d665a4608695d9cb82899ad36e8dc27a .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o "../UFM Library/DPM/src/dpm_interrupt.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_lcd.o: ../UFM\ Library/DPM/src/dpm_lcd.c  .generated_files/flags/Bootloader/1f862910f5bbb4faac9c5801f0224e14c826ba86 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o "../UFM Library/DPM/src/dpm_lcd.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_menu.o: ../UFM\ Library/DPM/src/dpm_menu.c  .generated_files/flags/Bootloader/2f1d4da5b431de69c59e31eb5e91f627d919b0ad .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_menu.o "../UFM Library/DPM/src/dpm_menu.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_protocol.o: ../UFM\ Library/DPM/src/dpm_protocol.c  .generated_files/flags/Bootloader/faa73df3b3acac554763612ab4d53ea5a873c7ce .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o "../UFM Library/DPM/src/dpm_protocol.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o: ../UFM\ Library/DPM/src/dpm_datalogger.c  .generated_files/flags/Bootloader/718ded1ec0f8ef634cec1fab4ef061d625f9f3fa .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o "../UFM Library/DPM/src/dpm_datalogger.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_config_read.o: ../UFM\ Library/DPM/src/dpm_config_read.c  .generated_files/flags/Bootloader/9927d908a296e72607456267db21392c5e785173 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o "../UFM Library/DPM/src/dpm_config_read.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1219524773/FSIO.o: ../UFM\ Library/DPM/usb\ lib/MDD_File_System/FSIO.c  .generated_files/flags/Bootloader/8b4f667a8456c06bd8286aa88fb2acaf795bc70d .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1219524773" 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1219524773/FSIO.o.d" -o ${OBJECTDIR}/_ext/1219524773/FSIO.o "../UFM Library/DPM/usb lib/MDD_File_System/FSIO.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_config.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_config.c  .generated_files/flags/Bootloader/44912c4c2018011e80b7f708116017a5a692c467 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_config.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_config.o "../UFM Library/DPM/usb lib/USB/usb_config.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host.c  .generated_files/flags/Bootloader/8e85cb1b60907641598f56ce99338ec4b1009f11 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host.o "../UFM Library/DPM/usb lib/USB/usb_host.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd.c  .generated_files/flags/Bootloader/9b5158fd28ac3a714368ed9fa4d7162bc3f73486 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd.o "../UFM Library/DPM/usb lib/USB/usb_host_msd.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd_scsi.c  .generated_files/flags/Bootloader/7f8c1ee0824ca85857ee50b547775e7c89be5e78 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o "../UFM Library/DPM/usb lib/USB/usb_host_msd_scsi.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sldrv2/ad_obj.o: sldrv2/ad_obj.c  .generated_files/flags/Bootloader/6a89b0b6c7f86fbe3050db843b03da04a549ba44 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sldrv2" 
	@${RM} ${OBJECTDIR}/sldrv2/ad_obj.o.d 
	@${RM} ${OBJECTDIR}/sldrv2/ad_obj.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/sldrv2/ad_obj.o.d" -o ${OBJECTDIR}/sldrv2/ad_obj.o sldrv2/ad_obj.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sldrv2/anybus.o: sldrv2/anybus.c  .generated_files/flags/Bootloader/6fe5d66276d4d815de7f3d380d9059dbec711bf7 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sldrv2" 
	@${RM} ${OBJECTDIR}/sldrv2/anybus.o.d 
	@${RM} ${OBJECTDIR}/sldrv2/anybus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/sldrv2/anybus.o.d" -o ${OBJECTDIR}/sldrv2/anybus.o sldrv2/anybus.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sldrv2/app_obj.o: sldrv2/app_obj.c  .generated_files/flags/Bootloader/c6e3a3dc8a1cbc872e54b235999b4aca7bdcc2c8 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sldrv2" 
	@${RM} ${OBJECTDIR}/sldrv2/app_obj.o.d 
	@${RM} ${OBJECTDIR}/sldrv2/app_obj.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/sldrv2/app_obj.o.d" -o ${OBJECTDIR}/sldrv2/app_obj.o sldrv2/app_obj.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sldrv2/etn_obj.o: sldrv2/etn_obj.c  .generated_files/flags/Bootloader/e904ff0d062f58ef438b74cfd202dd48b24997ca .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sldrv2" 
	@${RM} ${OBJECTDIR}/sldrv2/etn_obj.o.d 
	@${RM} ${OBJECTDIR}/sldrv2/etn_obj.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/sldrv2/etn_obj.o.d" -o ${OBJECTDIR}/sldrv2/etn_obj.o sldrv2/etn_obj.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sldrv2/pnet_obj.o: sldrv2/pnet_obj.c  .generated_files/flags/Bootloader/fafd3f9f7135231b7308a7477a15ca5104e25f7f .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sldrv2" 
	@${RM} ${OBJECTDIR}/sldrv2/pnet_obj.o.d 
	@${RM} ${OBJECTDIR}/sldrv2/pnet_obj.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/sldrv2/pnet_obj.o.d" -o ${OBJECTDIR}/sldrv2/pnet_obj.o sldrv2/pnet_obj.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/Bootloader/b95ff5aac264b58473b701781649372f34c70680 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pnet_app.o: pnet_app.c  .generated_files/flags/Bootloader/dbcaf675572542998ac01262f77738e93168ac3a .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pnet_app.o.d 
	@${RM} ${OBJECTDIR}/pnet_app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/pnet_app.o.d" -o ${OBJECTDIR}/pnet_app.o pnet_app.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/_ext/1970182031/dpm_adc.o: ../UFM\ Library/DPM/src/dpm_adc.c  .generated_files/flags/Bootloader/83031ee945fc7895a70f811dda865243a092a486 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_adc.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_adc.o "../UFM Library/DPM/src/dpm_adc.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_bsp.o: ../UFM\ Library/DPM/src/dpm_bsp.c  .generated_files/flags/Bootloader/aa401ff99359e5ae87c961b3c09aa8e94771e647 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_bsp.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_bsp.o "../UFM Library/DPM/src/dpm_bsp.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_cal.o: ../UFM\ Library/DPM/src/dpm_cal.c  .generated_files/flags/Bootloader/b44a05a0a47a61a5fbe58b166e71cc90ff5d742b .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_cal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_cal.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_cal.o "../UFM Library/DPM/src/dpm_cal.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o: ../UFM\ Library/DPM/src/dpm_eeprom.c  .generated_files/flags/Bootloader/62071261aa6d8828a356a14d510d172b2f0e89dc .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_eeprom.o "../UFM Library/DPM/src/dpm_eeprom.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_flow.o: ../UFM\ Library/DPM/src/dpm_flow.c  .generated_files/flags/Bootloader/474f5e022eac3112aad804ca2c6b7d21ea50c6b2 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_flow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_flow.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_flow.o "../UFM Library/DPM/src/dpm_flow.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o: ../UFM\ Library/DPM/src/dpm_interrupt.c  .generated_files/flags/Bootloader/bc5a1efe00cf54fa5f4d4d0295729b2dd48846e .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_interrupt.o "../UFM Library/DPM/src/dpm_interrupt.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_lcd.o: ../UFM\ Library/DPM/src/dpm_lcd.c  .generated_files/flags/Bootloader/a8d812b09a85e4c3e9a6845c1df65ea6638c9f7c .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_lcd.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_lcd.o "../UFM Library/DPM/src/dpm_lcd.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_menu.o: ../UFM\ Library/DPM/src/dpm_menu.c  .generated_files/flags/Bootloader/1765a34b0548d6f113dbee46e9b1d0ac1d50d7eb .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_menu.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_menu.o "../UFM Library/DPM/src/dpm_menu.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_protocol.o: ../UFM\ Library/DPM/src/dpm_protocol.c  .generated_files/flags/Bootloader/a111d2d790c931de648a1980215690c3d9078d0e .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_protocol.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_protocol.o "../UFM Library/DPM/src/dpm_protocol.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o: ../UFM\ Library/DPM/src/dpm_datalogger.c  .generated_files/flags/Bootloader/ba645ce1f58651bad03f045561133bd92f4eb867 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_datalogger.o "../UFM Library/DPM/src/dpm_datalogger.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1970182031/dpm_config_read.o: ../UFM\ Library/DPM/src/dpm_config_read.c  .generated_files/flags/Bootloader/a8ede039e1efc69b38348425ea5f3cdbb7e2a3b5 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1970182031" 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d 
	@${RM} ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1970182031/dpm_config_read.o.d" -o ${OBJECTDIR}/_ext/1970182031/dpm_config_read.o "../UFM Library/DPM/src/dpm_config_read.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1219524773/FSIO.o: ../UFM\ Library/DPM/usb\ lib/MDD_File_System/FSIO.c  .generated_files/flags/Bootloader/72bb00cdb99847d93779eae69db0a81dcad83d9 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/1219524773" 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1219524773/FSIO.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/1219524773/FSIO.o.d" -o ${OBJECTDIR}/_ext/1219524773/FSIO.o "../UFM Library/DPM/usb lib/MDD_File_System/FSIO.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_config.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_config.c  .generated_files/flags/Bootloader/e32fa2c3f5649318ec6c71bcce1405d943afa82f .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_config.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_config.o "../UFM Library/DPM/usb lib/USB/usb_config.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host.c  .generated_files/flags/Bootloader/c00eda7a3c72f0779f5c3d728161868d7b019d10 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host.o "../UFM Library/DPM/usb lib/USB/usb_host.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd.c  .generated_files/flags/Bootloader/ecd02a3d666c00a2e97615739f006a3a9f75d7f1 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd.o "../UFM Library/DPM/usb lib/USB/usb_host_msd.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o: ../UFM\ Library/DPM/usb\ lib/USB/usb_host_msd_scsi.c  .generated_files/flags/Bootloader/38484e5e8fbf81215306b8e36ebe555adfe47f1 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/_ext/421586199" 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/421586199/usb_host_msd_scsi.o "../UFM Library/DPM/usb lib/USB/usb_host_msd_scsi.c"    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sldrv2/ad_obj.o: sldrv2/ad_obj.c  .generated_files/flags/Bootloader/dcf8a8f5306717ddee4156de95985add3a6ed5 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sldrv2" 
	@${RM} ${OBJECTDIR}/sldrv2/ad_obj.o.d 
	@${RM} ${OBJECTDIR}/sldrv2/ad_obj.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/sldrv2/ad_obj.o.d" -o ${OBJECTDIR}/sldrv2/ad_obj.o sldrv2/ad_obj.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sldrv2/anybus.o: sldrv2/anybus.c  .generated_files/flags/Bootloader/d84068852c7db8f069ea825373f7608bae215450 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sldrv2" 
	@${RM} ${OBJECTDIR}/sldrv2/anybus.o.d 
	@${RM} ${OBJECTDIR}/sldrv2/anybus.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/sldrv2/anybus.o.d" -o ${OBJECTDIR}/sldrv2/anybus.o sldrv2/anybus.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sldrv2/app_obj.o: sldrv2/app_obj.c  .generated_files/flags/Bootloader/e6f4aa3760df8b7d46d5515e5e1adfa8c4ada5d .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sldrv2" 
	@${RM} ${OBJECTDIR}/sldrv2/app_obj.o.d 
	@${RM} ${OBJECTDIR}/sldrv2/app_obj.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/sldrv2/app_obj.o.d" -o ${OBJECTDIR}/sldrv2/app_obj.o sldrv2/app_obj.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sldrv2/etn_obj.o: sldrv2/etn_obj.c  .generated_files/flags/Bootloader/ec745238ac192d3ce49fd99b4b9f606a560a70d4 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sldrv2" 
	@${RM} ${OBJECTDIR}/sldrv2/etn_obj.o.d 
	@${RM} ${OBJECTDIR}/sldrv2/etn_obj.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/sldrv2/etn_obj.o.d" -o ${OBJECTDIR}/sldrv2/etn_obj.o sldrv2/etn_obj.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/sldrv2/pnet_obj.o: sldrv2/pnet_obj.c  .generated_files/flags/Bootloader/a39b234e6b3ec86ff76e8ce109b6f7438ac0db75 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}/sldrv2" 
	@${RM} ${OBJECTDIR}/sldrv2/pnet_obj.o.d 
	@${RM} ${OBJECTDIR}/sldrv2/pnet_obj.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/sldrv2/pnet_obj.o.d" -o ${OBJECTDIR}/sldrv2/pnet_obj.o sldrv2/pnet_obj.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/Bootloader/6b05d9fd86db050881fae596c9b4a6fce48b26b2 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pnet_app.o: pnet_app.c  .generated_files/flags/Bootloader/3fe816cdfef9a578852c114a8a55f398c724e249 .generated_files/flags/Bootloader/41a1366f5dc91e8d46feccce4badeda48f9c0218
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pnet_app.o.d 
	@${RM} ${OBJECTDIR}/pnet_app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -DCPM3F4T1_0 -DTRANSPORT_LAYER_USB_HOST -DBOOTLOADER_MODE -I"." -I"C:/Program Files (x86)/Microchip/xc32/v1.33/pic32mx/include" -I"../UFM Library/DPM/includes" -I"sldrv2" -I"../UFM Library/DPM/usb lib/Include" -I"../UFM Library/DPM/usb lib/Include/HardwareProfile" -I"../UFM Library/DPM/usb lib/Include/USB" -I"../UFM Library/DPM/usb lib/Include/MDD File System" -MP -MMD -MF "${OBJECTDIR}/pnet_app.o.d" -o ${OBJECTDIR}/pnet_app.o pnet_app.c    -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../UFM\ Library/DPM/bootloader/app_32MX440F256H-bootloader.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=_min_heap_size=2000,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../UFM\ Library/DPM/bootloader/app_32MX440F256H-bootloader.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Bootloader=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2000,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map" 
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/DPM_FP14.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Bootloader
	${RM} -r dist/Bootloader

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
