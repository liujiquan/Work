/*
   vfdmsg.h

   Virtual Floppy Drive for Windows
   Driver control library
   Message definition

   Copyright (c) 2003-2005 Ken Kato
*/

#ifndef _VFDMSG_H_
#define _VFDMSG_H_


//
//	Context menu text
//

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: MSG_MENU_OPEN
//
// MessageText:
//
//  &Open VFD image...%0
//
#define MSG_MENU_OPEN                    ((DWORD)0x00000001L)

//
// MessageId: MSG_HELP_OPEN
//
// MessageText:
//
//  Open a virtual floppy image.%0
//
#define MSG_HELP_OPEN                    ((DWORD)0x00000002L)

//
// MessageId: MSG_MENU_CLOSE
//
// MessageText:
//
//  &Close VFD image%0
//
#define MSG_MENU_CLOSE                   ((DWORD)0x00000003L)

//
// MessageId: MSG_HELP_CLOSE
//
// MessageText:
//
//  Close the current virtual floppy image.%0
//
#define MSG_HELP_CLOSE                   ((DWORD)0x00000004L)

//
// MessageId: MSG_MENU_SAVE
//
// MessageText:
//
//  &Save VFD image...%0
//
#define MSG_MENU_SAVE                    ((DWORD)0x00000005L)

//
// MessageId: MSG_HELP_SAVE
//
// MessageText:
//
//  Save the current image into a file.%0
//
#define MSG_HELP_SAVE                    ((DWORD)0x00000006L)

//
// MessageId: MSG_MENU_PROTECT
//
// MessageText:
//
//  &Write Protect%0
//
#define MSG_MENU_PROTECT                 ((DWORD)0x00000007L)

//
// MessageId: MSG_HELP_PROTECT
//
// MessageText:
//
//  Enable/disable the media write protection.%0
//
#define MSG_HELP_PROTECT                 ((DWORD)0x00000008L)

//
// MessageId: MSG_MENU_PROP
//
// MessageText:
//
//  VFD &Property%0
//
#define MSG_MENU_PROP                    ((DWORD)0x00000009L)

//
// MessageId: MSG_HELP_PROP
//
// MessageText:
//
//  Display the VFD property page.%0
//
#define MSG_HELP_PROP                    ((DWORD)0x0000000AL)

//
// MessageId: MSG_MENU_DROP
//
// MessageText:
//
//  &Open with VFD%0
//
#define MSG_MENU_DROP                    ((DWORD)0x0000000BL)

//
// MessageId: MSG_HELP_DROP
//
// MessageText:
//
//  Open the file with VFD.%0
//
#define MSG_HELP_DROP                    ((DWORD)0x0000000CL)


//
//	Dialog title text
//

//
// MessageId: MSG_OPEN_TITLE_EN
//
// MessageText:
//
//  Open Virtual Floppy Image%0
//
#define MSG_OPEN_TITLE_EN                ((DWORD)0x0000000DL)

//
// MessageId: MSG_OPEN_TITLE_IT
//
// MessageText:
//
//  Apri Immagine%0
//
#define MSG_OPEN_TITLE_IT                ((DWORD)0x0000000EL)

//
// MessageId: MSG_OPEN_TITLE_SP
//
// MessageText:
//
//  Abrir la imagen%0
//
#define MSG_OPEN_TITLE_SP                ((DWORD)0x0000000FL)

//
// MessageId: MSG_SAVE_TITLE_EN
//
// MessageText:
//
//  Save Virtual Floppy Image%0
//
#define MSG_SAVE_TITLE_EN                ((DWORD)0x00000010L)

//
// MessageId: MSG_SAVE_TITLE_IT
//
// MessageText:
//
//  Salva Immagine%0
//
#define MSG_SAVE_TITLE_IT                ((DWORD)0x00000011L)

//
// MessageId: MSG_SAVE_TITLE_SP
//
// MessageText:
//
//  Guardar imagen%0
//
#define MSG_SAVE_TITLE_SP                ((DWORD)0x00000012L)


//
//	Dialog label text
//

