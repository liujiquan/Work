;/*
;   vfdmsg.h
;
;   Virtual Floppy Drive for Windows
;   Driver control library
;   Message definition
;
;   Copyright (c) 2003-2005 Ken Kato
;*/
;

;#ifndef _VFDMSG_H_
;#define _VFDMSG_H_
;

MessageIdTypedef=DWORD
LanguageNames=(English=0x409:msg0409)

;
;//
;//	Context menu text
;//
;
MessageId=
SymbolicName=MSG_MENU_OPEN
Language=English
&Open VFD image...%0
.

MessageId=
SymbolicName=MSG_HELP_OPEN
Language=English
Open a virtual floppy image.%0
.

MessageId=
SymbolicName=MSG_MENU_CLOSE
Language=English
&Close VFD image%0
.

MessageId=
SymbolicName=MSG_HELP_CLOSE
Language=English
Close the current virtual floppy image.%0
.

MessageId=
SymbolicName=MSG_MENU_SAVE
Language=English
&Save VFD image...%0
.

MessageId=
SymbolicName=MSG_HELP_SAVE
Language=English
Save the current image into a file.%0
.

MessageId=
SymbolicName=MSG_MENU_PROTECT
Language=English
&Write Protect%0
.

MessageId=
SymbolicName=MSG_HELP_PROTECT
Language=English
Enable/disable the media write protection.%0
.

MessageId=
SymbolicName=MSG_MENU_PROP
Language=English
VFD &Property%0
.

MessageId=
SymbolicName=MSG_HELP_PROP
Language=English
Display the VFD property page.%0
.

MessageId=
SymbolicName=MSG_MENU_DROP
Language=English
&Open with VFD%0
.

MessageId=
SymbolicName=MSG_HELP_DROP
Language=English
Open the file with VFD.%0
.

;
;//
;//	Dialog title text
;//
;

MessageId=
SymbolicName=MSG_OPEN_TITLE_EN
Language=English
Open Virtual Floppy Image%0
.

MessageId=
SymbolicName=MSG_OPEN_TITLE_IT
Language=English
Apri Immagine%0
.

MessageId=
SymbolicName=MSG_OPEN_TITLE_SP
Language=English
Abrir la imagen%0
.

MessageId=
SymbolicName=MSG_SAVE_TITLE_EN
Language=English
Save Virtual Floppy Image%0
.

MessageId=
SymbolicName=MSG_SAVE_TITLE_IT
Language=English
Salva Immagine%0
.

MessageId=
SymbolicName=MSG_SAVE_TITLE_SP
Language=English
Guardar imagen%0
.

;
;//
;//	Dialog label text
;//
;

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
SymbolicName=MSG_IMAGEFILE_ACCEL_EN
Language=English
&Image File:%0
.

MessageId=
SymbolicName=MSG_IMAGEFILE_ACCEL_IT
Language=English
&Immagine:%0
.

MessageId=
SymbolicName=MSG_IMAGEFILE_ACCEL_SP
Language=English
&Imagen:%0
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
SymbolicName=MSG_MEDIATYPE_ACCEL_EN
Language=English
Media Type:%0
.

MessageId=
SymbolicName=MSG_MEDIATYPE_ACCEL_IT
Language=English
&Tipo:%0
.

MessageId=
SymbolicName=MSG_MEDIATYPE_ACCEL_SP
Language=English
&Tipo:%0
.

MessageId=
SymbolicName=MSG_TARGETFILE_LABEL_EN
Language=English
&Target File:%0
.

MessageId=
SymbolicName=MSG_TARGETFILE_LABEL_IT
Language=English
&Destinazione:%0
.

MessageId=
SymbolicName=MSG_TARGETFILE_LABEL_SP
Language=English
&Destinacion:%0
.

;
;//
;//	button text
;//
;

MessageId=
SymbolicName=MSG_OPEN_BUTTON_EN
Language=English
&Open%0
.

MessageId=
SymbolicName=MSG_OPEN_BUTTON_IT
Language=English
&Apri%0
.

MessageId=
SymbolicName=MSG_OPEN_BUTTON_SP
Language=English
&Abrir%0
.

MessageId=
SymbolicName=MSG_CREATE_BUTTON_EN
Language=English
&Create%0
.

MessageId=
SymbolicName=MSG_CREATE_BUTTON_IT
Language=English
&Crea%0
.

MessageId=
SymbolicName=MSG_CREATE_BUTTON_SP
Language=English
&Creación%0
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

MessageId=
SymbolicName=MSG_CONTROL_BUTTON
Language=English
&VFD Control Panel%0
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
&Configuración%0
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
SymbolicName=MSG_OVERWRITE_CHECK_EN
Language=English
Overwrite an existing file%0
.

MessageId=
SymbolicName=MSG_OVERWRITE_CHECK_IT
Language=English
Sovrascrivi un file esistente%0
.

MessageId=
SymbolicName=MSG_OVERWRITE_CHECK_SP
Language=English
Sobrescribir un archivo existente%0
.

MessageId=
SymbolicName=MSG_TRUNCATE_CHECK_EN
Language=English
Truncate an existing file%0
.

MessageId=
SymbolicName=MSG_TRUNCATE_CHECK_IT
Language=English
Tronca un file esistente%0
.

MessageId=
SymbolicName=MSG_TRUNCATE_CHECK_SP
Language=English
Trunca un archivo existente%0
.

;
;//
;//	file description text
;//
;

MessageId=
SymbolicName=MSG_FILETYPE_RAW_EN
Language=English
RAW image%0
.

MessageId=
SymbolicName=MSG_FILETYPE_RAW_IT
Language=English
Immagine RAW%0
.

MessageId=
SymbolicName=MSG_FILETYPE_RAW_SP
Language=English
Imagen RAW%0
.

