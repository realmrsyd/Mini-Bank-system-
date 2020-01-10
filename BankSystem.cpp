#include <iostream>
#include <cstdio>
// <cstdlib> and <ctime> libraries for using srand() and rand() to get random numbers
// taken from the reference below:
// taken from http://www.dreamincode.net/forums/topic/14057-producing-random-numbers/
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	// Jack is the number of 5cents that are available, Ace for 10c, Queen for 20c, and King for 50c
	int Jack,Ace,Queen,King;
	float Total,Withdraw;
	char choice;
	bool Rest=true,Exit=false;
	// starting the First screen
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
		 << "@@@@@@ W E L C O M E  T O  J A Q K  P o t @@@@@@\n"
		 << "@@@@@@@@@@@@@@@@@@@@@@     @@@@@@@@@@@@@@@@@@@@@\n"
		 << "@@@@@@@@@@@@@@@@@@@@@@ B Y @@@@@@@@@@@@@@@@@@@@@\n"
		 << "@@@@@@@@@@@@@@@@@@@@         @@@@@@@@@@@@@@@@@@@\n"
		 << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
	
	do
	{
	system("pause"); // waiting the user to enter any key ...
	system("cls"); // clearing the screen
	if(Rest==true) // producing new random numbers only if it's the first time or the user choose to rest
	{
		Rest = false;
		srand(time(NULL)); // taken from http://www.dreamincode.net/forums/topic/14057-producing-random-numbers/
		
		King=rand()%10+1; // getting random number from 1 to 10, where "King" is number of 50 cents available
		if(King!=10) // because only 10 random coins the program must starts with.
			Queen = rand()%(10-King);
		else
			Queen = 0;
		if(Queen!=0)
			Ace = rand()%Queen;
		else
			Ace = 0;
		Jack = abs(10-King-Queen-Ace);
	}
	
	Total = Jack*0.05 + Ace*0.1 + Queen*0.2 + King*0.5; // calculating the balance
	//Showing the Main Enterface
	cout << "\t..: JAQK POT :..\n"
		 << "********************************\n"
		 << "Jack\tAce\tQueen\tKing\n"
		 << "5c\t10c\t20c\t50c\n"
		 << Jack << "\t" << Ace << "\t" << Queen << "\t" << King << "\n\n"
		 << "Total = RM " << Total << "\n\n"
		 << "Press D or d if you want to deposit.\n"
		 << "Press W or w if you want to withdraw.\n"
		 << "Press R or r if you want to reset.\n"
		 << "Press N or n to exit the program."
		 << "==> ";
	cin >> choice;
	int input;
	switch(choice)
	{
		case 'd': // if user entered "d" in small-case letter
		case 'D':{ // OR "D" in Capital-case
			cout << "How many 50c coins? =>";
			cin >> input;
			if(input>=0)
			{
				King += input; // adding the 50 cent coints if the user entered positive number
				cout << "How many 20c coins? =>";
				cin >> input;
				if(input>=0)
				{
					Queen +=input;
					cout << "How many 10c coins? =>";
					cin >> input;
					if(input>=0)
					{
						Ace += input;
						cout << "How many 5c coins? =>";
						cin >> input;
						if(input>=0)
							Jack += input;
						else
							cout << "ERROR: Invalid input!\n";
					}
					else
						cout << "ERROR: Invalid input!\n";
				}
				else
					cout << "ERROR: Invalid input!\n";
			}
			else
				cout << "ERROR: Invalid input!\n"; // showing error then restarting the Main Enterface but without resting it
			break;
		}
		case 'w':
		case 'W':{
			cout << "Please enter the amount (in RM) =>";
			cin >> Withdraw;
			if(Withdraw>0)
			{
				if(Withdraw<=Total) // checking the available balance
				{
					Withdraw *= 100; // converting from ringgit to cents
					float Orginal_Withdraw = Withdraw; // making copy of total desired withdraw
					// Greedy approach on coins {50, 20, 10, 5}
					int desired50=Withdraw/50;
					if (desired50 > King)
					desired50 = King;
					Withdraw -= desired50 * 50;
					
					int desired20=Withdraw/20;
					if (desired20 > Queen)
						desired20 = Queen;
					Withdraw -= desired20 * 20;
					
					int desired10=Withdraw/10;
					if (desired10 > Ace)
						desired10 = Ace;
					Withdraw -= desired10 * 10;
					
					int desired05=Withdraw/5;
					if (desired05 > Jack)
						desired05 = Jack;
					Withdraw -= desired05 * 5;
					
					if (Withdraw > 0) // still remaining withdraw, Thus Greedy {50, 20, 10, 5} DON'T WORK
					{
						// Retry Greedy approach on {20, 10, 5} and Starting from one less 50cent coin
						desired50--;
						Withdraw = Orginal_Withdraw - desired50 * 50;
						
						desired20 = Withdraw / 20;
						if (desired20 > Queen)
							desired20 = Queen;
						Withdraw -= desired20 * 20;
						
						desired10 = Withdraw / 10;
						if (desired10 > Ace)
							desired10 = Ace;
						Withdraw -= desired10 * 10;
						
						desired05 = Withdraw /  5;
						if (desired05 > Jack)
							desired05 = Jack;
						Withdraw -= desired05 * 5;

						if (Withdraw > 0) // still remaining withdraw, Thus Greedy {20, 10, 5} DON'T WORK
						{
							// Retry Greedy approach on {10, 5} and Starting from one less 20cent coin
							desired20--;
							Withdraw = Orginal_Withdraw-desired50*50-desired20*20;
	
							desired10 = Withdraw / 10;
							if (desired10 > Ace)
								desired10 = Ace;
							Withdraw -= desired10 * 10;
							
							desired05 = Withdraw /  5;
							if (desired05 > Jack)
								desired05 = Jack;
							Withdraw -= desired05 * 5;
							
							if (Withdraw > 0) // still remaining withdraw, Thus Greedy {10, 5} DON'T WORK
							{
								// Retry Greedy approach on {5}s and Starting from one less 10cent coin
								desired10--;
								Withdraw = Orginal_Withdraw-desired50*50-desired20*20-desired10*10;
								
								desired05 = Withdraw /  5;
								if (desired05 > Jack)
									desired05 = Jack;
								Withdraw -= desired05 * 5;
								
								if (Withdraw > 0)  // still remaining withdraw, Thus Greedy {5}s DON'T WORK
								{
									cout << "Insufficient coins" << endl;	
								}
								else //Thus Greedy {5}S SUCCESSFULLY WORKED
								{
									cout << "Yes, please collect your coins:\n"
										 << "50c x " << desired50<<"\n"
										 << "20c x " << desired20 << "\n"
										 << "10c x " << desired10 << "\n"
										 << "05c x " << desired05 << "\n";
									//updating the balance
									King -= desired50;
									Queen -= desired20;
									Ace -= desired10;
									Jack -= desired05;
								}
							}
							else //Thus Greedy {10, 5} SUCCESSFULLY WORKED
							{
								cout << "Yes, please collect your coins:\n"
									 << "50c x " << desired50<<"\n"
									 << "20c x " << desired20 << "\n"
									 << "10c x " << desired10 << "\n"
									 << "05c x " << desired05 << "\n";
								King -= desired50;
								Queen -= desired20;
								Ace -= desired10;
								Jack -= desired05;
							}
						}
						else //Thus Greedy {20, 10, 5} SUCCESSFULLY WORKED
						{
							cout << "Yes, please collect your coins:\n"
								 << "50c x " << desired50<<"\n"
								 << "20c x " << desired20 << "\n"
								 << "10c x " << desired10 << "\n"
								 << "05c x " << desired05 << "\n";
							King -= desired50;
							Queen -= desired20;
							Ace -= desired10;
							Jack -= desired05;
						}
					}
					else //Thus Greedy {50,20, 10, 5} SUCCESSFULLY WORKED
					{
						cout << "Yes, please collect your coins:\n"
							 << "50c x " << desired50<<"\n"
							 << "20c x " << desired20 << "\n"
							 << "10c x " << desired10 << "\n"
							 << "05c x " << desired05 << "\n";
						King -= desired50;
						Queen -= desired20;
						Ace -= desired10;
						Jack -= desired05;
					}
						
				}
				else
					cout << "Sorry, insufficient coin. Transaction cancelled.\n";
			}
			else
				cout << "ERROR: Invalid input!\n";
			break;
		}
		case 'r':
		case 'R':{
			Rest=true;
			cout << "you are about to rest the program, ";
			break;
		}
		case 'n':
		case 'N':{
			Exit=true;
			break;
		}
		default:
			cout << "ERROR: Invalid input!\n";
	}
	} while(Exit==false); // the user didn't Enter "N" to Exit
}