//
// MessageId: MSG_IMAGEFILE_LABEL_EN
//
// MessageText:
//
//  Image File:%0
//
#define MSG_IMAGEFILE_LABEL_EN           ((DWORD)0x00000013L)

//
// MessageId: MSG_IMAGEFILE_LABEL_IT
//
// MessageText:
//
//  Immagine:%0
//
#define MSG_IMAGEFILE_LABEL_IT           ((DWORD)0x00000014L)

//
// MessageId: MSG_IMAGEFILE_LABEL_SP
//
// MessageText:
//
//  Imagen:%0
//
#define MSG_IMAGEFILE_LABEL_SP           ((DWORD)0x00000015L)

//
// MessageId: MSG_IMAGEFILE_ACCEL_EN
//
// MessageText:
//
//  &Image File:%0
//
#define MSG_IMAGEFILE_ACCEL_EN           ((DWORD)0x00000016L)

//
// MessageId: MSG_IMAGEFILE_ACCEL_IT
//
// MessageText:
//
//  &Immagine:%0
//
#define MSG_IMAGEFILE_ACCEL_IT           ((DWORD)0x00000017L)

//
// MessageId: MSG_IMAGEFILE_ACCEL_SP
//
// MessageText:
//
//  &Imagen:%0
//
#define MSG_IMAGEFILE_ACCEL_SP           ((DWORD)0x00000018L)

//
// MessageId: MSG_DESCRIPTION_LABEL_EN
//
// MessageText:
//
//  Description:%0
//
#define MSG_DESCRIPTION_LABEL_EN         ((DWORD)0x00000019L)

//
// MessageId: MSG_DESCRIPTION_LABEL_IT
//
// MessageText:
//
//  Descrizione:%0
//
#define MSG_DESCRIPTION_LABEL_IT         ((DWORD)0x0000001AL)

//
// MessageId: MSG_DESCRIPTION_LABEL_SP
//
// MessageText:
//
//  Descripción:%0
//
#define MSG_DESCRIPTION_LABEL_SP         ((DWORD)0x0000001BL)

//
// MessageId: MSG_DISKTYPE_LABEL
//
// MessageText:
//
//  Disk Type:%0
//
#define MSG_DISKTYPE_LABEL               ((DWORD)0x0000001CL)

//
// MessageId: MSG_MEDIATYPE_LABEL_EN
//
// MessageText:
//
//  Media Type:%0
//
#define MSG_MEDIATYPE_LABEL_EN           ((DWORD)0x0000001DL)

//
// MessageId: MSG_MEDIATYPE_LABEL_IT
//
// MessageText:
//
//  Tipo:%0
//
#define MSG_MEDIATYPE_LABEL_IT           ((DWORD)0x0000001EL)

//
// MessageId: MSG_MEDIATYPE_LABEL_SP
//
// MessageText:
//
//  Tipo:%0
//
#define MSG_MEDIATYPE_LABEL_SP           ((DWORD)0x0000001FL)

//
// MessageId: MSG_MEDIATYPE_ACCEL_EN
//
// MessageText:
//
//  Media Type:%0
//
#define MSG_MEDIATYPE_ACCEL_EN           ((DWORD)0x00000020L)

//
// MessageId: MSG_MEDIATYPE_ACCEL_IT
//
// MessageText:
//
//  &Tipo:%0
//
#define MSG_MEDIATYPE_ACCEL_IT           ((DWORD)0x00000021L)

//
// MessageId: MSG_MEDIATYPE_ACCEL_SP
//
// MessageText:
//
//  &Tipo:%0
//
#define MSG_MEDIATYPE_ACCEL_SP           ((DWORD)0x00000022L)

//
// MessageId: MSG_TARGETFILE_LABEL_EN
//
// MessageText:
//
//  &Target File:%0
//
#define MSG_TARGETFILE_LABEL_EN          ((DWORD)0x00000023L)

//
// MessageId: MSG_TARGETFILE_LABEL_IT
//
// MessageText:
//
//  &Destinazione:%0
//
#define MSG_TARGETFILE_LABEL_IT          ((DWORD)0x00000024L)

//
// MessageId: MSG_TARGETFILE_LABEL_SP
//
// MessageText:
//
//  &Destinacion:%0
//
#define MSG_TARGETFILE_LABEL_SP          ((DWORD)0x00000025L)


