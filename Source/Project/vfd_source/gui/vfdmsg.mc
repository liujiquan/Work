;/*
;   vfdmsg.h
;
;   Virtual Floppy Drive for Windows
;   GUI Control Panel
;   Message definition
;
;   Copyright (c) 2003-2008 Ken Kato
;*/
;
;#ifndef _VFDMSG_H_
;#define _VFDMSG_H_
;

MessageIdTypedef=DWORD
LanguageNames=(English=0x409:msg0409)

;//====================================
;//	Message text for main dialog
;//====================================
;//
;//	VFDWIN window title
;//
MessageId=
SymbolicName=MSG_APPLICATION_TITLE_EN
Language=English
VFD 2.1 [English & Simplified]%1!s!%0
.

MessageId=
SymbolicName=MSG_APPLICATION_TITLE_IT
Language=English
VFD 2.1 [Italiano & Semplificato]%1!s!%0
.

MessageId=
SymbolicName=MSG_APPLICATION_TITLE_SP
Language=English
VFD 2.1 [Español & simplificado]%1!s!%0
.

;//
;//	Drive 0 tab title
;//
MessageId=
SymbolicName=MSG_DRIVE0_TITLE_EN
Language=English
Virtual Drive%0
.

MessageId=
SymbolicName=MSG_DRIVE0_TITLE_IT
Language=English
Unità Virtuale%0
.

MessageId=
SymbolicName=MSG_DRIVE0_TITLE_SP
Language=English
Unidad Virtual%0
.

;//
;//	Drive 1 tab title
;//
MessageId=
SymbolicName=MSG_DRIVE1_TITLE
Language=English
Drive1%0
.

;//
;//	Driver tab title
;//
MessageId=
SymbolicName=MSG_DRIVER_TITLE_EN
Language=English
Configuration%0
.

MessageId=
SymbolicName=MSG_DRIVER_TITLE_IT
Language=English
Configurazione%0
.

MessageId=
SymbolicName=MSG_DRIVER_TITLE_SP
Language=English
Configuración%0
.

;//
;//	Shell tab title
;//
MessageId=
SymbolicName=MSG_SHELL_TITLE
Language=English
Shell%0
.

;//
;//	Association tab title
;//
MessageId=
SymbolicName=MSG_ASSOC_TITLE
Language=English
Association%0
.

;//
;//	About tab title
;//
MessageId=
SymbolicName=MSG_ABOUT_TITLE
Language=English
About%0
.

;//
;//	Driver status on status area
;//
MessageId=
SymbolicName=MSG_STAT_DRIVER_STOPPED_EN
Language=English
The VFD driver is stopped.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_STOPPED_IT
Language=English
Driver VFD: arrestato.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_STOPPED_SP
Language=English
Driver VFD: suspendido.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_START_PENDING_EN
Language=English
The VFD driver is start pending.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_START_PENDING_IT
Language=English
Driver VFD: avviamento in corso.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_START_PENDING_SP
Language=English
Driver VFD: puesta en marcha.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_STOP_PENDING_EN
Language=English
The VFD driver is stop pending.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_STOP_PENDING_IT
Language=English
Driver VFD: arresto in corso.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_STOP_PENDING_SP
Language=English
Driver VFD: parada en curso.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_RUNNING_EN
Language=English
The VFD driver %1!u!.%2!u!%3!s! is running.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_RUNNING_IT
Language=English
Driver VFD %1!u!.%2!u!%3!s!: avviato.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_RUNNING_SP
Language=English
Driver VFD %1!u!.%2!u!%3!s!: activado.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_CONTINUE_PENDING_EN
Language=English
The VFD driver is continue pending.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_CONTINUE_PENDING_IT
Language=English
Driver VFD: avviamento ancora in corso.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_CONTINUE_PENDING_SP
Language=English
Driver VFD: puesta en marcha todavìa en curso.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_PAUSE_PENDING_EN
Language=English
The VFD driver is pause pending.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_PAUSE_PENDING_IT
Language=English
Driver VFD: sospensione in corso.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_PAUSE_PENDING_SP
Language=English
Driver VFD: suspensiòn todavìa en curso.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_PAUSED_EN
Language=English
The VFD driver is paused.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_PAUSED_IT
Language=English
Driver VFD: sospeso.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_PAUSED_SP
Language=English
Driver VFD: suspendido.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_NOT_INSTALLED_EN
Language=English
The VFD driver is not installed.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_NOT_INSTALLED_IT
Language=English
Driver VFD: non installato.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_NOT_INSTALLED_SP
Language=English
Driver VFD  no instalado.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_UNKNOWN_STATE_EN
Language=English
Cannot get the VFD driver state.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_UNKNOWN_STATE_IT
Language=English
Driver VFD: impossibile accedere allo stato.%0
.

