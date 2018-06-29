//=============================================
//cd c:/
//cd c:\sources\test
//g++ test40.cpp -o test40.exe
//test40.exe

//========
//this is last file used for analysis of BTC TD signals
//this file is aimed at learning data manipulation
//this file allows to choose time frame for analysis, look for 'test40'
//####################
//####################
//####################
//####################
//####################
//####################
//####################
//####################

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

#include <stdio.h>  //needed for new examp
#include <string.h> //needed for new examp
#include <stdlib.h>     /* strtof */

#include<algorithm> //needed for min and max functions

#include <ctime> //needed for time calculations

using namespace std;
//================
//declare and define function
//=============================================
//function
string concatenate (string a, string b, string c)
{
  return a+b+c;
}

//=============================================
//function for conversion of candle start number to date
string candledate(long long int time) {
      //==============================
      //we need overloading for array elements
      //operator was not found, workaraund employed
      //==============================


      // 1 Januray 2018 0 hours is 1514764800000
      long long int start = 1514764800000;
      int hours = (time - start) / 3600000;
      int days = hours/ 24; //?this gives month 0?
      hours = hours - (days*24);
      int monthd [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
      int n=0;
      while (days>=0) {
                days = days- monthd[n];
                ++n;
      }
      n-=1;
      days = days + monthd[n] + 1;//+1 because we also have
                                  // hours
      int month = n+1;//+1 because e.g. 5 month is element no.4
      string strmonth = "Month: "+ to_string(month);
      string strdays =", Day: " + to_string(days);
      string strhours = ", Hour: " + to_string(hours);
      string result = concatenate (strmonth,strdays,strhours);

      return result;

}


//================
class Records {
  public:
   long long int  Time;
   double Open;
   double Close;
   double High;
   double Low;
   double Volume;
   int Real;
};

//================
class Profit {
  public:
   long long int  Time;
   string Time2;//month, day, hour
   double Candle;
   double Body;
   double Move;
   double MovExt;
   double CanExt;
   string GR12; //which candle above/below which
   double goLong;
   double goShort;
   double Profit[10];
   double Shareusd[10];//how much is realised at each profit level
   double Profitnet[10];//profit after fees
};

//================
// this is class to read data from csv
class CSVRow
{
    public:
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        std::size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(std::istream& str)
        {
            std::string         line;
            std::getline(str, line);

            std::stringstream   lineStream(line);
            std::string         cell;

            m_data.clear();
            while(std::getline(lineStream, cell, ','))
            {
                m_data.push_back(cell);
            }
            // This checks for a trailing comma with no data after it.
            if (!lineStream && cell.empty())
            {
                // If there was a trailing comma then add an empty element.
                m_data.push_back("");
            }
        }
    private:
        std::vector<std::string>    m_data;
};

//=============================================
//extraction operator (>>) applied to an input stream
//Overloading the >> Operator for Your Own Classes
// str is input stream object from which characters are extracted 
// data is object where the extracted character is stored
//=============================================
std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}   

//=============================================

//=============================================