//
//	button text
//

//
// MessageId: MSG_OPEN_BUTTON_EN
//
// MessageText:
//
//  &Open%0
//
#define MSG_OPEN_BUTTON_EN               ((DWORD)0x00000026L)

//
// MessageId: MSG_OPEN_BUTTON_IT
//
// MessageText:
//
//  &Apri%0
//
#define MSG_OPEN_BUTTON_IT               ((DWORD)0x00000027L)

//
// MessageId: MSG_OPEN_BUTTON_SP
//
// MessageText:
//
//  &Abrir%0
//
#define MSG_OPEN_BUTTON_SP               ((DWORD)0x00000028L)

//
// MessageId: MSG_CREATE_BUTTON_EN
//
// MessageText:
//
//  &Create%0
//
#define MSG_CREATE_BUTTON_EN             ((DWORD)0x00000029L)

//
// MessageId: MSG_CREATE_BUTTON_IT
//
// MessageText:
//
//  &Crea%0
//
#define MSG_CREATE_BUTTON_IT             ((DWORD)0x0000002AL)

//
// MessageId: MSG_CREATE_BUTTON_SP
//
// MessageText:
//
//  &Creación%0
//
#define MSG_CREATE_BUTTON_SP             ((DWORD)0x0000002BL)

//
// MessageId: MSG_SAVE_BUTTON_EN
//
// MessageText:
//
//  &Save%0
//
#define MSG_SAVE_BUTTON_EN               ((DWORD)0x0000002CL)

//
// MessageId: MSG_SAVE_BUTTON_IT
//
// MessageText:
//
//  &Salva%0
//
#define MSG_SAVE_BUTTON_IT               ((DWORD)0x0000002DL)

//
// MessageId: MSG_SAVE_BUTTON_SP
//
// MessageText:
//
//  &Guardar%0
//
#define MSG_SAVE_BUTTON_SP               ((DWORD)0x0000002EL)

//
// MessageId: MSG_CLOSE_BUTTON_EN
//
// MessageText:
//
//  &Close%0
//
#define MSG_CLOSE_BUTTON_EN              ((DWORD)0x0000002FL)

//
// MessageId: MSG_CLOSE_BUTTON_IT
//
// MessageText:
//
//  &Chiudi%0
//
#define MSG_CLOSE_BUTTON_IT              ((DWORD)0x00000030L)

//
// MessageId: MSG_CLOSE_BUTTON_SP
//
// MessageText:
//
//  &Cerrar%0
//
#define MSG_CLOSE_BUTTON_SP              ((DWORD)0x00000031L)

//
// MessageId: MSG_FORMAT_BUTTON
//
// MessageText:
//
//  &Format%0
//
#define MSG_FORMAT_BUTTON                ((DWORD)0x00000032L)

//
// MessageId: MSG_CONTROL_BUTTON
//
// MessageText:
//
//  &VFD Control Panel%0
//
#define MSG_CONTROL_BUTTON               ((DWORD)0x00000033L)

//
// MessageId: MSG_BROWSE_BUTTON_EN
//
// MessageText:
//
//  &Browse%0
//
#define MSG_BROWSE_BUTTON_EN             ((DWORD)0x00000034L)

//
// MessageId: MSG_BROWSE_BUTTON_IT
//
// MessageText:
//
//  &Imposta%0
//
#define MSG_BROWSE_BUTTON_IT             ((DWORD)0x00000035L)

//
// MessageId: MSG_BROWSE_BUTTON_SP
//
// MessageText:
//
//  &Configuración%0
//
#define MSG_BROWSE_BUTTON_SP             ((DWORD)0x00000036L)

//
// MessageId: MSG_CANCEL_BUTTON_EN
//
// MessageText:
//
//  Cancel%0
//
#define MSG_CANCEL_BUTTON_EN             ((DWORD)0x00000037L)

//
// MessageId: MSG_CANCEL_BUTTON_IT
//
// MessageText:
//
//  Annulla%0
//
#define MSG_CANCEL_BUTTON_IT             ((DWORD)0x00000038L)

