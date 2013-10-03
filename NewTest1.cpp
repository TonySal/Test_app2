#include "parse.cpp"
#include <map>
#include <fstream>
#include <vector>
#include <string>
int main()
{ 
	printf("Welcome to the TonySal test task. \n");
	printf("If you need help just put down commend 'help'\n");
    printf("Enter command: ");
	string cmd, name, text;
	int index, rel, id, parentId;
	bool success = false;
	
	
	
	//array to add node
	map< int, map < string, string > > book;
	map< int, map < string, string > > book2;
	
	//init Parse object
	Parse parse;
	
	//filename to save current node state
	string filename = "stream.txt";
	
	while( cin >> cmd ) {
    	if ( cmd == "add"  ) {
			//add node to array
			while (!success){
                  cout << "Enter id: ";
                  cin >> id;
                  if(cin.good())
                  {
                  //success = true;
            cout << "Content: ";
  			cin >> name;
  			//cin >> rel;
  			int bCount = 0;
            //if(book.size() > 2) {
            //    bCount = book.size() / 2;
            //} else {
                bCount = book.size();
            //}
            book[bCount]["content"] = name;
            book[bCount]["id"] = parse.IntToStr(id);
                        
            cout << "Created" << endl;
            cin.clear();
            printf("\nEnter command: ");
            break;
             }
            else{
                 cout << "Wrong input! Try again: \n";
                 success = false;
                 cin.clear();
                 _flushall();
                 }}
              } else if ( cmd == "create_node"  ) {
			//add node to array
			
            
            while (!success){
                cout << "Parent id: ";
                cin >> parentId;
                cout << "Child id: ";
                cin >> index;
                if(cin.good())
                  {
                  //success = true;
                  cout << "Content: ";
  			cin >> text;
  			int b2Count = 0;
            b2Count = book2.size();
            
  			book2[b2Count]["content"] = text;
            book2[b2Count]["id"] = parse.IntToStr(index);
            book2[b2Count]["parent"] = parse.IntToStr(parentId);
            cout << "Created" << endl;
            cin.clear();
            printf("\nEnter command: ");
            break;
             }
            else{
                 cout << "Wrong input! Try again: \n";
                 success = false;
                 cin.clear();
                 _flushall();
                 }}
        } else if (cmd == "open") {
			// get content node from file
			
            char* buff=NULL;
            int length;
            ifstream is;
            is.open ("stream.txt", ios::in );

            // get length of file:
            is.seekg (0, ios::end);
            length = is.tellg();
            is.seekg (0, ios::beg);
            
            buff = new char [length];
            // read data as a block:
            is.read (buff,length);
            is.close();
            
            cout.write (buff,length);
            delete[] buff;
            buff = NULL; 
            
            
			/* string contentSource = parse.open(filename);
			cout << contentSource;*/
			printf("\n \nEnter command: ");
        } else if ( cmd == "save" ) {
            int bCount = 0;
            int b2Count = 0;  
            bCount = book.size();              
            b2Count = book2.size();
            
			//build node state
			//save current node state to file
			
            string buildStringRelation("");

            
            for(int j = 0; j < bCount; j++) {
              buildStringRelation.append("\n");
	          buildStringRelation.append(" ");
              buildStringRelation.append(book[j]["id"]);
              buildStringRelation.append(" ");
              buildStringRelation.append(book[j]["content"]);

              for(int a = 0; a < b2Count; a++) {
                   if(book[j]["id"] == book2[a]["parent"]) {
    	               buildStringRelation.append("\n ");
                       buildStringRelation.append(" ");
                       buildStringRelation.append(book2[a]["id"]);
                       buildStringRelation.append("  ");
                       buildStringRelation.append(book2[a]["content"]);
                       //buildStringRelation.append("\n");
                    }
               }
              
            }         
            bool isSave = parse.save(filename, buildStringRelation);
            if(isSave) {
            	cout << "Save was success!\n";
            	printf("\nEnter command: ");
            } else {
        		cout << "Save was not success!\n";
        		printf("\nEnter command: ");
            }
        } else if ( cmd == "delete" ){
			//delete element from array
            cin >> id;
            int bCount = 0;
            int b2Count = 0; 
            bCount = book.size();    
            b2Count = book2.size();
            
            
            for(int j = 0; j < bCount; j++) {
                if(book[j]["id"] == parse.IntToStr(id)) {
                    book.erase( j );
                    for(int a = 0; a < b2Count; a++) {
                        if(book2[a]["parent"] == parse.IntToStr(id)) {
                            book2.erase( a );
                            break;    
                        }
                    }
                    break;   
                }
            }
            cout << "Deleted" << endl;
            printf("\nEnter command: ");
    	} else if ( cmd == "delete_node" ){
			//delete element from array
            cin >> index;
            int bCount2 = 0; 
            bCount2 = book2.size();
            
            
            for(int j = 0; j < bCount2; j++) {
                if(book2[j]["id"] == parse.IntToStr(index)) {
                    book2.erase( j );
                    break;    
                }
            }
            cout << "Deleted" << endl;
            printf("\nEnter command: ");
    	} else if ( cmd == "show" ) {
			//show tree of elements
            map< int, string >::const_iterator i;
            int b2Count = 0;
            int bCount = 0;
            bCount = book.size();
            b2Count = book2.size();
            
            
            for(int j = 0; j < bCount; j++)
            {
                cout << book[j]["id"];
                cout << " " << book[j]["content"] << endl;
                 for(int h = 0; h < b2Count; h++)
                {
                    if(book[j]["id"] == book2[h]["parent"])
                    {
                        cout << "  " << book2[h]["id"];
                        cout << " " << book2[h]["content"] << endl;  
                    }
                }
            }
              printf("\nEnter command: ");
        } else if ( cmd == "help") {
          printf("  add - create main node.\n");
          printf("  create_node - create node.\n");
          printf("  show - show all created node.\n");
          printf("  delete - delete main node.\n");
          printf("  delete_node - delete node.\n");
          printf("  save - saved books to the stream.txt .\n");
          printf("  open - show all saved nodes on a console.\n");
          printf("  quit - exit console.\n");
          printf("\nEnter command: ");
        } else if ( cmd == "quit") {
			//exit
          	return 0;
        } else {
          	cerr << "Bad command '" << cmd << "'" << endl;
          	printf("\nEnter command: ");
        }   
    } // while( cin >> cmd )
 
    return 0;
} 
