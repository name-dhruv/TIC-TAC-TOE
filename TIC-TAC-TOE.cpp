#include <iostream>
using namespace std;

void display(char (&grid)[3][3]){ // function to display the grid

	cout<<"\n";

	for(int a=0;a<9;++a)
		cout<<'-';
	cout<<"\n";
	
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			if(j!=2) // to not put "|" after the last column
				cout<<grid[i][j]<<" | "; 
			else{
				cout<<grid[i][j];
			}
		}
		cout<<'\n';
			for(int a=0;a<9;++a){
				cout<<'-'; // separating the rows with "-"
			}
		cout<<'\n';
	}
	cout<<"\n\n";

}

// to check if row,col is a corner
bool is_corner(char(&grid)[3][3],int row,int col){

	if(row==0 && (col==0 || col==2))return true;

	if(row==2 && (col==0 || col==2))return true;

	return false;
}

// to check if there is any free corner left
bool corner_check(char (&grid)[3][3],char cpu){

	if(grid[0][0]==' '){ // top left
		grid[0][0]=cpu;
		return true;
	}

	else if(grid[2][2]==' '){ // bottom right
		grid[2][2]=cpu;
		return true;
	}

	else if(grid[0][2]==' '){ // top right
		grid[0][2]=cpu;
		return true;
	}

	else if(grid[2][0]==' '){ // bottom left
		grid[2][0]=cpu;
		return true;
	}
	return false;
}

//to check if there is any free place left in some edge centre
bool edge_check(char (&grid)[3][3],char cpu){
	
	if(grid[0][1]==' '){ // top middle
		grid[0][1]=cpu;
		return true;		
	}

	if(grid[1][0]==' '){ // left middle
		grid[1][0]=cpu;
		return true;		
	}

	if(grid[1][2]==' '){ // right middle
		grid[1][2]=cpu;
		return true;		
	}

	if(grid[2][1]==' '){ //bottom middle
		grid[2][1]=cpu;
		return true;		
	}

	return false;
}


bool won(char (&grid)[3][3],char user){ // function to check if the cpu has won,i.e a complete row/column/diagonal with cpu's symbol is achived
										// we can replace user with cpu's character as an input to it and this function will give us if user has won 
	
	bool has_won=false; // variable to check if cpu has won
	
	char cpu='O';
	
	if(user=='O'){
		cpu='X'; // as cpu is oppsite of user
	}
	
	if(grid[0][0]==cpu && grid[0][0]==grid[1][1] &&grid[1][1]==grid[2][2]){ // diagonal going down from (0,0)
		has_won=true;
		return has_won;
	}

	if(grid[2][0]==cpu &&grid[2][0]==grid[1][1] &&grid[1][1]==grid[0][2]){ // diagonal going up from (2,0)
		has_won=true;
		return has_won;
	}

	for(int i=0;i<3;++i){
		if(grid[i][0]==cpu &&grid[i][0]==grid[i][1] &&grid[i][1]==grid[i][2]){ // checking rows
			has_won=true;
			return has_won;
		}	
	}

	for(int i=0;i<3;++i){
		if(grid[0][i]==cpu && grid[0][i]==grid[1][i] &&grid[1][i]==grid[2][i]){ // checking column
			has_won=true;
			return has_won;
		}	
	}

	return(has_won);
}


bool can_loose(char (&grid)[3][3],char cpu,char user){ // function to check if the user is just about to win, and if yes we prevent it from winning by placing cpu's symbol there

	for(int i=0;i<3;++i){ // iterate in all rows
		for(int j=0;j<3;++j){ //iterate in all column
			if(grid[i][j]==' '){ // first the position must not be already used
				grid[i][j]=user;  // to check if the user place his next move here can he win the game,so we put user here
				if(won(grid,cpu)){ // check if the user has won?
					grid[i][j]=cpu; // if user has won we put cpu's symbol there to prevent user from winning
					return true;    // return true...i.e cpu could have lost but we prevent it
				}
				grid[i][j]=' '; // if we comes out of if condition, it means the user can't win by placing his symbol there, revert the placing of user here,i.e clear it again
			}
		}
	}
	return false; // if we can't find any vaild position that can make user win we return false
}


bool can_win(char (&grid)[3][3],char cpu,char user){ //function to check if the cpu can win by placing his symbol somewhere


	for(int i=0;i<3;++i){ // iterate in all rows
		for(int j=0;j<3;++j){ //iterate in all columns
			if(grid[i][j]==' '){ // first find the valid position to place symbol
				grid[i][j]=cpu; // to check if placing here we can make cpu win the game
				if(won(grid,user)){	// checking if cpu has won? 
					return true; // if yes we return true that cpu has won
				}
				grid[i][j]=' '; // else we revert the placing of cpu in that position,i.e clear it again as of before it was
			}
		}
	}
	return false; // if none of the placements can make cpu win we return false
}