//=============================================
int main () {

//=============================================

//=============================================

//=============================================
//THIS BLOCK IS FOR INPUTING CANDLE DATA FROM CSV

//declare class
Records Candle[20000];
//declare class
CSVRow row;

//take data from csv

std::ifstream bigfile("bigdata.csv");

//cout titles
bigfile >> row;
cout << "TITLES" << endl;
cout << row[0] << "   " <<  row[1] << "   " << row[2]<< "   " << row[3]<< "   " << row[4]<< "   " << row[5]<<  "   " << row[6]<< endl;


int i=0;//loop?

    while(bigfile >> row) //while file has and returns a row???
    {

     //Converting Strings and specifying Candle[i]
       stringstream geek(row[0]);
       geek >> Candle[i].Time;
       //Candle[i].Time=row[0];
       
     //looking, how to read Time
//??? https://stackoverflow.com/questions/11052685/reading-csv-scientific-notation
       //char myArray[row[0].size()+1];
       //strcpy(myArray, row[0].c_str());
       //Candle[i].Time = strtof (myArray, NULL);
       
       stringstream geek1(row[1]);
       geek1 >> Candle[i].Open;
       stringstream geek2(row[2]);
       geek2 >> Candle[i].Close;
       stringstream geek3(row[3]);
       geek3 >> Candle[i].High;
       stringstream geek4(row[4]);
       geek4 >> Candle[i].Low;

       stringstream geek5(row[5]);
       geek5 >> Candle[i].Volume;
       
       //workarround below throws some error, maybe string too long?
       //double test = stod (row[5]);
       //Candle[i].Volume = test;


       stringstream geek6(row[6]);
       geek6 >> Candle[i].Real;


        i=i+1;

    }

//=============================================
//check if sucess

//test is printing last 4 min15 candles: j=i-4
int j=i-4; //last member is i-1, but number of candles is
           //1+(i-1)=i, i.e. [0,...,i]


cout << "This is test (4 last 15min candles): " << endl;


long long int testnum = Candle[j-1].Time ;
int k=0;
while (k <4) {

cout << Candle[j].Time << "   " << Candle[j].Open << "   " 
     << Candle[j].Close << "   " << Candle[j].High << "   " 
     << Candle[j].Low << "   " << Candle[j].Volume  << "   " 
     << Candle[j].Real << endl;
     //test
     //cout << Candle[j].Time- Candle[j-1].Time<<endl;
     ++j;
     ++k;
}

//=============================================

//=============================================

//=============================================
//let's create 4H candles or other time frame candles
//test40 changes here. change all num4h to numth
//change all Candle4h to Candleth
//change all 16 to ttt, input at the momemt ttt by hand
//change all 15 to (ttt-1)

int ttt=12; //currently we are analysing 3H candles, which is 12 min15 candles
//there are i objects in class Candle[] with last candle[i-1]
int numth = (i)/ttt;//number of 4h candles (or ttt framework candles)
                  //digits after dot will be removed

Records Candleth[numth+1];//not working having declared 20000
                     //1 additional candle is ongoing

//length of ongoing candles in terms of number of 15m candles
int rem15m = (i)- (numth)*ttt;

//=============================================
//couting for test
cout << "there are 15m candles: "<< i << endl;
cout << "there are 4h candles: "<< numth << endl;
cout << "remaining 15m candles: "<<rem15m << endl;
//=============================================

k=0;//was declared before
int k1=0;
int hight=ttt;//16 candles or less in case of ongoing 4H candle
//=============================================
while (k<(numth+1)) {        //has to be while (k<(num4h+1)) 

      if (k==numth) {  //do we have last ongoing candle?
              hight =rem15m;
      }

      Candleth[k].Time=Candle[k1].Time;
      Candleth[k].Open =Candle[k1].Open ;
      Candleth[k].Close =Candle[k1+(hight-1)].Close ;
      Candleth[k].Real =Candle[k1].Real ;//workaraund, as Real
                                        //is not important now

      double temph=Candle[k1].High;
      int kk=k1+1;
      while (kk<(k1+hight)) {
          if (temph < Candle[kk].High) {
              temph = Candle[kk].High;
          } 
          ++kk;
      }
      Candleth[k].High = temph;

      double templ=Candle[k1].Low;
      kk=k1+1;
      while (kk<(k1+hight)) {
          if (templ > Candle[kk].Low) {
              templ = Candle[kk].Low;
          } 
          ++kk;
      }
      Candleth[k].Low = templ;

      double tempv=Candle[k1].Volume;
      kk=k1+1;
      while (kk<(k1+hight)) {
          tempv+=Candle[kk].Volume;
          ++kk;
      }
      Candleth[k].Volume = tempv;

k1+=hight;
k+=1;
}


//=============================
//cout only for testing
k-=1;
cout << "Last 4H candle (most likely ongoing)" << endl;
cout <<Candleth[k].Time << "   " << Candleth[k].Open << "   " 
     <<Candleth[k].Close << "   " << Candleth[k].High << "   " 
     <<Candleth[k].Low << "   " << Candleth[k].Volume  <<"   " 
     <<Candleth[k].Real << endl;

//=============================================

//=============================================

//=============================================
//now we have 4h candles specified, let's give them TD number
// first candles are G4, G5, R1, R2

int TD[numth+1];//indluding 1 ongoing, from 0 to num4h


/*this was for 4h candles
TD[0]=4; //green4
TD[1]=5;
TD[2]=-1;//red1
TD[3]=-2; */

//introduce now manually 3 H candles
TD[0]=6; //green4
TD[1]=-1;
TD[2]=-2;//red1
TD[3]=-3;


int direction = -1; //1, if up
int direction1;
k=4;

//=============================
//print to test
//cout << "No." << "    " << "Start time of candle" << "    " << "Green(>0)/Red(<0)" << endl;
//j=1;//was declared
//while (j<5) {      
// cout << j << "    " <<Candle4h[j].Time << "    " << TD[j] << endl;
//++j;
//}

// open a file in write mode.
ofstream outfile;
outfile.open("TDnumbers.csv", ios::trunc);
//outfile headings
outfile << "No." << "," << "Start time of candle" << "," << "Month"<< "," << "Day"<< "," << "Hour"<< "," << "Green(>0)/Red(<0)" << endl;
//outfile first 4 candles for which TD is inputed
j=0;//was declared
while (j<4) {   
     string tempdate = candledate(Candleth[j].Time);
      outfile << j << ","<<Candleth[j].Time << ","<< tempdate<<"," << TD[j] << endl;
++j;
}

//=============================

while (k<(numth+1)) {           //has to be while (k<num4h) 
   //check direction (up or down)
   //=============================
   double dif = Candleth[k].Close - Candleth[k-4].Close; //can 
                                  //not put into if statement?
   int last=TD[k-1];
   //===============================
   if(direction>0){
       if(dif>0) {
           if(last>0) {
                    TD[k]=TD[k-1]+1;
                    direction1 = 1; //still up
           }
        }
    }
   //=============================
   if(direction>0){
       if(dif>0) {
           if(last==0) {//in conditions it is ==, not =!!!!
                    TD[k]=0;
                    direction1 = 1; //still up
           }
        }
    }
   //=============================
   if(direction>0){
       if(dif>0) {
           if(last==9) {
                    TD[k]=0;
                    direction1 = 1; //still up
           }
       }
    }
   //=============================
   if(direction>0){
       if(dif<0) {
                    TD[k]= -1;
                    direction1 = -1; //now down
        }
    }
   //=============================
   //=============================

   if(direction < 0){
       if(dif<0) {
           if(last< 0) {
                    TD[k]=TD[k-1]-1;
                    direction1 = -1; //still down
           }
        }
    }
   //=============================
   // this one deletes
   if(direction<0){
       if(dif<0) {
           if(last==0) { //in conditions it is ==, not =!!!!
                    TD[k]=0;
                    direction1 = -1; //still down
           }
        }
    }
   //=============================
   if(direction<0){
       if(dif<0) {
           if(last== -9) {
                    TD[k]=0;
                    direction1 = -1; //still down
           }
        }
    }
   //=============================
   if(direction<0){
       if(dif>0) {
                    TD[k]=1;
                    direction1 = 1; //now up
        }
    }


//=====================================
//test TD :
//cout << k << "    " <<Candle4h[k].Time << "    " << TD[k] << endl;

string tempdate = candledate(Candleth[k].Time);
outfile << k << "," <<Candleth[k].Time <<","<< tempdate <<","<< TD[k] << endl;



//================================
direction=direction1;
++k;
} //end of while
k-=1; //the real k

//=============================================
// close the opened file.
   outfile.close();

//=============================================
//#############################################
//=============================================
//
//identify trading signals G2>G1 and R2<R1
//
//#############################################
//=============================================

string GR12[numth+1];//plus 1 ongoing
int Real[numth+1];//plus 1 ongoing

k=3; //because we cannot check next position comparing to
     //4 candles back
//=============================================
//TEST ONLY
cout << "This is test of 1->2 trading signals identification..."<< endl;
// open a file in write mode.
//ofstream outfile;//don't need to rediclare?
outfile.open("GR12signals.csv", ios::trunc);
outfile << "TD number" << "," << "Start time of candle" << "," << "Month"<< "," << "Day"<< "," << "Hour"<< "," << "Signal" << "," << "Is signal TRUE" << endl;

//=============================================
while (k<(numth)) {           //has to be while (k<numth) 
            //it is not possible to check having 1 at the end
   //=============================
   //check if k candle is G1 which was surpassed by G2 (which
   //was G2 at the moment of suprassing), and whether surpass
   //was at least of 3 USD 
   //=============================

   int current=TD[k];

   int next=TD[k+1];

   //we also need close of next-4 candle
   double curhigh = Candleth[k].High;
   double curlow = Candleth[k].Low;

   double back3close = Candleth[k-3].Close;
   double nexthigh = Candleth[k+1].High;
   double nextlow = Candleth[k+1].Low;

   double breakpoint = curhigh+3.0;
   double downpoint = curlow-3.0;

int next2=0;//says that there is no need to check G2G3...
   //===============================
   
//are we analysing G1 now? (if not, go to next candle
if(current==1){ //don't forget that here we use ==

    //could next be G2 at surpassing point?
    if(back3close<curhigh) {

         //has next surpassed G1?
         if(nexthigh > breakpoint) {
              Real[k]=1; //there was real (not fake) signal
              
              //Has G2 after surpassing remained G2
              if(next==2) {GR12[k]="G1G2";}
              if(next==-1) {GR12[k]="G1G2R1";}
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================

         } else { // we have no "nexthigh > breakpoint"
              if(next==2) {
                  Real[k]=0;GR12[k]="G1G2";next2=1;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
              }//close if
           }//close else
     } else { //we have no "back3close<curhigh"
          if(next==2){
               Real[k]=0;GR12[k]="G1G2";next2=1;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
          }//end if
       }//end else
}//end first if

//=============================================
//having G1G2 and fake signal, go to G3>G2 and so on
//=============================================
//check if we have a candle after candle to be analysed
if(next2==1){ //don't forget that here we use ==
  ++k; 
  if (k<(numth)) {
        next2=1;
  } else {next2=0;--k;}
}
//=============================================
if(next2==1){ 
   current=TD[k];
   next=TD[k+1];
   curhigh = Candleth[k].High;
   back3close = Candleth[k-3].Close;
   nexthigh = Candleth[k+1].High;
   breakpoint = curhigh+3.0;

//are we analysing G2 now? next=1 says so. check if needed

    //could next be G3 at surpassing point?
    if(back3close<curhigh) {

         //has next surpassed G2?
         if(nexthigh > breakpoint) {
              Real[k]=1; //there was real (not fake) signal
              
              //Has G3 after surpassing remained G3
              if(next==3) {GR12[k]="G2G3";}
              if(next==-1) {GR12[k]="G2G3R1";}
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================

         } else { // we have no "nexthigh > breakpoint"
              if(next==3) {
                  Real[k]=0;GR12[k]="G2G3";next2=2;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
              }//close if
           }//close else
     } else { //we have no "back3close<curhigh"
          if(next==3){
               Real[k]=0;GR12[k]="G2G3";next2=2;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
          }//end if
       }//end else
}//end first if

//=============================================
//having G2G3 and fake signal, go to G4>G3
//=============================================
//check if we have a candle after candle to be analysed
if(next2==2){ //don't forget that here we use ==
  ++k; 
  if (k<(numth)) {
        next2=2;
  } else {next2=0;--k;}
}
//=============================================
if(next2==2){ 
   current=TD[k];
   next=TD[k+1];
   curhigh = Candleth[k].High;
   back3close = Candleth[k-3].Close;
   nexthigh = Candleth[k+1].High;
   breakpoint = curhigh+3.0;

//are we analysing G3 now? next=2 says so. check if needed

    //could next be G4 at surpassing point?
    if(back3close<curhigh) {

         //has next surpassed G3?
         if(nexthigh > breakpoint) {
              Real[k]=1; //there was real (not fake) signal
              
              //Has G4 after surpassing remained G4
              if(next==4) {GR12[k]="G3G4";}
              if(next==-1) {GR12[k]="G3G4R1";}
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================

         } else { // we have no "nexthigh > breakpoint"
              if(next==4) {
                  Real[k]=0;GR12[k]="G3G4";next2=3;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
              }//close if
           }//close else
     } else { //we have no "back3close<curhigh"
          if(next==4){
               Real[k]=0;GR12[k]="G3G4";next2=3;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
          }//end if
       }//end else
}//end first if

//=============================================
//having G3G4 and fake signal, go to G5>G4
//=============================================
//check if we have a candle after candle to be analysed
if(next2==3){ //don't forget that here we use ==
  ++k; 
  if (k<(numth)) {
        next2=3;
  } else {next2=0;--k;}
}
//=============================================
if(next2==3){ 
   current=TD[k];
   next=TD[k+1];
   curhigh = Candleth[k].High;
   back3close = Candleth[k-3].Close;
   nexthigh = Candleth[k+1].High;
   breakpoint = curhigh+3.0;

//are we analysing G4 now? next=3 says so. check if needed

    //could next be G5 at surpassing point?
    if(back3close<curhigh) {

         //has next surpassed G4?
         if(nexthigh > breakpoint) {
              Real[k]=1; //there was real (not fake) signal
              
              //Has G5 after surpassing remained G5
              if(next==5) {GR12[k]="G4G5";}
              if(next==-1) {GR12[k]="G4G5R1";}
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================

         } else { // we have no "nexthigh > breakpoint"
              if(next==5) {
                  Real[k]=0;GR12[k]="G4G5";next2=4;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
              }//close if
           }//close else
     } else { //we have no "back3close<curhigh"
          if(next==5){
               Real[k]=0;GR12[k]="G4G5";next2=4;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
          }//end if
       }//end else
}//end first if

//=============================================
//don't gonna check G6>G5, return next to 0
//=============================================
next2 = 0;


//=============================================
//#############################################
//the same for red
//#############################################
//=============================================

//are we analysing R1 now? (if not, go to next candle
if(current==-1){ //don't forget that here we use ==

    //could next be R2 at breakdown point?
    if(back3close>curlow) {

         //has next surpassed G1?
         if(nextlow < downpoint) {
              Real[k]=1; //there was real (not fake) signal
              
              //Has R2 after breaking down remained R2
              if(next==-2) {GR12[k]="R1R2";}
              if(next==1) {GR12[k]="R1R2G1";}
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================

         } else { // we have no "nextlow < downpoint"
              if(next==-2) {
                  Real[k]=0;GR12[k]="R1R2";next2=1;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
              }//close if
           }//close else
     } else { //we have no "back3close>curlow"
          if(next==-2){
               Real[k]=0;GR12[k]="R1R2";next2=1;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
          }//end if
       }//end else
}//end first if

//=============================================
//having R1R2 and fake signal, go to R3<R2 and so on
//=============================================
//check if we have a candle after candle to be analysed
if(next2==1){ //don't forget that here we use ==
  ++k; 
  if (k<(numth)) {
        next2=1;
  } else {next2=0;--k;}
}
//=============================================
if(next2==1){ 
   current=TD[k];
   next=TD[k+1];
   curlow = Candleth[k].Low;
   back3close = Candleth[k-3].Close;
   nextlow = Candleth[k+1].Low;
   downpoint = curlow-3.0;

//are we analysing R2 now? next=1 says so. check if needed

    //could next be R3 at breakdown point?
    if(back3close>curlow) {

         //has next went below R2?
         if(nextlow < downpoint) {
              Real[k]=1; //there was real (not fake) signal
              
              //Has R3 after breaking down remained R3
              if(next==-3) {GR12[k]="R2R3";}
              if(next==1) {GR12[k]="R2R3G1";}
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================

         } else { // we have no "nextlow < downpoint"
              if(next==-3) {
                  Real[k]=0;GR12[k]="R2R3";next2=2;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
              }//close if
           }//close else
     } else { //we have no "back3close>curlow"
          if(next==-3){
               Real[k]=0;GR12[k]="R2R3";next2=2;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
          }//end if
       }//end else
}//end first if

//=============================================
//having R2R3 and fake signal, go to R4<R3
//=============================================
//check if we have a candle after candle to be analysed
if(next2==2){ //don't forget that here we use ==
  ++k; 
  if (k<(numth)) {
        next2=2;
  } else {next2=0;--k;}
}
//=============================================
if(next2==2){ 
   current=TD[k];
   next=TD[k+1];
   curlow = Candleth[k].Low;
   back3close = Candleth[k-3].Close;
   nextlow = Candleth[k+1].Low;
   downpoint = curlow-3.0;

//are we analysing R3 now? next=2 says so. check if needed

    //could next be R4 at breaking down point?
    if(back3close>curlow) {

         //has next went below R3?
         if(nextlow < downpoint) {
              Real[k]=1; //there was real (not fake) signal
              
              //Has R4 after breaking down remained R4
              if(next==-4) {GR12[k]="R3R4";}
              if(next==1) {GR12[k]="R3R4G1";}
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================

         } else { // we have no "extlow < downpoint"
              if(next==-4) {
                  Real[k]=0;GR12[k]="R3R4";next2=3;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
              }//close if
           }//close else
     } else { //we have no "ack3close>curlow"
          if(next==-4){
               Real[k]=0;GR12[k]="R3R4";next2=3;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
          }//end if
       }//end else
}//end first if

//=============================================
//having R3R4 and fake signal, go to R5<R4
//=============================================
//check if we have a candle after candle to be analysed
if(next2==3){ //don't forget that here we use ==
  ++k; 
  if (k<(numth)) {
        next2=3;
  } else {next2=0;--k;}
}
//=============================================
if(next2==3){ 
   current=TD[k];
   next=TD[k+1];
   curlow = Candleth[k].Low;
   back3close = Candleth[k-3].Close;
   nextlow = Candleth[k+1].Low;
   downpoint = curlow-3.0;

//are we analysing R4 now? next=3 says so. check if needed

    //could next be R5 at breakdown point?
    if(back3close>curlow) {

         //has next went below R4?
         if(nextlow < downpoint) {
              Real[k]=1; //there was real (not fake) signal
              
              //Has R5 after breaking down remained R5
              if(next==-5) {GR12[k]="R4R5";}
              if(next==1) {GR12[k]="R4R5G1";}
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================

         } else { // we have no "nextlow < downpoint"
              if(next==-5) {
                  Real[k]=0;GR12[k]="R4R5";next2=4;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
              }//close if
           }//close else
     } else { //we have no "back3close>curlow"
          if(next==-5){
               Real[k]=0;GR12[k]="R4R5";next2=4;
        //=============================================
        outfile << TD[k]  << "," <<Candleth[k].Time << ","<< candledate(Candleth[k].Time)<<","<< GR12[k]<<","<<Real[k]<<endl;
        //=============================================
          }//end if
       }//end else
}//end first if

//=============================================
//don't gonna check R6<R5
//=============================================

//=============================================
//=============================================
++k;
} //end of while

// close the opened file.
   outfile.close();


//=============================================
//#############################################
//=============================================
//#############################################
//=============================================
//NEXT we have to check whether signals correspond to graphical charts ==>> correspond with 95% probability

//=============================================
//#############################################
//#############################################
//#############################################
//#############################################
//#############################################
//=============================================
//currently amount of position is defined below:

double possize=9000.0;
double crypto;

//#############################################
//#############################################

//input profit taking and stop loss levels

CSVRow row2;
double proflev[10];
double share[10];
double stop[10];

//take data from csv

std::ifstream levelfile("inputlevels.csv");

//cout titles
levelfile >> row2;
cout << "Testing input of profit and stop levels" << endl;
cout << "TITLES" << endl;
cout << row2[0] << "   " <<  row2[1] << "   " << row2[2]<< endl;


i=0;//loop?

    while(levelfile >> row2) //while file has and returns a level???
    {

     //Converting Strings and specifying Candle[i]
       stringstream geek(row2[0]);
       geek >> proflev[i];
       stringstream geek1(row2[1]);
       geek1 >> share[i];
       stringstream geek2(row2[2]);
       geek2 >> stop[i];
//=============================================
//test
cout << proflev[i]<< "   " << share[i]<< "   " 
     << stop[i]<< endl;

//=============================================
       ++i;

    }
//number of profit levels is from 0 to i:
--i;//remove excessive level

//=============================================
//#############################################
//=============================================
//check whether profit was achieved before trigerring stop loss levels 

//we need to have a list of candles analysed

//for test purposes input first signal

//GR12signals.csv
//rows 2 (long) and row 3 (short)

//TD number	Start time of candle	Month	Day	Hour	Signal	Is signal TRUE

//declare variables:
//=============================================
//no, the only one is missing is to put Candle4h[k].Time 
//into some Time[k]. then no repeated csv reading is needed
//=============================================

int Real2;//temp, for testing only

Profit profit[999]; //declare object of class Profit




//take data from csv

std::ifstream signalfile("GR12signals.csv");

int m=0;//this is no. of evaluated trade

//cout titles
signalfile >> row2;


//##############################################
//=============================================
//##############################################
//=============================================
//##############################################
//=============================================
//number of 15min candles is rem15m + (num4h)*16;
int stop15=rem15m +(numth)*ttt;
stop15-=1;//as first candle is no.0;


//=============================================
// write titles to the file
//open a file in write mode.
//ofstream outfile;//don't need to redeclare?
outfile.open("GR12profit.csv", ios::trunc);
outfile << "Time[m]" <<","<< "Month"<< "," << "Day"<< "," << "Hour"<<","<<"GR122[m]"<< ","<<"Real2[m]"<<","<<"Body"<<","<<"Move"<<","<<"Candle"<<","<<"MovExt"<<","<<"CanExt"<< ","<<"go long/SHORT"<< ","<<"Profit1"<< ","<<"Profit2"<< ","<<"Profit3"<< ","<<"Profit4"<<","<<"Profit5"<<","<<
"Profitnet1"<< ","<<"Profitnet2"<< ","<<"Profitnet3"<< ","<<"Profitnet4"<<","<<"Profitnet5"<<","<<"Tot.profit"<<","<<"Fees1"<<","<<"Fees2"<<","<<"Fees3"<<","<<"Fees4"<<","<<"Fees5"<<endl;

//=============================================




while (signalfile >> row2) {

//=============================================
//check if real (if not, go to next line)
stringstream geek2(row2[6]);
geek2 >> Real2;



//#############################################
//#############################################
//#############################################

if (Real2==1) {//execute the loop and record data to profit[m]
//=============================================
//##############################################
//=============================================

int TD;
stringstream geek2(row2[0]);
geek2 >> TD;


//#############################################
//#############################################
//#############################################
//=============================================
//long position will be tested
//=============================================
//#############################################
//#############################################
//#############################################



if (TD>0) { //execute only long signal
   
     stringstream geek(row2[1]);
     geek >> profit[m].Time;
     profit[m].GR12= row2[5];
     profit[m].Time2=candledate(profit[m].Time);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//     still need to specify:
//     profit[m].double Candle
//     profit[m].double Body
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//=============================================
//find candle in 15min candle class

int n=0;
while(profit[m].Time > Candle[n].Time ) 
    {
       ++n;
    }
//now we should have n

//=============================================
//find max of 1st candle
//calculate candle hight including shadows

profit[m].goLong=Candle[n].High; 
double low2=Candle[n].Low; 
profit[m].Body = Candle[n+(ttt-1)].Close-Candle[n].Open;

for (int i=(n+1); i<(n+ttt);++i) {
    if (Candle[i].High>profit[m].goLong) {
          profit[m].goLong=Candle[i].High;
    }//end of if
    if (Candle[i].Low<low2) {
          low2=Candle[i].Low;
    }//end of if
}

profit[m].Move = profit[m].goLong-Candle[n].Open;
profit[m].Candle = profit[m].goLong-low2;
profit[m].MovExt =  100 * (profit[m].Move / Candle[n].Open);
profit[m].CanExt =  100 * (profit[m].Candle / Candle[n].Open);


//1st candle is 1514865600000
profit[m].goLong+=3; // go long if candle 2 overcomes candle 1 by 3 USD

//=============================================
//find long signal. we know that candle 2 went above by >3 usd
int startlong; //number of candle in 15min class
for (int i=(n+ttt); i<(n+32);++i) {
    if (Candle[i].High>=profit[m].goLong) {startlong=i;break;}
}
//cout<<"startlong is: "<<startlong<<endl; //should be 128

//=============================================
//number of profit levels is from 0 to i (=i+1)
int ii=0;//number of levels of profits
double profitusd[i+1];
double stopusd[i+1];
double lag=7.0; // lag of price at execution of stop
//=============================================
//
//=============================================
   int nn= startlong;//
				//test: nn=128|

//=============================================
//###########################################
//=============================================
int catch1 =0;//to cathch whether stop loss was trigerred
int catch2[10];//only for debuging
double tempprofit;//to compare whether profit is stop loss 
int nn2[10];
int nn3[10];//for testing only

while (ii<(i+1)) { //loop for profit levels
				//test: ii=0|ii=1|ii=2|
//=============================================
				//test: nn=128|nn=132|132|

//=============================================
   if(ii==0) { 
                                     //test: ii=0|ii=1|ii=2|

       profit[m].Profit[ii]= - stop[ii] - 2 * lag -3;//let be 
                                     //equal
                                      //to max loss    
       stopusd[ii]=profit[m].goLong - 3 - stop[ii];}//compare 
                            //to ??? 
//=============================================
   else{
       profit[m].Profit[ii]= proflev[ii-1]- stop[ii] - 2* lag - 3;//let be equal to??

       stopusd[ii]=profitusd[ii-1] - stop[ii];}//compare to 
                                     //last taken profit
//=============================================
       profitusd[ii]=profit[m].goLong  - 3 +proflev[ii];//ok
       tempprofit=profit[m].Profit[ii];
    //=============================================
    //check whether stop loss was trigerred at previous level
       if (catch1==1) {
                         //test: catch1=0|catch=0|
            profit[m].Profit[ii]=profit[m].Profit[ii-1];
       } else {//look for profit taken in this level
    //=============================================
    //let's test whether stop loss was realised
    //=============================================


//=============================================
//=============================================
       while(Candle[nn].Low>stopusd[ii]) { //stoploss??
//=============================================
//=============================================

             if(Candle[nn].High>profitusd[ii]) {

                  profit[m].Profit[ii]=proflev[ii]-3-lag;//m 
                                       //is number of trade
                  nn2[ii]=nn;//to check if several profit
                         // levels 
                         //are reached at the same candle 
                  //cout<<nn2[ii]<<endl;
                               //test: nn2=132|132|does't catch

                               //test: nn=132|132|does't catch

                  break; // exit loop upon profit taking
    //=============================================
             }//end of if
//=============================================
//This is start of BREAK LOOP EFFECT

             ++nn;
//=============================================
             //stop if no candles are remaining
             if (nn>stop15) {break;}
//=============================================


    } //end loop for testing realisation of stop loss at 
         //certain level
//=============================================
//This is end of BREAK LOOP EFFECT

                           //test: nn=133|133|

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                               //if the same candle was checked as in previous level
//and now fail was cathched on this candle, there
//will be no n++





} // end of else (in case stop loss was not trigerred
        //in previous level










//test
nn3[ii]=nn;

//=============================================
if (tempprofit==profit[m].Profit[ii]) {
     catch1=1;
                 //test:catch1=0|0|
//=============================================
//workarounds to cach marginal case
//########################
//WORKARAUND NO.1
//########################
    //if this nn gave long signal, check whether Low is not the opening of the candle
    //candles ii>0 will with raised stop loss will be checked under next workarround
     if(nn==startlong) { 
//=============================================
       if (ii==0){
          if (Candle[nn].High<profitusd[ii]) {
             if (Candle[nn].Close>stopusd[ii]) {
                 cout<<"marginal case no.1.1: "<<nn<<endl;
                 --ii;
                 ++nn; //you should put it back into nn loop
                 catch1=0;
             }
           } else {
               cout<<"marginal case no.1.2: "<<nn<<endl;
               profit[m].Profit[ii]=proflev[ii]-3-lag;
               nn2[ii]=nn;//to check if several profit
                         // levels 
               catch1=0;
          } //end of else
       }
     }//end of workaround external if
//=============================================
//########################
//WORKARAUND NO.2
//########################
//if stop loss was recorded, check whether previous profit taking level was reached at the same candle, and if yes, check whether current level is reached ignoring stop loss (whis is raised with level)
//this should also work for startlong candle ii>0 levels, which "failed" due to increase in stop loss
//something like 
      int case2=0;
      if(ii>0) {     
         if (nn==nn2[ii-1]) {//
             if (Candle[nn].High>profitusd[ii]) {
                 cout<<"marginal case no.2: "<<nn<<endl;
                 profit[m].Profit[ii]=proflev[ii]-3-lag;
                 nn2[ii]=nn;//to check if several profit
                         // levels 
                 catch1=0;
                 case2=2;
           //=============================================
           //however, if previous level was reached on this candle, compare to close of the candle
                  } else {
                           if (Candle[nn].Close>stopusd[ii]) {
                                cout<<"marginal case no.2.2: "<<nn<<endl;
                                ++nn;//return to loop
                                --ii;//return to loop
                                catch1=0;
                           }
                     }//end of else
           //=============================================
         }
      }
//########################
//WORKARAUND NO.3
//########################
//if stop loss was recorded, check whether profit level was reached at high before closing the candle
//it is assumed that (achieve-open)>(open-low) gives highest probability to achieve level before stop loss
//something like 
      if (case2 == 0){
          if (nn!=startlong) { 
              if (Candle[nn].High>profitusd[ii]) {
                  if ((profitusd[ii]- Candle[nn].Open) 
                     < (Candle[nn].Open - Candle[nn].Low)) {
                     cout<<"marginal case no.3: "<<nn<<endl;
                     profit[m].Profit[ii]=proflev[ii]-3-lag;
                     //don't add nn, maybe next pofit can be taken 
                     //on this nn
                     catch1=0;
                   }
               }
           }
      }
//=============================================
}
catch2[ii]=catch1;

//=============================================

//=============================================
    ++ii;//go to next profit level
					 //test: ii=1|
//=============================================
}//end of loop for profit levels

//=============================================
//cout for testing


//###################################
//###################################
//###################################
//we have to calculate profit of each level in usd

crypto=possize/profit[m].goLong;
possize = crypto * (profit[m].goLong + lag);


int nnn=0;
double buyprice = profit[m].goLong + lag;
double buyamount;
double sellprice;
double Fees[10];
//============================================
while (nnn<ii) {
     profit[m].Shareusd[nnn]=possize * share[nnn];

     buyamount = profit[m].Shareusd[nnn] / buyprice;
     profit[m].Profitnet[nnn] = profit[m].Shareusd[nnn] * (profit[m].Profit[nnn] / (profit[m].goLong + lag));
     sellprice = profit[m].goLong + lag + profit[m].Profit[nnn];

     //have to deduct trading and funding fees
     //stop trading fees are 0.002 (0.2%) 
     //limit trading fees are 0.001 (0.1%) 
     //let's assume we are borrowing 2/3 of position amount with 0.0007 (0.07%) daily interest rate, and only for one day

     //fees in case position share closed as limit
     if (catch2[nnn]==0) {
          profit[m].Profitnet[nnn] = profit[m].Profitnet[nnn] - buyamount * buyprice *(0.002 + 0.0007 *(2/3)) - buyamount * sellprice *0.001;
          Fees[nnn]= - buyamount * buyprice *(0.002 + 0.0007 *(2/3)) - buyamount * sellprice *0.001;
     } else {
     //fees in case position share closed as stop loss
          profit[m].Profitnet[nnn] = profit[m].Profitnet[nnn] - buyamount * buyprice *(0.002 + 0.0007 *(2/3)) - buyamount * sellprice *0.002;
          Fees[nnn]= - buyamount * buyprice *(0.002 + 0.0007 *(2/3)) - buyamount * sellprice *0.002;
       } // end of else
//============================================
++nnn;
} // end of while
//###################################
//###################################
//###################################

outfile << profit[m].Time<< ","<<candledate(profit[m].Time)<<","<<profit[m].GR12<< ","<<Real2<< ","<<profit[m].Body<<","<<profit[m].Move<<","<<profit[m].Candle<<","<<profit[m].MovExt<<","<<profit[m].CanExt<<","<<profit[m].goLong<< ","<<profit[m].Profit[0]<< ","<<profit[m].Profit[1]<< ","<<profit[m].Profit[2]<< ","<<profit[m].Profit[3]<<","<<profit[m].Profit[4]<<","<<profit[m].Profitnet[0]<< ","<<profit[m].Profitnet[1]<< ","<<profit[m].Profitnet[2]<< ","<<profit[m].Profitnet[3]<<","<<profit[m].Profitnet[4]<<"," <<profit[m].Profitnet[0]+ profit[m].Profitnet[1]+profit[m].Profitnet[2]+profit[m].Profitnet[3]+profit[m].Profitnet[4]<<","<<Fees[ii-5]<<","<<Fees[ii-4]<<","<<Fees[ii-3]<<","<<Fees[ii-2]<<","<<Fees[ii-1]<<endl;


//=============================================


}//end of if (to check whether long signal)


//#############################################
//#############################################
//#############################################
//=============================================
//SHORT position will be tested
//=============================================
//#############################################
//#############################################
//#############################################



if (TD<0) { //execute only SHORT signal
   
     stringstream geek(row2[1]);
     geek >> profit[m].Time;
     profit[m].GR12= row2[5];
     profit[m].Time2=candledate(profit[m].Time);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//     still need to specify:
//     profit[m].double Candle
//     profit[m].double Body
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//=============================================
//find candle in 15min candle class

int n=0;
while(profit[m].Time > Candle[n].Time ) 
    {
       ++n;
    }
//now we should have n

//=============================================
//find MIN of 1st candle
//calculate candle hight including shadows

profit[m].goShort=Candle[n].Low; 

double high2=Candle[n].High; 
profit[m].Body = Candle[n].Open - Candle[n+(ttt-1)].Close;

for (int i=(n+1); i<(n+ttt);++i) {
    if (Candle[i].Low<profit[m].goShort) {
          profit[m].goShort=Candle[i].Low;
    }//end of if
    if (Candle[i].High>high2) {
          high2=Candle[i].High;
    }//end of if
}

profit[m].Move = Candle[n].Open - profit[m].goShort;
profit[m].Candle = high2 - profit[m].goShort;
profit[m].MovExt =  100 * (profit[m].Move / Candle[n].Open);
profit[m].CanExt =  100 * (profit[m].Candle / Candle[n].Open);





//1st candle is ???
profit[m].goShort-=3; // go SHORT if candle 2 gets below candle 1 by 3 USD

//=============================================
//find SHORT signal. we know that candle 2 went below by >3 usd
int startshort; //number of candle in 15min class
for (int i=(n+ttt); i<(n+32);++i) {
    if (Candle[i].Low<=profit[m].goShort) {startshort=i;break;}
}
//cout<<"startshort is: "<<startshort<<endl; //should be ???

//=============================================
//number of profit levels is from 0 to i (=i+1)
int ii=0;//number of levels of profits
double profitusd[i+1];
double stopusd[i+1];
double lag=7.0; // lag of price at execution of stop
//=============================================
//
//=============================================
   int nn= startshort;//
				//test: nn=???|

//=============================================
//###########################################
//=============================================
int catch1 =0;//to catch whether stop loss was trigerred
int catch2[10];//only for debuging
double tempprofit;//to compare whether profit is stop loss 
int nn2[10];
int nn3[10];//for testing only

while (ii<(i+1)) { //loop for profit levels
				//test: ii=???|
//=============================================
				//test: nn=???|

//=============================================
   if(ii==0) { 
                                     //test: ii=???|

       profit[m].Profit[ii]= - stop[ii] - 2 * lag -3;//let be 
                                     //equal
                                      //to max loss    
       stopusd[ii]=profit[m].goShort + 3 + stop[ii];}//compare 
                            //to ??? 
//=============================================
   else{
       profit[m].Profit[ii]= proflev[ii-1]- stop[ii] - 2* lag - 3;//let be equal to??

       stopusd[ii]=profitusd[ii-1] + stop[ii];}//compare to 
                                     //last taken profit
//=============================================
       profitusd[ii]=profit[m].goShort  + 3 - proflev[ii];//ok
       tempprofit=profit[m].Profit[ii];
    //=============================================
    //check whether stop loss was trigerred at previous level
       if (catch1==1) {
                         //test: catch1=0|catch=0|
            profit[m].Profit[ii]=profit[m].Profit[ii-1];
       } else {//look for profit taken in this level
    //=============================================
    //let's test whether stop loss was realised
    //=============================================


//=============================================
//=============================================
       while(Candle[nn].High<stopusd[ii]) { //stoploss??
//=============================================
//=============================================

             if(Candle[nn].Low<profitusd[ii]) {

                  profit[m].Profit[ii]=proflev[ii]-3-lag;//m 
                                       //is number of trade
                  nn2[ii]=nn;//to check if several profit
                         // levels 
                         //are reached at the same candle 
                  //cout<<nn2[ii]<<endl;
                               //test: nn2=???|

                               //test: nn=???|

                  break; // exit loop upon profit taking
    //=============================================
             }//end of if
//=============================================
//This is start of BREAK LOOP EFFECT

             ++nn;
//=============================================
             //stop if no candles are remaining
             if (nn>stop15) {break;}
//=============================================


    } //end of while(Candle[nn].High<stopusd[ii]) - of a loop for testing realisation of stop loss at 
         //certain level
//=============================================
//This is end of BREAK LOOP EFFECT

                           //test: nn=???|

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                               //if the same candle was checked as in previous level
//and now fail was cathched on this candle, there
//will be no n++


} // end of else (in case stop loss was not trigerred
        //in previous level



//test
nn3[ii]=nn;

//=============================================
if (tempprofit==profit[m].Profit[ii]) {
     catch1=1;
                 //test:catch1=0|0|
//=============================================
//workarounds to cach marginal case
//########################
//WORKARAUND NO.1
//########################
    //if this nn gave SHORT signal, check whether High is not the opening of the candle
    //candles ii>0 will with lowered stop loss will be checked under next workarround
     if(nn==startshort) { 
//=============================================
       if (ii==0){
          if (Candle[nn].Low>profitusd[ii]) {
             if (Candle[nn].Close<stopusd[ii]) {
                 cout<<"marginal case no.1.1(R): "<<nn<<endl;
                 --ii;
                 ++nn; //you should put it back into nn loop
                 catch1=0;
             }
           } else {
               cout<<"marginal case no.1.2(R): "<<nn<<endl;
               profit[m].Profit[ii]=proflev[ii]-3-lag;
               nn2[ii]=nn;//to check if several profit
                         // levels 

               catch1=0;
          } //end of else
       }
     }//end of workaround external if
//=============================================
//########################
//WORKARAUND NO.2
//########################
//if stop loss was recorded, check whether previous profit taking level was reached at the same candle, and if yes, check whether current level is reached ignoring stop loss (whis is lowered with level)
//this should also work for startSHORT candle ii>0 levels, which "failed" due to decrease in stop loss
//something like 
      int case2=0;
      if(ii>0) {     
         if (nn==nn2[ii-1]) {//
             if (Candle[nn].Low<profitusd[ii]) {
                 cout<<"marginal case no.2(R): "<<nn<<endl;
                 profit[m].Profit[ii]=proflev[ii]-3-lag;
                 nn2[ii]=nn;//to check if several profit
                         // levels 
                 catch1=0;
                 case2=2;
           //=============================================
           //however, if level is not reached, compare to close of the candle
              } else {
                      
                           if (Candle[nn].Close<stopusd[ii]) {
                                cout<<"marginal case no.2.2(R): "<<nn<<endl;
                                ++nn;//return to loop
                                --ii;//return to loop
                                catch1=0;
                            }
                     }//end of else
           //=============================================

         }
      }
//########################
//WORKARAUND NO.3
//########################
//if stop loss was recorded, check whether profit level was reached at low before closing the candle
//it is assumed that (open-achieve)<(high-open) gives highest probability to achieve level before stop loss
//something like 
      if (case2 == 0){
         if(nn!=startshort) {
              if (Candle[nn].Low<profitusd[ii]) {
                  if ((Candle[nn].Open - profitusd[ii]) 
                     < (Candle[nn].High - Candle[nn].Open)) {
                     cout<<"marginal case no.3(R): "<<nn<<endl;
                     profit[m].Profit[ii]=proflev[ii]-3-lag;
                     //don't add nn, maybe next pofit can be taken 
                     //on this nn
                     catch1=0;
                  }
               }
           }
      }
//=============================================
}
catch2[ii]=catch1;

//=============================================

//=============================================
    ++ii;//go to next profit level
					 //test: ii=1|
//=============================================
}//end of loop for profit levels






//###################################
//###################################
//###################################
//we have to calculate profit of each level in usd

crypto=possize/profit[m].goShort;
possize = crypto * (profit[m].goShort - lag);


int nnn=0;
double buyprice = profit[m].goShort - lag;
double buyamount;
double sellprice;
double Fees [10];
//============================================
while (nnn<ii) {
     profit[m].Shareusd[nnn]=possize * share[nnn];

     buyamount = profit[m].Shareusd[nnn] / buyprice;
     profit[m].Profitnet[nnn] = profit[m].Shareusd[nnn] * (profit[m].Profit[nnn] / (profit[m].goShort - lag));
     sellprice = profit[m].goShort - lag - profit[m].Profit[nnn];

     //have to deduct trading and funding fees
     //stop trading fees are 0.002 (0.2%) 
     //limit trading fees are 0.001 (0.1%) 
     //let's assume we are borrowing 2/3 of position amount with 0.0007 (0.07%) daily interest rate, and only for one day

     //fees in case position share closed as limit
     if (catch2[nnn]==0) {
          profit[m].Profitnet[nnn] = profit[m].Profitnet[nnn] - buyamount * buyprice *(0.002 + 0.0007 *(2/3)) - buyamount * sellprice *0.001;
          Fees[nnn]= - buyamount * buyprice *(0.002 + 0.0007 *(2/3)) - buyamount * sellprice *0.001;
     } else {
     //fees in case position share closed as stop loss
          profit[m].Profitnet[nnn] = profit[m].Profitnet[nnn] - buyamount * buyprice *(0.002 + 0.0007 *(2/3)) - buyamount * sellprice *0.002;
          Fees[nnn]= - buyamount * buyprice *(0.002 + 0.0007 *(2/3)) - buyamount * sellprice *0.002;
       } // end of else
//============================================
++nnn;
} // end of while
//###################################
//###################################
//###################################


//=============================================
//cout for testing


outfile << profit[m].Time<< ","<<candledate(profit[m].Time)<<","<<profit[m].GR12<< ","<<Real2<<","<<profit[m].Body<<","<<profit[m].Move<<","<<profit[m].Candle<<","<<profit[m].MovExt<<","<<profit[m].CanExt<< ","<<profit[m].goShort<< ","<<profit[m].Profit[0]<< ","<<profit[m].Profit[1]<< ","<<profit[m].Profit[2]<< ","<<profit[m].Profit[3]<<","<<profit[m].Profit[4]<<","<<profit[m].Profitnet[0]<< ","<<profit[m].Profitnet[1]<< ","<<profit[m].Profitnet[2]<< ","<<profit[m].Profitnet[3]<<","<<profit[m].Profitnet[4]<<"," <<profit[m].Profitnet[0] +profit[m].Profitnet[1]+profit[m].Profitnet[2]+profit[m].Profitnet[3]+profit[m].Profitnet[4]<<","<<Fees[ii-5]<<","<<Fees[ii-4]<<","<<Fees[ii-3]<<","<<Fees[ii-2]<<","<<Fees[ii-1]<<endl;

//=============================================


}//end of if (to check whether SHORT signal)


//#############################################
//#############################################
//#############################################

}//end of if (to check whether real)
//#############################################
//#############################################
//#############################################



++m;

} //end of while (signalfile >> row2) 

//=============================================
// close the opened file.
   outfile.close();

//=============================================
//#############################################



//            ######
//          ###########
//         ###       ###
//         ###       ###
//         ###       ###
//         ###       ###
//         ###       ###
//         ###       ###
//         ###       ###
//          ###########
//            ######


//=============================================
//#############################################
//=============================================

//############################
//#####################
//#############
//########
//####
//#
//and remaining tasks:




//calculate average monthly profit/loss

// check which profit taking and stop loss levels are most profitable

//repeat this task on 3H candles, etc.

//create online reader/writer that could make the trades automathically

// try to introduce additional variables, e.g. possible success of trade depending on 1D/1W/1H TD numbers or possible success depending on size of stop losses



//=============================================

////
//cd c:/
//cd c:\sources\test
//g++ test40.cpp -o test40.exe
//test40.exe


   return 0;
}