MessageId=
SymbolicName=MSG_STAT_DRIVER_UNKNOWN_STATE_SP
Language=English
Driver VFD: no se puede acceder al estado.%0
.

;//
;//	Log message text
;//
MessageId=
SymbolicName=MSG_LOG_DRIVER_INSTALLED_EN
Language=English
The VFD driver is installed.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_INSTALLED_IT
Language=English
Driver VFD installato.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_INSTALLED_SP
Language=English
Driver VFD instalado.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_CONFIGURED_EN
Language=English
The VFD driver configuration is changed.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_CONFIGURED_IT
Language=English
Cambio configurazione del driver VFD.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_CONFIGURED_SP
Language=English
Cambiar la configuración del driver VFD.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_REMOVED_EN
Language=English
The VFD driver is uninstalled.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_REMOVED_IT
Language=English
Driver VFD disinstallato.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_REMOVED_SP
Language=English
Driver VFD desinstalado.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_REMOVE_PENDING_EN
Language=English
The VFD driver is uninstall pending.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_REMOVE_PENDING_IT
Language=English
Driver VFD in corso di disinstallazione.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_REMOVE_PENDING_SP
Language=English
Driver VFD se está desinstalando.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STARTED_EN
Language=English
The VFD driver is started.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STARTED_IT
Language=English
Driver VFD avviato.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STARTED_SP
Language=English
Driver VFD puesta en marcha.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_START_PENDING_EN
Language=English
The VFD driver is start pending.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_START_PENDING_IT
Language=English
Driver VFD in corso di avviamento.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_START_PENDING_SP
Language=English
Driver VFD en curso de arranque.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STOPPED_EN
Language=English
The VFD driver is stopped.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STOPPED_IT
Language=English
Driver VFD arrestato.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STOPPED_SP
Language=English
Driver VFD arrestado.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STOP_PENDING_EN
Language=English
The VFD driver is stop pending.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STOP_PENDING_IT
Language=English
Driver VFD in corso d'arresto.
.

MessageId=
SymbolicName=MSG_LOG_DRIVER_STOP_PENDING_SP
Language=English
Driver VFD parada en curso.
.

MessageId=
SymbolicName=MSG_LOG_IMAGE_OPENED_EN
Language=English
Drive %1!lu!: A virtual floppy image is opened.
.

MessageId=
SymbolicName=MSG_LOG_IMAGE_OPENED_IT
Language=English
Unità virtuale %1!lu!: apertura di un file d'immagine.
.

MessageId=
SymbolicName=MSG_LOG_IMAGE_OPENED_SP
Language=English
Unidad virtual %1!lu!: abrir un archivo de imagen.
.

MessageId=
SymbolicName=MSG_LOG_IMAGE_CLOSED_EN
Language=English
Drive %1!lu!: A virtual floppy image is closed.
.

MessageId=
SymbolicName=MSG_LOG_IMAGE_CLOSED_IT
Language=English
Unità virtuale %1!lu!: chiusura di un file d'immagine.
.

MessageId=
SymbolicName=MSG_LOG_IMAGE_CLOSED_SP
Language=English
Unidad virtual %1!lu!: cerrar de un archivo de imagen.
.

MessageId=
SymbolicName=MSG_LOG_LETTER_ASSIGNED_EN
Language=English
Drive %1!lu!: A drive letter is assigned.
.

MessageId=
SymbolicName=MSG_LOG_LETTER_ASSIGNED_IT
Language=English
Unità virtuale %1!lu!: lettera assegnata.
.

MessageId=
SymbolicName=MSG_LOG_LETTER_ASSIGNED_SP
Language=English
Unidad virtual %1!lu!: letra seleccionada.
.

