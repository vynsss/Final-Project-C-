//reference: https://www.sanfoundry.com/cpp-program-hash-tables-singly-linked-list/

#include <iostream>
#include <cstring>
#include <cstdint>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

struct hashTable
{
    string key;
    string value;
    string email;
    bool isEmpty = true;
    hashTable *next;
};

//validation
bool name_validation(string name)
{
	if(name.length() >= 2) return true;
	else
	{
		cout << "     \nYou have to input 2 letters at least!\n" << endl;
		return false;
	}
	return false;
}

bool email_validation(string email)
{
	if(email.find("@") != std::string::npos && email.find(".co") != std::string::npos && email.length() >=5 ) return true;

	else
	{
		cout << "	\nInvalid email format! Please try again\n" << endl;
		return false;
	}
	return false;
}

bool number_validation(string number)
{
	if(number.length() > 10)
	{
		int check = 0;
		for(int i = 0; i < number.length(); i++)
		{
			if(number[i] >= '0' && number[i] <= '9') check++;
		}
		
		if(number.length() == check) return true;
		else
		{
			cout << "    \nMake sure all of 'em are digits!\n" << endl;
		}
		return false;
	}
	else 
	{
		cout << "    Make sure you have the correct length of number!\n    The minimum number is 9 digits!\n" << endl;
		return false;
	}
	return false;
}


class Contacts
{
    int num = 10;        																								// number of entries
    hashTable *phoneBook;
    int no_contact = 0;
    
    public:
    
    Contacts():phoneBook(NULL)
    {
		phoneBook = new hashTable[num];
    }

    void insert()
    {
        int index;
        string phoneNumber;
        string name;
        string email;
        
    	cout << "\nContact #" << no_contact + 1 << endl;
    	
    	while(true)
    	{
    		cout << "Enter the name: " << endl;
        	cin.ignore();
			cin >> name;
        	
        	if(name_validation(name)) break;
			else continue;
		}
		
		while(true)
		{
			cout << "Enter the phone number: " << endl;
			cin >> phoneNumber;
			
			if(number_validation(phoneNumber)) break;
			else continue;
		}
		
		while(true)
		{
			cout << "Enter the email: " << endl;
			cin >> email;
			
			if(email_validation(email)) break;
			else continue;
		}
		
        index = hashing(name, num);
        
        if(phoneBook[index].isEmpty)
        {        																								// if the slot is empty(no collision)...
            phoneBook[index].key = name;
            phoneBook[index].value = phoneNumber;
            phoneBook[index].email = email;
            phoneBook[index].isEmpty = false;				 													// done
            phoneBook[index].next = NULL;
        }
        else
        { 																										// in case of collision...
            hashTable *temp =&(phoneBook[index]);
            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new hashTable;
            temp->next->key = name;
            temp->next->value = phoneNumber;
            temp->next->email = email;
			temp->next->isEmpty = false;
            temp->next->next = NULL;
            
        }
        no_contact++;
    	//sort(phoneBook->key[0], phoneBook->key[no_contact]);
    	cout << "\n          :: HOORAY! :: \n     A new contact has been added!" << endl;
    }
    
    
    int hashing(string name, int n)
    {
        int len;
		int sum = 0;
		
        // converting string into char array...
        
        len = name.length();
        char temp[len+1];
        strcpy(temp, name.c_str());
        
        // calculating hash value...
        
        for(int i=0; i<len; i++)
        {
            sum = sum + temp[i];
        }
        return (sum%n);
    }
    
    
    void searchContact(string name)
    {
        int check;
        string email;
        check = hashing(name, num);
		
		cout << ">";
		sleep_for(seconds(1));
		cout << " >";
		sleep_for(seconds(1));
		cout << " >";
		sleep_for(seconds(1));
		cout << " >";
		sleep_for(seconds(1));
        if(phoneBook[check].next == NULL)
        {       																					 // if there is no collision seen in the current block..
			
			if(phoneBook[check].key == name)
            {
            	cout << "\nHere's what I found.. \n\n";
                cout << "Name		: " << phoneBook[check].key << endl;
                cout << "Email		: " << phoneBook[check].email << endl;
                cout << "Phone number	: " << phoneBook[check].value << "\n" << endl;
			}
            else
            {
                cout << "\n*** Whoops... \n Contact not found \n***" << endl;
            }
        }

        else
        {                                   														// if collision is seen in the current block...
            hashTable *temp =& (phoneBook[check]);
            while(temp != NULL)
            {
                if(temp->key == name)
                {
                	cout << "\nHere's what I found.. \n\n";
                    cout << "Name		: " << temp->key << endl;
                    cout << "Email		: " << temp->email << "\n" << endl;
                    cout << "Phone number	: " << temp->value << "\n" << endl;
                    break;
                }
                else
                {
                    temp = temp->next;
            	}
			}
            if(temp == NULL)
            {
                cout << "***\n Whoops... \n Contact not found \n***" << endl;
    		}
		}
    }
    