void play1(char (&grid)[3][3],char cpu,char user,int steps,int row,int col){      // function to be used when cpu is player 1
	// steps refer to which step of game we are in (zero based indexed) row,col is the position where user has placed his move in just earlier step

	// we follow the strategy of placing cpu in bottom left corner at first
	if(steps==0){ // at first we put cpu's symbol in bottom left corner
		grid[2][0]=cpu;
		return;
	}

	if(can_win(grid,cpu,user)){ // we check can win for cpu (can_win function is explained above)
		return; // return as we won
	}

	if(can_loose(grid,cpu,user)){ // as we have reached here it mean's cpu can't win at this moment,we check if user can_win i.e cpu can_loose
		return; // return as we are done with placement 
	}
	
	// when the user have made his first move we check if the centre is free,if user haven't placed at middle we can guarentee win of cpu B
	if(steps==2 && grid[1][1]==' '){ 
		if(!(row==0 && (col==0 || col==2)) && !(row==2 && col==2)){ // if user didn't placed at corners we place cpu at centre
			grid[1][1]=cpu;
			return;
		}
		else{  // if it is the diagonally opposite corner we place cpu at top left 
			if(row==0 && col==2){
				grid[0][0]=cpu;
				return;
			}
			// else we place cpu at diagonally opposite to already placed cpu i.e top right corner
 			else{ 
					grid[0][2]=cpu;
					return;
			}
		}
	}
	// if user place just above cpu in his first chance and then in next chance he saves him from loosing,after it we place cpu in bottom right corner 
	if(steps==4 && grid[1][0]==user && grid[0][2]==user){
		grid[2][2]=cpu;
		return;
	}
	// in all other cases we simply first try corners and then the middle of edges
	else{
		// here we are checking for free corners , if found, we place cpu's symbol there and return
		if(corner_check(grid,cpu))
			return;
	}

	// if there is no free corner we place it at some other location (middle of row/column) 
	if(edge_check(grid,cpu))
		return;

}

void play2(char (&grid)[3][3],char cpu,char user,int steps,int row,int col,bool corner){ // function to be used when cpu is player 2
	// steps refer to which step of game we are in (zero based indexed) row,col is the position where user has placed his move in just earlier step

	if(can_win(grid,cpu,user)){ // at first we check can_win for cpu (can_win is explained in can_win function)
		return;
	}

	if(can_loose(grid,cpu,user)){ // then we check can_lose for cpu
		return;
	}
		
		if(steps==1){ //for the first step of cpu we check if centre is empty
		if(grid[1][1]==user){// if not empty 
			grid[2][0]=cpu;  //we place cpu in top corner
			return;
		}
		else
			grid[1][1]=cpu; // else we place cpu in middle
		return;
	}

	// if the current step is 3 and the user's first move was corner
	if(steps==3 && corner){ 

	//	here we are blocking the possibilty of winning of user by placing cpu such that cpu can't have two simultaneous adjacent row's/column's benifit

		// if any of these are sequence of the placed user is true we block user by placing cpu at top middle
		if((grid[0][0]==user && grid[2][2]==user) ||(grid[0][2]==user && grid[2][0]==user)||(grid[0][0]==user && grid[1][2]==user) ||(grid[2][0]==user && grid[1][2]==user)){
			grid[0][1]=cpu;
			return;
		}
		// or any of these sequence of user's move is true we place cpu in left most column's middle
		else if((grid[0][0]==user && grid[2][1]==user)||(grid[0][2]==user &&grid[2][1]==user))
		{
			grid[1][0]=cpu;
			return;

		}
		//else we place cpu in top left corner
		grid[0][0]=cpu;
		return;
	}

	// when user's first move isn't corner
	// for other steps of move, we first check if possible we can place in corners if not we place in middle of some available edge
	   if(corner_check(grid,cpu))
			return;

		if(edge_check(grid,cpu))	
			return;	

}

// a function to be used when user is one of grid[2][1] or grid[1][2] in his first move
void play2_r(char (&grid)[3][3],char cpu,char user,int steps,int row,int col,bool corner){

    if(can_win(grid,cpu,user)){ // at first we check can_win for cpu (can_win is explained in can_win function)
        return;
    }

    if(can_loose(grid,cpu,user)){ // then we check can_lose for cpu
        return;
    }

    if(steps==1){ //for the first step of cpu we place cpu in the first row with column same as that of cpu
        grid[0][col]=cpu;
        return;
    }
	
	// in step 3 we try to block the future possiblity of user's win
	//	here we are blocking the possibilty of winning of user by placing cpu such that cpu can't have two simultaneous adjacent row's/column's benifit

    if(steps==3){
        if(grid[0][1]==cpu){ // if there is cpu in grid[0][1] it means it was due to the user in grid[2][1]
            if(grid[1][1]==user){ // if user is in middle we place cpu in top left corner
                grid[0][0]=cpu;
            }
            else{		
            //else we place cpu in grid[2][0]
                grid[2][0]=cpu;
            }
            
        }
        // if cpu is not in grid[0][1] it means user was not in grid[2][1],i.e user is in grid[1][2]
        else{
        	// if user is one of first two column of first row
            if(grid[0][0]==user || grid[0][1]==user){
                grid[1][0]=cpu;
            }
            //else if user is not one of first two column of first row
            else{
                grid[0][0]=cpu;
            }
        }
        return;
    }
	
	// if step=5 and centre is empty
    if(steps==5 && grid[1][1]==' '){
        grid[1][1]=cpu;
        return;
    }
    // in all other case we check corner first 
    if(corner_check(grid,cpu))
        return;
    //in all other case we check edge next
    if(edge_check(grid,cpu))    
        return; 

}