//
// MessageId: MSG_CANCEL_BUTTON_SP
//
// MessageText:
//
//  Anular%0
//
#define MSG_CANCEL_BUTTON_SP             ((DWORD)0x00000039L)

//
// MessageId: MSG_OVERWRITE_CHECK_EN
//
// MessageText:
//
//  Overwrite an existing file%0
//
#define MSG_OVERWRITE_CHECK_EN           ((DWORD)0x0000003AL)

//
// MessageId: MSG_OVERWRITE_CHECK_IT
//
// MessageText:
//
//  Sovrascrivi un file esistente%0
//
#define MSG_OVERWRITE_CHECK_IT           ((DWORD)0x0000003BL)

//
// MessageId: MSG_OVERWRITE_CHECK_SP
//
// MessageText:
//
//  Sobrescribir un archivo existente%0
//
#define MSG_OVERWRITE_CHECK_SP           ((DWORD)0x0000003CL)

//
// MessageId: MSG_TRUNCATE_CHECK_EN
//
// MessageText:
//
//  Truncate an existing file%0
//
#define MSG_TRUNCATE_CHECK_EN            ((DWORD)0x0000003DL)

//
// MessageId: MSG_TRUNCATE_CHECK_IT
//
// MessageText:
//
//  Tronca un file esistente%0
//
#define MSG_TRUNCATE_CHECK_IT            ((DWORD)0x0000003EL)

//
// MessageId: MSG_TRUNCATE_CHECK_SP
//
// MessageText:
//
//  Trunca un archivo existente%0
//
#define MSG_TRUNCATE_CHECK_SP            ((DWORD)0x0000003FL)


//
//	file description text
//

//
// MessageId: MSG_FILETYPE_RAW_EN
//
// MessageText:
//
//  RAW image%0
//
#define MSG_FILETYPE_RAW_EN              ((DWORD)0x00000040L)

//
// MessageId: MSG_FILETYPE_RAW_IT
//
// MessageText:
//
//  Immagine RAW%0
//
#define MSG_FILETYPE_RAW_IT              ((DWORD)0x00000041L)

//
// MessageId: MSG_FILETYPE_RAW_SP
//
// MessageText:
//
//  Imagen RAW%0
//
#define MSG_FILETYPE_RAW_SP              ((DWORD)0x00000042L)

//
// MessageId: MSG_FILETYPE_ZIP
//
// MessageText:
//
//  ZIP image%0
//
#define MSG_FILETYPE_ZIP                 ((DWORD)0x00000043L)

//
// MessageId: MSG_DESC_NEW_FILE_EN
//
// MessageText:
//
//  New file%0
//
#define MSG_DESC_NEW_FILE_EN             ((DWORD)0x00000044L)

//
// MessageId: MSG_DESC_NEW_FILE_IT
//
// MessageText:
//
//  Nuovo File%0
//
#define MSG_DESC_NEW_FILE_IT             ((DWORD)0x00000045L)

//
// MessageId: MSG_DESC_NEW_FILE_SP
//
// MessageText:
//
//  Nuevo archivo%0
//
#define MSG_DESC_NEW_FILE_SP             ((DWORD)0x00000046L)

//
// MessageId: MSG_DESC_FILESIZE
//
// MessageText:
//
//  %1!s! bytes (%2!s!)%0
//
#define MSG_DESC_FILESIZE                ((DWORD)0x00000047L)

//
// MessageId: MSG_ATTR_READONLY
//
// MessageText:
//
//  ReadOnly%0
//
#define MSG_ATTR_READONLY                ((DWORD)0x00000048L)

//
// MessageId: MSG_ATTR_COMPRESSED
//
// MessageText:
//
//  Compressed%0
//
#define MSG_ATTR_COMPRESSED              ((DWORD)0x00000049L)

//
// MessageId: MSG_ATTR_ENCRYPTED
//
// MessageText:
//
//  Encrypted%0
//
#define MSG_ATTR_ENCRYPTED               ((DWORD)0x0000004AL)


//
// ToolTip
//

//
// MessageId: MSG_WRITE_PROTECTED
//
// MessageText:
//
//  &Write Protected%0
//
#define MSG_WRITE_PROTECTED              ((DWORD)0x0000004BL)