    void delete_contact(string name)
    {
		int check;
        check = hashing(name, num);
        hashTable *curr =& (phoneBook[check]);
        if(no_contact <= 0)
        {
            cout << "***\n Whoops... \n Contact not found \n***" << endl;
		}
    	else if(curr->key == name)
    	{
    		phoneBook[check].isEmpty = true;
		}
		else{
            hashTable *temp = curr->next;
            while(curr != NULL)
            {
            	cout << "loop loop loop" << endl;
                if(temp->key == name)
                {
                	curr->next = temp->next;
            		temp->isEmpty = true;
            		break;
                }
                curr = curr->next;
                temp = curr->next;
			}
    	}
	    no_contact--;
    }
    
    void view()
	{
		cout << endl;

		int counter = 0;
		if(no_contact > 0)
		{
			cout << "--------------------------------------" << endl;
			for(int i = 0; i < num; i++)
			{
				hashTable *temp =& phoneBook[i];
				if(!temp->isEmpty)
				{
					do
					{	
						cout << "Contact #" << counter + 1 << endl;
						cout << "Name		: " << temp->key << endl;
						cout << "Email		: " << temp->email << endl;
						cout << "Phone number	: " << temp->value << "\n" << endl;
						cout << "--------------------------------------" << endl;
						temp = temp->next;
						counter++;
					}
					while(temp != NULL);
				}
			}
		}
		
		else cout << "\nNothing...\nJust nothingness..." << endl;
	}
	
    void store()
	{
		int counter = 0;
		if(no_contact > 0)
		{
			cout << " Preparing to Save" << endl;
			sleep_for(seconds(2));
			cout << " Opening the file.." << endl;
			
			const char *filename = "myCONTACTS.txt";
			FILE *f = fopen(filename, "w");
			
			fprintf(f, "\n~~~ My Lovely Contacts ~~~\n");
			fprintf(f, " ----- \n");
			for (int i = 0; i < num; i++)
			{
				hashTable *temp =& phoneBook[i];
				if(!temp->isEmpty)
				{
					do
					{
						sleep_for(seconds(1));
						cout << "\n Inserting data #" << counter + 1 << "..";
						fprintf(f, "\nName: %s ", temp->key.c_str());
					    fprintf(f, "\n[%s]", temp->email.c_str());
				        fprintf(f, "\nPhone: %s ", temp->value.c_str());
			        	fprintf(f, "\n------");
			        	counter++;
						temp = temp->next;
					}
					while(temp != NULL);
				}
			}
			fprintf(f, "\n--- End of contact ---");
			
			sleep_for(seconds(1));
			cout << " \n Closing the file.." << endl;
			fclose(f);
			
			sleep_for(seconds(2));
			cout << "\n\n		:: SUCCESS! ::\nYour contacts have been saved!" << endl;
		}
		else
		{
			cout << "\nThere is nothing to save.." << endl;
		}
	}

    ~Contacts()
    {
        delete []phoneBook;
    }
    
};


int main()
{
    string name;
    string delname;
    int n;
    int choice;
    
    Contacts newContactbook;
    
    while(true)
    {
    	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~CONTACT BOOK~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "What do you want to do..?\n" << endl;
		cout << "[1] Add contact" << endl;
		cout << "[2] Remove a contact" << endl;
		cout << "[3] Search a contact by name" << endl;
		cout << "[4] View your contact" << endl;
		cout << "[5] Save your contact" << endl;
		
		cout << "\n[0] Exit" << endl;
		cout << "============================================================" << endl;
		cout << "Input: ";
	
		cin >> choice;
	    switch(choice)
	    {
	    	case 0:
	    		cout << "\nByee.." << endl;
	    		exit(0);
	    		
	    	case 1:
	    		newContactbook.insert();
	    		break;
	    	
			case 2:
				cout << "\nEnter the name of the contact: " << endl;
				cin >> delname;
				newContactbook.delete_contact(delname);
	    		break;
	    		
	    	case 3:
	    		cout << "\nEnter name to search: " << endl;
			    cin >> name;
			    newContactbook.searchContact(name);
			    break;
			    
			case 4:
				newContactbook.view();
				break;   	
	
			case 5:
				newContactbook.store();
				break;
	
			default:
				cout << "\nInvalid input..\n";
				break;
		}
	}
	
    return 0;
    
}
