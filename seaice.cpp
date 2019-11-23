#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <iostream>
#include <fstream>


//USE FOR SMALL DATA SET
#define YearRange 16 	//YEARS 1990 - 2005  
#define X_Coor 63
#define Y_Coor 63
//*/


//USE FOR LARGE DATA SET
/*
#define YearRange 27
#define X_Coor 304
#define Y_Coor 448
*/


using namespace std;

void Load(float ***);

int main (){

	float ***dataCube = new float **[(YearRange * 52)];
	 
// new float [(YearRange * 52)][X_Coor][Y_Coor];		//[YEAR(27) X Weeks(52) =1,404][X-coor][Y-coor]

	Load(dataCube);

	
	for(int m = 0; m < Y_Coor; m++){
		for(int n = 0; n < X_Coor; n++){
			cout << dataCube[((YearRange * 52)-1)][m][n]; cout << " ";
		}
	}

	

	return 0;
}


void Load (float ***cube){
//void Load ( int Arr[][X_Coor][Y_Coor]){
	int yearStart = (2005 + 1 - YearRange);//Calculate start by substracting yearrange from end year, have to add one for correct calculation.
	int yearEnd = 2005;
	string fileName = "";

	//i == year number
	//j == week number
	for(int i = yearStart; i <= yearEnd; i++){	//Cycle through a range of years.
		for(int j = 1; j <= 52; j++){ //ough each week of said year
			int Z = (((i-yearStart)*52)+j-1);	//Cube starts at 0, i is eaul to a set of 52 weeks on time axis + current week minus one to re-sync array.
			cube[Z] = new float *[Y_Coor];		
				
			//Set Up Correct FileName 
			if(j < 10){	//If Week is a single digit number...
				fileName = to_string(i) + "/Beaufort_Sea_diffw0" + to_string(j) + "y" + to_string(i) + "+landmask";
			}else {		//...Otherwise Week is a two digit number
				fileName = to_string(i) + "/Beaufort_Sea_diffw"  + to_string(j) + "y" + to_string(i) + "+landmask";
			}
//			cout << fileName << endl;
			int Y = 0;
			int X = 0;
			cube[Z][Y] = new float[X_Coor];

			ifstream inputFile(fileName, ios::in | ios::binary);
	
			float dataIn = 4;
			inputFile.read((char*)&dataIn,4);
							
//			cube[Z][Y][X] = dataIn;	
//			X++;
//			int COUNT = 0;	
			while(!inputFile.eof()){
//				cout <<  dataIn;				
  // 				inputFile.read((char*)&dataIn, 4);	//Read Next data input....
//		
//				if(dataIn ==  157 || dataIn == 168){cout << "X";}else {	cout << " ";;	}
//				cout << ""; cout << Z; cout << "-"; cout << Y; cout << "-"; cout << X; cout << " ";
				cube[Z][Y][X] = dataIn;
				if(X == (X_Coor-1)){			//If the end of X axis is reached
//					cout << endl;
					X = 0;					//Reset X to origin
					Y++;				//Increment Y axis	
					if(Y <= (Y_Coor-1)){				//If not at final value of Y axis...
						cube[Z][Y] = new float[X_Coor];			//Create a new array for X axis
					}
				} else {				//Otherwise...
					X++;					//Increment X axis
				}
//				cube[Z][Y][X] = dataIn;			//Assign input to new value.
//				COUNT++;			
//				cout << COUNT;
//			 cout << "-";
	//			if(Y < 1) cout << dataIn;// cout << " ";

				inputFile.read((char*)&dataIn, 4);	//Read the Next data Input...				
			}
			inputFile.close();

		}

	}  
}

