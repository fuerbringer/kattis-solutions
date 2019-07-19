<?php

$instructions = [];
$memory = [];

//------------------------------------------------------------------------------

class Command
{  
  private $command;
  private $parameters; 

  public function __construct($command, $parameters) {
    $this->command = $command;
    $this->parameters = $parameters;
  }

  public function setCommand($command) {
    $this->command = $command;
  }

  public function setParameters($parameters) {
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

function cmp($a, $b) {
  if($a->line() == $b->line()) {
    return 0;
  }
  return ($a->line() < $b->line()) ? -1 : 1;
}

function lineToArrayIndex($a, $line) {
  for($i = 0; $i < size($instructions); $i++) {
    $ins = $instructions[$i];
    if($ins->line() == $line)
      return $i;
  }
  return -1;
}

//------------------------------------------------------------------------------

while(fscanf(STDIN, '%[^\n]', $in)){
  $inExpl = explode(' ', $in);
  $params = [];
  for($i = 2; $i < count($inExpl); $i++) {
    $params[] = $inExpl[$i];
  }
  $instructions[] = new Instruction(intval($inExpl[0]), $inExpl[1], $params);
}

usort($instructions, 'cmp');

for($i = 0; $i < size($instructions); $i++) {
  $ins = $instructions[$i];
  // TODO implement parsing and executing of instructions
  switch($ins->command()) {
  case 'LET':
    break;
  case 'IF':
    break;
  case 'PRINT':
    break;
  case 'PRINTLN':
    break;
  }
}

?>
