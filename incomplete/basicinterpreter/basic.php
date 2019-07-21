<?php
//------------------------------------------------------------------------------
// NOTE:  This BASIC interpreter is by no means complete or fully featured.
//        It is specifically designed to pass the open.kattis.com challenge
//        "basicinterpreter" and misses features such as error handling and
//        proper arithmetic.
//
//        This solution is technically working, but is not performant enough to
//        pass as kattis submission.
//



//------------------------------------------------------------------------------
// Globals

$instructions = [];
$memory = [];


//------------------------------------------------------------------------------
// Classes
class Command
{  
  private $command;
  private $parameters; 

  public function __construct($command, $parameters) {
    $this->command = $command;
    $this->setParameters($parameters);
  }

  public function setCommand($command) {
    $this->command = $command;
  }

  public function setParameters($parameters) {
    for($i = 0; $i < count($parameters); $i++) {
      $parameters[$i] = str_replace("\n", '', $parameters[$i]);
    }
    $this->parameters = $parameters;
  }

  public function command() {
    return $this->command;
  }

  public function parameters() {
    return $this->parameters;
  }
}

class Instruction extends Command {
  private $line;  // 10, 20, etc..

  public function __construct($line, $command, $parameters) {
    $this->line = $line;
    parent::__construct($command, $parameters);
  }

  public function setLine($line) {
    $this->line = $line;
  }

  public function line() {
    return $this->line;
  }
}

//------------------------------------------------------------------------------
// Functions
function cmp($a, $b) {
  if($a->line() == $b->line()) {
    return 0;
  }
  return ($a->line() < $b->line()) ? -1 : 1;
}


//------------------------------------------------------------------------------
// Figure out what array-index $line has in instruction list $instructions.
function lineToArrayIndex($instructions, $line) {
  for($i = 0; $i < count($instructions); $i++) {
    $ins = $instructions[$i];
    if($ins->line() == $line)
      return $i;
  }
  return false;
}

function to32BitSigned($n) {
  // Enforce 32-bit signed arithmetic as required by the problem description.
  // That's what I get for solving this in PHP..
  $mv = $n & 0xFFFFFFFF;
  if ($mv & 0x80000000) {
    $mv = $mv & ~0x80000000;
    $mv = -2147483648 + $mv;
  }
  return $mv;
}

function assignmentToMemCmd($params, $memory) {
  /*
    POSSIBLE PARAMS
    count($params) == 3 means simple assignment:
    <VAR> = <NUM>
    <VAR> = <VAR>
    count($params) == 5 means assignment with arithmetic:
    <VAR> = <NUM> {+,-,*,/} <NUM>
    <VAR> = <VAR> {+,-,*,/} <NUM>
    <VAR> = <NUM> {+,-,*,/} <VAR>
    <VAR> = <VAR> {+,-,*,/} <VAR>
   */
  $memVar = $params[0];
  if(count($params) === 3) {
    $rval = $params[2];
    if(is_numeric($rval)) {
      // Var-to-num assignment
      $rval = intval($rval);
    } else {
      // Var-to-var assignment
      $rval = $memory[$rval];
    }
    $memory[$memVar] = $rval;
  } else if(count($params) === 5) {
    // Assignment with arithmetic
    $val1 = $params[2];
    $op = $params[3];
    $val2 = $params[4];

    // Read vals from memory if needed
    if(is_numeric($val1)) {
      $val1 = intval($val1);
    } else {
      $val1 = $memory[$val1];
    }
    if(is_numeric($val2)) {
      $val2 = intval($val2);
    } else {
      $val2 = $memory[$val2];
    }

    switch($op) {
    case '+':
      $memory[$memVar] = $val1 + $val2;
      break;
    case '-':
      $memory[$memVar] = $val1 - $val2;
      break;
    case '*':
      $memory[$memVar] = $val1 * $val2;
      break;
    case '/':
      $memory[$memVar] = $val1 / $val2;
      break;
    }
    $memory[$memVar] = to32BitSigned((int)($memory[$memVar]));
  }
  return $memory;
}

function printCmd($str, $memory, $nl = false) {
  if(is_string($str) && strlen($str) >= 2) {
    if($str[0] === '"' && $str[strlen($str) - 1] === '"') {
      // Literal string
      $str = substr($str, 1, -1);
    }
  } else {
    // Variable
    $str = $memory[$str];
  }

  if($nl) {
    $str .= "\n";
  }

  echo $str;
}

function ifCmd($params, $memory) {
  /*
  [0] => <NUM or VAR>
  [1] => X = Y, X > Y, X < Y, X <> Y, X <= Y, or X >= Y
  [2] => <NUM or VAR>
  [3] => THEN
  [4] => GOTO
  [5] => <NUM>
  */
  $comp = $params[1];
  $val1 = $params[0];
  $val2 = $params[2];
  $line = $params[5];
  $goto = false;
  if(is_numeric($val1)) {
    $val1 = intval($val1);
  } else {
    $val1 = $memory[$val1];
  }
  if(is_numeric($val2)) {
    $val2 = intval($val2);
  } else {
    $val2 = $memory[$val2];
  }
  switch($comp) {
  case '=':
    $goto = $val1 == $val2; 
    break;
  case '>':
    $goto = $val1 > $val2; 
    break;
  case '<':
    $goto = $val1 < $val2; 
    break;
  case '<>':
    $goto = $val1 != $val2; 
    break;
  case '<=':
    $goto = $val1 <= $val2; 
    break;
  case '>=':
    $goto = $val1 >= $val2; 
    break;
  }
  if($goto) {
    return intval($line);
  }
  return false;
}


//------------------------------------------------------------------------------
// Read in BASIC instructions line-by-line.
while(fscanf(STDIN, '%[^\n]', $in)){
  $inExpl = explode(' ', $in);
  $params = [];

  // Skip first two elems because everything $i >= 2 are parameters for the
  // command ($inExpl[1] or $ins->parameters()).
  for($i = 2; $i < count($inExpl); $i++) {
    $params[] = $inExpl[$i];
  }
  $instructions[] = new Instruction(intval($inExpl[0]), $inExpl[1], $params);
}


//------------------------------------------------------------------------------
// Instructions may be passed in an arbitrary order; make order ready for
// execution.
usort($instructions, 'cmp');


//------------------------------------------------------------------------------
// BASIC parser and interpreter

// We run through the sorted instructions.
// GOTOs are handled by simply setting $i to whatever ::line() corresponds (see
// lineToArrayIndex()).
for($i = 0; $i < count($instructions); $i++) {
  $ins = $instructions[$i];
  switch($ins->command()) {
  case 'LET':
    $memory = assignmentToMemCmd($ins->parameters(), $memory);
    break;
    //----------------------------------------------------------------------------
  case 'IF':
    $line = ifCmd($ins->parameters(), $memory);
    if($line !== false) {
      // IF evaluated to true, so we do the GOTO
      $l = lineToArrayIndex($instructions, $line);
      if($l !== false) {
        $i = $l - 1;
      }
    }
    break;
    //----------------------------------------------------------------------------
  case 'PRINT':
    printCmd(implode(' ', $ins->parameters()), $memory);
    break;
    //----------------------------------------------------------------------------
  case 'PRINTLN':
    printCmd(implode(' ', $ins->parameters()), $memory, true);
    break;
    //----------------------------------------------------------------------------
    // default: noop, unrecognized command
  }
}
// print_r($memory);

?>