MessageId=
SymbolicName=MSG_LOG_LETTER_REMOVED_EN
Language=English
Drive %1!lu!: A drive letter is removed.
.

MessageId=
SymbolicName=MSG_LOG_LETTER_REMOVED_IT
Language=English
Unità virtuale %1!lu!: lettera rimossa.
.

MessageId=
SymbolicName=MSG_LOG_LETTER_REMOVED_SP
Language=English
Unidad virtual %1!lu!: letra eliminada.
.

MessageId=
SymbolicName=MSG_LOG_PROTECT_ENABLED_EN
Language=English
Drive %1!lu!: Write protected.
.

MessageId=
SymbolicName=MSG_LOG_PROTECT_ENABLED_IT
Language=English
Unità virtuale %1!lu!: protezione in scrittura.
.

MessageId=
SymbolicName=MSG_LOG_PROTECT_ENABLED_SP
Language=English
Unidad virtual %1!lu!: protección en la escritura.
.

MessageId=
SymbolicName=MSG_LOG_PROTECT_DISABLED_EN
Language=English
Drive %1!lu!: Write unprotected.
.

MessageId=
SymbolicName=MSG_LOG_PROTECT_DISABLED_IT
Language=English
Unità virtuale %1!lu!: abilitazione scrittura.
.

MessageId=
SymbolicName=MSG_LOG_PROTECT_DISABLED_SP
Language=English
Unidad virtual %1!lu!: habilitacion en la escritura.
.

MessageId=
SymbolicName=MSG_ERR_CHANGE_PROTECT_EN
Language=English
Failed to change the write protect state.
.

MessageId=
SymbolicName=MSG_ERR_CHANGE_PROTECT_IT
Language=English
Impossibile cambiare lo stato di protezione scrittura.
.

MessageId=
SymbolicName=MSG_ERR_CHANGE_PROTECT_SP
Language=English
No se puede cambiar el estado de protección de la escritura.
.

MessageId=
SymbolicName=MSG_ERR_FILE_CREATE_EN
Language=English
Failed to open file '%1!s!'.
.

MessageId=
SymbolicName=MSG_ERR_FILE_CREATE_IT
Language=English
Impossibile aprire il file '%1!s!'.
.

MessageId=
SymbolicName=MSG_ERR_FILE_CREATE_SP
Language=English
No se puede abrir el archivo '%1!s!'.
.

MessageId=
SymbolicName=MSG_ERR_FILE_OPEN_EN
Language=English
Failed to open file '%1!s!'.
.

MessageId=
SymbolicName=MSG_ERR_FILE_OPEN_IT
Language=English
Impossibile aprire il file '%1!s!'.
.

MessageId=
SymbolicName=MSG_ERR_FILE_OPEN_SP
Language=English
No se puede abrir el archivo '%1!s!'.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_OPEN_EN
Language=English
Failed to open an image.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_OPEN_IT
Language=English
Impossibile aprire l'immagine.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_OPEN_SP
Language=English
No se puede abrir la imagen.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_TOO_SMALL_EN
Language=English
The image is too small.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_TOO_SMALL_IT
Language=English
L'immagine e' troppo piccola.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_TOO_SMALL_SP
Language=English
La imagen de demasiado pequeña.
.

MessageId=
SymbolicName=MSG_ERR_DEVICE_OPEN_EN
Language=English
Failed to open Drive %1!c!.
.

MessageId=
SymbolicName=MSG_ERR_DEVICE_OPEN_IT
Language=English
Impossibile aprire il drive %1!c!.
.

MessageId=
SymbolicName=MSG_ERR_DEVICE_OPEN_SP
Language=English
No se puede abrir la unidad %1!c!.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_SAVE_EN
Language=English
Failed to save the image.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_SAVE_IT
Language=English
Impossibile salvare l'immagine.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_SAVE_SP
Language=English
No es posible guardar la imagen.
.

MessageId=
SymbolicName=MSG_IMAGE_SAVED_EN
Language=English
Saved the current image.
.

MessageId=
SymbolicName=MSG_IMAGE_SAVED_IT
Language=English
Salvataggio dell'immagine riuscito.
.

