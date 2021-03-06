@echo on
:**********************************************************************
:*       カラム定義　バッチファイル         　　　　　　　　　　　    *
:*                                                                    *
:*   DATE   : 2013-04-10   謝険峰                                     *
:*   LastUpdate:                                                      *
:**********************************************************************

     if "%1" == "" goto error
     if "%2" == "" goto error

echo ◆start > sql.log

echo DADAYIDF_COLM.csv >> sql.log
osql -S%1 -U%2 -P%3 -d%4 -Q "delete from DGCLMDEF where TableID = 'DADAYIDF'" -e -p >> sql.log
bcp %4.dbo.DGCLMDEF in DADAYIDF_COLM.csv /c /t , /r \n /S %1 /U %2 /P %3 >> sql.log

echo ◆end >> sql.log
	goto END_PROC
:error
echo ****************************************************************************
echo *                                                               	    	*
echo *  %1= "ServerName"  %2= "UserName"  %3= "Password"  %4= "DataBase"     	*
echo *                                                                       	*
echo ****************************************************************************
:END_PROC
