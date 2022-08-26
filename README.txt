Becky Lee, 811411949

INSTRUCTIONS FOR COMPILING, RUNNING, TESTING, AND ANSWERS FOR QUESTIONS

##############################################################################################

How to compile:
    In order to compile, implement the command:

    $make compile

    this command will execute the following command: gcc -Wall -pedantic -o fifteen fifteen.c which
    will create a new executable file under the name 'fifteen'

##############################################################################################

How to run:
    In order to run, implement the command:

    $./fifteen [board dimensions]

    replace the [board dimensions] with any integer value between 3 and 9. The minimum board size is
    3x3 and the maximum is 9x9, so any board dimensions will be valid.


    An example of how to run the program is:
    $./fifteen 3

    This will run the program with a board size of 3x3.

#################################################################################################


How to test:
    In order to test the given input files of 3x3 and 4x4, identify the txt files '3x3.txt' and
    '4x4.txt' in the project directory.

    Using the following input redirections below, you can automate the input and run the program:
    $./fifteen 3 < 3x3.txt
    $./fifteen 4 < 4x4.txt


    Both of these commands will lead to winning configurations.

#################################################################################################

How to clean:
    In order to clean, implement the command:
    $make clean

    The command clean will execute the command 'rm fifteen' which removes the executable file
    'fifteen' made during compiling.


##################################################################################################

Answers to the questions:

1. Besides 4x4, what other dimensions does the framework allow?
   the framework allows any dimensions between 3x3 and 9x9. So the valid board dimensions are 3x3, 4x4, 5x5
   6x6, 7x7, 8x8, and 9x9.

2. What data structure is used for representation of the game board?
   The game board is represented by a matrix and a 2D array.

3. What function is called to greet the player?
   The function greet() is called.

4. What functions do you need to implement?
   This project required us to implement the functions of move, won, draw, and init.
