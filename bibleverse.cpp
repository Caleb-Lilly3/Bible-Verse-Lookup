/*********************************************************
* Summary:Old Testament Verse Finder 
*
* Author: Caleb Lilly
* Created: 10/14/26
*
********************************************************/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

int main() {
   
   ifstream inFS;                   //For the external file
	ofstream outFS;
	string currentLine = "";         //For grabbing the line and checking
	string book = "";                //All Veriables for user input
	string bookUpper = "";
	string chapterFind = "CHAPTER ";
	string chapter = "";
	string verse = "";
	bool bookErr = false;            //All the bools for the input Errors
	bool chapterErr = false;
	bool verseErr = false;
	bool error = false;              //For when an error is triggered in the program
	
	//Get all the informatiuon from the user
	cout << "Please enter the reference of the verse you would like" << endl;
	cout << "  the book: ";
	getline(cin, book);
	cout << "  the chapter: ";
	cin >> chapter;
	cout << "  the verse: ";
	cin >> verse;

	//Change book to all uppercase
	for(int i = 0; i < book.size(); ++i) {
		bookUpper.push_back(toupper(book.at(i)));
	}

	//open file and check to make sure it opened
	inFS.open("OT.txt");

	if(!inFS.is_open()) {
		cout << "Error cannot open OT.txt" << endl;
		return 1;
	}
	//Find book
	else{
		getline(inFS, currentLine);
			while(currentLine.find(bookUpper) == string::npos && error == false){
				getline(inFS, currentLine);
				if(inFS.eof()){
					bookErr = true;
					error = true;
				}
			}
	}
	
	//Set up chapter
	if(bookUpper == "PSALM"){
		chapterFind = "PSALM " + chapter;
	}
	else{
	chapterFind = chapterFind + chapter;
	}
	
	//Find chapter
	if(!error){
		getline(inFS, currentLine);
		while(currentLine.find(chapterFind) == string::npos && error == false){
			getline(inFS, currentLine);
			if(currentLine.find("BOOK") != string::npos || inFS.eof() || chapter == "0"){
				error = true;
				chapterErr = true;
			}
		}
	}
	
	//Find verse
	if(!error){
		getline(inFS, currentLine);
		while(currentLine.find(verse) == string::npos && error == false){
			getline(inFS, currentLine);
			if(currentLine.find("CHAPTER") != string::npos || inFS.eof() || verse == "0"){
				error = true;
				verseErr = true;
			}
		}
	}
	
	inFS.close(); //Done with retreving information from file

	//All if statments for all possable outputs
	if(!error){
		outFS.open("verses.txt", ios::app);                    //Open to print to file
		cout << book << " " << chapter << endl;
		cout << currentLine << endl;
		outFS << book << " " << chapter << endl;
		outFS << currentLine << endl;
		outFS.close();                               //Close file done writting to it
	}
	else if(bookErr == true){
		cout << book << " does not exist in the Old Testament" << endl;
	}
	else if(chapterErr == true){
		cout << "Chapter " << chapter << " does not exist in " << book << endl;
	}
	else if(verseErr == true){
		cout << "Verse " << verse << " does not exist in " << book << " " << chapter << endl;
	}

   return 0;
}