//
// MessageId: MSG_WRITE_ALLOWED
//
// MessageText:
//
//  Write Allowed%0
//
#define MSG_WRITE_ALLOWED                ((DWORD)0x0000004CL)

//
// MessageId: MSG_IMAGE_INFOTIP
//
// MessageText:
//
//  %1!s!
//  %2!s!
//  Type: %3!s! disk
//  Media: %4!s!
//  %5!s!%0
//
#define MSG_IMAGE_INFOTIP                ((DWORD)0x0000004DL)


//
// Context help text
//

//
// MessageId: MSG_HELP_IMAGEFILE
//
// MessageText:
//
//  Image file name.%0
//
#define MSG_HELP_IMAGEFILE               ((DWORD)0x0000004EL)

//
// MessageId: MSG_HELP_IMAGEDESC
//
// MessageText:
//
//  Information about the image file.%0
//
#define MSG_HELP_IMAGEDESC               ((DWORD)0x0000004FL)

//
// MessageId: MSG_HELP_TARGETFILE
//
// MessageText:
//
//  Save target file name.%0
//
#define MSG_HELP_TARGETFILE              ((DWORD)0x00000050L)

//
// MessageId: MSG_HELP_DISKTYPE
//
// MessageText:
//
//  Virtual disk type.%0
//
#define MSG_HELP_DISKTYPE                ((DWORD)0x00000051L)

//
// MessageId: MSG_HELP_MEDIATYPE
//
// MessageText:
//
//  Virtual floppy media type.%0
//
#define MSG_HELP_MEDIATYPE               ((DWORD)0x00000052L)

//
// MessageId: MSG_HELP_FORMAT
//
// MessageText:
//
//  Click to format the
//  current image with FAT.%0
//
#define MSG_HELP_FORMAT                  ((DWORD)0x00000053L)

//
// MessageId: MSG_HELP_CONTROL
//
// MessageText:
//
//  Start the VFD Control Panel.%0
//
#define MSG_HELP_CONTROL                 ((DWORD)0x00000054L)

//
// MessageId: MSG_HELP_PROTECT_NOW
//
// MessageText:
//
//  Enable/disable the media write protection.
//  The change takes effect immediately.%0
//
#define MSG_HELP_PROTECT_NOW             ((DWORD)0x00000055L)

//
// MessageId: MSG_HELP_PROTECT_OPEN
//
// MessageText:
//
//  Open the image as a
//  write protected media.%0
//
#define MSG_HELP_PROTECT_OPEN            ((DWORD)0x00000056L)

//
// MessageId: MSG_HELP_BROWSE
//
// MessageText:
//
//  Browse for folders to
//  find the target file.%0
//
#define MSG_HELP_BROWSE                  ((DWORD)0x00000057L)

//
// MessageId: MSG_HELP_OVERWRITE
//
// MessageText:
//
//  Overwrite the existing file
//  to save the current image.%0
//
#define MSG_HELP_OVERWRITE               ((DWORD)0x00000058L)

//
// MessageId: MSG_HELP_TRUNCATE
//
// MessageText:
//
//  Truncate the target file after
//  saving the current image.%0
//
#define MSG_HELP_TRUNCATE                ((DWORD)0x00000059L)


//
// Hint text
//

//
// MessageId: MSG_CURRENT_FILE_EN
//
// MessageText:
//
//  Current image file%0
//
#define MSG_CURRENT_FILE_EN              ((DWORD)0x0000005AL)

//
// MessageId: MSG_CURRENT_FILE_IT
//
// MessageText:
//
//  File d'immagine corrente%0
//
#define MSG_CURRENT_FILE_IT              ((DWORD)0x0000005BL)

//
// MessageId: MSG_CURRENT_FILE_SP
//
// MessageText:
//
//  Archivo de imagen corriente%0
//
#define MSG_CURRENT_FILE_SP              ((DWORD)0x0000005CL)

//
// MessageId: MSG_FILE_TOO_SMALL_EN
//
// MessageText:
//
//  The file is too small for the selected media type%0
//
#define MSG_FILE_TOO_SMALL_EN            ((DWORD)0x0000005DL)