void go(){

	char grid[3][3]; // our gird for tic-tac-toe

	//we initalise it with ' '
    for(int i=0;i<3;++i){
    	for(int j=0;j<3;++j){
    		grid[i][j]=' ';
    	}
    }

    display(grid); // display empty grid

    // assign symbol to user and cpu corresponding to whether user is first player or second
    int which=-1;

    cout<<"Which Player you want to be 1 or 2 ? : ";
    cin>>which;

    char user='X',cpu='O'; // symbol to be assigned to cpu and user based on which player they are

	if(which==2){
		user='O';
		cpu='X';
	}

    cout<<"\nYou are user "<<which<<", use '"<<user<<"' as your symbol"<<"\n\n";

	int steps=0;// step variable to keep count of number of steps of game played,we use zero based indexing here

	int row=2,col=0; // row and col integer to maintain which row and column has the user moved
	
	bool corner=false; // boolean to check if user first attempt is corner
	
	bool user_is_right=false;// variable to check if user is first player and his move is one of the middle of right most row or botton most column
   
    while(!won(grid,user) || steps<9){ // we continoue placing until all the places are filled or cpu has won the game
    	
    	// if user is first player
    	if(user=='X'){
    		int pos=-1; // variable to take position input from user

    		cout<< "input the position of your move : ";
    		cin>> pos; //getting input from user for the position of placement of his move

    		row=(max(0,pos-1))/3; // figuring out which row it belongs

    		col=(pos+2)%3;	// which column it belongs
    		
    		grid[row][col]='X'; // place the user's symbol there
    		
    		display(grid); // display the gird
    		
    		steps++;// increasing the steps of game played (zero based indexing)
    		
    		if(steps==1){
    			corner=is_corner(grid,row,col); // checking if first attempt is corner
    		}
    		if(steps==9)break; // if we just had completely filled the grid we break

    		//checking if user is grid[2][1] or grid[1][2] in first step
    		if(steps==1&&(grid[2][1]==user || grid[1][2]==user)){
    			user_is_right=true;
    		}
    		//if yes we use function different from play2,we use play2_r
    		if(user_is_right){ 
    			play2_r(grid,'O','X',steps,row,col,corner);
    		}
    		//else we use play2 only
    		else{
    			play2(grid,'O','X',steps,row,col,corner); // cpu's turn, we pass the row and column of user's move and sybmol of user and cpu
    		}
    		display(grid);
    		
    		if(won(grid,user)){ // if the cpu won after placing we break;
    			break;
    		}
    		++steps; // increase step again as cpu has also played
    	}
    	// if user is second player
    	else{
    		play1(grid,'X','O',steps,row,col); // cpu plays
    		
    		steps++; // increase steps as cpu has just played
    		
    		display(grid); // display the grid after his play
    		
    		if(won(grid,user)){ // ifwe found cpu has won after his move we break
    			break;
    		}
    		// if we are done with all filling in grid we return 
    		if(steps==9)break;
    		
    		int pos=-1;
    		cout<< "input the position of your move : ";
    		cin>> pos; //getting input from user for the position of placement of his move
    		
    		row=(max(0,pos-1))/3;// figure out row of user's move
    		
    		col=(pos+2)%3; // figure out col of user's move
    		
    		grid[row][col]='O'; // place user,as user is second player his symbol is 'O'
    		
    		display(grid); // display grid after user's move
    		
    		steps++; // increase the steps as user has just moved

    	}
    }
    if(won(grid,user)){ // checking if cpu has won
    	cout<<"YOU LOSE!"<<'\n';
    }
    else if(won(grid,cpu)){ // checking if user has won
    	cout<<"YOU WON!! "<<'\n';
    }
    else{// if neighter user has won nor cpu has won ,it means it's a TIE!!
    	cout<<"THAT'S A TIE!!!!"<<'\n';
    }

    cout<<"Wants to play another game or not (Please reply in binary: 0 for No , 1 for Yes) \n";

    int once_more=-1; // variable used to figure out if user want to play again
    cin>>once_more;

    if(once_more==1){ // if got response that user want to play again
    	go(); //re-run the go function
    }
    return;

}


int main(){

	go(); // function responsible for creating matches

}