MessageId=
SymbolicName=MSG_FILETYPE_ZIP
Language=English
ZIP image%0
.

MessageId=
SymbolicName=MSG_DESC_NEW_FILE_EN
Language=English
New file%0
.

MessageId=
SymbolicName=MSG_DESC_NEW_FILE_IT
Language=English
Nuovo File%0
.

MessageId=
SymbolicName=MSG_DESC_NEW_FILE_SP
Language=English
Nuevo archivo%0
.

MessageId=
SymbolicName=MSG_DESC_FILESIZE
Language=English
%1!s! bytes (%2!s!)%0
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

;
;//
;// ToolTip
;//
;
MessageId=
SymbolicName=MSG_WRITE_PROTECTED
Language=English
&Write Protected%0
.

MessageId=
SymbolicName=MSG_WRITE_ALLOWED
Language=English
Write Allowed%0
.

MessageId=
SymbolicName=MSG_IMAGE_INFOTIP
Language=English
%1!s!
%2!s!
Type: %3!s! disk
Media: %4!s!
%5!s!%0
.

;
;//
;// Context help text
;//
;

MessageId=
SymbolicName=MSG_HELP_IMAGEFILE
Language=English
Image file name.%0
.

MessageId=
SymbolicName=MSG_HELP_IMAGEDESC
Language=English
Information about the image file.%0
.

MessageId=
SymbolicName=MSG_HELP_TARGETFILE
Language=English
Save target file name.%0
.

MessageId=
SymbolicName=MSG_HELP_DISKTYPE
Language=English
Virtual disk type.%0
.

MessageId=
SymbolicName=MSG_HELP_MEDIATYPE
Language=English
Virtual floppy media type.%0
.

MessageId=
SymbolicName=MSG_HELP_FORMAT
Language=English
Click to format the
current image with FAT.%0
.

MessageId=
SymbolicName=MSG_HELP_CONTROL
Language=English
Start the VFD Control Panel.%0
.

MessageId=
SymbolicName=MSG_HELP_PROTECT_NOW
Language=English
Enable/disable the media write protection.
The change takes effect immediately.%0
.

MessageId=
SymbolicName=MSG_HELP_PROTECT_OPEN
Language=English
Open the image as a
write protected media.%0
.

MessageId=
SymbolicName=MSG_HELP_BROWSE
Language=English
Browse for folders to
find the target file.%0
.

MessageId=
SymbolicName=MSG_HELP_OVERWRITE
Language=English
Overwrite the existing file
to save the current image.%0
.

MessageId=
SymbolicName=MSG_HELP_TRUNCATE
Language=English
Truncate the target file after
saving the current image.%0
.

;
;//
;// Hint text
;//
;

MessageId=
SymbolicName=MSG_CURRENT_FILE_EN
Language=English
Current image file%0
.

MessageId=
SymbolicName=MSG_CURRENT_FILE_IT
Language=English
File d'immagine corrente%0
.

MessageId=
SymbolicName=MSG_CURRENT_FILE_SP
Language=English
Archivo de imagen corriente%0
.

MessageId=
SymbolicName=MSG_FILE_TOO_SMALL_EN
Language=English
The file is too small for the selected media type%0
.

MessageId=
SymbolicName=MSG_FILE_TOO_SMALL_IT
Language=English
File troppo piccolo per il tipo selezionato%0
.

MessageId=
SymbolicName=MSG_FILE_TOO_SMALL_SP
Language=English
El archivo es demasiado pequeño para el tipo seleccionado%0
.

MessageId=
SymbolicName=MSG_SIZE_MISMATCH_EN
Language=English
The file size does not match the selected media size%0
.

MessageId=
SymbolicName=MSG_SIZE_MISMATCH_IT
Language=English
La dimensione del file non coincide col tipo%0
.

MessageId=
SymbolicName=MSG_SIZE_MISMATCH_SP
Language=English
El tamaño del archivo no coincide con el tipo%0
.

MessageId=
SymbolicName=MSG_FILE_ACCESS_ERROR_EN
Language=English
Cannot access the file%0
.

MessageId=
SymbolicName=MSG_FILE_ACCESS_ERROR_IT
Language=English
Impossibile accedere al file%0
.

MessageId=
SymbolicName=MSG_FILE_ACCESS_ERROR_SP
Language=English
No puedo acceder al archivo%0
.

MessageId=
SymbolicName=MSG_TARGET_IS_ZIP
Language=English
Cannot overwrite a ZIP compressed file.%0
.

;
;//
;// Other text
;//
;

MessageId=
SymbolicName=MSG_OPEN_FILTER_EN
Language=English
Image Files (.img)|*.img|%0
.

MessageId=
SymbolicName=MSG_OPEN_FILTER_IT
Language=English
Immagine (.img)|*.img|%0
.

MessageId=
SymbolicName=MSG_OPEN_FILTER_SP
Language=English
Imagen (.img) |*.img|%0
.

MessageId=
SymbolicName=MSG_FORMAT_WARNING
Language=English
Warning: Formatting will erase all data on this disk.
Click [OK] to format the disk, [Cancel] to quit.%0
.

MessageId=
SymbolicName=MSG_MEDIA_MODIFIED
Language=English
Data on the RAM disk is modified.
Save to a file before closing ?%0
.

MessageId=
SymbolicName=MSG_UNMOUNT_CONFIRM
Language=English
Failed to lock the volume.
Make sure that any files are not in use.
Continuing forces all files to be closed.%0
.

MessageId=
SymbolicName=MSG_UNMOUNT_FAILED
Language=English
Failed to unmount the volume.
Make sure that any files are not in use.%0
.

;
;#endif // _VFDMSG_H_
