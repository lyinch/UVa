#include <iostream>
#include <queue>

using namespace std;

//struct which is used by the queue to save the pieces position
struct t_pos{
  int x;
  int y;
  int piece;
};

string  k_colour;
//to remove
int pos_x_w, pos_x_b, pos_y_w, pos_y_b; //king position for both colours

enum colour_en {black = 0, white = 1};

//check if the position is still in the board
bool in_range(int x, int y){
  if((x < 0) || (x > 7) || (y < 0) || (y > 7))
    return false;
  
  return true;
}

//iterative call for pawn, knight
//gets coordinate of piece and the direction to check for, and the colour of the piece 0 for black, 1 for white
bool control_check_i(const char (&board)[8][8],int x, int y, int dir_x, int dir_y, int colour){
  x += dir_x;
  y += dir_y;
  if(!in_range(x,y))
    return false;
 
  if(board[x][y] == 'K' && colour == black){
    k_colour = "white";
    return true;
  }
  
  if(board[x][y] == 'k' && colour == white){
    k_colour = "black";
    return true;
  }
  
  return false;
}

//recursive call for queen, bishop, rook
bool control_check_r(const char (&board)[8][8], int x, int y, int dir_x, int dir_y, int colour){
  x += dir_x;
  y += dir_y;
  char king;
  //check if in range
  if(!(in_range(x,y)))
     return false;

  
  if(colour == white)
    king = 'k';
  else
    king = 'K';
  //check if king is in check
  if(board[x][y] == king){
    //cout << "CHECK(" << x << " " << y << ") " << " " << dir_x << " " << dir_y << " " << king <<  endl;
    
    if(king == 'k')
      k_colour = "black";
    else
      k_colour = "white";
    
    return true;
  }

  //if another piece blocks line of sight
  if(board[x][y] != '.')
    return false;

  control_check_r(board,x,y,dir_x,dir_y,colour);

 
  return false;
}

//determines the piece and calls the necessery function to see if king of opposite colour is in check
bool call_check_function(const char (&board)[8][8],t_pos piece_input){
  int colour;

  //set colour of piece
  if(isupper(piece_input.piece))
    colour = white;
  else
    colour = black;
  
  switch(piece_input.piece){
  case 'p': //black pawn
    control_check_i(board,piece_input.x,piece_input.y,-1,+1,colour);
    control_check_i(board,piece_input.x,piece_input.y,+1,+1,colour);
    break;
  case 'P': //white pawn
    control_check_i(board,piece_input.x,piece_input.y,-1,-1,colour);
    control_check_i(board,piece_input.x,piece_input.y,+1,-1,colour);
    break;
  case 'n': //knight
  case 'N':
    control_check_i(board,piece_input.x,piece_input.y,-1,2,colour);
    control_check_i(board,piece_input.x,piece_input.y,1,2,colour);
    control_check_i(board,piece_input.x,piece_input.y,-1,-2,colour);
    control_check_i(board,piece_input.x,piece_input.y,1,-2,colour);

    control_check_i(board,piece_input.x,piece_input.y,-2,1,colour);
    control_check_i(board,piece_input.x,piece_input.y,-2,-1,colour);
    control_check_i(board,piece_input.x,piece_input.y,2,-1,colour);
    control_check_i(board,piece_input.x,piece_input.y,2,1,colour);
    break;
  case'r': //rook
  case'R':
    control_check_r(board,piece_input.x,piece_input.y,1,0,colour);
    control_check_r(board,piece_input.x,piece_input.y,-1,0,colour);
    control_check_r(board,piece_input.x,piece_input.y,0,1,colour);
    control_check_r(board,piece_input.x,piece_input.y,0,-1,colour);
    break;
  case 'b':
  case 'B':
    control_check_r(board,piece_input.x,piece_input.y,1,1,colour);
    control_check_r(board,piece_input.x,piece_input.y,1,-1,colour);
    control_check_r(board,piece_input.x,piece_input.y,-1,-1,colour);
    control_check_r(board,piece_input.x,piece_input.y,-1,1,colour);	
    break;
  case 'q':
  case 'Q':
    //elements from rook
    control_check_r(board,piece_input.x,piece_input.y,1,0,colour);
    control_check_r(board,piece_input.x,piece_input.y,-1,0,colour);
    control_check_r(board,piece_input.x,piece_input.y,0,1,colour);
    control_check_r(board,piece_input.x,piece_input.y,0,-1,colour);
    //elements from bishop
    control_check_r(board,piece_input.x,piece_input.y,1,1,colour);
    control_check_r(board,piece_input.x,piece_input.y,1,-1,colour);
    control_check_r(board,piece_input.x,piece_input.y,-1,-1,colour);
    control_check_r(board,piece_input.x,piece_input.y,-1,1,colour);
    break;
  } //to add: default for queen, rook and bishop
  
  
  return false;
}

bool board_empty(const char (&board)[8][8]){
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      if((board[x][y]) != '.')
	return false;
    }
  }
  return true;
}

int main(void){
  queue <t_pos> pos;
  t_pos pos_tmp; //used to get elements from the queue, because it's based on the struct
  char board[8][8];
 
  int iterator = 1;
  string tmp_str;
  bool is_empty = false;
  
  while(true){
    //read in chess board
    k_colour = "no";
    
    for(int y = 0; y < 8; y++){
      cin >> tmp_str;
      for(int x = 0;  x < 8; x++){
	board[x][y] = tmp_str[x];
	//save positions of pieces to que/position of kings to variables
	if((tmp_str[x] != '.') && (tmp_str[x] != 'k') && (tmp_str[x] != 'K') ){
	  pos_tmp.x = x;
	  pos_tmp.y = y;
	  pos_tmp.piece = tmp_str[x];
	  pos.push(pos_tmp);
	}
      }
    }

    //call function to see if king is in check for every piece
    while(!pos.empty()){
      pos_tmp = pos.front(); //takes the first element of the queue
      call_check_function(board,pos_tmp);
      pos.pop(); //removes the first element of the queue
    }

    if(!board_empty(board))
      cout << "Game #" << iterator << ": " << k_colour << " king is in check." << endl;
    else
      break;
    
    
    iterator++;
  } //end endless loop (lol)

  
  return 0;
}
