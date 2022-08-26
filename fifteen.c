#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/**
 * We want to set up constants for the board size consisting
 * of the smallest board size and the biggest board size
 *
 */
#define BOARD_MIN 3
#define BOARD_MAX 9

/**
 * Various board variables used to track player's tile
 * movement.
 */

int tileRow;
int tileCol;
int dimension;
int newRow = -1;
int newCol = -1;

/**
 * Setting up Board dimensions for ouput
 *
 * The smallest board dimension is a 3x3 while the biggest board dimension is a 9x9
 */
int board[BOARD_MIN][BOARD_MAX];

// Function Prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
int move(int tile);
int won(void);

int main(int argc, char* argv[]) {
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    dimension = atoi(argv[1]);
    if (dimension < BOARD_MIN || dimension > BOARD_MAX) {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            BOARD_MIN, BOARD_MIN, BOARD_MAX, BOARD_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL) {
        return 3;
    }

    /**
     * If the file opens successfully, the program will provide the
     * prompt to the user.
     *
     * The user will then have the option to move tiles.
     */
    greet();

/**
 * Calls function to initialize board
 */
    init();

    //accepts moves until game is won
    while (1) {
        clear();
        draw();

        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                fprintf(file, "%i", board[i][j]);
                if (j < dimension - 1) {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("win!\n");
            break;
        }

        // prompt for move
        printf("Tile to move (0 to exit): ");
        int tile;
		scanf("%d", &tile);
		getchar();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(50000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

/**
 * This function intiializes the game board
 *
 * The function will fill the game board with the value of tiles.
 */
void init(void) {
    /**
     * The program intiializes the game board with the highest valid tile value
     *
     * tile value must be less than the dimension of the board in order to qualify for
     * a valid tile.
     */
    int tiles = (dimension * dimension)-1;


    /**
     * Copying tiles onto the board in form of 2d array
     *
     * We are not printing any tile values here but instead just
     * placing them into the game board.
     */

	for (int i = 0; i < dimension; i++){
		for(int j = 0;j < dimension; j++){
			board[i][j] = tiles--;
		}
	}


    /**
     * In case the board contains an odd number of tiles,
     *
     * The position of tiles numbered 1 through 2 are swapped. This
     * ensures even tile dimensions.
     */
	if(!((dimension * dimension) %2 == 0)){
		board[dimension - 1][dimension-2] = 2;
		board[dimension - 1][dimension - 3] = 1;
	}// if

}

/**
 * This function prints the board as different moves commense
 *
 * After the player makes a move, the board will reprint to the new
 * tile locations
 */
void draw(void) {
    //printing board in current state
  for(int i=0;i < dimension;i++) {
    /**
     * Printing the blank space for player's tile position
     *
     */

	for(int j=0;j < dimension;j++){
		if(board[i][j] == 0){printf(" _ ");}
		else{printf(" %d ", board[i][j]);}
	}
    //seperating each row
    printf("\n");

  } //for
}

/**
 * This function will dictate all the valid and invalid moves the player can make
 *
 * The function will first check the value of tile the player wants to move to
 * and if it is a valid spot, the program will move accordingly.
 */
int move(int tile) {
    /**
     * ERROR case: if the tile chosen by the user is negative or it is bigger
     * than the board's dimensions.
     */
	if(tile <= 0 || tile > (dimension * dimension)) {
        return 0;
    } //if

    /**
     * If the player's tile choice is valid, set the board's
     * new tile to the player's tile choice.
     */

	for (int i=0; i < dimension; i++) {
		for (int j=0;j < dimension; j++) {
			if(board[i][j] == tile) {
				tileRow = i;
				tileCol = j;
			}// if
		}// for
	}// for

    /**
     * This is the fail case when the player can make
     * no valud moves.
     *
     * the program will return -1 on failure;
     */
    if (newRow == -1 || newCol == -1) {
        return 0;
    } // if

    /**
     * This if statement checks the right tile of the player's desired
     * location
     *
     * The new column and the new row will shift right by 1 tile.
     */
    if(tileCol+1 <= dimension - 1 && board[tileRow][tileCol+1] == 0) {
        newRow = tileRow;
        newCol = tileCol+1;
    }

    /**
     * checking left tile of player's desired location
     *
     * shfts over left by 1 tile.
     */
    if(tileCol-1 >= 0 && board[tileRow][tileCol-1] == 0) {
        newRow = tileRow;
        newCol = tileCol -1;

    }

    /**
     * This if statement checks the below tile of the player's desired location
     *
     * The new Row will shift down by 1 tile.
     */

	if(tileRow-1 >= 0 && board[tileRow-1][tileCol] == 0){
		newRow = tileRow-1;
		newCol = tileCol;
	}


    /**
     * This if statment checks the above tile of the player's desired location
     *
     *  The new row will shift up by 1 tile.
     */
	if(tileRow+1 <= dimension - 1 && board[tileRow+1][tileCol] == 0){
		newRow = tileRow+1;
		newCol = tileCol;
	}


	/**
     * After checking player's inputted tile, program will
     * switch the empty space with the chosen tile.
     *
     * we want to set equal the chosen tile board to the original
     * board before the swap.
     */
	board[newRow][newCol] = board[tileRow][tileCol];
	board[tileRow][tileCol] = 0;

	return 1;
}


/**
 * Checks if the winning board configurations are met
 *
 * Function will iterate through the board to see if tiles are
 * all correct and will increment for every tile that is checked.
 */



int won(void) {
    int correct = 0;
    for(int i = 0, j= 0; i<dimension; i++, j++) {
        for(int j= 0; j<dimension-1; j++) {

            /**
             * Check if the board is still larger than the
             * shifted tile.
             */
            if(board[i][j] > board[i][j+1]) {
                  correct++;
                  if ((j== dimension-2)) {
                      if(i < dimension -1) {
                          if(board[i][j+1] > board[i-1][j]) {
                            correct++;
                          } //if
                      } //if
                  } //if
            } //if
        } //for
    } //for
    return 0;
} //won
