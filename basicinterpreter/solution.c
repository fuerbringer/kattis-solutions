#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_LET     "LET"
#define COMMAND_IF      "IF"
#define COMMAND_PRINT   "PRINT"
#define COMMAND_PRINTLN "PRINTLN"
#define INSTRUCTION_SEP " "

struct command {
  int statement;
  char* instruction;
  char* parameters;
};

/**
 * Tokenize a string to a command structure
 * "10" -> statement (number)
 * "LET" -> instruction
 * "X = 10" -> parameter
 */
struct command create_command_from_str(char* str) {
  struct command cmd;
  char* token = strtok(str, INSTRUCTION_SEP);
  std::size_t i = 0;
  for (; token; token = strtok(NULL, INSTRUCTION_SEP), i++) {
    switch(i) {
    case 0:
      cmd.statement = atoi(token);
      break;
    case 1:
      cmd.instruction = (char*)malloc(strlen(token) * sizeof(char));
      strcpy(cmd.instruction, token);
    case 2:
      cmd.parameters = (char*)malloc(strlen(token) * sizeof(char));
      strcpy(cmd.parameters, token);
      break;
    default:
      cmd.parameters = (char*)realloc(cmd.parameters, (strlen(cmd.parameters) + strlen(token) + 2) * sizeof(char));
      strcat(cmd.parameters, " ");
      strcat(cmd.parameters, token);
      break;
    }
  }
  return cmd;
}

/**
 * >= 0 GOTO specific command
 * -1 Proceed to next command
 * -2 Error
 */
int execute_command(struct command* cmd, int* memory) {
  if(strcmp(cmd->instruction, COMMAND_LET) == 0) {
    // TODO evaluate arithmetic expression
  } else if(strcmp(cmd->instruction, COMMAND_IF) == 0) {
  } else if(strcmp(cmd->instruction, COMMAND_PRINT) == 0) {
    for(size_t i = 1; i < strlen(cmd->parameters) - 1; i++) {
      putchar(cmd->parameters[i]);
    }
  } else if(strcmp(cmd->instruction, COMMAND_PRINTLN) == 0) {
    for(size_t i = 1; i < strlen(cmd->parameters) - 1; i++) {
      putchar(cmd->parameters[i]);
    }
    putchar('\n');
  }
  return 0;
}

void destroy_command(struct command* cmd) {
  free(cmd->instruction);
  free(cmd->parameters);
}

int main(const int argc, const char* argv[]) {
  static int memory[26]; // 'A'..'Z'

  char sample[100];
  //strcpy(sample, "10 LET X = 21");
  //strcpy(sample, "10 IF X <= THEN GOTO 20");
  strcpy(sample, "10 PRINTLN \"HELLO THERE !\"");
  struct command myCmd = create_command_from_str(sample);

  //printf("RESULT:\nSTATEMENT %d\nINSTRUCTION %s\nPARAMETER %s", myCmd.statement, myCmd.instruction, myCmd.parameters);
  execute_command(&myCmd, memory);

  destroy_command(&myCmd);

  return EXIT_SUCCESS;
}

/*
The BASIC computer programming language has been popular for many years, and there have been dozens of ‘dialects’ of the language. It’s considered a high-level language and is typically interpreted (rather than compiled). For this problem, write an interpreter for a restricted dialect of BASIC. Here is a description of the language.

Each input line contains one statement. Each statement begins with a non-negative integer, which we will call its label. Following the label is a single space and one of the following commands (with explanations following):

    LET X = <ARITHMETIC_STATEMENT>
    Assign the result of the arithmetic statement to variable X.

    IF <CONDITION> THEN GOTO L
    If the boolean given is true, then go to the statement labeled L, where L is a valid label. (If the condition is not true, continue execution to the statement with the next lowest label.)

    PRINT <PRINT_STATEMENT>
    Produce output, without an appended newline.

    PRINTLN <PRINT_STATEMENT>
    Produce output, with an appended newline.

Here are details on types, variables, and the terms <ARITHMETIC_STATEMENT>, <CONDITION>, and <PRINT_STATEMENT> used above.

    All numeric values (in the input and for the variable representation) are signed 32-bit integers.

    All variables are single uppercase characters (A through Z). They are all global in scope, and are all initialized to zero before program execution begins.

    <ARITHMETIC_STATEMENT> is one of the following: X, X + Y, X - Y, X * Y, or X / Y. Here, X and Y each indicate either a variable or an integer.

    <CONDITION> is one of the following: X = Y, X > Y, X < Y, X <> Y, X <= Y, or X >= Y. Again, X and Y each indicate either a variable or an integer. Here, <> indicates inequality.

    <PRINT_STATEMENT> is either a variable name or a literal string delimited by double quotes. Inside the quotes, the string contains only alphanumeric characters (a-z, A-Z, 0-9) and spaces.

In the signed 32-bit arithmetic, the usual rules of truncation towards zero (for division) and overflow (for addition and multiplication) and underflow (for subtraction) apply. The following examples illustrate these conditions:

5 / 2           = 2                  65536 * 32768   = -2147483648
-1 / 2          = 0                  -65536 * 32768  = -2147483648
2147483647 + 1  = -2147483648        -2147483648 * 2 = 0
-2147483648 - 1 = 2147483647         2147483647 * 2  = -2

Further, division by zero will not occur.

Program execution begins with the statement having the smallest label, and proceeds with the statement having the next smallest label. (Unless a GOTO executes, in which case execution proceeds at the designated label.) The program halts after it has completed the statement with the largest label (which is guaranteed not to contain a GOTO).
Input

Input consists of a single program. Each line contains a single valid statement. Each pair of adjacent tokens in the input is separated by a single space. Integers in the input will all be in the range −231
to 231−1

. Input ends at end of file.
Output

Give the output (PRINT and PRINTLN statements) of the input program when it is executed.
Sample Input 1 	Sample Output 1

10 LET A = 1
20 PRINT "HELLO THERE "
30 PRINTLN A
40 LET A = A + 1
50 IF A <= 5 THEN GOTO 20
60 PRINTLN "DONE"

	

HELLO THERE 1
HELLO THERE 2
HELLO THERE 3
HELLO THERE 4
HELLO THERE 5
DONE

Sample Input 2 	Sample Output 2

40 PRINT P
180 PRINTLN "DONE"
130 PRINTLN " IS PRIME"
60 LET X = D * D
80 LET R = P / D
100 LET R = P - R
20 LET D = 1
140 IF 1 = 1 THEN GOTO 180
30 LET P = 111
150 PRINTLN " IS NOT PRIME"
170 PRINTLN " IS A DIVISOR"
50 LET D = D + 1
70 IF P < X THEN GOTO 130
120 IF 1 = 1 THEN GOTO 50
90 LET R = R * D
110 IF R = 0 THEN GOTO 150
10 PRINTLN "PRIME TESTER"
160 PRINT D

	

PRIME TESTER
111 IS NOT PRIME
3 IS A DIVISOR
DONE
*/
