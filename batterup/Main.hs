module Main where

import Data.List.Split

tokenToInts :: String -> [Int]
tokenToInts xs = map read (splitOn " " xs)

calcResult :: Int -> Int -> Float
calcResult a b = (fromIntegral a) / (fromIntegral b)
  
main :: IO ()
main = do
  count <- getLine
  param <- getLine
  let params = tokenToInts param
  let walksDiff = sum (filter (\n -> n == -1) params)
  let nonWalks = sum (filter (\n -> n >= 0) params)
  let result = calcResult nonWalks atBats where atBats = ((read count) + walksDiff)
  putStrLn (show result)
