#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
//WOW! THIS IS A COMPLETELY DIFFERENT PROGRAM

class SalesRep
{
   public:
      char  rep[10];		// A character array for ‘rep’ last name.
      char  region[10];		// A character array for the rep’s ‘region’
};

class ItemCatalog
{
   friend   class SALESREC;
   public:
      char     item[10];	// character array for ‘item’ name.
   private:
      float    unitCost;	// a real number for ‘unitCost’.
     
};

class SALESREC: public SalesRep, public ItemCatalog
{
  friend ostream& operator << (ostream&, const SALESREC&);

   public:
      char     date[10];
      int      units;
     
      void setUnitCost(float  newCost)
      {
         unitCost = newCost;
      }
     void operator +(SALESREC b) 
       { 
          units += b.units; 
       }
      bool operator ==(SALESREC b) 
       { 
          return (string(date)==string(b.date) && string(item)==string(b.item) && string(rep) == string(b.rep));
       }
      float getUnitCost()
      {
         return  unitCost;
      }

      float Total()
      {
         return   units * unitCost;
      }
     
      
};

void simpleSortTotal(SALESREC* s[], int c);
ostream& operator<<(ostream& lhs, const SALESREC& rhs)
   {
        lhs << "Date: " << rhs.date << ", Rep:" << rhs.rep << ", Product:" << rhs.item<< endl;
        return lhs;
   }

int main()
{

   ifstream infile;
   int array[20];
   char cNum[10] ;
   SALESREC* salesArr[40];
   int   salesArrayCount;
   SALESREC* s[40];
  
    infile.open ("SalesDataP5.csv");
    if (infile.is_open())
    {
         int   c=0;
         float inputUnitCost;
         while (infile.good())
         {
                salesArr[c] = new SALESREC();
                 infile.getline(salesArr[c]->date, 256, ',');
                 infile.getline(salesArr[c]->region, 256, ',');
                 infile.getline(salesArr[c]->rep, 256, ',');
                 infile.getline(salesArr[c]->item, 256, ',');
                 infile.getline(cNum, 256, ',');
                 salesArr[c]->units = atoi(cNum);
                 infile.getline(cNum, 256, '\n');
                 inputUnitCost = atof(cNum);
                 salesArr[c]->setUnitCost(inputUnitCost);  //store in salesArr[c]
                 for (int i=0; i<c; i++){
                   if((*(salesArr[i]))==(*(salesArr[c]))){
                     *(salesArr[i]) + *(salesArr[c]);
                     salesArr[c] = new SALESREC();
                     c--;
                     break;
                   }
                 }
                 c++;
         }
         salesArrayCount = c-1;
         infile.close();
    }
    else
    {
         cout << "Error opening file";
    }
 
   for (int i=0; i < salesArrayCount; i++)
      s[i] = salesArr[i];

   cout << " Unsorted Sales Record Array\n" ;
   for (int i=0; i < salesArrayCount; i++)
      cout << *(salesArr[i]);
   simpleSortTotal (s, salesArrayCount);
   
   cout << " - - - - - - - - - - - -\n" ;
   cout << " Sorted Sales Record Array\n" ;
   
   for (int i=0; i < salesArrayCount; i++)
      cout << *(salesArr[i]);
  
   //clean up (remove from memory) allocated sales records
   for (int i=0; i < salesArrayCount; i++)
      delete   salesArr[i];
  
}


void simpleSortTotal(SALESREC* s[], int c)
{
   SALESREC* temp;
   for (int i=0; i < c; i++)
      for (int j=i; j < c; j++)
         if (s[i]->Total()>s[j]->Total())
         {
            temp = s[i];
			      s[i] = s[j];
			      s[j] = temp;
         }
}
