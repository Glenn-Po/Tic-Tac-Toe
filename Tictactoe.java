import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.*;
//import java.util.Scanner;

//TODO
//check how to resolve position to board cell

//#[Two player] mode only
class Tictactoe{
    String[] template;
    char[][] board;
    final char[] LEGAL_PLAYER = new char[]{'O', 'X'};
    //colors
    //GREEN, BRIGHT_YELLOW, YELLOW, RED, FUCHSIA, CYAN
    //effects
    //UNDERLINE, STRIKETHROUGH, BOLD
    private void init(){
        this.template = new String[]{
                " ------------------",
                " |  *  |  *  | *  |",
                " |-----+-----+----|",
                " |  *  |  *  | *  |",
                " |-----+-----+----|",
                " |  *  |  *  | *  |",
                " ------------------"
                };

        this.board = new char[][]{
                new char[]{'1', '2', '3'},
                new char[]{'4', '5', '6'},
                new char[]{'7', '8', '9'}
        };
    }

    private boolean isAvailable(int pos){
        if(pos<1 || pos>9) return false;
        //int row = ((pos % 3) + 2)%3, column =  ((pos+2) / 3) - 1; //correct later
        pos = pos - 1;//resolve from 1 to 9 to 0-8
        int row = pos/3, column = pos%3;
        return !(this.board[row][column] == this.LEGAL_PLAYER[0] || this.board[row][column] == this.LEGAL_PLAYER[1]);
    }
    private void playAt(int pos, char player){
        //this assumes that the position is available
        //int x =((pos % 3) + 2)%3, y = ((pos+2) / 3) - 1;
        pos = pos - 1;//resolve from 1 to 9 to 0-8
        int row = pos/3, column = pos%3;
        this.board[row][column] = player;

    }
    private void fillTemplate(){
        for(byte in = 0; in < this.template.length; ++in)
            this.template[in] = this.template[in].replace("*", "%c");

        /*for(byte line = 0; line<3 ; line++){
            for(byte column = 0; column < 3; column++){
                this.template[(line+1)*2][5+column*6] = this.board[line][column];
            }
        }*/
}
    private void printBoard() {
        this.fillTemplate();
        int in = 0;
        for (String line : this.template) {
            if((in+1)%2 == 0)
                System.out.printf(line, this.board[in/2][0],this.board[in/2][1],this.board[in/2][2]);
            else
                System.out.print(line);
            System.out.println();
            in++;
        }
    }

    public char checkForWin(){
        //check leading diagonal
        if(this.board[0][0]==board[1][1] && board[1][1]==board[2][2])
            return board[0][0];
        //check alternate diagonal
        if(this.board[0][2]==board[1][1] && board[1][1]==board[2][0])
            return board[0][2];
        //check the columns
        for(byte col=0; col<3; ++col){
            if(this.board[0][col]==board[1][col] && board[1][col]==board[2][col])
                return board[1][col];
        }
        //check the rows
        for(byte row=0 ; row<3; ++row){
            if(this.board[row][0]==this.board[row][1] && this.board[row][1]==this.board[row][2])
                return this.board[row][0];
        }
        //if no win detected, return space char
        return ' ';
    }

    //helper method to check if a particular player has already played on a winning line
    private boolean hookedHere(char one, char two, char three){
        boolean first = (one== LEGAL_PLAYER[0] || two ==LEGAL_PLAYER[0] || three ==LEGAL_PLAYER[0]),
                second = (one== LEGAL_PLAYER[1] || two ==LEGAL_PLAYER[1] || three ==LEGAL_PLAYER[1]);

        return (first&second);
    }
    public boolean isATie(){

        //check for tie by checking all winning opportunities and identifying that none is possible
        boolean winningSpotFound = false;

        //first assume the game is a tie then try to find possibility of a win

        //it is a tie if 2 opposing players are in the same winning line for all 6 winning lines
        //check leading diagonal
        if(!this.hookedHere(board[0][0], board[1][1], board[2][2]))
            winningSpotFound = true;
        //check alternate diagonal
        if(!this.hookedHere(this.board[0][2], board[1][1], board[2][0]))
            winningSpotFound = true;
        //check the columns
        for(byte col=0; col<3; ++col){
            if (!this.hookedHere(this.board[0][col], board[1][col], board[2][col])) {
                winningSpotFound = true;
                break;
            }
        }
        //check the rows
        for(byte row=0 ; row<3; ++row){
            if (!this.hookedHere(this.board[row][0], board[row][1], board[row][2])) {
                winningSpotFound = true;
                break;
            }
        }

        return !winningSpotFound;
    }

    private int getPlayerPos() {
        // Scanner scan = new Scanner(System.in);
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        boolean posGotten = false;
        int pos = 0;
        while(!posGotten){
            System.out.print("Enter a position to play in: ");
            try {
                pos = Integer.parseInt(String.valueOf(reader.readLine().strip().toCharArray()[0]));
            } catch (NumberFormatException e) {
                System.out.println("Number Format not Correct::");
            } catch (IOException e) {
                System.out.println("Input Error: Error accepting input");
                //e.printStackTrace();
            }
            if(this.isAvailable(pos))
                posGotten = true;
            else System.out.print("Unavailable--o_o--\n");
        }
        return pos;
    }
    
    public void playGame(){

        System.out.println("============================");
        this.printBoard();
        char Player1 = this.LEGAL_PLAYER[0], Player2=this.LEGAL_PLAYER[1],
        curPlayer = Player1;
        while(true){
            if(this.isATie()){
                System.out.println("Game is a TIE!!!!!!!!!");
                break;
            }
            char winner  = checkForWin();
            if(winner != ' '){
                System.out.println("Game Over .. Player \""+winner+ "\" wins (^_^) + (-_-) + (*_*)");
                break;
            }

            System.out.println("PLAYER "+(curPlayer)+" Play: ");
            this.playAt(this.getPlayerPos(), curPlayer);

            if(curPlayer==Player1 )
                curPlayer = Player2;
            else if(curPlayer == Player2)
                curPlayer = Player1;
            this.printBoard();
        }
        

    }
    public static void main(String[] args){
        System.out.print("\033[92m     Tic Tac Toe");
        System.out.print("\033[95m   Tic Tac Toe");
        System.out.print("\033[97m     Tic Tac Toe");
        System.out.print("\033[93m   Tic Tac Toe\n");
        Tictactoe newGame = new Tictactoe();
        newGame.init();
        newGame.printBoard();
        newGame.playGame();
    }
}