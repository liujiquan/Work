@echo on
:**********************************************************************
:*       create DataBase                 *
:*                                                                    *
:*   DATE   : 2014-06-07                                              *
:**********************************************************************
if "%1" == "" goto error
if "%2" == "" goto error
call crtb DataBase.SQL 	%1 %2 %3 %4

:error
echo **************************************************************************
echo *                                                               	      *
echo *  %1= "ServerName"  %2= "UserName"  %3= "Password"   %4= "DataBase"     *
echo *                                                               	      *
echo **************************************************************************