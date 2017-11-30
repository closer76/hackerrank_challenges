{- Super-Queen on a Chessboard -}
{- URL: https://www.hackerrank.com/challenges/super-queens-on-a-chessboard/problem -}

import Data.List

{- Solution 1: Original trial. -}
filterOut :: [Int] -> Int -> [Int] -> [Int]
filterOut [] _ = id
filterOut (x:xs) level = filterOut xs (level+1) . f
    where f = if level == 1 || level == 2
              then filter (\a -> abs(a-x) > 2)
              else filter (\a -> a /= x && a /= (x + level) && a /= (x - level))

solve_body :: Int -> [Int] -> Int
solve_body size [] = sum . map (solve_body size) . map (:[]) $ [1..size]
solve_body size queens = if length queens == size then 1
                         else sum . map (solve_body size) . map (:queens) . filterOut queens 1 $ [1..size]

solve n = solve_body n []

{- Solution 2: About 33% faster than Solution 1. -}
solve_body' :: (Int, Int) -> ([Int], [Int], [Int]) -> [Int] -> Int
solve_body' _ (_, _, queens) [] = 1
solve_body' (last2, last1) (diag, adiag, queens) left =
    sum $ map (\x -> solve_body' (last1, x) ((x-row):diag, (x+row):adiag, x:queens) $ delete x left) filtered
    where
        row = 1 + length queens
        filtered = [x | x <- left, abs(x-last2) /= 1, abs(x-last1) /= 2, not $ elem (x-row) diag, not $ elem (x+row) adiag]
                             
solve' n = solve_body' (100, 100) ([], [], []) [1..n]

main = do
    num <- fmap (read::String->Int) getContents
    putStrLn . show . solve' $ num