MessageId=
SymbolicName=MSG_IMAGE_SAVED_SP
Language=English
Salvamiento de la imagen salido.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_CLOSE_EN
Language=English
Failed to close the image on drive %1!c!.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_CLOSE_IT
Language=English
Impossibile chiudere l'immagine nel drive %1!c!.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_CLOSE_SP
Language=English
No se puede cerrar la imagen en la unidad %1!c!.
.

MessageId=
SymbolicName=MSG_ERR_IMAGE_FORMAT
Language=English
Failed to format the image.
.

MessageId=
SymbolicName=MSG_IMAGE_FORMATTED
Language=English
Formatted the current image.
.

;//====================================
;//	Generic text for controls
;//====================================

MessageId=
SymbolicName=MSG_GENERIC_NONE
Language=English
(none)%0
.

MessageId=
SymbolicName=MSG_OK_BUTTON
Language=English
OK%0
.

MessageId=
SymbolicName=MSG_CANCEL_BUTTON_EN
Language=English
Cancel%0
.

MessageId=
SymbolicName=MSG_CANCEL_BUTTON_IT
Language=English
Annulla%0
.

MessageId=
SymbolicName=MSG_CANCEL_BUTTON_SP
Language=English
Anular%0
.

MessageId=
SymbolicName=MSG_APPLY_BUTTON
Language=English
&Apply%0
.

;//====================================
;//	Message text for image dialogs
;//====================================

MessageId=
SymbolicName=MSG_LETTER_LABEL_EN
Language=English
Drive Letter: %0
.

MessageId=
SymbolicName=MSG_LETTER_LABEL_IT
Language=English
Unità: %0
.

MessageId=
SymbolicName=MSG_LETTER_LABEL_SP
Language=English
Unidad: %0
.

MessageId=
SymbolicName=MSG_PERSISTENT_EN
Language=English
Global%0
.

MessageId=
SymbolicName=MSG_PERSISTENT_IT
Language=English
Globale%0
.

MessageId=
SymbolicName=MSG_PERSISTENT_SP
Language=English
Gobal%0
.

MessageId=
SymbolicName=MSG_EPHEMERAL_EN
Language=English
Local%0
.

MessageId=
SymbolicName=MSG_EPHEMERAL_IT
Language=English
Locale%0
.

MessageId=
SymbolicName=MSG_EPHEMERAL_SP
Language=English
Local%0
.

MessageId=
SymbolicName=MSG_CHANGE_BUTTON_EN
Language=English
Change%0
.

MessageId=
SymbolicName=MSG_CHANGE_BUTTON_IT
Language=English
Imposta%0
.

MessageId=
SymbolicName=MSG_CHANGE_BUTTON_SP
Language=English
Configuración%0
.

MessageId=
SymbolicName=MSG_IMAGEFILE_LABEL_EN
Language=English
Image File:%0
.

MessageId=
SymbolicName=MSG_IMAGEFILE_LABEL_IT
Language=English
Immagine:%0
.

MessageId=
SymbolicName=MSG_IMAGEFILE_LABEL_SP
Language=English
Imagen:%0
.

MessageId=
SymbolicName=MSG_DESCRIPTION_LABEL_EN
Language=English
Description:%0
.

MessageId=
SymbolicName=MSG_DESCRIPTION_LABEL_IT
Language=English
Descrizione:%0
.

MessageId=
SymbolicName=MSG_DESCRIPTION_LABEL_SP
Language=English
Descripción:%0
.

MessageId=
SymbolicName=MSG_DESC_FILESIZE
Language=English
%1!s! bytes (%2!s!)%0
.

MessageId=
SymbolicName=MSG_DESC_FILE_RAW_EN
Language=English
RAW image%0
.

MessageId=
SymbolicName=MSG_DESC_FILE_RAW_IT
Language=English
Immagine RAW%0
.

MessageId=
SymbolicName=MSG_DESC_FILE_RAW_SP
Language=English
Imagen RAW%0
.

MessageId=
SymbolicName=MSG_DESC_FILE_ZIP
Language=English
ZIP image%0
.

MessageId=
SymbolicName=MSG_ATTR_READONLY
Language=English
ReadOnly%0
.

MessageId=
SymbolicName=MSG_ATTR_COMPRESSED
Language=English
Compressed%0
.

