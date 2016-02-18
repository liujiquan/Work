// stdafx.cpp : source file that includes just the standard includes
//	Encrypt.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"



switch(iToday) 		            //iTodayの値によって、パスワードの作成方法を変更
{
    case 1:
        {
            switch(ikeyNumber[i]) 
			{
                case 2:
					cMakeValue = Convert.ToString(ikeyNumber[i] - 1);   break;
				case 3:
					cMakeValue = Convert.ToString(ikeyNumber[i] - 1);   break;
				case 4:
					cMakeValue = Convert.ToString(ikeyNumber[i] - 2);   break;
				case 5:
					cMakeValue = Convert.ToString(ikeyNumber[i] - 2);   break;
				case 6:
					cMakeValue = Convert.ToString(ikeyNumber[i] - 1);   break;
				case 7:
					cMakeValue = Convert.ToString(ikeyNumber[i] - 3);   break;
				case 8:
					cMakeValue = Convert.ToString(ikeyNumber[i] - 5);   break;
				case 9:
					cMakeValue = Convert.ToString(ikeyNumber[i] - 7);   break;
                default:    break;
			}
        }
        break;
	case 2:
    {   
		switch(ikeyNumber[i]) 
        {
            case 2:
				cMakeValue = Convert.ToString(ikeyNumber[i] - 1);   break;
			case 3:
				cMakeValue = Convert.ToString(ikeyNumber[i] - 2);   break;
			case 4:
				cMakeValue = Convert.ToString(ikeyNumber[i] - 1);   break;
			case 5:
				cMakeValue = Convert.ToString(ikeyNumber[i] - 2);   break;
			case 6:
				cMakeValue = Convert.ToString(ikeyNumber[i] - 2);   break;
			case 7:
				cMakeValue = Convert.ToString(ikeyNumber[i] - 1);   break;
			case 8:
				cMakeValue = Convert.ToString(ikeyNumber[i] - 4);   break;
			case 9:
				cMakeValue = Convert.ToString(ikeyNumber[i] - 6);   break;
		default:    break;
			}
        }
        break;
	case 3:
        {
            switch(ikeyNumber[i]) 
			{
			case 2:
				cMakeValue = cABC[ikeyNumber[i] + iDate];   break;
			case 3:
				cMakeValue = cABC[ikeyNumber[i] + iDate * 2];   break;
			case 4:
				cMakeValue = cABC[ikeyNumber[i] + iDate];   break;
			case 5:
				cMakeValue = cABC[ikeyNumber[i] + iDate];   break;
			case 6:
				cMakeValue = cABC[ikeyNumber[i] + iDate];   break;
			case 7:
				cMakeValue = cABC[ikeyNumber[i] + iDate];   break;
			case 8:
				cMakeValue = cABC[ikeyNumber[i] + iDate];   break;
			case 9:
				cMakeValue = cABC[ikeyNumber[i] + iDate * 2];   break;
                default:    break;
			}
        }
        break;
  case 4:
      {
          switch(ikeyNumber[i]) 
			{
			case 2:
				cMakeValue = "T";   break;
			case 3:
				cMakeValue = "B";   break;
			case 4:
				cMakeValue = "O";   break;
			case 5:
				cMakeValue = "D";   break;
			case 6:
				cMakeValue = "E";   break;
			case 7:
				cMakeValue = "G";   break;
			case 8:
				cMakeValue = "S";   break;
			case 9:
				cMakeValue = "Z";   break;
		default:    break;
			}
        }
        break;
	case 5:
		{
            switch(ikeyNumber[i]) 
			{
			case 2:
				cMakeValue = "A";   break;
			case 3:
				cMakeValue = "B";   break;
			case 4:
				cMakeValue = "C";   break;
			case 5:
				cMakeValue = "D";   break;
			case 6:
				cMakeValue = "E";   break;
			case 7:
				cMakeValue = "F";   break;
			case 8:
				cMakeValue = "G";   break;
			case 9:
				cMakeValue = "H";   break;
		default:    break;
			}
        }
        break;
	case 6:
		{
            switch(ikeyNumber[i]) 
			{
			case 2:
				cMakeValue = "L";   break;
			case 3:
				cMakeValue = "R";   break;
			case 4:
				cMakeValue = "M";   break;
			case 5:
				cMakeValue = "Y";   break;
			case 6:
				cMakeValue = "E";   break;
			case 7:
				cMakeValue = "B";   break;
			case 8:
				cMakeValue = "G";   break;
			case 9:
				cMakeValue = "A";   break;
		default:    break;
			}
        }
        break;
	case 7:
		{
            switch(ikeyNumber[i]) 
			{
			case 2:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 3:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 4:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
            case 5:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 6:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 7:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 8:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 9:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
		default:    break;
			}
        }
        break;
	case 8:
		{
            switch(ikeyNumber[i]) 
			{
			case 2:
				cMakeValue = "F";   break;
			case 3:
				cMakeValue = "I";   break;
			case 4:
				cMakeValue = "E";   break;
			case 5:
				cMakeValue = "M";   break;
			case 6:
				cMakeValue = "W";   break;
			case 7:
				cMakeValue = "J";   break;
			case 8:
				cMakeValue = "Q";   break;
			case 9:
				cMakeValue = "P";   break;
		default:    break;
			}
        }
        break;
   default:
       {
           switch(ikeyNumber[i]) 
			{
			case 2:
				cMakeValue = Convert.ToString(2 * ikeyNumber[i] % iDate);   break;
			case 3:
				cMakeValue = Convert.ToString(2 * ikeyNumber[i] % iDate);   break;
			case 4:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 5:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 6:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 7:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 8:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
			case 9:
				cMakeValue = Convert.ToString(ikeyNumber[i] % iDate);   break;
		default:    break;
			}
        }
        break;
}
