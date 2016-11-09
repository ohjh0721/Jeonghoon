#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    char inputName[1024] = { '\0' };
    char outputName[1024] = { '\0' };
    string bent[5000];
    string match[5000];
    int count = 0;
	int weight[5000] = {0};
	int weightCovert[5000] = {0};
    int diameter[5000] = {0};
	int diameterConvert[5000] = {0};
    const int MAX_TRIES = 3;
    int numLines = 0;
    int numActualLines = 0;
    const int MIN_NUMLINES = 0;
    const int MAX_NUMLINES = 5000;
    const int MIN_SENSOR = 0;
    const int MAX_SENSOR = 255;
    int numNickels = 0;
    int numDimes = 0;
    int numQuarters = 0;
    int numLoonies = 0;
    int numToonies = 0;
	int TotalnumNickels = 0;
    int TotalnumDimes = 0;
    int TotalnumQuarters = 0;
    int TotalnumLoonies = 0;
    int TotalnumToonies = 0;
    int rollOfNickels = 0;
    int rollOfDimes = 0;
    int rollOfQuarters = 0;
    int rollOfLoonies = 0;
    int rollOfToonies = 0;
    int sumOfWeightOtherCoins = 0;
    int sumOfBentCoins = 0;
    int TotalWeightOtherCoins = 0;
    int TotalWeightBentCoins = 0;
    int numOfBentContainers = 0;
    int numOfOtherContainers = 0;
    int numOfOtherCoins = 0;
    int TotalnumOtherCoins = 0;
    char c = ' ';
	int i;
    ifstream inFile;
    ofstream outFile;

    //Prompt for and read the filename of the file containing the input data
    //Reprompt a maximum  of 2 times
    do 
	{
        cout << "Type the name of the input file containing sensor readings:" << endl;
        cin >> inputName;
        inFile.open(inputName); //Open the input file

        //Check if the input file is opened correctly
        if (inFile.fail()) 
		{
            //If all 3 times fail, print an error message and then terminate the program
            if (count == MAX_TRIES - 1) 
			{
                cerr << "ERROR: File " << inputName << " could not be opened for input" << endl;
                cerr << "ERROR: You exceeded maximum number of tries allowed" << endl;
                cerr << "while entering the input file name";
                return 1;
            }

            //Before 3 times fail, print an error message and then reprompt
            else 
			{
                cerr << "ERROR: File " << inputName << " could not be opened for input" << endl;
            }
        }

        count++;
    } while (inFile.fail());

    count = 0;
    //Prompt for and read the filename of the output file
    //Reprompt a maximum  of 2 times
    do 
	{
        cout << "Type the name of the output file";
        cout << " which will hold the simulation results:" << endl;
        cin >> outputName;
        outFile.open(outputName); //Open the output files

        //Check if the output file is opened correctly
        if (outFile.fail()) 
		{
            //If all 3 times fail, print an error message and then terminate the program
            if (count == MAX_TRIES - 1) 
			{
                cerr << "ERROR: You exceeded maximum number of tries allowed" << endl;
                cerr << "while entering the output file name";
                return 2;
            }

            //Before 3 times fail, print an error message and then reprompt
            else 
			{
                cerr << "ERROR: File " << inputName << " could not be opened" << endl;
            }
        }

        count++;
    } while (outFile.fail());

    //Read the number of lines in the input files(line0)
    if (!(inFile >> numLines)) 
	{
        //If the file is empty
        //print an error message then close the open files
        //and then terminate the program
        if (inFile.eof()) 
		{
            cerr << "ERROR: Input data file is empty";
            inFile.close();
            outFile.close();
            return 3;
        }

        //If the first character cannot be part of an integer
        //print an error message then close the open files
        //and then terminate the program
        else 
		{
            cerr << "ERROR: First piece of data in the file is not an integer";
            inFile.close();
            outFile.close();
            return 4;
        }
    }

    //Readed the data of the number of lines but
    //if the number of lines is out of range
    //print an error message then close the open files
    //and then terminate the program
    if (numLines <= MIN_NUMLINES || numLines > MAX_NUMLINES)
	{
        cerr << "ERROR: The number of sensor readings is out of range";
        inFile.close();
        outFile.close();
        return 5;
    }

    //Read the two sensor measurements and two strings
    //from Line1 to LineN
    for (i = 0; i < numLines; i++, numActualLines++)
	{
    	//Check if the two sensor measurements and two strings datas were present
        do 
		{
        	inFile.get(c);
		} while (c == ' ' || c == '\t');

		//weight[i] data was not read
		//because there was no more data
        //then leave the repeated block
        if (inFile.eof()) 
		{
            cerr << "ERROR: No more data," << endl;
            cerr << "Simulation completed early before line " << setw(3) << (i + 1);
            cerr << " of input\n";
            break;
        }
		inFile.unget();
		
        //weight[i] data was not read
        if (!(inFile >> weight[i]))
		{
            //because the data read was not an integer
            //print an error message
            //and then leave the block
            cerr << "ERROR: Weight sensor value read on line " << setw(3) << (i + 1);
            cerr << " is not an integer" << endl;
            cerr << "Simulation terminated early: Please correct your data file\n";
            break;
        }

        //Check if the three other datas were present
        do 
		{
        	inFile.get(c);
		} while (c == ' ' || c == '\t');
		inFile.unget();
        
        //If only weight sensor reading was present
        //print an error message
        //then move on to the next line
        if (c == '\n') 
		{
            cerr << "ERROR: Weight sensor measurement only" << endl;
            cerr << "Ignoring line " << setw(3) << (i + 1);
            cerr << " of the input file" << endl;
            continue;
        }
        
        //diameter[i] data was not read
        if (!(inFile >> diameter[i])) 
		{
            //because the diameter sensor data read was not an integer
            //print an error message
            //then leave the block
            cerr << "ERROR: Weight sensor value read on line " << setw(3) << (i + 1);
            cerr << " is not an integer" << endl;
            cerr << "Simulation terminated early: Please correct your data file";
            break;
        }

        //Check if the two other datas were present
        do 
		{
        	inFile.get(c);
		} while (c == ' ' || c == '\t');
		inFile.unget();

        //If only weight and diameter reading was present
        //print an error message
        //then move on to the next line
        if (c == '\n')
		{
            cerr << "ERROR: Weight and diameter sensor measurement only" << endl;
            cerr << "Ignoring line " << setw(3) << (i + 1);
            cerr << " of the input file" << endl;
            continue;
        }

        inFile >> bent[i];

        //bent[i] data was read but
        //the string is not "bent" or "usable"
        //print an error message
        //and then move on to the next line
        bool isBentOrUsable  = true;
        if (bent[i] != "bent" && bent[i] != "usable") 
		{
            cerr << "ERROR: Result of test to determine if coin is bent at line ";
            cerr << setw(3) << (i + 1) << " is invalid" << endl;
            cerr << "Ignoring this line of data" << endl;
            isBentOrUsable  = false;
        }

		if (isBentOrUsable) 
		{
	        //Check the last sensor data was present
	        do 
			{
	        	inFile.get(c);
			} while (c == ' ' || c == '\t');
			inFile.unget();
	        
	        //If only weight and diameter measurements and bent string were present
	        //print an error message
	        //then move on to the next line
	        if (c == '\n')
			{
	            cerr << "ERROR: Weight and diameter sensor measurement and bent string only" << endl;
	            cerr << "Ignoring line " << setw(3) << (i + 1);
	            cerr << " of the input file";
	            continue;
	        }
	       
			inFile >> match[i];
	
	        //match[i] data was read but
	        //the string is not "BothMatch" or "OneMatch" or "NotMatch"
	        //print an error message
	        //and then move on to the next line
	        if (match[i] != "BothMatch" && match[i] != "OneMatch" && match[i] != "NoMatch")
			{
	            cerr << "ERROR: image processing result at line ";
	            cerr << setw(3) << (i + 1) << " is invalid" << endl;
	            cerr << "Ignoring this line of data" << endl;
	            continue;
	        }
		}
        
		//Check if the extra data was present
        bool hasExtra = false;
        string extraData;
        inFile.get(c);
        extraData += c;
        if (c != '\n' && c != '\r')
		{
        	hasExtra = true;
        	while(c != '\n' && c != '\r')
			{
        		inFile.get(c);
      			extraData += c;
        	}
        }

		if (!isBentOrUsable)
		{
			continue;
        }
        
		//If there is extra data at the end of the line of data
        //print an error message
        if (hasExtra && isBentOrUsable)
		{
	    	cerr << "ERROR: Extra data at line " << setw(3) << (i + 1);
			cerr << "   Ignoring extra data" << endl;
			continue;
		}
		
        //If the weight and diameter sensor readings were not within the correct range
        //print an error message
        //and then move on reading and
        //analyzing the next pair of sensor readings
        if ( (weight[i] < MIN_SENSOR || weight[i] > MAX_SENSOR) || (diameter[i] < MIN_SENSOR || diameter[i] > MAX_SENSOR) )
		{
            cerr << "ERROR: Sensor reading out of range, ignoring line " << setw(3) << (i + 1);
            cerr << " in the input file" << endl;
			continue;
        }
    

	    //Determine which kind of coin the row of data represents
	
		//If the coin is bent
		//no further calculation is necessary
		//The bent coin is placed into the bent coin container
		//The bent coin container can hold up to 100g
		if( bent[i] == "bent" )        
		{ 
			sumOfBentCoins += weight[i];  
			TotalWeightBentCoins += sumOfBentCoins;
		    
			//If the bent coin container overweight
			//the container will be replaced and 
			//the weight of coins in the new container
			//will be updated to be the weight of the new coin
			if( sumOfBentCoins > 100)   
			{
				sumOfBentCoins = weight[i];
				outFile << "The Coin Sorter has sent this coin to the bent coin container" << endl;
				outFile << "The coin does not fit in the bent coin container" << endl;
				outFile << "The bent coin container has been replaced" << endl;
				outFile << "The coin in the new bent coin container weighs ";
				outFile << sumOfBentCoins << " grams" << endl; 
				cout << "The Coin Sorter has sent this coin to the bent coin container" << endl;
				cout << "The coin does not fit in the bent coin container" << endl;
				cout << "The bent coin container has been replaced" << endl;
				cout << "The coin in the new bent coin container weighs ";
				cout << sumOfBentCoins << " grams" << endl; 

				numOfBentContainers++;
			}

			//Otherwise the new coin will be added to the bent coin container
			else
			{
				outFile << "The Coin Sorter has sent this coin to the other coin container" << endl;
			    outFile << "The coins in the other coin container now weigh ";
			    outFile << sumOfBentCoins << " grams" << endl;
				cout << "The Coin Sorter has sent this coin to the other coin container" << endl;
			    cout << "The coins in the other coin container now weigh ";
			    cout << sumOfBentCoins << " grams" << endl;
			}
		}

		//If coin is not bent
	    //check to see if the weight, diameter, image of the coin are
	    //consistent with the weight, diameter, image of the Canadian coins
		else
		{
			weight[i] = 2.0 * ( weight[i] * 5.0 / MAX_SENSOR );  //convert the integer weight[i] to the weight of the coin in grams
			diameter[i] = 10 + diameter[i] * 30.0 / MAX_SENSOR;  //convert the integer diameter[i] to the diamter of the coin in millimeters
			
			//If the coin is nickel
			//the nickel is placed into the dime wrapper
			//The nickel wrapper can hold 40 nickels
			if( (weight[i] >= 3.60 && weight[i] <= 4.30) && (diameter[i] >= 20.2 && diameter[i] <= 21.8) && match[i] == "BothMatch" )  
			{
				numNickels++;
				TotalnumNickels += numNickels;
			
				//If the nickel wrapper is full
				//it will be replaced and 
				//the number of nickels in the wrapper will be reset to 0
				//and the number of the roll of nickels will be incremented
				if(numNickels == 40)
				{
					outFile << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
					outFile << "The nickel wrapper is now full" << endl;
					outFile << "The nickel wrapper has now been replaced" << endl;
					cout << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
					cout << "The nickel wrapper is now full" << endl;
					cout << "The nickel wrapper has now been replaced" << endl;
					rollOfNickels++;
					numNickels = 0;
				}
			
				//Otherwise the nickel will be added to the nickel wrapper
				else
				{
					outFile << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
					outFile << "There are now " << numNickels << " coins in the nickel wrapper" << endl;
					cout << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
					cout << "There are now " << numNickels << " coins in the nickel wrapper" << endl;
				}
			}

			//If the coin is dime
			//the dime is placed into the dime wrapper
			//The dime wrapper can hold 50 dimes
			else if( (weight[i] >= 1.30 && weight[i] <= 2.20) && (diameter[i] >= 17.3 && diameter[i] <= 18.7) && match[i] == "BothMatch" )
			{
				numDimes++;   
				TotalnumDimes += numDimes;
			
				//If the dime wrapper is full
				//it will be replaced and 
				//the number of dimes in the wrapper will be reset to 0
				//and the number of the roll of dimes will be incremented
				if(numDimes == 50)   
				{
					outFile << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;
					outFile << "The dime wrapper is now full" << endl;
					outFile << "The dime wrapper has now been replaced" << endl;
					cout << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;
					cout << "The dime wrapper is now full" << endl;
					cout << "The dime wrapper has now been replaced" << endl;
					rollOfDimes++;
					numDimes = 0;
				}

				//Otherwise the dime will be added to the dime wrapper
				else
				{
					outFile << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;
					outFile << "There are now " << numDimes << " coins in the dimes wrapper" << endl;
					cout << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;
					cout << "There are now " << numDimes << " coins in the dimes wrapper" << endl;
				}
			}

			//If the coin is quarter
			//the quarter is placed into the quarter wrapper
			//The quarter wrapper can hold 40 quarters
			else if( (weight[i] >= 4.00 && weight[i] <= 4.80) && (diameter[i] >= 22.8 && diameter[i] <= 24.6) && match[i] == "BothMatch" )
			{
				numQuarters++;
				TotalnumQuarters += numQuarters;

				//If the quarter wrapper is full
				//it will be replaced and 
				//the number of quarters in the wrapper will be reset to 0
				//and the number of the roll of quarters will be incremented
				if(numQuarters == 40)
				{
					outFile << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;
					outFile << "The quarter wrapper is now full" << endl;
					outFile << "The quarter wrapper has now been replaced" << endl;
					cout << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;
					cout << "The quarter wrapper is now full" << endl;
					cout << "The quarter wrapper has now been replaced" << endl;
					rollOfQuarters++;
					numQuarters = 0;
				}

				//Otherwise the dime will be added to the quarter wrapper
				else
				{
					outFile << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;
					outFile << "There are now " << numQuarters << " coins in the quarters wrapper" << endl;
					cout << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;
					cout << "There are now " << numQuarters << " coins in the quarters wrapper" << endl;
				}
			}

			//If the coin is loonie
			//the loonie is placed into the loonie wrapper
			//The loonie wrapper can hold 25 loonies
			else if( (weight[i] >= 6.50 && weight[i] <= 7.50) && (diameter[i] >= 25.0 && diameter[i] <= 27.0) && match[i] == "BothMatch" )
			{
				numLoonies++;
				TotalnumLoonies += numLoonies;

				//If the loonie wrapper is full
				//it will be replaced and 
				//the number of loonies in the wrapper will be reset to 0
				//and the number of the roll of loonies will be incremented
				if(numLoonies == 25)
				{
					outFile << "The Coin Sorter has sent one coin to the loonies wrapper" << endl;
					outFile << "The loonie wrapper is now full" << endl;
					outFile << "The loonie wrapper has now been replaced" << endl;
					cout << "The Coin Sorter has sent one coin to the loonies wrapper" << endl;
					cout << "The loonie wrapper is now full" << endl;
					cout << "The loonie wrapper has now been replaced" << endl;
					rollOfLoonies++;
					numLoonies = 0;
				}

				//Otherwise the dime will be added to the loonie wrapper
				else
				{
					outFile << "The Coin Sorter has sent one coin to the loonies wrapper" << endl;
					outFile << "There are now " << numLoonies << " coins in the loonies wrapper" << endl;
					cout << "The Coin Sorter has sent one coin to the loonies wrapper" << endl;
					cout << "There are now " << numLoonies << " coins in the loonies wrapper" << endl;
			    }
			}

			//If the coin is toonie
			//the toonie is placed into the toonie wrapper
			//The toonie wrapper can hold 25 toonies
			else if( (weight[i] >= 6.75 && weight[i] <= 4.30) && (diameter[i] >= 26.9 && diameter[i] <= 29.1) && match[i] == "BothMatch" )
			{
				numToonies++;
				TotalnumToonies += numToonies;

				//If the toonie wrapper is full
				//it will be replaced and 
				//the number of toonies in the wrapper will be reset to 0
				//and the number of the roll of toonies will be incremented
				if(numToonies == 25)
				{
					outFile << "The Coin Sorter has sent one coin to the toonies wrapper" << endl;
					outFile << "The toonie wrapper is now full" << endl;
					outFile << "The toonie wrapper has now been replaced" << endl;
					cout << "The Coin Sorter has sent one coin to the toonies wrapper" << endl;
					cout << "The toonie wrapper is now full" << endl;
					cout << "The toonie wrapper has now been replaced" << endl;
					rollOfToonies++;
					numToonies = 0;
				}

				//Otherwise the dime will be added to the toonie wrapper
				else
				{
					outFile << "The Coin Sorter has sent one coin to the tooies wrapper" << endl;
					outFile << "There are now " << numToonies << " coins in the toonies wrapper" << endl;
					cout << "The Coin Sorter has sent one coin to the tooies wrapper" << endl;
					cout << "There are now " << numToonies << " coins in the toonies wrapper" << endl;
				}
			}

			//If the coin is not a Canadian coin
			//The coin is placed into the the other coin container
			//The other coin container can hold up to 200g
			else
			{
				numOfOtherCoins++;
				TotalnumOtherCoins += numOfOtherCoins;
				sumOfWeightOtherCoins += weight[i];
				TotalWeightOtherCoins += sumOfWeightOtherCoins;
			
				//If the other coin container overweight
				//the container will be replaced and 
				//the weight of coins in the new container
				//will be updated to be the weight of the new coin
				if( sumOfWeightOtherCoins > 200)
				{
					sumOfWeightOtherCoins = weight[i];
					outFile << "The Coin Sorter has sent this coin to the other coin container" << endl;
					outFile << "The coins in the other coin container now weigh ";
					outFile << sumOfWeightOtherCoins << " grams" << endl; 
					cout << "The Coin Sorter has sent this coin to the other coin container" << endl;
					cout << "The coins in the other coin container now weigh ";
					cout << sumOfWeightOtherCoins << " grams" << endl; 
					numOfOtherContainers++;
					numOfOtherCoins = 0;
				}

				//Otherwise the new coin will be added to the other container
				else
				{
					outFile << "The Coin Sorter has sent this coin to the other coin container" << endl;
					outFile << "The coins in the other coin container now weigh ";
					outFile << sumOfWeightOtherCoins << " grams" << endl;
					cout << "The Coin Sorter has sent this coin to the other coin container" << endl;
					cout << "The coins in the other coin container now weigh ";
					cout << sumOfWeightOtherCoins << " grams" << endl;
				}
			}
		}
	}

	//Print the summary of the simulation
	cout << endl << endl << endl << endl;
	outFile << "SUMMARY" << endl;
	outFile << "The Coin Sorter made " << setw(3) << rollOfNickels << " rolls of nickels" << endl;
	outFile << "    There are " << setw(2) << numNickels << " in the partially full roll." << endl;
	outFile << "The Coin Sorter made " << setw(3) << rollOfDimes << " rolls of dimes" << endl;
	outFile << "    There are " << setw(2) << numDimes << " in the partially full roll." << endl;
	outFile << "The Coin Sorter made " << setw(3) << rollOfQuarters << " rolls of quarters" << endl;
	outFile << "    There are " << setw(2) << numQuarters << " in the partially full roll." << endl;
	outFile << "The Coin Sorter made " << setw(3) << rollOfLoonies << " rolls of loonies" << endl;
	outFile << "    There are " << setw(2) << numLoonies << " in the partially full roll." << endl;
	outFile << "The Coin Sorter made " << setw(3) << rollOfToonies << " rolls of toonies" << endl;
	outFile << "    There are " << setw(2) << numToonies << " in the partially full roll." << endl;
	outFile << "The Coin Sorter processed " << setw(5) << TotalnumOtherCoins  << " other coins" << endl;
	outFile << "    The other coins complete filled " << setw(3) << numOfOtherContainers << " containers" << endl;
	outFile << "    There were " << setw(2) << numOfOtherCoins;
	outFile << " coins in the partially full container" << endl;
	outFile << "    The total weight of the other coins was ";
	outFile << fixed << setprecision(3) << setw(9) << TotalWeightOtherCoins << " grams" << endl;
	outFile << "The Coin Sorter processed " << fixed << setprecision(4) << setw(11) << TotalWeightBentCoins << " g of bent coins";
	cout << "SUMMARY" << endl;
	cout << "The Coin Sorter made " << setw(3) << rollOfNickels << " rolls of nickels" << endl;
	cout << "    There are " << setw(2) << numNickels << " in the partially full roll." << endl;
	cout << "The Coin Sorter made " << setw(3) << rollOfDimes << " rolls of dimes" << endl;
	cout << "    There are " << setw(2) << numDimes << " in the partially full roll." << endl;
	cout << "The Coin Sorter made " << setw(3) << rollOfQuarters << " rolls of quarters" << endl;
	cout << "    There are " << setw(2) << numQuarters << " in the partially full roll." << endl;
	cout << "The Coin Sorter made " << setw(3) << rollOfLoonies << " rolls of loonies" << endl;
	cout << "    There are " << setw(2) << numLoonies << " in the partially full roll." << endl;
	cout << "The Coin Sorter made " << setw(3) << rollOfToonies << " rolls of toonies" << endl;
	cout << "    There are " << setw(2) << numToonies << " in the partially full roll." << endl;
	cout << "The Coin Sorter processed " << setw(5) << TotalnumOtherCoins  << " other coins" << endl;
	cout << "    The other coins complete filled " << setw(3) << numOfOtherContainers << " containers" << endl;
	cout << "    There were " << setw(2) << numOfOtherCoins;
	cout << " coins in the partially full container" << endl;
	cout << "    The total weight of the other coins was ";
	cout << fixed << setprecision(3) << setw(9) << TotalWeightOtherCoins << " grams" << endl;
	cout << "The Coin Sorter processed " << fixed << setprecision(4) << setw(11) << TotalWeightBentCoins << " g of bent coins";

	inFile.close();
	outFile.close();

	return 0;

}