MessageId=
SymbolicName=MSG_ATTR_ENCRYPTED
Language=English
Encrypted%0
.

MessageId=
SymbolicName=MSG_DISKTYPE_LABEL
Language=English
Disk Type:%0
.

MessageId=
SymbolicName=MSG_MEDIATYPE_LABEL_EN
Language=English
Media Type:%0
.

MessageId=
SymbolicName=MSG_MEDIATYPE_LABEL_IT
Language=English
Tipo:%0
.

MessageId=
SymbolicName=MSG_MEDIATYPE_LABEL_SP
Language=English
Tipo:%0
.

MessageId=
SymbolicName=MSG_PROTECT_BUTTON
Language=English
&Write Protect%0
.

MessageId=
SymbolicName=MSG_OPEN_BUTTON_EN
Language=English
&Open/Create%0
.

MessageId=
SymbolicName=MSG_OPEN_BUTTON_IT
Language=English
&Apri/Crea%0
.

MessageId=
SymbolicName=MSG_OPEN_BUTTON_SP
Language=English
&Abrir/Crear%0
.

MessageId=
SymbolicName=MSG_SAVE_BUTTON_EN
Language=English
&Save%0
.

MessageId=
SymbolicName=MSG_SAVE_BUTTON_IT
Language=English
&Salva%0
.

MessageId=
SymbolicName=MSG_SAVE_BUTTON_SP
Language=English
&Guardar%0
.

MessageId=
SymbolicName=MSG_CLOSE_BUTTON_EN
Language=English
&Close%0
.

MessageId=
SymbolicName=MSG_CLOSE_BUTTON_IT
Language=English
&Chiudi%0
.

MessageId=
SymbolicName=MSG_CLOSE_BUTTON_SP
Language=English
&Cerrar%0
.

MessageId=
SymbolicName=MSG_FORMAT_BUTTON
Language=English
&Format%0
.

;//====================================
;//	Drive letter dialog title
;//====================================

MessageId=
SymbolicName=MSG_LETTER_TITLE_EN
Language=English
Drive Letter%0
.

MessageId=
SymbolicName=MSG_LETTER_TITLE_IT
Language=English
Imposta Unità%0
.

MessageId=
SymbolicName=MSG_LETTER_TITLE_SP
Language=English
Configuración de Unidades%0
.

;//====================================
;//	Message text for driver dialog
;//====================================

MessageId=
SymbolicName=MSG_DRIVER_LABEL
Language=English
&VFD Driver:%0
.

MessageId=
SymbolicName=MSG_BROWSE_BUTTON_EN
Language=English
&Browse%0
.

MessageId=
SymbolicName=MSG_BROWSE_BUTTON_IT
Language=English
&Imposta%0
.

MessageId=
SymbolicName=MSG_BROWSE_BUTTON_SP
Language=English
&Cambiar%0
.

MessageId=
SymbolicName=MSG_VERSION_LABEL_EN
Language=English
Version:%0
.

MessageId=
SymbolicName=MSG_VERSION_LABEL_IT
Language=English
Versione:%0
.

MessageId=
SymbolicName=MSG_VERSION_LABEL_SP
Language=English
Versión:%0
.

MessageId=
SymbolicName=MSG_START_LABEL
Language=English
Start Type:%0
.

MessageId=
SymbolicName=MSG_START_MANUAL
Language=English
&Manual%0
.

MessageId=
SymbolicName=MSG_START_AUTO
Language=English
&Auto%0
.

MessageId=
SymbolicName=MSG_INSTALL_BUTTON_EN
Language=English
&Install%0
.

MessageId=
SymbolicName=MSG_INSTALL_BUTTON_IT
Language=English
&Installa%0
.

MessageId=
SymbolicName=MSG_INSTALL_BUTTON_SP
Language=English
&Instale%0
.

MessageId=
SymbolicName=MSG_START_BUTTON_EN
Language=English
&Start%0
.

MessageId=
SymbolicName=MSG_START_BUTTON_IT
Language=English
&Avvia%0
.

MessageId=
SymbolicName=MSG_START_BUTTON_SP
Language=English
&Comenzar%0
.

MessageId=
SymbolicName=MSG_STOP_BUTTON_EN
Language=English
&Stop%0
.

