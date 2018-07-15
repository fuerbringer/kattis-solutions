module Main where

castSpell a = putStrLn (show a ++ " Abracadabra")

barrage :: Int -> Int -> IO ()
barrage x b = do
  if x <= b
    then do
      castSpell x
      barrage (x + 1) b
    else putStrLn ""

main :: IO ()
main = do
  line <- getLine
  barrage 1 (read line)
