module Main where

import Text.Printf

eucledianArea :: Float -> Float
eucledianArea radius = pi * (radius ^ 2)

taxicabArea :: Float -> Float
taxicabArea radius = 2 * (radius ^ 2)

main :: IO ()
main = do
  radius <- readLn :: IO Float
  let eucArea = eucledianArea radius
  let taxArea = taxicabArea radius
  printf "%.4f\n" eucArea
  printf "%.4f\n" taxArea
