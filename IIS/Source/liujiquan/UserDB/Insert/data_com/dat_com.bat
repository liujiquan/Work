@echo on
:**********************************************************************
:*       カラム定義  バッチファイル                                   *
:*                                                                    *
:*   DATE       : 2009-05-14             	                      	  *
:*   LastUpdate : 			                             		 	  *
:**********************************************************************

     if "%1" == "" goto error
     if "%2" == "" goto error

echo ◆start > sql.log

echo DGENGTBL_DAT.csv >> sql.log
bcp  %4.dbo.DGENGTBL in DGENGTBL_DAT.csv /c /t , /r \n /S %1 /U %2 /P %3 >> sql.log

echo DGENGTB2_DAT.csv >> sql.log
bcp  %4.dbo.DGENGTB2 in DGENGTB2_DAT.csv /c /t , /r \n /S %1 /U %2 /P %3 >> sql.log

echo ◆end >> sql.log
    goto END_PROC

:error
echo ****************************************************************************
echo *                                                               	    	*
echo *  %1= "ServerName"  %2= "UserName"  %3= "Password"  %4= "DataBase"        *
echo *                                                               	    	*
echo ****************************************************************************
:END_PROC
