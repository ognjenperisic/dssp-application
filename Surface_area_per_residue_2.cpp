// Surface_area_per_residue_2.cpp : Defines the entry point for the console application.
//

// monomers.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "windows.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <direct.h>

#include <cmath>
#include <math.h>
#include <conio.h>

using namespace std;


void transforms(string a, float &br, int x, int y)
{
    char numb[256] = "";
    char i;

    for (i = x; i<x+y; i++)
      numb[i-x] = a[i];
    
    br = atof(numb);
}


void transforms(string a, int &br, int x, int y)
{
    char numb[256] = "";
    char i;

    for (i = x; i<x+y; i++)
      numb[i-x] = a[i];
    
    br = atoi(numb);
}



int main(int arcg, char* argv[])
{
   char readln[256];   
   string line;
   float xc, yc, zc;

   char file_name[20] = "";  
   char old_prot;
   char* file_ext = "single";
   char program[80];
   char file_name2[20] = "";
   char current_chain = '@';
   char* file_ext2 = "dssp"; 
   int previous_residue = -100;
   int current_residue;
   char sub = '^';
   
   /*
   WIN32_FIND_DATA FileData; 
   HANDLE hSearch; 
   */

   vector<char> chain;
   
   /*
   char* dir1="C:\\Articles\\decoy\\baker";
   char* dir2="C:\\Articles\\decoy\\baker\\results";
   */
  
   /*
   char* dir1 = "C:\\MBRB\\MOAD\\BindingMoad2005";
   char* dir2 = "C:\\MBRB\\MOAD\\BindingMoad2005\\results";
   */

   /*char* dir1 = "c:\\GNM\\FILES\\DIMER-1\\heterodimer\\";
   char* dir2 = "c:\\GNM\\FILES\\DIMER-1\\heterodimer\\test";*/


   
   int i = 0;
   FILE* out;   
   BOOL fFinished = FALSE; 
   BOOL write;
  
   
   ifstream fin(argv[1]);
   printf("\n%s\n",argv[1]);
   
   while (fin.getline(readln, 256))
   {
       line = readln;
       
       if (line.substr(0,4) == "ATOM")//&&(line.substr(13,4)==" CA "))
       {
           if (line.substr(12,4)==" CA ")
           {
               if (readln[21] != ' ')
               {
                   if(readln[21]!=current_chain)
                   {
                       chain.push_back(readln[21]);
                       current_chain = readln[21];
                   }
               }
               else
               {
                   if(readln[21] != current_chain)
                   {
                       if(current_chain!='#')
                       {
                           chain.push_back('#');
                           current_chain = '#';
                       }
                   }
               }                               
           } 
       }
   }   

   fin.close();
   /*
   for(i = 0; i<chain.size(); i++)
   {
       printf("Chain %3c\n", chain[i]);
   }
   */
   
   for(int p = 0; p <chain.size(); p++)
   {
       ifstream fin(argv[1]);

       i = 0;
       do
       {
           file_name[i] = argv[1][i];
           i++;
       }while (argv[1][i]!='.');
       
       file_name[i++] = '_';
       file_name[i++] = chain[p];
       file_name[i++] = '.';
       file_name[i] = '\0';
       strcat(file_name, file_ext);
       printf("%s\n", file_name);
       previous_residue = -100;
       write = true;
       
       //_chdir(dir2);
       out = fopen(file_name,"w");
       
       while (fin.getline(readln, 256))
       {           
           line = readln;
           if (line.substr(0,4)=="ATOM")//&&(line.substr(13,4)==" CA "))
           {                              
               //if ((readln[21]==comp->H)|((comp->H='Q')&(readln[21]==char(32))))
               if ((readln[21]==chain[p]))
               {  
                   transforms(line, current_residue, 22,4); 
                   if (current_residue!=previous_residue)
                       write = true;
                   
                   if ((current_residue==previous_residue)&(sub!=readln[26]))
                       write = false;
                   
                   if (write)
                   {
                       fprintf(out,"%s\n", readln);
                       transforms(line, previous_residue, 22, 4); 
                       sub = readln[26];
                   }
               }
           }
       }
   
       fin.close();
       fclose(out);
       
       i = 0;
       program[0] = '\0';
       strcat(program,"dsspcmbi ");
       do
       {
           file_name2[i]=file_name[i];
           i++;
       }while (file_name[i] != '.');
       
       file_name2[i++] = '.';
       file_name2[i++] = '\0';
       strcat(file_name2, file_ext2);
       printf("%s\n", file_name2);
       strcat(program, " ");
       strcat(program, file_name);
       strcat(program, " ");
       strcat(program, file_name2);
       printf("%s\n", program);
   
       WinExec(program, SW_SHOWNORMAL);
       //_chdir(dir1);
   }
   
   return 0;
}