//
// MessageId: MSG_FILE_TOO_SMALL_IT
//
// MessageText:
//
//  File troppo piccolo per il tipo selezionato%0
//
#define MSG_FILE_TOO_SMALL_IT            ((DWORD)0x0000005EL)

//
// MessageId: MSG_FILE_TOO_SMALL_SP
//
// MessageText:
//
//  El archivo es demasiado pequeño para el tipo seleccionado%0
//
#define MSG_FILE_TOO_SMALL_SP            ((DWORD)0x0000005FL)

//
// MessageId: MSG_SIZE_MISMATCH_EN
//
// MessageText:
//
//  The file size does not match the selected media size%0
//
#define MSG_SIZE_MISMATCH_EN             ((DWORD)0x00000060L)

//
// MessageId: MSG_SIZE_MISMATCH_IT
//
// MessageText:
//
//  La dimensione del file non coincide col tipo%0
//
#define MSG_SIZE_MISMATCH_IT             ((DWORD)0x00000061L)

//
// MessageId: MSG_SIZE_MISMATCH_SP
//
// MessageText:
//
//  El tamaño del archivo no coincide con el tipo%0
//
#define MSG_SIZE_MISMATCH_SP             ((DWORD)0x00000062L)

//
// MessageId: MSG_FILE_ACCESS_ERROR_EN
//
// MessageText:
//
//  Cannot access the file%0
//
#define MSG_FILE_ACCESS_ERROR_EN         ((DWORD)0x00000063L)

//
// MessageId: MSG_FILE_ACCESS_ERROR_IT
//
// MessageText:
//
//  Impossibile accedere al file%0
//
#define MSG_FILE_ACCESS_ERROR_IT         ((DWORD)0x00000064L)

//
// MessageId: MSG_FILE_ACCESS_ERROR_SP
//
// MessageText:
//
//  No puedo acceder al archivo%0
//
#define MSG_FILE_ACCESS_ERROR_SP         ((DWORD)0x00000065L)

//
// MessageId: MSG_TARGET_IS_ZIP
//
// MessageText:
//
//  Cannot overwrite a ZIP compressed file.%0
//
#define MSG_TARGET_IS_ZIP                ((DWORD)0x00000066L)


//
// Other text
//

//
// MessageId: MSG_OPEN_FILTER_EN
//
// MessageText:
//
//  Image Files (.img)|*.img|%0
//
#define MSG_OPEN_FILTER_EN               ((DWORD)0x00000067L)

//
// MessageId: MSG_OPEN_FILTER_IT
//
// MessageText:
//
//  Immagine (.img)|*.img|%0
//
#define MSG_OPEN_FILTER_IT               ((DWORD)0x00000068L)

//
// MessageId: MSG_OPEN_FILTER_SP
//
// MessageText:
//
//  Imagen (.img) |*.img|%0
//
#define MSG_OPEN_FILTER_SP               ((DWORD)0x00000069L)

//
// MessageId: MSG_FORMAT_WARNING
//
// MessageText:
//
//  Warning: Formatting will erase all data on this disk.
//  Click [OK] to format the disk, [Cancel] to quit.%0
//
#define MSG_FORMAT_WARNING               ((DWORD)0x0000006AL)

//
// MessageId: MSG_MEDIA_MODIFIED
//
// MessageText:
//
//  Data on the RAM disk is modified.
//  Save to a file before closing ?%0
//
#define MSG_MEDIA_MODIFIED               ((DWORD)0x0000006BL)

//
// MessageId: MSG_UNMOUNT_CONFIRM
//
// MessageText:
//
//  Failed to lock the volume.
//  Make sure that any files are not in use.
//  Continuing forces all files to be closed.%0
//
#define MSG_UNMOUNT_CONFIRM              ((DWORD)0x0000006CL)

//
// MessageId: MSG_UNMOUNT_FAILED
//
// MessageText:
//
//  Failed to unmount the volume.
//  Make sure that any files are not in use.%0
//
#define MSG_UNMOUNT_FAILED               ((DWORD)0x0000006DL)


#endif // _VFDMSG_H_
