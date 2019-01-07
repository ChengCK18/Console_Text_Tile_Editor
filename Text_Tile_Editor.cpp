/**********|**********|**********|
Program: TT04_A2_CHENG_CHIN_KHENG.cpp
Course: TCP1101 Programming Fundamentals
Year: 2017/18 Trimester 1
Name: Cheng Chin Kheng
ID: 1161101863
Email: chinkheng_98@hotmail.com
Phone: 016-4722386
**********|**********|**********/


#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;


//CCK

//functions declarations line 22-26
void get_fileName(string &fileName,int &fileNameSize,string response);//function to get file name
void display_table(string text[],int maxC[],int &textIndex,string fileName,int textSize[],string &find_text);//function to display the table
void textSize_max(int textSize[],int maxC[]); //function to determine the maximum text size column by column
void load_function(string &fileName,string text[],int textSize[],int &textIndex,int load_counter,int &status0,int maxC[]);//function to load file
void undo_function(int textIndex,string undo_variable[50][82],string text[],int &action_performed);//function to store initial state of text and textIndex


int main()
{
	string response="",fileName="NULL",text[82],text_input,text_store,clip_board[10],find_text="NULL",undo_variable[50][82]; 
	int fileNameSize=0,status=1,textSize[82],textIndex=1,tileNum=0,maxC[9],tempXO_var,
	tileNum1=0,del_counter=0,load_counter=0,copy_cut_counter=0,paste_counter=0,
	overwrite_counter=0,undo_textIndex=1,insert_counter=0,status0=0,action_performed= -1;//INITIALIZING VALUES LINE 31-45
	
	for (int count=0;count<82;count++) 
	{
		text[count]="     ";
		textSize[count]=5;
	}
	
	for (int count=0;count<9;count++)
	{
		maxC[count]=5;
	}
	
		
	cout<<"*============================================================================*\n"<<endl;
	cout<<"File name: "<<fileName<<endl<<endl; //displaying the file name
	cout<<"[N]ew, [I]nsert, [D]elete, [O]verwrite, [L]oad, [S]ave,\n[C]opy, show-clip[B]oard, [X] cut, [P]aste, [F]ind, [U]ndo"<<endl<<"==> ";
	
	getline(cin,response); //Get input from user to determine his/her action
	transform(response.begin(),response.end(),response.begin(),::toupper); //user input are transformed into uppercase for simplicity
	
	while (response!="N" && response!="L") //Stating of the program requires user to create new file or load only.
	{
		cout<<"Invalid action!\n==> ";
		getline(cin,response);
		transform(response.begin(),response.end(),response.begin(),::toupper);
	}
	
	while (status0==0) //Ensures that the file user wants to load exist or else ask for response again
	{
		if (response=="N")
		{
			get_fileName(fileName,fileNameSize,response); //Function to get the file name
			status0=1; //status0=1 to exit the loop
		}
		else if (response=="L")
		{
			load_function(fileName,text,textSize,textIndex,load_counter,status0,maxC);//function to load file.status0=1 if file exist
			textSize_max(textSize,maxC); //Comparing the text size according to column and determing the largest size
		}
	}
	
	while (status==1) //The main loop to keep the whole program going
	{
				
		display_table(text,maxC,textIndex,fileName,textSize,find_text); //Display the table
		cout<<"\n[N]ew, [I]nsert, [D]elete, [O]verwrite, [L]oad, [S]ave,\n[C]opy, show-clip[B]oard, [X] cut, [P]aste, [F]ind, [U]ndo"<<endl<<"==> ";
		getline(cin,response); //Get input from user to determine his/her action
		transform(response.begin(),response.end(),response.begin(),::toupper);//user input are transformed into uppercase for simplicity
		

		//***NEW***//
		if (response=="N") 
		{
			response="",fileName="NULL",find_text="NULL",//Reinitialise all values line 88-103
			
			fileNameSize=0,status=1,textIndex=1,tileNum=0,tileNum1=0,
			del_counter=0,load_counter=0,copy_cut_counter=0,paste_counter=0,overwrite_counter=0,
			undo_textIndex=1,insert_counter=0,status0=0,action_performed= -1;
			
			for (int count=0;count<82;count++)
			{
				text[count]="     ";
				textSize[count]=5;
			}
	
			for (int count=0;count<9;count++)
			{
				maxC[count]=5;
			}
			get_fileName(fileName,fileNameSize,response);
			
		}
				
		//***INSERT***//
		else if (response=="I") 
		{
			action_performed= -1;//resets the undo counter
			
			cout<<"Tile number ==> ";
			cin>>tileNum; //To obtain the tile number from user
			if (cin.fail()||tileNum>textIndex||tileNum==0||textIndex>80) //ERROR CHECKING FOR TILENUM. Ensures maximum number of words in the table is only 80
			{                                                                                //Ensures maximum number of words in the table is only 80
				if (textIndex>=80)//This message is for maximum number of words reached
				{
					cout<<"\n\n ###Limit of words reached###\n"<<endl;
				}
				else //This message is for invalid input such as characters entered by user
				{
					cout<<"\n\n### Invalid input for the tile number ###\n"<<endl;
				}
				cin.clear();
				cin.ignore(1000,'\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000,'\n');
				
				cout<<"\nText ==> ";
				getline(cin,text_input);//Get the text from the user
				istringstream ss(text_input);
				
				for (string text_store;ss>>text_store;)//Uses istringstream to split the input when whitespace appear
				{	
					insert_counter+=1; //Counter to count number of words
					if (insert_counter>10) //ERROR CHECKING FOR NUMBER OF WORDS.Accept up to 10 words and excess are discarded
					{
						cout<<"\n\n### Insert only accepts 1 to 10 words at a time.Excess words are discarded ###\n"<<endl;
						break;
					}
					else
					{
						if (textIndex>80) //Ensures maximum number of words in the table is only 80
						{
							cout<<"\n\n ###Limit of words reached###\n"<<endl;
							break;
						}
						for (int count=81;count>tileNum;count--) //"Pulls" the text from 81 which contain blank spaces
						{
							text[count]=text[count-1];// The "pull" action
							textSize[count]=text[count].size(); //text size are recalibrated accordingly
						}
						text[tileNum]=text_store; //inserting the user's text into text array
						textSize[tileNum]=text[tileNum].size();//text size are recalibrated accordingly
						tileNum++; //increment to advance to the next text array
						textIndex+=1;//to keep track of which cell is empty and which are not
						
					}						
				}
				insert_counter=0; //reset to 0 for future use
				textSize_max(textSize,maxC); //Comparing the text size according to column and determing the largest size				
			}
		}
		
		//***DELETE***//
		else if (response=="D") 
		{
			
			cout<<"From Tile Number ==> ";
			cin>>tileNum;//Getting the "From tile number: "
			if (cin.fail()||tileNum>=textIndex||tileNum==0||tileNum1==81) //ERROR CHECKING FOR TILENUM
			{
				cout<<"\n###Invalid input for the tile number###\n"<<endl;
				cin.clear();
				cin.ignore(1000,'\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000,'\n');
				cout<<"To Tile Number ==> ";
				cin>>tileNum1; //Getting the "To tile number: "
				if (cin.fail()||tileNum1>=textIndex||tileNum1==0||tileNum1==81||tileNum1<tileNum) //ERROR CHECKING FOR TILENUM1
				{
					cout<<"\n###Invalid input for the tile number###\n"<<endl;
					cin.clear();
					cin.ignore(1000,'\n');
				}
				else
				{
					undo_function(textIndex,undo_variable,text,action_performed);//Undo function save initial state of text before operation
					cin.clear();
					cin.ignore(1000,'\n');
					del_counter=tileNum1-tileNum; //Calculate the number of words user wish to delete
					if (del_counter>=11) //ERROR CHECKING triggers when user attempt to delete more than 11 words at a time
					{
						cout<<"\n\n ### Unable to perform delete.Only 1 to 11 words at a time ###\n"<<endl; 
					}
					else
					{					
						for (int count=0;count<=del_counter;count++) //Number of delete operation conducted
						{
							for (int count1=tileNum;count1<textIndex;count1++)
							{
								text[count1]=text[count1+1]; //replacing the text with the text from the front.Thus "deleting" it.
								textSize[count1]=text[count1].size();//text size are recalibrated accordingly
							}
							textIndex-=1; //to keep track of which cell is empty and which are not
						}
						textSize_max(textSize,maxC); //Comparing the text size according to column and determing the largest size
					}
				}
			}
			
		}
		
		//***OVERWRITE***//
		else if (response=="O") 
		{
			cout<<"Tile number ==> ";
			cin>>tileNum; //To obtain the tile number
			if (cin.fail()||tileNum>=textIndex||tileNum==0||tileNum==81) //ERROR CHECKING FOR TILENUM
			{
				cout<<"\n###Invalid operation! Can't overwrite empty cell###\n"<<endl;
				cin.clear();
				cin.ignore(1000,'\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000,'\n');
		
				undo_function(textIndex,undo_variable,text,action_performed);//Undo function save initial state of text before operation
				
				cout<<"\nText ==> ";
				getline(cin,text_input);
				istringstream ss(text_input); 
				overwrite_counter=tileNum;
				tempXO_var=overwrite_counter+10; //Plus 10 because only 10 words are allowed to be overwritten
				for (string text_store;ss>>text_store;) //Uses istringstream to split the input when whitespace appear
				{
					if (overwrite_counter>=tempXO_var)//Overwrite up to 10 words only.Excess are discarded
					{	
						cout<<"\n\n### Overwrite only accepts 1 to 10 words at a time.Excess words are discarded ###\n"<<endl;
						break;
					}
					else
					{
						text[tileNum]=text_store; //inserting the user's text into text array
						textSize[tileNum]=text[tileNum].size();//text size are recalibrated accordingly
						tileNum++;//increment to advance to the next text array
						overwrite_counter+=1;//keep track of number of words overwritten
					}					
				}
				
				if (overwrite_counter>textIndex) //RECALIBRATE TEXT INDEX AFTER CHANGES
				{
					textIndex=textIndex+(overwrite_counter - textIndex);
				}
				textSize_max(textSize,maxC); //Comparing the text size according to column and determing the largest size
			}
			
		}
		
		//***LOAD***//
		else if (response=="L") 
		{
			action_performed= -1;
			load_function(fileName,text,textSize,textIndex,load_counter,status0,maxC); //Function that loads file
			textSize_max(textSize,maxC); //Comparing the text size according to column and determing the largest size			
		}
		
		//***SAVE***//
		else if (response=="S") 
		{
			get_fileName(fileName,fileNameSize,response); //Get the file name from user to save file
			
			ofstream the_file_save;
			the_file_save.open(fileName.c_str());//creating the file with the file name user entered
			for (int count=0;count<82;count++)
			{
				the_file_save<<text[count]<<endl;
			}
			the_file_save.close();
			
			
			
			cout<<"\n***File saved***\n"<<endl;
			
			cout<<"------------------------ "<<fileName<<" for reference ------------------------\n\n"<<endl;
			for (int count=1;count<=textIndex;count++)
			{
				cout<<text[count]<<" ";
			}
			cout<<endl<<endl;
		}
		
		//***COPY***//
		else if (response=="C") 
		{
			cout<<"From Tile Number ==> ";
			cin>>tileNum; //to obtain "From tile number: "from user
			
			if (cin.fail()||tileNum>=textIndex||tileNum==0||tileNum==81) //ERROR CHECKING FOR TILENUM
			{
				cout<<"\n###Invalid input for the tile number###\n"<<endl;
				cin.clear();
				cin.ignore(1000,'\n');
			}
			
			else
			{
				cin.clear();
				cin.ignore(1000,'\n');
				
				cout<<"To Tile Number ==> ";
				cin>>tileNum1;//to obtain "To tile number: "from user
				
				if (cin.fail()||tileNum1>=textIndex||tileNum1==0||tileNum1==81||tileNum1<tileNum) //ERROR CHECKING FOR TILENUM1
				{
					cout<<"\n###Invalid input for the tile number###\n"<<endl;
					cin.clear();
					cin.ignore(1000,'\n');
				}
				else
				{
					cin.clear();
					cin.ignore(1000,'\n');
					copy_cut_counter=tileNum1 - tileNum;//Calculate the number of words user wish to copy
					if (copy_cut_counter<10)//only copies when number of words is less than 10
					{
						for (int count=0;count<10;count++) //reset clipboard to empty
						{
							clip_board[count]="";
						}
						
						for (int count=0;count<=copy_cut_counter;count++)//copies the text onto clipboard
						{
							clip_board[count]=text[tileNum];
							tileNum++;//increment to advance to the next text array
						}
					}
					else
					{
						cout<<"\n\n ###Unable to copy.Only 1 to 10 words only at a time###\n"<<endl;
					}
				}
			}
		}
		 
		 //***SHOW CLIPBOARD***//
		else if (response=="B") 
		{	
			cout<<endl<<endl<<"Clipboard: "<<endl;
			for (int count=0;count<10;count++) //printing the clipboard content
			{
				cout<<clip_board[count]<<" ";
			}
			cout<<endl<<endl;
				
		}
		
		//***CUT***//
		else if (response=="X") 
		{		
			cout<<"From Tile Number ==> ";
			cin>>tileNum; //to obtain "From tile number: "from user
			if (cin.fail()||tileNum>=textIndex||tileNum==0||tileNum==81) //ERROR CHECKING FOR TILENUM
			{
				cout<<"\n###Invalid input for the tile number###\n"<<endl;
				cin.clear();
				cin.ignore(1000,'\n');
			}
			else
			{
			
				cin.clear();
				cin.ignore(1000,'\n');
				cout<<"To Tile Number ==> ";
				cin>>tileNum1;//to obtain "To tile number: "from user
				if (cin.fail()||tileNum1>=textIndex||tileNum1==0||tileNum1==81||tileNum1<tileNum) //ERROR CHECKING FOR TILENUM1
				{
					cout<<"\n###Invalid input for the tile number###\n"<<endl;
					cin.clear();
					cin.ignore(1000,'\n');
				}
				else
				{
					cin.clear();
					cin.ignore(1000,'\n');
					
					undo_function(textIndex,undo_variable,text,action_performed);//Undo function save initial state of text before operation
					
					copy_cut_counter=tileNum1-tileNum;//Calculate the number of words user wish to cut
					tempXO_var=tileNum;//keep tilenum in temporary variable
					for (int count=0;count<10;count++)//reset clipboard to empty
					{
						clip_board[count]="";
					}
					for (int count=0;count<=copy_cut_counter;count++)//cut the text onto clipboard
					{
						clip_board[count]=text[tileNum];
						tileNum++;
					}
					tileNum=tempXO_var; //resetting the tile number
					for (int count=0;count<=copy_cut_counter;count++)//Number of delete operation conducted
					{
						for (int count1=tileNum;count1<=textIndex+1;count1++)
						{
							text[count1]=text[count1+1];//replacing the text with the text from the front.Thus "deleting" it.
							textSize[count1]=text[count1].size();//text size are recalibrated accordingly
						}
						textIndex-=1;//to keep track of which cell is empty and which are not
					}
					textSize_max(textSize,maxC); //Comparing the text size according to column and determing the largest size
				}
			}
		}
		
		//***PASTE***//
		else if (response=="P") 
		{
			if (clip_board[0].size()==0) //ERROR CHECKING FOR CLIPBOARD CONTENT
			{
				cout<<"\n###Clipboard is empty.Try copying or cutting first.###\n"<<endl;
			}
			else
			{
							
				cout<<"Tile Number ==> ";
				cin>>tileNum;//To get the tile number from user
				cin.clear();
				cin.ignore(1000,'\n');
				if (tileNum<=textIndex && tileNum>0) //ERROR CHECKING FOR TILENUM
				{
					
					undo_function(textIndex,undo_variable,text,action_performed);//Undo function save initial state of text before operation
					
					while (paste_counter<=copy_cut_counter) //paste_counter is equal to zero
					{
						for (int count=81;count>tileNum;count--) //"Pulls" the text from 81 which contain blank spaces
						{
							text[count]=text[count-1];// The "pull" action
							textSize[count]=text[count].size();//text size are recalibrated accordingly
						}
						paste_counter++;//to keep track of number word shifted	
					}
					for (int count1=0;count1<=copy_cut_counter;count1++)
					{
						text[tileNum]=clip_board[count1]; //replacing initial text with the one on clipboard
						textSize[tileNum]=text[tileNum].size();//text size are recalibrated accordingly
						tileNum++; //tilenum increment to advance to next text array
						textIndex++;//to keep track which cell is empty and which are not
					}
					paste_counter=0;//reset paste_counter to zero for future use
					textSize_max(textSize,maxC); //Comparing the text size according to column and determing the largest size
				}
				else
				{
					cout<<"\n\n###Unable to paste.Out of range.###\n"<<endl;
				}
			}
		}
		
		//***FIND***//
		else if (response=="F") 
		{
			cout<<"Enter text to find: ";
			getline(cin,find_text); //get the text user wish to find
			
		}
		
		//***UNDO***//
		else if (response=="U") 
		{
			for (int count=0;count<10;count++) //reset clipboard to empty
			{
				clip_board[count]="";
			}

			if (action_performed>=0 && action_performed<50) 
			{
				for (int count=0;count<82;count++) //reset text to previous state
				{
					text[count]=undo_variable[action_performed][count];
					textSize[count]=text[count].size();
				}
				for (int count=0;count<82;count++)
				{
					if (text[count]!="     ")
					{
						undo_textIndex+=1;
					}
				}
				textIndex=undo_textIndex; //rest textIndex to previous state
				undo_textIndex=1;
				action_performed-=1;
				textSize_max(textSize,maxC); //Comparing the text size according to column and determing the largest size
			}
			else
			{
				cout<<"\n\n###Unable to perform undo. Performing insert will reset the undo counter###\n"<<endl;
			}
			
		}
		
		
		//***INVALID RESPONSE***//
		else
		{
			cout<<"\n\n###INVALID ACTION###\n"<<endl;
		}		
		
	}	
	
}



//***************************FUNCTIONS***************************//




void get_fileName(string &fileName,int &fileNameSize,string response)
{
	if (response=="S") //different message for save when it calls this function
	{
		cout<<"File name (enter="<<fileName<<") ==> ";
		getline(cin,fileName); //to obtain the file name from user
		fileNameSize=fileName.size(); //getting the size of the file name
		while (fileNameSize==0 || fileNameSize>25) //checking the file name length
		{
			cout<<"The length of the file name is invalid, please reenter.(Between 0-25)\n==> ";
			getline(cin,fileName);//to obtain the file name from user
			fileNameSize=fileName.size();//getting the size of the file name
		}
	}
	else
	{
		cout<<"New file name ==>";
		getline(cin,fileName);//to obtain the file name from user
		fileNameSize=fileName.size();//getting the size of the file name
		while (fileNameSize==0 || fileNameSize>25)
		{
				cout<<"The length of the file name is invalid, please reenter.(Between 0-25)\n==> ";
				getline(cin,fileName);//to obtain the file name from user
				fileNameSize=fileName.size();//getting the size of the file nam
		}
	}
	
}

void display_table(string text[],int maxC[],int &textIndex,string fileName,int textSize[],string &find_text)
{
	
	cout<<"\n--------------------------------- new screen ---------------------------------"<<endl
	      <<"\nFile name : "<<fileName<<endl;
	
	for (int count=1;count<9;count++){     
		if (count==1)
		{
			cout<<"|-----|";
		}
		for (int count2=0;count2<maxC[count];count2++){ 
			cout<<"-";
		}
		if (count==8){                                  
			cout<<"|"<<endl;
		}
		else{
			cout<<"+";                                   
		}
	}

	for (int count=1;count<9;count++){      
		if (count==1){
			cout<<"|     |1";                        
		}
		for (int count2=0;count2<maxC[count]-1;count2++){ 
			cout<<" ";                                   
		}
		if (count==8){
			cout<<"|"<<endl;                                   
		}
		else{
			cout<<"|"<<count+1;                          
		}
	}
	
	for (int count=1;count<9;count++){ 
		if (count==1)
		{
			cout<<"|-----+";
		}

		for (int count2=0;count2<maxC[count];count2++){ 
			cout<<"-";
		}
		if (count==8){                                   
			cout<<"|"<<endl;
		}
		else{
			cout<<"+";                                   
		}
	}
	//00 LINE STARTS
	for (int count=1;count<9;count++){    
		if (count==1)
		{
			cout<<"| 00  |";
		}
		cout<<text[count];
		for (int count2=textSize[count];count2<maxC[count];count2++)
		{
			cout<<" ";
		}

		if (find_text==text[count]) //Compare text with the text user wish to find
		{
			cout<<"=";
		}
		else
		{
			cout<<"|";
		}

		
		if (count==8)
		{
			cout<<endl;
		}
		
	}
	for (int count=1;count<9;count++){ 
		if (count==1)
		{
			cout<<"|-----+";
		}
		for (int count2=0;count2<maxC[count];count2++){
			cout<<"-";
		}
		if (count==8){                                   
			cout<<"|"<<endl;
		}
		else{
			cout<<"+";                                   
		}
	}
	
	//00 LINE END
	
	
	//08 LINE START
	if (textIndex>=8)
	{
		for (int count=9;count<17;count++){    
			if (count==9)
			{
				cout<<"| 08  |";
			}
			cout<<text[count];
		
			for (int count2=textSize[count];count2<maxC[count-8];count2++)
			{
				cout<<" ";
			}
		
			if (find_text==text[count])//Compare text with the text user wish to find
			{
				cout<<"=";
			}
			else
			{
				cout<<"|";
			}
			
			if (count==16)
			{
				cout<<endl;
			}
		}
		
		for (int count=9;count<17;count++){ 
			if (count==9)
			{
				cout<<"|-----+";
			}
			for (int count2=0;count2<maxC[count-8];count2++){
				cout<<"-";
			}
			if (count==16){                                   
				cout<<"|"<<endl;
			}
			else{
				cout<<"+";                                   
			}
		}
	}
	//08 LINE ENDS
	
	//16 LINE STARTS
	if (textIndex>=16)
	{
		for (int count=17;count<25;count++){    
			if (count==17)
			{
				cout<<"| 16  |";
			}
			cout<<text[count];
			for (int count2=textSize[count];count2<maxC[count-16];count2++)
			{
				cout<<" ";
			}
			
			if (find_text==text[count])//Compare text with the text user wish to find
			{
				cout<<"=";
			}
			else
			{
				cout<<"|";
			}
			
			if (count==24)
			{
				cout<<endl;
			}
		}
		
		for (int count=17;count<25;count++){ 
			if (count==17)
			{
				cout<<"|-----+";
			}
			for (int count2=0;count2<maxC[count-16];count2++){
				cout<<"-";
			}
			if (count==24){                                   
				cout<<"|"<<endl;
			}
			else{
				cout<<"+";                                   
			}
		}
	}
	//16 LINE ENDS
	
	//24 LINE STARTS
	if (textIndex>=24)
	{
		for (int count=25;count<33;count++){    
			if (count==25)
			{
				cout<<"| 24  |";
			}
			cout<<text[count];
			for (int count2=textSize[count];count2<maxC[count-24];count2++)
			{
				cout<<" ";
			}
			
			if (find_text==text[count])//Compare text with the text user wish to find
			{
				cout<<"=";
			}
			else
			{
				cout<<"|";
			}
			
			if (count==32)
			{
				cout<<endl;
			}
		}
		
		for (int count=25;count<33;count++){ 
			if (count==25)
			{
				cout<<"|-----+";
			}
			for (int count2=0;count2<maxC[count-24];count2++){
				cout<<"-";
			}
			if (count==32){                                   
				cout<<"|"<<endl;
			}
			else{
				cout<<"+";                                   
			}
		}
	}
	//24 LINE ENDS
	
	//32 LINE STARTS
	if (textIndex>=32)
	{
		for (int count=33;count<41;count++){    
			if (count==33)
			{
				cout<<"| 32  |";
			}
			cout<<text[count];
			for (int count2=textSize[count];count2<maxC[count-32];count2++)
			{
				cout<<" ";
			}
			
			if (find_text==text[count])//Compare text with the text user wish to find
			{
				cout<<"=";
			}
			else
			{
				cout<<"|";
			}
			
			if (count==40)
			{
				cout<<endl;
			}
		}
		
		for (int count=33;count<41;count++){ 
			if (count==33)
			{
				cout<<"|-----+";
			}
			for (int count2=0;count2<maxC[count-32];count2++){
				cout<<"-";
			}
			if (count==40){                                   
				cout<<"|"<<endl;
			}
			else{
				cout<<"+";                                   
			}
		}
	}
	//32 LINE ENDS
	
	//40 LINE STARTS
	if (textIndex>=40)
	{
		for (int count=41;count<49;count++){    
			if (count==41)
			{
				cout<<"| 40  |";
			}
			cout<<text[count];
			for (int count2=textSize[count];count2<maxC[count-40];count2++)
			{
				cout<<" ";
			}
			
			if (find_text==text[count])//Compare text with the text user wish to find
			{
				cout<<"=";
			}
			else
			{
				cout<<"|";
			}
			
			if (count==48)
			{
				cout<<endl;
			}
		}
		
		for (int count=41;count<49;count++){ 
			if (count==41)
			{
				cout<<"|-----+";
			}
			for (int count2=0;count2<maxC[count-40];count2++){
				cout<<"-";
			}
			if (count==48){                                   
				cout<<"|"<<endl;
			}
			else{
				cout<<"+";                                   
			}
		}
	}
	//40 LINE ENDS
	
	//48 LINE STARTS
	if (textIndex>=48)
	{
		for (int count=49;count<57;count++){    
			if (count==49)
			{
				cout<<"| 48  |";
			}
			cout<<text[count];
			for (int count2=textSize[count];count2<maxC[count-48];count2++)
			{
				cout<<" ";
			}
			if (find_text==text[count])//Compare text with the text user wish to find
			{
				cout<<"=";
			}
			else
			{
				cout<<"|";
			}
			
			if (count==56)
			{
				cout<<endl;
			}
		}
		
		for (int count=49;count<57;count++){ 
			if (count==49)
			{
				cout<<"|-----+";
			}
			for (int count2=0;count2<maxC[count-48];count2++){
				cout<<"-";
			}
			if (count==56){                                   
				cout<<"|"<<endl;
			}
			else{
				cout<<"+";                                   
			}
		}
	}
	//48 LINE ENDS
	
	//56 LINE STARTS
	if (textIndex>=56)
	{
		for (int count=57;count<65;count++){    
			if (count==57)
			{
				cout<<"| 56  |";
			}
			cout<<text[count];
			for (int count2=textSize[count];count2<maxC[count-56];count2++)
			{
				cout<<" ";
			}
			
			if (find_text==text[count])//Compare text with the text user wish to find
			{
				cout<<"=";
			}
			else
			{
				cout<<"|";
			}
			
			if (count==64)
			{
				cout<<endl;
			}
		}
		
		for (int count=57;count<65;count++){ 
			if (count==57)
			{
				cout<<"|-----+";
			}
			for (int count2=0;count2<maxC[count-56];count2++){
				cout<<"-";
			}
			if (count==64){                                   
				cout<<"|"<<endl;
			}
			else{
				cout<<"+";                                   
			}
		}
	}
	//56 LINE ENDS
	
	//64 LINE STARTS
	if (textIndex>=64)
	{
		for (int count=65;count<73;count++){    
			if (count==65)
			{
				cout<<"| 64  |";
			}
			cout<<text[count];
			for (int count2=textSize[count];count2<maxC[count-64];count2++)
			{
				cout<<" ";
			}
			
			if (find_text==text[count])//Compare text with the text user wish to find
			{
				cout<<"=";
			}
			else
			{
				cout<<"|";
			}
			
			if (count==72)
			{
				cout<<endl;
			}
		}
		
		for (int count=65;count<73;count++){ 
			if (count==65)
			{
				cout<<"|-----+";
			}
			for (int count2=0;count2<maxC[count-64];count2++){
				cout<<"-";
			}
			if (count==72){                                   
				cout<<"|"<<endl;
			}
			else{
				cout<<"+";                                   
			}
		}
	}
	//64 LINE ENDS
	
	//72 LINE STARTS
	if (textIndex>=72)
	{
		for (int count=73;count<81;count++){    
			if (count==73)
			{
				cout<<"| 72  |";
			}
			cout<<text[count];
			for (int count2=textSize[count];count2<maxC[count-72];count2++)
			{
				cout<<" ";
			}
			
			if (find_text==text[count])//Compare text with the text user wish to find
			{
				cout<<"=";
			}
			else
			{
				cout<<"|";
			}
			
			if (count==80)
			{
				cout<<endl;
			}
		}
		
		for (int count=73;count<81;count++){ 
			if (count==73)
			{
				cout<<"|-----+";
			}
			for (int count2=0;count2<maxC[count-72];count2++){
				cout<<"-";
			}
			if (count==80){                                   
				cout<<"|"<<endl;
			}
			else{
				cout<<"+";                                   
			}
		}
	}
	//72 LINE ENDS
	find_text="NULL@!";//reset find_text to ensure the "=" dissapear after appearing once and not stick around
}




void textSize_max(int textSize[],int maxC[])
{
	for (int count=1;count<=8;count++) //initializing the values to 5
	{
		maxC[count]=5;
	}
	
	for (int count=1;count<=73;count+=8) //compare all textSize of text from column 1 and setting it as max
	{
		if (textSize[count]>maxC[1])
		{
			maxC[1]=textSize[count];
		}
	}
				
	for (int count=2;count<=74;count+=8)//compare all textSize of text from column 2 and setting it as max
	{
		if (textSize[count]>maxC[2])
		{
			maxC[2]=textSize[count];
		}
	}
				
	for (int count=3;count<=75;count+=8)//compare all textSize of text from column 3 and setting it as max
	{
		if (textSize[count]>maxC[3])
		{
			maxC[3]=textSize[count];
		}
	}
				
	for (int count=4;count<=76;count+=8)//compare all textSize of text from column 4 and setting it as max
	{
		if (textSize[count]>maxC[4])
		{
			maxC[4]=textSize[count];
		}
	}
				
	for (int count=5;count<=77;count+=8)//compare all textSize of text from column 5 and setting it as max
	{
		if (textSize[count]>maxC[5])
		{
			maxC[5]=textSize[count];
		}
	}
				
	for (int count=6;count<=78;count+=8)//compare all textSize of text from column 6 and setting it as max
	{
		if (textSize[count]>maxC[6])
		{
			maxC[6]=textSize[count];
		}
	}
				
	for (int count=7;count<=79;count+=8)//compare all textSize of text from column 7 and setting it as max
	{
		if (textSize[count]>maxC[7])
		{
			maxC[7]=textSize[count];
		}
	}
				
	for (int count=8;count<=80;count+=8)//compare all textSize of text from column 8 and setting it as max
	{
		if (textSize[count]>maxC[8])
		{
			maxC[8]=textSize[count];
		}
	}
}

void load_function(string &fileName,string text[],int textSize[],int &textIndex,int load_counter,int &status0,int maxC[])
{
	cout<<"File name ==> ";
	getline(cin,fileName);
	ifstream the_file_load;
	the_file_load.open(fileName.c_str());
			
	if (the_file_load.fail()) //if file cannot be found
	{
		cout<<"###File cannot be found!###"<<endl;
		status0=0;
	}
	else
	{
			for (int count=0;count<82;count++) 
			{
				text[count]="     ";
				textSize[count]=5;
			}
			
			for (int count=0;count<9;count++)
			{
				maxC[count]=5;
			}
		status0=1; //to exit the initial while loop at the start of the program
		textIndex=0;//reset textIndex to 0
		load_counter=1; //increment to advance to next text array
		while (!the_file_load.eof()) //while it does not equals to the end of file, it continues reading text from the file and assigning them into text array
		{
			the_file_load>>text[load_counter];
			textSize[load_counter]=text[load_counter].size();//text size are recalibrated
			textIndex+=1; //to keep track of which cell is empty and which are not
			load_counter+=1;//increment to advance to the next text array				
		}
		the_file_load.close();//closing file to avoid error
		cout<<"------------------------ "<<fileName<<" for reference ------------------------\n\n"<<endl;
		for (int count=1;count<82;count++)
		{
			cout<<text[count]<<" ";
			if (count==20||count==40||count==60||count==80)//make the "text for reference" more tidy by line spaces
			{
				cout<<endl;
			}
				
		}
		cout<<endl<<endl;
	}
}

void undo_function(int textIndex,string undo_variable[50][82],string text[],int &action_performed)
{
	if (action_performed<49)
	{
		action_performed+=1; //setting it so that undo operation will not trigger error message
		for (int count=0;count<82;count++)//to keep previous state of text array
		{
			undo_variable[action_performed][count]=text[count];
		}
	}
	else
	{
		cout<<"### Undo threshold limit have exceeded. Resetting undo counter. ###"<<endl;
		action_performed=-1;
	}
		
}