MessageId=
SymbolicName=MSG_STOP_BUTTON_IT
Language=English
&Arresta%0
.

MessageId=
SymbolicName=MSG_STOP_BUTTON_SP
Language=English
&Parada%0
.

MessageId=
SymbolicName=MSG_REMOVE_BUTTON_EN
Language=English
&Uninstall%0
.

MessageId=
SymbolicName=MSG_REMOVE_BUTTON_IT
Language=English
&Disinstalla%0
.

MessageId=
SymbolicName=MSG_REMOVE_BUTTON_SP
Language=English
&Desinstalar%0
.

MessageId=
SymbolicName=MSG_DRIVER_OPEN_TITLE_EN
Language=English
VFD Driver%0
.

MessageId=
SymbolicName=MSG_DRIVER_OPEN_TITLE_IT
Language=English
Driver VFD%0
.

MessageId=
SymbolicName=MSG_DRIVER_OPEN_TITLE_SP
Language=English
Driver VFD%0
.

MessageId=
SymbolicName=MSG_DRIVER_OPEN_FILTER
Language=English
VFD Driver (vfd.sys)|vfd.sys|%0
.

MessageId=
SymbolicName=MSG_ERR_DRIVER_INSTALL
Language=English
Failed to install the VFD driver.
.

MessageId=
SymbolicName=MSG_ERR_DRIVER_REMOVE
Language=English
Failed to uninstall the VFD driver.
.

MessageId=
SymbolicName=MSG_ERR_DRIVER_START
Language=English
Failed to start the VFD driver.
.

MessageId=
SymbolicName=MSG_ERR_DRIVER_STOP
Language=English
Failed to stop the VFD driver.
.

MessageId=
SymbolicName=MSG_ERR_DRIVER_CONFIG
Language=English
Failed to configure the VFD driver.
.

MessageId=
SymbolicName=MSG_CONFIRM_REMOVE
Language=English
Failed to stop the driver.
It may not unload properly.
Proceed?%0
.

;//====================================
;//	Message text for shell dialog
;//====================================

;//	text for tree view items
MessageId=
SymbolicName=MSG_TREE_SHELLEXT
Language=English
Shell Extensions%0
.

MessageId=
SymbolicName=MSG_TREE_CONFIG
Language=English
Shortcut to the VFD Control Panel%0
.

MessageId=
SymbolicName=MSG_TREE_DRIVE0
Language=English
Shortcut to the VFD drive 0%0
.

MessageId=
SymbolicName=MSG_TREE_DRIVE1
Language=English
Shortcut to the VFD drive 1%0
.

MessageId=
SymbolicName=MSG_TREE_DRIVE1_NT
Language=English
Windows NT does not properly handle the shortcut to drive 1%0
.

MessageId=
SymbolicName=MSG_ITEM_SHELLEXT
Language=English
Context menu, drag & drop handler and drive property sheet%0
.

MessageId=
SymbolicName=MSG_ITEM_SHELLEXT_NT
Language=English
Context menu and drive property sheet%0
.

MessageId=
SymbolicName=MSG_ITEM_DESKTOP
Language=English
Create on the Desktop%0
.

MessageId=
SymbolicName=MSG_ITEM_STARTMENU
Language=English
Create in the Start Menu%0
.

MessageId=
SymbolicName=MSG_ITEM_SENDTO
Language=English
Create in the SendTo folder%0
.

;// Shortcut link name for VFD drives

MessageId=
SymbolicName=MSG_LINK_DRIVE
Language=English
VFD drive %1!d!%0
.

;// Shortcut link name for the VFD control panel
MessageId=
SymbolicName=MSG_LINK_CONFIG
Language=English
VFD Control Panel%0
.

;//====================================
;//	Message text for association dialog
;//====================================

MessageId=
SymbolicName=MSG_NEW_BUTTON
Language=English
&New Extension%0
.

MessageId=
SymbolicName=MSG_CHECK_ALL
Language=English
&Check All%0
.

MessageId=
SymbolicName=MSG_CLEAR_ALL
Language=English
&Uncheck All%0
.

MessageId=
SymbolicName=MSG_EXT_HEADER
Language=English
Extension%0
.

