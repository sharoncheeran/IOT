/**
 * File: main.cpp
 * Author: Sharmin Rony and Sharon Cheeran
 * Date: 01/03/2019
 * Desc: Morse Code via Radio Signals
 */
 #include "MicroBit.h"
 #include "stdlib.h"
 #include "string"
 #include "vector"
 #include "map"
 #include "morseCode.h"

 using namespace std;
 int receivedInput[4]; //expecting array of size 4
 vector <char> receive;
 int charCount = 0;
 void printVector();
 morseMapClassTable newMorsecodeTable;
 map<string, char>::iterator morseIterator;
 MicroBit uBit;


 char dot = '.';
 char dash = '-';
 void onButtonA(MicroBitEvent e)
 {
     //gets the digital value and adds the respective char into a vector, which is declared as receive
   ManagedString value = uBit.radio.datagram.recv();
 //Need to turn string value TO INTEGER VALUE
     if (value == 1)
     {
       uBit.display.print('.');
       receive.push_back(dot);
       charCount = charCount + 1;
     }
     if (value == 2)
     {
       uBit.display.print('-');
       receive.push_back(dash);
       charCount = charCount+ 1;
     } //switched from 3 to 4 to allow numbers
     if (charCount > 4) //Morsecode map allows for 5 input items max
     {
       ManagedString answer;
       ManagedString answer2;
       uBit.display.scroll("done");
 	//5 ./- have been input so it's done
       for (int i = 0; i < receive.size(); i++)
       {
         answer = receive[i];
         uBit.display.scroll(answer);
       }
       string morseCode(receive.begin(), receive.end());
       //Convert to string
       for (morseIterator = newMorsecodeTable.tableMorseCode.begin(); morseIterator != newMorsecodeTable.tableMorseCode.end(); morseIterator++)
       {
         if (morseCode == morseIterator->first)
         {
           uBit.display.print(morseIterator->second);
           //Show the corresponding letter from morsecode
         }}}}
   //used for decoding characters with less than 4 symbols
   void onButtonB(MicroBitEvent e)
   {
     ManagedString answer2;
     uBit.display.scroll("output: ");
     //uBit.display.print(charCount);
     for (int i = 0; i < receive.size(); i++)
     {
       answer2 = receive[i];
       uBit.display.scroll(answer2);
     }
     //converts it into a string
     string morseCode(receive.begin(), receive.end());
     for (morseIterator = newMorsecodeTable.tableMorseCode.begin(); morseIterator != newMorsecodeTable.tableMorseCode.end(); morseIterator++)
     {
       if (morseCode == morseIterator->first)
       {
         uBit.display.print(morseIterator->second);
       }}}
 int main()
 {
     uBit.init();
     uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
     uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
     uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onButtonA);
     uBit.radio.enable();

     release_fiber();
 }
