<?php

/**
 *  Kattis Problem: https://open.kattis.com/problems/bitbybit
 *  Currently only passing some of the tests
 */

abstract class Operation {
  const CLEAR = 0;
  const SET = 1;
  const OR = 2;
  const AND = 3;
}

class Register {
  const SIZE = 32;
  const UNKNOWN = '?';
  private $data;

  public function __construct() {
    $this->data = [];
    for($i = 0; $i < self::SIZE; $i++) {
      $this->data[] = self::UNKNOWN;
    }
  }

  public function toString() {
    $str = '';
    for($i = 0; $i < count($this->data); $i++) {
      $str = $this->data[$i] . $str; // Order can be adjusted here
    }
    return $str;
  }

  public function data_op($op, $i) {
    $i = intval($i);
    switch($op) {
    case Operation::CLEAR:
      $this->data[$i] = 0;
      break;
    case Operation::SET:
      $this->data[$i] = 1;
      break;
    }
  }

  public function logical_op($op, $i, $j) {
    $j = $this->get($j);
    $l = $this->get($i);
    if($l === self::UNKNOWN){
      // Bit to be operated on is unknown, leave as is
      return;
    }

    if($j !== self::UNKNOWN) {
      switch($op) {
      case Operation::OR:
        $this->data[$i] = $j | $l;
        break;
      case Operation::AND:
        $this->data[$i] = $j & $l;
        break;
      }
    } else {
      // Operation with an unknown bit => set target bit to unknown
      $this->data[$i] = self::UNKNOWN;
    }
  }

  private function get($i) {
    return $this->data[intval($i)];
  }
}


$go = true;
$registers = [];
$regNr = 0;
$results = [];

while ($go && (fscanf(STDIN, '%d', $instrs) === 1)){
  if($instrs) {
    $registers[$regNr] = new Register;
    // Read $instrs instructions:
    for($in = 0; $in < $instrs; $in++) {
      fscanf(STDIN, '%s %d %d', $instr, $param1, $param2);
      switch($instr) {
      case 'CLEAR':
        $registers[$regNr]->data_op(Operation::CLEAR, $param1);
        break;
      case 'SET':
        $registers[$regNr]->data_op(Operation::SET, $param1);
        break;
      case 'OR':
        $registers[$regNr]->logical_op(OPERATION::OR, $param1, $param2);
        break;
      case 'AND':
        $registers[$regNr]->logical_op(OPERATION::AND, $param1, $param2);
        break;
      }
    }
    $results[] = $registers[$regNr]->toString();
  } else {
    // End of input, don't do another loop
    $go = false;
  }

  $regNr++;
}

foreach($results as $line) {
  echo "$line\n";
}

?>