MessageId=
SymbolicName=MSG_APP_HEADER
Language=English
Program%0
.

MessageId=
SymbolicName=MSG_ASSOC_CANT_WRITE
Language=English
Not enough rights to edit file association.%0
.

MessageId=
SymbolicName=MSG_ASSOC_CANT_READ
Language=English
Failed to read the association information.%0
.

MessageId=
SymbolicName=MSG_ASSOC_FILETYPE_DESC
Language=English
Floppy Image%0
.

MessageId=
SymbolicName=MSG_ASSOC_FILETYPE_VERB
Language=English
Open with &VFD%0
.

;//====================================
;//	New extension dialog title
;//====================================

MessageId=
SymbolicName=MSG_NEWEXT_TITLE
Language=English
New Extension%0
.

MessageId=
SymbolicName=MSG_NEWEXT_LABEL
Language=English
Extension:%0
.

;//====================================
;//	Message text for about dialog
;//====================================
;//
;//	information url
;//
MessageId=
SymbolicName=MSG_ABOUT_URL
Language=English
http://chitchat.at.infoseek.co.jp/vmware/vfd.html%0
.

;//
;//	Help text
;//
MessageId=
SymbolicName=MSG_HELP_TEXT
Language=English
Command Line
============

VfdWin.exe
  Start the Virtual Floppy Drive Control Panel.

VfdWin.exe /OPEN [drive:] [file] [/RAM] [/P | /W] [/size] [/5] [/Q]
  Open an image on a Virtual Floppy Drive.

  drive:	Specifies a target Virtual Floppy drive, either by a drive
	number or a drive letter, such as "0:", "1:", "B:", "X:".
	The trailing ':' is required.
	The drive 0 is used if not specified.

  file	Specifies a Virtual Floppy image file to open.
	If the file does not exist, a new file is created.
	If not specified, an empty RAM disk is created.

  /RAM	RAM mode - Creates a copy of the file on RAM.
	Changes made to the disk are lost when the image is
	closed.  Read only files, NTFS encrypted/compressed files
	and WinImage compressed image (IMZ) files are always
	opened in RAM mode.
	This option is needed only to open other files, which are
	usually mounted directly, in RAM mode.

  /P	Opens the image as a write protected media.
	This is the default for RAM mode (except for empty RAM
	disks).

  /W	Opens the image as a writable media.
	This is the default for non-RAM and empty RAM disks.

  /size	Specifies a media size.
	The following options are accepted:

	/160 (160KB)    /820 (820KB)
	/180 (180KB)    /120 or /1.20 (1.20MB)
	/320 (320KB)    /144 or /1.44 (1.44MB)
	/360 (360KB)    /168 or /1.68 (1.68MB DMF)
	/640 (640KB)    /172 or /1.72 (1.72MB DMF)
	/720 (720KB)    /288 or /2.88 (2.88MB)

	If not specified, the media is decided from the file size
	for opening an existing file, and 1.44MB is selected for
	creating new file.
	Cannot specify a larger media than the target file.

  /5	Specifies a 5.25" media.  Takes effect only with
	640KB, 720KB and 1.2MB media.

  /Q	Do not open the drive folder afterward.

  If the target drive does not have a drive letter, this command also
  assigns the first available letter to the drive.

VfdWin.exe /CLOSE [drive:]
  Close the image.

  drive:	Specifies a target Virtual Floppy drive, either by a drive
	number or a drive letter, such as "0:", "1", "B:", "X".
	You may or may not add the trailing ':' to the drive letter.
	"*" stands for both drives.
	The drive 0 is used if not specified.
.

MessageId=
SymbolicName=MSG_ERR_APP_INTERNAL
Language=English
Application intrnal error.
.

MessageId=
SymbolicName=MSG_ERR_WRONG_PLATFORM
Language=English
Virtual Floppy Drive does not run on Windows 95/98/Me.
.

MessageId=
SymbolicName=MSG_ERR_INVALID_PARAM
Language=English
Invalid command line parameter %1!s!.
.

MessageId=
SymbolicName=MSG_ERR_INVALID_SIZE
Language=English
Invalid image size.
.

MessageId=
SymbolicName=MSG_HELP_TAB_CONTROL
Language=English
Select a tab to display a child page.%0
.

