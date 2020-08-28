////////////////////////////////////////////////////////////
//	Jeaustin Sirias Chacon (jeaustin.sirias@ucr.ac.cr)	  //
//				Github: JeaustinSirias					  //
//					 ID: B66861							 //
///////////////////////////////////////////////////////////

//LABORATORY #2:
//a brief program that asks for some 2D rectangular coordinates and 
//calculates the largest and the shortest distances between them.
//The output is the found (x, y) pair(s) linked to max. and min. dists.

//packages in use
#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

int main(){

	//declaring initial variables
	int rows, coordsNum = 0; 
	float inputNum;
	float x, y; //candidates to be stored as (x, y)
	char comma; //a comma ',' heheps
	float distVector[400];

	//heading
	cout<<".\n.\n.\n.\n.\nHi there! this is a program that asks for some 2D (x, y) coords\n";
	cout<<"and calcs both largest and shortest distances beetween them.\n";
	cout<<"The output is the found (x, y) pair(s) linked to max. and min. dists.\n.\n.\n.\n.";
	
	//ask the user for the number of points to compute:
	do{

		cout<<"Input the number of rectangular coordinates to compute: "; cin>>inputNum; cout<<"\n. \n. \n. \n";

		//exceptions
		if((inputNum - int(inputNum)) != 0){ cout<<"Floats cannot be computed for this action. Try again.\n";}
		if(inputNum < 2){cout<<"You cannot choose less than 2 coordinates. Try again.\n";}

	} while(inputNum < 2 || (inputNum - int(inputNum)) != 0); coordsNum = int(inputNum);


	//save coordinates input by user:
	float coords[coordsNum][2]; //set up a [rows x cols] matrix to store (x, y) coordinates
	for(rows = 0; rows < coordsNum; rows++){

		cout<<rows + 1<<". Input a 2D rectangular coordinate as x,y: "; cin>>x>>comma>>y; cout<<endl;
		coords[rows][0] = x;
		coords[rows][1] = y;			
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*Since the way of sorting input (x,y) points doesnt matter
	so we need to get all the possible (x1, y1); (x2, y2) combinations
	without repeating cases. So the formula to use is: 		 r!
														-----------	= C(r, n)
														 n!(r - n)!		

	where r is the number of (x, y) input coordinates and n is a pair of coordinates; here n=2 always.							
	*/

	int count = 1, distStack = 0; //count is a counter to refresh the next nested loop, so we can get C(r, n) in a row.
	float largest = -1, shortest = -1; //these vars will save the current max and min (x1, y1); (x2, y2) distance until loop ends.

	vector<float> hiCoords(4); //a vector to store the (x, y) pair points linked to the largest distance
	vector<float> loCoords(4); //a vector to store the (x, y) pair points linked to the shortest distance

	//here we go iterating in order to get C(r, n)
	for(int i = 0; i < (coordsNum - 1); i++){
		for(int j = count; j < coordsNum; j++){
			
			//compute the norm as sqrt((x1- x2)^2 + (y1 - y2)^2). 
			distVector[distStack] = sqrt(pow((coords[i][0] - coords[j][0]), 2) + pow((coords[i][1] - coords[j][1]), 2));

			//Looking for the largest distance 
			if(largest == -1 || distVector[distStack] > largest){

				largest = distVector[distStack];

				//save the (x, y) pair 
				hiCoords[0] = coords[i][0];
				hiCoords[1] = coords[i][1];
				hiCoords[2] = coords[j][0];
				hiCoords[3] = coords[j][1];

				//delete all analog old pairs (if exist) if a larger distance is found 
				if(hiCoords.size() > 4){

					int hiSize = hiCoords.size();
					hiCoords.erase(hiCoords.begin() + 4, hiCoords.begin() + hiSize);
				}

			}

			//if there's one more than 1 (x1,y1);(x2,y2) pair with the same maximum distance, 
			//then save those points as it follows:
			else if(distVector[distStack] == largest){
				
				//append (x, y) analog pair if exists (a pair that shares the same current max. distance.)
				hiCoords.push_back(coords[i][0]);
				hiCoords.push_back(coords[i][1]);
				hiCoords.push_back(coords[j][0]);
				hiCoords.push_back(coords[j][1]);	

				}

			//Evaluating the shortest distance beetween points
			if(shortest == -1 || distVector[distStack] < shortest){

				shortest = distVector[distStack];

				loCoords[0] = coords[i][0];
				loCoords[1] = coords[i][1];
				loCoords[2] = coords[j][0];
				loCoords[3] = coords[j][1];

				//delete old analog pairs (if exist) if a shorter distance is found 
				if(loCoords.size() > 4){

					int loSize = loCoords.size();
					loCoords.erase(loCoords.begin() + 4, loCoords.begin() + loSize);
				}
			}
			//if there's one more than 1 (x1,y1);(x2,y2) pair with the same minimum distance, 
			//then save those points as it follows:
			else if(distVector[distStack] == shortest){

				//append (x, y) analog pair if exists (a pair that shares the same current min. distance.)
				loCoords.push_back(coords[i][0]);
				loCoords.push_back(coords[i][1]);
				loCoords.push_back(coords[j][0]);
				loCoords.push_back(coords[j][1]); 
			}
			
			//cout<<distVector[distStack]<<" for ("<<coords[i][0]<<", "<<coords[i][1]<<"); ("<<coords[j][0]<<", "<<coords[j][1]<<")"<<endl;
			distStack += 1;
		}

		count += 1; //refreshed in each loop to acheieve C(r, n)
	}

	//cout<<"largest dist found is:"<<largest<<endl;
	//cout<<"shortest dist found is:"<<shortest<<endl;

	//we get the vectors' lenght, so we can limit the loops to print (x, y) max./min. dist. pairs 
	int hiCoords_size = hiCoords.size()/4; //divided by 4 cause we have (x1, y1, x2, y2) styled pairs
	int loCoords_size = loCoords.size()/4;

	//PRINT THE COORDINATE(S) LINKED TO THE LARGEST DISTANCE FOUND
	int k = 0;
	cout<<"\n. \n. \n. \n. \nMax. distance occurs between the point(s):\n";
	for(int i = 0; i < hiCoords_size; i++){

		cout<<"("<<hiCoords[0+k]<<", "<<hiCoords[1+k]<<") and ("<<hiCoords[2+k]<<", "<<hiCoords[3+k]<<")\n";

		k += 4;
	}

	//PRINT THE COORDINATE(S) LINKED TO THE SHORTEST DISTANCE FOUND
	int q = 0; //q is a counter to get out all the (x, y) pairs saved
	cout<<"\n. \n. \n. \n. \nMin. distance occurs between the point(s):\n";
	for(int i = 0; i < loCoords_size; i++){

		cout<<"("<<loCoords[0+q]<<", "<<loCoords[1+q]<<") and ("<<loCoords[2+q]<<", "<<loCoords[3+q]<<")\n";

		q += 4;
	}

	return 0;	

}

