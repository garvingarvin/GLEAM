/*                                                                                              |
 * University of Minnesota - Twin Cities                                                        |
 * AEM 4490 - Introduction to Aerospace Topics                                                  |
 * GLEAM Project - Ground Unit Reciever: Data Parsing                                           |
 * Author: Joe Poeppel - poepp027@umn.edu                                                       |
 * Date: 2/25/2021                                                                              |                                          
 ----------------------------------------------------------------------------------------------*/

void parseData() {
  
  if(xbeeData.charAt(0) == 'A' && xbeeData.charAt(1) == '1' && UnitA1Bool == false) {
    UnitA1String = xbeeData + spacer;
    UnitA1Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit A1";
  }

  else if(xbeeData.charAt(0) == 'A' && xbeeData.charAt(1) == '2' && UnitA2Bool == false) {
    UnitA2String = xbeeData + spacer;
    UnitA2Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit A2";
  }

  else if(xbeeData.charAt(0) == 'A' && xbeeData.charAt(1) == '3' && UnitA3Bool == false) {
    UnitA3String = xbeeData + spacer;
    UnitA3Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit A3";
  }

  else if(xbeeData.charAt(0) == 'A' && xbeeData.charAt(1) == '4' && UnitA4Bool == false) {
    UnitA4String = xbeeData + spacer;
    UnitA4Bool = true;
   recentUnit = "Data\nreceived\nfrom:\n\nUnit A4";
  }

  else if(xbeeData.charAt(0) == 'A' && xbeeData.charAt(1) == '5' && UnitA5Bool == false) {
    UnitA5String = xbeeData + spacer;
    UnitA5Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit A5";
  }




  else if(xbeeData.charAt(0) == 'B' && xbeeData.charAt(1) == '1' && UnitB1Bool == false) {
    UnitB1String = xbeeData + spacer;
    UnitB1Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit B1";
  }

  else if(xbeeData.charAt(0) == 'B' && xbeeData.charAt(1) == '2' && UnitB2Bool == false) {
    UnitB2String = xbeeData + spacer;
    UnitB2Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit B2";
  }

  else if(xbeeData.charAt(0) == 'B' && xbeeData.charAt(1) == '3' && UnitB3Bool == false) {
    UnitB3String = xbeeData + spacer;
    UnitB3Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit B3";
  }

  else if(xbeeData.charAt(0) == 'B' && xbeeData.charAt(1) == '4' && UnitB4Bool == false) {
    UnitB4String = xbeeData + spacer;
    UnitB4Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit B4";
  }

  else if(xbeeData.charAt(0) == 'B' && xbeeData.charAt(1) == '5' && UnitB5Bool == false) {
    UnitB5String = xbeeData + spacer;
    UnitB5Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit B5";
  }




else if(xbeeData.charAt(0) == 'C' && xbeeData.charAt(1) == '1' && UnitC1Bool == false) {
    UnitC1String = xbeeData + spacer;
    UnitC1Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit C1";
  }

  else if(xbeeData.charAt(0) == 'C' && xbeeData.charAt(1) == '2' && UnitC2Bool == false) {
    UnitC2String = xbeeData + spacer;
    UnitC2Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit C2";
  }

  else if(xbeeData.charAt(0) == 'C' && xbeeData.charAt(1) == '3' && UnitC3Bool == false) {
    UnitC3String = xbeeData + spacer;
    UnitC3Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUni tC3";
  }

  else if(xbeeData.charAt(0) == 'C' && xbeeData.charAt(1) == '4' && UnitC4Bool == false) {
    UnitC4String = xbeeData + spacer;
    UnitC4Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit C4";
  }

  else if(xbeeData.charAt(0) == 'C' && xbeeData.charAt(1) == '5' && UnitC5Bool == false) {
    UnitC5String = xbeeData + spacer;
    UnitC5Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit C5";
  }




   else if(xbeeData.charAt(0) == 'D' && xbeeData.charAt(1) == '1' && UnitD1Bool == false) {
    UnitD1String = xbeeData + spacer;
    UnitD1Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit D1";
  }

  else if(xbeeData.charAt(0) == 'D' && xbeeData.charAt(1) == '2' && UnitD2Bool == false) {
    UnitD2String = xbeeData + spacer;
    UnitD2Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit D2";
  }

  else if(xbeeData.charAt(0) == 'D' && xbeeData.charAt(1) == '3' && UnitD3Bool == false) {
    UnitD3String = xbeeData + spacer;
    UnitD3Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit D3";
  }

  else if(xbeeData.charAt(0) == 'D' && xbeeData.charAt(1) == '4' && UnitD4Bool == false) {
    UnitD4String = xbeeData + spacer;
    UnitD4Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit D4";
  }

  else if(xbeeData.charAt(0) == 'D' && xbeeData.charAt(1) == '5' && UnitD5Bool == false) {
    UnitD5String = xbeeData + spacer;
    UnitD5Bool = true;
    recentUnit = "Data\nreceived\nfrom:\n\nUnit D5";
  }



 
  else if (xbeeData.charAt(0) == 'R' && ReceiverBool == false) { 
    ReceiverBool = true;
    recentUnit ="Data\nreceived\nfrom:\n\nCUT";
    blinkLED(2);
    delay(150);
    }

  else{}
}