MessageId=
SymbolicName=MSG_HELP_LOG_MESSAGE
Language=English
Displays operation log message.%0
.

MessageId=
SymbolicName=MSG_HELP_STATE
Language=English
Displays the current driver state.%0
.

MessageId=
SymbolicName=MSG_HELP_LETTER
Language=English
A drive letter assigned to
the Virtual Floppy drive.%0
.

MessageId=
SymbolicName=MSG_HELP_CHANGE
Language=English
Change drive letter assignment.%0
.

MessageId=
SymbolicName=MSG_HELP_IMAGEFILE
Language=English
Displays the current virtual floppy image.%0
.

MessageId=
SymbolicName=MSG_HELP_DESCRIPTION
Language=English
Displays the image information.%0
.

MessageId=
SymbolicName=MSG_HELP_DISKTYPE
Language=English
Displays the virtual disk type.%0
.

MessageId=
SymbolicName=MSG_HELP_MEDIATYPE
Language=English
Displays the virtual media type.%0
.

MessageId=
SymbolicName=MSG_HELP_PROTECT
Language=English
Enable/disable the write protection.
The change takes effect immediately.%0
.

MessageId=
SymbolicName=MSG_HELP_OPEN
Language=English
Open or create a virtual floppy image.%0
.

MessageId=
SymbolicName=MSG_HELP_SAVE
Language=English
Save the current image to a file.%0
.

MessageId=
SymbolicName=MSG_HELP_CLOSE
Language=English
Close the current image.%0
.

MessageId=
SymbolicName=MSG_HELP_FORMAT
Language=English
Format the current virtual media with FAT.%0
.

MessageId=
SymbolicName=MSG_HELP_DRIVER
Language=English
The VFD driver file path.%0
.

MessageId=
SymbolicName=MSG_HELP_BROWSE
Language=English
Browse for folders to find the driver file.%0
.

MessageId=
SymbolicName=MSG_HELP_VERSION
Language=English
Displays the driver file version.%0
.

MessageId=
SymbolicName=MSG_HELP_STARTTYPE
Language=English
The driver start type
Manual: the driver must be started manually.
Auto: the driver is started on system start up.%0
.

MessageId=
SymbolicName=MSG_HELP_INSTALL
Language=English
Install the driver.%0
.

MessageId=
SymbolicName=MSG_HELP_START
Language=English
Start the driver.%0
.

MessageId=
SymbolicName=MSG_HELP_STOP
Language=English
Stop the driver.%0
.

MessageId=
SymbolicName=MSG_HELP_REMOVE
Language=English
Uninstall the driver from system.
The driver file is not removed.%0
.

MessageId=
SymbolicName=MSG_HELP_LIST
Language=English
List of the current association.%0
.

MessageId=
SymbolicName=MSG_HELP_MESSAGE
Language=English
Displays the reason why the
association cannot be edited.%0
.

MessageId=
SymbolicName=MSG_HELP_NEW
Language=English
Add a new extension to show in the list.%0
.

MessageId=
SymbolicName=MSG_HELP_ALL
Language=English
Check all items in the list.%0
.

MessageId=
SymbolicName=MSG_HELP_CLEAR
Language=English
Uncheck all items in the list.%0
.

MessageId=
SymbolicName=MSG_HELP_APPLY
Language=English
Apply the current change.%0
.

MessageId=
SymbolicName=MSG_HELP_TREE
Language=English
Displays a list of shell related features.%0
.

MessageId=
SymbolicName=MSG_HELP_PRODUCT
Language=English
Displays the product name.%0
.

MessageId=
SymbolicName=MSG_HELP_URL
Language=English
Click to open the page in the browser.%0
.

MessageId=
SymbolicName=MSG_HELP_HELP
Language=English
Displays the command line usage of this program.%0
.

MessageId=
SymbolicName=MSG_HELP_COPYRIGHT
Language=English
Displays the copyright information.%0
.

MessageId=
SymbolicName=MSG_HELP_EXTENSION
Language=English
Enter a file extension to associate.
A leading period is optional.%0
.

MessageId=
SymbolicName=MSG_HELP_PERSISTENT
Language=English
Make the drive letter global/persistent.%0
.

;
;#endif // _VFDMSG_H_
