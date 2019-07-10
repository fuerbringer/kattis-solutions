<?php

$results = [];

while (fscanf(STDIN, '%[^\n]', $in)){
  $ns = explode(' ', $in);
  for($i = 0; $i < count($ns); $i++) {
    $sum = 0;
    for($j = 0; $j < count($ns); $j++) {
      if($i !== $j) {
        $sum += $ns[$j];
      }
    }
    if($sum == $ns[$i]) {
      $results[] = str_replace("\n", '', $ns[$i]);
      break;
    }
  }
  if(!is_string($in)) {
    if(feof($in)) {
      break;
    }
  }
}

foreach($results as $r) {
  if(strlen($r)) {
    echo "$r\n";
  }
}

?>
