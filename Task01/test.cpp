//========
//this is template aimed at reading bitfinex prices
//https://api.bitfinex.com/v2/candles/trade:15m:tBTCUSD/hist?limit=5
//example: http://www.cplusplus.com/reference/string/string/substr/

//cd c:\sources\test
//g++ test.cpp -o test.exe
//test.exe

//=============================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream> // needed for conversion of strings to doubles and other types

//looking for workaround:
#include <iterator>
#include <vector>
#include <iomanip> 



using namespace std;

//=============================================
int main () {

//first we need to read a file

string data;

ifstream infile; 
   infile.open("prices.txt"); 
 
   infile >> data; 

   // write the data at the screen.
   cout << data << endl << endl;
   
   infile.close();

//=============================================
//take out initial and final brackets
   size_t pos = data.find("]]");
   data = data.substr (2, pos-2);
   cout << data << endl << endl;
   
//what is remainging length of string data
   size_t postemp = pos-3;

//=============================================
// cut remaining strings into strings of each candle

   string candle [999];
   int i = 0;

   while( data.length() >75) {
      size_t pos = data.find("],[");
      candle[i] = data.substr (0, pos);
      data = data.substr (pos+3 , postemp);
      postemp = postemp - (pos+2); 
      
      cout << candle[i] << endl;
      cout << pos << endl;
      cout << data << endl;
      cout << data.length() << endl;

      ++i;

}

      candle[i] =data;
//=============================================
// only for testing
//    for (int j = 0; j < (i+1) ; j++) {
//       cout << candle[j] << endl;
//}

//=============================================
// what next?
int k;
string candle2 [i+1][6];


//loop to count candles
    int j = 0;
    //cout << i << endl;
    int n = i+1;

    while (j < n ) {
       
       //this one?
       data = candle[j].substr(0);

       //cout << data << endl;

    //internal loop to count commas
         k=0;
         while (k < 5) {
            pos = data.find(",");
            candle2[j][k] = data.substr (0, pos);
            
            //cout <<  candle2[j][k] << endl;
            data = data.substr (pos+1);
            ++k;
     }

       candle2[j][k] = data;
       //cout <<  candle2[j][k] << endl;

       ++j;
}

//=============================================
// only for testing
    for (int j = 0; j < (i+1) ; j++) {
       cout << "candle[" << j << "] is: " << candle2[j][0] << "   " << candle2[j][1] << "   " << candle2[j][2] << "   " << candle2[j][3] << "   " << candle2[j][4] << "   " <<candle2[j][5] << endl;
}

//=============================================
//write to csv
//https://waterprogramming.wordpress.com/2016/08/12/a-quick-example-code-to-write-data-to-a-csv-file-in-c/


//=============================================
   // open a file in write mode.
   ofstream outfile;
   outfile.open("pricedata.csv", ios::trunc);

    
    // write the file headers
   outfile << "Time" << "," << "Open" << ","
           <<  "Close" << "," << "High" << ","
           <<  "Low" << "," << "Volume" << endl;

//convert strings to integers [try1]

       //cout << candle2[i][0] << endl;
   j = i;
   while (j> -1) {
       char myArray[candle2[j][0].size()+1];
       strcpy(myArray, candle2[j][0].c_str());
       char myArray1[candle2[j][1].size()+1];
       strcpy(myArray1, candle2[j][1].c_str());
       char myArray2[candle2[j][2].size()+1];
       strcpy(myArray2, candle2[j][2].c_str());
       char myArray3[candle2[j][3].size()+1];
       strcpy(myArray3, candle2[j][3].c_str());
       char myArray4[candle2[j][4].size()+1];
       strcpy(myArray4, candle2[j][4].c_str());
       char myArray5[candle2[j][5].size()+1];
       strcpy(myArray5, candle2[j][5].c_str());
        outfile << myArray << "," << myArray1 << ","
                <<  myArray2 << "," << myArray3 << "," 
                <<  myArray4 << "," << myArray5 << endl;

       --j;

   }
	 
    
// close the opened file.
   outfile.close();


//=============================================

//g++ test.cpp -o test.exe
//test.exe


   return 0;
}

